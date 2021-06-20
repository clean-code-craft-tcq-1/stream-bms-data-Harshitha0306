#include "bms_Rx.h"

#if(TEST_MODE)
int TestCount[NUMOFPARAM] = {0};
#endif

int sig_caught = 0;
/****************************************************************************************
*Func desc : The function which updates the calculated value based on passed structure, it can be adapted based on needs, 
			 Currently it does printing of param values
*Param     : BatteryParamEvaluated  - structure which holds the calculated value
			 .SMA         - Calculated SMA value
			 .minRxd      - The valid minimum value received over console
			 .maxRxd	  - The valid maximum value received over console
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
			 Currently it does printing of param values
*Param     : BatteryParamEvaluated  - structure which holds the calculated value
			 .SMA         - Calculated SMA value
			 .minRxd      - The valid minimum value received over console
			 .maxRxd	  - The valid maximum value received over console
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

/****************************************************************************************
*Func desc : The function check if the passed value is within the range passed 
*Param     : value   - The value for which range is to be checked
			 min     - The range minimum value 
			 max     - The range minimum value 
*Return    : valid status - bool type 
			 If 1 : Within Range,else out of range or Invalid range
*****************************************************************************************/

bool IsWithinRange(float value, float min, float max)
{
    if(min<max)
    {
        return ((value>=min)&&(value<=max));
    }
    else
    {
	    printf("Minimum value passes is greater than Maximum");
        return 0;
    }
}

/****************************************************************************************
*Func desc : The function returns minimum of two values passed 
*Param     : value1   - Value1 
			 value2   - Value2
*Return    : minimum of 2 values passed - float type 
*****************************************************************************************/
float MinimumOfTwoFloatNumbers(float value1, float value2)
{
	if (value1 < value2)
	{
		return value1;
	}
	else 
	{
		return value2;
	}
}

/****************************************************************************************
*Func desc : The function returns maximum of two values passed 
*Param     : value1   - Value1 
			 value2   - Value2
*Return    : maximum of 2 values passed - float type 
*****************************************************************************************/
float MaximumOfTwoFloatNumbers(float value1, float value2)
{
	if (value1 > value2)
	{
		return value1;
	}
	else 
	{
		return value2;
	}
}
