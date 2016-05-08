ramsondon i2c library for arduino.

Notes:

	this library has only been tested with an arduino due and a drotek 10DOF breakout board (MPU9250 and MS5611).
	for testing purposes the breakout board has been connected directly to the 3.3v output pin of the arduino due.

	10DOF ----> Arduino
	SDA   ----> SDA (20)
	SCL   ----> SCL (21)
	VDD   ----> 3.3v
	GND   ----> GND

	



```c

#include "i2c.h"

#define MPU9250_DEFAULT_ADDRESS         0x69 
#define MPU9250_WHOAMI                  0x75

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  I2C* i2c = new I2C(MPU9250_DEFAULT_ADDRESS);
  byte c = i2c->read(MPU9250_WHOAMI);
  Serial.print("MPU9250 "); 
  Serial.print("I AM "); 
  Serial.print(c, HEX); 
  Serial.print(" I should be "); 
  Serial.println(0x71, HEX);
}

void loop() {}
```	
	