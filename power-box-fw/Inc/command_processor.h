
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __command_processor_H
#define __command_processor_H

#include "main.h"

typedef enum 
{
  CMD_PROC_OK       = 0x00U,
  CMD_PROC_ERROR    = 0x01U
} CMD_PROC_StatusTypeDef;

#define CMD_PROC_COMMAND_RTC "RTC"

#define CMD_PROC_SUBCOMMAND_GET "GET"

CMD_PROC_StatusTypeDef CMD_PROC_Process_Main(uint8_t* buffer);


#endif /* __command_processor_H */