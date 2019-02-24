
#include "command_processor.h"

#include "crc.h"
#include "printf.h"
#include "rtc.h"
#include "stm32f0xx_it.h"
#include <stdlib.h> // strtol 
#include <string.h>

CMD_PROC_StatusTypeDef CMD_PROC_Process_Main(char* buffer)
{
  CMD_PROC_CommandStruct recp_command;

  char *tok;
  char *pch;
  char response[150];
  int count;

  // Locate the last ',' of the command.
  pch = strrchr((char *)buffer, ',');
  count = (pch - buffer) + 1;
  if (count < 200)
  {
    // So as it turns out, CRC on the STM32 is stupid. Calculate it byte by byte like a sane
    //  person and use that value. 
    recp_command.cmd_crc = CalcCRC32(buffer, count);
  }

  // Get version
  tok = strtok((char *)buffer, ",");
  if (tok == NULL) return CMD_PROC_ERROR;
  recp_command.version = strtol (tok, NULL, 0);

  // Get Target
  if ((tok = strtok(NULL, ",")) == NULL) return CMD_PROC_ERROR;
  strcpy ((char *)recp_command.target, tok);

  // Get Source
  if ((tok = strtok(NULL, ",")) == NULL) return CMD_PROC_ERROR;
  strcpy ((char *)recp_command.transmitter, tok);

  // Get Command
  if ((tok = strtok(NULL, ",")) == NULL) return CMD_PROC_ERROR;
  strcpy ((char *)recp_command.command, tok);

  // Get Verb
  if ((tok = strtok(NULL, ",")) == NULL) return CMD_PROC_ERROR;
  strcpy ((char *)recp_command.verb, tok);

  // TODO: Not sure of the formatting of these else-ifs. Maybe make them prettier?
  if (strcmp(recp_command.command,"BAUD") == 0)
  {
    if (CMD_PROC_CMD_Baud(&recp_command, response) == CMD_PROC_ERROR)
      printf("ERROR\n");
  } else if (strcmp(recp_command.command,"RTC") == 0) 
  {
    if (CMD_PROC_CMD_RTC(&recp_command, response) == CMD_PROC_ERROR)
      printf("ERROR\n");
  } else if (strcmp(recp_command.command,"STATUS") == 0)
  {
    if (CMD_PROC_CMD_Status(&recp_command, response) == CMD_PROC_ERROR)
      printf("ERROR\n");
  } else {
    printf("Unknown command %s\n", recp_command.command);
    return CMD_PROC_ERROR;
  }
  printf("%lld\n",GetMyTick()/1000);

  return CMD_PROC_OK;
}

CMD_PROC_StatusTypeDef CMD_PROC_CMD_Baud(CMD_PROC_CommandStruct* recp_command, char* response)
{
  char *tok;

  printf("Process BAUD Command\n");

  while ((tok = strtok(NULL, ",")) != NULL)
  {
    printf("%s\n",tok);
  }
  return CMD_PROC_OK;
}

CMD_PROC_StatusTypeDef CMD_PROC_CMD_RTC(CMD_PROC_CommandStruct* recp_command, char* response)
{
  char *tok;
  RTC_TimeTypeDef time;
  RTC_DateTypeDef date;
  printf("Process RTC Command\n");

  if (strcmp(recp_command->verb,"GET") == 0)
  {
    // TODO: Respond with our own current RTC
    HAL_RTC_GetDate(&hrtc, &date, RTC_FORMAT_BIN);
    HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);

    printf("20%02d-%02d-%02d %02d:%02d:%02d\n", date.Year, date.Month, date.Date, time.Hours, time.Minutes, time.Seconds);

  } else if (strcmp(recp_command->verb,"SET") == 0)
  {
    // TODO: Parse RTC values
    if ((tok = strtok(NULL, ",")) == NULL) return CMD_PROC_ERROR;
    date.Year = strtol (tok, NULL, 0);

    if ((tok = strtok(NULL, ",")) == NULL) return CMD_PROC_ERROR;
    date.Month = strtol (tok, NULL, 0);

    if ((tok = strtok(NULL, ",")) == NULL) return CMD_PROC_ERROR;
    date.Date = strtol (tok, NULL, 0);

    if ((tok = strtok(NULL, ",")) == NULL) return CMD_PROC_ERROR;
    time.Hours = strtol (tok, NULL, 0);

    if ((tok = strtok(NULL, ",")) == NULL) return CMD_PROC_ERROR;
    time.Minutes = strtol (tok, NULL, 0);

    if ((tok = strtok(NULL, ",")) == NULL) return CMD_PROC_ERROR;
    time.Seconds = strtol (tok, NULL, 0);

    HAL_RTC_SetDate(&hrtc, &date, RTC_FORMAT_BIN);
    HAL_RTC_SetTime(&hrtc, &time, RTC_FORMAT_BIN);

  } else if (strcmp(recp_command->verb,"CLEAR") == 0)
  {

  }
  
  return CMD_PROC_OK;
}

CMD_PROC_StatusTypeDef CMD_PROC_CMD_Status(CMD_PROC_CommandStruct* recp_command, char* response)
{
  char *tok;
  printf("Process STATUS Command\n");

  while ((tok = strtok(NULL, ",")) != NULL)
  {
    printf("%s\n",tok);
  }
  return CMD_PROC_OK;
}

uint32_t CalcCRC32(char* buffer, int length)
{
  int index;
  __HAL_LOCK(&hcrc); 
  __HAL_CRC_INITIALCRCVALUE_CONFIG(&hcrc,0xFFFFFFFF); // Set to zero to match python poly config
  hcrc.State = HAL_CRC_STATE_BUSY;
  __HAL_CRC_DR_RESET(&hcrc);
  for(index = 0U; index < length; index++)
  {
    hcrc.Instance->DR = buffer[index];
  }
  hcrc.State = HAL_CRC_STATE_READY; 
  __HAL_UNLOCK(&hcrc);
  return hcrc.Instance->DR;
}
