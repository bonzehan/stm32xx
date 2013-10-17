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

/** // doc: test/unit/stm32xx/bcd_test.cpp {{{
 * @file test/unit/stm32xx/bcd_test.cpp
 * @todo Write documentation
 */ // }}}
#if 0
#include <stm32xx/date.hpp>
#include <CppUTest/TestHarness.h>

TEST_GROUP(stm32xx__bcd)
{
};

/*
 * encode()
 */
TEST(stm32xx__bcd, bcdp__0__encode__0)
{
  CHECK_EQUAL(0, stm32xx::bcdp<0>::encode(0));
};

TEST(stm32xx__bcd, bcdp__0__encode__10)
{
  CHECK_EQUAL(0, stm32xx::bcdp<0>::encode(10));
};

TEST(stm32xx__bcd, bcdp__1__encode__10)
{
  CHECK_EQUAL(0, stm32xx::bcdp<1>::encode(10));
};

TEST(stm32xx__bcd, bcdp__1__encode__12)
{
  CHECK_EQUAL(2, stm32xx::bcdp<1>::encode(12));
};

TEST(stm32xx__bcd, bcdp__2__encode__12)
{
  CHECK_EQUAL(0x12, stm32xx::bcdp<2>::encode(12));
};

TEST(stm32xx__bcd, bcdp__2__encode__123)
{
  CHECK_EQUAL(0x23, stm32xx::bcdp<2>::encode(123));
};

TEST(stm32xx__bcd, bcdp__3__encode__123)
{
  CHECK_EQUAL(0x123, stm32xx::bcdp<3>::encode(123));
};

TEST(stm32xx__bcd, bcdp__3__encode__1234)
{
  CHECK_EQUAL(0x234, stm32xx::bcdp<3>::encode(1234));
};

TEST(stm32xx__bcd, bcdp__4__encode__1234)
{
  CHECK_EQUAL(0x1234, stm32xx::bcdp<4>::encode(1234));
};

/*
 * decode()
 */
TEST(stm32xx__bcd, bcdp__0__decode__0x10)
{
  CHECK_EQUAL(0, stm32xx::bcdp<0>::decode(0x10));
};

TEST(stm32xx__bcd, bcdp__1__decode__0x10)
{
  CHECK_EQUAL(0, stm32xx::bcdp<1>::decode(0x10));
};

TEST(stm32xx__bcd, bcdp__1__decode__0x12)
{
  CHECK_EQUAL(2, stm32xx::bcdp<1>::decode(0x12));
};

TEST(stm32xx__bcd, bcdp__2__decode__0x12)
{
  CHECK_EQUAL(12, stm32xx::bcdp<2>::decode(0x12));
};

TEST(stm32xx__bcd, bcdp__2__decode__0x123)
{
  CHECK_EQUAL(23, stm32xx::bcdp<2>::decode(0x123));
};

TEST(stm32xx__bcd, bcdp__3__decode__0x123)
{
  CHECK_EQUAL(123, stm32xx::bcdp<3>::decode(0x123));
};

TEST(stm32xx__bcd, bcdp__3__decode__1234)
{
  CHECK_EQUAL(234, stm32xx::bcdp<3>::decode(0x1234));
};

TEST(stm32xx__bcd, bcdp__4__decode__1234)
{
  CHECK_EQUAL(1234, stm32xx::bcdp<4>::decode(0x1234));
};
#endif
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
