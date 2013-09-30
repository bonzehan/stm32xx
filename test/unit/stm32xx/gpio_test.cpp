#include <stm32xx/gpio.hpp>
#include <CppUTest/TestHarness.h>

TEST_GROUP(foo)
{
};

TEST(foo, bar)
{
  using namespace stm32xx::gpio::ct;
  //CHECK_EQUAL(get_mask<_mask_holder<0x12345678ul> >::value, 0x12345678ul);
};

