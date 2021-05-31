/* **************************************************************************************************
* File Name   : BMS_DataSender.c
* Author      : Harshitha Subramani
* * ************************************************************************************************** */


/* **************************************** Header Files **************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include "BMS_DataSender.h"



/* **************************************************************************************************
* Function    : This function reads the BMS temperature value from randomly generated stream
* Param       : Temperature parameter min value,max value
* Returns     : Temperature value
* * ************************************************************************************************** */

float * Get_BMSTemperatue(struct Battery_Parameter_s Temperature_s,int MAXPARAMNUM)
{
    static float Temperature_arr[20];
    for(int i=0;i<= MAXPARAMNUM;i++)
    {
       Temperature_arr[i] = RandomNumGenerator(Temperature_s.Min_value,Temperature_s.Max_value);
    }
    return Temperature_arr;
}

/* **************************************************************************************************
* Function    : This function reads the BMS Chargerate value from randomly generated stream
* Param       : Chargerate parameter min value,max value
* Returns     : Chargerate value
* * ************************************************************************************************** */

float * Get_BMSChargeRate(struct Battery_Parameter_s ChargeRate_s,int MAXPARAMNUM)
{
    static float ChargeRate_arr[20];
    for(int i=0;i <= MAXPARAMNUM;i++)
    {
        ChargeRate_arr[i] = RandomNumGenerator(ChargeRate_s.Min_value,ChargeRate_s.Max_value);
    }
    return ChargeRate_arr;
}

/* **************************************************************************************************
* Function    : This function generates random float number within the defined limits
* Param       : min value,max value
* Returns     : returns Random value
* * ************************************************************************************************** */

float RandomNumGenerator(float min, float max)
{
    if(min < max)
      {
        return (max - min) * ((float)rand() / RAND_MAX) + min;
      }
      else
      {
        printf("Invalid min and max input\n");
        return 0;
          
      }
    }

/* **************************************************************************************************
* Function      : This function sends BMS parameter value to console as an input
* Paramters     : None
* Returns       : Validity status if the inputs are printed  on console
* ***************************************************************************************************** */

SendStatus BMS_SendData(struct Battery_Parameter_s Temperature_s,struct Battery_Parameter_s ChargeRate_s,int MAXPARAMNUM)
{
   SendStatus Validity_status;
   float * Temperature = Get_BMSTemperatue(Temperature_s,MAXPARAMNUM);
   float * ChargeRate = Get_BMSChargeRate(ChargeRate_s,MAXPARAMNUM);
   Validity_status = Output_ToConsole(Temperature,ChargeRate,MAXPARAMNUM);
   return Validity_status;;
}

/* **************************************************************************************************
* Function      : This function Prints BMS parameter value on console
* Paramters     : Temperature and ChargeRate
* Returns       : Validity status if the inputs are printed on console
* ***************************************************************************************************** */

SendStatus Output_ToConsole(float * Temperature, float * ChargeRate,int MAXPARAMNUM) {

    for(int i=0;i <= MAXPARAMNUM;i++)
       {
          printf("Temperature:%0.3f,ChargeRate:%0.3f\n", Temperature[i],ChargeRate[i]);
       }
     return SENTSUCCESSFULLY;
}

