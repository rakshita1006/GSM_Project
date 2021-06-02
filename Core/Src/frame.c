/*
 * frame.c
 *
 *  Created on: 29-Apr-2021
 *      Author: rakshita.parihar
 */
#include "Include.h"

#include <string.h>


//Gsm_struct gsm;
char DeviceID[15] = "DS23456001";		//DS + IMEI last 5 digit  + 001 or DS + IMEI last 5 digit + K2K
char TimeStmp[15] = "123123123123123";
char RecordID[10] = "00123456";  //  K2K + IMEI last 5 digit
char SwVer[5] = "1.00";			//
char Server_name[] = "13.126.165.4";	// pankaj_personal  //  13.126.165.4
char Status_Port[5] = "9000";			// 4000
char Command_Port[5] = "8000";			// 8000
char Modem_data_status[2] = "1";
//char CRC_Value[15];
uint32_t CRC_Value1;
uint32_t CRC_Value2;

uint32_t str_copy_ram_lim_ret( char *rec_src_ram_add,  char *rec_dest_ram_add,  char rec_delimitter,char src_dest)
{
     char *rec_src_add = rec_src_ram_add;
    while(*rec_src_ram_add != rec_delimitter)
        *rec_dest_ram_add++ = *rec_src_ram_add++;
    return (rec_src_ram_add - rec_src_add + src_dest);
}
//
//
//unsigned str_comp_ram( char *rec_src_ram_add,  char *rec_dest_ram_add,  uint32_t rec_count)
//{
//    while(rec_count--)
//    {
//        if(*rec_dest_ram_add++ != *rec_src_ram_add++)
//            return(0);8
//    }
//    return(1);
//}
//
//
//
unsigned str_comp_ram_lim( char *rec_src_ram_add,  char *rec_dest_ram_add,  uint8_t rec_delim)
{
    while(*rec_src_ram_add != rec_delim)
    {
        if(*rec_dest_ram_add++ != *rec_src_ram_add++)
            return(0);
    }
    return(1);
}
//
//
void str_copy_ram_lim( char *rec_src_ram_add,  char *rec_dest_ram_add,  char rec_delimitter)
{
    while(*rec_src_ram_add != rec_delimitter)
        *rec_dest_ram_add++ = *rec_src_ram_add++;
}

int str_copy_count(char* Source_Ram_address, char* Destination_Ram_address, uint32_t length)
{
    int count=0;
	while( count != length)
		{
			  *Destination_Ram_address++ = *Source_Ram_address++;
			  count++;

		}
}


int convert_crcint_to_char(uint32_t num, char *str,uint32_t length)
{
	//int temp=count_intlength(num);
	if(num == 0)
	{
		*str  = '0';
		return 0;
	}
	switch(length)
	{
//		case 10:
//			*str++ = num/1000000000 + 0x30;
//			num =  num%1000000000;
		case 9:
			*str++ = num/100000000 + 0x30;
			num =  num%100000000;
		case 8:
			*str++ = num/10000000 + 0x30;
			num =  num%10000000;
		case 7:
			*str++ = num/1000000 + 0x30;
			num =  num%1000000;
		case 6:
			*str++ = num/100000 + 0x30;
			num =  num%100000;
		case 5:
			*str++ = num/10000 + 0x30;
			num =  num%10000;
		case 4:
			*str++ = num/1000 + 0x30;
			num =  num%1000;
		case 3:
			*str++ = num/100 + 0x30;
			num =  num%100;
		case 2:
			*str++ = (num/10) + 0x30;
			num =  num%10;
		case 1:
			*str++ = num + 0x30;
			num=0;
			break;
        default:
        	*str = '/0';
        	return 0;
	}
	return 1;
}
//CRC_Value= xcrc32 (gsm.TxData,4,1001);
void GenerateStausPacket()
{
//    memcpy(Gsm.GsmDataUni.GsmDataStru.utc_timeStamp,TimeStmp , sizeof(TimeStmp));

      memcpy(gsm.gsm_data.DeviceID,DeviceID, sizeof(DeviceID));
      memcpy(gsm.gsm_data.SwVer ,SwVer, sizeof(SwVer));
      memcpy(gsm.gsm_data.RecordID ,RecordID, sizeof(RecordID));
      memcpy(gsm.gsm_data.Status_Port,Status_Port , sizeof(Status_Port));
      memcpy(gsm.gsm_data.Command_Port,Command_Port , sizeof(Command_Port));
      memcpy(gsm.gsm_data.Server_name,Server_name , sizeof(Server_name));
    //  memcpy(gsm.gsm_data.CRC_Value,CRC_Value, sizeof(CRC_Value));
//
//    memcpy(Gsm.GsmDataUni.GsmDataStru.command_port,Command_Port , sizeof(Command_Port));
//    memcpy(Gsm.GsmDataUni.GsmDataStru.server_name,Server_name , sizeof(Server_name));
//    memcpy(Gsm.GsmDataUni.GsmDataStru.status_port,Status_Port , sizeof(Status_Port));

//
////    memcpy(Gsm.GsmDataUni.GsmDataStru.status_port,Status_Port , sizeof(Command_Port));
////
////    memcpy(Gsm.GsmDataUni.GsmDataStru.status_port,Status_Port , sizeof(Command_Port));
////
////    memcpy(Gsm.GsmDataUni.GsmDataStru.status_port,Status_Port , sizeof(Command_Port));
////
////    memcpy(Gsm.GsmDataUni.GsmDataStru.status_port,Status_Port , sizeof(Command_Port));
////    Gsm.GsmDataUni.GsmDataStru.VehicalID = "NER12345";
////    Gsm.GsmDataUni.GsmDataStru.RecordID = "12345";
////    Gsm.GsmDataUni.GsmDataStru.SwVer = "1.01";
////    Gsm.GsmDataUni.GsmDataStru.modem_data_status = "1";
//    // start frame
    unsigned char  *char_dest_ptr = &gsm.TxData[L_FRAME_INIT];
        // Device ID
    	char_dest_ptr += str_copy_ram_lim_ret(gsm.gsm_data.DeviceID,char_dest_ptr,0,0);
    	*char_dest_ptr++ = ','; // try once
        // Record ID
		char_dest_ptr += str_copy_ram_lim_ret(gsm.gsm_data.RecordID,char_dest_ptr,0,0);
		*char_dest_ptr++ = ','; // try once
        // Software Version
		char_dest_ptr += str_copy_ram_lim_ret(gsm.gsm_data.SwVer,char_dest_ptr,0,0);
		*char_dest_ptr++ = ','; // try once
    	// imei
        char_dest_ptr += str_copy_ram_lim_ret(gsm.gsm_data.imei,char_dest_ptr,0,0);
        *char_dest_ptr++ = ','; // try once
        // IMSI
		char_dest_ptr += str_copy_ram_lim_ret(gsm.gsm_data.imsi,char_dest_ptr,0,0);
        *char_dest_ptr++ = ','; // try once
        // CCID
        char_dest_ptr += str_copy_ram_lim_ret(gsm.gsm_data.ccid,char_dest_ptr,0,0);
        *char_dest_ptr++ = ','; // try once
        // Vendor Name
//		char_dest_ptr += str_copy_ram_lim_ret(gsm.gsm_data.GsmDataStru.ccid,char_dest_ptr,0,0);
//		*char_dest_ptr++ = ','; // try once
		//signal strength
		char_dest_ptr += str_copy_ram_lim_ret(gsm.gsm_data.network_strength,char_dest_ptr,0,0);
		*char_dest_ptr++ = ','; // try once
		//sensor data
//		char_dest_ptr += str_copy_ram_lim_ret(gsm.gsm_data.GsmDataStru.signal_strength,char_dest_ptr,0,0);
//		*char_dest_ptr++ = ','; // try once
//	     Band
//	    char_dest_ptr += str_copy_ram_lim_ret(gsm.gsm_data.GsmDataStru.gsm_band,char_dest_ptr,0,0);
//	    *char_dest_ptr++ = ','; // try once
	    //  Module(LTE)
//	     char_dest_ptr += str_copy_ram_lim_ret(gsm.gsm_data.gsm_band,char_dest_ptr,0,0);
//	     *char_dest_ptr++ = ','; // try once
		 //Server Name
		 char_dest_ptr += str_copy_ram_lim_ret(gsm.gsm_data.Server_name,char_dest_ptr,0,0);
		 *char_dest_ptr++ = ','; // try once
		 // Status Port
		 char_dest_ptr += str_copy_ram_lim_ret(gsm.gsm_data.Status_Port,char_dest_ptr,0,0);
		 *char_dest_ptr++ = ','; // try once
		 // Command Port
		 char_dest_ptr += str_copy_ram_lim_ret(gsm.gsm_data.Command_Port,char_dest_ptr,0,0);
		 *char_dest_ptr++ = ','; // try once
		 // date
		 char_dest_ptr += str_copy_ram_lim_ret(gsm.gsm_data.date,char_dest_ptr,0,0);
		 *char_dest_ptr++ = ','; // try once
		// time
        char_dest_ptr += str_copy_ram_lim_ret(gsm.gsm_data.time,char_dest_ptr,0,0);
        *char_dest_ptr++ = ','; // try once
//        //CRC
   //     char_dest_ptr += str_copy_ram_lim_ret(gsm.gsm_data.CRC_Value,char_dest_ptr,0,0);
  //      *char_dest_ptr++ = ',';







//    // COPS
//        char_dest_ptr += str_copy_ram_lim_ret(Gsm.GsmDataUni.GsmDataStru.cops,char_dest_ptr,0,0);
//        *char_dest_ptr++ = ','; // try once
//    // Modem Data status
//        char_dest_ptr += str_copy_ram_lim_ret(Gsm.GsmDataUni.GsmDataStru.modem_data_status,char_dest_ptr,0,0);
//        *char_dest_ptr++ = ','; // try once
//    // LAC
//        char_dest_ptr += str_copy_ram_lim_ret(Gsm.GsmDataUni.GsmDataStru.lac,char_dest_ptr,0,0);
//        *char_dest_ptr++ = ','; // try once
//    // CELLID
//        char_dest_ptr += str_copy_ram_lim_ret(Gsm.GsmDataUni.GsmDataStru.cellid,char_dest_ptr,0,0);
//        *char_dest_ptr++ = ','; // try once

//    // Channel
//        char_dest_ptr += str_copy_ram_lim_ret(Gsm.GsmDataUni.GsmDataStru.gsm_channel,char_dest_ptr,0,0);
//        *char_dest_ptr++ = ','; // try once
//    // FNN
//        char_dest_ptr += str_copy_ram_lim_ret(Gsm.GsmDataUni.GsmDataStru.fnn,char_dest_ptr,0,0);
//        *char_dest_ptr++ = ','; // try once
//    //SNN
//        char_dest_ptr += str_copy_ram_lim_ret(Gsm.GsmDataUni.GsmDataStru.snn,char_dest_ptr,0,0);
//        *char_dest_ptr++ = ','; // try once


//    //Latitude float to char
//        //char_dest_ptr += float_to_char(Gps.GpsDataString.latitude,char_dest_ptr,4);
////        char_dest_ptr += str_copy_ram_lim_ret(Gps.GpsDataString.latitude,char_dest_ptr,0,0);
////        *char_dest_ptr++ = ','; // try once
////    // Longitude float to char
////        //char_dest_ptr += float_to_char(Gps.GpsDataString.longitude,char_dest_ptr,4);
////        char_dest_ptr += str_copy_ram_lim_ret(Gps.GpsDataString.longitude,char_dest_ptr,0,0);
////        *char_dest_ptr++ = ','; // try once
////    // Speed float to char
////        //char_dest_ptr += float_to_char(Gps.GpsDataString.speed,char_dest_ptr,3);
////        char_dest_ptr += str_copy_ram_lim_ret(Gps.GpsDataString.speed,char_dest_ptr,0,0);
////        *char_dest_ptr++ = ','; // try once
////    // Altitude float to char
////        //char_dest_ptr += float_to_char(Gps.GpsDataString.altitude,char_dest_ptr,3);
////        char_dest_ptr += str_copy_ram_lim_ret(Gps.GpsDataString.altitude,char_dest_ptr,0,0);
////        *char_dest_ptr++ = ','; // try once
//////    // Angle
//////        char_dest_ptr += str_copy_ram_lim_ret(Gps.GpsDataUni.GpsDataStru.alt,char_dest_ptr,0,0);
//////        *char_dest_ptr++ = ','; // try once
////    // No. of Satellite
////        dec_byte_to_char_fixed(&Gps.GpsDataString.satCount,char_dest_ptr,2); // decimal to char
//        char_dest_ptr += 2;
//        *char_dest_ptr++ = ',';
//    //char_dest_ptr += str_copy_ram_lim_ret(Gps.GpsDataUni.GpsDataStru.satlCnt,char_dest_ptr,0,0);
//    //*char_dest_ptr++ = ','; // try once
//    // HDOP float to char
////        char_dest_ptr += str_copy_ram_lim_ret(Gps.GpsDataString.hdopString,char_dest_ptr,0,0);
//        *char_dest_ptr++ = ','; // try once
//
//        char crc_high_byte = 55;
//        char crc_low_byte = 58;
//        //socketTxData  ,  Gsm.socketTxData[L_FRAME_INIT]
        str_copy_ram_lim("STX,",gsm.TxData,0);
        uint16_t temp_frame_len = L_FRAME_LEN(char_dest_ptr - &gsm.TxData[L_FRAME_INIT]);
        convert_integer_to_char(temp_frame_len,&gsm.TxData[L_STX],4);
  //      gsm.TxData[L_STX+4] = ',';
        gsm.TxData[L_STX+L_FR_LEN]   = gsm.gsm_data.FC_CONFIGURATION;
        gsm.TxData[L_STX+L_FR_LEN+1] = ',';

//0x17dfeb99
//        //crc_generate_modbus(Gsm.socketTxData,(char_dest_ptr - Gsm.socketTxData));
//        //crc_high_byte = Gsm.socketTxData[char_dest_ptr - Gsm.socketTxData];
//        //crc_low_byte = Gsm.socketTxData[char_dest_ptr - Gsm.socketTxData + 1];
//        dec_byte_to_char_fixed(&crc_high_byte,&gsm.TxData[char_dest_ptr - gsm.TxData],3);
//        dec_byte_to_char_fixed(&crc_low_byte,&gsm.TxData[char_dest_ptr - gsm.TxData+3],3);
//        crc_generate_ascii_modbus(Gsm.socketTxData,(char_dest_ptr - Gsm.socketTxData));
        gsm.gsm_data.CRC_Value= xcrc32 (gsm.TxData,133,0xffffffff);
        convert_crcint_to_char(gsm.gsm_data.CRC_Value,&gsm.TxData[char_dest_ptr - gsm.TxData],9);
        str_copy_ram_lim("ETX",&gsm.TxData[char_dest_ptr - gsm.TxData+9],0);
        gsm.TxDataCnt = char_dest_ptr - gsm.TxData + L_CRC + L_ETX;
////        GSM.Params.socket[socket].updated = 1;
        //str_copy_count(gsm.TxData,gsm.RxData,(gsm.TxDataCnt-12));
int i=0;
        while(gsm.TxData[i] !='\0')
        {
//        	uint16_t count=0;
//        	count = (gsm.TxDataCnt-12);
//        	str_copy_count(gsm.TxData,gsm.RxData,(gsm.TxDataCnt-12));
//        	CRC_Value2 = xcrc32 (gsm.RxData,144,0xffffffff);
        	//break;
        	gsm.RxData[i] = gsm.TxData[i];
        	i++;
        }
        // verification crc function call
        // verify_crc(gsm rx data, length( total length - crc & etx)
      //  CRC_Value2 = xcrc32 (gsm.RxData,144,0xffffffff);
        if(verify_crc(gsm.RxData,(gsm.TxDataCnt-12)))
        {
        	gsm.Flags.DataCRCCorrect = 1;
        }
        gsm.Flags.DataPacketReady = 1;
   //     Gsm.TxOperation = 1;
}


