// Arduino
#include "Arduino.h"
// MAIN
#include <stdint.h>
//#include "FloatFilterMovingAverage.h"
#include "FloatFilterWeighed.h"
// I2C
#include "Wire.h"
// OLED
#include "SparkFunBME280.h"
// Sensor
#include "Sensor.h"
#include "SensorBME280.h"
#include "SensorSimulator.h"

#include "DisplayOLED.h"
// SCREEN MANAGER
#include "ScreenManager.h"
#include "SpeakerPWM.h"
// Free Memory
#include "MemoryFree.h"

DisplayOLED *display;
SpeakerPWM *buzzer;
Buttons *buttons;
Sensor *sensor;
ScreenManager *scrMan;

void setup() {

	//sensor = new SensorSimulator();
	sensor = new SensorBME280();
	buttons = new Buttons();
	display = new DisplayOLED();
	buzzer = new SpeakerPWM();
	scrMan = new ScreenManager(display,buzzer,buttons,sensor);


	display->init();
	buzzer->init();
	scrMan->init();

}

void loop() {

	sensor->tick();
	buttons->tick();
	buzzer->tick();
	scrMan->tick();



}








