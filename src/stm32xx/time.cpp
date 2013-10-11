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

/** // doc: stm32xx/time.cpp {{{
 * @file stm32xx/time.cpp
 * @todo Write documentation
 */ // }}}
#include <stm32xx/time.hpp>

namespace stm32xx {

void time::
set_hour(hour_t h)
{
  const sec_cnt_t tail = (h * hour_secs) + (this->_M_sec_cnt % hour_secs);
  this->_M_sec_cnt = this->_M_sec_cnt - (this->_M_sec_cnt % day_secs) + tail;
}

void time::
set_min(min_t m)
{
  const sec_cnt_t tail = (m * min_secs) + (this->_M_sec_cnt % min_secs);
  this->_M_sec_cnt = this->_M_sec_cnt - (this->_M_sec_cnt % hour_secs) + tail;
}

void time::
set_sec(sec_t s)
{
  this->_M_sec_cnt = this->_M_sec_cnt - (this->_M_sec_cnt % min_secs) + s;
}

void time::
dec_hour() noexcept
{
  if (this->hour() > 0)
    this->_M_sec_cnt -= hour_secs;
  else
    this->_M_sec_cnt += (23 * hour_secs);
}

void time::
inc_hour() noexcept
{
  if (this->hour() < 23)
    this->_M_sec_cnt += hour_secs;
  else
    this->_M_sec_cnt -= (23 * hour_secs);
}

void time::
dec_min() noexcept
{
  if (this->min() > 0)
    this->_M_sec_cnt -= min_secs;
  else
    this->_M_sec_cnt += (59 * min_secs);
}

void time::
inc_min() noexcept
{
  if (this->min() < 59)
    this->_M_sec_cnt += min_secs;
  else
    this->_M_sec_cnt -= (59 * min_secs);
}

void time::
dec_sec() noexcept
{
  if (this->sec() > 0)
    this->_M_sec_cnt -= 1;
  else
    this->_M_sec_cnt += 59;
}

void time::
inc_sec() noexcept
{
  if (this->sec() < 59)
    this->_M_sec_cnt += 1;
  else
    this->_M_sec_cnt -= 59;
}

} /* namespace stm32xx */

// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
