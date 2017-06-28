/*
 * Sensor.h
 *
 *  Created on: 25.01.2017
 *      Author: stefan

 */

#ifndef SENSOR_H_
#define SENSOR_H_

class Sensor {
public:
	virtual void tick()=0;
	virtual float getAltitude()=0;
	virtual float getRelativeAltitude()=0;
	virtual void setAltitudeReference()=0; // "Reset" relative altitude to 0
	virtual float getVario()=0; // in m/s
	virtual unsigned long getVarioSampleTime()=0;
	virtual float getTemp()=0;
};

#endif /* SENSOR_H_ */
