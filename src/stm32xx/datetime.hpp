/*
 * @COPYRIGHT@
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

// stm32xx/datetime.hpp

/** // doc: stm32xx/datetime.hpp {{{ 
 * @file stm32xx/datetime.hpp
 * @todo Write documentation
 */ // }}}
#ifndef STM32XX_DATETIME_HPP_INCLUDED
#define STM32XX_DATETIME_HPP_INCLUDED

#include <stm32xx/date.hpp>
#include <stm32xx/time.hpp>

namespace stm32xx {

/** // doc: datetime {{{
 * @todo Write documentation for datetime.
 */ // }}}
class datetime
  : date, time
{
public: /* types */
public: /* constants */
public: /* static methods */
public: /* member methods */
  /// Default constructor.
  constexpr datetime()
    : date(), time()
  { }
  /** // doc: datetime(y,m,d, c) {{{
   * @brief Constructor
   * @todo Write documentation
   */ // }}}
  constexpr datetime(year_t y, mon_t m, mday_t d, sec_cnt_t c)
    : date(y,m,d), time(c) 
  { }
  /** // doc: datetime(y,m,d, h,mn,s) {{{
   * @brief Constructor
   * @todo Write documentation
   */ // }}}
  constexpr datetime(year_t y, mon_t m, mday_t d, hour_t h, min_t mn, sec_t s)
    : date(y,m,d), time(h,mn,s)
  { }
  /** // doc: datetime(y,m,d, h,mn,s) {{{
   * @brief Constructor
   * @todo Write documentation
   */ // }}}
  constexpr datetime(year_t y, mon_t m, mday_t d, hour_t h, min_t mn, sec_t s,
                     bool pm)
    : date(y,m,d), time(h,mn,s,pm)
  { }
public: /* member data */
};

} /* namespace stm32xx */

#endif /* STM32XX_DATETIME_HPP_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
