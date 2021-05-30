/* File Details ***********************************************************************************************
* File Name   :    main.c
* Author      : Arul Kumar Sundaramoorthy
* Description : Battery Management System(BMS) Temperature & SOC Data Sends for every 1 Seconds
* Functions   : main
* *********************************************************************************************************** */

/* **************************************** Header Files **************************************************** */

#include "BMS_DataSender.h"

/* Function Details *******************************************************************************************
* Function Name : main
* Description   : main function to transmit data for every 1 seconds
* Arguments     : -
* Returns       : 0
* *********************************************************************************************************** */
int main() {
    int MAXPRINT = 15;
    for(int i=0;i <= MAXPRINT;i++)
    {
    BMS_SendData();
    }
    
    return 0;
}
