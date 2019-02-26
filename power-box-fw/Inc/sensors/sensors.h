#ifndef __sensors_H
#define __sensors_H

#include "stm32f0xx_hal.h"

// Constants for calculating object temperature
#define TMP006_B0 -0.0000294
#define TMP006_B1 -0.00000057
#define TMP006_B2 0.00000000463
#define TMP006_C2 13.4
#define TMP006_TREF 298.15
#define TMP006_A2 -0.00001678
#define TMP006_A1 0.00175
#define TMP006_S0 6.5  // * 10^-14
 
// Configuration Settings
#define TMP006_CFG_RESET    0x80
#define TMP006_CFG_MODEON   0x70
#define TMP006_CFG_1SAMPLE  0x00
#define TMP006_CFG_2SAMPLE  0x02
#define TMP006_CFG_4SAMPLE  0x04
#define TMP006_CFG_8SAMPLE  0x06
#define TMP006_CFG_16SAMPLE 0x08
#define TMP006_CFG_DRDYEN   0x01

#define TMP006_CFG_DRDY     0x80
 
// Registers to read thermopile voltage and sensor temperature
#define TMP006_VOBJ  0x00
#define TMP006_TAMB 0x01
#define TMP006_CONFIG 0x02
 

void sensor_main(void); // Process sensors code in main() loop

#endif /* __command_processor_H */