
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "bms_Rx.h"
#include "stddef.h"
#include "string.h"

/* Validating Get data from Console */
TEST_CASE("Test from Console - Valid data")
{
	float tempCalc, ChrgRateCalc;
	char *str;
	strcpy(str,"Temperature:25.6degress     ChargeRate:1.2A");
    tempCalc = getParamValuefromConsoleCustom(str,TEMPERATURE);
    ChrgRateCalc = getParamValuefromConsoleCustom(str,CHARGERATE);
    
	REQUIRE(fabs(tempCalc - 25.6)<0.01);
	REQUIRE(fabs(ChrgRateCalc - 1.2)<0.01);
	
}

TEST_CASE("Test from Console - Temperature data not found")
{
	float tempCalc, ChrgRateCalc;
	char *str;
	strcpy(str,"TemperaturE:25.6degress     ChargeRate:3.6A");
    tempCalc = getParamValuefromConsoleCustom(str,TEMPERATURE);
    ChrgRateCalc = getParamValuefromConsoleCustom(str,CHARGERATE);
    
	REQUIRE(fabs(tempCalc - VALUE_NOTFOUND) <0.01);
	REQUIRE(fabs(ChrgRateCalc - 3.6)<0.01);
	
}

TEST_CASE("Test from Console - ChargeRate data not found")
{
	float tempCalc, ChrgRateCalc;
	char *str;
	strcpy(str,"Temperature:99.5degress     Chargerate:3.6A");
    tempCalc = getParamValuefromConsoleCustom(str,TEMPERATURE);
    ChrgRateCalc = getParamValuefromConsoleCustom(str,CHARGERATE);
    
	REQUIRE(fabs(tempCalc - 99.5) <0.01);
	REQUIRE(fabs(ChrgRateCalc - VALUE_NOTFOUND)<0.01);
	
}

TEST_CASE("Test from Console - Different order")
{
	float tempCalc, ChrgRateCalc;
	char *str;
	strcpy(str,"Chargerate:5.4A		Temperature:13.7degress");
    tempCalc = getParamValuefromConsoleCustom(str,TEMPERATURE);
    ChrgRateCalc = getParamValuefromConsoleCustom(str,CHARGERATE);
    
	REQUIRE(fabs(tempCalc - 13.7) <0.01);
	REQUIRE(fabs(ChrgRateCalc - 5.4)<0.01);
}

/* End of  Validating Get data from Console */

/* SMA function validation */
TEST_CASE("Valid data SMA check")
{
	float SMABuffer[5]={0}, SMASum;
	float smaCalc ;
	SMASum = 0;
	int pos = 0, range = 5;
	float dataArray[10] = {65.34,98.66,10.25,-1.36,85.6,45.6,17.5,-10.00,0,36.55};
	float SMABufferExpected[10] = {13.06,32.8,34.85,34.57,51.69,47.75,31.51,27.46,27.74,17.93};
	for(int i=0; i<10;i++)
	{
	    smaCalc =  movingAverageForRangeofValue(SMABuffer, &SMASum ,pos, range, dataArray[i]);
      	assert(fabs(smaCalc - SMABufferExpected[i]) <0.01);
		pos++;
       if (pos >= range)
        {
            pos = 0;
        }
	}

}

TEST_CASE("Valid data SMA check Range 1")
{
	float SMABuffer[5]={0}, SMASum;
	float smaCalc ;
	SMASum = 0;
	int pos = 0, range = 1;
	float dataArray[10] = {65.34,98.66,10.25,-1.36,85.6,45.6,17.5,-10.00,0,36.55};
	float SMABufferExpected[10] = {65.34,98.66,10.25,-1.36,85.6,45.6,17.5,-10.00,0,36.55};
	for(int i=0; i<10;i++)
	{
	    smaCalc =  movingAverageForRangeofValue(SMABuffer, &SMASum ,pos, range, dataArray[i]);
      	assert(fabs(smaCalc - SMABufferExpected[i]) <0.01);
		pos++;
       if (pos >= range)
        {
            pos = 0;
        }
	}
}

TEST_CASE("Valid data SMA check Range 0")
{
	float SMABuffer[5]={0}, SMASum;
	float smaCalc ;
	SMASum = 0;
	int pos = 0, range = 0;
	float dataArray[10] = {65.34,98.66,10.25,-1.36,85.6,45.6,17.5,-10.00,0,36.55};
	
	for(int i=0; i<10;i++)
	{
	    smaCalc =  movingAverageForRangeofValue(SMABuffer, &SMASum ,pos, range, dataArray[i]);
      	assert(fabs(smaCalc - INVALID_INPUT) <0.01);
		pos++;
       if (pos >= range)
        {
            pos = 0;
        }
	}
}

/*End of SMA function validation */

/*IsWithin Range function validation */
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

/*End of IsWithin Range function validation */

/*Validating Integrated test */
TEST_CASE("Integrated test ")
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
/*End of Validating Integrated test */	

/*Min and Max detection check */
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
            printf("\n %d Min :%f  Max:%f",i, TestMinOuputValue[i][j], TestMaxOuputValue[i][i]);
            printf("\n %d Min :%f  Max:%f",i, ExpectedMin1[j][i], ExpectedMax1[j][i]);
           
            assert(fabs(TestMinOuputValue[i][j] - ExpectedMin1[i][j]) < 0.02);
            assert(fabs(TestMaxOuputValue[i][j] - ExpectedMax1[i][j]) < 0.02);
            
        }
        
    }
}

/*Validating Update data  test function*/
TEST_CASE("Update function check -UpdateChargeRateCalcData")
{
		
	struct BatteryParamOutput_s BatteryParamInput[5]= {{2.365,25.65,10.23},
													   {71.35,9.14,-23.23},
													   {98.65,100.25,4.87},
													   {0.00,9563.23,-1.235},
													   {-3.754,0.00,123.45}};
		
	/*Reset Test count*/
	TestCount[TEMPERATURE] = 0;
	TestCount[CHARGERATE] = 0;
	
	/* Valid range data*/
	for(int i=0;i<5;i++)
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
	TestCount[CHARGERATE] = 0;
	
	/* Valid range data*/
	for(int i=0;i<5;i++)
	{
		UpdateChargeRateCalcData(BatteryParamInput[i]);
		assert(fabs(BatteryParamInput[i].SMA - TestSMAOuputValue[i][CHARGERATE]) < 0.02);
		assert(fabs(BatteryParamInput[i].minRxd - TestMinOuputValue[i][CHARGERATE]) < 0.02);
		assert(fabs(BatteryParamInput[i].maxRxd - TestMaxOuputValue[i][CHARGERATE]) < 0.02);
	}	
}
