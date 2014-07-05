/* 
 * File:   communication.h
 * Author: user
 *
 * Created on 27 Èþíü 2014 ã., 12:31
 */

#ifndef COMMUNICATION_H
#define	COMMUNICATION_H

#ifdef	__cplusplus
extern "C" {
#endif

void handle_incoming_messages();
void ProcessCommand(MessageHeader * msgh);
void SendEquipmentNotification(const char * EquipmentCode, long state);
void SendRegMessage();
void send_parameters();
void SendLogLine(const char * line);

#define FLAG_IDLE (1<<0)
#define FLAG_WAITMONEY  (1<<1)
#define FLAG_POURWATER  (1<<2)
#define FLAG_UPPERLEVEL (1<<3)
#define FLAG_CALIBRATION (1<<4)
#define FLAG_CALIBRATIONLOCK (1<<5)
#define FLAG_UPPERLEVELOCK (1<<6)
#define FLAG_NALIV (1<<7)
#define FLAG_OUTPUT_ON (1<<8)

void SetFlag(long flag,char notify);
void ClearFlag(long flag,char notify);

#ifdef	__cplusplus
}
#endif

#endif	/* COMMUNICATION_H */

