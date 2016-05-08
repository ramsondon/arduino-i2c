

// I2C.h
#ifndef I2C_H
#define I2C_H

#include <stdint.h>

typedef int(*i2c_cb_ptr)(int);

/*
 * class I2C
 * 
 * communication middleware for i2c with arduino.
 */
class I2C
{
    private:
        /*
         * slave address on the arduino board
         */
        uint8_t mSlaveAddress;
        
        /*
         * static Wire.begin() for using multiple i2c objects
         */
        static bool sWireInit;
        
        /*
         * initialization of the arduino Wire api
         */
        static void init(void);
        
    public:
        
        /*
         * constructor 
         */
        I2C(uint8_t slave_address = 0);
        
        /*
         * switches the device
         * 
         * @param slave_address 
         */
        void use(uint8_t slave_address);
        
        /*
         * reads a single byte at address 'address' of device mSlave
         */
        uint8_t read(uint8_t address);
        
        /*
         * reads #'count' bytes at address 'address' of device mSlave
         */
        void read(uint8_t address, uint8_t count, uint8_t * buf);
        
        /*
         * write data to address of mSlave device
         */
        void write(uint8_t address, uint8_t data);
        
        /*
         * scans the i2c bus
         * @return number of devices found
         */
        int scan(i2c_cb_ptr ptr_success, i2c_cb_ptr ptr_error);
};

#endif
