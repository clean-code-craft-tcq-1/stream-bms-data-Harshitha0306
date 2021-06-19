#include "bms_Rx.h"

#if(TEST_MODE)
char strInput[TestSize][100] = {0};
#endif

#if(TEST_MODE)
float TestSMAOuputValue[TestSize][NUMOFPARAM] = {0.0};
float TestMinOuputValue[TestSize][NUMOFPARAM] = {0.0};
float TestMaxOuputValue[TestSize][NUMOFPARAM] = {0.0};
#endif

/* Structure initialisation of battery parameters */
struct BatteryParam_s BatteryParam[NUMOFPARAM] = {{"Temperature", TEMP_MIN , TEMP_MAX},
                                                  {"ChargeRate", CHRGRATE_MIN , CHRGRATE_MAX}};

									 

/* Function pointer initialisation with functions to update the battery parameters */
UpdateParamSMAData_funcPtr UpdateParamSMAData[NUMOFPARAM] = {UpdateTemperatureCalcData , UpdateChargeRateCalcData};

/****************************************************************************************
*Func desc : This function is to receive the parameter value from console converts into float and does the following calculation
			- Simple moving average (sends INVALID_VALUE if input value received over stream is not valid)
			- Minimum value received over stream (sends INVALID_VALUE if input value received over stream is not valid) 
			- Maximum value received over stream (sends INVALID_VALUE if input value received over stream is not valid) 
*Return    : None
*****************************************************************************************/

void BMSDataReceiverCalc()
{
   int EoFDetected =0;
   float BMSParamValueRxd[NUMOFPARAM] = {0};
   float ReadingsBuffer[NUMOFPARAM][SMA_RANGE]= {0};
   float ReadingsSum[NUMOFPARAM]={0};
   int pos[NUMOFPARAM]={0};
   char str[MAXLENGTH_INPUTSTRING];
   struct BatteryParamOutput_s INVALID_VALUE_s = {INVALID_VALUE,INVALID_VALUE,INVALID_VALUE};
   
   /* Structure initialisation of battery evaluated parameters */
   struct BatteryParamOutput_s BatteryParamEvaluated[NUMOFPARAM]= {{0, TEMP_MAX, TEMP_MIN},
                                                             {0, CHRGRATE_MAX , CHRGRATE_MIN}};
  
    #if TEST_MODE
    int count=0;
    #endif 

    do
    {
        #if(TEST_MODE)
	    strcpy(str,strInput[count]);
	    #else
	    if(fgets(str,MAXLENGTH_INPUTSTRING, stdin)==NULL)
	    {
	        EoFDetected  = 1;
	    }
	   #endif
	   
        for (int i=0 ; i < NUMOFPARAM; i++)
	    {
	        BMSParamValueRxd[i] = getParamValuefromConsoleCustom(str,i);
	        
	        if(IsWithinRange(BMSParamValueRxd[i], BatteryParam[i].minValue , BatteryParam[i].maxValue))
	        {
	  
	            BatteryParamEvaluated[i].SMA =  movingAverageForRangeofValue((ReadingsBuffer+i), (ReadingsSum+i), i, SMA_RANGE, BMSParamValueRxd[i]);
	            
	            BatteryParamEvaluated[i].minRxd = (BMSParamValueRxd[i] < BatteryParamEvaluated[i].minRxd) ? BMSParamValueRxd[i] : BatteryParamEvaluated[i].minRxd;
	            
	            BatteryParamEvaluated[i].maxRxd = (BMSParamValueRxd[i] > BatteryParamEvaluated[i].maxRxd) ? BMSParamValueRxd[i] : BatteryParamEvaluated[i].maxRxd;
	            
		        UpdateParamSMAData[i](BatteryParamEvaluated[i]);
		        
	        }
	        else
	        {
	           UpdateParamSMAData[i](INVALID_VALUE_s);
	        } 
	       
        }
        
        #if(TEST_MODE)
        printf("Temperature:%f, ChargeRate:%f\n",BMSParamValueRxd[0],BMSParamValueRxd[1]);
	    printf("SMA Temperature:%f, ChargeRate:%f\n",BatteryParamEvaluated[0].SMA,BatteryParamEvaluated[1].SMA);
		printf("Min Temperature:%f, ChargeRate:%f\n",BatteryParamEvaluated[0].minRxd,BatteryParamEvaluated[1].minRxd);
		printf("Max Temperature:%f, ChargeRate:%f\n\n",BatteryParamEvaluated[0].maxRxd,BatteryParamEvaluated[1].maxRxd);
	    	    
	    count ++;
	    #endif
    }
    #if(TEST_MODE)
    while(count < TestSize);
    #else
    while(!((EoFDetected == 1)||(sig_caught == 1)));
    #endif
    
}

/****************************************************************************************
*Func desc : This function is to get the parameter value from the string passed
*Param     : scanLine     - String from which the parameter value is to be extracted
			 batteryParam - The parameter whise value is to be extracted from the passed string
*Return    : Parameter value - float type
*****************************************************************************************/

float getParamValuefromConsoleCustom(char *scanLine, enum BATTERYPARAM batteryParam)
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
*Func desc : The function to find the simple moving average . To be called only with valid data
*Param     : ptrArrNumbers  - pointer for Array which holds the values (modified by this function)
			 ptrSum         - pointer for sum variables which holds the previous sum value (modified by this function)
			 param_id       - The parameter whose data are passed in other param
			 range			- The range for which SMA is calculated
			 nextNum        - The new number which has to be appended and SMA is to be calculated
*Return    : Calculated SMA value for range passed - float type
*****************************************************************************************/

float movingAverageForRangeofValue(float *ptrArrNumbers, float *ptrSum, int param_id, int range, float nextNum)
{
	static int pos[NUMOFPARAM]= {0};
	
    if(range>1)
    {
   
       *ptrSum = *ptrSum - ptrArrNumbers[pos[param_id]] + nextNum;
  
        ptrArrNumbers[pos[param_id]] = nextNum;
        
		pos[param_id]++;
		if (pos[param_id] >= range)
        {
            pos[param_id] = 0;
        }
		
		return *ptrSum / range;
		
    }
    else if (range == 1)
    {
       return nextNum;
        
    }
    else
    {
        return INVALID_SMARANGE;
    }
 
}

