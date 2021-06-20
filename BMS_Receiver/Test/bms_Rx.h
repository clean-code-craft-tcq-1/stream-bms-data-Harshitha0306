/************************************************************************************************************************/
/* This file contains the inclusions and definitions needed for BMS functions*/
/************************************************************************************************************************/

/******************** INCLUDE SECTION ***********************/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
/************************************************************/


/***************DEFINES section *****************************/
#define TEST_MODE 1

#define CHRGRATE_MIN 0.0
#define CHRGRATE_MAX 5.0
#define TEMP_MIN     20.0
#define TEMP_MAX     80.0

#define SMA_RANGE 5
#define MAXLENGTH_INPUTSTRING 100

#define VALUE_NOTFOUND 65532
#define INVALID_SMARANGE 65530
#define INVALID_VALUE 65535

/**************************************************************/


/***************GLOBAL variables section **********************/
enum BATTERYPARAM {TEMPERATURE, CHARGERATE, NUMOFPARAM};


struct BatteryParam_s
{
    char ParamName[20];
    float minValue;
    float maxValue;
};

struct BatteryParamOutput_s
{
    float SMA;
    float minRxd;
    float maxRxd;
};

extern struct BatteryParam_s BatteryParam[NUMOFPARAM];

extern int sig_caught ;

#if(TEST_MODE)
#define  TestSize 13
extern float TestSMAOuputValue[TestSize][NUMOFPARAM];
extern float TestMaxOuputValue[TestSize][NUMOFPARAM];
extern float TestMinOuputValue[TestSize][NUMOFPARAM];
extern int TestCount[NUMOFPARAM];
extern char strInput[TestSize][100];
#endif

/************************************************************/

/**************Function prototype section*********************/

float getParamValuefromConsoleCustom(char *scanLine, enum BATTERYPARAM batteryParam);

void BMSDataReceiverCalc();

typedef bool (*UpdateParamSMAData_funcPtr)(struct BatteryParamOutput_s BatteryParamEvaluated);

bool UpdateTemperatureCalcData (struct BatteryParamOutput_s BatteryParamEvaluated);

bool UpdateChargeRateCalcData (struct BatteryParamOutput_s BatteryParamEvaluated);

bool IsWithinRange(float value, float min, float max);

float MinimumOfTwoFloatNumbers(float value1, float value2);

float MaximumOfTwoFloatNumbers(float value1, float value2);

float movingAverageForRangeofValue(float *ptrArrNumbers, float *ptrSum, int param_id, int range, float nextNum);
/************************************************************/