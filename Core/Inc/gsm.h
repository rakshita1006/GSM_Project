/*
 * gsm.h
 *
 *  Created on: 30-Oct-2020
 *      Author: rakshita.parihar
 */


#ifndef GSM_H_
#define GSM_H_


//#include "main.h"

#include "stm32f4xx.h"
#include "Include.h"
#include "systick_timer.h"


#define MAX_Buff_Size 1024

#define SIZE_OF_AT_TX_RX_BUFFER 1024

UART_HandleTypeDef huart2;

static uint8_t gsm_state;
static uint8_t gprs_state;
static uint8_t tcp_state;

enum
{
GSM_INIT_STATE = 0,
NETWORK_STATE,
GSM_GPRS_STATE,
GSM_DATAPACKET_STATE,
GSM_TCPIP_STATE,
TCP_RECEIVE_DATA,
};

enum
{
TCPIP_Application_Mode_NonTransparent = 0,
TCPIP_Start_Connection_Mode,
TCPIP_DataRetrieve_DirectPUSh_Mode,
TCPIP_Open_Connection_Mode,
TCPIP_Send_Data_Mode,
TCPIP_Close_Connection_Mode,
TCPIP_END_Connection_Mode,
};

enum
{
gprs_registration = 0,
gprs_PDP_Attachment,
gprs_PDP_Context,
gprs_PDP_Activate,
};

typedef struct
{
	unsigned char command[50];
	unsigned char Response[3][20];
	unsigned char ResponseType[3];
	unsigned char dillimeter1;
	unsigned char dillimeter2;
	uint32_t timeout;
}ATCommadsConfig;


struct gsm_data_struct
{
   char imei[16];
   char imsi[16];
   char ccid[20];
   char network_strength[4];
   char cops[15];
   char copn[15];
   char cnbp[15];
   char Server_Response[1024];
   char gprs_registration[15];

}__attribute__ ((packed));

struct Gsm_Flags
{
	 unsigned  Start:1;
     unsigned  GsmInitialised:1;
     unsigned  GsmNetworkInitialised:1;
     unsigned  GPRS_REG_Flag:1;
     unsigned  GPRS_Attachment_Flag:1;
     unsigned  GPRS_PDP_Context_Flag:1;
     unsigned  GPRS_PDP_Activate_Flag:1;
     unsigned  GPRSInitialised:1;
     unsigned  TCPIP_Nontransparent_Mode:1;
     unsigned  TCPIP_Connection_Mode:1;
     unsigned  TCPIP_DataRetrieve_Mode:1;
     unsigned  TCPIP_Open_Connection_Mode:1;
     unsigned  TCPIP_Data_Send_Mode:1;
     unsigned  TCPIP_Close_Connection_Mode:1;
     unsigned  TCPIP_END_Connection_Mode:1;
     unsigned  Server_Response_Flag:1;
     unsigned Receive_Data_Flag:1;

}__attribute__ ((packed));

typedef struct {
    struct Gsm_Flags Flags;
    struct gsm_data_struct gsm_data;
    uint16_t RxDataCnt;
    uint16_t TxDataCnt;
	uint8_t TxData[SIZE_OF_AT_TX_RX_BUFFER];
	uint8_t RxData[SIZE_OF_AT_TX_RX_BUFFER];
}Gsm_struct;

extern Gsm_struct gsm;

struct AT_Command_Flags
{
	unsigned AT_Response:1;
}__attribute__ ((packed));

struct AT_Command_Flags AT_Flag;

void gsmtask();
void PeripheralInit();
void MX_GPIO_Init(void);
void MX_USART2_UART_Init(void);
void SystemClock_Config(void);
uint8_t Send_AT_Command(ATCommadsConfig *atcommand);
unsigned char* jump_char_fixed(unsigned char *pktPtr, char character);
bool gsm_sim_Status();
void gsm_ccid();
void gsm_imsi();
void gsm_imei();
bool network_registration_status(void);
void network_signal_strength();
void cops(void);
void copn(void);
bool PDP_status(void);
bool gprs_registration_status(void);
void gsm_data();
bool VerifyResponseCommand(ATCommadsConfig *atcommand);
bool Server_Response();
//#define SIZE_OF_AT_TX_RX_BUFFER 1024
//
//typedef struct  {
//	unsigned char command[40];
//	unsigned char Responce [3][20];
//	unsigned char ResponceType[3];
//	unsigned char delimit1;
//	unsigned char delimit2;
//	uint16_t ResponseTime;
//}ATCOMMANDS;
//
////extern ATCOMMANDS ;
//
//
//struct gsm_data_struct
//{
//   char imei[16];
//  // char utc_timeStamp[16];
////   char VehicalID[15];
////   char RecordID[15];
//   char SwVer[15];
//   char imsi[16];
//   char ccid[20];
//   char cops[15];
//   char lac[8];
//   char cellid[6];
//   char gsm_channel[2];
//   char status_port[6];
//   char command_port[6];
//
//   char signal_strength[3];
//   char modem_data_status[2];
//   char gsm_band[20];
//   char fnn[32];
//   char snn[16];
//   char server_name[25];
////   struct gsm_time_struct time;
////   struct gsm_date_struct date;
//}__attribute__ ((packed));
//
//
//struct Gsm_Flags{
//	volatile unsigned  Start:1;
//	volatile unsigned  GsmInitialised:1;
//	volatile unsigned  GsmErrorResponce:1;
//	volatile unsigned  ATCommandResponceReceive:1;
//	volatile unsigned  ATCommandResponceOK:1;
//}__attribute__ ((packed));
//
////struct gsm_flags
////{
////    volatile unsigned Start:1;
////    volatile unsigned GsmInitialised:1;
////    volatile unsigned GSMNetworkCheck:1;
////    volatile unsigned GprsInitialise:1;
////    volatile unsigned GprsAttachment:1;
////    volatile unsigned PdpContextPara:1;
////    volatile unsigned ActivePdpContext:1;
////    volatile unsigned DataPacketReady:1;
////    volatile unsigned SocketCreated:1;
////    volatile unsigned SocketConfigured:1;
////    volatile unsigned SocketConnected:1;
////    volatile unsigned SocketSent:1;
////    volatile unsigned SocketClosed:1;
////    volatile unsigned ServerResponsed:1;
////    volatile unsigned ServerResponsedFailed:1;
////    volatile unsigned SleepModeActivate:1;
////    volatile unsigned WakeupModeActivate:1;
////    volatile unsigned GsmWakeup:1;
////    volatile unsigned WrittenSuccessfully:1;
////    volatile unsigned WriteAttemptComplete:1;
////
////    volatile unsigned FramDataRead:1;
////    volatile unsigned FramPacketReady:1;
////
////    volatile unsigned ActivateGprs:1;
////    volatile unsigned GprsIdentify:1;
////
////    volatile unsigned TransmitData:1;
////    volatile unsigned AtCommandResponseReceived:1;
////}__attribute__ ((packed));
//typedef struct{
//	struct Gsm_Flags Flags;
//	struct gsm_data_struct gsm_data;
//    uint8_t NetworkRegistrationStat;
//    uint8_t NetworkRegistrationN;
//    uint8_t SocketNo;
//    uint8_t TxOperation;
//    uint16_t RxDataCnt;
//    uint16_t TxDataCnt;
//	uint8_t TxData[SIZE_OF_AT_TX_RX_BUFFER];
//	uint8_t RxData[SIZE_OF_AT_TX_RX_BUFFER];
//}Gsm_struct;
//
//extern Gsm_struct gsm;




#endif /* GSM_H_ */
