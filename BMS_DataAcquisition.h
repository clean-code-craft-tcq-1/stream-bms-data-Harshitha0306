/* **************************************************************************************************
* File Name   : BMS_DataAcquisition.h
* Author      : Harshitha Subramani
* * ************************************************************************************************** */


#ifndef BMS_DataAcquisition_h
#define BMS_DataAcquisition_h

#include <stdio.h>
#include <stdlib.h>


/* ******************************* Defines ******************************* */
 struct Battery_Parameter_s
{
  float  Min_value;
  float  Max_value;
  float  Error_value;
};

 struct Battery_Parameter_s Temperature_s;
 struct Battery_Parameter_s  ChargeRate_s;




/* ***************************** Prototypes ***************************** */
int isInRange(float Parameter_value, float min_value, float max_value);
float Get_BMSTemperatue(struct Battery_Parameter_s Temperature_s);
float Get_BMSChargeRate(struct Battery_Parameter_s ChargeRate_s);
float RandomNumGenerator(float min,float max);


#endif /* BMS_DataAcquisition_h */
