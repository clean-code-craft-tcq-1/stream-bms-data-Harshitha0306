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
  REQUIRE(Get_BMSTemperatue()!= 255);
}


TEST_CASE("Test for valid SOC values")
{
  REQUIRE(Get_BMSChargeRate()!= 255);
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
  float random_value = 0;
  float min = 50;
  float max = 10;
  REQUIRE(RandomNumGenerator(min,max) == 0);
}


TEST_CASE("Test for Send BMS data")
{
  int MAXPRINT = 20;
  REQUIRE(BMS_SendData() == SENTSUCCESSFULLY);
}

TEST_CASE("Test for Send BMS data")
{
  REQUIRE(BMS_SendData() == SENTSUCCESSFULLY);
}
