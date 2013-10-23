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
 * @brief Represent and/or manipulate date and time.
 *
 * The stm32xx::datetime object may be used to represent and manipulate
 * calendar date and daytime at once. The class inherits from stm32xx::date and
 * stm32xx::time.
 */ // }}}
class datetime
  : public date, public time
{
public: /* types */
  /// Unsigned integer type used to represent flags
  typedef uint8_t flag_t;
public: /* constants */
  /// Summer time flag.
  constexpr static flag_t flag_isdst = 0x01u; 
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
  /** // doc: isdst() {{{
   * @todo Write documentation for stm32xx::datetime::isdst()
   */ // }}}
  constexpr flag_t isdst() const noexcept { return this->_M_flags & flag_isdst; }
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
   * @todo Write documentation for dst_udpate().
   */ // }}}
  inline int32_t dst_update(int32_t dst_s, int32_t std_s) const noexcept
  {
    return dst_update(dst_s, std_s, day_secs*yday() + sec_cnt(), isdst());
  }
  /** // doc: dst_update() {{{
   * @todo Write documentation for dst_udpate().
   */ // }}}
  int32_t dst_update() const noexcept;
protected: /* member data */
  flag_t _M_flags;

public: /* static methods */
  /** // doc: dst_update(dst_s, std_s, ys, dst) {{{
   * @todo Write documentation for dst_udpate().
   *
   * @param dst_s the time at which transition to DST (summer) time should be
   * triggered (zero-based second of a year); zero for Jan 1, 00:00:00.
   * @param std_s the time at which standard (winter) time starts (zero-based
   * second of a year); zero for Jan 1, 00:00:00.
   * @param s current time (zero based second of a year)
   * @param dst daylight saving time flag, @c true if DST time is currently
   * used (by a clock invoking this method), @c false otherwise.
   *
   * The value of @c s should be computed as:
   * @code
   * int32_t s = day_secs * yday() + sec_cnt()
   * @endcode
   * The quantities @c dst_s and @c std_s should be computed taking into
   * account transition date (relative to the Jan 1'st) and the transition
   * daytime, for example:
   * example:
   * @code
   * // transition from CET to CEST (winter to summer in Poland, for example)
   * dst_rule dst_day(wday_sun,4,1,-7);
   * int32_t dst_s = day_secs * dst_day(2013) + 2 * hour_secs;
   * @endcode
   *
   * @returns time offset (in seconds) necessary to account time update; this
   * shall be zero most of the time (no update needed), positive value when
   * transition to DST (summer) time is pending, or negative when transition to
   * STD (winter) time is pending.
   */ // }}}
  static int32_t dst_update(int32_t dst_s, int32_t std_s, int32_t s, bool dst);
};

} /* namespace stm32xx */

#endif /* STM32XX_DATETIME_HPP_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
