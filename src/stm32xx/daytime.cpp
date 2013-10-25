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

/** // doc: stm32xx/daytime.cpp {{{
 * @file stm32xx/daytime.cpp
 * @todo Write documentation
 */ // }}}
#include <stm32xx/daytime.hpp>

namespace stm32xx {

bool daytime::
inc_daytime() noexcept
{
  this->inc_sec();
  if(this->sec() == 0)
    {
      this->inc_min();
      if (this->min() == 0)
        {
          this->inc_hour();
          if (this->hour() == 0)
            return true;
        }
    }
  return true;
}

int32_t daytime::
dst_update(int32_t dst_s, int32_t std_s, int32_t s, bool dst)
{
  bool is_summer;
  bool is_winter;

  /* The transition from DST to STD time (-1 hour) is tricky. One hour repeats
   * once as DST time and once as STD time. To avoid flapping between DST
   * and STD time during this period, we exclude it from consiteration. This
   * is why there is 1 hour gap between "is_summer" and "is_winter". */
  if (dst_s < std_s)
    {
      /* Noth semisphere */
      is_summer = (s >= dst_s && s < std_s);
      is_winter = (s < dst_s  || s >= (std_s+hour_secs));
    }
  else
    {
      /* South semisphere */
      is_summer = (s >= dst_s || s < std_s);
      is_winter = (s < dst_s  && s >= (std_s+hour_secs)); 
    }

  if(is_summer)
    {
      /* Summer time */
      if(!dst)
        {
          /* From now on, we have dst_s time */
          //set_flags(flags() | summer_time);
          //this->advance_datetime(+hour_secs);
          return hour_secs;
        }
    }
  else if(is_winter)
    {
      /* Winter time */
      if(dst)
        {
          //this->advance_datetime(-hour_secs);
          /* From now on, we have std_s time */
          //set_flags(flags() & ~summer_time);
          return -hour_secs;
        }
    }

  return 0;
}

} /* namespace stm32xx */

// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
