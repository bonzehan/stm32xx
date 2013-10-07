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
      CHECK_EQUAL(((_mode & 0x0Cul) << 0x00), (crl_cnf_bits<GPIO_Pin_0, _mode>::value));
      CHECK_EQUAL(((_mode & 0x0Cul) << 0x04), (crl_cnf_bits<GPIO_Pin_1, _mode>::value));
      CHECK_EQUAL(((_mode & 0x0Cul) << 0x08), (crl_cnf_bits<GPIO_Pin_2, _mode>::value));
      CHECK_EQUAL(((_mode & 0x0Cul) << 0x0C), (crl_cnf_bits<GPIO_Pin_3, _mode>::value));
      CHECK_EQUAL(((_mode & 0x0Cul) << 0x10), (crl_cnf_bits<GPIO_Pin_4, _mode>::value));
      CHECK_EQUAL(((_mode & 0x0Cul) << 0x14), (crl_cnf_bits<GPIO_Pin_5, _mode>::value));
      CHECK_EQUAL(((_mode & 0x0Cul) << 0x18), (crl_cnf_bits<GPIO_Pin_6, _mode>::value));
      CHECK_EQUAL(((_mode & 0x0Cul) << 0x1C), (crl_cnf_bits<GPIO_Pin_7, _mode>::value));
      CHECK_EQUAL(0ul,                        (crl_cnf_bits<GPIO_Pin_8, _mode>::value));
      CHECK_EQUAL(0ul,                        (crl_cnf_bits<GPIO_Pin_9, _mode>::value));
      CHECK_EQUAL(0ul,                        (crl_cnf_bits<GPIO_Pin_10,_mode>::value));
      CHECK_EQUAL(0ul,                        (crl_cnf_bits<GPIO_Pin_11,_mode>::value));
      CHECK_EQUAL(0ul,                        (crl_cnf_bits<GPIO_Pin_12,_mode>::value));
      CHECK_EQUAL(0ul,                        (crl_cnf_bits<GPIO_Pin_13,_mode>::value));
      CHECK_EQUAL(0ul,                        (crl_cnf_bits<GPIO_Pin_14,_mode>::value));
      CHECK_EQUAL(0ul,                        (crl_cnf_bits<GPIO_Pin_15,_mode>::value));
    }
  };
  
  template <GPIOMode_TypeDef _mode> 
  struct check_crh_cnf_bits
  {
    static void apply()
    {
      using namespace stm32xx::gpio::ct;
      CHECK_EQUAL(0ul,                        (crh_cnf_bits<GPIO_Pin_0, _mode>::value));
      CHECK_EQUAL(0ul,                        (crh_cnf_bits<GPIO_Pin_1, _mode>::value));
      CHECK_EQUAL(0ul,                        (crh_cnf_bits<GPIO_Pin_2, _mode>::value));
      CHECK_EQUAL(0ul,                        (crh_cnf_bits<GPIO_Pin_3, _mode>::value));
      CHECK_EQUAL(0ul,                        (crh_cnf_bits<GPIO_Pin_4, _mode>::value));
      CHECK_EQUAL(0ul,                        (crh_cnf_bits<GPIO_Pin_5, _mode>::value));
      CHECK_EQUAL(0ul,                        (crh_cnf_bits<GPIO_Pin_6, _mode>::value));
      CHECK_EQUAL(0ul,                        (crh_cnf_bits<GPIO_Pin_7, _mode>::value));
      CHECK_EQUAL(((_mode & 0x0Cul) << 0x00), (crh_cnf_bits<GPIO_Pin_8, _mode>::value));
      CHECK_EQUAL(((_mode & 0x0Cul) << 0x04), (crh_cnf_bits<GPIO_Pin_9, _mode>::value));
      CHECK_EQUAL(((_mode & 0x0Cul) << 0x08), (crh_cnf_bits<GPIO_Pin_10,_mode>::value));
      CHECK_EQUAL(((_mode & 0x0Cul) << 0x0C), (crh_cnf_bits<GPIO_Pin_11,_mode>::value));
      CHECK_EQUAL(((_mode & 0x0Cul) << 0x10), (crh_cnf_bits<GPIO_Pin_12,_mode>::value));
      CHECK_EQUAL(((_mode & 0x0Cul) << 0x14), (crh_cnf_bits<GPIO_Pin_13,_mode>::value));
      CHECK_EQUAL(((_mode & 0x0Cul) << 0x18), (crh_cnf_bits<GPIO_Pin_14,_mode>::value));
      CHECK_EQUAL(((_mode & 0x0Cul) << 0x1C), (crh_cnf_bits<GPIO_Pin_15,_mode>::value));
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
      CHECK_EQUAL(((_speed & 0x03ul) << 0x00), (crl_mode_bits<GPIO_Pin_0, _speed>::value));
      CHECK_EQUAL(((_speed & 0x03ul) << 0x04), (crl_mode_bits<GPIO_Pin_1, _speed>::value));
      CHECK_EQUAL(((_speed & 0x03ul) << 0x08), (crl_mode_bits<GPIO_Pin_2, _speed>::value));
      CHECK_EQUAL(((_speed & 0x03ul) << 0x0C), (crl_mode_bits<GPIO_Pin_3, _speed>::value));
      CHECK_EQUAL(((_speed & 0x03ul) << 0x10), (crl_mode_bits<GPIO_Pin_4, _speed>::value));
      CHECK_EQUAL(((_speed & 0x03ul) << 0x14), (crl_mode_bits<GPIO_Pin_5, _speed>::value));
      CHECK_EQUAL(((_speed & 0x03ul) << 0x18), (crl_mode_bits<GPIO_Pin_6, _speed>::value));
      CHECK_EQUAL(((_speed & 0x03ul) << 0x1C), (crl_mode_bits<GPIO_Pin_7, _speed>::value));
      CHECK_EQUAL(0ul,                         (crl_mode_bits<GPIO_Pin_8, _speed>::value));
      CHECK_EQUAL(0ul,                         (crl_mode_bits<GPIO_Pin_9, _speed>::value));
      CHECK_EQUAL(0ul,                         (crl_mode_bits<GPIO_Pin_10,_speed>::value));
      CHECK_EQUAL(0ul,                         (crl_mode_bits<GPIO_Pin_11,_speed>::value));
      CHECK_EQUAL(0ul,                         (crl_mode_bits<GPIO_Pin_12,_speed>::value));
      CHECK_EQUAL(0ul,                         (crl_mode_bits<GPIO_Pin_13,_speed>::value));
      CHECK_EQUAL(0ul,                         (crl_mode_bits<GPIO_Pin_14,_speed>::value));
      CHECK_EQUAL(0ul,                         (crl_mode_bits<GPIO_Pin_15,_speed>::value));
    }
  };
  
  template <GPIOSpeed_TypeDef _speed> 
  struct check_crh_mode_bits
  {
    static void apply()
    {
      using namespace stm32xx::gpio::ct;
      CHECK_EQUAL(0ul,                         (crh_mode_bits<GPIO_Pin_0, _speed>::value));
      CHECK_EQUAL(0ul,                         (crh_mode_bits<GPIO_Pin_1, _speed>::value));
      CHECK_EQUAL(0ul,                         (crh_mode_bits<GPIO_Pin_2, _speed>::value));
      CHECK_EQUAL(0ul,                         (crh_mode_bits<GPIO_Pin_3, _speed>::value));
      CHECK_EQUAL(0ul,                         (crh_mode_bits<GPIO_Pin_4, _speed>::value));
      CHECK_EQUAL(0ul,                         (crh_mode_bits<GPIO_Pin_5, _speed>::value));
      CHECK_EQUAL(0ul,                         (crh_mode_bits<GPIO_Pin_6, _speed>::value));
      CHECK_EQUAL(0ul,                         (crh_mode_bits<GPIO_Pin_7, _speed>::value));
      CHECK_EQUAL(((_speed & 0x03ul) << 0x00), (crh_mode_bits<GPIO_Pin_8, _speed>::value));
      CHECK_EQUAL(((_speed & 0x03ul) << 0x04), (crh_mode_bits<GPIO_Pin_9, _speed>::value));
      CHECK_EQUAL(((_speed & 0x03ul) << 0x08), (crh_mode_bits<GPIO_Pin_10,_speed>::value));
      CHECK_EQUAL(((_speed & 0x03ul) << 0x0C), (crh_mode_bits<GPIO_Pin_11,_speed>::value));
      CHECK_EQUAL(((_speed & 0x03ul) << 0x10), (crh_mode_bits<GPIO_Pin_12,_speed>::value));
      CHECK_EQUAL(((_speed & 0x03ul) << 0x14), (crh_mode_bits<GPIO_Pin_13,_speed>::value));
      CHECK_EQUAL(((_speed & 0x03ul) << 0x18), (crh_mode_bits<GPIO_Pin_14,_speed>::value));
      CHECK_EQUAL(((_speed & 0x03ul) << 0x1C), (crh_mode_bits<GPIO_Pin_15,_speed>::value));
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

  template <GPIOMode_TypeDef _mode, GPIOSpeed_TypeDef _speed=(GPIOSpeed_TypeDef)0>
    struct check_crl_bits
    {
      static void
      apply()
      {
        using namespace stm32xx::gpio::ct;
        constexpr uint32_t _ms = (_mode & 0x0Cul)|(_speed & 0x03ul);
        CHECK_EQUAL((_ms << 0x00), (crl_bits<GPIO_Pin_0, _mode,_speed>::value));
        CHECK_EQUAL((_ms << 0x04), (crl_bits<GPIO_Pin_1, _mode,_speed>::value));
        CHECK_EQUAL((_ms << 0x08), (crl_bits<GPIO_Pin_2, _mode,_speed>::value));
        CHECK_EQUAL((_ms << 0x0C), (crl_bits<GPIO_Pin_3, _mode,_speed>::value));
        CHECK_EQUAL((_ms << 0x10), (crl_bits<GPIO_Pin_4, _mode,_speed>::value));
        CHECK_EQUAL((_ms << 0x14), (crl_bits<GPIO_Pin_5, _mode,_speed>::value));
        CHECK_EQUAL((_ms << 0x18), (crl_bits<GPIO_Pin_6, _mode,_speed>::value));
        CHECK_EQUAL((_ms << 0x1C), (crl_bits<GPIO_Pin_7, _mode,_speed>::value));
        CHECK_EQUAL(0ul,           (crl_bits<GPIO_Pin_8, _mode,_speed>::value));
        CHECK_EQUAL(0ul,           (crl_bits<GPIO_Pin_9, _mode,_speed>::value));
        CHECK_EQUAL(0ul,           (crl_bits<GPIO_Pin_10,_mode,_speed>::value));
        CHECK_EQUAL(0ul,           (crl_bits<GPIO_Pin_11,_mode,_speed>::value));
        CHECK_EQUAL(0ul,           (crl_bits<GPIO_Pin_12,_mode,_speed>::value));
        CHECK_EQUAL(0ul,           (crl_bits<GPIO_Pin_13,_mode,_speed>::value));
        CHECK_EQUAL(0ul,           (crl_bits<GPIO_Pin_14,_mode,_speed>::value));
        CHECK_EQUAL(0ul,           (crl_bits<GPIO_Pin_15,_mode,_speed>::value));
      }
    };

  template <GPIOMode_TypeDef _mode>
    struct check_crl_bits<_mode, (GPIOSpeed_TypeDef)0>
    {
      static void
      apply()
      {
        using namespace stm32xx::gpio::ct;
        constexpr uint32_t _ms = (_mode & 0x0Cul);
        CHECK_EQUAL((_ms << 0x00), (crl_bits<GPIO_Pin_0, _mode>::value));
        CHECK_EQUAL((_ms << 0x04), (crl_bits<GPIO_Pin_1, _mode>::value));
        CHECK_EQUAL((_ms << 0x08), (crl_bits<GPIO_Pin_2, _mode>::value));
        CHECK_EQUAL((_ms << 0x0C), (crl_bits<GPIO_Pin_3, _mode>::value));
        CHECK_EQUAL((_ms << 0x10), (crl_bits<GPIO_Pin_4, _mode>::value));
        CHECK_EQUAL((_ms << 0x14), (crl_bits<GPIO_Pin_5, _mode>::value));
        CHECK_EQUAL((_ms << 0x18), (crl_bits<GPIO_Pin_6, _mode>::value));
        CHECK_EQUAL((_ms << 0x1C), (crl_bits<GPIO_Pin_7, _mode>::value));
        CHECK_EQUAL(0ul,           (crl_bits<GPIO_Pin_8, _mode>::value));
        CHECK_EQUAL(0ul,           (crl_bits<GPIO_Pin_9, _mode>::value));
        CHECK_EQUAL(0ul,           (crl_bits<GPIO_Pin_10,_mode>::value));
        CHECK_EQUAL(0ul,           (crl_bits<GPIO_Pin_11,_mode>::value));
        CHECK_EQUAL(0ul,           (crl_bits<GPIO_Pin_12,_mode>::value));
        CHECK_EQUAL(0ul,           (crl_bits<GPIO_Pin_13,_mode>::value));
        CHECK_EQUAL(0ul,           (crl_bits<GPIO_Pin_14,_mode>::value));
        CHECK_EQUAL(0ul,           (crl_bits<GPIO_Pin_15,_mode>::value));
      }
    };

  template <GPIOMode_TypeDef _mode, GPIOSpeed_TypeDef _speed=(GPIOSpeed_TypeDef)0>
    struct check_crh_bits
    {
      static void
      apply()
      {
        using namespace stm32xx::gpio::ct;
        constexpr uint32_t _ms = (_mode & 0x0Cul)|(_speed & 0x03ul);
        CHECK_EQUAL(0ul,           (crh_bits<GPIO_Pin_0, _mode,_speed>::value));
        CHECK_EQUAL(0ul,           (crh_bits<GPIO_Pin_1, _mode,_speed>::value));
        CHECK_EQUAL(0ul,           (crh_bits<GPIO_Pin_2, _mode,_speed>::value));
        CHECK_EQUAL(0ul,           (crh_bits<GPIO_Pin_3, _mode,_speed>::value));
        CHECK_EQUAL(0ul,           (crh_bits<GPIO_Pin_4, _mode,_speed>::value));
        CHECK_EQUAL(0ul,           (crh_bits<GPIO_Pin_5, _mode,_speed>::value));
        CHECK_EQUAL(0ul,           (crh_bits<GPIO_Pin_6, _mode,_speed>::value));
        CHECK_EQUAL(0ul,           (crh_bits<GPIO_Pin_7, _mode,_speed>::value));
        CHECK_EQUAL((_ms << 0x00), (crh_bits<GPIO_Pin_8, _mode,_speed>::value));
        CHECK_EQUAL((_ms << 0x04), (crh_bits<GPIO_Pin_9, _mode,_speed>::value));
        CHECK_EQUAL((_ms << 0x08), (crh_bits<GPIO_Pin_10,_mode,_speed>::value));
        CHECK_EQUAL((_ms << 0x0C), (crh_bits<GPIO_Pin_11,_mode,_speed>::value));
        CHECK_EQUAL((_ms << 0x10), (crh_bits<GPIO_Pin_12,_mode,_speed>::value));
        CHECK_EQUAL((_ms << 0x14), (crh_bits<GPIO_Pin_13,_mode,_speed>::value));
        CHECK_EQUAL((_ms << 0x18), (crh_bits<GPIO_Pin_14,_mode,_speed>::value));
        CHECK_EQUAL((_ms << 0x1C), (crh_bits<GPIO_Pin_15,_mode,_speed>::value));
      }
    };

  template <GPIOMode_TypeDef _mode>
    struct check_crh_bits<_mode, (GPIOSpeed_TypeDef)0>
    {
      static void
      apply()
      {
        using namespace stm32xx::gpio::ct;
        constexpr uint32_t _ms = (_mode & 0x0Cul);
        CHECK_EQUAL(0ul,           (crh_bits<GPIO_Pin_0, _mode>::value));
        CHECK_EQUAL(0ul,           (crh_bits<GPIO_Pin_1, _mode>::value));
        CHECK_EQUAL(0ul,           (crh_bits<GPIO_Pin_2, _mode>::value));
        CHECK_EQUAL(0ul,           (crh_bits<GPIO_Pin_3, _mode>::value));
        CHECK_EQUAL(0ul,           (crh_bits<GPIO_Pin_4, _mode>::value));
        CHECK_EQUAL(0ul,           (crh_bits<GPIO_Pin_5, _mode>::value));
        CHECK_EQUAL(0ul,           (crh_bits<GPIO_Pin_6, _mode>::value));
        CHECK_EQUAL(0ul,           (crh_bits<GPIO_Pin_7, _mode>::value));
        CHECK_EQUAL((_ms << 0x00), (crh_bits<GPIO_Pin_8, _mode>::value));
        CHECK_EQUAL((_ms << 0x04), (crh_bits<GPIO_Pin_9, _mode>::value));
        CHECK_EQUAL((_ms << 0x08), (crh_bits<GPIO_Pin_10,_mode>::value));
        CHECK_EQUAL((_ms << 0x0C), (crh_bits<GPIO_Pin_11,_mode>::value));
        CHECK_EQUAL((_ms << 0x10), (crh_bits<GPIO_Pin_12,_mode>::value));
        CHECK_EQUAL((_ms << 0x14), (crh_bits<GPIO_Pin_13,_mode>::value));
        CHECK_EQUAL((_ms << 0x18), (crh_bits<GPIO_Pin_14,_mode>::value));
        CHECK_EQUAL((_ms << 0x1C), (crh_bits<GPIO_Pin_15,_mode>::value));
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

  template<GPIOMode_TypeDef _mode, GPIOSpeed_TypeDef _speed=(GPIOSpeed_TypeDef)0>
    struct check_crl_masked
    {
      static void apply()
      {
        using namespace stm32xx::gpio::ct;
        using stm32xx::bits::ct::get_bits;
        using stm32xx::bits::ct::get_mask;

        using _m0  = crl_masked<GPIO_Pin_0,  _mode, _speed>;
        using _m1  = crl_masked<GPIO_Pin_1,  _mode, _speed>;
        using _m2  = crl_masked<GPIO_Pin_2,  _mode, _speed>;
        using _m3  = crl_masked<GPIO_Pin_3,  _mode, _speed>;
        using _m4  = crl_masked<GPIO_Pin_4,  _mode, _speed>;
        using _m5  = crl_masked<GPIO_Pin_5,  _mode, _speed>;
        using _m6  = crl_masked<GPIO_Pin_6,  _mode, _speed>;
        using _m7  = crl_masked<GPIO_Pin_7,  _mode, _speed>;
        using _m8  = crl_masked<GPIO_Pin_8,  _mode, _speed>;
        using _m9  = crl_masked<GPIO_Pin_9,  _mode, _speed>;
        using _m10 = crl_masked<GPIO_Pin_10, _mode, _speed>;
        using _m11 = crl_masked<GPIO_Pin_11, _mode, _speed>;
        using _m12 = crl_masked<GPIO_Pin_12, _mode, _speed>;
        using _m13 = crl_masked<GPIO_Pin_13, _mode, _speed>;
        using _m14 = crl_masked<GPIO_Pin_14, _mode, _speed>;
        using _m15 = crl_masked<GPIO_Pin_15, _mode, _speed>;

        CHECK_EQUAL((crl_bits<GPIO_Pin_0, _mode,_speed>::value), (get_bits<_m0>::value));
        CHECK_EQUAL((crl_bits<GPIO_Pin_1, _mode,_speed>::value), (get_bits<_m1>::value));
        CHECK_EQUAL((crl_bits<GPIO_Pin_2, _mode,_speed>::value), (get_bits<_m2>::value));
        CHECK_EQUAL((crl_bits<GPIO_Pin_3, _mode,_speed>::value), (get_bits<_m3>::value));
        CHECK_EQUAL((crl_bits<GPIO_Pin_4, _mode,_speed>::value), (get_bits<_m4>::value));
        CHECK_EQUAL((crl_bits<GPIO_Pin_5, _mode,_speed>::value), (get_bits<_m5>::value));
        CHECK_EQUAL((crl_bits<GPIO_Pin_6, _mode,_speed>::value), (get_bits<_m6>::value));
        CHECK_EQUAL((crl_bits<GPIO_Pin_7, _mode,_speed>::value), (get_bits<_m7>::value));
        CHECK_EQUAL((crl_bits<GPIO_Pin_8, _mode,_speed>::value), (get_bits<_m8>::value));
        CHECK_EQUAL((crl_bits<GPIO_Pin_9, _mode,_speed>::value), (get_bits<_m9>::value));
        CHECK_EQUAL((crl_bits<GPIO_Pin_10,_mode,_speed>::value), (get_bits<_m10>::value));
        CHECK_EQUAL((crl_bits<GPIO_Pin_11,_mode,_speed>::value), (get_bits<_m11>::value));
        CHECK_EQUAL((crl_bits<GPIO_Pin_12,_mode,_speed>::value), (get_bits<_m12>::value));
        CHECK_EQUAL((crl_bits<GPIO_Pin_13,_mode,_speed>::value), (get_bits<_m13>::value));
        CHECK_EQUAL((crl_bits<GPIO_Pin_14,_mode,_speed>::value), (get_bits<_m14>::value));
        CHECK_EQUAL((crl_bits<GPIO_Pin_15,_mode,_speed>::value), (get_bits<_m15>::value));

        CHECK_EQUAL((crl_mask<GPIO_Pin_0>::value),  (get_mask<_m0>::value));
        CHECK_EQUAL((crl_mask<GPIO_Pin_1>::value),  (get_mask<_m1>::value));
        CHECK_EQUAL((crl_mask<GPIO_Pin_2>::value),  (get_mask<_m2>::value));
        CHECK_EQUAL((crl_mask<GPIO_Pin_3>::value),  (get_mask<_m3>::value));
        CHECK_EQUAL((crl_mask<GPIO_Pin_4>::value),  (get_mask<_m4>::value));
        CHECK_EQUAL((crl_mask<GPIO_Pin_5>::value),  (get_mask<_m5>::value));
        CHECK_EQUAL((crl_mask<GPIO_Pin_6>::value),  (get_mask<_m6>::value));
        CHECK_EQUAL((crl_mask<GPIO_Pin_7>::value),  (get_mask<_m7>::value));
        CHECK_EQUAL((crl_mask<GPIO_Pin_8>::value),  (get_mask<_m8>::value));
        CHECK_EQUAL((crl_mask<GPIO_Pin_9>::value),  (get_mask<_m9>::value));
        CHECK_EQUAL((crl_mask<GPIO_Pin_10>::value), (get_mask<_m10>::value));
        CHECK_EQUAL((crl_mask<GPIO_Pin_11>::value), (get_mask<_m11>::value));
        CHECK_EQUAL((crl_mask<GPIO_Pin_12>::value), (get_mask<_m12>::value));
        CHECK_EQUAL((crl_mask<GPIO_Pin_13>::value), (get_mask<_m13>::value));
        CHECK_EQUAL((crl_mask<GPIO_Pin_14>::value), (get_mask<_m14>::value));
        CHECK_EQUAL((crl_mask<GPIO_Pin_15>::value), (get_mask<_m15>::value));
      }
    };

  template<GPIOMode_TypeDef _mode>
    struct check_crl_masked<_mode, (GPIOSpeed_TypeDef)0>
    {
      static void apply()
      {
        using namespace stm32xx::gpio::ct;
        using stm32xx::bits::ct::get_bits;
        using stm32xx::bits::ct::get_mask;

        using _m0  = crl_masked<GPIO_Pin_0,  _mode>;
        using _m1  = crl_masked<GPIO_Pin_1,  _mode>;
        using _m2  = crl_masked<GPIO_Pin_2,  _mode>;
        using _m3  = crl_masked<GPIO_Pin_3,  _mode>;
        using _m4  = crl_masked<GPIO_Pin_4,  _mode>;
        using _m5  = crl_masked<GPIO_Pin_5,  _mode>;
        using _m6  = crl_masked<GPIO_Pin_6,  _mode>;
        using _m7  = crl_masked<GPIO_Pin_7,  _mode>;
        using _m8  = crl_masked<GPIO_Pin_8,  _mode>;
        using _m9  = crl_masked<GPIO_Pin_9,  _mode>;
        using _m10 = crl_masked<GPIO_Pin_10, _mode>;
        using _m11 = crl_masked<GPIO_Pin_11, _mode>;
        using _m12 = crl_masked<GPIO_Pin_12, _mode>;
        using _m13 = crl_masked<GPIO_Pin_13, _mode>;
        using _m14 = crl_masked<GPIO_Pin_14, _mode>;
        using _m15 = crl_masked<GPIO_Pin_15, _mode>;

        CHECK_EQUAL((crl_bits<GPIO_Pin_0, _mode>::value), (get_bits<_m0>::value));
        CHECK_EQUAL((crl_bits<GPIO_Pin_1, _mode>::value), (get_bits<_m1>::value));
        CHECK_EQUAL((crl_bits<GPIO_Pin_2, _mode>::value), (get_bits<_m2>::value));
        CHECK_EQUAL((crl_bits<GPIO_Pin_3, _mode>::value), (get_bits<_m3>::value));
        CHECK_EQUAL((crl_bits<GPIO_Pin_4, _mode>::value), (get_bits<_m4>::value));
        CHECK_EQUAL((crl_bits<GPIO_Pin_5, _mode>::value), (get_bits<_m5>::value));
        CHECK_EQUAL((crl_bits<GPIO_Pin_6, _mode>::value), (get_bits<_m6>::value));
        CHECK_EQUAL((crl_bits<GPIO_Pin_7, _mode>::value), (get_bits<_m7>::value));
        CHECK_EQUAL((crl_bits<GPIO_Pin_8, _mode>::value), (get_bits<_m8>::value));
        CHECK_EQUAL((crl_bits<GPIO_Pin_9, _mode>::value), (get_bits<_m9>::value));
        CHECK_EQUAL((crl_bits<GPIO_Pin_10,_mode>::value), (get_bits<_m10>::value));
        CHECK_EQUAL((crl_bits<GPIO_Pin_11,_mode>::value), (get_bits<_m11>::value));
        CHECK_EQUAL((crl_bits<GPIO_Pin_12,_mode>::value), (get_bits<_m12>::value));
        CHECK_EQUAL((crl_bits<GPIO_Pin_13,_mode>::value), (get_bits<_m13>::value));
        CHECK_EQUAL((crl_bits<GPIO_Pin_14,_mode>::value), (get_bits<_m14>::value));
        CHECK_EQUAL((crl_bits<GPIO_Pin_15,_mode>::value), (get_bits<_m15>::value));

        CHECK_EQUAL((crl_mask<GPIO_Pin_0>::value),  (get_mask<_m0>::value));
        CHECK_EQUAL((crl_mask<GPIO_Pin_1>::value),  (get_mask<_m1>::value));
        CHECK_EQUAL((crl_mask<GPIO_Pin_2>::value),  (get_mask<_m2>::value));
        CHECK_EQUAL((crl_mask<GPIO_Pin_3>::value),  (get_mask<_m3>::value));
        CHECK_EQUAL((crl_mask<GPIO_Pin_4>::value),  (get_mask<_m4>::value));
        CHECK_EQUAL((crl_mask<GPIO_Pin_5>::value),  (get_mask<_m5>::value));
        CHECK_EQUAL((crl_mask<GPIO_Pin_6>::value),  (get_mask<_m6>::value));
        CHECK_EQUAL((crl_mask<GPIO_Pin_7>::value),  (get_mask<_m7>::value));
        CHECK_EQUAL((crl_mask<GPIO_Pin_8>::value),  (get_mask<_m8>::value));
        CHECK_EQUAL((crl_mask<GPIO_Pin_9>::value),  (get_mask<_m9>::value));
        CHECK_EQUAL((crl_mask<GPIO_Pin_10>::value), (get_mask<_m10>::value));
        CHECK_EQUAL((crl_mask<GPIO_Pin_11>::value), (get_mask<_m11>::value));
        CHECK_EQUAL((crl_mask<GPIO_Pin_12>::value), (get_mask<_m12>::value));
        CHECK_EQUAL((crl_mask<GPIO_Pin_13>::value), (get_mask<_m13>::value));
        CHECK_EQUAL((crl_mask<GPIO_Pin_14>::value), (get_mask<_m14>::value));
        CHECK_EQUAL((crl_mask<GPIO_Pin_15>::value), (get_mask<_m15>::value));
      }
    };

  template<GPIOMode_TypeDef _mode, GPIOSpeed_TypeDef _speed=(GPIOSpeed_TypeDef)0>
    struct check_crh_masked
    {
      static void apply()
      {
        using namespace stm32xx::gpio::ct;
        using stm32xx::bits::ct::get_bits;
        using stm32xx::bits::ct::get_mask;

        using _m0  = crh_masked<GPIO_Pin_0,  _mode, _speed>;
        using _m1  = crh_masked<GPIO_Pin_1,  _mode, _speed>;
        using _m2  = crh_masked<GPIO_Pin_2,  _mode, _speed>;
        using _m3  = crh_masked<GPIO_Pin_3,  _mode, _speed>;
        using _m4  = crh_masked<GPIO_Pin_4,  _mode, _speed>;
        using _m5  = crh_masked<GPIO_Pin_5,  _mode, _speed>;
        using _m6  = crh_masked<GPIO_Pin_6,  _mode, _speed>;
        using _m7  = crh_masked<GPIO_Pin_7,  _mode, _speed>;
        using _m8  = crh_masked<GPIO_Pin_8,  _mode, _speed>;
        using _m9  = crh_masked<GPIO_Pin_9,  _mode, _speed>;
        using _m10 = crh_masked<GPIO_Pin_10, _mode, _speed>;
        using _m11 = crh_masked<GPIO_Pin_11, _mode, _speed>;
        using _m12 = crh_masked<GPIO_Pin_12, _mode, _speed>;
        using _m13 = crh_masked<GPIO_Pin_13, _mode, _speed>;
        using _m14 = crh_masked<GPIO_Pin_14, _mode, _speed>;
        using _m15 = crh_masked<GPIO_Pin_15, _mode, _speed>;

        CHECK_EQUAL((crh_bits<GPIO_Pin_0, _mode,_speed>::value), (get_bits<_m0>::value));
        CHECK_EQUAL((crh_bits<GPIO_Pin_1, _mode,_speed>::value), (get_bits<_m1>::value));
        CHECK_EQUAL((crh_bits<GPIO_Pin_2, _mode,_speed>::value), (get_bits<_m2>::value));
        CHECK_EQUAL((crh_bits<GPIO_Pin_3, _mode,_speed>::value), (get_bits<_m3>::value));
        CHECK_EQUAL((crh_bits<GPIO_Pin_4, _mode,_speed>::value), (get_bits<_m4>::value));
        CHECK_EQUAL((crh_bits<GPIO_Pin_5, _mode,_speed>::value), (get_bits<_m5>::value));
        CHECK_EQUAL((crh_bits<GPIO_Pin_6, _mode,_speed>::value), (get_bits<_m6>::value));
        CHECK_EQUAL((crh_bits<GPIO_Pin_7, _mode,_speed>::value), (get_bits<_m7>::value));
        CHECK_EQUAL((crh_bits<GPIO_Pin_8, _mode,_speed>::value), (get_bits<_m8>::value));
        CHECK_EQUAL((crh_bits<GPIO_Pin_9, _mode,_speed>::value), (get_bits<_m9>::value));
        CHECK_EQUAL((crh_bits<GPIO_Pin_10,_mode,_speed>::value), (get_bits<_m10>::value));
        CHECK_EQUAL((crh_bits<GPIO_Pin_11,_mode,_speed>::value), (get_bits<_m11>::value));
        CHECK_EQUAL((crh_bits<GPIO_Pin_12,_mode,_speed>::value), (get_bits<_m12>::value));
        CHECK_EQUAL((crh_bits<GPIO_Pin_13,_mode,_speed>::value), (get_bits<_m13>::value));
        CHECK_EQUAL((crh_bits<GPIO_Pin_14,_mode,_speed>::value), (get_bits<_m14>::value));
        CHECK_EQUAL((crh_bits<GPIO_Pin_15,_mode,_speed>::value), (get_bits<_m15>::value));

        CHECK_EQUAL((crh_mask<GPIO_Pin_0>::value),  (get_mask<_m0>::value));
        CHECK_EQUAL((crh_mask<GPIO_Pin_1>::value),  (get_mask<_m1>::value));
        CHECK_EQUAL((crh_mask<GPIO_Pin_2>::value),  (get_mask<_m2>::value));
        CHECK_EQUAL((crh_mask<GPIO_Pin_3>::value),  (get_mask<_m3>::value));
        CHECK_EQUAL((crh_mask<GPIO_Pin_4>::value),  (get_mask<_m4>::value));
        CHECK_EQUAL((crh_mask<GPIO_Pin_5>::value),  (get_mask<_m5>::value));
        CHECK_EQUAL((crh_mask<GPIO_Pin_6>::value),  (get_mask<_m6>::value));
        CHECK_EQUAL((crh_mask<GPIO_Pin_7>::value),  (get_mask<_m7>::value));
        CHECK_EQUAL((crh_mask<GPIO_Pin_8>::value),  (get_mask<_m8>::value));
        CHECK_EQUAL((crh_mask<GPIO_Pin_9>::value),  (get_mask<_m9>::value));
        CHECK_EQUAL((crh_mask<GPIO_Pin_10>::value), (get_mask<_m10>::value));
        CHECK_EQUAL((crh_mask<GPIO_Pin_11>::value), (get_mask<_m11>::value));
        CHECK_EQUAL((crh_mask<GPIO_Pin_12>::value), (get_mask<_m12>::value));
        CHECK_EQUAL((crh_mask<GPIO_Pin_13>::value), (get_mask<_m13>::value));
        CHECK_EQUAL((crh_mask<GPIO_Pin_14>::value), (get_mask<_m14>::value));
        CHECK_EQUAL((crh_mask<GPIO_Pin_15>::value), (get_mask<_m15>::value));
      }
    };

  template<GPIOMode_TypeDef _mode>
    struct check_crh_masked<_mode, (GPIOSpeed_TypeDef)0>
    {
      static void apply()
      {
        using namespace stm32xx::gpio::ct;
        using stm32xx::bits::ct::get_bits;
        using stm32xx::bits::ct::get_mask;

        using _m0  = crh_masked<GPIO_Pin_0,  _mode>;
        using _m1  = crh_masked<GPIO_Pin_1,  _mode>;
        using _m2  = crh_masked<GPIO_Pin_2,  _mode>;
        using _m3  = crh_masked<GPIO_Pin_3,  _mode>;
        using _m4  = crh_masked<GPIO_Pin_4,  _mode>;
        using _m5  = crh_masked<GPIO_Pin_5,  _mode>;
        using _m6  = crh_masked<GPIO_Pin_6,  _mode>;
        using _m7  = crh_masked<GPIO_Pin_7,  _mode>;
        using _m8  = crh_masked<GPIO_Pin_8,  _mode>;
        using _m9  = crh_masked<GPIO_Pin_9,  _mode>;
        using _m10 = crh_masked<GPIO_Pin_10, _mode>;
        using _m11 = crh_masked<GPIO_Pin_11, _mode>;
        using _m12 = crh_masked<GPIO_Pin_12, _mode>;
        using _m13 = crh_masked<GPIO_Pin_13, _mode>;
        using _m14 = crh_masked<GPIO_Pin_14, _mode>;
        using _m15 = crh_masked<GPIO_Pin_15, _mode>;

        CHECK_EQUAL((crh_bits<GPIO_Pin_0, _mode>::value), (get_bits<_m0>::value));
        CHECK_EQUAL((crh_bits<GPIO_Pin_1, _mode>::value), (get_bits<_m1>::value));
        CHECK_EQUAL((crh_bits<GPIO_Pin_2, _mode>::value), (get_bits<_m2>::value));
        CHECK_EQUAL((crh_bits<GPIO_Pin_3, _mode>::value), (get_bits<_m3>::value));
        CHECK_EQUAL((crh_bits<GPIO_Pin_4, _mode>::value), (get_bits<_m4>::value));
        CHECK_EQUAL((crh_bits<GPIO_Pin_5, _mode>::value), (get_bits<_m5>::value));
        CHECK_EQUAL((crh_bits<GPIO_Pin_6, _mode>::value), (get_bits<_m6>::value));
        CHECK_EQUAL((crh_bits<GPIO_Pin_7, _mode>::value), (get_bits<_m7>::value));
        CHECK_EQUAL((crh_bits<GPIO_Pin_8, _mode>::value), (get_bits<_m8>::value));
        CHECK_EQUAL((crh_bits<GPIO_Pin_9, _mode>::value), (get_bits<_m9>::value));
        CHECK_EQUAL((crh_bits<GPIO_Pin_10,_mode>::value), (get_bits<_m10>::value));
        CHECK_EQUAL((crh_bits<GPIO_Pin_11,_mode>::value), (get_bits<_m11>::value));
        CHECK_EQUAL((crh_bits<GPIO_Pin_12,_mode>::value), (get_bits<_m12>::value));
        CHECK_EQUAL((crh_bits<GPIO_Pin_13,_mode>::value), (get_bits<_m13>::value));
        CHECK_EQUAL((crh_bits<GPIO_Pin_14,_mode>::value), (get_bits<_m14>::value));
        CHECK_EQUAL((crh_bits<GPIO_Pin_15,_mode>::value), (get_bits<_m15>::value));

        CHECK_EQUAL((crh_mask<GPIO_Pin_0>::value),  (get_mask<_m0>::value));
        CHECK_EQUAL((crh_mask<GPIO_Pin_1>::value),  (get_mask<_m1>::value));
        CHECK_EQUAL((crh_mask<GPIO_Pin_2>::value),  (get_mask<_m2>::value));
        CHECK_EQUAL((crh_mask<GPIO_Pin_3>::value),  (get_mask<_m3>::value));
        CHECK_EQUAL((crh_mask<GPIO_Pin_4>::value),  (get_mask<_m4>::value));
        CHECK_EQUAL((crh_mask<GPIO_Pin_5>::value),  (get_mask<_m5>::value));
        CHECK_EQUAL((crh_mask<GPIO_Pin_6>::value),  (get_mask<_m6>::value));
        CHECK_EQUAL((crh_mask<GPIO_Pin_7>::value),  (get_mask<_m7>::value));
        CHECK_EQUAL((crh_mask<GPIO_Pin_8>::value),  (get_mask<_m8>::value));
        CHECK_EQUAL((crh_mask<GPIO_Pin_9>::value),  (get_mask<_m9>::value));
        CHECK_EQUAL((crh_mask<GPIO_Pin_10>::value), (get_mask<_m10>::value));
        CHECK_EQUAL((crh_mask<GPIO_Pin_11>::value), (get_mask<_m11>::value));
        CHECK_EQUAL((crh_mask<GPIO_Pin_12>::value), (get_mask<_m12>::value));
        CHECK_EQUAL((crh_mask<GPIO_Pin_13>::value), (get_mask<_m13>::value));
        CHECK_EQUAL((crh_mask<GPIO_Pin_14>::value), (get_mask<_m14>::value));
        CHECK_EQUAL((crh_mask<GPIO_Pin_15>::value), (get_mask<_m15>::value));
      }
    };
};

#define _CONCAT(_a, _b) _a ## _b

/* Test with 0 args */
#define _TEST0(_name) \
  TEST(stm32xx__gpio__ct, _name) { \
    check_ ## _name();\
  }

/* Test with 1 arg */
#define _TEST1(_name,_arg1) \
  TEST(stm32xx__gpio__ct, _name ## __ ## _arg1) { \
    check_ ## _name<_arg1>::apply(); \
  }

/* Test with 2 args */
#define _TEST2(_name,_arg1, _arg2) \
  TEST(stm32xx__gpio__ct, _name ## __ ## _arg1 ## __ ## _arg2) { \
    check_ ## _name<_arg1,_arg2>::apply(); \
  }

/*
 * CRL
 */
#if defined _HAVE_GPIO_CRL_REGISTER

_TEST0(crl_cnf_mask);
_TEST0(crl_mode_mask);
_TEST0(crl_mask);

/* crl_mode_bits */
# if defined _HAVE_GPIO_SPEED_10MHz
_TEST1(crl_mode_bits, GPIO_Speed_10MHz);
# endif
# if defined _HAVE_GPIO_SPEED_2MHz
_TEST1(crl_mode_bits, GPIO_Speed_2MHz);
# endif
# if defined _HAVE_GPIO_SPEED_50MHz
_TEST1(crl_mode_bits, GPIO_Speed_50MHz);
# endif

/* crl_cnf_bits */
# if defined _HAVE_GPIO_MODE_AIN
_TEST1(crl_cnf_bits, GPIO_Mode_AIN);
# endif
# if defined _HAVE_GPIO_MODE_IN_FLOATING
_TEST1(crl_cnf_bits, GPIO_Mode_IN_FLOATING);
# endif
# if defined _HAVE_GPIO_MODE_IPD
_TEST1(crl_cnf_bits, GPIO_Mode_IPD);
# endif
# if defined _HAVE_GPIO_MODE_IPU
_TEST1(crl_cnf_bits, GPIO_Mode_IPU);
# endif
# if defined _HAVE_GPIO_MODE_Out_OD
_TEST1(crl_cnf_bits, GPIO_Mode_Out_OD);
# endif
# if defined _HAVE_GPIO_MODE_Out_PP
_TEST1(crl_cnf_bits, GPIO_Mode_Out_PP);
# endif
# if defined _HAVE_GPIO_MODE_AF_OD
_TEST1(crl_cnf_bits, GPIO_Mode_AF_OD);
# endif
# if defined _HAVE_GPIO_MODE_AF_PP
_TEST1(crl_cnf_bits, GPIO_Mode_AF_PP);
# endif

/* crl_bits (for inputs) */
#if defined _HAVE_GPIO_MODE_AIN
_TEST1(crl_bits, GPIO_Mode_AIN)
#endif
#if defined _HAVE_GPIO_MODE_IN_FLOATING
_TEST1(crl_bits, GPIO_Mode_IN_FLOATING)
#endif
#if defined _HAVE_GPIO_MODE_IPD
_TEST1(crl_bits, GPIO_Mode_IPD)
#endif
#if defined _HAVE_GPIO_MODE_IPU
_TEST1(crl_bits, GPIO_Mode_IPU)
#endif

/* crl_bits (for outputs) */
# if defined _HAVE_GPIO_MODE_Out_OD
#   if defined _HAVE_GPIO_SPEED_10MHz
_TEST2(crl_bits, GPIO_Mode_Out_OD, GPIO_Speed_10MHz);
#   endif
#   if defined _HAVE_GPIO_SPEED_2MHz
_TEST2(crl_bits, GPIO_Mode_Out_OD, GPIO_Speed_2MHz);
#   endif
#   if defined _HAVE_GPIO_SPEED_50MHz
_TEST2(crl_bits, GPIO_Mode_Out_OD, GPIO_Speed_50MHz);
#   endif
# endif
# if defined _HAVE_GPIO_MODE_Out_PP
#   if defined _HAVE_GPIO_SPEED_10MHz
_TEST2(crl_bits, GPIO_Mode_Out_PP, GPIO_Speed_10MHz);
#   endif
#   if defined _HAVE_GPIO_SPEED_2MHz
_TEST2(crl_bits, GPIO_Mode_Out_PP, GPIO_Speed_2MHz);
#   endif
#   if defined _HAVE_GPIO_SPEED_50MHz
_TEST2(crl_bits, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
#   endif
# endif
# if defined _HAVE_GPIO_MODE_AF_OD
#   if defined _HAVE_GPIO_SPEED_10MHz
_TEST2(crl_bits, GPIO_Mode_AF_OD, GPIO_Speed_10MHz);
#   endif
#   if defined _HAVE_GPIO_SPEED_2MHz
_TEST2(crl_bits, GPIO_Mode_AF_OD, GPIO_Speed_2MHz);
#   endif
#   if defined _HAVE_GPIO_SPEED_50MHz
_TEST2(crl_bits, GPIO_Mode_AF_OD, GPIO_Speed_50MHz);
#   endif
# endif
# if defined _HAVE_GPIO_MODE_AF_PP
#   if defined _HAVE_GPIO_SPEED_10MHz
_TEST2(crl_bits, GPIO_Mode_AF_PP, GPIO_Speed_10MHz);
#   endif
#   if defined _HAVE_GPIO_SPEED_2MHz
_TEST2(crl_bits, GPIO_Mode_AF_PP, GPIO_Speed_2MHz);
#   endif
#   if defined _HAVE_GPIO_SPEED_50MHz
_TEST2(crl_bits, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);
#   endif
# endif

/* crl_masked (for inputs) */
#if defined _HAVE_GPIO_MODE_AIN
_TEST1(crl_masked, GPIO_Mode_AIN)
#endif
#if defined _HAVE_GPIO_MODE_IN_FLOATING
_TEST1(crl_masked, GPIO_Mode_IN_FLOATING)
#endif
#if defined _HAVE_GPIO_MODE_IPD
_TEST1(crl_masked, GPIO_Mode_IPD)
#endif
#if defined _HAVE_GPIO_MODE_IPU
_TEST1(crl_masked, GPIO_Mode_IPU)
#endif

/* crl_masked (for outputs) */
# if defined _HAVE_GPIO_MODE_Out_OD
#   if defined _HAVE_GPIO_SPEED_10MHz
_TEST2(crl_masked, GPIO_Mode_Out_OD, GPIO_Speed_10MHz);
#   endif
#   if defined _HAVE_GPIO_SPEED_2MHz
_TEST2(crl_masked, GPIO_Mode_Out_OD, GPIO_Speed_2MHz);
#   endif
#   if defined _HAVE_GPIO_SPEED_50MHz
_TEST2(crl_masked, GPIO_Mode_Out_OD, GPIO_Speed_50MHz);
#   endif
# endif
# if defined _HAVE_GPIO_MODE_Out_PP
#   if defined _HAVE_GPIO_SPEED_10MHz
_TEST2(crl_masked, GPIO_Mode_Out_PP, GPIO_Speed_10MHz);
#   endif
#   if defined _HAVE_GPIO_SPEED_2MHz
_TEST2(crl_masked, GPIO_Mode_Out_PP, GPIO_Speed_2MHz);
#   endif
#   if defined _HAVE_GPIO_SPEED_50MHz
_TEST2(crl_masked, GPIO_Mode_Out_PP, GPIO_Speed_50MHz);
#   endif
# endif
# if defined _HAVE_GPIO_MODE_AF_OD
#   if defined _HAVE_GPIO_SPEED_10MHz
_TEST2(crl_masked, GPIO_Mode_AF_OD, GPIO_Speed_10MHz);
#   endif
#   if defined _HAVE_GPIO_SPEED_2MHz
_TEST2(crl_masked, GPIO_Mode_AF_OD, GPIO_Speed_2MHz);
#   endif
#   if defined _HAVE_GPIO_SPEED_50MHz
_TEST2(crl_masked, GPIO_Mode_AF_OD, GPIO_Speed_50MHz);
#   endif
# endif
# if defined _HAVE_GPIO_MODE_AF_PP
#   if defined _HAVE_GPIO_SPEED_10MHz
_TEST2(crl_masked, GPIO_Mode_AF_PP, GPIO_Speed_10MHz);
#   endif
#   if defined _HAVE_GPIO_SPEED_2MHz
_TEST2(crl_masked, GPIO_Mode_AF_PP, GPIO_Speed_2MHz);
#   endif
#   if defined _HAVE_GPIO_SPEED_50MHz
_TEST2(crl_masked, GPIO_Mode_AF_PP, GPIO_Speed_50MHz);
#   endif
# endif

/* crl_mix */
TEST(stm32xx__gpio__ct, crl_mix__with_no_args)
{
  using namespace stm32xx::gpio::ct;
  using stm32xx::bits::ct::get_bits;
  using stm32xx::bits::ct::get_mask;
  CHECK_EQUAL(0ul, get_bits<crl_mix<> >::value);
  CHECK_EQUAL(0ul, get_mask<crl_mix<> >::value);
};
TEST(stm32xx__gpio__ct, crl_mix__with_1_arg)
{
  using namespace stm32xx::gpio::ct;
  using stm32xx::bits::ct::get_bits;
  using stm32xx::bits::ct::get_mask;
  using arg1 = pin_conf<GPIO_Pin_0,GPIO_Mode_AIN>;
  constexpr uint32_t bits1 = crl_bits<GPIO_Pin_0,GPIO_Mode_AIN>::value;
  constexpr uint32_t mask1 = crl_mask<GPIO_Pin_0>::value;
  CHECK_EQUAL(bits1, (get_bits<crl_mix<arg1> >::value));
  CHECK_EQUAL(mask1, (get_mask<crl_mix<arg1> >::value));
};
TEST(stm32xx__gpio__ct, crl_mix__with_2_args)
{
  using namespace stm32xx::gpio::ct;
  using stm32xx::bits::ct::get_bits;
  using stm32xx::bits::ct::get_mask;
  using arg1 = pin_conf<GPIO_Pin_1,GPIO_Mode_Out_PP,GPIO_Speed_10MHz>;
  using arg2 = pin_conf<GPIO_Pin_0,GPIO_Mode_AIN>;
  constexpr uint32_t bits1 = crl_bits<GPIO_Pin_1,GPIO_Mode_Out_PP,GPIO_Speed_10MHz>::value;
  constexpr uint32_t mask1 = crl_mask<GPIO_Pin_1>::value;
  constexpr uint32_t bits2 = crl_bits<GPIO_Pin_0,GPIO_Mode_AIN>::value;
  constexpr uint32_t mask2 = crl_mask<GPIO_Pin_0>::value;
  CHECK_EQUAL(bits1|bits2, (get_bits<crl_mix<arg1,arg2> >::value));
  CHECK_EQUAL(mask1|mask2, (get_mask<crl_mix<arg1,arg2> >::value));
};

TEST(stm32xx__gpio__ct, configure_gpio__1)
{
  using namespace stm32xx::gpio::ct;
  typedef gpio_conf<
    pin_conf<GPIO_Pin_0 | GPIO_Pin_4, GPIO_Mode_Out_PP, GPIO_Speed_10MHz>
  , pin_conf<GPIO_Pin_1, GPIO_Mode_AIN> 
  >  my_gpio_conf;
  /* FIXME: don't touch hardware (GPIOA)! */
  set<my_gpio_conf>::in(GPIOA);
}

#endif /* _HAVE_GPIO_CRL_REGISTER */
