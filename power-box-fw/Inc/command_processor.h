
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __command_processor_H
#define __command_processor_H

#include "main.h"

typedef enum 
{
  CMD_PROC_OK       = 0x00U,
  CMD_PROC_ERROR    = 0x01U
} CMD_PROC_StatusTypeDef;

typedef struct 
{
	unsigned int version;
  
  char target[20];

  char transmitter[20];

  char command[20];

  char verb[10];        // Cap to 5 characters (size 6 for null)?

  unsigned int option1;

  unsigned int option2;

  unsigned int cmd_crc;

} CMD_PROC_CommandStruct;

#define CMD_PROC_COMMAND_RTC "RTC"

#define CMD_PROC_SUBCOMMAND_GET "GET"

CMD_PROC_StatusTypeDef CMD_PROC_Process_Main(char* buffer);

CMD_PROC_StatusTypeDef CMD_PROC_CMD_Baud(CMD_PROC_CommandStruct* recp_command, char* response);
CMD_PROC_StatusTypeDef CMD_PROC_CMD_RTC(CMD_PROC_CommandStruct* recp_command, char* response);
CMD_PROC_StatusTypeDef CMD_PROC_CMD_Status(CMD_PROC_CommandStruct* recp_command, char* response);
uint32_t CalcCRC32(char* buffer, int length);

#endif /* __command_processor_H */