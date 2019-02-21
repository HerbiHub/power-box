
#include "command_processor.h"

#include "printf.h"
#include <stdlib.h>
#include <string.h>
#include "crc.h"

CMD_PROC_StatusTypeDef CMD_PROC_Process_Main(char* buffer)
{
  uint8_t version;
  char target[20];
  char transmitter[20];
  char command[20];
  uint32_t cmd_crc;

  char *tok;
  char *pch;
  uint32_t count=0;
  uint32_t index;

  // Locate the last ',' of the command.
  pch = strrchr((char *)buffer, ',');
  count = (pch - buffer) + 1;
  if (count < 200)
  {
    // So as it turns out, CRC on the STM32 is stupid. Calculate it byte by byte like a sane
    //  person and use that value. 
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

    // temp = HAL_CRC_Calculate(&hcrc, (uint32_t *) buffer, count);
    printf("Crc: %X\n",cmd_crc);
  }



  // Reset count 
  // count = 0;

  // printf("Parse: '%s'\n", buffer);
  // tok = strtok((char *)buffer, ",");
  // do
  // {
  //   printf("%d:%s\n", count++, tok );
  // } while ((tok = strtok(NULL, ",")) != NULL);
  // printf("\n");

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

  return CMD_PROC_OK;
}


CMD_PROC_StatusTypeDef CMD_PROC_CMD_Baud(char version, char* verb)
{
  return CMD_PROC_OK;
}