/* *************************************************************************
* File Name   :    BMS_DataSender.h
* Description : Header file for BMS Sender type selection
* ************************************************************************* */
#ifndef BMS_DataSender_h
#define BMS_DataSender_h

#include "BMS_DataAcquisition.h"


/* ******************************* Defines ******************************* */

typedef enum {
  SENDING_FAILED,
  SENTSUCCESSFULLY
} SendStatus;

/* ***************************** Prototypes ***************************** */

SendStatus Print_ToConsole(float Temperature, float ChargeRate);
SendStatus BMS_SendData(void);

#endif

