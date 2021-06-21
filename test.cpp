#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "BMS_DataSender.h"
#include "stddef.h"
#include "string.h"

TEST_CASE("Test for valid temperature values")
{
  struct Battery_Parameter_s Temperature_s = {-40,80};

REQUIRE((Get_BMSTemperatue(Temperature_s,1)[0] >= -40) & (Get_BMSTemperatue(Temperature_s,1)[0] <= 80));
}


TEST_CASE("Test for valid ChargeRate values")
{
  struct Battery_Parameter_s ChargeRate_s = {0,30};

  REQUIRE((Get_BMSChargeRate(ChargeRate_s,1)[0] >= 0) & (Get_BMSChargeRate(ChargeRate_s,1)[0] <= 30));
}


TEST_CASE("Test for random number valid limits")
{
  float random_value = 0;
  float min = 10;
  float max = 50;
  random_value = RandomNumGenerator(min,max);
  REQUIRE(min <= random_value);
  REQUIRE(max >= random_value);
}


TEST_CASE("Test for Random number invalid limits")
{
  float min = 50;
  float max = 10;
  REQUIRE(RandomNumGenerator(min,max) == 32767);
}


TEST_CASE("Test for Successful Send Operation of BMS paramaters")
{
    struct Battery_Parameter_s Temperature_s = {-40,80};
    struct Battery_Parameter_s ChargeRate_s  = {10,30};
    int MAXPARAMNUM =10;
    
REQUIRE(BMS_SendData(Temperature_s,ChargeRate_s,MAXPARAMNUM) == SENTSUCCESSFULLY);
}

TEST_CASE("Test to print paramters on console")
{
    struct Battery_Parameter_s Temperature_s = {-40,80};
    struct Battery_Parameter_s ChargeRate_s  = {10,30};
    int MAXPARAMNUM =30;
    
REQUIRE(BMS_SendData(Temperature_s,ChargeRate_s,MAXPARAMNUM) == SENTSUCCESSFULLY);
}

