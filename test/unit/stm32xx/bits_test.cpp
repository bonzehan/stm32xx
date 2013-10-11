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

/** // doc: test/unit/stm32xx/bits_test.cpp {{{
 * @file test/unit/stm32xx/bits_test.cpp
 * @todo Write documentation
 */ // }}}
#include <stm32xx/bits.hpp>
#include <CppUTest/TestHarness.h>

TEST_GROUP(stm32xx__bits__ct)
{
  template <uint32_t _bits> 
    struct _bits_holder
    { constexpr static uint32_t bits = _bits; };
  template <uint32_t _mask>
    struct _mask_holder
    { constexpr static uint32_t mask = _mask; };
};

TEST(stm32xx__bits__ct, get_bits__from_bits_holder)
{
  using namespace stm32xx::bits::ct;
  CHECK_EQUAL(get_bits<_bits_holder<0x12345678ul> >::value, 0x12345678ul);
};

TEST(stm32xx__bits__ct, get_mask__from_mask_holder)
{
  using namespace stm32xx::bits::ct;
  CHECK_EQUAL(get_mask<_mask_holder<0x12345678ul> >::value, 0x12345678ul);
};

TEST(stm32xx__bits__ct, masked__holds_bits)
{
  using namespace stm32xx::bits::ct;
  CHECK_EQUAL((masked<0x12345678,0xFFFFFFFFul>::bits), 0x12345678ul);
};

TEST(stm32xx__bits__ct, masked__holds_mask)
{
  using namespace stm32xx::bits::ct;
  CHECK_EQUAL((masked<0x00000000,0x0000FFFFul>::mask), 0x0000FFFFul);
};

TEST(stm32xx__bits__ct, masked__doesnt_fail_when_bits_fit_to_mask)
{
  using namespace stm32xx::bits::ct;
  CHECK_EQUAL((masked<0x00001234,0x0000FFFFul>::bits), 0x00001234ul);
};

TEST(stm32xx__bits__ct, get_bits__from_masked)
{
  using namespace stm32xx::bits::ct;
  CHECK_EQUAL((get_bits<masked<0x00001234,0x0000FFFFul> >::value), 0x00001234ul);
};

TEST(stm32xx__bits__ct, get_mask__from_masked)
{
  using namespace stm32xx::bits::ct;
  CHECK_EQUAL((get_mask<masked<0x00001234,0x0000FFFFul> >::value), 0x0000FFFFul);
};

TEST(stm32xx__bits__ct, mix__with_no_args)
{
  using namespace stm32xx::bits::ct;
  CHECK_EQUAL((mix<>::value), 0x00000000ul);
  CHECK_EQUAL((mix<>::bits),  0x00000000ul);
  CHECK_EQUAL((mix<>::mask),  0x00000000ul);
}

TEST(stm32xx__bits__ct, mix__with_one_arg)
{
  using namespace stm32xx::bits::ct;
  CHECK_EQUAL((mix<masked<0x12345678ul,0xFFFFFFFFul> >::value), 0x12345678ul);
  CHECK_EQUAL((mix<masked<0x12345678ul,0xFFFFFFFFul> >::bits),  0x12345678ul);
  CHECK_EQUAL((mix<masked<0x12345678ul,0xFFFFFFFFul> >::mask),  0xFFFFFFFFul);
}

TEST(stm32xx__bits__ct, mix__with_two_args)
{
  using namespace stm32xx::bits::ct;
  using m1 = masked<0x00004321ul,0x0000FFFFul>;
  using m2 = masked<0x87650000ul,0xFFFF0000ul>;
  CHECK_EQUAL((mix<m1,m2>::value), 0x87654321ul);
  CHECK_EQUAL((mix<m1,m2>::bits),  0x87654321ul);
  CHECK_EQUAL((mix<m1,m2>::mask),  0xFFFFFFFFul);
}

TEST(stm32xx__bits__ct, modify_modifies_only_masked_bits)
{
  using namespace stm32xx::bits::ct;
  volatile uint32_t var = 0x5678ul;
  using bits = masked<0x12340000ul, 0xFFFF0000ul>;
  modify<bits>::in(var);
  CHECK_EQUAL(var, 0x12345678ul);
}
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
