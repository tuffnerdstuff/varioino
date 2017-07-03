/*
 * SensorSimulator.h
 *
 *  Created on: 29.06.2017
 *      Author: stefan
 */

#ifndef SENSORSIMULATOR_H_
#define SENSORSIMULATOR_H_

#include "Sensor.h"

class SensorSimulator: public Sensor {
public:
	SensorSimulator();
	virtual ~SensorSimulator();
	void tick();
	float getAltitude();
	float getRelativeAltitude();
	void setAltitudeReference(); // "Reset" relative altitude to 0
	float getVario(); // in m/s
	unsigned long getVarioSampleTime();
	float getTemp();

private:
	float currTemp;
	float currAlt;
	int direction;
	bool firstTickDone;
	unsigned long lastTickTime;
	int varioValuesCount = 12;
	float varioValues[12] = {0,0.1,0.3,0.5,0.9,1.5,2,3,4,8,16,32};
	int varioIndex;
	unsigned long lastVarioTime;
};

#endif /* SENSORSIMULATOR_H_ */
