

// I2C.h
#ifndef I2C_H
#define I2C_H

#include <stdint.h>


class I2C
{
    private:
        uint8_t mSlave;

    public:
      I2C(uint8_t slave_address);
      uint8_t read(uint8_t address);
      void read(uint8_t address, uint8_t count, uint8_t * dest);
      void write(uint8_t address, uint8_t data);
};

#endif
