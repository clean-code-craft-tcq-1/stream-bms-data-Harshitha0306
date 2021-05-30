/* **************************************************************************************************
* File Name   : BMS_DataSender.c
* Author      : Harshitha Subramani
* * ************************************************************************************************** */

/* **************************************** Header Files **************************************************** */
#include "BMS_DataSender.h"
#include "stdio.h"
#include "string.h"

/* ***************************************** Variables ****************************************************** */
SendStatus(*SendData)(float,float) = {Print_ToConsole};


/* **************************************************************************************************
* Function      : This function sends BMS parameter value to console as an input
* Paramters     : None
* Returns       : Validity status if the inputs are printed  on console
* ***************************************************************************************************** */
SendStatus BMS_SendData()
{
  float Temperature;
  float ChargeRate;
  SendStatus Validity_status;

Temperature = Get_BMSTemperatue(Temperature_st);
ChargeRate = Get_BMSChargeRate(ChargeRate_st);

 Validity_status = SendData(Temperature, ChargeRate);
  
  return Validity_status;
}

/* **************************************************************************************************
* Function      : This function Prints BMS parameter value on console
* Paramters     : Temperature and ChargeRate
* Returns       : Validity status if the inputs are printed on console
* ***************************************************************************************************** */
SendStatus Print_ToConsole(float Temperature, float ChargeRate) {
  
  printf("Temperature:%+06.1f,SOC:%05.1f$\n", Temperature,ChargeRate);
  
  return SENTSUCCESSFULLY;
}
