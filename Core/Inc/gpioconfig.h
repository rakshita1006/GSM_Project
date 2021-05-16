/*
 * gpioconfig.h
 *
 *  Created on: 05-Oct-2020
 *      Author: rakshita.parihar
 */


//#include "stm32f4xx_hal.h"



#ifndef GPIOCONFIG_H_
#define GPIOCONFIG_H_

/*
 * gpioconfig.h
 *
 *  Created on: 05-Oct-2020
 *      Author: rakshita.parihar
 */



#define  MODE_INPUT                  0x00000000U   /*!< Input Floating Mode                   */
#define  MODE_OUTPUT_PP              0x00000001U   /*!< Output Push Pull Mode                 */
#define  MODE_OUTPUT_OD              0x00000011U   /*!< Output Open Drain Mode                */
#define  MODE_AF_PP                  0x00000002U   /*!< Alternate Function Push Pull Mode     */
#define  MODE_AF_OD                  0x00000012U   /*!< Alternate Function Open Drain Mode    */
#define  MODE_ANALOG                 0x00000003U

#define  SPEED_FREQ_LOW              0x00000000U  /*!< IO works at 2 MHz, please refer to the product datasheet */
#define  SPEED_FREQ_MEDIUM     		 0x00000001U  /*!< range 12,5 MHz to 50 MHz, please refer to the product datasheet */
#define  SPEED_FREQ_HIGH      		 0x00000002U  /*!< range 25 MHz to 100 MHz, please refer to the product datasheet  */
#define  SPEED_FREQ_VERY_HIGH  		 0x00000003U

#define  NOPULL             	     0x00000000U   /*!< No Pull-up or Pull-down activation  */
#define  PULLUP       				 0x00000001U   /*!< Pull-up activation                  */
#define  PULLDOWN     				 0x00000002U   /*!< Pull-down activation                */

#define OUTPUT_TYPE                  0x00000010U

#define GPIO_MODE_Ref                0x00000003U

#define GPIO_PIN_NO_0                0
#define GPIO_PIN_NO_1                1
#define GPIO_PIN_NO_2                2
#define GPIO_PIN_NO_3                3
#define GPIO_PIN_NO_4                4
#define GPIO_PIN_NO_5                5
#define GPIO_PIN_NO_6                6
#define GPIO_PIN_NO_7                7
#define GPIO_PIN_NO_8                8
#define GPIO_PIN_NO_9                9
#define GPIO_PIN_NO_10               10
#define GPIO_PIN_NO_11               11
#define GPIO_PIN_NO_12               12
#define GPIO_PIN_NO_13               13
#define GPIO_PIN_NO_14               14
#define GPIO_PIN_NO_15               15


#define GPIO_MODE            		 0x00000003U
#define EXTI_MODE             		 0x10000000U
#define GPIO_MODE_IT         		 0x00010000U
#define GPIO_MODE_EVT         		 0x00020000U
#define RISING_EDGE           		 0x00100000U
#define FALLING_EDGE          		 0x00200000U
#define GPIO_OUTPUT_TYPE      		 0x00000010U

#define  NOPULL             	     0x00000000U   /*!< No Pull-up or Pull-down activation  */
#define  PULLUP       				 0x00000001U   /*!< Pull-up activation                  */
#define  PULLDOWN     				 0x00000002U   /*!< Pull-down activation                */

#define  MODE_IT_RISING              0x10110000U   /*!< External Interrupt Mode with Rising edge trigger detection          */
#define  MODE_IT_FALLING             0x10210000U   /*!< External Interrupt Mode with Falling edge trigger detection         */
#define  IT_RISING_FALLING           0x10310000U   /*!< External Interrupt Mode with Rising/Falling edge trigger detection  */



//#define GPIO_12_PIN 	12
typedef struct
{

	uint32_t Pin;

	uint32_t Mode;

	uint32_t Pull;

	uint32_t Speed;

	uint32_t Otype;

	uint32_t Alternate;

}GPIO_User_Config;  //GPIO_INIT_Def

extern GPIO_User_Config;

typedef enum
{
  PIN_RESET = 0,
  PIN_SET,
}PinStatus;

typedef struct
  {
	   uint32_t MODER;
	   uint32_t OTYPER;
	   uint32_t OSPEEDR;
	   uint32_t PUPDR;
	   uint32_t IDR;
	   uint32_t ODR;
	   uint32_t BSRR;
	   uint32_t LCKR;
	   uint32_t AFR[2];


  } GPIO_Reg_Config;  //GPIO_Type_Def

  typedef struct
  {
     uint32_t IMR;    /*!< EXTI Interrupt mask register,            Address offset: 0x00 */
     uint32_t EMR;    /*!< EXTI Event mask register,                Address offset: 0x04 */
     uint32_t RTSR;   /*!< EXTI Rising trigger selection register,  Address offset: 0x08 */
     uint32_t FTSR;   /*!< EXTI Falling trigger selection register, Address offset: 0x0C */
     uint32_t SWIER;  /*!< EXTI Software interrupt event register,  Address offset: 0x10 */
     uint32_t PR;     /*!< EXTI Pending register,                   Address offset: 0x14 */
  } GPIO_EXTI_TypeDef;

  void GPIO_Init(GPIO_Reg_Config* GPIOx, GPIO_User_Config* GPIO_INITx);
  void GPIO_Interrupt_Init(IRQn_Type IRQn, uint32_t Priority,uint32_t SubPriority);

 // void GPIO_Init (GPIO_Reg_Config* GPIOx, GPIO_User_Config* GPIO_INITx);
 // void GPIO_Interrupt_Init(GPIO_EXTI_TypeDef *GPIOx,GPIO_InitTypeDef *GPIO_Init);
  void ON_OFF(GPIO_Reg_Config* GPIOx,uint16_t GPIO_Pin,int ON_OFF);
  PinStatus ReadPin(GPIO_Reg_Config* GPIOx, uint16_t GPIO_Pin);
  void MS_Delay(void);


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




#endif /* GPIOCONFIG_H_ */


