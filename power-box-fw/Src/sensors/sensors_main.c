#include "sensors/sensors.h"
#include "i2c.h"
#include "printf.h"

void sensor_main(void)
{
  uint8_t data_buffer[10];
  double Vobj,Tdie;
  int ret1, ret2;

  // HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
  // HAL_StatusTypeDef HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);

  data_buffer[0] = 0x02;
  data_buffer[1] = (TMP006_CFG_MODEON) | (TMP006_CFG_DRDYEN) | (TMP006_CFG_16SAMPLE);
  data_buffer[2] = 0x00;
  ret1 = HAL_I2C_Master_Transmit(&hi2c1, 0x40<<1, data_buffer, 3, 100);

  // data_buffer[0] = 0x02;
  // ret1 = HAL_I2C_Master_Transmit(&hi2c1, 0x40<<1, data_buffer, 1, 100);
  // ret2 = HAL_I2C_Master_Receive(&hi2c1, 0x40<<1, data_buffer, 2, 100);

  // printf("Ret1: %d\n", ret1);
  // printf("Ret2: %d\n", ret2);
  //printf("Data Buffer: %08b %08b\n", data_buffer[0], data_buffer[1]);

  while (1)
  {
    do{
      HAL_Delay(1);
      data_buffer[0] = 0x02;
      ret1 = HAL_I2C_Master_Transmit(&hi2c1, 0x40<<1, data_buffer, 1, 100);
      ret2 = HAL_I2C_Master_Receive(&hi2c1, 0x40<<1, data_buffer, 2, 100);
      // printf(".");
    } while ((data_buffer[1] & TMP006_CFG_DRDY) == 0);
    // printf("\n");

    data_buffer[0] = 00;
    ret1 = HAL_I2C_Master_Transmit(&hi2c1, 0x40<<1, data_buffer, 1, 100);
    ret2 = HAL_I2C_Master_Receive(&hi2c1, 0x40<<1, data_buffer, 2, 100);
    Vobj = (double)((int16_t)((data_buffer[0] << 8) + data_buffer[1]));
    data_buffer[0] = 01;
    ret1 = HAL_I2C_Master_Transmit(&hi2c1, 0x40<<1, data_buffer, 1, 100);
    ret2 = HAL_I2C_Master_Receive(&hi2c1, 0x40<<1, data_buffer, 2, 100);
    Tdie = (double)((int16_t)((data_buffer[0] << 8) + data_buffer[1]));

  Vobj *= 156.25;  // 156.25 nV per LSB
  Vobj /= 1000000000; // nV -> V
  Tdie *= 0.03125; // convert to celsius
  Tdie += 273.15; // convert to kelvin
 
  // Equations for calculating temperature found in section 5.1 in the user guide
  double tdie_tref = Tdie - TMP006_TREF;
  double S = (1 + TMP006_A1*tdie_tref + 
      TMP006_A2*tdie_tref*tdie_tref);
  S *= TMP006_S0;
  S /= 10000000;
  S /= 10000000;
 
  double Vos = TMP006_B0 + TMP006_B1*tdie_tref + 
    TMP006_B2*tdie_tref*tdie_tref;
 
  double fVobj = (Vobj - Vos) + TMP006_C2*(Vobj-Vos)*(Vobj-Vos);
 
  double Tobj = sqrt(sqrt(Tdie * Tdie * Tdie * Tdie + fVobj/S));
 
  Tobj -= 273.15; // Kelvin -> *C
  printf("%f %f\n", Tobj, Tobj*2-128);
  break;
  }
}