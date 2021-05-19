/*
 * gsm.c
 *
 *  Created on: 30-Oct-2020
 *      Author: rakshita.parihar
 */

#include "Include.h"
#include "stm32f4xx_hal_uart.h"
//#include "stm32f4_discovery.h"
#include "stm32f4xx.h"
#include "gsm.h"



int AT_timer = 0;
int Response_Timer=0;
Gsm_struct gsm;
UART_HandleTypeDef huart2;
static uint8_t gsm_state;
static uint8_t gprs_state;
static uint8_t tcp_state;


ATCommadsConfig ECHO ={"ATE0",{"\r\nOK\r\n"," ","\r\nERROR\r\n"},{0,0,0},'\r','\n',500};
ATCommadsConfig Formate_Change ={"ATV0",{"\r\nOK\r\n"," ","\r\nERROR\r\n"},{0,0,0},'\r','\n',500};

ATCommadsConfig Sim_Detect = {"AT+CPIN?",{"READY","","\r\n+CME ERROR\r\n"},{0,0,0},'\r','\n',500};
ATCommadsConfig IMSI = {"AT+CIMI",{"\r\nOK\r\n","","\r\nCME ERROR\r\n"},{0,0,0},'\r','\n',500};
ATCommadsConfig IMEI = {"AT+CGSN",{"\r\nOK\r\n","","\r\n+CME ERROR\r\n"},{0,0,0},'\r','\n',500};
ATCommadsConfig CCID = {"AT+CICCID",{"\r\n+CCID:","","\r\n+CME ERROR\r\n"},{0,0,0},'\r','\n',500};

ATCommadsConfig NetwrokRegistration = {"AT+CREG=1",{"\r\nOK\r\n","","\r\nCME ERROR\r\n"},{0,0,0},'\r','\n',500};
ATCommadsConfig NetwrokRegistrationStatus = {"AT+CREG?",{"\r\n+CREG:","","\r\nCME ERROR\r\n"},{0,0,0},'\r','\n',500};
ATCommadsConfig NetwrokSignalStrength = {"AT+CSQ",{"\r\n+CSQ: \r\n","","\r\n+CME ERROR\r\n"},{0,0,0},'\r','\n',500};
ATCommadsConfig OperatorSelection = {"AT+COPS?",{"\r\n+COPS: \r\n","","\r\nCME ERROR\r\n"},{0,0,0},'\r','\n',500};
ATCommadsConfig ReadOperatorName = {"AT+COPN",{"\r\n+COPN: \r\n","","\r\nCME ERROR\r\n"},{0,0,0},'\r','\n',500};
// not fixed
//ATCommadsConfig BaudSelectionWrite = {"AT+CNBP=<mode>[,<lte_mode>][,<tds_mode>]",{"\r\nOK\r\n","","\r\nCME ERROR\r\n"},{0,0,0},'\r','\n',500};
ATCommadsConfig BaudSelection = {"AT+CNBP?",{"\r\nOK\r\n","","\r\n CME ERROR\r\n"},{0,0,0},'\r','\n',500};

ATCommadsConfig GPRSRegistration = {"AT+CGREG=1",{"\r\nOK\r\n","","\r\n+CME ERROR\r\n"},{0,0,0},'\r','\n',500};
ATCommadsConfig GPRSRegistrationStatus = {"AT+CGREG?",{"\r\n+CGREG:","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCommadsConfig PDPAttachWrite = {"AT+CGATT=1",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCommadsConfig PDPDetachWrite = {"AT+CGATT=0",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCommadsConfig PDPStatus = {"AT+CGATT?",{"\r\n+CGATT:","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCommadsConfig PDPActivate = {"AT+CGACT=1,1",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCommadsConfig PDPDeactivate = {"AT+CGACT=0",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCommadsConfig PDPActivateStatus = {"AT+CGACT?",{"\r\n+CGACT:","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//ATCommadsConfig PDPContext = {"AT+CGDCONT=1",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//not fixed
ATCommadsConfig PDPContext = {"AT+CGDCONT=1,""\"IP""\",""\"airtelgprs.com""\"",{"\r\n+CGDCONT: ","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCommadsConfig PDPContextStatus = {"AT+CGDCONT?",{"\r\n+CGDCONT: ","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};

ATCommadsConfig TCPIP_Application_Mode = {"AT+CIPMODE=0",{"\r\nOK\r\n ","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCommadsConfig TCPIP_Application_Mode_Status = {"AT+CIPMODE?",{"\r\n+CIPMODE:","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCommadsConfig TCPIP_Connection = {"AT+NETOPEN",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCommadsConfig TCPIP_Connection_Status = {"AT+NETOPEN?",{"\r\n+NETOPEN:","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCommadsConfig TCPIP_DataRetrieve = {"AT+CIPRXGET=0",{"\r\nOK\r\n ","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCommadsConfig TCPIP_DataRetrieve_Status = {"AT+CIPRXGET?",{"\r\n+CIPRXGET:","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCommadsConfig TCPIP_Connection_Establish = {"AT+CIPOPEN=0,""\"TCP""\",""\"13.126.165.4""\",4000",{"\r\nOK\r\n ","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCommadsConfig TCPIP_Connection_Establish_Status = {"AT+CIPOPEN?",{"\r\n+CIPOPEN:","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//ATCommadsConfig TCPIP_DataSend = {"AT+CIPSEND=0,",{"\r\n>\r\n ","\r\nOK\r\n+CIPSEND:","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCommadsConfig TCPIP_Close_Connection = {"AT+CIPCLOSE=0",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCommadsConfig TCPIP_END_Connection = {"AT+NETCLOSE",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCommadsConfig TCPIP_DataSend = {"AT+CIPSEND=0,",{"\r\n>\r\nOK\r\n+CIPSEND:"," ","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//ATCOMMANDS TcpIp_Send_data = {"AT+CIPSEND=0,",{"\r\nOK\r\n+CIPSEND:","\r\n>","\r\n+CME ERROR"},{0,0,0},'\r','\n',5000}; //returns a number identifying the socket
//ATCOMMANDS Socket_connection_Direct_Mode = {"AT+CIPOPEN=0,""\"TCP""\",""\"13.126.165.4""\",""\"4000",{"\r\nOK\r\n","","\r\n+CME ERROR"},{0,0,0},'\r','\n',5000}; //returns a number identifying the socket
//ATCommadsConfig ServerResponse = {" ",{"\r\nRECV FROM:13.126.165.4:4000\r\n+IPD","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
//ATCommadsConfig GSM_Date&time= {"AT+CCLK?",{"\r\n+CCLK:","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};
ATCommadsConfig GSM_Date_time = {"AT+CCLK?",{"\r\n+CCLK:","","\r\n+CME ERROR"},{0,0,0},'\r','\n',500};


uint8_t Send_AT_Command(ATCommadsConfig *atcommand)
{
	int i=0;

	while(atcommand->command[i] != '\0')
	{
	HAL_UART_Transmit(&huart2,&atcommand->command[i] ,1,100);
	i++;
	}

	HAL_UART_Transmit(&huart2,&atcommand->dillimeter1 ,1,100);
	HAL_UART_Transmit(&huart2,&atcommand->dillimeter2 ,1,100);

	startTimer(&AT_timer,atcommand->timeout, false);
	while (AT_Flag.AT_Response == false)
	{
	 if(isTimerComplete(AT_timer))
		{
         break;
	    }
	}

	 stopTimer(AT_timer);
	 return 1;

}


bool gsm_sim_Status()
{
	int i=0,j=0;
	Send_AT_Command(&Sim_Detect);
	unsigned char *pktptr = &gsm.RxData[0];
//	pktptr = jump_char_fixed(pktptr,':');
//	pktptr++;
	while(*pktptr != '\r')
	{
		if(*pktptr == Sim_Detect.Response[0][i])
			i++;
		else return false;
		pktptr++;
	}
	return true;
}


void gsm_ccid()
{
	int i=0,j=0;
	Send_AT_Command(&CCID);
//	char Data[]="\r\n+ICCID:8991102005303552671\r\n\r\nOK\r\n";
//	while(Data[j]!='K')
//	{
//		gsm.RxData[j] = Data[j];
//		j++;
//
//	}
	unsigned char *pktptr = &gsm.RxData[0];
	pktptr = jump_char_fixed(pktptr,':');
	//pktptr++;
	while(*pktptr != '\r')
	{
		gsm.gsm_data.ccid[i++] = *pktptr;
		pktptr++;
	}
}
void gsm_imsi()
{
	int i=0,j=0;
	Send_AT_Command(&IMSI);
//	char Data[]="\r\n404100530355267\r\n\r\nOK\r\n";
//	while(Data[j]!='K')
//	{
//		gsm.RxData[j] = Data[j];
//		j++;
//
//	}
	unsigned char *pktptr = &gsm.RxData[0];
	pktptr = jump_char_fixed(pktptr,'\n');
	//pktptr++;
	while(*pktptr != '\r')
	{
		gsm.gsm_data.imsi[i++] = *pktptr;
		pktptr++;
	}
}

void gsm_imei()
{
	int i=0,j=0;
	Send_AT_Command(&IMEI);
//	char Data[]="\r\n861123052577218\r\n\r\nOK\r\n";
//		while(Data[j]!='K')
//		{
//			gsm.RxData[j] = Data[j];
//			j++;
//
//		}
	unsigned char *pktptr = &gsm.RxData[0];
	pktptr = jump_char_fixed(pktptr,'\n');
	//pktptr++;
	while(*pktptr != '\r')
	{
		gsm.gsm_data.imei[i++] = *pktptr;
		pktptr++;
	}
}

bool network_registration_status(void)
{
	Send_AT_Command(&NetwrokRegistrationStatus);
	unsigned char *pktptr = &gsm.RxData[0];
	pktptr = jump_char_fixed(pktptr,',');
	pktptr++;
	if(*pktptr == '1')
		return true;
	else
		return false;
}

void date(void)
{
		unsigned char Data[]="+CCLK: ""\"04/01/2001,00:14:12+22""\"";  // AT+CIPOPEN=0,""\"TCP""\",""\"13.126.165.4""\",4000"
		int j=0;
		while(true)
		{
			if(Data[j]!='\0'){
			gsm.RxData[j] = Data[j];
			j++;
			}
			else{
				gsm.RxData[j] = Data[j];
				break;
			}

		}
	//Send_AT_Command(&GSM_Date_time);
	int i=0;
	unsigned char *pktptr = &gsm.RxData[0];
	pktptr = jump_char_fixed(pktptr,'"');
	//pktptr++;
		while(*pktptr != ',')
		{
			gsm.gsm_data.date[i++] = *pktptr;
			pktptr++;
		}
}
void time(void)
{
		char Data[]="+CCLK: “04/01/2001,00:14:12+22”";
		int j=0;
		while(true)
		{
			if(Data[j]!='\0'){
			gsm.RxData[j] = Data[j];
			j++;
			}
			else{
				gsm.RxData[j] = Data[j];
				break;
			}

		}
		//Send_AT_Command(&GSM_Date_time);
		int i=0;
		unsigned char *pktptr = &gsm.RxData[0];
		pktptr = jump_char_fixed(pktptr,',');
		while(*pktptr != '+')
		{
			gsm.gsm_data.time[i++] = *pktptr;
			pktptr++;
		}
}
void network_signal_strength()
{
	int i=0,j=0;
	Send_AT_Command(&NetwrokSignalStrength);
//	char Data[]="\r\n+CSQ: 22,0\r\n\r\nOK\r\n";
//		while(Data[j]!='K')
//		{
//			gsm.RxData[j] = Data[j];
//			j++;
//
//		}
	unsigned char *pktptr = &gsm.RxData[0];
	pktptr = jump_char_fixed(pktptr,':');
	pktptr++;
	while(*pktptr != '\r')
	{
		gsm.gsm_data.network_strength[i++] = *pktptr;
		pktptr++;
	}
}

void cops(void)
{
	int i=0;
	Send_AT_Command(&OperatorSelection);
	unsigned char *pktptr = &gsm.RxData[0];
	pktptr = jump_char_fixed(pktptr,':');
	pktptr++;
	while(*pktptr != '\r')
	{
		gsm.gsm_data.cops[i++] = *pktptr;
		pktptr++;
	}
}

void copn(void)
{
	int i=0;
	Send_AT_Command(&ReadOperatorName);
	unsigned char *pktptr = &gsm.RxData[0];
	pktptr = jump_char_fixed(pktptr,':');
	pktptr++;
	while(*pktptr != '\r')
	{
		gsm.gsm_data.copn[i++] = *pktptr;
		pktptr++;
	}
}


void cnbp(void)
{
//	char Data[]="\r\n+CGREG:";
//	int j=0;
//	while(true)
//	{
//		if(Data[j]!=':'){
//		gsm.RxData[j] = Data[j];
//		j++;
//		}
//		else{
//			gsm.RxData[j] = Data[j];
//			break;
//		}
//
//	}
	int i=0;
	Send_AT_Command(&BaudSelection);
	unsigned char *pktptr = &gsm.RxData[0];
	pktptr = jump_char_fixed(pktptr,':');
	pktptr++;
	while(*pktptr != '\r')
	{
		gsm.gsm_data.cnbp[i++] = *pktptr;
		pktptr++;
	}
}

bool gprs_registration_status(void)
{
	Send_AT_Command(&GPRSRegistrationStatus);
	unsigned char *pktptr = &gsm.RxData[0];
	pktptr = jump_char_fixed(pktptr,',');
	pktptr++;
	if(*pktptr == '1')
		return true;
	else
		return false;
}

void gsm_data()
{
	copn();
	cnbp();
	date();
	time();
}

bool VerifyResponseCommand(ATCommadsConfig *atcommand, char dilli)
{
	if(str_comp_dilimetr(gsm.RxData, &atcommand->Response[0][0],dilli) == true)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

unsigned char* jump_char_fixed(unsigned char *pktPtr, char character)
{
    while(*pktPtr++ !=  character);
    return pktPtr;
}

void gsmtask()
{
	date();
	time();
	GenerateStausPacket();
}

//void gsmtask()
//{
//	switch(gsm_state)
//		{
//		case GSM_INIT_STATE:
//		{
//			if (gsm.Flags.Start == true && gsm.Flags.GsmInitialised !=true)
//			{
//				gsm_init();
//				Send_AT_Command(&ECHO);
//			}
//			if(gsm.Flags.GsmInitialised == true)
//			{
//				if(gsm_sim_Status() == true)
//				{
//
//					gsm_imsi();
//					gsm_imei();
//					gsm_ccid();
//					gsm.Flags.GsmSimStatus = true;
//					gsm_state = GSM_NETWORK_STATE;
//					break;
//				}
//				else
//				{
//					gsm_state = GSM_INIT_STATE;
//				}
//			}
//		}
//	    break;
//		case GSM_NETWORK_STATE:
//		{
//			Send_AT_Command(&NetwrokRegistration);
//			if (network_registration_status() == true)
//			{
//				cops();
//				network_signal_strength();
//				gsm.Flags.GsmNetworkInitialised = true;
//	    		gsm_state = GSM_GPRS_STATE;
//			}
//			else
//			{
//				gsm_state = GSM_NETWORK_STATE;
//			}
//		}
//		break;
//		case GSM_GPRS_STATE:
//		{
//			if(gsm.Flags.GsmNetworkInitialised == true)
//			{
//				switch(gprs_state)
//				{
//					case Gprs_Registration:
//					{
//
//						uint8_t gprs_reg_state=0;
//						Send_AT_Command(&GPRSRegistration);
//						Send_AT_Command(&GPRSRegistrationStatus);
//						gprs_reg_state=VerifyResponseCommand(&GPRSRegistrationStatus,':');
//						if(gprs_reg_state == true)
//						{
//							gsm.Flags.GPRS_REG_Flag = true;
//							gprs_state = Gprs_PDP_Attachment;
//						}
//						else
//						{
//							gsm.Flags.GPRS_REG_Flag =false;
//						}
//					}
//					break;
//					case Gprs_PDP_Attachment:
//					{
//						uint8_t gprs_attachment_state=0;
//					    Send_AT_Command(&PDPAttachWrite);
//					    Send_AT_Command(&PDPStatus);
//					    gprs_attachment_state=VerifyResponseCommand(&PDPStatus,':');
//						if(gprs_attachment_state== true)
//						{
//							gsm.Flags.GPRS_Attachment_Flag =true;
//							gprs_state = Gprs_PDP_Context;
//						}
//						else
//						{
//							gsm.Flags.GPRS_Attachment_Flag =false;
//						}
//					}
//					break;
//					case Gprs_PDP_Context:
//					{
//						uint8_t gprs_PDP_Context_state=0;
//						Send_AT_Command(&PDPContext);
//						Send_AT_Command(&PDPContextStatus);
//						gprs_PDP_Context_state=VerifyResponseCommand(&PDPContextStatus,':');
//						if(gprs_PDP_Context_state== true)
//						{
//							gsm.Flags.GPRS_PDP_Context_Flag =true;
//							gprs_state = Gprs_PDP_Activate;
//						}
//						else
//						{
//							gsm.Flags.GPRS_PDP_Context_Flag =false;
//						}
//					}
//					break;
//					case Gprs_PDP_Activate:
//					{
//						uint8_t gprs_PDP_Activate_state=0;
//						Send_AT_Command(&PDPActivate);
//						Send_AT_Command(&PDPActivateStatus);
//						gprs_PDP_Activate_state=VerifyResponseCommand(&PDPActivateStatus,':');
//						if(gprs_PDP_Activate_state == true)
//						{
//							gsm.Flags.GPRS_PDP_Activate_Flag =true;
//							gsm.Flags.GPRSInitialised =true;
//							gprs_state = Gprs_PDP_Attachment;
//							gsm_state = GSM_DATAPACKET_STATE;
//						}
//						else
//						{
//
//							Send_AT_Command(&PDPDeactivate);
//							gsm.Flags.GPRS_PDP_Activate_Flag =false;
//							gprs_state = Gprs_PDP_Activate;
//						}
//					}
//					break;
//			    }
//			}
//		}
//		break;
//		case GSM_DATAPACKET_STATE:
//				{
//					gsm_data();
//					gsm_state = GSM_TCPIP_STATE;
//				}
//	    break;
//		case GSM_TCPIP_STATE:
//				{
//					if(gsm.Flags.GPRSInitialised == true)
//					{
//						switch(tcp_state)
//						{
//						case TCPIP_Application_Mode_NonTransparent:
//						{
//							uint8_t TCPIP_Application_Mode_state=0;
//							Send_AT_Command(&TCPIP_Application_Mode);
//							Send_AT_Command(&TCPIP_Application_Mode_Status);
//							TCPIP_Application_Mode_state=VerifyResponseCommand(&TCPIP_Application_Mode_Status,':');
//							if( TCPIP_Application_Mode_state == true)
//							{
//								gsm.Flags.TCPIP_Nontransparent_Mode =true;
//								tcp_state = TCPIP_Start_Connection_Mode;
//							}
//							else
//							{
//								gsm.Flags.TCPIP_Nontransparent_Mode =false;
//							}
//						}
//						break;
//						case TCPIP_Start_Connection_Mode:
//						{
//							uint8_t TCPIP_Connection_Mode_state=0;
//							Send_AT_Command(&TCPIP_Connection);
//							Send_AT_Command(&TCPIP_Connection_Status);
//							TCPIP_Connection_Mode_state=VerifyResponseCommand(&TCPIP_Connection_Status,':');
//							if( TCPIP_Connection_Mode_state == true)
//							{
//								gsm.Flags.TCPIP_Connection_Mode =true;
//								tcp_state = TCPIP_DataRetrieve_DirectPUSh_Mode;
//							}
//							else
//							{
//								Send_AT_Command(&TCPIP_END_Connection);
//								Send_AT_Command(&TCPIP_Close_Connection);
//								gsm.Flags.TCPIP_Connection_Mode =false;
//							}
//						}
//						break;
//						case TCPIP_DataRetrieve_DirectPUSh_Mode:
//						{
//							uint8_t TCPIP_DataRetrieve_Mode_state=0;
//							Send_AT_Command(&TCPIP_DataRetrieve);
//							Send_AT_Command(&TCPIP_DataRetrieve_Status);
//							TCPIP_DataRetrieve_Mode_state=VerifyResponseCommand(&TCPIP_DataRetrieve_Status,':');
//							if( TCPIP_DataRetrieve_Mode_state == true)
//							{
//								gsm.Flags.TCPIP_DataRetrieve_Mode =true;
//								tcp_state = TCPIP_Open_Connection_Mode;
//							}
//							else
//							{
//								gsm.Flags.TCPIP_DataRetrieve_Mode =false;
//							}
//						}
//						break;
//						case TCPIP_Open_Connection_Mode:
//						{
//							uint8_t TCPIP_Open_Connection_Mode_state=0;
//							Send_AT_Command(&TCPIP_Connection_Establish);
//							Send_AT_Command(&TCPIP_Connection_Establish_Status);
//							TCPIP_Open_Connection_Mode_state=VerifyResponseCommand(&TCPIP_Connection_Establish_Status,':');
//							if( TCPIP_Open_Connection_Mode_state == true)
//							{
//								gsm.Flags.TCPIP_Open_Connection_Mode =true;
//								tcp_state =TCPIP_Send_Data_Mode ;
//							}
//							else
//							{
//								gsm.Flags.TCPIP_Open_Connection_Mode =false;
//							}
//						}
//						break;
//						case TCPIP_Send_Data_Mode:
//						{
//							Send_AT_Command(&TCPIP_DataSend);
//							char data[] ="Hello GS group";
//							GenerateStausPacket();
//							uint8_t CNTRL_Z = 0x1A;
//							uint8_t TCPIP_DATA_Send_Mode_state=0;
//							if(str_comp_dilimetr(gsm.RxData, &TCPIP_DataSend.Response[1][0],0) == true)
//							{
//								HAL_UART_Transmit(&huart2, &data, sizeof(data), 1000);
//								HAL_UART_Transmit(&huart2,&CNTRL_Z, 1, 1000);
//
//							}
//							else
//							{
//                                break;
//							}
//						    HAL_Delay(1000);    //delay 1sec
//							TCPIP_DATA_Send_Mode_state=VerifyResponseCommand(&TCPIP_DataSend,':');
//							if(TCPIP_DATA_Send_Mode_state == true)
//							{
//								gsm.Flags.TCPIP_Data_Send_Mode =true;
//								gsm_state =TCP_RECEIVE_DATA;
//				                tcp_state =TCPIP_Start_Connection_Mode ;
//				                gsm.Flags.Server_Response_Flag = false;
//							}
//
//							else
//							{
//								gsm.Flags.TCPIP_Data_Send_Mode =false;
//								tcp_state =TCPIP_Send_Data_Mode;
//							}
//						}
//						break;
//						}
//				}
//		}
//		break;
//		case TCP_RECEIVE_DATA:
//		{
//			startTimer(&Response_Timer,5000, false);
//			while (gsm.Flags.Server_Response_Flag == false)
//			{
//				if(isTimerComplete(Response_Timer))
//				{
//					break;
//				}
//			}
//		    stopTimer(Response_Timer);
//			//gsm.Flags.Server_Response_Flag = true;// for testing
//			if(str_comp_dilimetr(gsm.RxData,"\r\nRECV FROM:13.126.165.4:4000\r\n+IPD", 0))
//			{
//				gsm.Flags.Server_Response_Flag = false;
//				Send_AT_Command(&TCPIP_END_Connection);
//				Send_AT_Command(&TCPIP_Close_Connection);
//				gsm.Flags.Receive_Data_Flag = true;
//				gsm_state = GSM_SLEEP;
//
//			}
//			else
//			{
//				gsm.Flags.Receive_Data_Flag = false;
//				gsm_state = GSM_TCPIP_STATE;
//				tcp_state =TCPIP_Send_Data_Mode;
//				break;
//			}
//		}
//		break;
//		case GSM_SLEEP:
//		{
//			gsm_state = GSM_RESET;
//		}
//
//		case GSM_RESET:
//		{
//			gsm_state = GSM_INIT_STATE;
//		}
//		default:
//		break;
//	}
//}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	gsm.Flags.Server_Response_Flag = true;
	gsm.RxData[gsm.RxDataCnt]=Uart_Rx_Buffer;
	gsm.RxDataCnt=(1+ gsm.RxDataCnt) % MAX_Buff_Size;
	HAL_UART_Receive_IT(&huart2,&Uart_Rx_Buffer, sizeof(Uart_Rx_Buffer));

}


// git add .
//  git status
// git commit -m "gsm verification function"
// git push -u origin master










