#include "bms_Rx.h"

#if(TEST_MODE)
int TestCount[NUMOFPARAM] = {0};
#endif

int sig_caught = 0;

/****************************************************************************************
*Func desc : The function to get the string which hold the Parameter data
*Param     : appendStr  - pointer to teh string which needs to be updated with string which has param details (modified by this function)
	     stringSize - the maximum length to which the data can be copied to passed string pointer
*Return    : Returns 0 if updation is successful 
	     Returns 1 if EoFDetected
	     Different integer values can be added based on additional error cases realised
*****************************************************************************************/

int GetParamDataString(char *appendStr, int stringSize)
{
	int EoFDetected = 0;
	#if(TEST_MODE)
	strcpy(appendStr,strInput[TestCount[TEMPERATURE]]);
	#else
	/*Released only for console, if in future, it is from file, it can be adapted here*/
	if(fgets(appendStr,stringSize,stdin)== NULL)
	{
		strcpy(appendStr,"EoF detected");
		printf("EoF detected, stopping reception\n");
	    EoFDetected  = 1;
	}
	#endif
	return EoFDetected;
}

/****************************************************************************************
*Func desc : This function is to get the parameter value from the string passed
	     Expected Format in scanLine string is as follows -> ParamName1:Value1Unit1	 ParamName2:Value2Unit2 	etc
	     Example:"Temperature:26.476degrees		ChargeRate:10.326A"
             Unit is optional, but the value should be followed by ':' after ParamName and unit and value should not have any spaces or token between them
   
*Param     : scanLine     - String from which the parameter value is to be extracted (Maximum string length size as "MAXLENGTH_INPUTSTRING")
	     batteryParam - The parameter whise value is to be extracted from the passed string
*Return    : Parameter value - float type
*****************************************************************************************/

float getParamValuefromString(char *scanLine, enum BATTERYPARAM batteryParam)
{
  char splitStr[NUMOFPARAM*2][12]={'\0'};
  char * pch;    
  int k=0;
  float temp;
  char buffer[MAXLENGTH_INPUTSTRING];
  
  strcpy(buffer,scanLine);
  pch = strtok (buffer," :\t");
  
  while (pch != NULL)
  {
    
    strcpy((splitStr[k]),pch);
	//printf("\n%s",splitStr[k]);
    k++;
    pch = strtok (NULL, " :\t");
  } 
  
  for(int j=0;j < (NUMOFPARAM*2);j=j+2)
  {
        
      if(strcmp((splitStr[j]),BatteryParam[batteryParam].ParamName) == 0)
      {
         temp = atof(splitStr[j+1]);
	
         break;
      }
      else
      {
          temp = VALUE_NOTFOUND;
      }
  }

  pch = NULL;

  return temp; 
}   


/****************************************************************************************
*Func desc : The function which updates the calculated value based on passed structure, it can be adapted based on needs, 
			 Currently it does printing of Temperature data in the following format 
			 "Temperature -> SMA : 14.08 degrees, Minimum : 70.41 degrees , Maximum : 70.41 degrees"
			 If additional parameters are to be added as output , the BatteryParamEvaluated needs to be adapted followed by printf realisation
*Param     : BatteryParamEvaluated  - structure which holds the calculated value
			 .SMA       - Calculated SMA value
			 .minRxd    - The valid minimum value received over console
			 .maxRxd    - The valid maximum value received over console
*Return    : Updation status- bool type
*****************************************************************************************/

bool UpdateTemperatureCalcData (struct BatteryParamOutput_s BatteryParamEvaluated)
{
	 /*This function can be adapted in production based on the usage, say to append data to file or Printing as needed*/
    #if(TEST_MODE)
    int i=TestCount[TEMPERATURE];
    TestSMAOuputValue[i][TEMPERATURE] = BatteryParamEvaluated.SMA;
    TestMinOuputValue[i][TEMPERATURE] = BatteryParamEvaluated.minRxd;
    TestMaxOuputValue[i][TEMPERATURE] = BatteryParamEvaluated.maxRxd;
	TestCount[TEMPERATURE]++;
	if(TestCount[TEMPERATURE] >= TestSize)
	{
		sig_caught = 1;
	}
	else
	{
		sig_caught = 0;
	}
    #endif
	if (BatteryParamEvaluated.SMA == INVALID_VALUE)
	{
	   printf("No Valid Temperature data received\n");
	}
	else
	{
		printf("Temperature -> SMA : %.2f degrees, Minimum : %.2f degrees , Maximum : %0.2f degrees \n", BatteryParamEvaluated.SMA, BatteryParamEvaluated.minRxd, BatteryParamEvaluated.maxRxd);
	}
		
    return 1;
}

/****************************************************************************************
*Func desc : The function which updates the calculated value based on passed structure, it can be adapted based on needs, 
			 Currently it does printing of charge rate data in the following format 
			 "ChargeRate -> SMA : 0.84 A , Minimum : 4.20 A, Maximum : 4.20 A"
			 If additional parameters are to be added as output , the BatteryParamEvaluated needs to be adapted followed by printf realisation
*Param     : BatteryParamEvaluated  - structure which holds the calculated value
			 .SMA       - Calculated SMA value
			 .minRxd    - The valid minimum value received over console
			 .maxRxd    - The valid maximum value received over console
*Return    : Updation status- bool type
*****************************************************************************************/
bool UpdateChargeRateCalcData (struct BatteryParamOutput_s BatteryParamEvaluated)
{
	 /*This function can be adapted in production based on the usage, say to append data to file or Printing as needed*/
    #if(TEST_MODE)
    int i = TestCount[CHARGERATE];
    TestSMAOuputValue[i][CHARGERATE] = BatteryParamEvaluated.SMA;
    TestMinOuputValue[i][CHARGERATE] = BatteryParamEvaluated.minRxd;
    TestMaxOuputValue[i][CHARGERATE] = BatteryParamEvaluated.maxRxd;
	TestCount[CHARGERATE]++;
	if(TestCount[CHARGERATE] >= TestSize)
	{
		sig_caught = 1;
	}
	else
	{
		sig_caught = 0;
	}
    #endif
	
	if (BatteryParamEvaluated.SMA == INVALID_VALUE)
	{
	   printf("No Valid Charge Rate data received\n");
	}
	else
	{
		printf("ChargeRate -> SMA : %.2f A , Minimum : %.2f A, Maximum : %0.2f A\n", BatteryParamEvaluated.SMA, BatteryParamEvaluated.minRxd, BatteryParamEvaluated.maxRxd);
	}
    
    return 1;
}


