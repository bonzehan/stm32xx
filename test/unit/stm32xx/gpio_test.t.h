/*
 * Copyright (c) 2013 by Pawel Tomulik <ptomulik@meil.pw.edu.pl>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE
 */

/** // doc: test/unit/stm32xx/gpio_test.t.h {{{
 * @file test/unit/stm32xx/gpio_test.t.h
 * @todo Write documentation
 */ // }}}

#include <stm32xx/gpio.hpp>
#include <cxxtest/TestSuite.h>

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


class stm32xx__gpio__ct__testsuite : public CxxTest::TestSuite
  {
      template <GPIOMode_TypeDef _mode> 
      struct check_crl_cnf_bits
      {
        static void apply()
        {
          using namespace stm32xx::gpio::ct;
          TS_ASSERT_EQUALS(((_mode & 0x0Cul) << 0x00), (crl_cnf_bits<GPIO_Pin_0, _mode>::value));
          TS_ASSERT_EQUALS(((_mode & 0x0Cul) << 0x04), (crl_cnf_bits<GPIO_Pin_1, _mode>::value));
          TS_ASSERT_EQUALS(((_mode & 0x0Cul) << 0x08), (crl_cnf_bits<GPIO_Pin_2, _mode>::value));
          TS_ASSERT_EQUALS(((_mode & 0x0Cul) << 0x0C), (crl_cnf_bits<GPIO_Pin_3, _mode>::value));
          TS_ASSERT_EQUALS(((_mode & 0x0Cul) << 0x10), (crl_cnf_bits<GPIO_Pin_4, _mode>::value));
          TS_ASSERT_EQUALS(((_mode & 0x0Cul) << 0x14), (crl_cnf_bits<GPIO_Pin_5, _mode>::value));
          TS_ASSERT_EQUALS(((_mode & 0x0Cul) << 0x18), (crl_cnf_bits<GPIO_Pin_6, _mode>::value));
          TS_ASSERT_EQUALS(((_mode & 0x0Cul) << 0x1C), (crl_cnf_bits<GPIO_Pin_7, _mode>::value));
          TS_ASSERT_EQUALS(0ul,                        (crl_cnf_bits<GPIO_Pin_8, _mode>::value));
          TS_ASSERT_EQUALS(0ul,                        (crl_cnf_bits<GPIO_Pin_9, _mode>::value));
          TS_ASSERT_EQUALS(0ul,                        (crl_cnf_bits<GPIO_Pin_10,_mode>::value));
          TS_ASSERT_EQUALS(0ul,                        (crl_cnf_bits<GPIO_Pin_11,_mode>::value));
          TS_ASSERT_EQUALS(0ul,                        (crl_cnf_bits<GPIO_Pin_12,_mode>::value));
          TS_ASSERT_EQUALS(0ul,                        (crl_cnf_bits<GPIO_Pin_13,_mode>::value));
          TS_ASSERT_EQUALS(0ul,                        (crl_cnf_bits<GPIO_Pin_14,_mode>::value));
          TS_ASSERT_EQUALS(0ul,                        (crl_cnf_bits<GPIO_Pin_15,_mode>::value));
        }
      };
      
      template <GPIOMode_TypeDef _mode> 
      struct check_crh_cnf_bits
      {
        static void apply()
        {
          using namespace stm32xx::gpio::ct;
          TS_ASSERT_EQUALS(0ul,                        (crh_cnf_bits<GPIO_Pin_0, _mode>::value));
          TS_ASSERT_EQUALS(0ul,                        (crh_cnf_bits<GPIO_Pin_1, _mode>::value));
          TS_ASSERT_EQUALS(0ul,                        (crh_cnf_bits<GPIO_Pin_2, _mode>::value));
          TS_ASSERT_EQUALS(0ul,                        (crh_cnf_bits<GPIO_Pin_3, _mode>::value));
          TS_ASSERT_EQUALS(0ul,                        (crh_cnf_bits<GPIO_Pin_4, _mode>::value));
          TS_ASSERT_EQUALS(0ul,                        (crh_cnf_bits<GPIO_Pin_5, _mode>::value));
          TS_ASSERT_EQUALS(0ul,                        (crh_cnf_bits<GPIO_Pin_6, _mode>::value));
          TS_ASSERT_EQUALS(0ul,                        (crh_cnf_bits<GPIO_Pin_7, _mode>::value));
          TS_ASSERT_EQUALS(((_mode & 0x0Cul) << 0x00), (crh_cnf_bits<GPIO_Pin_8, _mode>::value));
          TS_ASSERT_EQUALS(((_mode & 0x0Cul) << 0x04), (crh_cnf_bits<GPIO_Pin_9, _mode>::value));
          TS_ASSERT_EQUALS(((_mode & 0x0Cul) << 0x08), (crh_cnf_bits<GPIO_Pin_10,_mode>::value));
          TS_ASSERT_EQUALS(((_mode & 0x0Cul) << 0x0C), (crh_cnf_bits<GPIO_Pin_11,_mode>::value));
          TS_ASSERT_EQUALS(((_mode & 0x0Cul) << 0x10), (crh_cnf_bits<GPIO_Pin_12,_mode>::value));
          TS_ASSERT_EQUALS(((_mode & 0x0Cul) << 0x14), (crh_cnf_bits<GPIO_Pin_13,_mode>::value));
          TS_ASSERT_EQUALS(((_mode & 0x0Cul) << 0x18), (crh_cnf_bits<GPIO_Pin_14,_mode>::value));
          TS_ASSERT_EQUALS(((_mode & 0x0Cul) << 0x1C), (crh_cnf_bits<GPIO_Pin_15,_mode>::value));
        }
      };

      static void 
      check_crl_cnf_mask()
      {
          using namespace stm32xx::gpio::ct;
          TS_ASSERT_EQUALS((0x0Cul << 0x00), (crl_cnf_mask<GPIO_Pin_0 >::value));
          TS_ASSERT_EQUALS((0x0Cul << 0x04), (crl_cnf_mask<GPIO_Pin_1 >::value));
          TS_ASSERT_EQUALS((0x0Cul << 0x08), (crl_cnf_mask<GPIO_Pin_2 >::value));
          TS_ASSERT_EQUALS((0x0Cul << 0x0C), (crl_cnf_mask<GPIO_Pin_3 >::value));
          TS_ASSERT_EQUALS((0x0Cul << 0x10), (crl_cnf_mask<GPIO_Pin_4 >::value));
          TS_ASSERT_EQUALS((0x0Cul << 0x14), (crl_cnf_mask<GPIO_Pin_5 >::value));
          TS_ASSERT_EQUALS((0x0Cul << 0x18), (crl_cnf_mask<GPIO_Pin_6 >::value));
          TS_ASSERT_EQUALS((0x0Cul << 0x1C), (crl_cnf_mask<GPIO_Pin_7 >::value));
          TS_ASSERT_EQUALS(0ul,              (crl_cnf_mask<GPIO_Pin_8 >::value));
          TS_ASSERT_EQUALS(0ul,              (crl_cnf_mask<GPIO_Pin_9 >::value));
          TS_ASSERT_EQUALS(0ul,              (crl_cnf_mask<GPIO_Pin_10>::value));
          TS_ASSERT_EQUALS(0ul,              (crl_cnf_mask<GPIO_Pin_11>::value));
          TS_ASSERT_EQUALS(0ul,              (crl_cnf_mask<GPIO_Pin_12>::value));
          TS_ASSERT_EQUALS(0ul,              (crl_cnf_mask<GPIO_Pin_13>::value));
          TS_ASSERT_EQUALS(0ul,              (crl_cnf_mask<GPIO_Pin_14>::value));
          TS_ASSERT_EQUALS(0ul,              (crl_cnf_mask<GPIO_Pin_15>::value));
      }

      static void 
      check_crh_cnf_mask()
      {
          using namespace stm32xx::gpio::ct;
          TS_ASSERT_EQUALS(0ul,              (crh_cnf_mask<GPIO_Pin_0 >::value));
          TS_ASSERT_EQUALS(0ul,              (crh_cnf_mask<GPIO_Pin_1 >::value));
          TS_ASSERT_EQUALS(0ul,              (crh_cnf_mask<GPIO_Pin_2 >::value));
          TS_ASSERT_EQUALS(0ul,              (crh_cnf_mask<GPIO_Pin_3 >::value));
          TS_ASSERT_EQUALS(0ul,              (crh_cnf_mask<GPIO_Pin_4 >::value));
          TS_ASSERT_EQUALS(0ul,              (crh_cnf_mask<GPIO_Pin_5 >::value));
          TS_ASSERT_EQUALS(0ul,              (crh_cnf_mask<GPIO_Pin_6 >::value));
          TS_ASSERT_EQUALS(0ul,              (crh_cnf_mask<GPIO_Pin_7 >::value));
          TS_ASSERT_EQUALS((0x0Cul << 0x00), (crh_cnf_mask<GPIO_Pin_8 >::value));
          TS_ASSERT_EQUALS((0x0Cul << 0x04), (crh_cnf_mask<GPIO_Pin_9 >::value));
          TS_ASSERT_EQUALS((0x0Cul << 0x08), (crh_cnf_mask<GPIO_Pin_10>::value));
          TS_ASSERT_EQUALS((0x0Cul << 0x0C), (crh_cnf_mask<GPIO_Pin_11>::value));
          TS_ASSERT_EQUALS((0x0Cul << 0x10), (crh_cnf_mask<GPIO_Pin_12>::value));
          TS_ASSERT_EQUALS((0x0Cul << 0x14), (crh_cnf_mask<GPIO_Pin_13>::value));
          TS_ASSERT_EQUALS((0x0Cul << 0x18), (crh_cnf_mask<GPIO_Pin_14>::value));
          TS_ASSERT_EQUALS((0x0Cul << 0x1C), (crh_cnf_mask<GPIO_Pin_15>::value));
      }

      template <GPIOSpeed_TypeDef _speed> 
      struct check_crl_mode_bits
      {
        static void apply()
        {
          using namespace stm32xx::gpio::ct;
          TS_ASSERT_EQUALS(((_speed & 0x03ul) << 0x00), (crl_mode_bits<GPIO_Pin_0, _speed>::value));
          TS_ASSERT_EQUALS(((_speed & 0x03ul) << 0x04), (crl_mode_bits<GPIO_Pin_1, _speed>::value));
          TS_ASSERT_EQUALS(((_speed & 0x03ul) << 0x08), (crl_mode_bits<GPIO_Pin_2, _speed>::value));
          TS_ASSERT_EQUALS(((_speed & 0x03ul) << 0x0C), (crl_mode_bits<GPIO_Pin_3, _speed>::value));
          TS_ASSERT_EQUALS(((_speed & 0x03ul) << 0x10), (crl_mode_bits<GPIO_Pin_4, _speed>::value));
          TS_ASSERT_EQUALS(((_speed & 0x03ul) << 0x14), (crl_mode_bits<GPIO_Pin_5, _speed>::value));
          TS_ASSERT_EQUALS(((_speed & 0x03ul) << 0x18), (crl_mode_bits<GPIO_Pin_6, _speed>::value));
          TS_ASSERT_EQUALS(((_speed & 0x03ul) << 0x1C), (crl_mode_bits<GPIO_Pin_7, _speed>::value));
          TS_ASSERT_EQUALS(0ul,                         (crl_mode_bits<GPIO_Pin_8, _speed>::value));
          TS_ASSERT_EQUALS(0ul,                         (crl_mode_bits<GPIO_Pin_9, _speed>::value));
          TS_ASSERT_EQUALS(0ul,                         (crl_mode_bits<GPIO_Pin_10,_speed>::value));
          TS_ASSERT_EQUALS(0ul,                         (crl_mode_bits<GPIO_Pin_11,_speed>::value));
          TS_ASSERT_EQUALS(0ul,                         (crl_mode_bits<GPIO_Pin_12,_speed>::value));
          TS_ASSERT_EQUALS(0ul,                         (crl_mode_bits<GPIO_Pin_13,_speed>::value));
          TS_ASSERT_EQUALS(0ul,                         (crl_mode_bits<GPIO_Pin_14,_speed>::value));
          TS_ASSERT_EQUALS(0ul,                         (crl_mode_bits<GPIO_Pin_15,_speed>::value));
        }
      };
      
      template <GPIOSpeed_TypeDef _speed> 
      struct check_crh_mode_bits
      {
        static void apply()
        {
          using namespace stm32xx::gpio::ct;
          TS_ASSERT_EQUALS(0ul,                         (crh_mode_bits<GPIO_Pin_0, _speed>::value));
          TS_ASSERT_EQUALS(0ul,                         (crh_mode_bits<GPIO_Pin_1, _speed>::value));
          TS_ASSERT_EQUALS(0ul,                         (crh_mode_bits<GPIO_Pin_2, _speed>::value));
          TS_ASSERT_EQUALS(0ul,                         (crh_mode_bits<GPIO_Pin_3, _speed>::value));
          TS_ASSERT_EQUALS(0ul,                         (crh_mode_bits<GPIO_Pin_4, _speed>::value));
          TS_ASSERT_EQUALS(0ul,                         (crh_mode_bits<GPIO_Pin_5, _speed>::value));
          TS_ASSERT_EQUALS(0ul,                         (crh_mode_bits<GPIO_Pin_6, _speed>::value));
          TS_ASSERT_EQUALS(0ul,                         (crh_mode_bits<GPIO_Pin_7, _speed>::value));
          TS_ASSERT_EQUALS(((_speed & 0x03ul) << 0x00), (crh_mode_bits<GPIO_Pin_8, _speed>::value));
          TS_ASSERT_EQUALS(((_speed & 0x03ul) << 0x04), (crh_mode_bits<GPIO_Pin_9, _speed>::value));
          TS_ASSERT_EQUALS(((_speed & 0x03ul) << 0x08), (crh_mode_bits<GPIO_Pin_10,_speed>::value));
          TS_ASSERT_EQUALS(((_speed & 0x03ul) << 0x0C), (crh_mode_bits<GPIO_Pin_11,_speed>::value));
          TS_ASSERT_EQUALS(((_speed & 0x03ul) << 0x10), (crh_mode_bits<GPIO_Pin_12,_speed>::value));
          TS_ASSERT_EQUALS(((_speed & 0x03ul) << 0x14), (crh_mode_bits<GPIO_Pin_13,_speed>::value));
          TS_ASSERT_EQUALS(((_speed & 0x03ul) << 0x18), (crh_mode_bits<GPIO_Pin_14,_speed>::value));
          TS_ASSERT_EQUALS(((_speed & 0x03ul) << 0x1C), (crh_mode_bits<GPIO_Pin_15,_speed>::value));
        }
      };

      static void 
      check_crl_mode_mask()
      {
          using namespace stm32xx::gpio::ct;
          TS_ASSERT_EQUALS((0x03ul << 0x00), (crl_mode_mask<GPIO_Pin_0 >::value));
          TS_ASSERT_EQUALS((0x03ul << 0x04), (crl_mode_mask<GPIO_Pin_1 >::value));
          TS_ASSERT_EQUALS((0x03ul << 0x08), (crl_mode_mask<GPIO_Pin_2 >::value));
          TS_ASSERT_EQUALS((0x03ul << 0x0C), (crl_mode_mask<GPIO_Pin_3 >::value));
          TS_ASSERT_EQUALS((0x03ul << 0x10), (crl_mode_mask<GPIO_Pin_4 >::value));
          TS_ASSERT_EQUALS((0x03ul << 0x14), (crl_mode_mask<GPIO_Pin_5 >::value));
          TS_ASSERT_EQUALS((0x03ul << 0x18), (crl_mode_mask<GPIO_Pin_6 >::value));
          TS_ASSERT_EQUALS((0x03ul << 0x1C), (crl_mode_mask<GPIO_Pin_7 >::value));
          TS_ASSERT_EQUALS(0ul,              (crl_mode_mask<GPIO_Pin_8 >::value));
          TS_ASSERT_EQUALS(0ul,              (crl_mode_mask<GPIO_Pin_9 >::value));
          TS_ASSERT_EQUALS(0ul,              (crl_mode_mask<GPIO_Pin_10>::value));
          TS_ASSERT_EQUALS(0ul,              (crl_mode_mask<GPIO_Pin_11>::value));
          TS_ASSERT_EQUALS(0ul,              (crl_mode_mask<GPIO_Pin_12>::value));
          TS_ASSERT_EQUALS(0ul,              (crl_mode_mask<GPIO_Pin_13>::value));
          TS_ASSERT_EQUALS(0ul,              (crl_mode_mask<GPIO_Pin_14>::value));
          TS_ASSERT_EQUALS(0ul,              (crl_mode_mask<GPIO_Pin_15>::value));
      }

      static void 
      check_crh_mode_mask()
      {
          using namespace stm32xx::gpio::ct;
          TS_ASSERT_EQUALS(0ul,              (crh_mode_mask<GPIO_Pin_0 >::value));
          TS_ASSERT_EQUALS(0ul,              (crh_mode_mask<GPIO_Pin_1 >::value));
          TS_ASSERT_EQUALS(0ul,              (crh_mode_mask<GPIO_Pin_2 >::value));
          TS_ASSERT_EQUALS(0ul,              (crh_mode_mask<GPIO_Pin_3 >::value));
          TS_ASSERT_EQUALS(0ul,              (crh_mode_mask<GPIO_Pin_4 >::value));
          TS_ASSERT_EQUALS(0ul,              (crh_mode_mask<GPIO_Pin_5 >::value));
          TS_ASSERT_EQUALS(0ul,              (crh_mode_mask<GPIO_Pin_6 >::value));
          TS_ASSERT_EQUALS(0ul,              (crh_mode_mask<GPIO_Pin_7 >::value));
          TS_ASSERT_EQUALS((0x03ul << 0x00), (crh_mode_mask<GPIO_Pin_8 >::value));
          TS_ASSERT_EQUALS((0x03ul << 0x04), (crh_mode_mask<GPIO_Pin_9 >::value));
          TS_ASSERT_EQUALS((0x03ul << 0x08), (crh_mode_mask<GPIO_Pin_10>::value));
          TS_ASSERT_EQUALS((0x03ul << 0x0C), (crh_mode_mask<GPIO_Pin_11>::value));
          TS_ASSERT_EQUALS((0x03ul << 0x10), (crh_mode_mask<GPIO_Pin_12>::value));
          TS_ASSERT_EQUALS((0x03ul << 0x14), (crh_mode_mask<GPIO_Pin_13>::value));
          TS_ASSERT_EQUALS((0x03ul << 0x18), (crh_mode_mask<GPIO_Pin_14>::value));
          TS_ASSERT_EQUALS((0x03ul << 0x1C), (crh_mode_mask<GPIO_Pin_15>::value));
      }

      template <GPIOMode_TypeDef _mode, GPIOSpeed_TypeDef _speed=(GPIOSpeed_TypeDef)0>
        struct check_crl_bits
        {
          static void
          apply()
          {
            using namespace stm32xx::gpio::ct;
            constexpr uint32_t _ms = (_mode & 0x0Cul)|(_speed & 0x03ul);
            TS_ASSERT_EQUALS((_ms << 0x00), (crl_bits<GPIO_Pin_0, _mode,_speed>::value));
            TS_ASSERT_EQUALS((_ms << 0x04), (crl_bits<GPIO_Pin_1, _mode,_speed>::value));
            TS_ASSERT_EQUALS((_ms << 0x08), (crl_bits<GPIO_Pin_2, _mode,_speed>::value));
            TS_ASSERT_EQUALS((_ms << 0x0C), (crl_bits<GPIO_Pin_3, _mode,_speed>::value));
            TS_ASSERT_EQUALS((_ms << 0x10), (crl_bits<GPIO_Pin_4, _mode,_speed>::value));
            TS_ASSERT_EQUALS((_ms << 0x14), (crl_bits<GPIO_Pin_5, _mode,_speed>::value));
            TS_ASSERT_EQUALS((_ms << 0x18), (crl_bits<GPIO_Pin_6, _mode,_speed>::value));
            TS_ASSERT_EQUALS((_ms << 0x1C), (crl_bits<GPIO_Pin_7, _mode,_speed>::value));
            TS_ASSERT_EQUALS(0ul,           (crl_bits<GPIO_Pin_8, _mode,_speed>::value));
            TS_ASSERT_EQUALS(0ul,           (crl_bits<GPIO_Pin_9, _mode,_speed>::value));
            TS_ASSERT_EQUALS(0ul,           (crl_bits<GPIO_Pin_10,_mode,_speed>::value));
            TS_ASSERT_EQUALS(0ul,           (crl_bits<GPIO_Pin_11,_mode,_speed>::value));
            TS_ASSERT_EQUALS(0ul,           (crl_bits<GPIO_Pin_12,_mode,_speed>::value));
            TS_ASSERT_EQUALS(0ul,           (crl_bits<GPIO_Pin_13,_mode,_speed>::value));
            TS_ASSERT_EQUALS(0ul,           (crl_bits<GPIO_Pin_14,_mode,_speed>::value));
            TS_ASSERT_EQUALS(0ul,           (crl_bits<GPIO_Pin_15,_mode,_speed>::value));
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
            TS_ASSERT_EQUALS((_ms << 0x00), (crl_bits<GPIO_Pin_0, _mode>::value));
            TS_ASSERT_EQUALS((_ms << 0x04), (crl_bits<GPIO_Pin_1, _mode>::value));
            TS_ASSERT_EQUALS((_ms << 0x08), (crl_bits<GPIO_Pin_2, _mode>::value));
            TS_ASSERT_EQUALS((_ms << 0x0C), (crl_bits<GPIO_Pin_3, _mode>::value));
            TS_ASSERT_EQUALS((_ms << 0x10), (crl_bits<GPIO_Pin_4, _mode>::value));
            TS_ASSERT_EQUALS((_ms << 0x14), (crl_bits<GPIO_Pin_5, _mode>::value));
            TS_ASSERT_EQUALS((_ms << 0x18), (crl_bits<GPIO_Pin_6, _mode>::value));
            TS_ASSERT_EQUALS((_ms << 0x1C), (crl_bits<GPIO_Pin_7, _mode>::value));
            TS_ASSERT_EQUALS(0ul,           (crl_bits<GPIO_Pin_8, _mode>::value));
            TS_ASSERT_EQUALS(0ul,           (crl_bits<GPIO_Pin_9, _mode>::value));
            TS_ASSERT_EQUALS(0ul,           (crl_bits<GPIO_Pin_10,_mode>::value));
            TS_ASSERT_EQUALS(0ul,           (crl_bits<GPIO_Pin_11,_mode>::value));
            TS_ASSERT_EQUALS(0ul,           (crl_bits<GPIO_Pin_12,_mode>::value));
            TS_ASSERT_EQUALS(0ul,           (crl_bits<GPIO_Pin_13,_mode>::value));
            TS_ASSERT_EQUALS(0ul,           (crl_bits<GPIO_Pin_14,_mode>::value));
            TS_ASSERT_EQUALS(0ul,           (crl_bits<GPIO_Pin_15,_mode>::value));
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
            TS_ASSERT_EQUALS(0ul,           (crh_bits<GPIO_Pin_0, _mode,_speed>::value));
            TS_ASSERT_EQUALS(0ul,           (crh_bits<GPIO_Pin_1, _mode,_speed>::value));
            TS_ASSERT_EQUALS(0ul,           (crh_bits<GPIO_Pin_2, _mode,_speed>::value));
            TS_ASSERT_EQUALS(0ul,           (crh_bits<GPIO_Pin_3, _mode,_speed>::value));
            TS_ASSERT_EQUALS(0ul,           (crh_bits<GPIO_Pin_4, _mode,_speed>::value));
            TS_ASSERT_EQUALS(0ul,           (crh_bits<GPIO_Pin_5, _mode,_speed>::value));
            TS_ASSERT_EQUALS(0ul,           (crh_bits<GPIO_Pin_6, _mode,_speed>::value));
            TS_ASSERT_EQUALS(0ul,           (crh_bits<GPIO_Pin_7, _mode,_speed>::value));
            TS_ASSERT_EQUALS((_ms << 0x00), (crh_bits<GPIO_Pin_8, _mode,_speed>::value));
            TS_ASSERT_EQUALS((_ms << 0x04), (crh_bits<GPIO_Pin_9, _mode,_speed>::value));
            TS_ASSERT_EQUALS((_ms << 0x08), (crh_bits<GPIO_Pin_10,_mode,_speed>::value));
            TS_ASSERT_EQUALS((_ms << 0x0C), (crh_bits<GPIO_Pin_11,_mode,_speed>::value));
            TS_ASSERT_EQUALS((_ms << 0x10), (crh_bits<GPIO_Pin_12,_mode,_speed>::value));
            TS_ASSERT_EQUALS((_ms << 0x14), (crh_bits<GPIO_Pin_13,_mode,_speed>::value));
            TS_ASSERT_EQUALS((_ms << 0x18), (crh_bits<GPIO_Pin_14,_mode,_speed>::value));
            TS_ASSERT_EQUALS((_ms << 0x1C), (crh_bits<GPIO_Pin_15,_mode,_speed>::value));
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
            TS_ASSERT_EQUALS(0ul,           (crh_bits<GPIO_Pin_0, _mode>::value));
            TS_ASSERT_EQUALS(0ul,           (crh_bits<GPIO_Pin_1, _mode>::value));
            TS_ASSERT_EQUALS(0ul,           (crh_bits<GPIO_Pin_2, _mode>::value));
            TS_ASSERT_EQUALS(0ul,           (crh_bits<GPIO_Pin_3, _mode>::value));
            TS_ASSERT_EQUALS(0ul,           (crh_bits<GPIO_Pin_4, _mode>::value));
            TS_ASSERT_EQUALS(0ul,           (crh_bits<GPIO_Pin_5, _mode>::value));
            TS_ASSERT_EQUALS(0ul,           (crh_bits<GPIO_Pin_6, _mode>::value));
            TS_ASSERT_EQUALS(0ul,           (crh_bits<GPIO_Pin_7, _mode>::value));
            TS_ASSERT_EQUALS((_ms << 0x00), (crh_bits<GPIO_Pin_8, _mode>::value));
            TS_ASSERT_EQUALS((_ms << 0x04), (crh_bits<GPIO_Pin_9, _mode>::value));
            TS_ASSERT_EQUALS((_ms << 0x08), (crh_bits<GPIO_Pin_10,_mode>::value));
            TS_ASSERT_EQUALS((_ms << 0x0C), (crh_bits<GPIO_Pin_11,_mode>::value));
            TS_ASSERT_EQUALS((_ms << 0x10), (crh_bits<GPIO_Pin_12,_mode>::value));
            TS_ASSERT_EQUALS((_ms << 0x14), (crh_bits<GPIO_Pin_13,_mode>::value));
            TS_ASSERT_EQUALS((_ms << 0x18), (crh_bits<GPIO_Pin_14,_mode>::value));
            TS_ASSERT_EQUALS((_ms << 0x1C), (crh_bits<GPIO_Pin_15,_mode>::value));
          }
        };

      static void 
      check_crl_mask()
      {
          using namespace stm32xx::gpio::ct;
          TS_ASSERT_EQUALS((0x0Ful << 0x00), (crl_mask<GPIO_Pin_0 >::value));
          TS_ASSERT_EQUALS((0x0Ful << 0x04), (crl_mask<GPIO_Pin_1 >::value));
          TS_ASSERT_EQUALS((0x0Ful << 0x08), (crl_mask<GPIO_Pin_2 >::value));
          TS_ASSERT_EQUALS((0x0Ful << 0x0C), (crl_mask<GPIO_Pin_3 >::value));
          TS_ASSERT_EQUALS((0x0Ful << 0x10), (crl_mask<GPIO_Pin_4 >::value));
          TS_ASSERT_EQUALS((0x0Ful << 0x14), (crl_mask<GPIO_Pin_5 >::value));
          TS_ASSERT_EQUALS((0x0Ful << 0x18), (crl_mask<GPIO_Pin_6 >::value));
          TS_ASSERT_EQUALS((0x0Ful << 0x1C), (crl_mask<GPIO_Pin_7 >::value));
          TS_ASSERT_EQUALS(0ul,              (crl_mask<GPIO_Pin_8 >::value));
          TS_ASSERT_EQUALS(0ul,              (crl_mask<GPIO_Pin_9 >::value));
          TS_ASSERT_EQUALS(0ul,              (crl_mask<GPIO_Pin_10>::value));
          TS_ASSERT_EQUALS(0ul,              (crl_mask<GPIO_Pin_11>::value));
          TS_ASSERT_EQUALS(0ul,              (crl_mask<GPIO_Pin_12>::value));
          TS_ASSERT_EQUALS(0ul,              (crl_mask<GPIO_Pin_13>::value));
          TS_ASSERT_EQUALS(0ul,              (crl_mask<GPIO_Pin_14>::value));
          TS_ASSERT_EQUALS(0ul,              (crl_mask<GPIO_Pin_15>::value));
      }

      static void 
      check_crh_mask()
      {
          using namespace stm32xx::gpio::ct;
          TS_ASSERT_EQUALS(0ul,              (crh_mask<GPIO_Pin_0 >::value));
          TS_ASSERT_EQUALS(0ul,              (crh_mask<GPIO_Pin_1 >::value));
          TS_ASSERT_EQUALS(0ul,              (crh_mask<GPIO_Pin_2 >::value));
          TS_ASSERT_EQUALS(0ul,              (crh_mask<GPIO_Pin_3 >::value));
          TS_ASSERT_EQUALS(0ul,              (crh_mask<GPIO_Pin_4 >::value));
          TS_ASSERT_EQUALS(0ul,              (crh_mask<GPIO_Pin_5 >::value));
          TS_ASSERT_EQUALS(0ul,              (crh_mask<GPIO_Pin_6 >::value));
          TS_ASSERT_EQUALS(0ul,              (crh_mask<GPIO_Pin_7 >::value));
          TS_ASSERT_EQUALS((0x0Ful << 0x00), (crh_mask<GPIO_Pin_8 >::value));
          TS_ASSERT_EQUALS((0x0Ful << 0x04), (crh_mask<GPIO_Pin_9 >::value));
          TS_ASSERT_EQUALS((0x0Ful << 0x08), (crh_mask<GPIO_Pin_10>::value));
          TS_ASSERT_EQUALS((0x0Ful << 0x0C), (crh_mask<GPIO_Pin_11>::value));
          TS_ASSERT_EQUALS((0x0Ful << 0x10), (crh_mask<GPIO_Pin_12>::value));
          TS_ASSERT_EQUALS((0x0Ful << 0x14), (crh_mask<GPIO_Pin_13>::value));
          TS_ASSERT_EQUALS((0x0Ful << 0x18), (crh_mask<GPIO_Pin_14>::value));
          TS_ASSERT_EQUALS((0x0Ful << 0x1C), (crh_mask<GPIO_Pin_15>::value));
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

            TS_ASSERT_EQUALS((crl_bits<GPIO_Pin_0, _mode,_speed>::value), (get_bits<_m0>::value));
            TS_ASSERT_EQUALS((crl_bits<GPIO_Pin_1, _mode,_speed>::value), (get_bits<_m1>::value));
            TS_ASSERT_EQUALS((crl_bits<GPIO_Pin_2, _mode,_speed>::value), (get_bits<_m2>::value));
            TS_ASSERT_EQUALS((crl_bits<GPIO_Pin_3, _mode,_speed>::value), (get_bits<_m3>::value));
            TS_ASSERT_EQUALS((crl_bits<GPIO_Pin_4, _mode,_speed>::value), (get_bits<_m4>::value));
            TS_ASSERT_EQUALS((crl_bits<GPIO_Pin_5, _mode,_speed>::value), (get_bits<_m5>::value));
            TS_ASSERT_EQUALS((crl_bits<GPIO_Pin_6, _mode,_speed>::value), (get_bits<_m6>::value));
            TS_ASSERT_EQUALS((crl_bits<GPIO_Pin_7, _mode,_speed>::value), (get_bits<_m7>::value));
            TS_ASSERT_EQUALS((crl_bits<GPIO_Pin_8, _mode,_speed>::value), (get_bits<_m8>::value));
            TS_ASSERT_EQUALS((crl_bits<GPIO_Pin_9, _mode,_speed>::value), (get_bits<_m9>::value));
            TS_ASSERT_EQUALS((crl_bits<GPIO_Pin_10,_mode,_speed>::value), (get_bits<_m10>::value));
            TS_ASSERT_EQUALS((crl_bits<GPIO_Pin_11,_mode,_speed>::value), (get_bits<_m11>::value));
            TS_ASSERT_EQUALS((crl_bits<GPIO_Pin_12,_mode,_speed>::value), (get_bits<_m12>::value));
            TS_ASSERT_EQUALS((crl_bits<GPIO_Pin_13,_mode,_speed>::value), (get_bits<_m13>::value));
            TS_ASSERT_EQUALS((crl_bits<GPIO_Pin_14,_mode,_speed>::value), (get_bits<_m14>::value));
            TS_ASSERT_EQUALS((crl_bits<GPIO_Pin_15,_mode,_speed>::value), (get_bits<_m15>::value));

            TS_ASSERT_EQUALS((crl_mask<GPIO_Pin_0>::value),  (get_mask<_m0>::value));
            TS_ASSERT_EQUALS((crl_mask<GPIO_Pin_1>::value),  (get_mask<_m1>::value));
            TS_ASSERT_EQUALS((crl_mask<GPIO_Pin_2>::value),  (get_mask<_m2>::value));
            TS_ASSERT_EQUALS((crl_mask<GPIO_Pin_3>::value),  (get_mask<_m3>::value));
            TS_ASSERT_EQUALS((crl_mask<GPIO_Pin_4>::value),  (get_mask<_m4>::value));
            TS_ASSERT_EQUALS((crl_mask<GPIO_Pin_5>::value),  (get_mask<_m5>::value));
            TS_ASSERT_EQUALS((crl_mask<GPIO_Pin_6>::value),  (get_mask<_m6>::value));
            TS_ASSERT_EQUALS((crl_mask<GPIO_Pin_7>::value),  (get_mask<_m7>::value));
            TS_ASSERT_EQUALS((crl_mask<GPIO_Pin_8>::value),  (get_mask<_m8>::value));
            TS_ASSERT_EQUALS((crl_mask<GPIO_Pin_9>::value),  (get_mask<_m9>::value));
            TS_ASSERT_EQUALS((crl_mask<GPIO_Pin_10>::value), (get_mask<_m10>::value));
            TS_ASSERT_EQUALS((crl_mask<GPIO_Pin_11>::value), (get_mask<_m11>::value));
            TS_ASSERT_EQUALS((crl_mask<GPIO_Pin_12>::value), (get_mask<_m12>::value));
            TS_ASSERT_EQUALS((crl_mask<GPIO_Pin_13>::value), (get_mask<_m13>::value));
            TS_ASSERT_EQUALS((crl_mask<GPIO_Pin_14>::value), (get_mask<_m14>::value));
            TS_ASSERT_EQUALS((crl_mask<GPIO_Pin_15>::value), (get_mask<_m15>::value));
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

            TS_ASSERT_EQUALS((crl_bits<GPIO_Pin_0, _mode>::value), (get_bits<_m0>::value));
            TS_ASSERT_EQUALS((crl_bits<GPIO_Pin_1, _mode>::value), (get_bits<_m1>::value));
            TS_ASSERT_EQUALS((crl_bits<GPIO_Pin_2, _mode>::value), (get_bits<_m2>::value));
            TS_ASSERT_EQUALS((crl_bits<GPIO_Pin_3, _mode>::value), (get_bits<_m3>::value));
            TS_ASSERT_EQUALS((crl_bits<GPIO_Pin_4, _mode>::value), (get_bits<_m4>::value));
            TS_ASSERT_EQUALS((crl_bits<GPIO_Pin_5, _mode>::value), (get_bits<_m5>::value));
            TS_ASSERT_EQUALS((crl_bits<GPIO_Pin_6, _mode>::value), (get_bits<_m6>::value));
            TS_ASSERT_EQUALS((crl_bits<GPIO_Pin_7, _mode>::value), (get_bits<_m7>::value));
            TS_ASSERT_EQUALS((crl_bits<GPIO_Pin_8, _mode>::value), (get_bits<_m8>::value));
            TS_ASSERT_EQUALS((crl_bits<GPIO_Pin_9, _mode>::value), (get_bits<_m9>::value));
            TS_ASSERT_EQUALS((crl_bits<GPIO_Pin_10,_mode>::value), (get_bits<_m10>::value));
            TS_ASSERT_EQUALS((crl_bits<GPIO_Pin_11,_mode>::value), (get_bits<_m11>::value));
            TS_ASSERT_EQUALS((crl_bits<GPIO_Pin_12,_mode>::value), (get_bits<_m12>::value));
            TS_ASSERT_EQUALS((crl_bits<GPIO_Pin_13,_mode>::value), (get_bits<_m13>::value));
            TS_ASSERT_EQUALS((crl_bits<GPIO_Pin_14,_mode>::value), (get_bits<_m14>::value));
            TS_ASSERT_EQUALS((crl_bits<GPIO_Pin_15,_mode>::value), (get_bits<_m15>::value));

            TS_ASSERT_EQUALS((crl_mask<GPIO_Pin_0>::value),  (get_mask<_m0>::value));
            TS_ASSERT_EQUALS((crl_mask<GPIO_Pin_1>::value),  (get_mask<_m1>::value));
            TS_ASSERT_EQUALS((crl_mask<GPIO_Pin_2>::value),  (get_mask<_m2>::value));
            TS_ASSERT_EQUALS((crl_mask<GPIO_Pin_3>::value),  (get_mask<_m3>::value));
            TS_ASSERT_EQUALS((crl_mask<GPIO_Pin_4>::value),  (get_mask<_m4>::value));
            TS_ASSERT_EQUALS((crl_mask<GPIO_Pin_5>::value),  (get_mask<_m5>::value));
            TS_ASSERT_EQUALS((crl_mask<GPIO_Pin_6>::value),  (get_mask<_m6>::value));
            TS_ASSERT_EQUALS((crl_mask<GPIO_Pin_7>::value),  (get_mask<_m7>::value));
            TS_ASSERT_EQUALS((crl_mask<GPIO_Pin_8>::value),  (get_mask<_m8>::value));
            TS_ASSERT_EQUALS((crl_mask<GPIO_Pin_9>::value),  (get_mask<_m9>::value));
            TS_ASSERT_EQUALS((crl_mask<GPIO_Pin_10>::value), (get_mask<_m10>::value));
            TS_ASSERT_EQUALS((crl_mask<GPIO_Pin_11>::value), (get_mask<_m11>::value));
            TS_ASSERT_EQUALS((crl_mask<GPIO_Pin_12>::value), (get_mask<_m12>::value));
            TS_ASSERT_EQUALS((crl_mask<GPIO_Pin_13>::value), (get_mask<_m13>::value));
            TS_ASSERT_EQUALS((crl_mask<GPIO_Pin_14>::value), (get_mask<_m14>::value));
            TS_ASSERT_EQUALS((crl_mask<GPIO_Pin_15>::value), (get_mask<_m15>::value));
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

            TS_ASSERT_EQUALS((crh_bits<GPIO_Pin_0, _mode,_speed>::value), (get_bits<_m0>::value));
            TS_ASSERT_EQUALS((crh_bits<GPIO_Pin_1, _mode,_speed>::value), (get_bits<_m1>::value));
            TS_ASSERT_EQUALS((crh_bits<GPIO_Pin_2, _mode,_speed>::value), (get_bits<_m2>::value));
            TS_ASSERT_EQUALS((crh_bits<GPIO_Pin_3, _mode,_speed>::value), (get_bits<_m3>::value));
            TS_ASSERT_EQUALS((crh_bits<GPIO_Pin_4, _mode,_speed>::value), (get_bits<_m4>::value));
            TS_ASSERT_EQUALS((crh_bits<GPIO_Pin_5, _mode,_speed>::value), (get_bits<_m5>::value));
            TS_ASSERT_EQUALS((crh_bits<GPIO_Pin_6, _mode,_speed>::value), (get_bits<_m6>::value));
            TS_ASSERT_EQUALS((crh_bits<GPIO_Pin_7, _mode,_speed>::value), (get_bits<_m7>::value));
            TS_ASSERT_EQUALS((crh_bits<GPIO_Pin_8, _mode,_speed>::value), (get_bits<_m8>::value));
            TS_ASSERT_EQUALS((crh_bits<GPIO_Pin_9, _mode,_speed>::value), (get_bits<_m9>::value));
            TS_ASSERT_EQUALS((crh_bits<GPIO_Pin_10,_mode,_speed>::value), (get_bits<_m10>::value));
            TS_ASSERT_EQUALS((crh_bits<GPIO_Pin_11,_mode,_speed>::value), (get_bits<_m11>::value));
            TS_ASSERT_EQUALS((crh_bits<GPIO_Pin_12,_mode,_speed>::value), (get_bits<_m12>::value));
            TS_ASSERT_EQUALS((crh_bits<GPIO_Pin_13,_mode,_speed>::value), (get_bits<_m13>::value));
            TS_ASSERT_EQUALS((crh_bits<GPIO_Pin_14,_mode,_speed>::value), (get_bits<_m14>::value));
            TS_ASSERT_EQUALS((crh_bits<GPIO_Pin_15,_mode,_speed>::value), (get_bits<_m15>::value));

            TS_ASSERT_EQUALS((crh_mask<GPIO_Pin_0>::value),  (get_mask<_m0>::value));
            TS_ASSERT_EQUALS((crh_mask<GPIO_Pin_1>::value),  (get_mask<_m1>::value));
            TS_ASSERT_EQUALS((crh_mask<GPIO_Pin_2>::value),  (get_mask<_m2>::value));
            TS_ASSERT_EQUALS((crh_mask<GPIO_Pin_3>::value),  (get_mask<_m3>::value));
            TS_ASSERT_EQUALS((crh_mask<GPIO_Pin_4>::value),  (get_mask<_m4>::value));
            TS_ASSERT_EQUALS((crh_mask<GPIO_Pin_5>::value),  (get_mask<_m5>::value));
            TS_ASSERT_EQUALS((crh_mask<GPIO_Pin_6>::value),  (get_mask<_m6>::value));
            TS_ASSERT_EQUALS((crh_mask<GPIO_Pin_7>::value),  (get_mask<_m7>::value));
            TS_ASSERT_EQUALS((crh_mask<GPIO_Pin_8>::value),  (get_mask<_m8>::value));
            TS_ASSERT_EQUALS((crh_mask<GPIO_Pin_9>::value),  (get_mask<_m9>::value));
            TS_ASSERT_EQUALS((crh_mask<GPIO_Pin_10>::value), (get_mask<_m10>::value));
            TS_ASSERT_EQUALS((crh_mask<GPIO_Pin_11>::value), (get_mask<_m11>::value));
            TS_ASSERT_EQUALS((crh_mask<GPIO_Pin_12>::value), (get_mask<_m12>::value));
            TS_ASSERT_EQUALS((crh_mask<GPIO_Pin_13>::value), (get_mask<_m13>::value));
            TS_ASSERT_EQUALS((crh_mask<GPIO_Pin_14>::value), (get_mask<_m14>::value));
            TS_ASSERT_EQUALS((crh_mask<GPIO_Pin_15>::value), (get_mask<_m15>::value));
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

            TS_ASSERT_EQUALS((crh_bits<GPIO_Pin_0, _mode>::value), (get_bits<_m0>::value));
            TS_ASSERT_EQUALS((crh_bits<GPIO_Pin_1, _mode>::value), (get_bits<_m1>::value));
            TS_ASSERT_EQUALS((crh_bits<GPIO_Pin_2, _mode>::value), (get_bits<_m2>::value));
            TS_ASSERT_EQUALS((crh_bits<GPIO_Pin_3, _mode>::value), (get_bits<_m3>::value));
            TS_ASSERT_EQUALS((crh_bits<GPIO_Pin_4, _mode>::value), (get_bits<_m4>::value));
            TS_ASSERT_EQUALS((crh_bits<GPIO_Pin_5, _mode>::value), (get_bits<_m5>::value));
            TS_ASSERT_EQUALS((crh_bits<GPIO_Pin_6, _mode>::value), (get_bits<_m6>::value));
            TS_ASSERT_EQUALS((crh_bits<GPIO_Pin_7, _mode>::value), (get_bits<_m7>::value));
            TS_ASSERT_EQUALS((crh_bits<GPIO_Pin_8, _mode>::value), (get_bits<_m8>::value));
            TS_ASSERT_EQUALS((crh_bits<GPIO_Pin_9, _mode>::value), (get_bits<_m9>::value));
            TS_ASSERT_EQUALS((crh_bits<GPIO_Pin_10,_mode>::value), (get_bits<_m10>::value));
            TS_ASSERT_EQUALS((crh_bits<GPIO_Pin_11,_mode>::value), (get_bits<_m11>::value));
            TS_ASSERT_EQUALS((crh_bits<GPIO_Pin_12,_mode>::value), (get_bits<_m12>::value));
            TS_ASSERT_EQUALS((crh_bits<GPIO_Pin_13,_mode>::value), (get_bits<_m13>::value));
            TS_ASSERT_EQUALS((crh_bits<GPIO_Pin_14,_mode>::value), (get_bits<_m14>::value));
            TS_ASSERT_EQUALS((crh_bits<GPIO_Pin_15,_mode>::value), (get_bits<_m15>::value));

            TS_ASSERT_EQUALS((crh_mask<GPIO_Pin_0>::value),  (get_mask<_m0>::value));
            TS_ASSERT_EQUALS((crh_mask<GPIO_Pin_1>::value),  (get_mask<_m1>::value));
            TS_ASSERT_EQUALS((crh_mask<GPIO_Pin_2>::value),  (get_mask<_m2>::value));
            TS_ASSERT_EQUALS((crh_mask<GPIO_Pin_3>::value),  (get_mask<_m3>::value));
            TS_ASSERT_EQUALS((crh_mask<GPIO_Pin_4>::value),  (get_mask<_m4>::value));
            TS_ASSERT_EQUALS((crh_mask<GPIO_Pin_5>::value),  (get_mask<_m5>::value));
            TS_ASSERT_EQUALS((crh_mask<GPIO_Pin_6>::value),  (get_mask<_m6>::value));
            TS_ASSERT_EQUALS((crh_mask<GPIO_Pin_7>::value),  (get_mask<_m7>::value));
            TS_ASSERT_EQUALS((crh_mask<GPIO_Pin_8>::value),  (get_mask<_m8>::value));
            TS_ASSERT_EQUALS((crh_mask<GPIO_Pin_9>::value),  (get_mask<_m9>::value));
            TS_ASSERT_EQUALS((crh_mask<GPIO_Pin_10>::value), (get_mask<_m10>::value));
            TS_ASSERT_EQUALS((crh_mask<GPIO_Pin_11>::value), (get_mask<_m11>::value));
            TS_ASSERT_EQUALS((crh_mask<GPIO_Pin_12>::value), (get_mask<_m12>::value));
            TS_ASSERT_EQUALS((crh_mask<GPIO_Pin_13>::value), (get_mask<_m13>::value));
            TS_ASSERT_EQUALS((crh_mask<GPIO_Pin_14>::value), (get_mask<_m14>::value));
            TS_ASSERT_EQUALS((crh_mask<GPIO_Pin_15>::value), (get_mask<_m15>::value));
          }
        };

  public:
    void test__crl_cnf_mask(void)
    {
#if defined _HAVE_GPIO_CRL_REGISTER
      check_crl_cnf_mask();
#endif
    }

    void test__crl_mode_mask(void)
    {
#if defined _HAVE_GPIO_CRL_REGISTER
      check_crl_mode_mask();
#endif
    }

    void test__crl_mask(void)
    {
#if defined _HAVE_GPIO_CRL_REGISTER
      check_crl_mask();
#endif
    }

    void test__crl_mode_bits(void)
    {
#if defined _HAVE_GPIO_CRL_REGISTER
# if defined _HAVE_GPIO_SPEED_10MHz
      check_crl_mode_bits<GPIO_Speed_10MHz>::apply();
# endif
# if defined _HAVE_GPIO_SPEED_2MHz
      check_crl_mode_bits<GPIO_Speed_2MHz>::apply();
# endif
# if defined _HAVE_GPIO_SPEED_50MHz
      check_crl_mode_bits<GPIO_Speed_50MHz>::apply();
# endif
#endif
    }

    void test__crl_cnf_bits(void)
    {
#if defined _HAVE_GPIO_CRL_REGISTER
# if defined _HAVE_GPIO_MODE_AIN
      check_crl_cnf_bits<GPIO_Mode_AIN>::apply();
# endif
# if defined _HAVE_GPIO_MODE_IN_FLOATING
      check_crl_cnf_bits<GPIO_Mode_IN_FLOATING>::apply();
# endif
# if defined _HAVE_GPIO_MODE_IPD
      check_crl_cnf_bits<GPIO_Mode_IPD>::apply();
# endif
# if defined _HAVE_GPIO_MODE_IPU
      check_crl_cnf_bits<GPIO_Mode_IPU>::apply();
# endif
# if defined _HAVE_GPIO_MODE_Out_OD
      check_crl_cnf_bits<GPIO_Mode_Out_OD>::apply();
# endif
# if defined _HAVE_GPIO_MODE_Out_PP
      check_crl_cnf_bits<GPIO_Mode_Out_PP>::apply();
# endif
# if defined _HAVE_GPIO_MODE_AF_OD
      check_crl_cnf_bits<GPIO_Mode_AF_OD>::apply();
# endif
# if defined _HAVE_GPIO_MODE_AF_PP
      check_crl_cnf_bits<GPIO_Mode_AF_PP>::apply();
# endif
#endif
    }

    void test__crl_bits(void)
    {
#if defined _HAVE_GPIO_CRL_REGISTER
    /* crl_bits (for inputs) */
# if defined _HAVE_GPIO_MODE_AIN
      check_crl_bits<GPIO_Mode_AIN>::apply();
# endif
# if defined _HAVE_GPIO_MODE_IN_FLOATING
      check_crl_bits<GPIO_Mode_IN_FLOATING>::apply();
# endif
# if defined _HAVE_GPIO_MODE_IPD
      check_crl_bits<GPIO_Mode_IPD>::apply();
# endif
# if defined _HAVE_GPIO_MODE_IPU
      check_crl_bits<GPIO_Mode_IPU>::apply();
# endif
# if defined _HAVE_GPIO_MODE_Out_OD
#   if defined _HAVE_GPIO_SPEED_10MHz
      check_crl_bits<GPIO_Mode_Out_OD, GPIO_Speed_10MHz>::apply();
#   endif
#   if defined _HAVE_GPIO_SPEED_2MHz
      check_crl_bits<GPIO_Mode_Out_OD, GPIO_Speed_2MHz>::apply();
#   endif
#   if defined _HAVE_GPIO_SPEED_50MHz
      check_crl_bits<GPIO_Mode_Out_OD, GPIO_Speed_50MHz>::apply();
#   endif
# endif
# if defined _HAVE_GPIO_MODE_Out_PP
#   if defined _HAVE_GPIO_SPEED_10MHz
      check_crl_bits<GPIO_Mode_Out_PP, GPIO_Speed_10MHz>::apply();
#   endif
#   if defined _HAVE_GPIO_SPEED_2MHz
      check_crl_bits<GPIO_Mode_Out_PP, GPIO_Speed_2MHz>::apply();
#   endif
#   if defined _HAVE_GPIO_SPEED_50MHz
      check_crl_bits<GPIO_Mode_Out_PP, GPIO_Speed_50MHz>::apply();
#   endif
# endif
# if defined _HAVE_GPIO_MODE_AF_OD
#   if defined _HAVE_GPIO_SPEED_10MHz
      check_crl_bits<GPIO_Mode_AF_OD, GPIO_Speed_10MHz>::apply();
#   endif
#   if defined _HAVE_GPIO_SPEED_2MHz
      check_crl_bits<GPIO_Mode_AF_OD, GPIO_Speed_2MHz>::apply();
#   endif
#   if defined _HAVE_GPIO_SPEED_50MHz
      check_crl_bits<GPIO_Mode_AF_OD, GPIO_Speed_50MHz>::apply();
#   endif
# endif
# if defined _HAVE_GPIO_MODE_AF_PP
#   if defined _HAVE_GPIO_SPEED_10MHz
      check_crl_bits<GPIO_Mode_AF_PP, GPIO_Speed_10MHz>::apply();
#   endif
#   if defined _HAVE_GPIO_SPEED_2MHz
      check_crl_bits<GPIO_Mode_AF_PP, GPIO_Speed_2MHz>::apply();
#   endif
#   if defined _HAVE_GPIO_SPEED_50MHz
      check_crl_bits<GPIO_Mode_AF_PP, GPIO_Speed_50MHz>::apply();
#   endif
# endif
#endif
    }

    void test__crl_masked(void)
    {
    /* crl_masked (for inputs) */
#if defined _HAVE_GPIO_CRL_REGISTER
# if defined _HAVE_GPIO_MODE_AIN
      check_crl_masked<GPIO_Mode_AIN>::apply();
# endif
# if defined _HAVE_GPIO_MODE_IN_FLOATING
      check_crl_masked<GPIO_Mode_IN_FLOATING>::apply();
# endif
# if defined _HAVE_GPIO_MODE_IPD
      check_crl_masked<GPIO_Mode_IPD>::apply();
# endif
# if defined _HAVE_GPIO_MODE_IPU
      check_crl_masked<GPIO_Mode_IPU>::apply();
# endif

    /* crl_masked (for outputs>::apply(); */
# if defined _HAVE_GPIO_MODE_Out_OD
#   if defined _HAVE_GPIO_SPEED_10MHz
      check_crl_masked<GPIO_Mode_Out_OD, GPIO_Speed_10MHz>::apply();;
#   endif
#   if defined _HAVE_GPIO_SPEED_2MHz
      check_crl_masked<GPIO_Mode_Out_OD, GPIO_Speed_2MHz>::apply();;
#   endif
#   if defined _HAVE_GPIO_SPEED_50MHz
      check_crl_masked<GPIO_Mode_Out_OD, GPIO_Speed_50MHz>::apply();;
#   endif
# endif
# if defined _HAVE_GPIO_MODE_Out_PP
#   if defined _HAVE_GPIO_SPEED_10MHz
      check_crl_masked<GPIO_Mode_Out_PP, GPIO_Speed_10MHz>::apply();;
#   endif
#   if defined _HAVE_GPIO_SPEED_2MHz
      check_crl_masked<GPIO_Mode_Out_PP, GPIO_Speed_2MHz>::apply();;
#   endif
#   if defined _HAVE_GPIO_SPEED_50MHz
      check_crl_masked<GPIO_Mode_Out_PP, GPIO_Speed_50MHz>::apply();;
#   endif
# endif
# if defined _HAVE_GPIO_MODE_AF_OD
#   if defined _HAVE_GPIO_SPEED_10MHz
      check_crl_masked<GPIO_Mode_AF_OD, GPIO_Speed_10MHz>::apply();;
#   endif
#   if defined _HAVE_GPIO_SPEED_2MHz
      check_crl_masked<GPIO_Mode_AF_OD, GPIO_Speed_2MHz>::apply();;
#   endif
#   if defined _HAVE_GPIO_SPEED_50MHz
      check_crl_masked<GPIO_Mode_AF_OD, GPIO_Speed_50MHz>::apply();;
#   endif
# endif
# if defined _HAVE_GPIO_MODE_AF_PP
#   if defined _HAVE_GPIO_SPEED_10MHz
      check_crl_masked<GPIO_Mode_AF_PP, GPIO_Speed_10MHz>::apply();;
#   endif
#   if defined _HAVE_GPIO_SPEED_2MHz
      check_crl_masked<GPIO_Mode_AF_PP, GPIO_Speed_2MHz>::apply();;
#   endif
#   if defined _HAVE_GPIO_SPEED_50MHz
      check_crl_masked<GPIO_Mode_AF_PP, GPIO_Speed_50MHz>::apply();;
#   endif
# endif
#endif
    }

    /* crl_mix */
    void test__crl_mix()
    {
#if defined _HAVE_GPIO_CRL_REGISTER
      using namespace stm32xx::gpio::ct;
      using stm32xx::bits::ct::get_bits;
      using stm32xx::bits::ct::get_mask;
      /* With no args */
      TS_ASSERT_EQUALS(0ul, get_bits<crl_mix<> >::value);
      TS_ASSERT_EQUALS(0ul, get_mask<crl_mix<> >::value);

      {
        /* with 1 arg */
        using arg1 = pin_conf<GPIO_Pin_0,GPIO_Mode_AIN>;
        constexpr uint32_t bits1 = crl_bits<GPIO_Pin_0,GPIO_Mode_AIN>::value;
        constexpr uint32_t mask1 = crl_mask<GPIO_Pin_0>::value;
        TS_ASSERT_EQUALS(bits1, (get_bits<crl_mix<arg1> >::value));
        TS_ASSERT_EQUALS(mask1, (get_mask<crl_mix<arg1> >::value));
      }

      {
        /* with 2 args */
        using arg1 = pin_conf<GPIO_Pin_1,GPIO_Mode_Out_PP,GPIO_Speed_10MHz>;
        using arg2 = pin_conf<GPIO_Pin_0,GPIO_Mode_AIN>;
        constexpr uint32_t bits1 = crl_bits<GPIO_Pin_1,GPIO_Mode_Out_PP,GPIO_Speed_10MHz>::value;
        constexpr uint32_t mask1 = crl_mask<GPIO_Pin_1>::value;
        constexpr uint32_t bits2 = crl_bits<GPIO_Pin_0,GPIO_Mode_AIN>::value;
        constexpr uint32_t mask2 = crl_mask<GPIO_Pin_0>::value;
        TS_ASSERT_EQUALS(bits1|bits2, (get_bits<crl_mix<arg1,arg2> >::value));
        TS_ASSERT_EQUALS(mask1|mask2, (get_mask<crl_mix<arg1,arg2> >::value));
      }
#endif
    }


    void test__crh_cnf_mask(void)
    {
#if defined _HAVE_GPIO_CRH_REGISTER
      check_crh_cnf_mask();
#endif
    }

    void test__crh_mode_mask(void)
    {
#if defined _HAVE_GPIO_CRH_REGISTER
      check_crh_mode_mask();
#endif
    }

    void test__crh_mask(void)
    {
#if defined _HAVE_GPIO_CRH_REGISTER
      check_crh_mask();
#endif
    }

    void test__crh_mode_bits(void)
    {
#if defined _HAVE_GPIO_CRH_REGISTER
# if defined _HAVE_GPIO_SPEED_10MHz
      check_crh_mode_bits<GPIO_Speed_10MHz>::apply();
# endif
# if defined _HAVE_GPIO_SPEED_2MHz
      check_crh_mode_bits<GPIO_Speed_2MHz>::apply();
# endif
# if defined _HAVE_GPIO_SPEED_50MHz
      check_crh_mode_bits<GPIO_Speed_50MHz>::apply();
# endif
#endif
    }

    void test__crh_cnf_bits(void)
    {
#if defined _HAVE_GPIO_CRH_REGISTER
# if defined _HAVE_GPIO_MODE_AIN
      check_crh_cnf_bits<GPIO_Mode_AIN>::apply();
# endif
# if defined _HAVE_GPIO_MODE_IN_FLOATING
      check_crh_cnf_bits<GPIO_Mode_IN_FLOATING>::apply();
# endif
# if defined _HAVE_GPIO_MODE_IPD
      check_crh_cnf_bits<GPIO_Mode_IPD>::apply();
# endif
# if defined _HAVE_GPIO_MODE_IPU
      check_crh_cnf_bits<GPIO_Mode_IPU>::apply();
# endif
# if defined _HAVE_GPIO_MODE_Out_OD
      check_crh_cnf_bits<GPIO_Mode_Out_OD>::apply();
# endif
# if defined _HAVE_GPIO_MODE_Out_PP
      check_crh_cnf_bits<GPIO_Mode_Out_PP>::apply();
# endif
# if defined _HAVE_GPIO_MODE_AF_OD
      check_crh_cnf_bits<GPIO_Mode_AF_OD>::apply();
# endif
# if defined _HAVE_GPIO_MODE_AF_PP
      check_crh_cnf_bits<GPIO_Mode_AF_PP>::apply();
# endif
#endif
    }

    void test__crh_bits(void)
    {
#if defined _HAVE_GPIO_CRH_REGISTER
    /* crh_bits (for inputs) */
# if defined _HAVE_GPIO_MODE_AIN
      check_crh_bits<GPIO_Mode_AIN>::apply();
# endif
# if defined _HAVE_GPIO_MODE_IN_FLOATING
      check_crh_bits<GPIO_Mode_IN_FLOATING>::apply();
# endif
# if defined _HAVE_GPIO_MODE_IPD
      check_crh_bits<GPIO_Mode_IPD>::apply();
# endif
# if defined _HAVE_GPIO_MODE_IPU
      check_crh_bits<GPIO_Mode_IPU>::apply();
# endif
# if defined _HAVE_GPIO_MODE_Out_OD
#   if defined _HAVE_GPIO_SPEED_10MHz
      check_crh_bits<GPIO_Mode_Out_OD, GPIO_Speed_10MHz>::apply();
#   endif
#   if defined _HAVE_GPIO_SPEED_2MHz
      check_crh_bits<GPIO_Mode_Out_OD, GPIO_Speed_2MHz>::apply();
#   endif
#   if defined _HAVE_GPIO_SPEED_50MHz
      check_crh_bits<GPIO_Mode_Out_OD, GPIO_Speed_50MHz>::apply();
#   endif
# endif
# if defined _HAVE_GPIO_MODE_Out_PP
#   if defined _HAVE_GPIO_SPEED_10MHz
      check_crh_bits<GPIO_Mode_Out_PP, GPIO_Speed_10MHz>::apply();
#   endif
#   if defined _HAVE_GPIO_SPEED_2MHz
      check_crh_bits<GPIO_Mode_Out_PP, GPIO_Speed_2MHz>::apply();
#   endif
#   if defined _HAVE_GPIO_SPEED_50MHz
      check_crh_bits<GPIO_Mode_Out_PP, GPIO_Speed_50MHz>::apply();
#   endif
# endif
# if defined _HAVE_GPIO_MODE_AF_OD
#   if defined _HAVE_GPIO_SPEED_10MHz
      check_crh_bits<GPIO_Mode_AF_OD, GPIO_Speed_10MHz>::apply();
#   endif
#   if defined _HAVE_GPIO_SPEED_2MHz
      check_crh_bits<GPIO_Mode_AF_OD, GPIO_Speed_2MHz>::apply();
#   endif
#   if defined _HAVE_GPIO_SPEED_50MHz
      check_crh_bits<GPIO_Mode_AF_OD, GPIO_Speed_50MHz>::apply();
#   endif
# endif
# if defined _HAVE_GPIO_MODE_AF_PP
#   if defined _HAVE_GPIO_SPEED_10MHz
      check_crh_bits<GPIO_Mode_AF_PP, GPIO_Speed_10MHz>::apply();
#   endif
#   if defined _HAVE_GPIO_SPEED_2MHz
      check_crh_bits<GPIO_Mode_AF_PP, GPIO_Speed_2MHz>::apply();
#   endif
#   if defined _HAVE_GPIO_SPEED_50MHz
      check_crh_bits<GPIO_Mode_AF_PP, GPIO_Speed_50MHz>::apply();
#   endif
# endif
#endif
    }

    void test__crh_masked(void)
    {
    /* crh_masked (for inputs) */
#if defined _HAVE_GPIO_CRH_REGISTER
# if defined _HAVE_GPIO_MODE_AIN
      check_crh_masked<GPIO_Mode_AIN>::apply();
# endif
# if defined _HAVE_GPIO_MODE_IN_FLOATING
      check_crh_masked<GPIO_Mode_IN_FLOATING>::apply();
# endif
# if defined _HAVE_GPIO_MODE_IPD
      check_crh_masked<GPIO_Mode_IPD>::apply();
# endif
# if defined _HAVE_GPIO_MODE_IPU
      check_crh_masked<GPIO_Mode_IPU>::apply();
# endif

    /* crh_masked (for outputs>::apply(); */
# if defined _HAVE_GPIO_MODE_Out_OD
#   if defined _HAVE_GPIO_SPEED_10MHz
      check_crh_masked<GPIO_Mode_Out_OD, GPIO_Speed_10MHz>::apply();;
#   endif
#   if defined _HAVE_GPIO_SPEED_2MHz
      check_crh_masked<GPIO_Mode_Out_OD, GPIO_Speed_2MHz>::apply();;
#   endif
#   if defined _HAVE_GPIO_SPEED_50MHz
      check_crh_masked<GPIO_Mode_Out_OD, GPIO_Speed_50MHz>::apply();;
#   endif
# endif
# if defined _HAVE_GPIO_MODE_Out_PP
#   if defined _HAVE_GPIO_SPEED_10MHz
      check_crh_masked<GPIO_Mode_Out_PP, GPIO_Speed_10MHz>::apply();;
#   endif
#   if defined _HAVE_GPIO_SPEED_2MHz
      check_crh_masked<GPIO_Mode_Out_PP, GPIO_Speed_2MHz>::apply();;
#   endif
#   if defined _HAVE_GPIO_SPEED_50MHz
      check_crh_masked<GPIO_Mode_Out_PP, GPIO_Speed_50MHz>::apply();;
#   endif
# endif
# if defined _HAVE_GPIO_MODE_AF_OD
#   if defined _HAVE_GPIO_SPEED_10MHz
      check_crh_masked<GPIO_Mode_AF_OD, GPIO_Speed_10MHz>::apply();;
#   endif
#   if defined _HAVE_GPIO_SPEED_2MHz
      check_crh_masked<GPIO_Mode_AF_OD, GPIO_Speed_2MHz>::apply();;
#   endif
#   if defined _HAVE_GPIO_SPEED_50MHz
      check_crh_masked<GPIO_Mode_AF_OD, GPIO_Speed_50MHz>::apply();;
#   endif
# endif
# if defined _HAVE_GPIO_MODE_AF_PP
#   if defined _HAVE_GPIO_SPEED_10MHz
      check_crh_masked<GPIO_Mode_AF_PP, GPIO_Speed_10MHz>::apply();;
#   endif
#   if defined _HAVE_GPIO_SPEED_2MHz
      check_crh_masked<GPIO_Mode_AF_PP, GPIO_Speed_2MHz>::apply();;
#   endif
#   if defined _HAVE_GPIO_SPEED_50MHz
      check_crh_masked<GPIO_Mode_AF_PP, GPIO_Speed_50MHz>::apply();;
#   endif
# endif
#endif
    }

    /* crh_mix */
    void test__crh_mix()
    {
#if defined _HAVE_GPIO_CRH_REGISTER
      using namespace stm32xx::gpio::ct;
      using stm32xx::bits::ct::get_bits;
      using stm32xx::bits::ct::get_mask;
      /* With no args */
      TS_ASSERT_EQUALS(0ul, get_bits<crh_mix<> >::value);
      TS_ASSERT_EQUALS(0ul, get_mask<crh_mix<> >::value);

      {
        /* with 1 arg */
        using arg1 = pin_conf<GPIO_Pin_0,GPIO_Mode_AIN>;
        constexpr uint32_t bits1 = crh_bits<GPIO_Pin_0,GPIO_Mode_AIN>::value;
        constexpr uint32_t mask1 = crh_mask<GPIO_Pin_0>::value;
        TS_ASSERT_EQUALS(bits1, (get_bits<crh_mix<arg1> >::value));
        TS_ASSERT_EQUALS(mask1, (get_mask<crh_mix<arg1> >::value));
      }

      {
        /* with 2 args */
        using arg1 = pin_conf<GPIO_Pin_1,GPIO_Mode_Out_PP,GPIO_Speed_10MHz>;
        using arg2 = pin_conf<GPIO_Pin_0,GPIO_Mode_AIN>;
        constexpr uint32_t bits1 = crh_bits<GPIO_Pin_1,GPIO_Mode_Out_PP,GPIO_Speed_10MHz>::value;
        constexpr uint32_t mask1 = crh_mask<GPIO_Pin_1>::value;
        constexpr uint32_t bits2 = crh_bits<GPIO_Pin_0,GPIO_Mode_AIN>::value;
        constexpr uint32_t mask2 = crh_mask<GPIO_Pin_0>::value;
        TS_ASSERT_EQUALS(bits1|bits2, (get_bits<crh_mix<arg1,arg2> >::value));
        TS_ASSERT_EQUALS(mask1|mask2, (get_mask<crh_mix<arg1,arg2> >::value));
      }
#endif
    }

    void test__configure_gpio__1(void)
    {
#ifdef STM32_FAMILY_STM32F10X
      GPIO_TypeDef gpiox = {
        /* Reset values */
        0x44444444ul,     /* CRL */
        0x44444444ul,     /* CRH */
        0x00000000ul,     /* IDR */
        0x00000000ul,     /* ODR */
        0x00000000ul,     /* BSRR */
        0x00000000ul,     /* BRR */
        0x00000000ul      /* LCKR */
      };
      using namespace stm32xx::gpio::ct;

      typedef gpio_conf<
        pin_conf<GPIO_Pin_0 | GPIO_Pin_4, GPIO_Mode_Out_PP, GPIO_Speed_10MHz>
      , pin_conf<GPIO_Pin_1, GPIO_Mode_AIN> 
      >  my_gpio_conf;

      set<my_gpio_conf>::in(&gpiox);

      TS_ASSERT_EQUALS(0x44414401ul, gpiox.CRL);
      TS_ASSERT_EQUALS(0x44444444ul, gpiox.CRH);
      TS_ASSERT_EQUALS(0x00000000ul, gpiox.IDR);
      TS_ASSERT_EQUALS(0x00000000ul, gpiox.ODR);
      TS_ASSERT_EQUALS(0x00000000ul, gpiox.BSRR);
      TS_ASSERT_EQUALS(0x00000000ul, gpiox.BRR);
      TS_ASSERT_EQUALS(0x00000000ul, gpiox.LCKR);
#else
# error "Not implemented yet!"
#endif
    }

    void test__configure_gpio__2()
    {
#ifdef STM32_FAMILY_STM32F10X
      GPIO_TypeDef gpiox = {
        /* Reset values */
        0x44444444ul,     /* CRL */
        0x44444444ul,     /* CRH */
        0x00000000ul,     /* IDR */
        0x00000000ul,     /* ODR */
        0x00000000ul,     /* BSRR */
        0x00000000ul,     /* BRR */
        0x00000000ul      /* LCKR */
      };
      using namespace stm32xx::gpio::ct;

      typedef gpio_conf<
        pin_conf<GPIO_Pin_8 | GPIO_Pin_12, GPIO_Mode_Out_PP, GPIO_Speed_10MHz>
      , pin_conf<GPIO_Pin_9, GPIO_Mode_AIN> 
      >  my_gpio_conf;

      set<my_gpio_conf>::in(&gpiox);

      TS_ASSERT_EQUALS(0x44444444ul, gpiox.CRL);
      TS_ASSERT_EQUALS(0x44414401ul, gpiox.CRH);
      TS_ASSERT_EQUALS(0x00000000ul, gpiox.IDR);
      TS_ASSERT_EQUALS(0x00000000ul, gpiox.ODR);
      TS_ASSERT_EQUALS(0x00000000ul, gpiox.BSRR);
      TS_ASSERT_EQUALS(0x00000000ul, gpiox.BRR);
      TS_ASSERT_EQUALS(0x00000000ul, gpiox.LCKR);
#else
# error "Not implemented yet!"
#endif
    }

    void test__configure_gpio__3()
    {
#ifdef STM32_FAMILY_STM32F10X
      GPIO_TypeDef gpiox = {
        /* Reset values */
        0x44444444ul,     /* CRL */
        0x44444444ul,     /* CRH */
        0x00000000ul,     /* IDR */
        0x00000000ul,     /* ODR */
        0x00000000ul,     /* BSRR */
        0x00000000ul,     /* BRR */
        0x00000000ul      /* LCKR */
      };
      using namespace stm32xx::gpio::ct;

      typedef gpio_conf<
        pin_conf<GPIO_Pin_0 | GPIO_Pin_4, GPIO_Mode_Out_PP, GPIO_Speed_10MHz>
      , pin_conf<GPIO_Pin_1, GPIO_Mode_AIN> 
      , pin_conf<GPIO_Pin_8 | GPIO_Pin_12, GPIO_Mode_Out_PP, GPIO_Speed_10MHz>
      , pin_conf<GPIO_Pin_9, GPIO_Mode_AIN> 
      >  my_gpio_conf;

      set<my_gpio_conf>::in(&gpiox);

      TS_ASSERT_EQUALS(0x44414401ul, gpiox.CRL);
      TS_ASSERT_EQUALS(0x44414401ul, gpiox.CRH);
      TS_ASSERT_EQUALS(0x00000000ul, gpiox.IDR);
      TS_ASSERT_EQUALS(0x00000000ul, gpiox.ODR);
      TS_ASSERT_EQUALS(0x00000000ul, gpiox.BSRR);
      TS_ASSERT_EQUALS(0x00000000ul, gpiox.BRR);
      TS_ASSERT_EQUALS(0x00000000ul, gpiox.LCKR);
#else
# error "Not implemented yet!"
#endif
    }
  };

// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
