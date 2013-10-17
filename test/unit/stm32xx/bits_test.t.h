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

// test/unit/stm32xx/bits_test.t.h

/** // doc: test/unit/stm32xx/bits_test.t.h {{{ 
 * @file test/unit/stm32xx/bits_test.t.h
 * @todo Write documentation
 */ // }}}
#include <cxxtest/TestSuite.h>
#include <stm32xx/bits.hpp>

class stm32xx__bits__ct__testsuite: public CxxTest::TestSuite
  {
    template <uint32_t _bits>
      struct bits_holder { constexpr static uint32_t bits = _bits; };
    template <uint32_t _mask>
      struct mask_holder { constexpr static uint32_t mask = _mask; };
  public:
    void test__get_bits(void)
    {
      using namespace stm32xx::bits::ct;
      TS_ASSERT_EQUALS(get_bits<bits_holder<0x12345678ul> >::value, 0x12345678);
    }
    void test__get_mask(void)
    {
      using namespace stm32xx::bits::ct;
      TS_ASSERT_EQUALS(get_mask<mask_holder<0x12345678ul> >::value, 0x12345678);
    }
    void test__masked__members(void)
    {
      using namespace stm32xx::bits::ct;
      TS_ASSERT_EQUALS((masked<0x12345678,0xFFFFFFFFul>::bits), 0x12345678ul);
      TS_ASSERT_EQUALS((masked<0x00000000,0x0000FFFFul>::mask), 0x0000FFFFul);
    };

    void test__masked__when_bits_fit_to_mask(void)
    {
      using namespace stm32xx::bits::ct;
      TS_ASSERT_EQUALS((masked<0x00001234,0x0000FFFFul>::bits), 0x00001234ul);
    };

    void test__masked__get_bits(void)
    {
      using namespace stm32xx::bits::ct;
      TS_ASSERT_EQUALS((get_bits<masked<0x00001234,0x0000FFFFul> >::value), 0x00001234ul);
    };

    void test__masked__get_mask(void)
    {
      using namespace stm32xx::bits::ct;
      TS_ASSERT_EQUALS((get_mask<masked<0x00001234,0x0000FFFFul> >::value), 0x0000FFFFul);
    };

    void test__mix(void)
    {
      using namespace stm32xx::bits::ct;
      /* with no args */
      TS_ASSERT_EQUALS((mix<>::value), 0x00000000ul);
      TS_ASSERT_EQUALS((mix<>::bits),  0x00000000ul);
      TS_ASSERT_EQUALS((mix<>::mask),  0x00000000ul);
      /* with one arg */
      TS_ASSERT_EQUALS((mix<masked<0x12345678ul,0xFFFFFFFFul> >::value), 0x12345678ul);
      TS_ASSERT_EQUALS((mix<masked<0x12345678ul,0xFFFFFFFFul> >::bits),  0x12345678ul);
      TS_ASSERT_EQUALS((mix<masked<0x12345678ul,0xFFFFFFFFul> >::mask),  0xFFFFFFFFul);
      /* with two args */
      using m1 = masked<0x00004321ul,0x0000FFFFul>;
      using m2 = masked<0x87650000ul,0xFFFF0000ul>;
      TS_ASSERT_EQUALS((mix<m1,m2>::value), 0x87654321ul);
      TS_ASSERT_EQUALS((mix<m1,m2>::bits),  0x87654321ul);
      TS_ASSERT_EQUALS((mix<m1,m2>::mask),  0xFFFFFFFFul);
    }

    void test__modify__modifies_only_masked_bits(void)
    {
      using namespace stm32xx::bits::ct;
      volatile uint32_t var = 0x5678ul;
      using bits = masked<0x12340000ul, 0xFFFF0000ul>;
      modify<bits>::in(var);
      TS_ASSERT_EQUALS(var, 0x12345678ul);
    }
  };
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
