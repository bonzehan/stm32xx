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

/** // doc: test/unit/stm32xx/datetime_test.cpp {{{
 * @file test/unit/stm32xx/datetime_test.cpp
 * @todo Write documentation
 */ // }}}
#include <stm32xx/datetime.hpp>
#include <CppUTest/TestHarness.h>

TEST_GROUP(stm32xx__datetime)
{
  using year_t = stm32xx::date::year_t;
  using mon_t = stm32xx::date::mon_t;
  using mday_t = stm32xx::date::mday_t;
  using hour_t = stm32xx::time::hour_t;
  using min_t = stm32xx::time::min_t;
  using sec_t = stm32xx::time::sec_t;
  using flag_t = stm32xx::datetime::flag_t;

  void test_dst_update(year_t y, mon_t m, mday_t d, hour_t h, min_t mn, 
                       sec_t s, bool summ, year_t y2, mon_t m2, mday_t d2,
                       hour_t h2)
  {
    using namespace stm32xx; 
    datetime dt(y, m, d, h, mn, s, (flag_t)(summ ? datetime::summer_time : 0x00));
    dt.dst_update(); 
    CHECK_EQUAL(y2, dt.year()); 
    CHECK_EQUAL(m2, dt.mon()); 
    CHECK_EQUAL(d2, dt.mday()); 
    CHECK_EQUAL(h2, dt.hour()); 
    CHECK_EQUAL(mn, dt.min()); 
    CHECK_EQUAL(s,  dt.sec()); 
  }
};

/*
 * datetime()
 */
TEST(stm32xx__datetime, datetime)
{
  stm32xx::datetime dt;
  CHECK_EQUAL(STM32XX_DATE_DEFAULT_YEAR, dt.year());
  CHECK_EQUAL(STM32XX_DATE_DEFAULT_MON, dt.mon());
  CHECK_EQUAL(STM32XX_DATE_DEFAULT_MDAY, dt.mday());
  CHECK_EQUAL(0, dt.sec_cnt());
}

/*
 * datetime(y,m,d,c)
 */
TEST(stm32xx__datetime, datetime__2013__10__11__75313)
{
  stm32xx::datetime dt(2013, 10, 11, 74313);
  CHECK_EQUAL(2013, dt.year());
  CHECK_EQUAL(10, dt.mon());
  CHECK_EQUAL(11, dt.mday());
  CHECK_EQUAL(74313, dt.sec_cnt());
}

/*
 * datetime(y,m,d,h,mn,s)
 */
TEST(stm32xx__datetime, datetime__2013__10__11__20__57__15)
{
  stm32xx::datetime dt(2013, 10, 11, 20, 57, 15);
  CHECK_EQUAL(2013, dt.year());
  CHECK_EQUAL(10, dt.mon());
  CHECK_EQUAL(11, dt.mday());
  CHECK_EQUAL(20, dt.hour());
  CHECK_EQUAL(57, dt.min());
  CHECK_EQUAL(15, dt.sec());
}

/*
 * datetime(y,m,d,h,mn,s,pm)
 */
TEST(stm32xx__datetime, datetime__2013__10__11__8__57__30__true)
{
  stm32xx::datetime dt(2013, 10, 11, 8, 57, 30, true);
  CHECK_EQUAL(2013, dt.year());
  CHECK_EQUAL(10, dt.mon());
  CHECK_EQUAL(11, dt.mday());
  CHECK_EQUAL(8,  dt.hour12());
  CHECK_EQUAL(57, dt.min());
  CHECK_EQUAL(30, dt.sec());
  CHECK(dt.pm() == true);
}

/*
 * datetime(d, t)
 */
TEST(stm32xx__datetime, datetime__date__time)
{
  stm32xx::datetime dt(stm32xx::date(2013,10,11), stm32xx::time(9,6,20,true));
  CHECK_EQUAL(2013, dt.year());
  CHECK_EQUAL(10, dt.mon());
  CHECK_EQUAL(11, dt.mday());
  CHECK_EQUAL(9,  dt.hour12());
  CHECK_EQUAL(6,  dt.min());
  CHECK_EQUAL(20, dt.sec());
  CHECK(dt.pm() == true);
}

#define TEST_dst_update(_y,_m,_d,_h,_mn,_s,_f,_y2,_m2,_d2,_h2) \
  TEST(stm32xx__datetime, dst_update__ ## _y ## __ ## _m ## __ ## _d ## __ ## _h ## __ ## _mn ## __ ## _s ## __ ## _f) \
  { \
    test_dst_update(_y,_m,_d,_h,_mn,_s,_f,_y2,_m2,_d2,_h2); \
  }

TEST_dst_update(2013, 1, 1, 0, 0, 0, true,  2012,12,31, 23);
TEST_dst_update(2013, 1, 1,20,59, 0, false, 2013, 1, 1, 20);
TEST_dst_update(2013, 1, 1,20,59, 0, true,  2013, 1, 1, 19);
TEST_dst_update(2013, 3,31, 1,59,59, false, 2013, 3,31, 1);
TEST_dst_update(2013, 3,31, 1,59,59, true,  2013, 3,31, 0);
TEST_dst_update(2013, 3,31, 2, 0, 0, false, 2013, 3,31, 3);
TEST_dst_update(2013, 3,31, 2, 0, 0, true,  2013, 3,31, 2);
TEST_dst_update(2013, 5,20,23, 0, 1, false, 2013, 5,21, 0);
TEST_dst_update(2013,10,13, 4,38, 0, false, 2013,10,13, 5);
TEST_dst_update(2013,10,13, 4,38, 0, true,  2013,10,13, 4);
TEST_dst_update(2013,10,27, 0,59,59, false, 2013,10,27, 1);
TEST_dst_update(2013,10,27, 1, 0, 0, false, 2013,10,27, 2);
TEST_dst_update(2013,10,27, 1,59,59, false, 2013,10,27, 2);
TEST_dst_update(2013,10,27, 1,59,59, true,  2013,10,27, 1);
TEST_dst_update(2013,10,27, 3, 0, 0, false, 2013,10,27, 3);
TEST_dst_update(2013,10,27, 3, 0, 0, true,  2013,10,27, 2);
TEST_dst_update(2013,12,31, 1, 0, 0, false, 2013,12,31, 1);
TEST_dst_update(2013,12,31, 1, 0, 0, true,  2013,12,31, 0);

// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
