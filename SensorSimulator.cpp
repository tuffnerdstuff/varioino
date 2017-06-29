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
#define VARIO_MIN 1.3
#define VARIO_MAX 20
#define VARIO_INC 0.6
#define TEMP_MIN 21.5
#define DIR_UP 1
#define DIR_DOWN -1

SensorSimulator::SensorSimulator() {
	this->currAlt = ALT_MIN;
	this->currTemp = TEMP_MIN;
	this->currVario = VARIO_MIN;
	this->direction = DIR_UP;
	this->firstTickDone = false;
	this->lastTickTime = 0;
}

SensorSimulator::~SensorSimulator() {
	// TODO Auto-generated destructor stub
}

void SensorSimulator::tick() {

	unsigned long now = millis();

	if (!this->firstTickDone)
	{

		this->firstTickDone = true;
	}
	else
	{
		float altDelta = this->direction * (this->currVario / 1000.0) * (now - this->lastTickTime);
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
			this->currTemp = TEMP_MIN - (0.006 * this->currAlt);
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
	return this->currVario;
}

unsigned long SensorSimulator::getVarioSampleTime() {
	return VARIO_SAMPLE_TIME;
}

float SensorSimulator::getTemp() {
	return this->currTemp;
}
