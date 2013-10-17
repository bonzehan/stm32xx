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

/** // doc: test/unit/stm32xx/date_test.t.h {{{
 * @file test/unit/stm32xx/date_test.t.h
 * @todo Write documentation
 */ // }}}

#include <stm32xx/date.hpp>
#include <cxxtest/TestSuite.h>


#define STM32XX_DATE_YEAR_MIN_minus_1 (STM32XX_DATE_YEAR_MIN-1)
#define STM32XX_DATE_YEAR_MAX_plus_1  (STM32XX_DATE_YEAR_MAX+1)

class stm32xx__date__testsuite : public CxxTest::TestSuite
{
public:
  void test__date(void)
  {
    using namespace stm32xx;
    date dt;
    TS_ASSERT_EQUALS(STM32XX_DATE_DEFAULT_YEAR, dt.year());
    TS_ASSERT_EQUALS(STM32XX_DATE_DEFAULT_MON, dt.mon());
    TS_ASSERT_EQUALS(STM32XX_DATE_DEFAULT_MDAY, dt.mday());
  };

  void test__date__year__mon__mday(void)
  {
    using namespace stm32xx;
    date dt(2013,10,9);
    TS_ASSERT_EQUALS(2013, dt.year());
    TS_ASSERT_EQUALS(10, dt.mon());
    TS_ASSERT_EQUALS(9, dt.mday());
  };

  void test__leap_year(void)
  {
    using namespace stm32xx;
    TS_ASSERT(date::leap_year(2012) == true);
    TS_ASSERT(date::leap_year(2013) == false);
    TS_ASSERT(date::leap_year(2100) == false);
    TS_ASSERT(date::leap_year(2400) == true);
  }
 
  void test__mdays(void)
  {
    using namespace stm32xx;
    TS_ASSERT_EQUALS((date::mdays(2013,1)), 31);
    TS_ASSERT_EQUALS((date::mdays(2013,2)), 28);
    TS_ASSERT_EQUALS((date::mdays(2013,3)), 31);
    TS_ASSERT_EQUALS((date::mdays(2013,4)), 30);
    TS_ASSERT_EQUALS((date::mdays(2013,5)), 31);
    TS_ASSERT_EQUALS((date::mdays(2013,6)), 30);
    TS_ASSERT_EQUALS((date::mdays(2013,7)), 31);
    TS_ASSERT_EQUALS((date::mdays(2013,8)), 31);
    TS_ASSERT_EQUALS((date::mdays(2013,9)), 30);
    TS_ASSERT_EQUALS((date::mdays(2013,10)),31);
    TS_ASSERT_EQUALS((date::mdays(2013,11)),30);
    TS_ASSERT_EQUALS((date::mdays(2013,12)),31);
    TS_ASSERT_EQUALS((date::mdays(2012,2)), 29);
    TS_ASSERT_EQUALS((date::mdays(2100,2)), 28);
    TS_ASSERT_EQUALS((date::mdays(2400,2)), 29);
  }

  void test__gday(void)
  {
    using namespace stm32xx;
    TS_ASSERT_EQUALS((date::gday(1582,10,15)),1);
    TS_ASSERT_EQUALS((date::gday(2013,10,12)),157418);
    TS_ASSERT_EQUALS((date::gday(2013,12,31)),157498);
    TS_ASSERT_EQUALS((date::gday(2100,3,1)),  188969);
    TS_ASSERT_EQUALS((date::gday(2400,2,29)), 298541);
  }

  void test__yday(void)
  {
    using namespace stm32xx;
    TS_ASSERT_EQUALS((date::yday(2013,1,1)),  0);
    TS_ASSERT_EQUALS((date::yday(2013,1,31)), 30);
    TS_ASSERT_EQUALS((date::yday(2013,2,1)),  31);
    TS_ASSERT_EQUALS((date::yday(2013,2,28)), 58);
    TS_ASSERT_EQUALS((date::yday(2013,12,31)),364);
    TS_ASSERT_EQUALS((date::yday(2012,12,31)),365);
    TS_ASSERT_EQUALS((date::yday(2100,12,31)),364);
    TS_ASSERT_EQUALS((date::yday(2400,12,31)),365);
  }

  void test__wday(void)
  {
    using namespace stm32xx;
    TS_ASSERT_EQUALS((date(2013,1,1).wday()),   date::wday_tue);
    TS_ASSERT_EQUALS((date(2013,2,15).wday()),  date::wday_fri);
    TS_ASSERT_EQUALS((date(2013,3,1).wday()),   date::wday_fri);
    TS_ASSERT_EQUALS((date(2013,4,1).wday()),   date::wday_mon);
    TS_ASSERT_EQUALS((date(2013,4,2).wday()),   date::wday_tue);
    TS_ASSERT_EQUALS((date(2013,4,3).wday()),   date::wday_wed);
    TS_ASSERT_EQUALS((date(2013,4,4).wday()),   date::wday_thu);
    TS_ASSERT_EQUALS((date(2013,4,5).wday()),   date::wday_fri);
    TS_ASSERT_EQUALS((date(2013,4,6).wday()),   date::wday_sat);
    TS_ASSERT_EQUALS((date(2013,4,7).wday()),   date::wday_sun);
    TS_ASSERT_EQUALS((date(2013,12,31).wday()), date::wday_tue);
    TS_ASSERT_EQUALS((date(2100,2,28).wday()),  date::wday_sun);
    TS_ASSERT_EQUALS((date(2400,2,29).wday()),  date::wday_tue);
  }

  void test__clamp_year(void)
  {
    using namespace stm32xx;
    TS_ASSERT_EQUALS(date::clamp_year(2013), 2013);
    TS_ASSERT_EQUALS(date::clamp_year(STM32XX_DATE_YEAR_MIN), STM32XX_DATE_YEAR_MIN);
    TS_ASSERT_EQUALS(date::clamp_year(STM32XX_DATE_YEAR_MAX), STM32XX_DATE_YEAR_MAX);
    TS_ASSERT_EQUALS(date::clamp_year(STM32XX_DATE_YEAR_MIN_minus_1), STM32XX_DATE_YEAR_MIN);
    TS_ASSERT_EQUALS(date::clamp_year(STM32XX_DATE_YEAR_MAX_plus_1), STM32XX_DATE_YEAR_MAX);
  }

  void test__clamp_mon(void)
  {
    using namespace stm32xx;
    TS_ASSERT_EQUALS((date::clamp_mon(1)),   1);
    TS_ASSERT_EQUALS((date::clamp_mon(6)),   6);
    TS_ASSERT_EQUALS((date::clamp_mon(12)), 12);
    TS_ASSERT_EQUALS((date::clamp_mon(0)),   1);
    TS_ASSERT_EQUALS((date::clamp_mon(13)), 12);
  }

  void test__clamp_mday(void)
  {
    using namespace stm32xx;
    TS_ASSERT_EQUALS((date::clamp_mday(2013, 1,1)),   1);
    TS_ASSERT_EQUALS((date::clamp_mday(2013, 1,31)), 31);
    TS_ASSERT_EQUALS((date::clamp_mday(2013, 6,5)),   5);
    TS_ASSERT_EQUALS((date::clamp_mday(2013,10,0)),   1);
    TS_ASSERT_EQUALS((date::clamp_mday(2012, 2,29)), 29);
    TS_ASSERT_EQUALS((date::clamp_mday(2400, 2,29)), 29)

    TS_ASSERT_EQUALS((date::clamp_mday(2013,10,32)), 31);
    TS_ASSERT_EQUALS((date::clamp_mday(2013, 9,31)), 30);
    TS_ASSERT_EQUALS((date::clamp_mday(2013, 9,32)), 30);
    TS_ASSERT_EQUALS((date::clamp_mday(2013, 2,29)), 28);
    TS_ASSERT_EQUALS((date::clamp_mday(2012, 2,30)), 29);
    TS_ASSERT_EQUALS((date::clamp_mday(2100, 2,29)), 28)
    TS_ASSERT_EQUALS((date::clamp_mday(2400, 2,30)), 29)
  }


  void test__date_valid(void)
  {
    using namespace stm32xx;
    TS_ASSERT_EQUALS((date(2013,10,9).date_valid()),true);
    TS_ASSERT_EQUALS((date(STM32XX_DATE_YEAR_MIN, 10, 9).date_valid()), true);
    TS_ASSERT_EQUALS((date(STM32XX_DATE_YEAR_MAX, 10, 9).date_valid()), true);
    TS_ASSERT_EQUALS((date(2013,1,1).date_valid()),true);
    TS_ASSERT_EQUALS((date(2013,12,31).date_valid()),true);
    TS_ASSERT_EQUALS((date(2013,2,28).date_valid()),true);
    TS_ASSERT_EQUALS((date(2012,2,29).date_valid()),true);
    TS_ASSERT_EQUALS((date(2400,2,29).date_valid()),true);

    TS_ASSERT_EQUALS((date(STM32XX_DATE_YEAR_MIN_minus_1,10, 9).date_valid()), false);
    TS_ASSERT_EQUALS((date(STM32XX_DATE_YEAR_MAX_plus_1,10, 9).date_valid()), false);
    TS_ASSERT_EQUALS((date(2013,0,1).date_valid()),false);
    TS_ASSERT_EQUALS((date(2013,13,1).date_valid()),false);
    TS_ASSERT_EQUALS((date(2013,1,0).date_valid()),false);
    TS_ASSERT_EQUALS((date(2013,1,32).date_valid()),false);
    TS_ASSERT_EQUALS((date(2013,2,29).date_valid()),false);
    TS_ASSERT_EQUALS((date(2013,4,31).date_valid()),false);
    TS_ASSERT_EQUALS((date(2100,2,29).date_valid()),false);
  }

  void clamp_date_check(int32_t y, int32_t  m,  int32_t d,
                              int32_t y2, int32_t m2, int32_t d2)
  {
      stm32xx::date date(y,m,d);
      date.clamp_date(); 
      TS_ASSERT_EQUALS(y2, date.year());
      TS_ASSERT_EQUALS(m2, date.mon());
      TS_ASSERT_EQUALS(d2, date.mday());
  }

  void test__clamp_date(void)
  {
    clamp_date_check(2013,10, 9, 2013,10, 9);
    clamp_date_check(STM32XX_DATE_YEAR_MAX,12,31, STM32XX_DATE_YEAR_MAX,12,31);

    clamp_date_check(STM32XX_DATE_YEAR_MAX_plus_1,12,31, STM32XX_DATE_YEAR_MAX,12,31);

    clamp_date_check(2013, 0, 1, 2013, 1, 1);
    clamp_date_check(2013,13,31, 2013,12,31);

    clamp_date_check(2013,10, 0, 2013,10, 1);
    clamp_date_check(2013,10,32, 2013,10,31);
    clamp_date_check(2013,11,32, 2013,11,30);
    clamp_date_check(2013, 2,29, 2013, 2,28);
    clamp_date_check(2012, 2,30, 2012, 2,29);

    clamp_date_check(STM32XX_DATE_YEAR_MAX_plus_1,  0, 1, STM32XX_DATE_YEAR_MAX, 1, 1);
    clamp_date_check(STM32XX_DATE_YEAR_MAX_plus_1, 13, 1, STM32XX_DATE_YEAR_MAX,12, 1);

#if STM32XX_DATE_YEAR_MIN > 1582
    clamp_date_check(STM32XX_DATE_YEAR_MIN, 1, 1, STM32XX_DATE_YEAR_MIN, 1, 1);
    clamp_date_check(STM32XX_DATE_YEAR_MIN_minus_1, 1, 1, STM32XX_DATE_YEAR_MIN, 1, 1);
    clamp_date_check(STM32XX_DATE_YEAR_MIN_minus_1, 0, 1, STM32XX_DATE_YEAR_MIN, 1, 1);
    clamp_date_check(STM32XX_DATE_YEAR_MIN_minus_1,13, 1, STM32XX_DATE_YEAR_MIN,12, 1);
    clamp_date_check(STM32XX_DATE_YEAR_MIN_minus_1, 2,30, STM32XX_DATE_YEAR_MIN, 2,
                    (stm32xx::date::leap_year(STM32XX_DATE_YEAR_MIN) ? 29 :28));
    clamp_date_check(STM32XX_DATE_YEAR_MIN_minus_1, 2,29, STM32XX_DATE_YEAR_MIN, 2,
                    (stm32xx::date::leap_year(STM32XX_DATE_YEAR_MIN) ? 29 :28));
#else
    clamp_date_check(STM32XX_DATE_YEAR_MIN,         1, 1, 1582, 10, 15);
    clamp_date_check(STM32XX_DATE_YEAR_MIN_minus_1, 1, 1, 1582, 10, 15);
    clamp_date_check(STM32XX_DATE_YEAR_MIN_minus_1, 0, 1, 1582, 10, 15);
    clamp_date_check(STM32XX_DATE_YEAR_MIN_minus_1,13, 1, 1582, 10, 15);
    clamp_date_check(STM32XX_DATE_YEAR_MIN_minus_1, 2,30, 1582, 10, 15);
    clamp_date_check(STM32XX_DATE_YEAR_MIN_minus_1, 2,29, 1582, 10, 15);
#endif

    clamp_date_check(STM32XX_DATE_YEAR_MAX_plus_1,  2,30, STM32XX_DATE_YEAR_MAX, 2, 
                    (stm32xx::date::leap_year(STM32XX_DATE_YEAR_MAX) ? 29 :28));
    clamp_date_check(STM32XX_DATE_YEAR_MAX_plus_1,  2,29, STM32XX_DATE_YEAR_MAX, 2, 
                    (stm32xx::date::leap_year(STM32XX_DATE_YEAR_MAX) ? 29 :28));
  }

  void dec_year_check(int32_t y, int32_t m, int32_t d, int32_t res)
  {
      stm32xx::date dt(y,m,d);
      dt.dec_year();
      TS_ASSERT_EQUALS(res, dt.year());
      TS_ASSERT_EQUALS(m, dt.mon());
      TS_ASSERT_EQUALS(d, dt.mday());
  }
  void test__dec_year(void)
  {
    dec_year_check(2013, 1,10,  2012);
    dec_year_check(2012, 2,29,  2011);
    dec_year_check(STM32XX_DATE_YEAR_MIN, 1,10,  STM32XX_DATE_YEAR_MAX);
  }

  void inc_year_check(int32_t y, int32_t m, int32_t d, int32_t res)
  {
    stm32xx::date dt(y,m,d);
    dt.inc_year();
    TS_ASSERT_EQUALS(res, dt.year());
    TS_ASSERT_EQUALS(m, dt.mon());
    TS_ASSERT_EQUALS(d, dt.mday());
  }
  void test__inc_year(void)
  {
    inc_year_check(2013, 1,10, 2014);
    inc_year_check(2012, 2,29, 2013);
    inc_year_check(STM32XX_DATE_YEAR_MAX, 1,10,  STM32XX_DATE_YEAR_MIN);
  }

  void dec_mon_check(int32_t y, int32_t m, int32_t d, int32_t res)
  {
    stm32xx::date dt(y,m,d);
    dt.dec_mon();
    TS_ASSERT_EQUALS(y, dt.year());
    TS_ASSERT_EQUALS(res, dt.mon());
    TS_ASSERT_EQUALS(d, dt.mday());
  }

  void test__dec_mon(void)
  {
    dec_mon_check(2013,10, 9,  9);
    dec_mon_check(2013,10,31,  9);
    dec_mon_check(2013, 1,10, 12);
  }

  void inc_mon_check(int32_t y, int32_t m, int32_t d, int32_t res)
  {
    stm32xx::date dt(y,m,d);
    dt.inc_mon();
    TS_ASSERT_EQUALS(y, dt.year());
    TS_ASSERT_EQUALS(res, dt.mon());
    TS_ASSERT_EQUALS(d, dt.mday());
  }

  void test__inc_mon(void)
  {
    inc_mon_check(2013,10, 9, 11);
    inc_mon_check(2013,10,31, 11);
    inc_mon_check(2013,12,10,  1);
  }

  void dec_mday_check(int32_t y, int32_t m, int32_t d, int32_t res)
  {
    stm32xx::date dt(y,m,d);
    dt.dec_mday();
    TS_ASSERT_EQUALS(y, dt.year());
    TS_ASSERT_EQUALS(m, dt.mon());
    TS_ASSERT_EQUALS(res, dt.mday());
  }

  void test__dec_mday(void)
  {
    dec_mday_check(2013,10, 9,  8);
    dec_mday_check(2013,10, 1, 31);
    dec_mday_check(2013, 2, 1, 28);
    dec_mday_check(2012, 2, 1, 29);
    dec_mday_check(2100, 2, 1, 28);
    dec_mday_check(2400, 2, 1, 29);
  }

  void inc_mday_check(int32_t y, int32_t m, int32_t d, int32_t res)
  {
    stm32xx::date dt(y,m,d);
    dt.inc_mday();
    TS_ASSERT_EQUALS(y, dt.year());
    TS_ASSERT_EQUALS(m, dt.mon());
    TS_ASSERT_EQUALS(res, dt.mday());
  }

  void test__inc_mday(void)
  {
    inc_mday_check(2013,10, 9, 10);
    inc_mday_check(2013,10,30, 31);
    inc_mday_check(2013,10,31,  1);
    inc_mday_check(2013, 2,28,  1);
    inc_mday_check(2012, 2,28, 29);
    inc_mday_check(2012, 2,29,  1);
    inc_mday_check(2100, 2,28,  1);
    inc_mday_check(2400, 2,28, 29);
    inc_mday_check(2400, 2,29,  1);
  }

  void inc_date_check(int32_t y, int32_t m, int32_t d, int32_t y2, int32_t m2, int32_t d2)
  {
    stm32xx::date date(y,m,d);
    date.inc_date();
    TS_ASSERT_EQUALS(y2, date.year());
    TS_ASSERT_EQUALS(m2, date.mon());
    TS_ASSERT_EQUALS(d2, date.mday());
  }

  void test__inc_date(void)
  {
    inc_date_check(2013, 10, 9, 2013,10,10);
    inc_date_check(2013, 10,31, 2013,11, 1);
    inc_date_check(2013,  2,28, 2013, 3, 1);
    inc_date_check(2013, 12,31, 2014, 1, 1);
    inc_date_check(2012,  2,28, 2012, 2,29);
    inc_date_check(2012,  2,29, 2012, 3, 1);
    inc_date_check(2100,  2,28, 2100, 3, 1);
    inc_date_check(2400,  2,28, 2400, 2,29);
    inc_date_check(2400,  2,29, 2400, 3, 1);
    inc_date_check(STM32XX_DATE_YEAR_MAX,12,31, STM32XX_DATE_YEAR_MIN, 10, 15);
  }

  void test__eq(void)
  {
    using namespace stm32xx;
    TS_ASSERT_EQUALS((date(2013,10, 9) == date(2013,10, 9)), true);
    TS_ASSERT_EQUALS((date(2013,10, 9) == date(2013,10,10)), false);
    TS_ASSERT_EQUALS((date(2013,10, 9) == date(2013,11, 9)), false);
    TS_ASSERT_EQUALS((date(2013,10, 9) == date(2014,10, 9)), false);
  }

  void test__neq(void)
  {
    using namespace stm32xx;
    TS_ASSERT_EQUALS((date(2013,10, 9) != date(2013,10, 9)), false);
    TS_ASSERT_EQUALS((date(2013,10, 9) != date(2013,10,10)), true);
    TS_ASSERT_EQUALS((date(2013,10, 9) != date(2013,11, 9)), true);
    TS_ASSERT_EQUALS((date(2013,10, 9) != date(2014,10, 9)), true);
  }

  void test__lt(void)
  {
    using namespace stm32xx;

    TS_ASSERT_EQUALS((date(2013,10,9) < date(2013,10,9)), false);
    TS_ASSERT_EQUALS((date(2013,10,9) < date(2013,10,8)), false);
    TS_ASSERT_EQUALS((date(2013,10,9) < date(2013,9,9)), false);
    TS_ASSERT_EQUALS((date(2013,10,9) < date(2013,9,10)), false);
    TS_ASSERT_EQUALS((date(2013,10,9) < date(2012,9,8)), false);

    TS_ASSERT_EQUALS((date(2013,10,9) < date(2014,1,1)), true);
    TS_ASSERT_EQUALS((date(2013,10,9) < date(2013,11,1)), true);
    TS_ASSERT_EQUALS((date(2013,10,9) < date(2013,10,10)), true);
  }

  void test__le(void)
  {
    using namespace stm32xx;

    TS_ASSERT_EQUALS((date(2013,10,9) <= date(2013,10,8)), false);
    TS_ASSERT_EQUALS((date(2013,10,9) <= date(2013,9,9)), false);
    TS_ASSERT_EQUALS((date(2013,10,9) <= date(2013,9,10)), false);
    TS_ASSERT_EQUALS((date(2013,10,9) <= date(2012,9,8)), false);

    TS_ASSERT_EQUALS((date(2013,10,9) <= date(2013,10,9)), true);
    TS_ASSERT_EQUALS((date(2013,10,9) <= date(2014,1,1)), true);
    TS_ASSERT_EQUALS((date(2013,10,9) <= date(2013,11,1)), true);
    TS_ASSERT_EQUALS((date(2013,10,9) <= date(2013,10,10)), true);
  }

  void test__gt(void)
  {
    using namespace stm32xx;

    TS_ASSERT_EQUALS((date(2013,10,9) > date(2013,10,9)), false);
    TS_ASSERT_EQUALS((date(2013,10,8) > date(2013,10,9)), false);
    TS_ASSERT_EQUALS((date(2013,9,9) > date(2013,10,9)), false);
    TS_ASSERT_EQUALS((date(2013,9,10) > date(2013,10,9)), false);
    TS_ASSERT_EQUALS((date(2012,9,8) > date(2013,10,9)), false);

    TS_ASSERT_EQUALS((date(2014,1,1) > date(2013,10,9)), true);
    TS_ASSERT_EQUALS((date(2013,11,1) > date(2013,10,9)), true);
    TS_ASSERT_EQUALS((date(2013,10,10) > date(2013,10,9)), true);
  }

  void test__ge(void)
  {
    using namespace stm32xx;

    TS_ASSERT_EQUALS((date(2013,10,8) >= date(2013,10,9)), false);
    TS_ASSERT_EQUALS((date(2013,9,9) >= date(2013,10,9)), false);
    TS_ASSERT_EQUALS((date(2013,9,10) >= date(2013,10,9)), false);
    TS_ASSERT_EQUALS((date(2012,9,8) >= date(2013,10,9)), false);

    TS_ASSERT_EQUALS((date(2013,10,9) >= date(2013,10,9)), true);
    TS_ASSERT_EQUALS((date(2014,1,1) >= date(2013,10,9)), true);
    TS_ASSERT_EQUALS((date(2013,11,1) >= date(2013,10,9)), true);
    TS_ASSERT_EQUALS((date(2013,10,10) >= date(2013,10,9)), true);
  }

  void test__year_bcdp(void)
  {
    TS_ASSERT_EQUALS((stm32xx::date(2013,1,1).year_bcdp()), 0x2013);
  }

  void test__mon_bcdp(void)
  {
    TS_ASSERT_EQUALS((stm32xx::date(2013,1, 1).mon_bcdp()), 0x01);
    TS_ASSERT_EQUALS((stm32xx::date(2013,12,1).mon_bcdp()), 0x12);
  }

  void test__mday_bcdp(void)
  {
    TS_ASSERT_EQUALS((stm32xx::date(2013,1, 1).mday_bcdp()), 0x01);
    TS_ASSERT_EQUALS((stm32xx::date(2013,1,31).mday_bcdp()), 0x31);
  }

  void test__date_bcdp(void)
  {
    TS_ASSERT_EQUALS((stm32xx::date(2013, 1, 1).date_bcdp()), 0x20130101);
    TS_ASSERT_EQUALS((stm32xx::date(2013,12,31).date_bcdp()), 0x20131231);
  }

  void test__to_rtc_dr(void)
  {
    TS_ASSERT_EQUALS((stm32xx::date(2013, 1, 1).to_rtc_dr()), 0x20134101);
    TS_ASSERT_EQUALS((stm32xx::date(2013,12,31).to_rtc_dr()), 0x20135231);
  }

  void from_gday_check(int32_t g, int32_t y, int32_t m, int32_t d)
  {
    stm32xx::date dt(stm32xx::date::from_gday(g));
    TS_ASSERT_EQUALS(y, dt.year());
    TS_ASSERT_EQUALS(m, dt.mon());
    TS_ASSERT_EQUALS(d, dt.mday());
  }

  void test__from_gday(void)
  {
    from_gday_check(1,      1582,10,15);
    from_gday_check(157418, 2013,10,12);
    from_gday_check(157498, 2013,12,31);
    from_gday_check(188969, 2100, 3, 1);
    from_gday_check(298541, 2400, 2,29);
    from_gday_check(917933, 4095,12,31);
  }

  void from_rtc_dr_check(uint32_t dr, int32_t y, int32_t m, int32_t d)
  {
    stm32xx::date dt(stm32xx::date::from_rtc_dr(dr));
    TS_ASSERT_EQUALS(y, dt.year());
    TS_ASSERT_EQUALS(m, dt.mon());
    TS_ASSERT_EQUALS(d, dt.mday());
  }

  void test__form_rtc_dr(void)
  {
    from_rtc_dr_check(0x20134101, 2013, 1, 1);
    from_rtc_dr_check(0x20135231, 2013,12,31);
  }
};

// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
