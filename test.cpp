#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "BMS_DataAcquisition.h"
#include "BMS_DataSender.h"
#include "stddef.h"
#include "string.h"


TEST_CASE("Test case to test the value within the Range")
{
  REQUIRE(isInRange(1,0,70)== 1);
}


TEST_CASE("Test case to test the value invaild Range")
{
  REQUIRE(isInRange(-100,-1,100)== 0);
}


TEST_CASE("Test for valid temperature values")
{
    struct Battery_Parameter_s Temperature_TC = {-40,80,255};
    
   REQUIRE(Get_BMSTemperatue(Temperature_TC)!= 255);
}


TEST_CASE("Test for valid SOC values")
{
  struct Battery_Parameter_s  ChargeRate_TC = {0,30,255};
    
  REQUIRE(Get_BMSChargeRate(ChargeRate_TC)!= 255);
}


TEST_CASE("Test for valid Random values")
{
  float random_value = 0;
  float min = 10;
  float max = 50;
  random_value = RandomNumGenerator(min,max);
  REQUIRE(min <= random_value);
  REQUIRE(max >= random_value);
}


TEST_CASE("Test for invalid Random values")
{
  
  float min = 50;
  float max = 10;
  REQUIRE(RandomNumGenerator(min,max) == 0);
}


TEST_CASE("Test for Send BMS data")
{
  REQUIRE(BMS_SendData() == SENTSUCCESSFULLY);
}


