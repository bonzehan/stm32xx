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

/** // doc: stm32xx/date.cpp {{{
 * @file stm32xx/date.cpp
 * @brief Software calendar implementation for STM32 devices.
 * @todo Write documentation
 */ // }}}
#include <stm32xx/date.hpp>

namespace stm32xx {

date::year_t date::
clamp_year(year_t y) noexcept
{
  return  (y < STM32XX_DATE_YEAR_MIN) ?  STM32XX_DATE_YEAR_MIN 
      :  ((y > STM32XX_DATE_YEAR_MAX) ?  STM32XX_DATE_YEAR_MAX : y);
}

date::mon_t date::
clamp_mon(mon_t m) noexcept
{
  return (m < 1) ? 1 : ((m > 12) ? 12 : m);
}

date::mday_t date::
clamp_mday(year_t y, mon_t m, mday_t d) noexcept
{
  if(d < 1)
    return 1;
  else 
    {
      mday_t md = date::mdays(y, m);
      if (d > md)
        return md;
      else
        return d;
    }
}

bool date::
leap_year(year_t y) noexcept
{
  /* FIXME: implement assert_param */
  /* assert_param(y>=STM32XX_DATE_YEAR_MIN && y<=STM32XX_DATE_YEAR_MAX); */
  if((y % 400) == 0) return true;
  if((y % 100) == 0) return false;
  return ((y % 4) == 0);
}

date::mday_t date::
mdays(year_t y, mon_t m) noexcept
{
  /* days in months:           1  2  3  4  5  6  7  8  9 10 11 12 */
  static const uint8_t t[] = {31,28,31,30,31,30,31,31,30,31,30,31};
  /* FIXME: implement assert_param */
  /* assert_param(m>=1 && m<=12); */
  return (m==2 && leap_year(y)) ? (mday_t)29 : (mday_t)(t[m-1]);
}

static date::yday_t
yday_base(date::year_t y, date::mon_t m) noexcept
{
  static const uint16_t t[] = {0,31,59,90,120,151,181,212,243,273,304,334};
  /* FIXME: implement assert_param */
  /* assert_param(m>=1 && m<=12); */
  return (date::yday_t)((m>=3 && date::leap_year(y)) ? t[m-1]+1 : t[m-1]);
}

date::yday_t date::
yday(year_t y, mon_t m, mday_t d) noexcept
{
  /* FIXME: implement assert_param */
  /* assert_param(d>=1 && d<=mdays(y,m)); */
  return yday_base(y,m) + (d-1);
}

date::wday_t date::
wday(year_t y, mon_t m, mday_t d) noexcept
{
  uint32_t tmp1, tmp2, tmp3, tmp4;
  if(m < 3)
    {
      m += 12;
      y -= 1;
    }
  tmp1  = (6*(m+1))/10;
  tmp2  = y/4;
  tmp3  = y/100;
  tmp4  = y/400;
  return  (wday_t)(1 + ((y + 2*m + d + tmp1 + tmp2 - tmp3 + tmp4) % 7));
}

bool date::
date_valid() const noexcept
{
  return (this->_M_year >= STM32XX_DATE_YEAR_MIN) 
      && (this->_M_year <= STM32XX_DATE_YEAR_MAX)
      && (this->_M_mon  >=  1)
      && (this->_M_mon  <= 12)
      && (this->_M_mday >=  1)
      && (this->_M_mday <= mdays(this->_M_year, this->_M_mon));
}

void date::
clamp_date() noexcept
{
  /* Order is important: year, month, then day */
  this->_M_year = clamp_year(this->year());
  this->_M_mon = clamp_mon(this->mon());
  this->_M_mday = clamp_mday(this->year(), this->mon(), this->mday());
}


void date::
dec_year() noexcept
{
  if(this->_M_year > STM32XX_DATE_YEAR_MIN)
    --this->_M_year;
  else
    this->_M_year = STM32XX_DATE_YEAR_MAX;
}

void date::
inc_year() noexcept
{
  if(this->_M_year < STM32XX_DATE_YEAR_MAX)
    ++this->_M_year;
  else
    this->_M_year = STM32XX_DATE_YEAR_MIN;
}

void date::
dec_mon() noexcept
{
  if(this->_M_mon > 1)
    --this->_M_mon;
  else
    this->_M_mon = 12;
}

void date::
inc_mon() noexcept
{
  if(this->_M_mon < 12)
    ++this->_M_mon;
  else
    this->_M_mon = 1;
}

void date::
dec_mday() noexcept
{
  if(this->_M_mday > 1)
    --this->_M_mday;
  else
    this->_M_mday = mdays(this->_M_year,this->_M_mon);
}

void date::
inc_mday() noexcept
{
  if(this->_M_mday < mdays(this->_M_year, this->_M_mon))
    ++this->_M_mday;
  else
    this->_M_mday = 1;
}

void date::
inc_date() noexcept
{
  this->inc_mday();
  if(this->_M_mday == 1) 
    {
      /* end of month reached */
      this->inc_mon();
      if(this->_M_mon == 1)
        {
          /* end of year reached */
          this->inc_year();
        }
    }
}

uint32_t date::
to_rtc_dr(year_t yoff) const noexcept
{
  return  this->date_bcdp(yoff) | (this->wday_bcdp() << 13);
}

} /* namespace stm32xx */

// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
