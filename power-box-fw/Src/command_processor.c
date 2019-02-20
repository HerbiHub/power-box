
#include "command_processor.h"

#include "printf.h"
#include <stdlib.h>
#include <string.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpointer-sign"
CMD_PROC_StatusTypeDef CMD_PROC_Process_Main(uint8_t* buffer)
{
  uint8_t version;
  uint8_t target[4];
  uint8_t transmitter[4];
  uint8_t command[20];

  uint8_t *tok;
  int count=0;

  // TODO: We must calculate our CRC before touching the string, as we will
  //  be adding \0 characters to it. 

  printf("Parse: '%s'\n", buffer);
  tok = strtok((char *)buffer, ",");
  do
  {
    printf("%d:%s\n", count++, tok );
  } while ((tok = strtok(NULL, ",")) != NULL);
  printf("\n");

  return CMD_PROC_OK;
}
#pragma GCC diagnostic pop