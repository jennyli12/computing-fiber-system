/**
 * @file    main.c
 * @brief   
 * @details 
 */

/***** Includes *****/
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "i2c.h"
#include "mxc_device.h"
#include "mxc_delay.h"
#include "led.h"

#include "MXC4005XC.h"

/***** Definitions *****/
#define I2C_MASTER MXC_I2C1
#define I2C_FREQ 100000

/***** Globals *****/

/***** Functions *****/

// *****************************************************************************
int main(void)
{
	int error = E_NO_ERROR;
    float xaxis, yaxis, zaxis;

    error = MXC_I2C_Init(I2C_MASTER, 1, 0);
    if (error != E_NO_ERROR) {
        printf("I2C master configure failed with error %i\n", error);
        return error;
    }

    MXC_I2C_SetFrequency(I2C_MASTER, I2C_FREQ);

	error = MXC4005XC_init(I2C_MASTER, 4);
	if (error != E_NO_ERROR) {
        printf("MXC4005XC configure failed with error %i\n", error);
        return error;
    }

	while (1) {
		xaxis = MXC4005XC_readX_Axis();
		yaxis = MXC4005XC_readY_Axis();
		zaxis = MXC4005XC_readZ_Axis();

		printf("X_axis:%f ", (double) xaxis);
		printf("Y_axis:%f ", (double) yaxis);
		printf("Z_axis:%f \n", (double) zaxis);

		MXC_Delay(MXC_DELAY_MSEC(20));
		LED_Toggle(0);
	}
}
