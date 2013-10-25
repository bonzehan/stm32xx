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

/** // doc: test/unit/stm32xx/daytime_test.t.h {{{
 * @file test/unit/stm32xx/daytime_test.t.h
 * @todo Write documentation
 */ // }}}
#include <stm32xx/daytime.hpp>
#include <cxxtest/TestSuite.h>

class stm32xx__time__testsuite : public CxxTest::TestSuite
{
public:
  using sec_cnt_t = stm32xx::daytime::sec_cnt_t;
  using hour_t = stm32xx::daytime::hour_t;
  using min_t = stm32xx::daytime::min_t;
  using sec_t = stm32xx::daytime::sec_t;
  using flag_t = stm32xx::daytime::flag_t;

  void set_hour_check(sec_cnt_t c, hour_t h)
  {
    stm32xx::daytime t(c);
    t.set_hour(h);
    TS_ASSERT_EQUALS(h, t.hour());
    TS_ASSERT_EQUALS((c/86400ul), (t.sec_cnt()/86400ul));
    TS_ASSERT_EQUALS((c%3600ul),  (t.sec_cnt()%3600ul));
  }

  void set_min_check(sec_cnt_t c, min_t m)
  {
    stm32xx::daytime t(c);
    t.set_min(m);
    TS_ASSERT_EQUALS(m, t.min());
    TS_ASSERT_EQUALS(((uint32_t)c/3600ul), ((uint32_t)t.sec_cnt()/3600ul));
    TS_ASSERT_EQUALS(((uint32_t)c%60ul), ((uint32_t)t.sec_cnt()%60ul));
  }
 
  void set_sec_check(sec_cnt_t c, sec_t s)
  {
    stm32xx::daytime t(c);
    t.set_sec(s);
    TS_ASSERT_EQUALS(s, t.sec());
    TS_ASSERT_EQUALS(((uint32_t)c/60ul), ((uint32_t)t.sec_cnt()/60ul)); 
  }

  void set_flags_check(flag_t f)
  {
    stm32xx::daytime t;
    t.set_flags(f);
    TS_ASSERT_EQUALS(f, t.flags());
  }

  void set_daytime_check(stm32xx::daytime const& other)
  {
    stm32xx::daytime t;
    t.set_daytime(other);
    TS_ASSERT_EQUALS(t, other);
  }

  void set_daytime_check(hour_t h, min_t m, sec_t s)
  {
    stm32xx::daytime t;
    t.set_daytime(h,m,s);
    TS_ASSERT_EQUALS(h, t.hour());
    TS_ASSERT_EQUALS(m, t.min());
    TS_ASSERT_EQUALS(s, t.sec());
  }

  void set_daytime_check(hour_t h, min_t m, sec_t s, flag_t f)
  {
    stm32xx::daytime t;
    t.set_daytime(h,m,s,f);
    TS_ASSERT_EQUALS(h, t.hour());
    TS_ASSERT_EQUALS(m, t.min());
    TS_ASSERT_EQUALS(s, t.sec());
    TS_ASSERT_EQUALS(f, t.flags());
  }

  void set_daytime_check(sec_cnt_t s)
  {
    stm32xx::daytime t;
    t.set_daytime(s);
    TS_ASSERT_EQUALS(s, t.sec_cnt());
  }

  void set_daytime_check(sec_cnt_t s, flag_t f)
  {
    stm32xx::daytime t;
    t.set_daytime(s,f);
    TS_ASSERT_EQUALS(s, t.sec_cnt());
    TS_ASSERT_EQUALS(f, t.flags());
  }

  void inc_hour_check(sec_cnt_t s, hour_t res)
  {
    stm32xx::daytime t(s);
    t.inc_hour();
    TS_ASSERT_EQUALS(res, t.hour());
    TS_ASSERT_EQUALS((s/86400ul), (t.sec_cnt()/86400ul));
    TS_ASSERT_EQUALS((s%3600ul),  (t.sec_cnt()%3600ul));
  }

  void dec_hour_check(sec_cnt_t s, hour_t res)
  {
    stm32xx::daytime t(s);
    t.dec_hour();
    TS_ASSERT_EQUALS(res, t.hour());
    TS_ASSERT_EQUALS((s/86400ul), (t.sec_cnt()/86400ul));
    TS_ASSERT_EQUALS((s%3600ul),  (t.sec_cnt()%3600ul));
  }

  void inc_min_check(sec_cnt_t s, min_t res)
  {
    stm32xx::daytime t(s);
    t.inc_min();
    TS_ASSERT_EQUALS(res, t.min());
    TS_ASSERT_EQUALS(((uint32_t)s/3600ul), ((uint32_t)t.sec_cnt()/3600ul));
    TS_ASSERT_EQUALS(((uint32_t)s%60ul), ((uint32_t)t.sec_cnt()%60ul));
  }

  void dec_min_check(sec_cnt_t s, min_t res)
  {
    stm32xx::daytime t(s);
    t.dec_min();
    TS_ASSERT_EQUALS(res, t.min());
    TS_ASSERT_EQUALS(((uint32_t)s/3600ul), ((uint32_t)t.sec_cnt()/3600ul));
    TS_ASSERT_EQUALS(((uint32_t)s%60ul),   ((uint32_t)t.sec_cnt()%60ul));
  }

  void inc_sec_check(sec_cnt_t s, sec_t res)
  {
    stm32xx::daytime t(s);
    t.inc_sec();
    TS_ASSERT_EQUALS(res, t.sec());
    TS_ASSERT_EQUALS(((uint32_t)s/60ul), ((uint32_t)t.sec_cnt()/60ul)); 
  }

  void dec_sec_check(sec_cnt_t s, sec_t res)
  {
    stm32xx::daytime t(s);
    t.dec_sec();
    TS_ASSERT_EQUALS(res, t.sec());
    TS_ASSERT_EQUALS(((uint32_t)s/60ul), ((uint32_t)t.sec_cnt()/60ul)); 
  }

  void advance_daytime_check(hour_t h, min_t m, sec_t s, int32_t x, int32_t res,
                         hour_t h2, min_t m2, sec_t s2)
  {
    stm32xx::daytime t(h,m,s);
    TS_ASSERT_EQUALS(res, t.advance_daytime(x));
    TS_ASSERT_EQUALS(h2, t.hour());
    TS_ASSERT_EQUALS(m2, t.min());
    TS_ASSERT_EQUALS(s2, t.sec());
  }

  void advance_daytime_check(int32_t h, int32_t m, int32_t s, int32_t x, 
                          int32_t res, int32_t h2, int32_t m2, int32_t s2)
  {
    stm32xx::daytime t(h,m,s);
    TS_ASSERT_EQUALS(res, t.advance_daytime(x));
    TS_ASSERT_EQUALS(h2, t.hour());
    TS_ASSERT_EQUALS(m2, t.min());
    TS_ASSERT_EQUALS(s2, t.sec());
  }

  /*
   * daytime()
   */
  void test__time(void)
  { 
    using daytime = stm32xx::daytime;

    /* daytime() */
    TS_ASSERT_EQUALS(0ul,   daytime().sec_cnt());
    TS_ASSERT_EQUALS(0,     daytime().flags());
    /* daytime(10ul) */
    TS_ASSERT_EQUALS(10ul,    daytime(10ul).sec_cnt()); 
    TS_ASSERT_EQUALS(0ul,     daytime(10ul).hour()); 
    TS_ASSERT_EQUALS(0ul,     daytime(10ul).min()); 
    TS_ASSERT_EQUALS(10ul,    daytime(10ul).sec()); 
    TS_ASSERT_EQUALS(0,       daytime(10ul).flags());
    /* daytime(0, flag_isdst) */
    TS_ASSERT_EQUALS(daytime::flag_isdst, daytime(0ul, daytime::flag_isdst).flags());
    /* daytime(76750ul) */
    TS_ASSERT_EQUALS(76750ul, daytime(76750ul).sec_cnt());
    TS_ASSERT_EQUALS(21,      daytime(76750ul).hour());
    TS_ASSERT_EQUALS(9,       daytime(76750ul).hour12());
    TS_ASSERT_EQUALS(19,      daytime(76750ul).min());
    TS_ASSERT_EQUALS(10,      daytime(76750ul).sec());
    TS_ASSERT_EQUALS(0,       daytime(76750ul).flags());
    /* daytime(21,19,10) */
    TS_ASSERT_EQUALS(21,      daytime(21,19,10).hour());
    TS_ASSERT_EQUALS(19,      daytime(21,19,10).min());
    TS_ASSERT_EQUALS(10,      daytime(21,19,10).sec());
    TS_ASSERT_EQUALS(76750ul, daytime(21,19,10).sec_cnt());
    TS_ASSERT_EQUALS(0,       daytime(21,19,10).flags());
    /* daytime(21,19,10,flag_isdst) */
    TS_ASSERT_EQUALS(daytime::flag_isdst, daytime(21,19,10, daytime::flag_isdst).flags());
    /* daytime(9,19,10,false) */
    TS_ASSERT_EQUALS(9,       daytime(9,19,10,false).hour12());
    TS_ASSERT_EQUALS(19,      daytime(9,19,10,false).min());
    TS_ASSERT_EQUALS(10,      daytime(9,19,10,false).sec());
    TS_ASSERT_EQUALS(33550ul, daytime(9,19,10,false).sec_cnt());
    TS_ASSERT_EQUALS(0,       daytime(9,19,10,false).flags());
    TS_ASSERT(daytime(9,19,10,false).pm() == false);
    /* daytime(9,19,10,false,flag_isdst) */
    TS_ASSERT_EQUALS(daytime::flag_isdst, daytime(9,19,10,false, daytime::flag_isdst).flags());
    /* daytime(9,19,10,true) */
    TS_ASSERT_EQUALS(9,       daytime(9,19,10,true).hour12());
    TS_ASSERT_EQUALS(19,      daytime(9,19,10,true).min());
    TS_ASSERT_EQUALS(10,      daytime(9,19,10,true).sec());
    TS_ASSERT_EQUALS(76750ul, daytime(9,19,10,true).sec_cnt()); 
    TS_ASSERT_EQUALS(0,       daytime(9,19,10,true).flags()); 
    TS_ASSERT(daytime(9,19,10,true).pm() == true);
    /* daytime(9,19,10,true,flag_isdst) */
    TS_ASSERT_EQUALS(daytime::flag_isdst, daytime(9,19,10,true,daytime::flag_isdst).flags()); 
  }

  /*
   * from_rtc_tr(tr)
   */
  void test__from_rtc_tr(void)
  { 
    using daytime = stm32xx::daytime;
    /* 0x00211244 */
    TS_ASSERT_EQUALS(21,      daytime::from_rtc_tr(0x00211244).hour());
    TS_ASSERT_EQUALS(12,      daytime::from_rtc_tr(0x00211244).min());
    TS_ASSERT_EQUALS(44,      daytime::from_rtc_tr(0x00211244).sec());
    TS_ASSERT_EQUALS(76364ul, daytime::from_rtc_tr(0x00211244).sec_cnt());
  }

  /*
   * hour12()
   */
  void test__hour12(void)
  { 
    using daytime = stm32xx::daytime;
    TS_ASSERT_EQUALS(12,  daytime(0,0,0).hour12()); 
    TS_ASSERT_EQUALS(12,  daytime(12,0,0).hour12());
    TS_ASSERT_EQUALS(1,   daytime(13,1,2).hour12());
  }

  /*
   * pm()
   */
  void test__pm(void)
  { 
    using daytime = stm32xx::daytime;
    TS_ASSERT(daytime(0,0,0).pm()==false); 
    TS_ASSERT(daytime(12,0,0).pm()==true);
    TS_ASSERT(daytime(9,19,10).pm() == false); 
    TS_ASSERT(daytime(21,19,10).pm() == true); 
  }

  /*
   * hour_bcdp()
   */
  void test__hour_bcdp(void)
  { 
    using daytime = stm32xx::daytime;
    TS_ASSERT_EQUALS(0x03,daytime(3,0,0).hour_bcdp());
    TS_ASSERT_EQUALS(0x13,daytime(13,0,0).hour_bcdp());
    TS_ASSERT_EQUALS(0x23,daytime(23,0,0).hour_bcdp());
  }

  /*
   * hour12_bcdp()
   */
  void test__hour12_bcdp(void)
  { 
    using daytime = stm32xx::daytime;
    TS_ASSERT_EQUALS(0x03,daytime(3,0,0,false).hour12_bcdp());
    TS_ASSERT_EQUALS(0x12,daytime(12,0,0,false).hour12_bcdp());
  }

  /*
   * min_bcdp()
   */
  void test__min_bcdp(void)
  {
    using daytime = stm32xx::daytime;
    TS_ASSERT_EQUALS(0x00,daytime(0,0,0).min_bcdp()); 
    TS_ASSERT_EQUALS(0x02,daytime(0,2,0).min_bcdp());
    TS_ASSERT_EQUALS(0x59,daytime(0,59,0).min_bcdp()); 
  }

  /*
   * sec_bcdp()
   */
  void test__sec_bcdp(void)
  {
    using daytime = stm32xx::daytime;
    TS_ASSERT_EQUALS(0x00,daytime(0,0,0).sec_bcdp()); 
    TS_ASSERT_EQUALS(0x02,daytime(0,0,2).sec_bcdp());
    TS_ASSERT_EQUALS(0x59,daytime(0,0,59).sec_bcdp()); 
  }

  /*
   * daytime_bcdp()
   */
  void test__time_bcdp(void)
  { 
    using daytime = stm32xx::daytime;
    TS_ASSERT_EQUALS(0x00000000ul,daytime(0ul).daytime_bcdp());
    TS_ASSERT_EQUALS(0x00000000ul,daytime(0,0,0).daytime_bcdp()); 
    TS_ASSERT_EQUALS(0x00000059ul,daytime(0,0,59).daytime_bcdp()); 
    TS_ASSERT_EQUALS(0x00005900ul,daytime(0,59,0).daytime_bcdp()); 
    TS_ASSERT_EQUALS(0x00230000ul,daytime(23,0,0).daytime_bcdp()); 
    TS_ASSERT_EQUALS(0x00235859ul,daytime(23,58,59).daytime_bcdp()); 
  }

  /*
   * daytime12_bcdp()
   */
  void test__time12_bcdp(void)
  {
    using daytime = stm32xx::daytime;
    TS_ASSERT_EQUALS(0x00120000ul,daytime(0ul).daytime12_bcdp()); 
    TS_ASSERT_EQUALS(0x00120000ul,daytime(12,0,0,false).daytime12_bcdp()); 
    TS_ASSERT_EQUALS(0x00520000ul,daytime(12,0,0,true).daytime12_bcdp()); 
    TS_ASSERT_EQUALS(0x00120059ul,daytime(12,0,59,false).daytime12_bcdp()); 
    TS_ASSERT_EQUALS(0x00125900ul,daytime(12,59,0,false).daytime12_bcdp()); 
    TS_ASSERT_EQUALS(0x00510000ul,daytime(23,0,0,true).daytime12_bcdp()); 
    TS_ASSERT_EQUALS(0x00515859ul,daytime(23,58,59,true).daytime12_bcdp()); 
  }

  void test__set_hour(void)
  {
    set_hour_check(86339ul, 21); // 23:58:59 -> 21:58:59
  }

  void test__set_min(void)
  {
    set_min_check(10799ul, 33); // 02:59:59 -> 02:33:59
  }

  void test__set_sec(void)
  {
    set_sec_check(10799ul, 37); // 02:59:59 -> 02:59:37
  }

  void test__set_flags(void)
  {
    set_flags_check(0);
    set_flags_check(stm32xx::daytime::flag_isdst);
  }

  void test__set_daytime(void)
  {
    using daytime = stm32xx::daytime;
    /* set_daytime(other) */
    set_daytime_check(daytime(10,11,12));
    set_daytime_check(daytime(10,11,12,daytime::flag_isdst));
    /* set_daytime(h,m,s) */
    set_daytime_check(10,11,12);
    /* set_daytime(h,m,s,f) */
    set_daytime_check(10,11,12,0);
    set_daytime_check(10,11,12,daytime::flag_isdst);
    /* set_daytime(s) */
    set_daytime_check(3662ul);
    /* set_daytime(s,f) */
    set_daytime_check(3662ul,daytime::flag_isdst);
  }

  void test__inc_hour(void)
  {
    inc_hour_check(     0ul,  1); // 00:00:00
    inc_hour_check(  3600ul,  2); // 01:00:00
    inc_hour_check( 82800ul,  0); // 23:00:00
  }

  void test__dec_hour(void)
  {
    dec_hour_check(     0ul, 23); // 00:00:00
    dec_hour_check(  3600ul,  0); // 01:00:00
    dec_hour_check( 82800ul, 22); // 23:00:00
  }

  void test__inc_min(void)
  {
    inc_min_check(     0ul,  1); // 00:00:00
    inc_min_check(    60ul,  2); // 00:01:00
    inc_min_check(  3540ul,  0); // 00:59:00
  }

  void test__dec_min(void)
  {
    dec_min_check(     0ul, 59); // 00:00:00
    dec_min_check(    60ul,  0); // 00:01:00
    dec_min_check(  3540ul, 58); // 00:59:00
  }

  void test__inc_sec(void)
  {
    inc_sec_check(     0ul,  1); // 00:00:00
    inc_sec_check(    59ul,  0); // 00:00:59
    inc_sec_check(  3540ul,  1); // 00:59:00
    inc_sec_check(  3599ul,  0); // 00:59:59
    inc_sec_check( 86340ul,  1); // 23:59:00
    inc_sec_check( 86399ul,  0); // 23:59:59
  }

  void test__dec_sec(void)
  {
    dec_sec_check(     0ul, 59); // 00:00:00
    dec_sec_check(    59ul, 58); // 00:00:59
    dec_sec_check(  3540ul, 59); // 00:59:00
    dec_sec_check(  3599ul, 58); // 00:59:59
    dec_sec_check( 86340ul, 59); // 23:59:00
    dec_sec_check( 86399ul, 58); // 23:59:59
  }

  void test__advance_daytime(void)
  {
    advance_daytime_check( 0, 0, 0,     1,   0, 0, 0, 1);
    advance_daytime_check( 0, 0, 0,    -1,  -1,23,59,59);
    advance_daytime_check(23,59,59,     1,   1, 0, 0, 0);
    advance_daytime_check(10, 0, 0, 86400,   1,10, 0, 0);
    advance_daytime_check(10, 0, 0,-86400,  -1,10, 0, 0);
  }

  void test__dst_update(void)
  {
    /* TODO: implement tests */
  }

};
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
