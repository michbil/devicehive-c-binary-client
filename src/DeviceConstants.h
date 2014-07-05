#ifndef __DEVICE_CONSTANTS_H__
#define __DEVICE_CONSTANTS_H__

#include "Guid.h"

#define DEVICE_KEY              "WATER_F1"
#define DEVICE_NAME             "WATER_SARAY"
#define DEVICE_CLASS_NAME       "vending_water"
#define DEVICE_CLASS_VERSION    "1.0"

#define EQUIPMENT_LENGTH        2
#define NOTIFICATIONS_COUNT     1
#define COMMANDS_COUNT          1
#define NPEQ_COUNT              2
#define LED_CMD_COUNT           1

//const GUID DeviceID =           {0x7201BE97, 0x4677, 0x4A57, {0xAA, 0xB1, 0x89, 0x56, 0x39, 0xAF, 0x8B, 0xD5}};
#define DEVICE_ID               "7201be97-4677-4a57-aab1-895639af8bd9"

#define NP_EQUIPMENT            "equipment"
#define NP_STATE                "state"
#define NOTIFY_EQUIPMENT        "equipment"
#define LED_CMD_NAME            "UpdateLedState"

#define LEVEL_EQP_NAME            "LEVEL"
#define LEVEL_EQP_CODE            "LEVEL"
#define LEVEL_EQP_TYPE            "TANK LEVEL"

#define VOLUME_EQP_NAME            "VOLUME_S"
#define VOLUME_EQP_CODE            "VOLUME_S"
#define VOLUME_EQP_TYPE            "TANK VOLUME"

#define TEMP_EQP_NAME            "TEMP"
#define TEMP_EQP_CODE            "TEMP"
#define TEMP_EQP_TYPE            "Temperatuer sensor"

#define CNT_EQP_NAME            "COUNTER"
#define CNT_EQP_CODE            "COUNTER"
#define CNT_EQP_TYPE            "OVERALL COUNTER"

#define MONEY_EQP_NAME            "MONEY_IN"
#define MONEY_EQP_CODE            "MONEY_IN"
#define MONEY_EQP_TYPE            "MONEY AFTER INCASS"

#define LITER_INCASS_EQP_NAME     "LITER_INCASS"
#define LITER_INCASS_EQP_CODE     "LITER_INCASS"
#define LITER_INCASS_EQP_TYPE     "LITERS AFTER INCASS"

#define ERRORS_EQP_NAME            "ERRORS"
#define ERRORS_EQP_CODE            "ERRORS"
#define ERRORS_EQP_TYPE            "ERRORS"

#define ERR_UNKNOWN_CMD         "Unknown command"
#define ERR_FAIL                "Failed"
#define ERR_INVALID_VALUE       "Invalid data. 1-byte Boolean value expected."
#define ERR_EMPTY_EQUIPMENT     "Failed to receive the equipment name."
#define ERR_INVALID_EQUIPMENT   "The specified equipment not supported."
#define ERR_TIMEOUT             "Failed to retrieve LED state due to timeout."
#define ERR_CHECKSUM            "Invalid checksum."

#define RESULT_OK               "OK"
#define ST_SUCCESS              "ERRORS CLEARED"

#define D2G_EQUIPMENT           (MIN_CUSTOM_INTENT)
//#define G2D_LED                 (MIN_CUSTOM_INTENT + 1)
#define G2D_CLEAR_ERRORS        (MIN_CUSTOM_INTENT + 1)
#define G2D_READ_EEPROM         (MIN_CUSTOM_INTENT + 2)
#define D2G_EEPROM_CONTENTS     (MIN_CUSTOM_INTENT + 3)
#define D2G_LOGLINE             (MIN_CUSTOM_INTENT +4 )

typedef struct tagEquipmentNotification
{
    char * EquipmentCode;
    BOOL State;
} EquipmentNotification;

#endif
