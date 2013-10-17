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

/** // doc: test/unit/stm32xx/bcd_test.t.h {{{
 * @file test/unit/stm32xx/bcd_test.t.h
 * @todo Write documentation
 */ // }}}
#include <stm32xx/date.hpp>
#include <cxxtest/TestSuite.h>

class stm32xx__bcd__testsuite : public CxxTest::TestSuite
{
public:
  /*
   * encode()
   */
  void test__bcdp__encode(void)
  {
    TS_ASSERT_EQUALS(stm32xx::bcdp<0>::encode(0), 0);
    TS_ASSERT_EQUALS(stm32xx::bcdp<0>::encode(10), 0);
    TS_ASSERT_EQUALS(stm32xx::bcdp<1>::encode(10), 0);
    TS_ASSERT_EQUALS(stm32xx::bcdp<1>::encode(12), 2);
    TS_ASSERT_EQUALS(stm32xx::bcdp<2>::encode(12), 0x12);
    TS_ASSERT_EQUALS(stm32xx::bcdp<2>::encode(123), 0x23);
    TS_ASSERT_EQUALS(stm32xx::bcdp<3>::encode(123), 0x123);
    TS_ASSERT_EQUALS(stm32xx::bcdp<3>::encode(1234), 0x234);
    TS_ASSERT_EQUALS(stm32xx::bcdp<4>::encode(1234), 0x1234);
  }

  /*
   * decode()
   */
  void test__bcdp__decode(void)
  {
    TS_ASSERT_EQUALS(stm32xx::bcdp<0>::decode(0x10), 0);
    TS_ASSERT_EQUALS(stm32xx::bcdp<1>::decode(0x10), 0);
    TS_ASSERT_EQUALS(stm32xx::bcdp<1>::decode(0x12), 2);
    TS_ASSERT_EQUALS(stm32xx::bcdp<2>::decode(0x12), 12);
    TS_ASSERT_EQUALS(stm32xx::bcdp<2>::decode(0x123), 23);
    TS_ASSERT_EQUALS(stm32xx::bcdp<3>::decode(0x123), 123);
    TS_ASSERT_EQUALS(stm32xx::bcdp<3>::decode(0x1234), 234);
    TS_ASSERT_EQUALS(stm32xx::bcdp<4>::decode(0x1234), 1234);
  }
};
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
