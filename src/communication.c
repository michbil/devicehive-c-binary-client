
#ifndef __WIN32

#include <htc.h>
#include "eeprom.h"
#include "uart.h"
#include "pinout.h"

#endif

#include "DeviceHiveEngine.h"
#include "communication.h"
#include "DeviceConstants.h"
#include "CustomCommands.h"
#include "communication.h"


void SendRegMessage()
{
    SendRegistration2Data("{"
        "id:\"" DEVICE_ID "\","
        "key:\"" DEVICE_KEY "\","
        "name:\"" DEVICE_NAME "\","
        "deviceClass:{"
            "name:\"" DEVICE_CLASS_NAME"\","
            "version:\"" DEVICE_CLASS_VERSION "\"},"
        "equipment:["
            "{code:\"" LEVEL_EQP_CODE "\",name:\"" LEVEL_EQP_NAME "\",type:\"" LEVEL_EQP_TYPE "\"},"
            "{code:\"" VOLUME_EQP_CODE "\",name:\"" VOLUME_EQP_NAME "\",type:\"" VOLUME_EQP_TYPE "\"},"
            "{code:\"" CNT_EQP_CODE "\",name:\"" CNT_EQP_NAME "\",type:\"" CNT_EQP_TYPE "\"},"
            "{code:\"" TEMP_EQP_CODE "\",name:\"" TEMP_EQP_NAME "\",type:\"" TEMP_EQP_TYPE "\"},"
            "{code:\"" ERRORS_EQP_CODE "\",name:\"" ERRORS_EQP_NAME "\",type:\"" ERRORS_EQP_TYPE "\"},"
            "{code:\"" MONEY_EQP_CODE "\",name:\"" MONEY_EQP_NAME "\",type:\"" MONEY_EQP_TYPE "\"},"
            "{code:\"" "FLAGS" "\",name:\"" "FLAGS" "\",type:\"""binary flags""\"},"
            "{code:\"" LITER_INCASS_EQP_CODE "\",name:\"" LITER_INCASS_EQP_NAME "\",type:\"" LITER_INCASS_EQP_TYPE "\"},"
            "{code:\" ADC_VOLTS \",name:\"ADC_VOLTS\",type:\"VOLTAGE PRESSURE\"},"
            "{code:\" FROM_FULL \",name:\"FROM_FULL\",type:\"LITERS SINCE FULL\"}"
            "],"
        "commands:["
            "{intent:257,name:\"ClearErrors\",params:{}},"
            "{intent:258,name:\"ReadEeprom\",params:{adr:u16}}"
            "],"
        "notifications:["
            "{intent:256,name:\"equipment\",params:{equipment:str,value:u32}},"
            "{intent:259,name:\"eeblock\",params:{adr:u16,value:[u8]}},"
            "{intent:260,name:\"logline\",params:{line:str}}"
            "]"
        "}");
}

void SendLogLine(const char * line) {

    WORD len = GetStringSize(line);

    MessageHeader msgh = MESSAGE_HEADER_INIT(D2G_LOGLINE);
    msgh.Length = len;

    ResetChecksum(CHECKSUM_TX);
    SendBytes((unsigned char*)&msgh, sizeof(msgh));
    SendString(line);

    SendChecksum();
}

void SendEquipmentNotification(const char * EquipmentCode, long state)
{
    WORD len = sizeof(long) + GetStringSize(EquipmentCode);


    MessageHeader msgh = MESSAGE_HEADER_INIT(D2G_EQUIPMENT);
    msgh.Length = len;

    ResetChecksum(CHECKSUM_TX);
    SendBytes((unsigned char*)&msgh, sizeof(msgh));
    SendString(EquipmentCode);
    SendBytes((unsigned char*)&state, 4);

    SendChecksum();
}

void SendEEpromNotification(WORD addr)
{
    WORD len = 16+2+2;
    WORD i,res_adr;
    dataStruct ee_data;

    for (i=0;i<16;i++) {
        res_adr = addr+i;
        //ee_data.Items[i] = eeprom_read(res_adr);
    }
    ee_data.addr = addr;
    ee_data.Length = 16;

    MessageHeader msgh = MESSAGE_HEADER_INIT(D2G_EEPROM_CONTENTS);
    msgh.Length = len;

    ResetChecksum(CHECKSUM_TX);
    SendBytes((unsigned char*)&msgh, sizeof(msgh));
    SendBytes(&ee_data.addr,sizeof(WORD));
                                        
    SendBytes((unsigned char*)&ee_data.Length, sizeof(WORD));
    SendBytes(&ee_data.Items,16);
    
    SendChecksum();
}

void ReadEepromCommand(MessageHeader * msgh)
{
    char eeb;
    ReadEeepromData lcd = {FALSE, 0};

    if (RecvBytes((BYTE*)&lcd.Code, sizeof(DWORD)) > 0)
    {
            if (RecvBytes(&lcd.addr, sizeof(lcd.addr)))
            {
                if (RecvAndValidateChecksum())
                {
                    if (lcd.addr < 1024) {
                        SendNotificationData(lcd.Code, "READING", RESULT_OK);
                        SendEEpromNotification(lcd.addr);
                    } else {
                        SendNotificationData(lcd.Code, "WRONGADDRESS", ERR_FAIL);
                    }
                    //SendEquipmentNotification(CNT_EQP_CODE, 0x434343);
                }
                else
                {
                    SendNotificationData(lcd.Code, ERR_CHECKSUM, ERR_FAIL);
                }
            }
            else
            {
                SendNotificationData(lcd.Code, ERR_INVALID_VALUE, ERR_FAIL);
           
        }

    }
    else
    {
        SendNotificationData(0, ERR_TIMEOUT, ERR_FAIL);
    }
}
void ProcessClearErrorsCommand(MessageHeader * msgh)
{
    ClearErrorsCMD cmd;
   

    if (RecvBytes((BYTE*)&cmd.Code, sizeof(DWORD)) > 0)
    {
        if (msgh->Length != 4) {
            SendNotificationData(cmd.Code,ERR_INVALID_VALUE,ERR_FAIL);
        }
       if (RecvAndValidateChecksum()) {
            SendNotificationData(cmd.Code, ST_SUCCESS, RESULT_OK);

       } else SendNotificationData(cmd.Code, ERR_CHECKSUM, ERR_FAIL);
     }
    else
    {
        SendNotificationData(0, ERR_TIMEOUT, ERR_FAIL);
    }
}


extern long errors;
long flags = 0;

void send_parameters() {

    SendEquipmentNotification(CNT_EQP_CODE, 443335L);
    SendEquipmentNotification(ERRORS_EQP_CODE,1);
    SendEquipmentNotification(MONEY_EQP_CODE,1232);
    SendEquipmentNotification(LITER_INCASS_EQP_CODE,3232323);
    SendEquipmentNotification("FLAGS",1);
    SendEquipmentNotification("FROM_FULL",33);

 }





void SetFlag(long flag,char notify)
{
    flags |= flag;
    if (notify) SendEquipmentNotification("FLAGS",flags);
}
void ClearFlag(long flag,char notify)
{
    flags &= ~flag;
    if (notify) SendEquipmentNotification("FLAGS",flags);
}


int has_valid_message=0;
int auto_update_tmr=0;

char is_data() {
	return 0;
}

void handle_incoming_messages() {

        if (auto_update_tmr > 120) {
            auto_update_tmr = 1;
            send_parameters();

        }

        while (is_data()) {
            //push_message_into_receive_buffer(getchar());
        }

        if (has_valid_message)
        {
            has_valid_message=0;
            MessageHeader msgh;
            
            if (ReceiveMessageHeader(&msgh))
            {
                switch (msgh.Intent)
                {
                    case G2D_REQREG:
                        if (RecvAndValidateChecksum())
                        {
                            SendRegMessage();
                            send_parameters();
                        }
                        break;
                    case G2D_CLEAR_ERRORS:
                        ProcessClearErrorsCommand(&msgh);
                        break;
                    case G2D_READ_EEPROM:
                        ReadEepromCommand(&msgh);
                         
                        break;
                    default:
                        SkipMessage(msgh.Length);
                        break;
                }

            }
        }


}


