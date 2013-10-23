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

/** // doc: test/unit/stm32xx/datetime_test.t.h {{{
 * @file test/unit/stm32xx/datetime_test.t.h
 * @todo Write documentation
 */ // }}}
#include <stm32xx/datetime.hpp>
#include <CppUTest/TestHarness.h>

class stm32xx__datetime__testsuite : public CxxTest::TestSuite
{
public:
  void dst_update_check(int32_t y, int32_t m, int32_t d, int32_t h, int32_t mn, 
                        int32_t s, bool dst, int32_t res)
  {
    using date = stm32xx::date;
    using time = stm32xx::time;
    using datetime = stm32xx::datetime;
    const datetime::flag_t f = (dst ? datetime::flag_isdst : 0x00);
    TS_ASSERT_EQUALS(datetime(date(y,m,d),time(h,mn,s),f).dst_update(), res); 
  }
  
  void test__datetime(void)
  {
    using date = stm32xx::date;
    using time = stm32xx::time;
    using datetime = stm32xx::datetime;
    /* datetime(date(...), time(...)) */
    TS_ASSERT_EQUALS(2013, datetime(date(2013,10,11),time(9,6,20,true)).year());
    TS_ASSERT_EQUALS(10, datetime(date(2013,10,11),time(9,6,20,true)).mon());
    TS_ASSERT_EQUALS(11, datetime(date(2013,10,11),time(9,6,20,true)).mday());
    TS_ASSERT_EQUALS(9,  datetime(date(2013,10,11),time(9,6,20,true)).hour12());
    TS_ASSERT_EQUALS(6,  datetime(date(2013,10,11),time(9,6,20,true)).min());
    TS_ASSERT_EQUALS(20, datetime(date(2013,10,11),time(9,6,20,true)).sec());
    TS_ASSERT(datetime(date(2013,10,11),time(9,6,20,true)).pm() == true);
  }

  void test__dst_update(void)
  {
    dst_update_check(2013, 1, 1, 0, 0, 0, true,  -3600);
    dst_update_check(2013, 1, 1,20,59, 0, false,  0);
    dst_update_check(2013, 1, 1,20,59, 0, true,  -3600);
    dst_update_check(2013, 3,31, 1,59,59, false,  0);
    dst_update_check(2013, 3,31, 1,59,59, true,  -3600);
    dst_update_check(2013, 3,31, 2, 0, 0, false, +3600);
    dst_update_check(2013, 3,31, 2, 0, 0, true,   0);
    dst_update_check(2013, 5,20,23, 0, 1, false, +3600);
    dst_update_check(2013,10,13, 4,38, 0, false, +3600);
    dst_update_check(2013,10,13, 4,38, 0, true,   0);
    dst_update_check(2013,10,27, 0,59,59, false, +3600);
    dst_update_check(2013,10,27, 1, 0, 0, false, +3600);
    dst_update_check(2013,10,27, 1,59,59, false, +3600);
    dst_update_check(2013,10,27, 1,59,59, true,   0);
    dst_update_check(2013,10,27, 3, 0, 0, false,  0);
    dst_update_check(2013,10,27, 3, 0, 0, true,  -3600);
    dst_update_check(2013,12,31, 1, 0, 0, false,  0);
    dst_update_check(2013,12,31, 1, 0, 0, true,  -3600);
  }
};
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
