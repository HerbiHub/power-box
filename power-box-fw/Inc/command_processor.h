
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __command_processor_H
#define __command_processor_H

#include "main.h"

#define MAX_ADDRESS_STRING_LENGTH 20 + 1 // 20 characters, plus the null
#define MAX_COMMAND_STRING_LENGTH 20 + 1 // 20 characters, plus the null
#define MAX_VERB_STRING_LENGTH 10 + 1 // 20 characters, plus the null

#define CMD_PROC_COMMAND_RTC "RTC"
#define CMD_PROC_SUBCOMMAND_GET "GET"

typedef enum 
{
  CMD_PROC_OK       = 0x00U,
  CMD_PROC_ERROR    = 0x01U
} CMD_PROC_StatusTypeDef;

typedef struct 
{
  unsigned int version;
  
  char target[MAX_ADDRESS_STRING_LENGTH];

  char transmitter[MAX_ADDRESS_STRING_LENGTH];

  char command[MAX_COMMAND_STRING_LENGTH];

  char verb[MAX_VERB_STRING_LENGTH];        // Cap to 5 characters (size 6 for null)?

  unsigned int option1;
  unsigned int option2;
  unsigned int option3;
  unsigned int option4;
  unsigned int option5;
  unsigned int option6;

  unsigned int cmd_crc;

} CMD_PROC_CommandStruct;


CMD_PROC_StatusTypeDef CMD_PROC_Process_Main(char* buffer);

CMD_PROC_StatusTypeDef CMD_PROC_CMD_Baud(CMD_PROC_CommandStruct* recp_command, char* response);
CMD_PROC_StatusTypeDef CMD_PROC_CMD_RTC(CMD_PROC_CommandStruct* recp_command, char* response);
CMD_PROC_StatusTypeDef CMD_PROC_CMD_Status(CMD_PROC_CommandStruct* recp_command, char* response);
uint32_t CalcCRC32(char* buffer, int length);
void ResponseStringGenerator(char* response_buffer, CMD_PROC_CommandStruct* command_struct, int options);

#endif /* __command_processor_H */