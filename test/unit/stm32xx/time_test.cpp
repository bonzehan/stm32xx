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

/** // doc: test/unit/stm32xx/time_test.cpp {{{
 * @file test/unit/stm32xx/time_test.cpp
 * @todo Write documentation
 */ // }}}
#include <stm32xx/time.hpp>
#include <CppUTest/TestHarness.h>

TEST_GROUP(stm32xx__time)
{
  using sec_cnt_t = stm32xx::time::sec_cnt_t;
  using hour_t = stm32xx::time::hour_t;
  using min_t = stm32xx::time::min_t;
  using sec_t = stm32xx::time::sec_t;

  void test_set_hour(sec_cnt_t c, hour_t h)
  {
    stm32xx::time t(c);
    t.set_hour(h);
    CHECK_EQUAL(h, t.hour());
    CHECK_EQUAL((c/86400ul), (t.sec_cnt()/86400ul));
    CHECK_EQUAL((c%3600ul),  (t.sec_cnt()%3600ul));
  }

  void test_set_min(sec_cnt_t c, min_t m)
  {
    stm32xx::time t(c);
    t.set_min(m);
    CHECK_EQUAL(m, t.min());
    CHECK_EQUAL(((uint32_t)c/3600ul), ((uint32_t)t.sec_cnt()/3600ul));
    CHECK_EQUAL(((uint32_t)c%60ul), ((uint32_t)t.sec_cnt()%60ul));
  }
 
  void test_set_sec(sec_cnt_t c, sec_t s)
  {
    stm32xx::time t(c);
    t.set_sec(s);
    CHECK_EQUAL(s, t.sec());
    CHECK_EQUAL(((uint32_t)c/60ul), ((uint32_t)t.sec_cnt()/60ul)); 
  }

  void test_inc_hour(sec_cnt_t s, hour_t res)
  {
    stm32xx::time t(s);
    t.inc_hour();
    CHECK_EQUAL(res, t.hour());
    CHECK_EQUAL((s/86400ul), (t.sec_cnt()/86400ul));
    CHECK_EQUAL((s%3600ul),  (t.sec_cnt()%3600ul));
  }

  void test_dec_hour(sec_cnt_t s, hour_t res)
  {
    stm32xx::time t(s);
    t.dec_hour();
    CHECK_EQUAL(res, t.hour());
    CHECK_EQUAL((s/86400ul), (t.sec_cnt()/86400ul));
    CHECK_EQUAL((s%3600ul),  (t.sec_cnt()%3600ul));
  }

  void test_inc_min(sec_cnt_t s, min_t res)
  {
    stm32xx::time t(s);
    t.inc_min();
    CHECK_EQUAL(res, t.min());
    CHECK_EQUAL(((uint32_t)s/3600ul), ((uint32_t)t.sec_cnt()/3600ul));
    CHECK_EQUAL(((uint32_t)s%60ul), ((uint32_t)t.sec_cnt()%60ul));
  }

  void test_dec_min(sec_cnt_t s, min_t res)
  {
    stm32xx::time t(s);
    t.dec_min();
    CHECK_EQUAL(res, t.min());
    CHECK_EQUAL(((uint32_t)s/3600ul), ((uint32_t)t.sec_cnt()/3600ul));
    CHECK_EQUAL(((uint32_t)s%60ul),   ((uint32_t)t.sec_cnt()%60ul));
  }

  void test_inc_sec(sec_cnt_t s, sec_t res)
  {
    stm32xx::time t(s);
    t.inc_sec();
    CHECK_EQUAL(res, t.sec());
    CHECK_EQUAL(((uint32_t)s/60ul), ((uint32_t)t.sec_cnt()/60ul)); 
  }

  void test_dec_sec(sec_cnt_t s, sec_t res)
  {
    stm32xx::time t(s);
    t.dec_sec();
    CHECK_EQUAL(res, t.sec());
    CHECK_EQUAL(((uint32_t)s/60ul), ((uint32_t)t.sec_cnt()/60ul)); 
  }
};

/*
 * time()
 */
TEST(stm32xx__time, time)
{ CHECK_EQUAL(0ul, stm32xx::time().sec_cnt()); }

/*
 * time(cnt)
 */
TEST(stm32xx__time, time__10)
{ CHECK_EQUAL(10ul, stm32xx::time(10ul).sec_cnt()); }
TEST(stm32xx__time, time__767650__hour)
{ CHECK_EQUAL(21, stm32xx::time(76750ul).hour()); }
TEST(stm32xx__time, time__767650__hour12)
{ CHECK_EQUAL(9, stm32xx::time(76750ul).hour12()); }
TEST(stm32xx__time, time__767650__min)
{ CHECK_EQUAL(19, stm32xx::time(76750ul).min()); }
TEST(stm32xx__time, time__767650__sec)
{ CHECK_EQUAL(10, stm32xx::time(76750ul).sec()); }

/*
 * time(h,m,s)
 */
TEST(stm32xx__time, time__21__19__10)
{ CHECK_EQUAL(76750ul,  stm32xx::time(21,19,10).sec_cnt()); }

/*
 * time(h,m,s,pm)
 */
TEST(stm32xx__time, time__9__19__10__false)
{ CHECK_EQUAL(33550ul, stm32xx::time(9, 19, 10, false).sec_cnt()); }
TEST(stm32xx__time, time__9__19__10__true)
{ CHECK_EQUAL(76750ul, stm32xx::time(9, 19, 10, true).sec_cnt()); }

/*
 * hour12()
 */
TEST(stm32xx__time, time__0__0__0__hour12)
{ CHECK_EQUAL(12, stm32xx::time(0,0,0).hour12()); }
TEST(stm32xx__time, time__12__0__0__hour12)
{ CHECK_EQUAL(12, stm32xx::time(12,0,0).hour12()); }
TEST(stm32xx__time, time__13__1__2__hour12)
{ CHECK_EQUAL(1, stm32xx::time(13,1,2).hour12()); }

/*
 * pm()
 */
TEST(stm32xx__time, time__0__0__0__pm)
{ CHECK(stm32xx::time(0,0,0).pm()==false); }
TEST(stm32xx__time, time__12__0__0__pm)
{ CHECK(stm32xx::time(12,0,0).pm()==true); }
TEST(stm32xx__time, time__9__19__10__pm)
{ CHECK(stm32xx::time(9,19,10).pm() == false); }
TEST(stm32xx__time, time__21__19__10__pm)
{ CHECK(stm32xx::time(21,19,10).pm() == true); }

/*
 * hour_bcdp()
 */
TEST(stm32xx__time, time__3__0__0__hour_bcdp)
{ CHECK_EQUAL(0x03,stm32xx::time(3,0,0).hour_bcdp()); }
TEST(stm32xx__time, time__13__0__0__hour_bcdp)
{ CHECK_EQUAL(0x13,stm32xx::time(13,0,0).hour_bcdp()); }
TEST(stm32xx__time, time__23__0__0__hour_bcdp)
{ CHECK_EQUAL(0x23,stm32xx::time(23,0,0).hour_bcdp()); }

/*
 * hour12_bcdp()
 */
TEST(stm32xx__time, time__3__0__0__false__hour12_bcdp)
{ CHECK_EQUAL(0x03,stm32xx::time(3,0,0,false).hour12_bcdp()); }
TEST(stm32xx__time, time__12__0__0__false__hour12_bcdp)
{ CHECK_EQUAL(0x12,stm32xx::time(12,0,0,false).hour12_bcdp()); }

/*
 * min_bcdp()
 */
TEST(stm32xx__time, time__0__0__0__min_bcdp)
{ CHECK_EQUAL(0x00,stm32xx::time(0,0,0).min_bcdp()); }
TEST(stm32xx__time, time__0__2__0__min_bcdp)
{ CHECK_EQUAL(0x02,stm32xx::time(0,2,0).min_bcdp()); }
TEST(stm32xx__time, time__0__59__0__min_bcdp)
{ CHECK_EQUAL(0x59,stm32xx::time(0,59,0).min_bcdp()); }

/*
 * sec_bcdp()
 */
TEST(stm32xx__time, time__0__0__0__sec_bcdp)
{ CHECK_EQUAL(0x00,stm32xx::time(0,0,0).sec_bcdp()); }
TEST(stm32xx__time, time__0__0__2__sec_bcdp)
{ CHECK_EQUAL(0x02,stm32xx::time(0,0,2).sec_bcdp()); }
TEST(stm32xx__time, time__0__0__59__sec_bcdp)
{ CHECK_EQUAL(0x59,stm32xx::time(0,0,59).sec_bcdp()); }

/*
 * time_bcdp()
 */
TEST(stm32xx__time, time__0__time_bcdp)
{ CHECK_EQUAL(0x00000000ul,stm32xx::time(0ul).time_bcdp()); }
TEST(stm32xx__time, time__86400__time_bcdp)
{ CHECK_EQUAL(0x00000000ul,stm32xx::time(86400ul).time_bcdp()); }
TEST(stm32xx__time, time__0__0__0__time_bcdp)
{ CHECK_EQUAL(0x00000000ul,stm32xx::time(0,0,0).time_bcdp()); }
TEST(stm32xx__time, time__0__0__59__time_bcdp)
{ CHECK_EQUAL(0x00000059ul,stm32xx::time(0,0,59).time_bcdp()); }
TEST(stm32xx__time, time__0__59__0__time_bcdp)
{ CHECK_EQUAL(0x00005900ul,stm32xx::time(0,59,0).time_bcdp()); }
TEST(stm32xx__time, time__23__0__0__time_bcdp)
{ CHECK_EQUAL(0x00230000ul,stm32xx::time(23,0,0).time_bcdp()); }
TEST(stm32xx__time, time__23__58__59__time_bcdp)
{ CHECK_EQUAL(0x00235859ul,stm32xx::time(23,58,59).time_bcdp()); }

/*
 * time12_bcdp()
 */
TEST(stm32xx__time, time__0__time12_bcdp)
{ CHECK_EQUAL(0x00120000ul,stm32xx::time(0ul).time12_bcdp()); }
TEST(stm32xx__time, time__86400__time12_bcdp)
{ CHECK_EQUAL(0x00120000ul,stm32xx::time(86400ul).time12_bcdp()); }
TEST(stm32xx__time, time__12__0__0__false__time12_bcdp)
{ CHECK_EQUAL(0x00120000ul,stm32xx::time(12,0,0,false).time12_bcdp()); }
TEST(stm32xx__time, time__12__0__0__true__time12_bcdp)
{ CHECK_EQUAL(0x00520000ul,stm32xx::time(12,0,0,true).time12_bcdp()); }
TEST(stm32xx__time, time__12__0__59__false__time12_bcdp)
{ CHECK_EQUAL(0x00120059ul,stm32xx::time(12,0,59,false).time12_bcdp()); }
TEST(stm32xx__time, time__12__59__0__false__time12_bcdp)
{ CHECK_EQUAL(0x00125900ul,stm32xx::time(12,59,0,false).time12_bcdp()); }
TEST(stm32xx__time, time__11__0__0__true__time12_bcdp)
{ CHECK_EQUAL(0x00510000ul,stm32xx::time(23,0,0,true).time12_bcdp()); }
TEST(stm32xx__time, time__11__58__59__true__time12_bcdp)
{ CHECK_EQUAL(0x00515859ul,stm32xx::time(23,58,59,true).time12_bcdp()); }

#define TEST_set_hour(_c,_h) \
TEST(stm32xx__time, time__ ## _c ## __set_hour__ ## _h) {test_set_hour(_c,_h);}

TEST_set_hour(259193ul, 21); // 2days + 23:58:59 -> 2days + 21:58:59

#define TEST_set_min(_c,_m) \
TEST(stm32xx__time, time__ ## _c ## __set_min__ ## _m) {test_set_min(_c,_m);}

TEST_set_min(183599ul, 33); // 2days + 02:59:59 -> 2days + 02:33:59

#define TEST_set_sec(_c,_s) \
TEST(stm32xx__time, time__ ## _c ## __set_sec__ ## _s) {test_set_sec(_c,_s);}

TEST_set_sec(183599ul, 37); // 2days + 02:59:59 -> 2days + 02:59:37

#define TEST_inc_hour(_s,_res) \
TEST(stm32xx__time, time__ ## _s ## __inc_hour) {test_inc_hour(_s, _res);}

TEST_inc_hour(     0ul,  1); // 00:00:00
TEST_inc_hour(  3600ul,  2); // 01:00:00
TEST_inc_hour( 82800ul,  0); // 23:00:00
TEST_inc_hour(172800ul,  1); // 2days + 00:00:00
TEST_inc_hour(255600ul,  0); // 2days + 23:00:00
TEST_inc_hour(176339ul,  1); // 2days + 00:58:59
TEST_inc_hour(259193ul,  0); // 2days + 23:58:59

#define TEST_dec_hour(_s,_res) \
TEST(stm32xx__time, time__ ## _s ## __dec_hour) { test_dec_hour(_s,_res); }

TEST_dec_hour(     0ul, 23); // 00:00:00
TEST_dec_hour(  3600ul,  0); // 01:00:00
TEST_dec_hour( 82800ul, 22); // 23:00:00
TEST_dec_hour(172800ul, 23); // 2days + 00:00:00
TEST_dec_hour(255600ul, 22); // 2days + 23:00:00
TEST_dec_hour(176339ul, 23); // 2days + 00:58:59
TEST_dec_hour(259193ul, 22); // 2days + 23:58:59

#define TEST_inc_min(_s,_res) \
TEST(stm32xx__time, time__ ## _s ## __inc_min) { test_inc_min(_s,_res); }

TEST_inc_min(     0ul,  1); // 00:00:00
TEST_inc_min(    60ul,  2); // 00:01:00
TEST_inc_min(  3540ul,  0); // 00:59:00
TEST_inc_min(172800ul,  1); // 2days + 00:00:00
TEST_inc_min(176340ul,  0); // 2days + 00:59:00
TEST_inc_min(180059ul,  1); // 2days + 02:00:59
TEST_inc_min(183599ul,  0); // 2days + 02:59:59

#define TEST_dec_min(_s,_res) \
TEST(stm32xx__time, time__ ## _s ## __dec_min) { test_dec_min(_s,_res); }

TEST_dec_min(     0ul, 59); // 00:00:00
TEST_dec_min(    60ul,  0); // 00:01:00
TEST_dec_min(  3540ul, 58); // 00:59:00
TEST_dec_min(172800ul, 59); // 2days + 00:00:00
TEST_dec_min(176340ul, 58); // 2days + 00:59:00
TEST_dec_min(180059ul, 59); // 2days + 02:00:59
TEST_dec_min(183599ul, 58); // 2days + 02:59:59

#define TEST_inc_sec(_s,_res) \
TEST(stm32xx__time, time__ ## _s ## __inc_sec) { test_inc_sec(_s,_res); }

TEST_inc_sec(     0ul,  1); // 00:00:00
TEST_inc_sec(    59ul,  0); // 00:00:59
TEST_inc_sec(  3540ul,  1); // 00:59:00
TEST_inc_sec(  3599ul,  0); // 00:59:59
TEST_inc_sec( 86340ul,  1); // 23:59:00
TEST_inc_sec( 86399ul,  0); // 23:59:59
TEST_inc_sec(172800ul,  1); // 2days + 00:00:00
TEST_inc_sec(180059ul,  0); // 2days + 02:00:59
TEST_inc_sec(176340ul,  1); // 2days + 00:59:00
TEST_inc_sec(183599ul,  0); // 2days + 02:59:59

#define TEST_dec_sec(_s,_res) \
TEST(stm32xx__time, time__ ## _s ## __dec_sec) { test_dec_sec(_s,_res); }

TEST_dec_sec(     0ul, 59); // 00:00:00
TEST_dec_sec(    59ul, 58); // 00:00:59
TEST_dec_sec(  3540ul, 59); // 00:59:00
TEST_dec_sec(  3599ul, 58); // 00:59:59
TEST_dec_sec( 86340ul, 59); // 23:59:00
TEST_dec_sec( 86399ul, 58); // 23:59:59
TEST_dec_sec(172800ul, 59); // 2days + 00:00:00
TEST_dec_sec(180059ul, 58); // 2days + 02:00:59
TEST_dec_sec(176340ul, 59); // 2days + 00:59:00
TEST_dec_sec(183599ul, 58); // 2days + 02:59:59


// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
