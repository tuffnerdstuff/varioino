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
	float currVario;
	float currTemp;
	float currAlt;
	int direction;
	bool firstTickDone;
	unsigned long lastTickTime;
};

#endif /* SENSORSIMULATOR_H_ */
