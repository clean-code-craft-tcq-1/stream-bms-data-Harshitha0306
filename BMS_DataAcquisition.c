/* **************************************************************************************************
* File Name   : BMS_DataAcquisition.c
* Author      : Harshitha Subramani
* * ************************************************************************************************** */


/* **************************************** Header Files **************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include "BMS_DataAcquisition.h"

/* **************************************************************************************************
* Function    : This function checks whether the BMS Parameter is in given range
* Param       : BMS Parameter min value,max value and Paramter input value
* Returns     : returns value 1 if the paramter is in given range else 0.
* * ************************************************************************************************** */

int isInRange(float Parameter_value, float min_value, float max_value)
{
  if((Parameter_value >= min_value) && (Parameter_value <= max_value))
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/* **************************************************************************************************
* Function    : This function is to fetch the BMS temperature value from randomly generated stream (faked)
* Param       : Temperature parameter min value,max value and Error value
* Returns     : Temperature value
* * ************************************************************************************************** */

float Get_BMSTemperatue(struct Battery_Parameter_s Temperature_s)
{
    float Temperature = 0;
    Temperature = RandomNumGenerator(Temperature_s.Min_value,Temperature_s.Max_value);
    if(isInRange(Temperature,Temperature_s.Min_value,Temperature_s.Max_value))
      {
          return Temperature;
      }
      
      return Temperature_s.Error_value;
}

/* **************************************************************************************************
* Function    : This function is to fetch the BMS Chargerate value from randomly generated stream (faked)
* Param       : Chargerate parameter min value,max value and Error value
* Returns     : Chargerate value
* * ************************************************************************************************** */

float Get_BMSChargeRate(struct Battery_Parameter_s ChargeRate_s)
{
    float ChargeRate = 0;
    ChargeRate = RandomNumGenerator(ChargeRate_s.Min_value,ChargeRate_s.Max_value);
    if(isInRange(ChargeRate,ChargeRate_s.Min_value,ChargeRate_s.Max_value))
      {
          return ChargeRate;
      }
      
      return ChargeRate_s.Error_value;
    
}

/* **************************************************************************************************
* Function    : This function to generate a random float number within the limits passed
* Param       :min value,max value
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
        return 0;
      }
    }
