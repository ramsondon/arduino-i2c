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
  Serial.begin(9600);
  I2C* i2c = new I2C(MPU9250_DEFAULT_ADDRESS);

  // to test you can scan I2C bus - and use callback functions here
  i2c->scan((i2c_cb_ptr)scan_success, (i2c_cb_ptr)scan_error);

  // another test -> read who am i regsiter of MPU9250 on the breakout board
  byte c = i2c->read(MPU9250_WHOAMI);
  
  Serial.print("MPU9250 "); 
  Serial.print("I AM "); 
  Serial.print(c, HEX); 
  Serial.print(" I should be "); 
  Serial.println(0x71, HEX);
  
}

void loop() {}

void scan_success(int address) {
  Serial.print("I2C device found at address 0x");
  if (address<16)
    Serial.print("0");
  Serial.print(address,HEX);
  Serial.println("!");
}

void scan_error(int address) {
  Serial.print("Unknow error at address 0x");
  if (address<16)
    Serial.print("0");
  Serial.println(address,HEX);
}

```	

As output you should receive the following:

	I2C device found at address 0x69!
	MPU9250 I AM 71 I should be 71

	
