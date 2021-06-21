#include "bms_Rx.h"

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