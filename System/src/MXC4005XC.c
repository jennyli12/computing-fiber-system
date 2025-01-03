#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "i2c.h"
#include "MXC4005XC.h"

mxc_i2c_req_t reqMaster;
uint8_t txdata[2];
uint8_t rxdata[2];
float sensitivity;

int MXC4005XC_init(mxc_i2c_regs_t *i2c, uint8_t fsr) {
    txdata[0] = MXC4005XC_CONTROL;

    if (fsr == 4) {
        txdata[1] = MXC4005XC_FSR_4G;
        sensitivity = 512;
    } else if (fsr == 8) {
        txdata[1] = MXC4005XC_FSR_8G;
        sensitivity = 256;
    } else {
        txdata[1] = MXC4005XC_FSR_2G;
        sensitivity = 1024;
    }

    reqMaster.i2c = i2c;
    reqMaster.addr = MXC4005XC_ADDRESS;
    reqMaster.tx_buf = txdata;
    reqMaster.tx_len = 2;
    reqMaster.rx_buf = rxdata;
    reqMaster.rx_len = 0;
    reqMaster.restart = 0;
    reqMaster.callback = NULL;

    return MXC_I2C_MasterTransaction(&reqMaster);
}

float MXC4005XC_readX_Axis(void) {
    txdata[0] = MXC4005XC_XOUT_UPPER;
    reqMaster.tx_len = 1;
    reqMaster.rx_len = 1;
    MXC_I2C_MasterTransaction(&reqMaster);

    int16_t xaxis = rxdata[0];
    xaxis <<= 8;

    txdata[0] = MXC4005XC_XOUT_LOWER;
    MXC_I2C_MasterTransaction(&reqMaster);

    xaxis |= rxdata[0];
    xaxis >>= 4;

    return xaxis / sensitivity;
}

float MXC4005XC_readY_Axis(void) {
    txdata[0] = MXC4005XC_YOUT_UPPER;
    reqMaster.tx_len = 1;
    reqMaster.rx_len = 1;
    MXC_I2C_MasterTransaction(&reqMaster);

    int16_t yaxis = rxdata[0];
    yaxis <<= 8;

    txdata[0] = MXC4005XC_YOUT_LOWER;
    MXC_I2C_MasterTransaction(&reqMaster);

    yaxis |= rxdata[0];
    yaxis >>= 4;

    return yaxis / sensitivity;
}

float MXC4005XC_readZ_Axis(void) {
    txdata[0] = MXC4005XC_ZOUT_UPPER;
    reqMaster.tx_len = 1;
    reqMaster.rx_len = 1;
    MXC_I2C_MasterTransaction(&reqMaster);

    int16_t zaxis = rxdata[0];
    zaxis <<= 8;

    txdata[0] = MXC4005XC_ZOUT_LOWER;
    MXC_I2C_MasterTransaction(&reqMaster);

    zaxis |= rxdata[0];
    zaxis >>= 4;

    return zaxis / sensitivity;
}
