// i2c.cpp
#include "i2c.h"
#include <Wire.h>

I2C::I2C(uint8_t slave_address)
{
    mSlave = slave_address;
}

uint8_t I2C::read(uint8_t address)
{
    uint8_t data;                           // 'data' will store the register data   
    Wire.beginTransmission(mSlave);         // Initialize the Tx buffer
    Wire.write(address);                    // Put slave register address in Tx buffer
    Wire.endTransmission(false);            // Send the Tx buffer, but send a restart to keep connection alive
    Wire.requestFrom(mSlave, (uint8_t) 1);  // Read one byte from slave register address 
    data = Wire.read();                     // Fill Rx buffer with result
    return data;                            // Return exactly one byte
}

void I2C::read(uint8_t address, uint8_t count, uint8_t * dest) 
{
    Wire.beginTransmission(mSlave);     // Initialize the Tx buffer
    Wire.write(address);                // Put slave register address in Tx buffer
    Wire.endTransmission(false);        // Send the Tx buffer, but send a restart to keep connection alive
    uint8_t i = 0;
    Wire.requestFrom(mSlave, count);    // Read bytes from slave register address 
    while (Wire.available()) {
        dest[i++] = Wire.read();        // Put read results in the Rx buffer
    }
}

void I2C::write(uint8_t address, uint8_t data)
{
    Wire.beginTransmission(mSlave); // Initialize the Tx buffer
    Wire.write(address);            // Put slave register address in Tx buffer
    Wire.write(data);               // Put data in Tx buffer
    Wire.endTransmission();         // Send the Tx buffer
}
