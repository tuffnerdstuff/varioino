/*
 * Sensor.h
 *
 *  Created on: 25.01.2017
 *      Author: stefan
 *
 *      Some abbreviations which are nice to know:
 *      - AGL = above ground level
 *      - MSL = mean sea level
 *      - QNH = the pressure at sea level -> altimeter shows height above sea level at runway
 *      - QFE = the pressure at runway -> altimeter shows 0 at runway
 */

#ifndef SENSOR_H_
#define SENSOR_H_

#include "SparkFunBME280.h"
#include "FloatFilterMovingAverage.h"
#include "FloatFilterWeighed.h"
#include "Arduino.h"

class Sensor {
public:
	Sensor();
	virtual ~Sensor();
	virtual void tick();
	virtual float getAltitude();
	virtual float getRelativeAltitude();
	virtual void setAltitudeReference(); // "Reset" relative altitude to 0
	virtual float getVario(); // in m/s
	virtual float getTemp();
private:
	BME280 *sensor;
	FloatFilterMovingAverage *buffAlt;
	FloatFilterWeighed *buffTemp;
	float altitudeRef = 0;
	float currVario = 0;
	float timeOfLastVario = 0;
	float altitudeOfLastVario = 0;

};

#endif /* SENSOR_H_ */
