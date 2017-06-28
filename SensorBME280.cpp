/*
 * Sensor.cpp
 *
 *  Created on: 25.01.2017
 *      Author: stefan
 */

#include "SensorBME280.h"

#define FILTER_SAMPLES 50
#define VARIO_SAMPLE_TIME 250L

SensorBME280::SensorBME280() {

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
	buffAlt = new FloatFilterWeighed(0.1);

	buffTemp = new FloatFilterWeighed(0.025);

}

SensorBME280::~SensorBME280() {
	delete sensor;
	delete buffAlt;
	delete buffTemp;
}

unsigned long SensorBME280::getVarioSampleTime()
{
	return VARIO_SAMPLE_TIME;
}

void SensorBME280::tick() {


	// Push new sensor reading into filter
	buffAlt->pushValue(sensor->readFloatAltitudeMeters());
	buffTemp->pushValue(sensor->readTempC());

	unsigned long currTime = micros();
	float currAlt = buffAlt->getFilteredValue();
	unsigned long timeSinceLastVario = currTime - timeOfLastVario;

	// Calculate vario if VARIO_DELAY ms have passed
	if (timeSinceLastVario > VARIO_SAMPLE_TIME * 1000L)
	{

		// Calculate vario
		currVario = ((currAlt - altitudeOfLastVario) / timeSinceLastVario) * 1000000;

		// Save last altitude value for vario
		altitudeOfLastVario = currAlt;

		// Store current time
		timeOfLastVario = currTime;
	}



}

float SensorBME280::getAltitude() {
	return buffAlt->getFilteredValue();
}

void SensorBME280::setAltitudeReference() {
	altitudeRef = buffAlt->getFilteredValue();
}

float SensorBME280::getVario() {
	return currVario;
}

float SensorBME280::getRelativeAltitude() {
	return getAltitude() - altitudeRef;
}

float SensorBME280::getTemp() {
	return buffTemp->getFilteredValue();
}
