
  // uint8_t data_buffer[10];
  // double Vobj,Tdie;
  // int ret1, ret2;

  // // HAL_StatusTypeDef HAL_I2C_Master_Transmit(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
  // // HAL_StatusTypeDef HAL_I2C_Master_Receive(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint8_t *pData, uint16_t Size, uint32_t Timeout);
  // data_buffer[0] = 0x02;
  // ret1 = HAL_I2C_Master_Transmit(&hi2c1, 0x40<<1, data_buffer, 1, 100);
  // ret2 = HAL_I2C_Master_Receive(&hi2c1, 0x40<<1, data_buffer, 2, 100);

  // printf("Ret1: %d\n", ret1);
  // printf("Ret2: %d\n", ret2);
  // printf("Data Buffer: %08b %08b\n\n", data_buffer[0], data_buffer[1]);
  // while (1)
  // {

  //   data_buffer[0] = 00;
  //   ret1 = HAL_I2C_Master_Transmit(&hi2c1, 0x40<<1, data_buffer, 1, 100);
  //   ret2 = HAL_I2C_Master_Receive(&hi2c1, 0x40<<1, data_buffer, 2, 100);
  //   Vobj = (double)((int16_t)((data_buffer[1] << 8) + data_buffer[0]));
  //   data_buffer[0] = 01;
  //   ret1 = HAL_I2C_Master_Transmit(&hi2c1, 0x40<<1, data_buffer, 1, 100);
  //   ret2 = HAL_I2C_Master_Receive(&hi2c1, 0x40<<1, data_buffer, 2, 100);
  //   Tdie = (double)((int16_t)((data_buffer[1] << 8) + data_buffer[0]));

  //  // double Tdie = readRawDieTemperature();
  //  // double Vobj = readRawVoltage();
  //  Vobj *= 156.25;  // 156.25 nV per LSB
  //  Vobj /= 1000; // nV -> uV
  //  Vobj /= 1000; // uV -> mV
  //  Vobj /= 1000; // mV -> V
  //  Tdie *= 0.03125; // convert to celsius
  //  Tdie += 273.15; // convert to kelvin

  
  //  double tdie_tref = Tdie - TMP006_TREF;
  //  double S = (1 + TMP006_A1*tdie_tref + 
  //                    TMP006_A2*tdie_tref*tdie_tref);
  //  S *= TMP006_S0;
  //  S /= 10000000;
  //  S /= 10000000;
   
  //  double Vos = TMP006_B0 + TMP006_B1*tdie_tref + 
  //               TMP006_B2*tdie_tref*tdie_tref;
   
  //  double fVobj = (Vobj - Vos) + TMP006_C2*(Vobj-Vos)*(Vobj-Vos);
   
  //  double Tobj = sqrt(sqrt(Tdie * Tdie * Tdie * Tdie + fVobj/S));
   
  //  Tobj -= 273.15; // Kelvin -> *C
  //  printf("%lf\n", Tobj);

  //   HAL_Delay(10000);
  // }