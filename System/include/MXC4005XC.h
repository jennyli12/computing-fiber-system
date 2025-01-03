#ifndef MXC4005XC_H_
#define MXC4005XC_H_

#include <stdint.h>
#include "i2c.h"

#define MXC4005XC_ADDRESS       0x15

#define MXC4005XC_INT_SRC0      0X00
#define MXC4005XC_INT_CLR0      0X00
#define MXC4005XC_INT_SRC1      0X01
#define MXC4005XC_INT_CLR1      0X01
#define MXC4005XC_STATUS        0X02
#define MXC4005XC_XOUT_UPPER    0X03
#define MXC4005XC_XOUT_LOWER    0X04
#define MXC4005XC_YOUT_UPPER    0X05
#define MXC4005XC_YOUT_LOWER    0X06
#define MXC4005XC_ZOUT_UPPER    0X07
#define MXC4005XC_ZOUT_LOWER    0X08
#define MXC4005XC_TOUT          0X09
#define MXC4005XC_INT_MASK0     0X0A
#define MXC4005XC_INT_MASK1     0X0B
#define MXC4005XC_DETECTION     0X0C
#define MXC4005XC_CONTROL       0X0D
#define MXC4005XC_DEVICE_ID     0X0E
#define MXC4005XC_WHO_AM_I      0X0F

#define MXC4005XC_FSR_2G        (0)
#define MXC4005XC_FSR_4G        (1 << 5)
#define MXC4005XC_FSR_8G        (1 << 6)

/**
 * Initializes the sensor and sets up the full-scale range
 */
int MXC4005XC_init(mxc_i2c_regs_t *i2c, uint8_t fsr);

/**
 * Returns X-axis acceleration (g's)
 */
float MXC4005XC_readX_Axis(void);

/**
 * Returns Y-axis acceleration (g's)
 */
float MXC4005XC_readY_Axis(void);

/**
 * Returns Z-axis acceleration (g's)
 */
float MXC4005XC_readZ_Axis(void);

#endif /* MXC4005XC_H_ */
