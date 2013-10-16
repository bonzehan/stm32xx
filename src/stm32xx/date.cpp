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

date date::
from_gday(gday_t g) noexcept
{
  // http://alcor.concordia.ca/~gpkatch/gdate-c.html
  int32_t ddd, mi, y, m, d;
  g += 578040; // Compensate offset introduced in gday().
  y = (10000 * (int64_t)g + 14780) / 3652425;
  ddd = g - (365*y + y/4 - y/100 + y/400);
  if (ddd < 0) 
    {
      y = y - 1;
      ddd = g - (365*y + y/4 - y/100 + y/400);
    }
  mi = (100 * ddd + 52)/3060;
  m = ((mi + 2) % 12) + 1;
  y = y + (mi + 2)/12;
  d = ddd - (mi*306 + 5)/10 + 1;
  return date((year_t)y, (mon_t)m, (mday_t)d);
}

void date::
clamp_date() noexcept
{
  if (this->_M_year <= 1582)
    {
      if (this->gday() < 1)
        {
          this->_M_year = 1582;
          this->_M_mon = 10;
          this->_M_mday = 15;
        }
    }
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

bool date::
inc_date() noexcept
{
  this->inc_mday();
  if(this->mday() == 1) 
    {
      /* end of month reached */
      this->inc_mon();
      if(this->mon() == 1)
        {
          /* end of year reached */
          this->inc_year();
          if (this->year() == STM32XX_DATE_YEAR_MIN)
            {
              this->clamp_date(); // ensure we dont go before start of calendar
              return true;
            }
        }
    }
  return false;
}

} /* namespace stm32xx */

// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
