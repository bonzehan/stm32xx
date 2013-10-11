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

/** // doc: test/unit/stm32xx/date_test.cpp {{{
 * @file test/unit/stm32xx/date_test.cpp
 * @todo Write documentation
 */ // }}}
#include <stm32xx/date.hpp>
#include <CppUTest/TestHarness.h>

TEST_GROUP(stm32xx__date)
{
};

#define STM32XX_DATE_YEAR_MIN_minus_1 (STM32XX_DATE_YEAR_MIN-1)
#define STM32XX_DATE_YEAR_MAX_plus_1  (STM32XX_DATE_YEAR_MAX+1)

TEST(stm32xx__date, date)
{
  using namespace stm32xx;
  date d;
  CHECK_EQUAL(STM32XX_DATE_YEAR_MIN, d.year());
  CHECK_EQUAL(1, d.mon());
  CHECK_EQUAL(1, d.mday());
};

TEST(stm32xx__date, date__year__mon__mday)
{
  using namespace stm32xx;
  date d(2013,10,9);
  CHECK_EQUAL(2013, d.year());
  CHECK_EQUAL(10, d.mon());
  CHECK_EQUAL(9, d.mday());
};

#define TEST_leap_year(_y,_res) \
  TEST(stm32xx__date, leap_year__ ## _y) \
  { \
    CHECK(stm32xx::date::leap_year(_y) == _res); \
  }

TEST_leap_year(2012, true);
TEST_leap_year(2013, false);
TEST_leap_year(2100, false);
TEST_leap_year(2400, true);

#define TEST_mdays(_y,_m,_res) \
  TEST(stm32xx__date, mdays__ ## _y ## _m) \
  { \
    CHECK_EQUAL(_res, stm32xx::date::mdays(_y,_m)); \
  }

TEST_mdays(2013, 1, 31);
TEST_mdays(2013, 2, 28);
TEST_mdays(2013, 3, 31);
TEST_mdays(2013, 4, 30);
TEST_mdays(2013, 5, 31);
TEST_mdays(2013, 6, 30);
TEST_mdays(2013, 7, 31);
TEST_mdays(2013, 8, 31);
TEST_mdays(2013, 9, 30);
TEST_mdays(2013,10, 31);
TEST_mdays(2013,11, 30);
TEST_mdays(2013,12, 31);
TEST_mdays(2012, 2, 29);
TEST_mdays(2100, 2, 28);
TEST_mdays(2400, 2, 29);

#define TEST_yday(_y,_m,_d,_res) \
  TEST(stm32xx__date, yday__ ## _y ## __ ## _m ## __ ## _d) \
  { \
    CHECK_EQUAL(_res, stm32xx::date::yday(_y,_m,_d)); \
  }

TEST_yday(2013, 1, 1,   0);
TEST_yday(2013, 1,31,  30);
TEST_yday(2013, 2, 1,  31);
TEST_yday(2013, 2,28,  58);
TEST_yday(2013,12,31, 364);
TEST_yday(2012,12,31, 365);
TEST_yday(2100,12,31, 364);
TEST_yday(2400,12,31, 365);

#define TEST_wday(_y,_m,_d,_res) \
  TEST(stm32xx__date, wday__ ## _y ## __ ## _m ## __ ## _d) \
  { \
    CHECK_EQUAL(stm32xx::date::wday_ ## _res, stm32xx::date::wday(_y,_m,_d)); \
  }

TEST_wday(2013, 1, 1, tue);
TEST_wday(2013, 2,15, fri);
TEST_wday(2013, 3, 1, fri);
TEST_wday(2013, 4, 1, mon);
TEST_wday(2013, 4, 2, tue);
TEST_wday(2013, 4, 3, wed);
TEST_wday(2013, 4, 4, thu);
TEST_wday(2013, 4, 5, fri);
TEST_wday(2013, 4, 6, sat);
TEST_wday(2013, 4, 7, sun);
TEST_wday(2100, 2,28, sun);
TEST_wday(2400, 2,29, tue);

#define TEST_clamp_year(_y,_res) \
  TEST(stm32xx__date, correct_year__  ## _y) \
  { \
    CHECK_EQUAL(_res, stm32xx::date::clamp_year(_y)); \
  }

TEST_clamp_year(2013, 2013);
TEST_clamp_year(STM32XX_DATE_YEAR_MIN, STM32XX_DATE_YEAR_MIN);
TEST_clamp_year(STM32XX_DATE_YEAR_MAX, STM32XX_DATE_YEAR_MAX);
TEST_clamp_year(STM32XX_DATE_YEAR_MIN_minus_1, STM32XX_DATE_YEAR_MIN);
TEST_clamp_year(STM32XX_DATE_YEAR_MAX_plus_1, STM32XX_DATE_YEAR_MAX);

#define TEST_clamp_mon(_m,_res) \
  TEST(stm32xx__date, correct_mon__  ## _m) \
  { \
    CHECK_EQUAL(_res, stm32xx::date::clamp_mon(_m)); \
  }

TEST_clamp_mon( 1, 1);
TEST_clamp_mon( 6, 6);
TEST_clamp_mon(12,12);
TEST_clamp_mon( 0, 1);
TEST_clamp_mon(13,12);

#define TEST_clamp_mday(_y,_m,_d,_res) \
  TEST(stm32xx__date, correct_mday__ ## _y ## __ ## _m ## __ ## _d) \
  { \
    CHECK_EQUAL(_res, stm32xx::date::clamp_mday(_y,_m,_d)); \
  }

TEST_clamp_mday(2013, 1, 1, 1);
TEST_clamp_mday(2013, 1,31,31);
TEST_clamp_mday(2013, 6, 5, 5);
TEST_clamp_mday(2013,10, 0, 1);
TEST_clamp_mday(2012, 2,29,29);
TEST_clamp_mday(2400, 2,29,29)

TEST_clamp_mday(2013,10,32,31);
TEST_clamp_mday(2013, 9,31,30);
TEST_clamp_mday(2013, 9,32,30);
TEST_clamp_mday(2013, 2,29,28);
TEST_clamp_mday(2012, 2,30,29);
TEST_clamp_mday(2100, 2,29,28)
TEST_clamp_mday(2400, 2,30,29)


#define TEST_date_valid(_y,_m,_d,_res) \
  TEST(stm32xx__date, date_valid__ ## __ ## _y ## __ ## _m ## __ ## _d) \
  { \
    CHECK(stm32xx::date(_y,_m,_d).date_valid() == _res); \
  }

TEST_date_valid(2013, 10, 9, true);
TEST_date_valid(STM32XX_DATE_YEAR_MIN, 10, 9, true);
TEST_date_valid(STM32XX_DATE_YEAR_MAX, 10, 9, true);
TEST_date_valid(2013, 1, 1, true);
TEST_date_valid(2013,12,31, true);
TEST_date_valid(2013, 2,28, true);
TEST_date_valid(2012, 2,29, true);
TEST_date_valid(2400, 2,29, true);

TEST_date_valid(STM32XX_DATE_YEAR_MIN_minus_1,10, 9, false);
TEST_date_valid(STM32XX_DATE_YEAR_MAX_plus_1,10, 9, false);
TEST_date_valid(2013, 0, 1, false);
TEST_date_valid(2013,13, 1, false);
TEST_date_valid(2013, 1, 0, false);
TEST_date_valid(2013, 1,32, false);
TEST_date_valid(2013, 2,29, false);
TEST_date_valid(2013, 4,31, false);
TEST_date_valid(2100, 2,29, false);

#define TEST_clamp_date(_y,_m,_d, _y2, _m2, _d2) \
  TEST(stm32xx__date, correct__ ## _y ## __ ## _m ## __ ## _d) \
  { \
    stm32xx::date date(_y,_m,_d); \
    date.clamp_date(); \
    CHECK_EQUAL(_y2, date.year()); \
    CHECK_EQUAL(_m2, date.mon()); \
    CHECK_EQUAL(_d2, date.mday()); \
  }

TEST_clamp_date(2013,10, 9, 2013,10, 9);
TEST_clamp_date(STM32XX_DATE_YEAR_MIN, 1, 1, STM32XX_DATE_YEAR_MIN, 1, 1);
TEST_clamp_date(STM32XX_DATE_YEAR_MAX,12,31, STM32XX_DATE_YEAR_MAX,12,31);

TEST_clamp_date(STM32XX_DATE_YEAR_MIN_minus_1, 1, 1, STM32XX_DATE_YEAR_MIN, 1, 1);
TEST_clamp_date(STM32XX_DATE_YEAR_MAX_plus_1,12,31, STM32XX_DATE_YEAR_MAX,12,31);

TEST_clamp_date(2013, 0, 1, 2013, 1, 1);
TEST_clamp_date(2013,13,31, 2013,12,31);

TEST_clamp_date(2013,10, 0, 2013,10, 1);
TEST_clamp_date(2013,10,32, 2013,10,31);
TEST_clamp_date(2013,11,32, 2013,11,30);
TEST_clamp_date(2013, 2,29, 2013, 2,28);
TEST_clamp_date(2012, 2,30, 2012, 2,29);

TEST_clamp_date(STM32XX_DATE_YEAR_MIN_minus_1, 0, 1, STM32XX_DATE_YEAR_MIN, 1, 1);
TEST_clamp_date(STM32XX_DATE_YEAR_MIN_minus_1,13, 1, STM32XX_DATE_YEAR_MIN,12, 1);
TEST_clamp_date(STM32XX_DATE_YEAR_MAX_plus_1,  0, 1, STM32XX_DATE_YEAR_MAX, 1, 1);
TEST_clamp_date(STM32XX_DATE_YEAR_MAX_plus_1, 13, 1, STM32XX_DATE_YEAR_MAX,12, 1);
TEST_clamp_date(STM32XX_DATE_YEAR_MIN_minus_1, 2,30, STM32XX_DATE_YEAR_MIN, 2, \
                (stm32xx::date::leap_year(STM32XX_DATE_YEAR_MIN) ? 29 :28));
TEST_clamp_date(STM32XX_DATE_YEAR_MAX_plus_1,  2,30, STM32XX_DATE_YEAR_MAX, 2, \
                (stm32xx::date::leap_year(STM32XX_DATE_YEAR_MAX) ? 29 :28));
TEST_clamp_date(STM32XX_DATE_YEAR_MIN_minus_1, 2,29, STM32XX_DATE_YEAR_MIN, 2, \
                (stm32xx::date::leap_year(STM32XX_DATE_YEAR_MIN) ? 29 :28));
TEST_clamp_date(STM32XX_DATE_YEAR_MAX_plus_1,  2,29, STM32XX_DATE_YEAR_MAX, 2, \
                (stm32xx::date::leap_year(STM32XX_DATE_YEAR_MAX) ? 29 :28));

#define TEST_dec_year(_y,_m,_d,_res) \
  TEST(stm32xx__date, dec_year__ ## _y ## __ ## _m ## __ ## _d) \
  { \
    stm32xx::date d(_y,_m,_d); \
    d.dec_year(); \
    CHECK_EQUAL(_res, d.year()); \
    CHECK_EQUAL(_m, d.mon()); \
    CHECK_EQUAL(_d, d.mday()); \
  }
#define TEST_inc_year(_y,_m,_d,_res) \
  TEST(stm32xx__date, inc_year__ ## _y ## __ ## _m ## __ ## _d) \
  { \
    stm32xx::date d(_y,_m,_d); \
    d.inc_year(); \
    CHECK_EQUAL(_res, d.year()); \
    CHECK_EQUAL(_m, d.mon()); \
    CHECK_EQUAL(_d, d.mday()); \
  }

TEST_dec_year(2013, 1,10,  2012);
TEST_dec_year(2012, 2,29,  2011);
TEST_dec_year(STM32XX_DATE_YEAR_MIN, 1,10,  STM32XX_DATE_YEAR_MAX);

TEST_inc_year(2013, 1,10, 2014);
TEST_inc_year(2012, 2,29, 2013);
TEST_inc_year(STM32XX_DATE_YEAR_MAX, 1,10,  STM32XX_DATE_YEAR_MIN);

#define TEST_dec_mon(_y,_m,_d,_res) \
  TEST(stm32xx__date, dec_mon__ ## _y ## __ ## _m ## __ ## _d) \
  { \
    stm32xx::date d(_y,_m,_d); \
    d.dec_mon(); \
    CHECK_EQUAL(_y, d.year()); \
    CHECK_EQUAL(_res, d.mon()); \
    CHECK_EQUAL(_d, d.mday()); \
  }
#define TEST_inc_mon(_y,_m,_d,_res) \
  TEST(stm32xx__date, inc_mon__ ## _y ## __ ## _m ## __ ## _d) \
  { \
    stm32xx::date d(_y,_m,_d); \
    d.inc_mon(); \
    CHECK_EQUAL(_y, d.year()); \
    CHECK_EQUAL(_res, d.mon()); \
    CHECK_EQUAL(_d, d.mday()); \
  }

TEST_dec_mon(2013,10, 9,  9);
TEST_dec_mon(2013,10,31,  9);
TEST_dec_mon(2013, 1,10, 12);

TEST_inc_mon(2013,10, 9, 11);
TEST_inc_mon(2013,10,31, 11);
TEST_inc_mon(2013,12,10,  1);

#define TEST_dec_mday(_y,_m,_d,_res) \
  TEST(stm32xx__date, dec_mday__ ## _y ## __ ## _m ## __ ## _d) \
  { \
    stm32xx::date d(_y,_m,_d); \
    d.dec_mday(); \
    CHECK_EQUAL(_y, d.year()); \
    CHECK_EQUAL(_m, d.mon()); \
    CHECK_EQUAL(_res, d.mday()); \
  }
#define TEST_inc_mday(_y,_m,_d,_res) \
  TEST(stm32xx__date, inc_mday__ ## _y ## __ ## _m ## __ ## _d) \
  { \
    stm32xx::date d(_y,_m,_d); \
    d.inc_mday(); \
    CHECK_EQUAL(_y, d.year()); \
    CHECK_EQUAL(_m, d.mon()); \
    CHECK_EQUAL(_res, d.mday()); \
  }

TEST_dec_mday(2013,10, 9,  8);
TEST_dec_mday(2013,10, 1, 31);
TEST_dec_mday(2013, 2, 1, 28);
TEST_dec_mday(2012, 2, 1, 29);
TEST_dec_mday(2100, 2, 1, 28);
TEST_dec_mday(2400, 2, 1, 29);

TEST_inc_mday(2013,10, 9, 10);
TEST_inc_mday(2013,10,30, 31);
TEST_inc_mday(2013,10,31,  1);
TEST_inc_mday(2013, 2,28,  1);
TEST_inc_mday(2012, 2,28, 29);
TEST_inc_mday(2012, 2,29,  1);
TEST_inc_mday(2100, 2,28,  1);
TEST_inc_mday(2400, 2,28, 29);
TEST_inc_mday(2400, 2,29,  1);

#define TEST_inc_date(_y,_m,_d, _y2, _m2, _d2) \
  TEST(stm32xx__date, inc__ ## _y ## __ ## _m ## __ ## _d) \
  { \
    stm32xx::date date(_y,_m,_d); \
    date.inc_date(); \
    CHECK_EQUAL(_y2, date.year()); \
    CHECK_EQUAL(_m2, date.mon()); \
    CHECK_EQUAL(_d2, date.mday()); \
  }

TEST_inc_date(2013, 10, 9, 2013,10,10);
TEST_inc_date(2013, 10,31, 2013,11, 1);
TEST_inc_date(2013,  2,28, 2013, 3, 1);
TEST_inc_date(2013, 12,31, 2014, 1, 1);
TEST_inc_date(2012,  2,28, 2012, 2,29);
TEST_inc_date(2012,  2,29, 2012, 3, 1);
TEST_inc_date(2100,  2,28, 2100, 3, 1);
TEST_inc_date(2400,  2,28, 2400, 2,29);
TEST_inc_date(2400,  2,29, 2400, 3, 1);
TEST_inc_date(STM32XX_DATE_YEAR_MAX,12,31, STM32XX_DATE_YEAR_MIN, 1, 1);

#define TEST_eq(_y1,_m1,_d1,_y2,_m2,_d2,_res) \
  TEST(stm32xx__date, eq__ ## _y1 ## __ ## _m1 ## __ ## _d1 ## ____ ## _y2 ## __ ## _m2 ## __ ## _d2) \
  {\
    CHECK((stm32xx::date(_y1,_m1,_d1) == stm32xx::date(_y2,_m2,_d2)) == _res) \
  }

TEST_eq(2013,10, 9, 2013,10, 9, true);
TEST_eq(2013,10, 9, 2013,10,10, false);
TEST_eq(2013,10, 9, 2013,11, 9, false);
TEST_eq(2013,10, 9, 2014,10, 9, false);

#define TEST_neq(_y1,_m1,_d1,_y2,_m2,_d2,_res) \
  TEST(stm32xx__date, neq__ ## _y1 ## __ ## _m1 ## __ ## _d1 ## ____ ## _y2 ## __ ## _m2 ## __ ## _d2) \
  {\
    CHECK((stm32xx::date(_y1,_m1,_d1) != stm32xx::date(_y2,_m2,_d2)) == _res) \
  }

TEST_neq(2013,10, 9, 2013,10, 9, false);
TEST_neq(2013,10, 9, 2013,10,10, true);
TEST_neq(2013,10, 9, 2013,11, 9, true);
TEST_neq(2013,10, 9, 2014,10, 9, true);

#define TEST_lt(_y1,_m1,_d1,_y2,_m2,_d2,_res) \
  TEST(stm32xx__date, lt__ ## _y1 ## __ ## _m1 ## __ ## _d1 ## ____ ## _y2 ## __ ## _m2 ## __ ## _d2) \
  {\
    CHECK((stm32xx::date(_y1,_m1,_d1) < stm32xx::date(_y2,_m2,_d2)) == _res) \
  }

TEST_lt(2013,10, 9, 2013,10, 9, false);
TEST_lt(2013,10, 9, 2013,10, 8, false);
TEST_lt(2013,10, 9, 2013, 9, 9, false);
TEST_lt(2013,10, 9, 2013, 9,10, false);
TEST_lt(2013,10, 9, 2012, 9, 8, false);

TEST_lt(2013,10, 9, 2014, 1, 1, true);
TEST_lt(2013,10, 9, 2013,11, 1, true);
TEST_lt(2013,10, 9, 2013,10,10, true);

#define TEST_le(_y1,_m1,_d1,_y2,_m2,_d2,_res) \
  TEST(stm32xx__date, le__ ## _y1 ## __ ## _m1 ## __ ## _d1 ## ____ ## _y2 ## __ ## _m2 ## __ ## _d2) \
  {\
    CHECK((stm32xx::date(_y1,_m1,_d1) <= stm32xx::date(_y2,_m2,_d2)) == _res) \
  }

TEST_le(2013,10, 9, 2013,10, 8, false);
TEST_le(2013,10, 9, 2013, 9, 9, false);
TEST_le(2013,10, 9, 2013, 9,10, false);
TEST_le(2013,10, 9, 2012, 9, 8, false);

TEST_le(2013,10, 9, 2013,10, 9, true);
TEST_le(2013,10, 9, 2014, 1, 1, true);
TEST_le(2013,10, 9, 2013,11, 1, true);
TEST_le(2013,10, 9, 2013,10,10, true);

#define TEST_gt(_y1,_m1,_d1,_y2,_m2,_d2,_res) \
  TEST(stm32xx__date, gt__ ## _y1 ## __ ## _m1 ## __ ## _d1 ## ____ ## _y2 ## __ ## _m2 ## __ ## _d2) \
  {\
    CHECK((stm32xx::date(_y1,_m1,_d1) > stm32xx::date(_y2,_m2,_d2)) == _res) \
  }

TEST_gt(2013,10, 9, 2013,10, 9, false);
TEST_gt(2013,10, 8, 2013,10, 9, false);
TEST_gt(2013, 9, 9, 2013,10, 9, false);
TEST_gt(2013, 9,10, 2013,10, 9, false);
TEST_gt(2012, 9, 8, 2013,10, 9, false);

TEST_gt(2014, 1, 1, 2013,10, 9, true);
TEST_gt(2013,11, 1, 2013,10, 9, true);
TEST_gt(2013,10,10, 2013,10, 9, true);

#define TEST_ge(_y1,_m1,_d1,_y2,_m2,_d2,_res) \
  TEST(stm32xx__date, ge__ ## _y1 ## __ ## _m1 ## __ ## _d1 ## ____ ## _y2 ## __ ## _m2 ## __ ## _d2) \
  {\
    CHECK((stm32xx::date(_y1,_m1,_d1) >= stm32xx::date(_y2,_m2,_d2)) == _res) \
  }

TEST_ge(2013,10, 8, 2013,10, 9, false);
TEST_ge(2013, 9, 9, 2013,10, 9, false);
TEST_ge(2013, 9,10, 2013,10, 9, false);
TEST_ge(2012, 9, 8, 2013,10, 9, false);

TEST_ge(2013,10, 9, 2013,10, 9, true);
TEST_ge(2014, 1, 1, 2013,10, 9, true);
TEST_ge(2013,11, 1, 2013,10, 9, true);
TEST_ge(2013,10,10, 2013,10, 9, true);

#define TEST_year_bcdp(_y,_m,_d, _res) \
  TEST(stm32xx__date, year_bcdp__ ## _y ## __ ## _m ## __ ## _d) \
  { \
    CHECK_EQUAL(_res, stm32xx::date(_y,_m,_d).year_bcdp()); \
  }

TEST_year_bcdp(2013, 1, 1, 0x2013);

#define TEST_mon_bcdp(_y,_m,_d, _res) \
  TEST(stm32xx__date, mon_bcdp__ ## _y ## __ ## _m ## __ ## _d) \
  { \
    CHECK_EQUAL(_res, stm32xx::date(_y,_m,_d).mon_bcdp()); \
  }

TEST_mon_bcdp(2013, 1, 1, 0x01);
TEST_mon_bcdp(2013,12, 1, 0x12);

#define TEST_mday_bcdp(_y,_m,_d, _res) \
  TEST(stm32xx__date, mday_bcdp__ ## _y ## __ ## _m ## __ ## _d) \
  { \
    CHECK_EQUAL(_res, stm32xx::date(_y,_m,_d).mday_bcdp()); \
  }

TEST_mday_bcdp(2013, 1, 1, 0x01);
TEST_mday_bcdp(2013, 1,31, 0x31);

#define TEST_date_bcdp(_y,_m,_d, _res) \
  TEST(stm32xx__date, date_bcdp__ ## _y ## __ ## _m ## __ ## _d) \
  { \
    CHECK_EQUAL(_res, stm32xx::date(_y,_m,_d).date_bcdp()); \
  }

TEST_date_bcdp(2013, 1, 1, 0x20130101);
TEST_date_bcdp(2013,12,31, 0x20131231);

#define TEST_to_rtc_dr(_y,_m,_d, _res) \
  TEST(stm32xx__date, to_rtc_dr__ ## _y ## __ ## _m ## __ ## _d) \
  { \
    CHECK_EQUAL(_res, stm32xx::date(_y,_m,_d).to_rtc_dr()); \
  }

TEST_to_rtc_dr(2013, 1, 1, 0x20134101);
TEST_to_rtc_dr(2013,12,31, 0x20135231);

#define TEST_from_rtc_dr(_dr, _y,_m,_d) \
  TEST(stm32xx__date, from_rtc_dr__ ## _dr) \
  { \
    stm32xx::date d = stm32xx::date::from_rtc_dr(_dr); \
    CHECK_EQUAL(_y, d.year()); \
    CHECK_EQUAL(_m, d.mon()); \
    CHECK_EQUAL(_d, d.mday()); \
  }

TEST_from_rtc_dr(0x20134101, 2013, 1, 1);
TEST_from_rtc_dr(0x20135231, 2013,12,31);
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
