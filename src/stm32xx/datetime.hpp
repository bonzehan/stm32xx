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
  : public date, public time
{
public: /* types */
  /// Unsigned integer type used to represent flags
  typedef uint8_t flag_t;
public: /* constants */
  /// Summer time flag.
  constexpr static flag_t summer_time = 0x01u; 
public: /* member methods */
  /// Default constructor.
  constexpr datetime()
    : date(), time(), _M_flags(0)
  { }
  /** // doc: datetime(d,t) {{{
   * @brief Constructor
   * @todo Write documentation
   */ // }}}
  constexpr datetime(date d, time t, flag_t f=0)
      : date(d), time(t), _M_flags(f)
  { }
  /** // doc: flags() {{{
   * @todo Write documentation for stm32xx::datetime::flags()
   */ // }}}
  constexpr flag_t flags() const noexcept { return this->_M_flags; }
  /** // doc: set_flags(f) {{{
   * @todo Write documentation for stm32xx::datetime::flags()
   */ // }}}
  inline void set_flags(flag_t f) noexcept { this->_M_flags = f; }
  /** // doc: advance_datetime(s) {{{
   * @brief Add @c s seconds to current time modifying date if necessary.
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
    this->advance_date(this->advance_time(s));
  }
  /** // doc: dst_update() {{{
   * @brief Apply Daylight Saving Time update.
   * @return the number of hours added to current time.
   *
   * The returned value is:
   * - @c  0 if time is left unchanged (this is for most cases),
   * - @c  1 if time has been changed from winter to summer (+1 hour),
   * - @c -1 if time has been changed from summer to winter (-1 hour).
   */ // }}}
  int32_t dst_update() const noexcept;
protected: /* member data */
  flag_t _M_flags;

public: /* static methods */
};

} /* namespace stm32xx */

#endif /* STM32XX_DATETIME_HPP_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
