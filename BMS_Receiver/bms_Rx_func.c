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
   char str[MAXLENGTH_INPUTSTRING];
   struct BatteryParamOutput_s INVALID_VALUE_s = {INVALID_VALUE,INVALID_VALUE,INVALID_VALUE};
   
   /* Structure initialisation of battery evaluated parameters */
   struct BatteryParamOutput_s BatteryParamEvaluated[NUMOFPARAM]= {{0, TEMP_MAX, TEMP_MIN},
                                                             {0, CHRGRATE_MAX , CHRGRATE_MIN}};
  
    do
    {
		EoFDetected = GetParamDataString(str,MAXLENGTH_INPUTSTRING);
        	   
        for (int i=0 ; i < NUMOFPARAM; i++)
	    {
	        BMSParamValueRxd[i] = getParamValuefromString(str,(enum BATTERYPARAM)i);
	        
	        if(IsWithinRange(BMSParamValueRxd[i], BatteryParam[i].minValue , BatteryParam[i].maxValue))
	        {
	  
	            BatteryParamEvaluated[i].SMA =  movingAverageForRangeofValue((ReadingsBuffer[i]), (ReadingsSum+i), i, SMA_RANGE, BMSParamValueRxd[i]);
	            
	            BatteryParamEvaluated[i].minRxd = MinimumOfTwoFloatNumbers(BMSParamValueRxd[i],BatteryParamEvaluated[i].minRxd);
	            
	            BatteryParamEvaluated[i].maxRxd = MaximumOfTwoFloatNumbers(BMSParamValueRxd[i],BatteryParamEvaluated[i].maxRxd);
				
				/*In case if additional statistics data are to be computed, the same to be appended before UpdateParamSMAData*/
	            
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
	    #endif	    
 
	}while(!((EoFDetected == 1)||(sig_caught == 1)));
   
    
}


