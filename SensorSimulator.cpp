/*
 * SensorSimulator.cpp
 *
 *  Created on: 29.06.2017
 *      Author: stefan
 */

#include "SensorSimulator.h"
#include "Arduino.h"

#define VARIO_SAMPLE_TIME 250L
#define ALT_MIN 0
#define ALT_MAX 100
#define VARIO_UPDATE_DELAY 5000
#define TEMP_MSL 21.5
#define DIR_UP 1
#define DIR_DOWN -1

SensorSimulator::SensorSimulator() {
	this->currAlt = ALT_MIN;
	this->currTemp = TEMP_MSL;
	this->direction = DIR_UP;
	this->firstTickDone = false;
	this->lastTickTime = 0;
	this->lastVarioTime = 0;
	this->varioIndex = 1;
}

SensorSimulator::~SensorSimulator() {
	// TODO Auto-generated destructor stub
}

void SensorSimulator::tick() {

	unsigned long now = millis();
	unsigned long timeDelta = now - this->lastTickTime;

	if (!this->firstTickDone)
	{

		this->firstTickDone = true;
		this->lastVarioTime = now;
	}
	else
	{
		// Change vario
		if(now - this->lastVarioTime > VARIO_UPDATE_DELAY)
		{
			this->varioIndex = (this->varioIndex + 1) % this->varioValuesCount;
			this->lastVarioTime = now;
		}


		// Change altitude
		float altDelta = this->direction * (this->getVario() / 1000.0) * timeDelta;
		float newAlt = this->currAlt + altDelta;

		if (newAlt > ALT_MAX)
		{
			this->direction = DIR_DOWN;
		}
		else if (newAlt < ALT_MIN)
		{
			this->direction = DIR_UP;
		}
		else
		{
			this->currAlt = newAlt;
			this->currTemp = TEMP_MSL - (0.006 * this->currAlt);
		}
	}

	this->lastTickTime = now;

}

float SensorSimulator::getAltitude() {
	return this->currAlt;
}

float SensorSimulator::getRelativeAltitude() {
	// FIXME: relative!
	return this->currAlt;
}

void SensorSimulator::setAltitudeReference() {
	//TODO: logic
}

float SensorSimulator::getVario() {
	return this->varioValues[varioIndex];
}

unsigned long SensorSimulator::getVarioSampleTime() {
	return VARIO_SAMPLE_TIME;
}

float SensorSimulator::getTemp() {
	return this->currTemp;
}
