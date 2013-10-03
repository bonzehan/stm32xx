#include <stm32xx/gpio.hpp>
#include <CppUTest/TestHarness.h>

#if defined STM32_FAMILY_STM32F10X
# define _HAVE_GPIO_CRL_REGISTER
# define _HAVE_GPIO_CRH_REGISTER
# define _HAVE_GPIO_MODE_AIN 
# define _HAVE_GPIO_MODE_IN_FLOATING
# define _HAVE_GPIO_MODE_IPD
# define _HAVE_GPIO_MODE_IPU
# define _HAVE_GPIO_MODE_Out_OD
# define _HAVE_GPIO_MODE_Out_PP
# define _HAVE_GPIO_MODE_AF_OD
# define _HAVE_GPIO_MODE_AF_PP
# define _HAVE_GPIO_SPEED_10MHz
# define _HAVE_GPIO_SPEED_2MHz
# define _HAVE_GPIO_SPEED_50MHz
#endif

#if defined STM32_FAMILY_STM32F4XX
#endif

TEST_GROUP(stm32xx__gpio__ct)
{
  template <GPIOMode_TypeDef _mode> 
  struct check_crl_cnf_bits
  {
    static void apply()
    {
      using namespace stm32xx::gpio::ct;
      CHECK_EQUAL(((_mode & 0x0Cul) << 0x00), (crl_cnf_bits<GPIO_Pin_0,  _mode>::value));
      CHECK_EQUAL(((_mode & 0x0Cul) << 0x04), (crl_cnf_bits<GPIO_Pin_1,  _mode>::value));
      CHECK_EQUAL(((_mode & 0x0Cul) << 0x08), (crl_cnf_bits<GPIO_Pin_2,  _mode>::value));
      CHECK_EQUAL(((_mode & 0x0Cul) << 0x0C), (crl_cnf_bits<GPIO_Pin_3,  _mode>::value));
      CHECK_EQUAL(((_mode & 0x0Cul) << 0x10), (crl_cnf_bits<GPIO_Pin_4,  _mode>::value));
      CHECK_EQUAL(((_mode & 0x0Cul) << 0x14), (crl_cnf_bits<GPIO_Pin_5,  _mode>::value));
      CHECK_EQUAL(((_mode & 0x0Cul) << 0x18), (crl_cnf_bits<GPIO_Pin_6,  _mode>::value));
      CHECK_EQUAL(((_mode & 0x0Cul) << 0x1C), (crl_cnf_bits<GPIO_Pin_7,  _mode>::value));
      CHECK_EQUAL(0ul,                        (crl_cnf_bits<GPIO_Pin_8,  _mode>::value));
      CHECK_EQUAL(0ul,                        (crl_cnf_bits<GPIO_Pin_9,  _mode>::value));
      CHECK_EQUAL(0ul,                        (crl_cnf_bits<GPIO_Pin_10, _mode>::value));
      CHECK_EQUAL(0ul,                        (crl_cnf_bits<GPIO_Pin_11, _mode>::value));
      CHECK_EQUAL(0ul,                        (crl_cnf_bits<GPIO_Pin_12, _mode>::value));
      CHECK_EQUAL(0ul,                        (crl_cnf_bits<GPIO_Pin_13, _mode>::value));
      CHECK_EQUAL(0ul,                        (crl_cnf_bits<GPIO_Pin_14, _mode>::value));
      CHECK_EQUAL(0ul,                        (crl_cnf_bits<GPIO_Pin_15, _mode>::value));
    }
  };
  
  template <GPIOMode_TypeDef _mode> 
  struct check_crh_cnf_bits
  {
    static void apply()
    {
      using namespace stm32xx::gpio::ct;
      CHECK_EQUAL(0ul,                        (crh_cnf_bits<GPIO_Pin_0,  _mode>::value));
      CHECK_EQUAL(0ul,                        (crh_cnf_bits<GPIO_Pin_1,  _mode>::value));
      CHECK_EQUAL(0ul,                        (crh_cnf_bits<GPIO_Pin_2,  _mode>::value));
      CHECK_EQUAL(0ul,                        (crh_cnf_bits<GPIO_Pin_3,  _mode>::value));
      CHECK_EQUAL(0ul,                        (crh_cnf_bits<GPIO_Pin_4,  _mode>::value));
      CHECK_EQUAL(0ul,                        (crh_cnf_bits<GPIO_Pin_5,  _mode>::value));
      CHECK_EQUAL(0ul,                        (crh_cnf_bits<GPIO_Pin_6,  _mode>::value));
      CHECK_EQUAL(0ul,                        (crh_cnf_bits<GPIO_Pin_7,  _mode>::value));
      CHECK_EQUAL(((_mode & 0x0Cul) << 0x00), (crh_cnf_bits<GPIO_Pin_8,  _mode>::value));
      CHECK_EQUAL(((_mode & 0x0Cul) << 0x04), (crh_cnf_bits<GPIO_Pin_9,  _mode>::value));
      CHECK_EQUAL(((_mode & 0x0Cul) << 0x08), (crh_cnf_bits<GPIO_Pin_10, _mode>::value));
      CHECK_EQUAL(((_mode & 0x0Cul) << 0x0C), (crh_cnf_bits<GPIO_Pin_11, _mode>::value));
      CHECK_EQUAL(((_mode & 0x0Cul) << 0x10), (crh_cnf_bits<GPIO_Pin_12, _mode>::value));
      CHECK_EQUAL(((_mode & 0x0Cul) << 0x14), (crh_cnf_bits<GPIO_Pin_13, _mode>::value));
      CHECK_EQUAL(((_mode & 0x0Cul) << 0x18), (crh_cnf_bits<GPIO_Pin_14, _mode>::value));
      CHECK_EQUAL(((_mode & 0x0Cul) << 0x1C), (crh_cnf_bits<GPIO_Pin_15, _mode>::value));
    }
  };

  static void 
  check_crl_cnf_mask()
  {
      using namespace stm32xx::gpio::ct;
      CHECK_EQUAL((0x0Cul << 0x00), (crl_cnf_mask<GPIO_Pin_0 >::value));
      CHECK_EQUAL((0x0Cul << 0x04), (crl_cnf_mask<GPIO_Pin_1 >::value));
      CHECK_EQUAL((0x0Cul << 0x08), (crl_cnf_mask<GPIO_Pin_2 >::value));
      CHECK_EQUAL((0x0Cul << 0x0C), (crl_cnf_mask<GPIO_Pin_3 >::value));
      CHECK_EQUAL((0x0Cul << 0x10), (crl_cnf_mask<GPIO_Pin_4 >::value));
      CHECK_EQUAL((0x0Cul << 0x14), (crl_cnf_mask<GPIO_Pin_5 >::value));
      CHECK_EQUAL((0x0Cul << 0x18), (crl_cnf_mask<GPIO_Pin_6 >::value));
      CHECK_EQUAL((0x0Cul << 0x1C), (crl_cnf_mask<GPIO_Pin_7 >::value));
      CHECK_EQUAL(0ul,              (crl_cnf_mask<GPIO_Pin_8 >::value));
      CHECK_EQUAL(0ul,              (crl_cnf_mask<GPIO_Pin_9 >::value));
      CHECK_EQUAL(0ul,              (crl_cnf_mask<GPIO_Pin_10>::value));
      CHECK_EQUAL(0ul,              (crl_cnf_mask<GPIO_Pin_11>::value));
      CHECK_EQUAL(0ul,              (crl_cnf_mask<GPIO_Pin_12>::value));
      CHECK_EQUAL(0ul,              (crl_cnf_mask<GPIO_Pin_13>::value));
      CHECK_EQUAL(0ul,              (crl_cnf_mask<GPIO_Pin_14>::value));
      CHECK_EQUAL(0ul,              (crl_cnf_mask<GPIO_Pin_15>::value));
  }

  static void 
  check_crh_cnf_mask()
  {
      using namespace stm32xx::gpio::ct;
      CHECK_EQUAL(0ul,              (crh_cnf_mask<GPIO_Pin_0 >::value));
      CHECK_EQUAL(0ul,              (crh_cnf_mask<GPIO_Pin_1 >::value));
      CHECK_EQUAL(0ul,              (crh_cnf_mask<GPIO_Pin_2 >::value));
      CHECK_EQUAL(0ul,              (crh_cnf_mask<GPIO_Pin_3 >::value));
      CHECK_EQUAL(0ul,              (crh_cnf_mask<GPIO_Pin_4 >::value));
      CHECK_EQUAL(0ul,              (crh_cnf_mask<GPIO_Pin_5 >::value));
      CHECK_EQUAL(0ul,              (crh_cnf_mask<GPIO_Pin_6 >::value));
      CHECK_EQUAL(0ul,              (crh_cnf_mask<GPIO_Pin_7 >::value));
      CHECK_EQUAL((0x0Cul << 0x00), (crh_cnf_mask<GPIO_Pin_8 >::value));
      CHECK_EQUAL((0x0Cul << 0x04), (crh_cnf_mask<GPIO_Pin_9 >::value));
      CHECK_EQUAL((0x0Cul << 0x08), (crh_cnf_mask<GPIO_Pin_10>::value));
      CHECK_EQUAL((0x0Cul << 0x0C), (crh_cnf_mask<GPIO_Pin_11>::value));
      CHECK_EQUAL((0x0Cul << 0x10), (crh_cnf_mask<GPIO_Pin_12>::value));
      CHECK_EQUAL((0x0Cul << 0x14), (crh_cnf_mask<GPIO_Pin_13>::value));
      CHECK_EQUAL((0x0Cul << 0x18), (crh_cnf_mask<GPIO_Pin_14>::value));
      CHECK_EQUAL((0x0Cul << 0x1C), (crh_cnf_mask<GPIO_Pin_15>::value));
  }

  template <GPIOSpeed_TypeDef _speed> 
  struct check_crl_mode_bits
  {
    static void apply()
    {
      using namespace stm32xx::gpio::ct;
      CHECK_EQUAL(((_speed & 0x03ul) << 0x00), (crl_mode_bits<GPIO_Pin_0,  _speed>::value));
      CHECK_EQUAL(((_speed & 0x03ul) << 0x04), (crl_mode_bits<GPIO_Pin_1,  _speed>::value));
      CHECK_EQUAL(((_speed & 0x03ul) << 0x08), (crl_mode_bits<GPIO_Pin_2,  _speed>::value));
      CHECK_EQUAL(((_speed & 0x03ul) << 0x0C), (crl_mode_bits<GPIO_Pin_3,  _speed>::value));
      CHECK_EQUAL(((_speed & 0x03ul) << 0x10), (crl_mode_bits<GPIO_Pin_4,  _speed>::value));
      CHECK_EQUAL(((_speed & 0x03ul) << 0x14), (crl_mode_bits<GPIO_Pin_5,  _speed>::value));
      CHECK_EQUAL(((_speed & 0x03ul) << 0x18), (crl_mode_bits<GPIO_Pin_6,  _speed>::value));
      CHECK_EQUAL(((_speed & 0x03ul) << 0x1C), (crl_mode_bits<GPIO_Pin_7,  _speed>::value));
      CHECK_EQUAL(0ul,                         (crl_mode_bits<GPIO_Pin_8,  _speed>::value));
      CHECK_EQUAL(0ul,                         (crl_mode_bits<GPIO_Pin_9,  _speed>::value));
      CHECK_EQUAL(0ul,                         (crl_mode_bits<GPIO_Pin_10, _speed>::value));
      CHECK_EQUAL(0ul,                         (crl_mode_bits<GPIO_Pin_11, _speed>::value));
      CHECK_EQUAL(0ul,                         (crl_mode_bits<GPIO_Pin_12, _speed>::value));
      CHECK_EQUAL(0ul,                         (crl_mode_bits<GPIO_Pin_13, _speed>::value));
      CHECK_EQUAL(0ul,                         (crl_mode_bits<GPIO_Pin_14, _speed>::value));
      CHECK_EQUAL(0ul,                         (crl_mode_bits<GPIO_Pin_15, _speed>::value));
    }
  };
  
  template <GPIOSpeed_TypeDef _speed> 
  struct check_crh_mode_bits
  {
    static void apply()
    {
      using namespace stm32xx::gpio::ct;
      CHECK_EQUAL(0ul,                         (crh_mode_bits<GPIO_Pin_0,  _speed>::value));
      CHECK_EQUAL(0ul,                         (crh_mode_bits<GPIO_Pin_1,  _speed>::value));
      CHECK_EQUAL(0ul,                         (crh_mode_bits<GPIO_Pin_2,  _speed>::value));
      CHECK_EQUAL(0ul,                         (crh_mode_bits<GPIO_Pin_3,  _speed>::value));
      CHECK_EQUAL(0ul,                         (crh_mode_bits<GPIO_Pin_4,  _speed>::value));
      CHECK_EQUAL(0ul,                         (crh_mode_bits<GPIO_Pin_5,  _speed>::value));
      CHECK_EQUAL(0ul,                         (crh_mode_bits<GPIO_Pin_6,  _speed>::value));
      CHECK_EQUAL(0ul,                         (crh_mode_bits<GPIO_Pin_7,  _speed>::value));
      CHECK_EQUAL(((_speed & 0x03ul) << 0x00), (crh_mode_bits<GPIO_Pin_8,  _speed>::value));
      CHECK_EQUAL(((_speed & 0x03ul) << 0x04), (crh_mode_bits<GPIO_Pin_9,  _speed>::value));
      CHECK_EQUAL(((_speed & 0x03ul) << 0x08), (crh_mode_bits<GPIO_Pin_10, _speed>::value));
      CHECK_EQUAL(((_speed & 0x03ul) << 0x0C), (crh_mode_bits<GPIO_Pin_11, _speed>::value));
      CHECK_EQUAL(((_speed & 0x03ul) << 0x10), (crh_mode_bits<GPIO_Pin_12, _speed>::value));
      CHECK_EQUAL(((_speed & 0x03ul) << 0x14), (crh_mode_bits<GPIO_Pin_13, _speed>::value));
      CHECK_EQUAL(((_speed & 0x03ul) << 0x18), (crh_mode_bits<GPIO_Pin_14, _speed>::value));
      CHECK_EQUAL(((_speed & 0x03ul) << 0x1C), (crh_mode_bits<GPIO_Pin_15, _speed>::value));
    }
  };

  static void 
  check_crl_mode_mask()
  {
      using namespace stm32xx::gpio::ct;
      CHECK_EQUAL((0x03ul << 0x00), (crl_mode_mask<GPIO_Pin_0 >::value));
      CHECK_EQUAL((0x03ul << 0x04), (crl_mode_mask<GPIO_Pin_1 >::value));
      CHECK_EQUAL((0x03ul << 0x08), (crl_mode_mask<GPIO_Pin_2 >::value));
      CHECK_EQUAL((0x03ul << 0x0C), (crl_mode_mask<GPIO_Pin_3 >::value));
      CHECK_EQUAL((0x03ul << 0x10), (crl_mode_mask<GPIO_Pin_4 >::value));
      CHECK_EQUAL((0x03ul << 0x14), (crl_mode_mask<GPIO_Pin_5 >::value));
      CHECK_EQUAL((0x03ul << 0x18), (crl_mode_mask<GPIO_Pin_6 >::value));
      CHECK_EQUAL((0x03ul << 0x1C), (crl_mode_mask<GPIO_Pin_7 >::value));
      CHECK_EQUAL(0ul,              (crl_mode_mask<GPIO_Pin_8 >::value));
      CHECK_EQUAL(0ul,              (crl_mode_mask<GPIO_Pin_9 >::value));
      CHECK_EQUAL(0ul,              (crl_mode_mask<GPIO_Pin_10>::value));
      CHECK_EQUAL(0ul,              (crl_mode_mask<GPIO_Pin_11>::value));
      CHECK_EQUAL(0ul,              (crl_mode_mask<GPIO_Pin_12>::value));
      CHECK_EQUAL(0ul,              (crl_mode_mask<GPIO_Pin_13>::value));
      CHECK_EQUAL(0ul,              (crl_mode_mask<GPIO_Pin_14>::value));
      CHECK_EQUAL(0ul,              (crl_mode_mask<GPIO_Pin_15>::value));
  }

  static void 
  check_crh_mode_mask()
  {
      using namespace stm32xx::gpio::ct;
      CHECK_EQUAL(0ul,              (crh_mode_mask<GPIO_Pin_0 >::value));
      CHECK_EQUAL(0ul,              (crh_mode_mask<GPIO_Pin_1 >::value));
      CHECK_EQUAL(0ul,              (crh_mode_mask<GPIO_Pin_2 >::value));
      CHECK_EQUAL(0ul,              (crh_mode_mask<GPIO_Pin_3 >::value));
      CHECK_EQUAL(0ul,              (crh_mode_mask<GPIO_Pin_4 >::value));
      CHECK_EQUAL(0ul,              (crh_mode_mask<GPIO_Pin_5 >::value));
      CHECK_EQUAL(0ul,              (crh_mode_mask<GPIO_Pin_6 >::value));
      CHECK_EQUAL(0ul,              (crh_mode_mask<GPIO_Pin_7 >::value));
      CHECK_EQUAL((0x03ul << 0x00), (crh_mode_mask<GPIO_Pin_8 >::value));
      CHECK_EQUAL((0x03ul << 0x04), (crh_mode_mask<GPIO_Pin_9 >::value));
      CHECK_EQUAL((0x03ul << 0x08), (crh_mode_mask<GPIO_Pin_10>::value));
      CHECK_EQUAL((0x03ul << 0x0C), (crh_mode_mask<GPIO_Pin_11>::value));
      CHECK_EQUAL((0x03ul << 0x10), (crh_mode_mask<GPIO_Pin_12>::value));
      CHECK_EQUAL((0x03ul << 0x14), (crh_mode_mask<GPIO_Pin_13>::value));
      CHECK_EQUAL((0x03ul << 0x18), (crh_mode_mask<GPIO_Pin_14>::value));
      CHECK_EQUAL((0x03ul << 0x1C), (crh_mode_mask<GPIO_Pin_15>::value));
  }
  template <GPIOMode_TypeDef _mode, GPIOSpeed_TypeDef _speed>
    struct check_crl_bits
    {
      static void
      apply()
      {
        using namespace stm32xx::gpio::ct;
        constexpr uint32_t _ms = (_mode & 0x0Cul)|(_speed & 0x03ul);
        CHECK_EQUAL((_ms << 0x00), (crl_bits<GPIO_Pin_0,  _mode,_speed>::value));
        CHECK_EQUAL((_ms << 0x04), (crl_bits<GPIO_Pin_1,  _mode,_speed>::value));
        CHECK_EQUAL((_ms << 0x08), (crl_bits<GPIO_Pin_2,  _mode,_speed>::value));
        CHECK_EQUAL((_ms << 0x0C), (crl_bits<GPIO_Pin_3,  _mode,_speed>::value));
        CHECK_EQUAL((_ms << 0x10), (crl_bits<GPIO_Pin_4,  _mode,_speed>::value));
        CHECK_EQUAL((_ms << 0x14), (crl_bits<GPIO_Pin_5,  _mode,_speed>::value));
        CHECK_EQUAL((_ms << 0x18), (crl_bits<GPIO_Pin_6,  _mode,_speed>::value));
        CHECK_EQUAL((_ms << 0x1C), (crl_bits<GPIO_Pin_7,  _mode,_speed>::value));
        CHECK_EQUAL(0ul,           (crl_bits<GPIO_Pin_8,  _mode,_speed>::value));
        CHECK_EQUAL(0ul,           (crl_bits<GPIO_Pin_9,  _mode,_speed>::value));
        CHECK_EQUAL(0ul,           (crl_bits<GPIO_Pin_10, _mode,_speed>::value));
        CHECK_EQUAL(0ul,           (crl_bits<GPIO_Pin_11, _mode,_speed>::value));
        CHECK_EQUAL(0ul,           (crl_bits<GPIO_Pin_12, _mode,_speed>::value));
        CHECK_EQUAL(0ul,           (crl_bits<GPIO_Pin_13, _mode,_speed>::value));
        CHECK_EQUAL(0ul,           (crl_bits<GPIO_Pin_14, _mode,_speed>::value));
        CHECK_EQUAL(0ul,           (crl_bits<GPIO_Pin_15, _mode,_speed>::value));
      }
    };
  template <GPIOMode_TypeDef _mode, GPIOSpeed_TypeDef _speed>
    struct check_crh_bits
    {
      static void
      apply()
      {
        using namespace stm32xx::gpio::ct;
        constexpr uint32_t _ms = (_mode & 0x0Cul)|(_speed & 0x03ul);
        CHECK_EQUAL(0ul,           (crh_bits<GPIO_Pin_0,  _mode,_speed>::value));
        CHECK_EQUAL(0ul,           (crh_bits<GPIO_Pin_1,  _mode,_speed>::value));
        CHECK_EQUAL(0ul,           (crh_bits<GPIO_Pin_2,  _mode,_speed>::value));
        CHECK_EQUAL(0ul,           (crh_bits<GPIO_Pin_3,  _mode,_speed>::value));
        CHECK_EQUAL(0ul,           (crh_bits<GPIO_Pin_4,  _mode,_speed>::value));
        CHECK_EQUAL(0ul,           (crh_bits<GPIO_Pin_5,  _mode,_speed>::value));
        CHECK_EQUAL(0ul,           (crh_bits<GPIO_Pin_6,  _mode,_speed>::value));
        CHECK_EQUAL(0ul,           (crh_bits<GPIO_Pin_7,  _mode,_speed>::value));
        CHECK_EQUAL((_ms << 0x00), (crh_bits<GPIO_Pin_8,  _mode,_speed>::value));
        CHECK_EQUAL((_ms << 0x04), (crh_bits<GPIO_Pin_9,  _mode,_speed>::value));
        CHECK_EQUAL((_ms << 0x08), (crh_bits<GPIO_Pin_10, _mode,_speed>::value));
        CHECK_EQUAL((_ms << 0x0C), (crh_bits<GPIO_Pin_11, _mode,_speed>::value));
        CHECK_EQUAL((_ms << 0x10), (crh_bits<GPIO_Pin_12, _mode,_speed>::value));
        CHECK_EQUAL((_ms << 0x14), (crh_bits<GPIO_Pin_13, _mode,_speed>::value));
        CHECK_EQUAL((_ms << 0x18), (crh_bits<GPIO_Pin_14, _mode,_speed>::value));
        CHECK_EQUAL((_ms << 0x1C), (crh_bits<GPIO_Pin_15, _mode,_speed>::value));
      }
    };
  static void 
  check_crl_mask()
  {
      using namespace stm32xx::gpio::ct;
      CHECK_EQUAL((0x0Ful << 0x00), (crl_mask<GPIO_Pin_0 >::value));
      CHECK_EQUAL((0x0Ful << 0x04), (crl_mask<GPIO_Pin_1 >::value));
      CHECK_EQUAL((0x0Ful << 0x08), (crl_mask<GPIO_Pin_2 >::value));
      CHECK_EQUAL((0x0Ful << 0x0C), (crl_mask<GPIO_Pin_3 >::value));
      CHECK_EQUAL((0x0Ful << 0x10), (crl_mask<GPIO_Pin_4 >::value));
      CHECK_EQUAL((0x0Ful << 0x14), (crl_mask<GPIO_Pin_5 >::value));
      CHECK_EQUAL((0x0Ful << 0x18), (crl_mask<GPIO_Pin_6 >::value));
      CHECK_EQUAL((0x0Ful << 0x1C), (crl_mask<GPIO_Pin_7 >::value));
      CHECK_EQUAL(0ul,              (crl_mask<GPIO_Pin_8 >::value));
      CHECK_EQUAL(0ul,              (crl_mask<GPIO_Pin_9 >::value));
      CHECK_EQUAL(0ul,              (crl_mask<GPIO_Pin_10>::value));
      CHECK_EQUAL(0ul,              (crl_mask<GPIO_Pin_11>::value));
      CHECK_EQUAL(0ul,              (crl_mask<GPIO_Pin_12>::value));
      CHECK_EQUAL(0ul,              (crl_mask<GPIO_Pin_13>::value));
      CHECK_EQUAL(0ul,              (crl_mask<GPIO_Pin_14>::value));
      CHECK_EQUAL(0ul,              (crl_mask<GPIO_Pin_15>::value));
  }

  static void 
  check_crh_mask()
  {
      using namespace stm32xx::gpio::ct;
      CHECK_EQUAL(0ul,              (crh_mask<GPIO_Pin_0 >::value));
      CHECK_EQUAL(0ul,              (crh_mask<GPIO_Pin_1 >::value));
      CHECK_EQUAL(0ul,              (crh_mask<GPIO_Pin_2 >::value));
      CHECK_EQUAL(0ul,              (crh_mask<GPIO_Pin_3 >::value));
      CHECK_EQUAL(0ul,              (crh_mask<GPIO_Pin_4 >::value));
      CHECK_EQUAL(0ul,              (crh_mask<GPIO_Pin_5 >::value));
      CHECK_EQUAL(0ul,              (crh_mask<GPIO_Pin_6 >::value));
      CHECK_EQUAL(0ul,              (crh_mask<GPIO_Pin_7 >::value));
      CHECK_EQUAL((0x0Ful << 0x00), (crh_mask<GPIO_Pin_8 >::value));
      CHECK_EQUAL((0x0Ful << 0x04), (crh_mask<GPIO_Pin_9 >::value));
      CHECK_EQUAL((0x0Ful << 0x08), (crh_mask<GPIO_Pin_10>::value));
      CHECK_EQUAL((0x0Ful << 0x0C), (crh_mask<GPIO_Pin_11>::value));
      CHECK_EQUAL((0x0Ful << 0x10), (crh_mask<GPIO_Pin_12>::value));
      CHECK_EQUAL((0x0Ful << 0x14), (crh_mask<GPIO_Pin_13>::value));
      CHECK_EQUAL((0x0Ful << 0x18), (crh_mask<GPIO_Pin_14>::value));
      CHECK_EQUAL((0x0Ful << 0x1C), (crh_mask<GPIO_Pin_15>::value));
  }
};

/*
 * CRL
 */
#if defined _HAVE_GPIO_CRL_REGISTER
TEST(stm32xx__gpio__ct, crl_cnf_mask)
{
  check_crl_cnf_mask();
};
TEST(stm32xx__gpio__ct, crl_mode_mask)
{
  check_crl_mode_mask();
};
TEST(stm32xx__gpio__ct, crl_mask)
{
  check_crl_mask();
};

# if defined _HAVE_GPIO_MODE_AIN
TEST(stm32xx__gpio__ct, crl_cnf_bits__gpio_mode_ain)
{
  check_crl_cnf_bits<GPIO_Mode_AIN>::apply();
};
TEST(stm32xx__gpio__ct, crl_bits__gpio_mode_ain)
{
  /* This tests meta-function call with default parameter in action */
  using namespace stm32xx::gpio::ct;
  CHECK_EQUAL(GPIO_Mode_AIN, (crl_bits<GPIO_Pin_0, GPIO_Mode_AIN>::value));
};
# endif

# if defined _HAVE_GPIO_MODE_IN_FLOATING
TEST(stm32xx__gpio__ct, crl_cnf_bits__gpio_mode_in_floating)
{
  check_crl_cnf_bits<GPIO_Mode_IN_FLOATING>::apply();
};
# endif

# if defined _HAVE_GPIO_MODE_IPD
TEST(stm32xx__gpio__ct, crl_cnf_bits__gpio_mode_ipd)
{
  check_crl_cnf_bits<GPIO_Mode_IPD>::apply();
};
# endif

# if defined _HAVE_GPIO_MODE_IPU
TEST(stm32xx__gpio__ct, crl_cnf_bits__gpio_mode_ipu)
{
  check_crl_cnf_bits<GPIO_Mode_IPU>::apply();
};
# endif

# if defined _HAVE_GPIO_MODE_Out_OD
TEST(stm32xx__gpio__ct, crl_cnf_bits__gpio_mode_out_od)
{
  check_crl_cnf_bits<GPIO_Mode_Out_OD>::apply();
};
#   if defined _HAVE_GPIO_SPEED_10MHz
TEST(stm32xx__gpio__ct, crl_bits__gpio_mode_od__speed_10MHz)
{
  check_crl_bits<GPIO_Mode_Out_OD, GPIO_Speed_10MHz>::apply();
};
#   endif
#   if defined _HAVE_GPIO_SPEED_2MHz
TEST(stm32xx__gpio__ct, crl_bits__gpio_mode_od__speed_2MHz)
{
  check_crl_bits<GPIO_Mode_Out_OD, GPIO_Speed_2MHz>::apply();
};
#   endif
#   if defined _HAVE_GPIO_SPEED_50MHz
TEST(stm32xx__gpio__ct, crl_bits__gpio_mode_od__speed_50MHz)
{
  check_crl_bits<GPIO_Mode_Out_OD, GPIO_Speed_50MHz>::apply();
};
#   endif
# endif

# if defined _HAVE_GPIO_MODE_Out_PP
TEST(stm32xx__gpio__ct, crl_cnf_bits__gpio_mode_out_pp)
{
  check_crl_cnf_bits<GPIO_Mode_Out_PP>::apply();
};
#   if defined _HAVE_GPIO_SPEED_10MHz
TEST(stm32xx__gpio__ct, crl_bits__gpio_mode_out_pp__speed_10MHz)
{
  check_crl_bits<GPIO_Mode_Out_PP, GPIO_Speed_10MHz>::apply();
};
#   endif
#   if defined _HAVE_GPIO_SPEED_2MHz
TEST(stm32xx__gpio__ct, crl_bits__gpio_mode_out_pp__speed_2MHz)
{
  check_crl_bits<GPIO_Mode_Out_PP, GPIO_Speed_2MHz>::apply();
};
#   endif
#   if defined _HAVE_GPIO_SPEED_50MHz
TEST(stm32xx__gpio__ct, crl_bits__gpio_mode_out_pp__speed_50MHz)
{
  check_crl_bits<GPIO_Mode_Out_PP, GPIO_Speed_50MHz>::apply();
};
#   endif
# endif

# if defined _HAVE_GPIO_MODE_AF_OD
TEST(stm32xx__gpio__ct, crl_cnf_bits__gpio_mode_af_od)
{
  check_crl_cnf_bits<GPIO_Mode_AF_OD>::apply();
};
#   if defined _HAVE_GPIO_SPEED_10MHz
TEST(stm32xx__gpio__ct, crl_bits__gpio_mode_af_od__speed_10MHz)
{
  check_crl_bits<GPIO_Mode_AF_OD, GPIO_Speed_10MHz>::apply();
};
#   endif
#   if defined _HAVE_GPIO_SPEED_2MHz
TEST(stm32xx__gpio__ct, crl_bits__gpio_mode_af_od__speed_2MHz)
{
  check_crl_bits<GPIO_Mode_AF_OD, GPIO_Speed_2MHz>::apply();
};
#   endif
#   if defined _HAVE_GPIO_SPEED_50MHz
TEST(stm32xx__gpio__ct, crl_bits__gpio_mode_af_od__speed_50MHz)
{
  check_crl_bits<GPIO_Mode_AF_OD, GPIO_Speed_50MHz>::apply();
};
#   endif
# endif

# if defined _HAVE_GPIO_MODE_AF_PP
TEST(stm32xx__gpio__ct, crl_cnf_bits__gpio_mode_af_pp)
{
  check_crl_cnf_bits<GPIO_Mode_AF_PP>::apply();
};
#   if defined _HAVE_GPIO_SPEED_10MHz
TEST(stm32xx__gpio__ct, crl_bits__gpio_mode_af_pp__speed_10MHz)
{
  check_crl_bits<GPIO_Mode_AF_PP, GPIO_Speed_10MHz>::apply();
};
#   endif
#   if defined _HAVE_GPIO_SPEED_2MHz
TEST(stm32xx__gpio__ct, crl_bits__gpio_mode_af_pp__speed_2MHz)
{
  check_crl_bits<GPIO_Mode_AF_PP, GPIO_Speed_2MHz>::apply();
};
#   endif
#   if defined _HAVE_GPIO_SPEED_50MHz
TEST(stm32xx__gpio__ct, crl_bits__gpio_mode_af_pp__speed_50MHz)
{
  check_crl_bits<GPIO_Mode_AF_PP, GPIO_Speed_50MHz>::apply();
};
#   endif
# endif

# if defined _HAVE_GPIO_SPEED_10MHz
TEST(stm32xx__gpio__ct, crl_mode_bits__gpio_speed_10MHz)
{
  check_crl_mode_bits<GPIO_Speed_10MHz>::apply();
}
# endif

# if defined _HAVE_GPIO_SPEED_2MHz
TEST(stm32xx__gpio__ct, crl_mode_bits__gpio_speed_2MHz)
{
  check_crl_mode_bits<GPIO_Speed_2MHz>::apply();
}
# endif

# if defined _HAVE_GPIO_SPEED_50MHz
TEST(stm32xx__gpio__ct, crl_mode_bits__gpio_speed_50MHz)
{
  check_crl_mode_bits<GPIO_Speed_50MHz>::apply();
}
# endif
#endif /* _HAVE_GPIO_CRL_REGISTER */


/*
 * CRH
 */
#if defined _HAVE_GPIO_CRH_REGISTER
TEST(stm32xx__gpio__ct, crh_cnf_mask)
{
  check_crh_cnf_mask();
};
TEST(stm32xx__gpio__ct, crh_mode_mask)
{
  check_crh_mode_mask();
};
TEST(stm32xx__gpio__ct, crh_mask)
{
  check_crh_mask();
};

# if defined _HAVE_GPIO_MODE_AIN
TEST(stm32xx__gpio__ct, crh_cnf_bits__gpio_mode_ain)
{
  check_crh_cnf_bits<GPIO_Mode_AIN>::apply();
};
TEST(stm32xx__gpio__ct, crh_bits__gpio_mode_ain)
{
  /* This tests meta-function call with default parameter in action */
  using namespace stm32xx::gpio::ct;
  CHECK_EQUAL(GPIO_Mode_AIN, (crh_bits<GPIO_Pin_0, GPIO_Mode_AIN>::value));
};
# endif

# if defined _HAVE_GPIO_MODE_IN_FLOATING
TEST(stm32xx__gpio__ct, crh_cnf_bits__gpio_mode_in_floating)
{
  check_crh_cnf_bits<GPIO_Mode_IN_FLOATING>::apply();
};
# endif

# if defined _HAVE_GPIO_MODE_IPD
TEST(stm32xx__gpio__ct, crh_cnf_bits__gpio_mode_ipd)
{
  check_crh_cnf_bits<GPIO_Mode_IPD>::apply();
};
# endif

# if defined _HAVE_GPIO_MODE_IPU
TEST(stm32xx__gpio__ct, crh_cnf_bits__gpio_mode_ipu)
{
  check_crh_cnf_bits<GPIO_Mode_IPU>::apply();
};
# endif

# if defined _HAVE_GPIO_MODE_Out_OD
TEST(stm32xx__gpio__ct, crh_cnf_bits__gpio_mode_out_od)
{
  check_crh_cnf_bits<GPIO_Mode_Out_OD>::apply();
};
#   if defined _HAVE_GPIO_SPEED_10MHz
TEST(stm32xx__gpio__ct, crh_bits__gpio_mode_od__speed_10MHz)
{
  check_crh_bits<GPIO_Mode_Out_OD, GPIO_Speed_10MHz>::apply();
};
#   endif
#   if defined _HAVE_GPIO_SPEED_2MHz
TEST(stm32xx__gpio__ct, crh_bits__gpio_mode_od__speed_2MHz)
{
  check_crh_bits<GPIO_Mode_Out_OD, GPIO_Speed_2MHz>::apply();
};
#   endif
#   if defined _HAVE_GPIO_SPEED_50MHz
TEST(stm32xx__gpio__ct, crh_bits__gpio_mode_od__speed_50MHz)
{
  check_crh_bits<GPIO_Mode_Out_OD, GPIO_Speed_50MHz>::apply();
};
#   endif
# endif

# if defined _HAVE_GPIO_MODE_Out_PP
TEST(stm32xx__gpio__ct, crh_cnf_bits__gpio_mode_out_pp)
{
  check_crh_cnf_bits<GPIO_Mode_Out_PP>::apply();
};
#   if defined _HAVE_GPIO_SPEED_10MHz
TEST(stm32xx__gpio__ct, crh_bits__gpio_mode_out_pp__speed_10MHz)
{
  check_crh_bits<GPIO_Mode_Out_PP, GPIO_Speed_10MHz>::apply();
};
#   endif
#   if defined _HAVE_GPIO_SPEED_2MHz
TEST(stm32xx__gpio__ct, crh_bits__gpio_mode_out_pp__speed_2MHz)
{
  check_crh_bits<GPIO_Mode_Out_PP, GPIO_Speed_2MHz>::apply();
};
#   endif
#   if defined _HAVE_GPIO_SPEED_50MHz
TEST(stm32xx__gpio__ct, crh_bits__gpio_mode_out_pp__speed_50MHz)
{
  check_crh_bits<GPIO_Mode_Out_PP, GPIO_Speed_50MHz>::apply();
};
#   endif
# endif

# if defined _HAVE_GPIO_MODE_AF_OD
TEST(stm32xx__gpio__ct, crh_cnf_bits__gpio_mode_af_od)
{
  check_crh_cnf_bits<GPIO_Mode_AF_OD>::apply();
};
#   if defined _HAVE_GPIO_SPEED_10MHz
TEST(stm32xx__gpio__ct, crh_bits__gpio_mode_af_od__speed_10MHz)
{
  check_crh_bits<GPIO_Mode_AF_OD, GPIO_Speed_10MHz>::apply();
};
#   endif
#   if defined _HAVE_GPIO_SPEED_2MHz
TEST(stm32xx__gpio__ct, crh_bits__gpio_mode_af_od__speed_2MHz)
{
  check_crh_bits<GPIO_Mode_AF_OD, GPIO_Speed_2MHz>::apply();
};
#   endif
#   if defined _HAVE_GPIO_SPEED_50MHz
TEST(stm32xx__gpio__ct, crh_bits__gpio_mode_af_od__speed_50MHz)
{
  check_crh_bits<GPIO_Mode_AF_OD, GPIO_Speed_50MHz>::apply();
};
#   endif
# endif

# if defined _HAVE_GPIO_MODE_AF_PP
TEST(stm32xx__gpio__ct, crh_cnf_bits__gpio_mode_af_pp)
{
  check_crh_cnf_bits<GPIO_Mode_AF_PP>::apply();
};
#   if defined _HAVE_GPIO_SPEED_10MHz
TEST(stm32xx__gpio__ct, crh_bits__gpio_mode_af_pp__speed_10MHz)
{
  check_crh_bits<GPIO_Mode_AF_PP, GPIO_Speed_10MHz>::apply();
};
#   endif
#   if defined _HAVE_GPIO_SPEED_2MHz
TEST(stm32xx__gpio__ct, crh_bits__gpio_mode_af_pp__speed_2MHz)
{
  check_crh_bits<GPIO_Mode_AF_PP, GPIO_Speed_2MHz>::apply();
};
#   endif
#   if defined _HAVE_GPIO_SPEED_50MHz
TEST(stm32xx__gpio__ct, crh_bits__gpio_mode_af_pp__speed_50MHz)
{
  check_crh_bits<GPIO_Mode_AF_PP, GPIO_Speed_50MHz>::apply();
};
#   endif
# endif

# if defined _HAVE_GPIO_SPEED_10MHz
TEST(stm32xx__gpio__ct, crh_mode_bits__gpio_speed_10MHz)
{
  check_crh_mode_bits<GPIO_Speed_10MHz>::apply();
}
# endif

# if defined _HAVE_GPIO_SPEED_2MHz
TEST(stm32xx__gpio__ct, crh_mode_bits__gpio_speed_2MHz)
{
  check_crh_mode_bits<GPIO_Speed_2MHz>::apply();
}
# endif

# if defined _HAVE_GPIO_SPEED_50MHz
TEST(stm32xx__gpio__ct, crh_mode_bits__gpio_speed_50MHz)
{
  check_crh_mode_bits<GPIO_Speed_50MHz>::apply();
}
# endif
#endif /* _HAVE_GPIO_CRH_REGISTER */
