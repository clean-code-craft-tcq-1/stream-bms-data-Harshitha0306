#include <stdio.h>
#include <stdlib.h>
#include "BMS_DataSender.h"

void main()
{
	  struct Battery_Parameter_s Temperature_s = {20,80};
    struct Battery_Parameter_s ChargeRate_s  = {0,5};
    int MAXPARAMNUM = 30;
    
    BMS_SendData(Temperature_s,ChargeRate_s,MAXPARAMNUM);
}
