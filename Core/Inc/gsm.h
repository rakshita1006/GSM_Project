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



enum
{
GSM_INIT_STATE = 0,
GSM_NETWORK_STATE,
GSM_GPRS_STATE,
GSM_DATAPACKET_STATE,
GSM_TCPIP_STATE,
TCP_RECEIVE_DATA,
GSM_SLEEP,
GSM_RESET,
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
Gprs_Registration = 0,
Gprs_PDP_Attachment,
Gprs_PDP_Context,
Gprs_PDP_Activate,
};

typedef struct
{
	unsigned char command[50];
	unsigned char Response[3][40];
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
   char DeviceID[15];
   char SwVer[5];
   char RecordID[10];
   char Server_name[20];
   char Status_Port[5];
   char Command_Port[5];
   unsigned  char date[10];
   char time[8];
}__attribute__ ((packed));

struct Gsm_Flags
{
	 unsigned  Start:1;
     unsigned  GsmInitialised:1;
     unsigned  GsmSimStatus:1;
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
bool VerifyResponseCommand(ATCommadsConfig *atcommand, char dilli);
bool Server_Response();
void date(void);
void time(void);


#endif /* GSM_H_ */
