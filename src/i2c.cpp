// i2c.cpp
#include "i2c.h"
#include <Wire.h>

bool I2C::sWireInit = false;

I2C::I2C(uint8_t slave_address)
{
    mSlaveAddress = slave_address;
    I2C::init();
}

void I2C::init(void)
{
    if (false == sWireInit) {
        Wire.begin();
        sWireInit = true;
    }
}

void I2C::use(uint8_t slave_address) 
{
    mSlaveAddress = slave_address;
}

uint8_t I2C::read(uint8_t address)
{
    uint8_t data;                                   // 'data' will store the register data   
    Wire.beginTransmission(mSlaveAddress);          // Initialize the Tx buffer
    Wire.write(address);                            // Put slave register address in Tx buffer
    Wire.endTransmission(false);                    // Send the Tx buffer, but send a restart to keep connection alive
    Wire.requestFrom(mSlaveAddress, (uint8_t) 1);   // Read one byte from slave register address 
    data = Wire.read();                             // Fill Rx buffer with result
    return data;                                    // Return exactly one byte
}

void I2C::read(uint8_t address, uint8_t count, uint8_t * buf) 
{
    Wire.beginTransmission(mSlaveAddress);  // Initialize the Tx buffer
    Wire.write(address);                    // Put slave register address in Tx buffer
    Wire.endTransmission(false);            // Send the Tx buffer, but send a restart to keep connection alive
    uint8_t i = 0;
    Wire.requestFrom(mSlaveAddress, count); // Read bytes from slave register address 
    while (Wire.available()) {
        buf[i++] = Wire.read();            // Put read results in the Rx buffer
    }
}

void I2C::write(uint8_t address, uint8_t data)
{
    Wire.beginTransmission(mSlaveAddress);  // Initialize the Tx buffer
    Wire.write(address);                    // Put slave register address in Tx buffer
    Wire.write(data);                       // Put data in Tx buffer
    Wire.endTransmission();                 // Send the Tx buffer
}

int I2C::scan(i2c_cb_ptr ptr_success, i2c_cb_ptr ptr_error)
{
    byte error, address;
    int nrOfDevices; 
    nrOfDevices = 0;
    
    for(address = 1; address < 127; address++) {
        
        // We use the return value of Wire.endTransmission to see if a device
        // did acknowledge at a specific address.
        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0) {
            ptr_success(address);
            nrOfDevices++;
        } else if (error == 4) {
            ptr_error(address);
        }    
    }
 
    return nrOfDevices;
}
