#ifndef __CUSTOM_COMMANDS_H__
#define __CUSTOM_COMMANDS_H__


typedef struct tagEquipmentNotificationData
{
    char * EquipmentCode;
    long data;
} EquipmentNotificationData;

typedef struct tagLogLine {
    char * LoggedLine;
} LogLine;

typedef struct tagClearErrorsCMD
{
    DWORD Code;

} ClearErrorsCMD;

typedef struct tagReadEepromData
{
    DWORD Code;
    WORD addr;

} ReadEeepromData;

typedef struct {
    WORD addr;
    WORD Length;
    BYTE Items[16];
} dataStruct;


#endif
