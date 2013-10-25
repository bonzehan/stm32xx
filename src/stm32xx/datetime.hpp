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
#include <stm32xx/daytime.hpp>

namespace stm32xx {

/** // doc: datetime {{{
 * @brief Represent and/or manipulate date and time.
 *
 * The stm32xx::datetime object may be used to represent and manipulate
 * calendar date and daytime at once. The class inherits from stm32xx::date and
 * stm32xx::daytime.
 */ // }}}
class datetime
  : public date, public daytime
{
public: /* constants */
public: /* member methods */
  /// Default constructor.
  constexpr datetime()
    : date(), daytime()
  { }
  /** // doc: datetime(d,t) {{{
   * @brief Constructor
   * @todo Write documentation
   */ // }}}
  constexpr datetime(date d, daytime t)
      : date(d), daytime(t)
  { }
  /** // doc: advance_datetime(s) {{{
   * @brief Add @c s seconds to current daytime modifying date if necessary.
   *
   * <b>Example</b>:
   * @code
   * using namespace stm32xx;
   * datetime dt(2013,10,13, 23,0,0); //          2013-10-13 23:00:00
   * dt.advance_datetime(3601);       // +1h1s => 2013-10-14 00:00:01
   * @endcode
   */ // }}}
  inline void advance_datetime(int32_t s)
  {
    this->advance_date(this->advance_daytime(s));
  }
  /** // doc: dst_update() {{{
   * @todo Write documentation for dst_udpate().
   */ // }}}
  int32_t dst_update() const noexcept;
protected: /* member data */

public: /* static methods */
};

} /* namespace stm32xx */

#endif /* STM32XX_DATETIME_HPP_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
