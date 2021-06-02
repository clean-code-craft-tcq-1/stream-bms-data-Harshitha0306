/* *************************************************************************
* File Name   : BMS_DataSender.h
* Description : Header file for BMS Sender type selection
* ************************************************************************* */

#ifndef BMS_DataSender_h
#define BMS_DataSender_h

#include <stdio.h>
#include <stdlib.h>

/* ******************************* Defines ******************************* */
#define PARAM_SIZE 100
#define INVALID 32767

 struct Battery_Parameter_s
{
  float  Min_value;
  float  Max_value;
};

typedef enum {
  SENDING_FAILED,
  SENTSUCCESSFULLY
} SendStatus;



/* ***************************** Prototypes ***************************** */

float * Get_BMSTemperatue(struct Battery_Parameter_s Temperature_s,int MAXPARAMNUM);
float * Get_BMSChargeRate(struct Battery_Parameter_s ChargeRate_s,int MAXPARAMNUM);
float RandomNumGenerator(float min,float max);
SendStatus Output_ToConsole(float* Temperature, float* ChargeRate,int MAXPARAMNUM);
SendStatus BMS_SendData(struct Battery_Parameter_s Temperature_s,struct Battery_Parameter_s ChargeRate_s,int MAXPARAMNUM);

#endif /* BMS_DataSender_h */
