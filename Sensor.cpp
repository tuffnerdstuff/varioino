/*
 * Sensor.cpp
 *
 *  Created on: 25.01.2017
 *      Author: stefan
 */

#include "Sensor.h"

#define FILTER_SAMPLES 50
#define VARIO_DELAY 250L

Sensor::Sensor() {

	/*********
	 * SENSOR
	 **********/
	sensor = new BME280();

	// Configure sensor
	// Serial.println("init sensor ...");
	sensor->settings.commInterface = I2C_MODE;
	sensor->settings.I2CAddress = 0x76;
	sensor->settings.runMode = 3; // Normal (auto poll)
	sensor->settings.tStandby = 0; // 0.5ms
	//filter can be off or number of FIR coefficients to use:
	//  0, filter off
	//  1, coefficients = 2
	//  2, coefficients = 4
	//  3, coefficients = 8
	//  4, coefficients = 16
	sensor->settings.filter = 16;
	//  0, skipped
	//  1 through 5, oversampling *1, *2, *4, *8, *16 respectively
	sensor->settings.tempOverSample = 1;
	sensor->settings.pressOverSample = 5;
	sensor->settings.humidOverSample = 0;

	// Initialize sensor
	sensor->begin();


	/*********
	 * FILTERS
	 **********/
	buffAlt = new FloatFilterMovingAverage(FILTER_SAMPLES);

	buffTemp = new FloatFilterWeighed();

}

Sensor::~Sensor() {
	delete sensor;
	delete buffAlt;
	delete buffTemp;
}

void Sensor::tick() {

	// Push new sensor reading into filter
	buffAlt->pushValue(sensor->readFloatAltitudeMeters());
	buffTemp->pushValue(sensor->readTempC());

	float currTime = micros();
	float currAlt = buffAlt->getFilteredValue();
	float timeSinceLastVario = currTime - timeOfLastVario;

	// Calculate vario if VARIO_DELAY ms have passed
	if (timeSinceLastVario > VARIO_DELAY * 1000L)
	{

		// Calculate vario
		currVario = ((currAlt - altitudeOfLastVario) / timeSinceLastVario) * 1000000;

		// Save last altitude value for vario
		altitudeOfLastVario = currAlt;

		// Store current time
		timeOfLastVario = currTime;
	}



}

float Sensor::getAltitude() {
	return buffAlt->getFilteredValue();
}

void Sensor::setAltitudeReference() {
	altitudeRef = buffAlt->getFilteredValue();
}

float Sensor::getVario() {
	return currVario;
}

float Sensor::getRelativeAltitude() {
	return getAltitude() - altitudeRef;
}

float Sensor::getTemp() {
	return buffTemp->getFilteredValue();
}
