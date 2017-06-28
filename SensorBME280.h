/*
 * SensorBME280.h
 *  Created on: 28.06.2017
 *      Author: stefan
 *
 *      Some abbreviations which are nice to know:
 *      - AGL = above ground level
 *      - MSL = mean sea level
 *      - QNH = the pressure at sea level -> altimeter shows height above sea level at runway
 *      - QFE = the pressure at runway -> altimeter shows 0 at runway
 */

#ifndef SENSORBME280_H_
#define SENSORBME280_H_

#include "Sensor.h"
#include "SparkFunBME280.h"
#include "FloatFilterWeighed.h"
#include "Arduino.h"

class SensorBME280 : public Sensor {
public:
	SensorBME280();
	~SensorBME280();
	void tick();
	float getAltitude();
	float getRelativeAltitude();
	void setAltitudeReference(); // "Reset" relative altitude to 0
	float getVario(); // in m/s
	unsigned long getVarioSampleTime();
	float getTemp();
private:
	BME280 *sensor;
	FloatFilterWeighed *buffAlt;
	FloatFilterWeighed *buffTemp;
	float altitudeRef = 0;
	float currVario = 0;
	unsigned long timeOfLastVario = 0;
	float altitudeOfLastVario = 0;

};

#endif /* SENSOR_H_ */
