
#include "command_processor.h"

#include "crc.h"
#include "printf.h"
#include "stm32f0xx_it.h"
#include <stdlib.h>
#include <string.h>

CMD_PROC_StatusTypeDef CMD_PROC_Process_Main(char* buffer)
{
  uint8_t version;
  char target[20];
  char transmitter[20];
  char command[20];
  uint32_t cmd_crc;

  char *tok;
  char *pch;
  int index;
  int count;

  // Locate the last ',' of the command.
  pch = strrchr((char *)buffer, ',');
  count = (pch - buffer) + 1;
  if (count < 200)
  {
    // So as it turns out, CRC on the STM32 is stupid. Calculate it byte by byte like a sane
    //  person and use that value. 

    // temp = HAL_CRC_Calculate(&hcrc, (uint32_t *) buffer, count);
    __HAL_LOCK(&hcrc); 
    __HAL_CRC_INITIALCRCVALUE_CONFIG(&hcrc,0xFFFFFFFF); // Set to zero to match python poly config
    hcrc.State = HAL_CRC_STATE_BUSY;
    __HAL_CRC_DR_RESET(&hcrc);
    for(index = 0U; index < count; index++)
    {
      hcrc.Instance->DR = buffer[index];
    }
    cmd_crc = hcrc.Instance->DR;
    hcrc.State = HAL_CRC_STATE_READY; 
    __HAL_UNLOCK(&hcrc);

    printf("Crc: %X\n",cmd_crc);
  }


  // Get version
  tok = strtok((char *)buffer, ",");
  if (tok == NULL) return CMD_PROC_ERROR;
  version = tok[0];

  // Get Target
  if ((tok = strtok(NULL, ",")) == NULL) return CMD_PROC_ERROR;
  strcpy ((char *)target, tok);

  // Get Source
  if ((tok = strtok(NULL, ",")) == NULL) return CMD_PROC_ERROR;
  strcpy ((char *)transmitter, tok);

  // Get Command
  if ((tok = strtok(NULL, ",")) == NULL) return CMD_PROC_ERROR;
  strcpy ((char *)command, tok);

  // printf("Parsed command:\n");
  // printf("  Version: %c\n",version);
  // printf("  Target: %s\n",target);
  // printf("  Transmitter: %s\n",transmitter);
  // printf("  Command: %s\n",command);

  if (strcmp(command,"STATUS") == 0)
  {
    printf("Found a status command\n");
  } else if (strcmp(command,"BAUD") == 0)
  {
    printf("Found a baud command\n");
  } else {
    printf("Unknown command %s\n", command);
    return CMD_PROC_ERROR;
  }
  printf("%lld\n",GetMyTick()/1000);

  return CMD_PROC_OK;
}


CMD_PROC_StatusTypeDef CMD_PROC_CMD_Baud(char version, char* verb)
{
  char *tok;

  while ((tok = strtok(NULL, ",")) != NULL)
  {
    printf("%s\n",tok);
  }
  return CMD_PROC_OK;
}