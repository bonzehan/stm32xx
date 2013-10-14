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

/** // doc: stm32xx/datetime.cpp {{{
 * @file stm32xx/datetime.cpp
 * @todo Write documentation
 */ // }}}
#include <stm32xx/datetime.hpp>

namespace stm32xx {

int32_t datetime::
dst_update() noexcept
{
  const int32_t summer_ts = day_secs * dst_summer_yday() + 2*hour_secs;
  const int32_t winter_ts = day_secs * dst_winter_yday() + 2*hour_secs;
  const int32_t s = day_secs * yday() + sec_cnt();
  bool is_summer;
  bool is_winter;

  /* The transition from summer to winter time (-1 hour) is tricky, because
   * one hour repeats once as summer time and once as winter time. To avoid
   * flapping between winter and summer time during this period, we exclude it
   * from consiteration. This is why there is 1 hour gap between "is_summer"
   * and "is_winter". */
  if (summer_ts < winter_ts)
    {
      /* Noth semisphere */
      is_summer = (s >= summer_ts && s < winter_ts);
      is_winter = (s < summer_ts  || s >= (winter_ts+hour_secs));
    }
  else
    {
      /* South semisphere */
      is_summer = (s >= summer_ts || s < winter_ts);
      is_winter = (s < summer_ts  && s >= (winter_ts+hour_secs)); 
    }

  if(is_summer)
    {
      /* Summer time */
      if((flags() & summer_time)==0)
        {
          this->advance_datetime(+hour_secs);
          /* From now on, we have summer time */
          set_flags(flags() | summer_time);
          return 1;
        }
    }
  else if(is_winter)
    {
      /* Winter time */
      if((flags() & summer_time)!=0)
        {
          this->advance_datetime(-hour_secs);
          /* From now on, we have winter time */
          set_flags(flags() & ~summer_time);
          return -1;
        }
    }

  return 0;
}

} /* namespace stm32xx */

// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
