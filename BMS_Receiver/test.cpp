#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include "bms_Rx.h"
#include "stddef.h"
#include "string.h"

/* Validating "getParamValuefromString"- data seperation from string */
TEST_CASE("Data seperation from Valid data string")
{
	float tempCalc, ChrgRateCalc;
	char str[100];
	strcpy(str,"Temperature:25.6degress     ChargeRate:1.2A");
    tempCalc = getParamValuefromString(str,TEMPERATURE);
    ChrgRateCalc = getParamValuefromString(str,CHARGERATE);
    
	REQUIRE(fabs(tempCalc - 25.6)<0.01);
	REQUIRE(fabs(ChrgRateCalc - 1.2)<0.01);
	
}

TEST_CASE("Data seperation from data string - Temperature data not found")
{
	float tempCalc, ChrgRateCalc;
	char str[100];
	strcpy(str,"TemperaturE:25.6degress     ChargeRate:3.6A");
    tempCalc = getParamValuefromString(str,TEMPERATURE);
    ChrgRateCalc = getParamValuefromString(str,CHARGERATE);
    
	REQUIRE(fabs(tempCalc - VALUE_NOTFOUND) <0.01);
	REQUIRE(fabs(ChrgRateCalc - 3.6)<0.01);
	
}

TEST_CASE("Data seperation from data string - ChargeRate data not found")
{
	float tempCalc, ChrgRateCalc;
	char str[100];
	strcpy(str,"Temperature:99.5degress     Chargerate:3.6A");
    tempCalc = getParamValuefromString(str,TEMPERATURE);
    ChrgRateCalc = getParamValuefromString(str,CHARGERATE);
    
	REQUIRE(fabs(tempCalc - 99.5) <0.01);
	REQUIRE(fabs(ChrgRateCalc - VALUE_NOTFOUND)<0.01);
	
}

TEST_CASE("Data seperation from data string - Valid Parameter in different order")
{
	float tempCalc, ChrgRateCalc;
	char str[100];
	strcpy(str,"ChargeRate:4.9A		Temperature:13.7degress");
    tempCalc = getParamValuefromString(str,TEMPERATURE);
    ChrgRateCalc = getParamValuefromString(str,CHARGERATE);
    
	REQUIRE(fabs(tempCalc - 13.7) <0.01);
	REQUIRE(fabs(ChrgRateCalc - 4.9)<0.01);
}

/* End of Validating "getParamValuefromString"- data seperation from string  */

/* Validating "movingAverageForRangeofValue" - SMA calculation */
TEST_CASE("Valid data range SMA check")
{
	float SMABuffer[5]={0}, SMASum;
	float smaCalc ;
	SMASum = 0;
	int  range = 5;
	float dataArray[10] = {65.34,98.66,10.25,-1.36,85.6,45.6,17.5,-10.00,0,36.55};
	float SMABufferExpected[10] = {13.06,32.8,34.85,34.57,51.69,47.75,31.51,27.46,27.74,17.93};
	for(int i=0; i<10;i++)
	{
	    smaCalc =  movingAverageForRangeofValue(SMABuffer, &SMASum ,0, range, dataArray[i]);
      	assert(fabs(smaCalc - SMABufferExpected[i]) <0.01);
		
	}

}

TEST_CASE("SMA check - Range 1")
{
	float SMABuffer[5]={0}, SMASum;
	float smaCalc ;
	SMASum = 0;
	int  range = 1;
	float dataArray[11] = {65.34,98.66,10.25,-1.36,85.6,45.6,17.5,-10.00,0,36.55,99.99};
	float SMABufferExpected[11] = {65.34,98.66,10.25,-1.36,85.6,45.6,17.5,-10.00,0,36.55,99.99};
	for(int i=0; i<11;i++)
	{
	    smaCalc =  movingAverageForRangeofValue(SMABuffer, &SMASum ,0, range, dataArray[i]);
      	assert(fabs(smaCalc - SMABufferExpected[i]) <0.01);
		
	}
}

TEST_CASE("SMA check - Range 0")
{
	float SMABuffer[5]={0}, SMASum;
	float smaCalc ;
	SMASum = 0;
	int  range = 0;
	float dataArray[9] = {65.34,98.66,10.25,-1.36,85.6,45.6,17.5,-10.00,0};
	
	for(int i=0; i<9;i++)
	{
	    smaCalc =  movingAverageForRangeofValue(SMABuffer, &SMASum ,0, range, dataArray[i]);
      	assert(fabs(smaCalc - INVALID_SMARANGE) <0.01);
		
	}
}

/*End of Validating "movingAverageForRangeofValue" - SMA calculation */


/*Validation of "IsWithinRange" function */
TEST_CASE("Range check")
{
	float paramValue;
	
	/* Valid range data*/
	paramValue = 75.2;
  	assert(IsWithinRange(paramValue , 50.55, 100) == 1);
	/* Less than min*/
	paramValue = 50.54;
  	assert(IsWithinRange(paramValue , 50.55, 100) == 0);
    /* Greater than max*/
	paramValue = 100.01;
  	assert(IsWithinRange(paramValue , 50.55, 100) == 0);
	/*Min > max input*/
	paramValue = 50.54;
	assert(IsWithinRange(paramValue , 50.55, 50.54) == 0);
	
}
/*End of Validation of "IsWithinRange" function*/



/*Validation of "MinimumOfTwoFloatNumbers" - Minimum finding function*/
TEST_CASE("Minimum function check ")
{
	float value1, value2, min;
	
	/* Value2 less than value1*/
	value1 = 75.2;
	value2 = 13.7;
	min = MinimumOfTwoFloatNumbers(value1,value2);
  	assert(fabs(min - 13.7 ) < 0.01);
	
	/* Value1 less than value2*/
	value1 = 100.87;
	value2 = 100.99;
	min = MinimumOfTwoFloatNumbers(value1,value2);
  	assert(fabs(min - 100.87 ) < 0.01);
	
	/* Both equal*/
	value1 = 54.37;
	value2 = 54.37;
	min = MinimumOfTwoFloatNumbers(value1,value2);
  	assert(fabs(min - 54.37 ) < 0.01);
	
	/* Minimum check for negative values*/
	value1 = -1.23;
	value2 = -2.35;
	min = MinimumOfTwoFloatNumbers(value1,value2);
  	assert(fabs(min - (-2.35) ) < 0.01);
	
}
/*End of Validation of "MinimumOfTwoFloatNumbers" - Minimum finding function*/

/* Validation of "MaximumOfTwoFloatNumbers" - Maximum finding function */
TEST_CASE("Maximum function check ")
{
	float value1, value2, max;
	
	/* Value2 less than value1*/
	value1 = 75.2;
	value2 = 13.7;
	max = MaximumOfTwoFloatNumbers(value1,value2);
  	assert(fabs(max - 75.2 ) < 0.01);
	
	/* Value1 less than value2*/
	value1 = 100.87;
	value2 = 100.99;
	max = MaximumOfTwoFloatNumbers(value1,value2);
  	assert(fabs(max - 100.99 ) < 0.01);
	
	/* Both equal*/
	value1 = 54.37;
	value2 = 54.37;
	max = MaximumOfTwoFloatNumbers(value1,value2);
  	assert(fabs(max - 54.37 ) < 0.01);
	
	/* Maximum check for negative values*/
	value1 = -1.23;
	value2 = -2.35;
	max = MaximumOfTwoFloatNumbers(value1,value2);
  	assert(fabs(max - (-1.23) ) < 0.01);
	
}
/*End of Validation of "MaximumOfTwoFloatNumbers" - Maximum finding function */

/*Validating "UpdateParamSMAData" function*/
TEST_CASE("Update function check -UpdateChargeRateCalcData")
{
		
	struct BatteryParamOutput_s BatteryParamInput[4]= {{2.365,25.65,10.23},
													   {71.35,9.14,-23.23},
													   {0.00,9563.23,-1.235},
													   {-3.754,0.00,123.45}};
		
	/*Reset Test count*/
	TestCount[CHARGERATE] = 0;
	
	/* Valid range data*/
	for(int i=0;i<4;i++)
	{
		UpdateChargeRateCalcData(BatteryParamInput[i]);
		assert(fabs(BatteryParamInput[i].SMA - TestSMAOuputValue[i][CHARGERATE]) < 0.02);
		assert(fabs(BatteryParamInput[i].minRxd - TestMinOuputValue[i][CHARGERATE]) < 0.02);
		assert(fabs(BatteryParamInput[i].maxRxd - TestMaxOuputValue[i][CHARGERATE]) < 0.02);
	}	
}

TEST_CASE("Update function check -UpdateTemperatureCalcData")
{
		
	struct BatteryParamOutput_s BatteryParamInput[5]= {{12.365,2.65,101.23},
													   {98.65,100.25,4.87},
													   {71.35,9.14,-23.23},
													   {0.00,9563.23,-1.235},
													   {-3.754,0.00,123.45}};
			
	/*Reset Test count*/
	TestCount[TEMPERATURE] = 0;
	
	/* Valid range data*/
	for(int i=0;i<5;i++)
	{
		UpdateTemperatureCalcData(BatteryParamInput[i]);
		assert(fabs(BatteryParamInput[i].SMA - TestSMAOuputValue[i][TEMPERATURE]) < 0.02);
		assert(fabs(BatteryParamInput[i].maxRxd - TestMaxOuputValue[i][TEMPERATURE]) < 0.02);
		assert(fabs(BatteryParamInput[i].minRxd - TestMinOuputValue[i][TEMPERATURE]) < 0.02);
	}	
}
/*End of Validating "UpdateParamSMAData" function*/


/*Validating Integration test of all functions */
TEST_CASE("Integrated test for all functions validating the requirement")
{
	strcpy(strInput[0],"Temperature:25.6degress     ChargeRate:1.2A");
    strcpy(strInput[1],"Temperature:79.65degress     ChargeRate:3.2A");
    strcpy(strInput[2],"Temperature:61.3degress     ChargeRate:0.0A");
    strcpy(strInput[3],"ChargeRate:3.6A     Temperature:37.54degress"); 
    strcpy(strInput[4],"ChargeRate:1.16A     Temperature:54.37degress");
    strcpy(strInput[5],"Temperature:47.23degress     ChargeRate:2.4A");
    strcpy(strInput[6],"Temperature:39.65degress     ChargeRate:0.37A");
    strcpy(strInput[7],"Temperature:109.65degress     ChargeRate:4.56A"); /*Out of range*/
    strcpy(strInput[8],"Temperature:19.65degress     ChargeRate:11.56A"); /* Temperature and Charge Rate Out of Range */
    strcpy(strInput[9],"TemperaturE:19.65degress     ChargeRate:4.56A");  /*Temperature not found*/
    strcpy(strInput[10],"Temperature:77.86degress     ChargeRate:0.54A"); 
    strcpy(strInput[11],"Temperature:20.00degress     Chargerate:4.56A"); /*Charge rate not found */
    
	/*Reset test count*/
	TestCount[TEMPERATURE] = 0;
	TestCount[CHARGERATE] = 0;
	
    BMSDataReceiverCalc();
    
    float ExpectedSMA[TestSize][NUMOFPARAM]= {5.12,0.24,
                                              21.05,0.88,
                                              33.31,0.88,
                                              40.81,1.6,
                                              51.69,1.83,
                                              56.029,2.07,
                                              48.01,1.506,
                                              65535,2.418,
                                              65535,65535,
                                              65535,2.61,
                                              51.33,2.48,
                                              47.82,65535,
                                              65535,65535};
                                              
    float ExpectedMin[TestSize][NUMOFPARAM] = {25.6,1.2,
                                               25.6,1.2,
                                               25.6,0.0,
                                               25.6,0.0,
                                               25.6,0.0,
                                               25.6,0.0,
                                               25.6,0.0,
                                               65535,0.0,
                                               65535,65535,
                                               65535,0.0,
                                               25.6,0.0,
                                               20.00,65535,
                                               65535,65535};
   
   float ExpectedMax[TestSize][NUMOFPARAM] = { 25.6,1.2,
                                               79.65,3.2,
                                               79.65,3.2,
                                               79.65,3.6,
                                               79.65,3.6,
                                               79.65,3.6,
                                               79.65,3.6,
                                               65535,4.56,
                                               65535,65535,
                                               65535,4.56,
                                               79.65,4.56,
                                               79.65,65535,
                                               65535,65535};
    
    for(int i = 0; i<TestSize ; i++)
    {
        for(int j=0;j<NUMOFPARAM;j++)
        {
            printf("\n %d Min :%f  Max:%f",i, TestMinOuputValue[i][j], TestMaxOuputValue[i][i]);
            printf("\n %d Min :%f  Max:%f",i, ExpectedMin[j][i], ExpectedMax[j][i]);
            assert(fabs(TestSMAOuputValue[i][j] - ExpectedSMA[i][j]) < 0.02);
            assert(fabs(TestMinOuputValue[i][j] - ExpectedMin[i][j]) < 0.02);
            assert(fabs(TestMaxOuputValue[i][j] - ExpectedMax[i][j]) < 0.02);
            
        }
        
    }
}
/* End of Integration test of all functions */	


/*Min and Max calculation check along integration check done */

TEST_CASE("Min max check test ")
{
	strcpy(strInput[0],"Temperature:50.65degress     ChargeRate:1.2A");
    strcpy(strInput[1],"Temperature:54.37degress     ChargeRate:3.2A");
    strcpy(strInput[2],"Temperature:61.3degress     ChargeRate:2.3A");
    strcpy(strInput[3],"ChargeRate:3.6A     Temperature:37.54degress"); 
    strcpy(strInput[4],"ChargeRate:1.16A     Temperature:79.37degress");
    strcpy(strInput[5],"Temperature:47.23degress     ChargeRate:2.4A");
	strcpy(strInput[6],"Temperature:109.65degress     ChargeRate:4.56A"); /*Temperature Out of range*/
    strcpy(strInput[7],"Temperature:32.65degress     ChargeRate:0.54A");
    strcpy(strInput[8],"Temperature:39.65degress     ChargeRate:11.56A"); /* Charge Rate Out of Range */
    strcpy(strInput[9],"TemperaturE:20.00degress     ChargeRate:4.57A");  /*Temperature not found*/
    strcpy(strInput[10],"Temperature:20.10degress     ChargeRate:0.37A"); 
    strcpy(strInput[11],"Temperature:20.01degress     Chargerate:4.56A"); /*Charge rate not found */
    strcpy(strInput[12],"Temperature:19.65degress     ChargeRate:5.1A"); /* Temperature and Charge Rate Out of Range */
	
	/*Reset Test count*/
	TestCount[TEMPERATURE] = 0;
	TestCount[CHARGERATE] = 0;
	
	
    BMSDataReceiverCalc();
                                 
    float ExpectedMin1[TestSize][NUMOFPARAM] = {50.65,1.2,
                                               50.65,1.2,
                                               50.65,1.2,
                                               37.54,1.2,
                                               37.54,1.16,
                                               37.54,1.16,
                                               65535,1.16,
                                               32.65,0.54,
                                               32.65,65535,
                                               65535,0.54,
                                               20.1,0.37,
                                               20.01,65535,
                                               65535,65535};
   
   float ExpectedMax1[TestSize][NUMOFPARAM] = { 50.65,1.2,
                                               54.37,3.2,
                                               61.3,3.2,
                                               61.3,3.6,
                                               79.37,3.6,
                                               79.37,3.6,
                                               65535,4.56,
                                               79.37,4.56,
                                               79.37,65535,
                                               65535,4.57,
                                               79.37,4.57,
                                               79.37,65535,
                                               65535,65535};
    
    for(int i = 0; i<TestSize ; i++)
    {
        for(int j=0;j<NUMOFPARAM;j++)
        {
            assert(fabs(TestMinOuputValue[i][j] - ExpectedMin1[i][j]) < 0.02);
            assert(fabs(TestMaxOuputValue[i][j] - ExpectedMax1[i][j]) < 0.02);
            
        }
        
    }
}
/*End of Min and Max calculation check along integration check done */


/*Checking "GetParamDataString" string updation for testing*/
TEST_CASE("String value fetched in passed sting for testing purpose")
{
	char appendStr[MAXLENGTH_INPUTSTRING];
	
	/*Reset Test count*/
	TestCount[TEMPERATURE] = 0;
	TestCount[CHARGERATE] = 0;
	
    /*	Check string 1 */
	strcpy(strInput[0],"Temperature:100.25degress     ChargeRate:3.7A");
	GetParamDataString(appendStr,MAXLENGTH_INPUTSTRING);
	assert(strcmp(appendStr,strInput[0])==0);
	TestCount[TEMPERATURE]++;
	
	/*	Check string 2 */
    strcpy(strInput[1],"Temperature:37.54degress     ChargeRate:5.4A");
	GetParamDataString(appendStr,MAXLENGTH_INPUTSTRING);
	assert(strcmp(appendStr,strInput[1])==0);
	TestCount[TEMPERATURE]++;
}
/*End of Checking "GetParamDataString" string updation for testing*/
