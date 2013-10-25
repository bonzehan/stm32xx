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

// stm32xx/daytime.hpp

/** // doc: stm32xx/daytime.hpp {{{ 
 * @file stm32xx/daytime.hpp
 * @todo Write documentation
 */ // }}}
#ifndef STM32XX_DAYTIME_HPP_INCLUDED
#define STM32XX_DAYTIME_HPP_INCLUDED

#include <stm32xx/bcd.hpp>
#include <cstdint>

#ifndef STM32XX_DAYTIME_HOUR_T
/// Unsigned integer type used to represent hours in stm32xx::daytime
# define STM32XX_DAYTIME_HOUR_T int8_t
#endif
#ifndef STM32XX_DAYTIME_MIN_T
/// Unsigned integer type used to represent minutes in stm32xx::daytime
# define STM32XX_DAYTIME_MIN_T int8_t
#endif
#ifndef STM32XX_DAYTIME_SEC_T
/// Unsigned integer type used to represent seconds in stm32xx::daytime
# define STM32XX_DAYTIME_SEC_T int8_t
#endif

namespace stm32xx {

/** // doc: stm32xx::daytime {{{
 * @brief Represent and manipulate daytime.
 *
 * The stm32xx::daytime may be used to represent and manipulate daytime. The time
 * is stored in binary form as three integers. These are:
 *
 * - hour (read by hour() method) - an integer in range <tt>[0 .. 23]</tt>,
 * - minute (read by min() method) - an integer in range <tt>[0 .. 59]</tt>,
 * - second (read by sec() method) - an integer in range <tt>[0 .. 59]</tt>.
 *
 * The object also holds 
 *
 * - flags (read by flags()) - an integer with defined bit flags.
 *
 * The currently defined bit flags are: 
 *
 * - @ref flag_isdst - set if the time is the Daylight Saving Time (DST),
 *
 * <b>Daytime components</b>
 *
 * The daytime components may be obtained by the following methods:
 *
 * - hour() for 24-hour hours <tt>[0 .. 23]</tt> or hour12() for 12-hour hours
 *   <tt>[1 .. 12]</tt>,
 * - min() for minutes <tt>[0 .. 59]</tt>,
 * - sec() for seconds <tt>[0 .. 59]</tt>,
 * - pm() a PM/AM boolean flag for use with hour12().
 *
 * <b>Initialization and modification</b>
 *
 * The daytime may be initialized by constructors and/or set by setter methods:
 * set_sec_cnt(), set_hour(), set_min(), set_sec(), set_flags(), set_daytime().
 *
 * @note Neither the constructors nor setters prevent from setting an invalid
 * time (25:00:00 for example). Your application should validate user's input
 * before using it as an argument to constructor or setter.
 *
 * The daytime may also be modified by using inc_hour(), dec_hour(), inc_min(),
 * dec_min(), inc_sec() and dec_sec() methods. They may be used to implement
 * button-driven user interfaces for daytime adjustment. 
 *
 * <b>Support for RTC timers</b>
 *
 * There are three "entry points" for RTC timers without hardware
 * clock/calendar support. First appropach is to initialize daytime object with
 * RTC_CNT value (via constructor). Equivalently, one may set_sec_cnt(RTC_CNT).
 * The third possibility is to increase time by one with inc_daytime() at every
 * second (in the interrupt routine for example).
 *
 * Some of the STM32 MCUs are equipped with hardware RTC clock/calendar (see
 * AN3371 and reference manuals for relevant MCUs). These chips store the
 * daytime as packed BCD code in RTC_TR register. The stm32xx::daytime class is
 * able to convert daytime from and to the format compatible with RTC_TR
 * register. The relevant methods are from_rtc_tr() and to_rtc_tr().
 *
 * <b>Support for Daylight Saving Time update</b>
 *
 * The stm32xx::daytime class provides support for simple Daylight Saving Time
 * update algorithms. This consists of:
 *
 * - the @ref flag_isdst flag, set_flags(), flags() and isdst() methods,
 * - the dst_update() methods,
 *
 * <b>Converting to packed BCD codes</b>
 *
 * Daytime as well as its individual parts (hours, minutes, seconds) may be
 * converted to a packeged BCD codes. The relevant methods are daytime_bcdp(), 
 * hour_bcdp(), hour12_bcdp(), min_bcdp(), and sec_bcdp().
 *
 * <b>Overloaded operators</b>
 *
 * The class overloads comparison operators. Comparing two daytimes is a simple
 * one-liner:
 * @code
 * stm32xx::daytime(20,10,15) < stm32xx::daytime(20,11,10); // true
 * @endcode
 */ // }}}
class daytime
{
public: /* types */
  /// Type used to represent hours.
  typedef STM32XX_DAYTIME_HOUR_T hour_t;
  /// Type used to represent minutes.
  typedef STM32XX_DAYTIME_MIN_T min_t;
  /// Type used to represent seconds.
  typedef STM32XX_DAYTIME_SEC_T sec_t;
  /// Type used to represent seconds' counter.
  typedef int32_t sec_cnt_t;
  /// Unsigned integer type used to represent flags
  typedef uint8_t flag_t;
public: /* constants */
  /// Number of seconds in minute.
  constexpr static sec_cnt_t min_secs = 60ul;
  /// Number of seconds in hour.
  constexpr static sec_cnt_t hour_secs = 60ul * min_secs;
  /// Number of seconds in day.
  constexpr static sec_cnt_t day_secs = 24ul * hour_secs;
  /// Daylight Saving Time (DST) flag (also known as the Summer Time).
  constexpr static flag_t flag_isdst = 0x01u; 
public: /* member methods */
  /* constructors */
  /** // doc: daytime() {{{
   * @brief Default constructor.
   *
   * Initializes seconds' counter with zero.
   * counters).
   */ // }}}
  constexpr daytime() noexcept 
    : _M_hour(0), _M_min(0), _M_sec(0), _M_flags(0)
  { }
  /** // doc: daytime(s) {{{
   * @brief Constructor
   * @param s initial value of the seconds' counter.
   * @param f flags
   */ // }}}
  constexpr daytime(sec_cnt_t s, flag_t f=0) noexcept 
    : _M_hour(s/hour_secs), _M_min((s%hour_secs)/min_secs), _M_sec(s%min_secs),
      _M_flags(f)
  { }
  /** // doc: daytime(h,m,s) {{{
   * @brief Constructor accepting daytime in 24-hour format.
   * @param h hour (24-hour format),
   * @param m minute,
   * @param s second.
   * @param f flags
   *
   * This constructor initializes the daytime object with daytime described by
   * <tt>(h,m,s)</tt> triple.
   */ // }}}
  constexpr daytime(hour_t h, min_t m, sec_t s, flag_t f=0) noexcept
    : _M_hour(h), _M_min(m), _M_sec(s), _M_flags(f)
  { }
  /** // doc: daytime(h,m,s,pm) {{{
   * @brief Constructor accepting daytime in 12-hour format.
   * @param h hour (12-hour format),
   * @param m minute,
   * @param s second.
   * @param pm AM/PM flag, if @c true, PM is assumed.
   * @param f flags
   *
   * This constructor initializes the daytime object with daytime described by
   * <tt>(h,m,s)</tt> triple plus @c pm flag.
   */ // }}}
  constexpr daytime(hour_t h, min_t m, sec_t s, bool pm, flag_t f=0) noexcept
    : daytime(pm ? (12+(h%12)) : (h%12), m, s, f)
  { }

  /* getters */
  /// Return seconds' counter
  constexpr sec_cnt_t sec_cnt() const noexcept 
  {
    return sec_cnt(this->hour(), this->min(), this->sec());
  }

  /* setters */
  /// Set seconds' counter.
  inline void set_sec_cnt(sec_cnt_t s) noexcept
  {
    this->set_hour(s/hour_secs);
    this->set_min((s%hour_secs)/min_secs);
    this->set_sec((s%min_secs));
  }
  /** // doc: set_hour() {{{
   * @brief Set hour.
   * @param h hour to be set, in 24-hour format.
   */ // }}}
  inline void set_hour(hour_t h) noexcept { this->_M_hour = h; }
  /** // doc: set_min() {{{
   * @brief Set minute.
   * @param m minute value to be set.
   */ // }}}
  inline void set_min(min_t m) noexcept { this->_M_min = m; }
  /** // doc: set_sec() {{{
   * @brief Set second.
   * @param s second value to be set.
   */ // }}}
  inline void set_sec(sec_t s) noexcept { this->_M_sec = s; }
  /** // doc: set_daytime(other) {{{
   * @fn void set_daytime(daytime const&)
   * @brief Set time.
   * @param other The daytime to set
   */ // }}}
  inline void set_daytime(daytime const& other) noexcept { *this = other; }
  /** // doc: set_daytime(h,m,s) {{{
   * @fn void set_daytime(hour_t,min_t,sec_t)
   * @brief Set time.
   * @param h hours,
   * @param m minutes,
   * @param s seconds
   */ // }}}
  inline void set_daytime(hour_t h, min_t m, sec_t s) noexcept 
  {
    this->set_hour(h);
    this->set_min(m);
    this->set_sec(s);
  }
  /** // doc: set_daytime(h,m,s,f) {{{
   * @fn void set_daytime(hour_t,min_t,sec_t,flag_t)
   * @brief Set time.
   * @param h hours,
   * @param m minutes,
   * @param s seconds,
   * @param f flags
   */ // }}}
  inline void set_daytime(hour_t h, min_t m, sec_t s, flag_t f) noexcept 
  {
    this->set_daytime(h,m,s);
    this->set_flags(f);
  }
  /** // doc: set_daytime(s) {{{
   * @fn void set_daytime(sec_cnt_t s)
   * @brief Set time.
   * @param s The daytime to set (expressed as seconds' counter).
   */ // }}}
  inline void set_daytime(sec_cnt_t s) noexcept { this->set_sec_cnt(s); }
  /** // doc: set_daytime(s,f) {{{
   * @fn void set_daytime(sec_cnt_t s)
   * @brief Set time.
   * @param s The daytime to set (expressed as seconds' counter).
   */ // }}}
  inline void set_daytime(sec_cnt_t s, flag_t f) noexcept 
  {
    this->set_sec_cnt(s);
    this->set_flags(f);
  }
  /** // doc: flags() {{{
   * @todo Write documentation for stm32xx::datetime::flags()
   */ // }}}
  constexpr flag_t flags() const noexcept { return this->_M_flags; }
  /** // doc: set_flags(f) {{{
   * @brief Set flags
   * @param f new flags
   */ // }}}
  inline void set_flags(flag_t f) noexcept { this->_M_flags = f; }
  /* modifiers */
  /** // doc: dec_hour() {{{
   * @brief Decrement hour by one (with wrapping)
   *
   * This method decrements hour by one. If hour() is initially 0, then it is
   * set back to 23 (wrapped). The method may be used to implement simple
   * button-driven user interfaces for daytime adjustment.
   */ // }}}
  inline void dec_hour() noexcept
  {
    this->_M_hour = (this->_M_hour > 0) ? (this->_M_hour - 1) : 23;
  }
  /** // doc: inc_hour() {{{
   * @brief Increment hour by one (with wrapping)
   *
   * This method increments hour by one. If hour() is initially 23, then it is
   * set back to 0 (wrapped). The method may be used to implement simple
   * button-driven GUIs for setting daytime.
   */ // }}}
  inline void inc_hour() noexcept 
  {
    this->_M_hour = (this->_M_hour < 23) ? (this->_M_hour + 1) : 0;
  }
  /** // doc: dec_min() {{{
   * @brief Decrement minute by one (with wrapping)
   *
   * This method decrements minute by one. If min() is initially 0, then it is
   * set back to 59 (wrapped). The method may be used to implement simple
   * button-driven GUIs for setting the daytime.
   */ // }}}
  inline void dec_min() noexcept
  {
    this->_M_min = (this->_M_min > 0) ? (this->_M_min - 1) : 59;
  }
  /** // doc: inc_min() {{{
   * @brief Increment minute by one (with wrapping)
   *
   * This method increments minute by one. If min() is initially 59, then it
   * is set back to 0 (wrapped). The method may be used to implement simple
   * button-driven GUIs for setting the daytime.
   */ // }}}
  inline void inc_min() noexcept
  {
    this->_M_min = (this->_M_min < 59) ? (this->_M_min + 1) : 0;
  }
  /** // doc: dec_sec() {{{
   * @brief Decrement second by one (with wrapping)
   *
   * This method decrements second by one. If sec() is initially 0, then it is
   * set back to 59 (wrapped). The method may be used to implement simple
   * button-driven GUIs for setting daytime.
   */ // }}}
  inline void dec_sec() noexcept
  {
    this->_M_sec = (this->_M_sec > 0) ? (this->_M_sec - 1) : 59;
  }
  /** // doc: inc_sec() {{{
   * @brief Increment second by one (with wrapping)
   *
   * This method increments second by one. If sec() is initially 59, then it
   * is set back to 0 (wrapped). The method may be used to implement simple
   * button-driven GUIs for setting daytime.
   */ // }}}
  inline void inc_sec() noexcept
  {
    this->_M_sec = (this->_M_sec < 59) ?  (this->_M_sec + 1) : 0;
  }

  /** // doc: inc_daytime() {{{
   * @brief Increment daytime by one second.
   *
   * This method increments daytime by one second. 
   *
   * @return @c true if daytime wrap occured (midnight passed).
   */ // }}}
  bool inc_daytime() noexcept;
  /** // doc: advance_daytime(s) {{{
   * @brief Add @c s seconds to current daytime.
   *
   * @param s number of seconds to add to current daytime
   * @return number of days that should be added to current date to correctly
   * handle time modification.
   *
   * This method increments time by @c s second. If the resultant time is
   * beyond daytime (25:00:00, for example) it gets wrapped to a corresponding
   * daytime (01:00:00 in our example).
   *
   * <b>Example 1</b>:
   * @code
   * using namespace stm32xx;
   * time t;
   * t.set_daytime(23,59,59);  // 23:59:59
   * t.advance_daytime(+2);    // + 2 seconds => 00:00:01
   * t.advance_daytime(-2);    // - 2 seconds => 23:59:59
   * @endcode
   *
   * <b>Example 2 </b>: advancing time and date at once
   * @code
   * using namespace stm32xx;
   * date d(2013,10,13);                    // 2013-10-13
   * daytime t(23,0,0);                        // 23:00:00
   * d.advance_date(t.advance_daytime(3601));  // + 1h1s => 2013-10-14 00:00:01
   * @endcode
   */ // }}}
  inline int32_t advance_daytime(int32_t s) noexcept
  {
    const int32_t c = sec_cnt() + s;
    if(c >= 0)
      {
        this->set_daytime(c % day_secs);
        return c / day_secs;
      }
    else
      {
        this->set_daytime(day_secs + (c % day_secs));
        return c / day_secs - 1;
      }
  }

  /* other methods */
  /// Return hours <tt>[0 .. 23]</tt>.
  constexpr hour_t hour() const noexcept { return this->_M_hour; }
  /// Return hours <tt>[0 .. 12]</tt>.
  constexpr hour_t hour12() const noexcept {return daytime::hour12(this->hour());}
  /// Return minutes <tt>[0 .. 59]</tt>.
  constexpr min_t min() const noexcept { return this->_M_min; }
  /// Return seconds <tt>[0 .. 59]</tt>.
  constexpr sec_t sec() const noexcept { return this->_M_sec; }
  /// Return false is the time is an AM time or true if the time is a PM time.
  constexpr bool pm() const noexcept { return (this->hour() >= 12); }
  /** // doc: set_isdst(f) {{{
   * @brief Set new value of DST flag
   * @param f new flag state: @c true for DST time, @c false for standard time,
   */ // }}}
  inline void set_isdst(bool f) noexcept 
  { 
    this->set_flags(f ? (this->flags() |  flag_isdst) 
                      : (this->flags() & ~flag_isdst) );
  }
  /** // doc: isdst() {{{
   * @brief Return the value of DST flag.
   */ // }}}
  constexpr flag_t isdst() const noexcept { return this->_M_flags & flag_isdst; }
  /** // doc: hour_bcdp() {{{
   * @brief Return hour (in 24-hour format) as packed BCD code.
   * @return hour (in 24-hour format) as packed BCD code.
   *
   * The value returned by hour_bcdp() has the following format:
     @verbatim
      31   30   29   28   27   26   25   24   23   22   21   20   19   18   17   16  
     +------------------------------------------------------------------------------+
     :                                      0                                       :
     +------------------------------------------------------------------------------+
    
      15   14   13   12   11   10    9    8    7    6    5    4    3    2    1    0
     +------------------------------------------------+---------+-------------------+
     :                         0                      : HT[1:0] :     HU[3:0]       :
     +------------------------------------------------+---------+-------------------+
     @endverbatim
   * with the bits defined as:
   * - bits 31:6 zeros
   * - bits 5:4 <b>HT[1:0]</b>: hour tens in BCD format,
   * - bits 3:0 <b>HU[3:0]</b>: hour units in BCD format,
   */ // }}}
  constexpr uint32_t hour_bcdp() const noexcept
  {
    return bcdp<2>::encode(this->hour());
  }
  /** // doc: hour12_bcdp() {{{
   * @brief Return hour (in 12-hour format) as packed BCD code.
   * @return hour (in 12-hour format) as packed BCD code.
   *
   * The value returned by hour12_bcdp() has the following format:
     @verbatim
      31   30   29   28   27   26   25   24   23   22   21   20   19   18   17   16  
     +------------------------------------------------------------------------------+
     :                                      0                                       :
     +------------------------------------------------------------------------------+
    
      15   14   13   12   11   10    9    8    7    6    5    4    3    2    1    0
     +-------------------------------------------+----+----+----+-------------------+
     :                       0                   : PM : 0  : HT :     HU[3:0]       :
     +-------------------------------------------+----+----+----+-------------------+
     @endverbatim
   * with the bits defined as:
   *
   * - bits 31:7 zeros
   * - bit 6 <b>PM</b>: AM/PM notation
   *   - 0: AM 
   *   - 1: PM
   * - bit 5 zero
   * - bit 4 <b>HT</b>: hour tens in BCD format (single bit, 1 or 0),
   * - bits 3:0 <b>HU[3:0]</b>: hour units in BCD format,
   */ // }}}
  constexpr uint32_t hour12_bcdp() const noexcept
  {
    return daytime::hour12_bcdp(this->hour());
  }
  /** // doc: min_bcdp() {{{
   * @brief Return minute as 32-bit packed BCD code.
   * @return minute as 32-bit packed BCD code.
   *
   * The value returned by min_bcdp() has the following format:
     @verbatim
      31   30   29   28   27   26   25   24   23   22   21   20   19   18   17   16  
     +------------------------------------------------------------------------------+
     :                                      0                                       :
     +------------------------------------------------------------------------------+
    
      15   14   13   12   11   10    9    8    7    6    5    4    3    2    1    0
     +-------------------------------------------+--------------+-------------------+
     :                     0                     :   MNT[2:0]   :      MNU[3:0]     : 
     +-------------------------------------------+--------------+-------------------+
     @endverbatim
   * with the bits defined as:
   *
   * - bits 31:7 zeros
   * - bits 6:4 <b>MNT[2:0]</b>: minute tens in BCD format,
   * - bits 3:0 <b>MNU[3:0]</b>: minute units in BCD format,
   */ // }}}
  constexpr uint32_t min_bcdp() const noexcept
  {
    return bcdp<2>::encode(this->min());
  }
  /** // doc: sec_bcdp() {{{
   * @brief Return second as 32-bit packed BCD code.
   * @return second as 32-bit packed BCD code.
   *
   * The value returned by sec_bcdp() has the following format:
     @verbatim
      31   30   29   28   27   26   25   24   23   22   21   20   19   18   17   16  
     +------------------------------------------------------------------------------+
     :                                      0                                       :
     +------------------------------------------------------------------------------+
    
      15   14   13   12   11   10    9    8    7    6    5    4    3    2    1    0
     +-------------------------------------------+--------------+-------------------+
     :                     0                     :   ST[2:0]    :     SU[3:0]       :
     +-------------------------------------------+--------------+-------------------+
     @endverbatim
   * with the bits defined as:
   *
   * - bits 31:7 zeros
   * - bits 6:4 <b>ST[2:0]</b>: second tens in BCD format,
   * - bits 3:0 <b>SU[3:0]</b>: second units in BCD format,
   */ // }}}
  constexpr uint32_t sec_bcdp() const noexcept
  {
    return bcdp<2>::encode(this->sec());
  }
  /** // doc: daytime_bcdp() {{{
   * @brief Return the daytime as 32-bit packed BCD code.
   * @return the daytime (in 24-hour format) encoded as packed BCD code. 
   *
   * The value returned by daytime_bcdp() has the following format:
   * @verbatim
      31   30   29   28   27   26   25   24   23   22   21   20   19   18   17   16  
     +------------------------------------------------+---------+-------------------+
     :                         0                      : HT[1:0] :     HU[3:0]       :
     +------------------------------------------------+---------+-------------------+
    
      15   14   13   12   11   10    9    8    7    6    5    4    3    2    1    0
     +---+--------------+-------------------+----+--------------+-------------------+
     : 0 :   MNT[2:0]   :      MNU[3:0]     : 0  :   ST[2:0]    :     SU[3:0]       :
     +---+--------------+-------------------+----+--------------+-------------------+
     @endverbatim
   * with the bits defined as:
   *
   * - bits 31:22 zeros
   * - bits 21:20 <b>HT[1:0]</b>: hour tens in BCD format,
   * - bits 19:16 <b>HU[3:0]</b>: hour units in BCD format,
   * - bit 15 zero
   * - bits 14:12 <b>MNT[2:0]</b>: minute tens in BCD format,
   * - bits 11:8 <b>MNU[3:0]</b>: minute units in BCD format,
   * - bit 7 zero
   * - bits 6:4 <b>ST[2:0]</b>: second tens in BCD format,
   * - bits 3:0 <b>SU[3:0]</b>: second units in BCD format,
   */ // }}}
  constexpr uint32_t daytime_bcdp() const noexcept
  {
    return (this->hour_bcdp() << 16)
         | (this->min_bcdp()  <<  8)
         |  this->sec_bcdp();
  }
  /** // doc: daytime12_bcdp() {{{
   * @brief Return the daytime as 32-bit packed BCD code.
   * @return the daytime (in 12-hour format) encoded as packed BCD code. 
   *
   * The value returned by daytime12_bcdp() has the following format:
   * @verbatim
      31   30   29   28   27   26   25   24   23   22   21   20   19   18   17   16  
     +-------------------------------------------+----+----+----+-------------------+
     :                       0                   : PM : 0  : HT :     HU[3:0]       :
     +-------------------------------------------+----+----+----+-------------------+
    
      15   14   13   12   11   10    9    8    7    6    5    4    3    2    1    0
     +---+--------------+-------------------+----+--------------+-------------------+
     : 0 :   MNT[2:0]   :      MNU[3:0]     : 0  :   ST[2:0]    :     SU[3:0]       :
     +---+--------------+-------------------+----+--------------+-------------------+
     @endverbatim
   * with the bits defined as:
   *
   * - bits 31:23 zeros
   * - bit 22 <b>PM</b>: AM/PM notation
   *   - 0: AM 
   *   - 1: PM
   * - bit 21 zero
   * - bit 20 <b>HT</b>: hour tens in BCD format (single bit, 1 or 0),
   * - bits 19:16 <b>HU[3:0]</b>: hour units in BCD format,
   * - bit 15 zero
   * - bits 14:12 <b>MNT[2:0]</b>: minute tens in BCD format,
   * - bits 11:8 <b>MNU[3:0]</b>: minute units in BCD format,
   * - bit 7 zero
   * - bits 6:4 <b>ST[2:0]</b>: second tens in BCD format,
   * - bits 3:0 <b>SU[3:0]</b>: second units in BCD format,
   */ // }}}
  constexpr uint32_t daytime12_bcdp() const noexcept
  {
    return (this->hour12_bcdp() << 16)
         | (this->min_bcdp()    <<  8)
         |  this->sec_bcdp();
  }
  /** // doc: to_rtc_tr(fmt) {{{
   * @brief Return the daytime as 32-bit value compatible with RTC_TR.
   *
   * @param fmt format selector, if @c true then 12-hour format is used with
   * AM/PM flag, otherwise (default) the 24-hour format is used.
   *
   * @return the daytime in packed BCD form compatible with RTC_TR.
   *
   * This method returns the daytime converted to a format compatible with
   * RTC_TR register. The RTC_TR register is present in MCUs equipped with
   * hardware RTC calendar and has the following layout:
   * @verbatim
      31   30   29   28   27   26   25   24   23   22   21   20   19   18   17   16  
     +-------------------------------------------+----+---------+-------------------+
     :                   reserved                : PM : HT[1:0] :     HU[3:0]       :
     +-------------------------------------------+----+---------+-------------------+
    
      15   14   13   12   11   10    9    8    7    6    5    4    3    2    1    0
     +---+--------------+-------------------+----+--------------+-------------------+
     :res:   MNT[2:0]   :      MNU[3:0]     :res :   ST[2:0]    :     SU[3:0]       :
     +---+--------------+-------------------+----+--------------+-------------------+
     @endverbatim
   * with the bits defined as:
   *
   * - bits 31:24 reserved
   * - bit 23 reserved, must be kept at reset value,
   * - bit 22 <b>PM</b>: AM/PM notation
   *   - 0: AM or 24-hour format,
   *   - 1: PM
   * - bits 21:20 <b>HT[1:0]</b>: hour tens in BCD format,
   * - bits 19:16 <b>HU[3:0]</b>: hour units in BCD format,
   * - bit 15 reserved, must be kept at reset value.
   * - bits 14:12 <b>MNT[2:0]</b>: minute tens in BCD format,
   * - bits 11:8 <b>MNU[3:0]</b>: minute units in BCD format,
   * - bit 7 reserved, must be kept at reset value,
   * - bits 6:4 <b>ST[2:0]</b>: second tens in BCD format,
   * - bits 3:0 <b>SU[3:0]</b>: second units in BCD format,
   *
   * The value returned by to_rtc_tr() has the following format:
   * @verbatim
      31   30   29   28   27   26   25   24   23   22   21   20   19   18   17   16  
     +-------------------------------------------+----+---------+-------------------+
     :                       0                   : PM : HT[1:0] :     HU[3:0]       :
     +-------------------------------------------+----+---------+-------------------+
    
      15   14   13   12   11   10    9    8    7    6    5    4    3    2    1    0
     +---+--------------+-------------------+----+--------------+-------------------+
     : 0 :   MNT[2:0]   :      MNU[3:0]     : 0  :   ST[2:0]    :     SU[3:0]       :
     +---+--------------+-------------------+----+--------------+-------------------+
     @endverbatim
   */ // }}}
  constexpr uint32_t to_rtc_tr(bool fmt = false) const noexcept
  {
    return fmt ? daytime12_bcdp() : daytime_bcdp();
  }
  /** // doc: dst_update(dst_s, std_s, yday) {{{
   * @fn int32_t dst_update(int32_t,int32_t,int32_t) const
   *
   * @brief Determine the necessary Daylight Saving Time update.
   *
   * @param dst_s the time at which transition to DST (summer) time should be
   * triggered (zero-based second of a year); zero for Jan 1, 00:00:00.
   * @param std_s the time at which standard (winter) time starts (zero-based
   * second of a year); zero for Jan 1, 00:00:00.
   * @param yday day of year number for the current time (zero for Jan 1),
   *
   * @returns time offset (in seconds) necessary to account time update; this
   * shall be zero most of the time (no update needed), positive value when
   * transition to DST (summer) time is pending, or negative when transition to
   * STD (winter) time is pending.
   *
   * This function simply returns the result of:
   * @code
   * time::dst_update(dst_s, std_s, day_secs*yday + sec_cnt(), isdst())
   * @endcode 
   * see @ref dst_update(int32_t,int32_t,int32_t,bool).
   */ // }}}
  inline int32_t dst_update(int32_t dst_s, int32_t std_s, int32_t yday) const noexcept
  {
    return dst_update(dst_s, std_s, day_secs*yday + sec_cnt(), isdst());
  }

  /* overloaded operators */
  /// operator==
  constexpr bool
  operator==(daytime const& other) const noexcept
  {
    return (this->sec_cnt() == other.sec_cnt());
  }
  /// operator!=
  constexpr bool
  operator!=(daytime const& other) const noexcept
  {
    return (this->sec_cnt() != other.sec_cnt());
  }
  /// operator<
  constexpr bool
  operator<(daytime const& other) const noexcept
  {
    return (this->sec_cnt() < other.sec_cnt());
  }
  /// operator<=
  constexpr bool
  operator<=(daytime const& other) const noexcept
  {
    return (this->sec_cnt() <= other.sec_cnt());
  }
  /// operator>=
  constexpr bool
  operator>=(daytime const& other) const noexcept
  {
    return (this->sec_cnt() >= other.sec_cnt());
  }
  /// operator>
  constexpr bool
  operator>(daytime const& other) const noexcept
  {
    return (this->sec_cnt() > other.sec_cnt());
  }
  /// operator +=
  inline daytime& operator += (sec_cnt_t secs) noexcept
  {
    this->advance_daytime(secs);
    return *this;
  }
  /// operator -=
  inline daytime& operator -= (sec_cnt_t secs) noexcept
  {
    this->advance_daytime(-secs);
    return *this;
  }
protected:
  hour_t _M_hour;
  min_t _M_min;
  sec_t _M_sec;
  flag_t _M_flags;

public: /* static methods */
  /** // doc: from_rtc_tr(tr,fmt) {{{
   * @brief Create stm32xx::daytime object from a 32-bit word in RTC_TR format.
   * @param tr daytime encoded as 32-bit packed BCD word, the format is same as
   * that returned by to_rtc_tr(),
   * @param fmt if @c true, the @c tr is assumed to be in 12-hour format,
   * otherwise (default) it is assumed to be in 24-hour format.
   * @return a stm32xx::daytime object initialized with data decoded from @c tr.
   *
   * This method accepts @c rt in both 24- and 12-hour formats.
   */ // }}}
  constexpr static daytime from_rtc_tr(uint32_t tr, bool fmt = false) noexcept
  {
    return fmt ? daytime(bcdp<2>::decode((tr>>16)&0x1F),
                      bcdp<2>::decode((tr>>8)&0x7F),
                      bcdp<2>::decode(tr&0x7F),
                      (bool)((tr>>22)&1))
               : daytime(bcdp<2>::decode((tr>>16)&0x3F),
                      bcdp<2>::decode((tr>>8)&0x7F),
                      bcdp<2>::decode(tr&0x7F));
  }
  /** // doc: sec_cnt(h,m,s) {{{
   * @brief Determine seconds' counter value.
   * @param h hour, an integer in range <tt>[0 .. 23]</tt>,
   * @param m minute, an integer in range <tt>[0 .. 59]</tt>,
   * @param s second, an integer in range <tt>[0 .. 59]</tt>,
   * @return seconds' counter value
   */ // }}}
  constexpr static int32_t sec_cnt(int32_t h, int32_t m, int32_t s) noexcept
  {
    return hour_secs*h + min_secs*m + s;
  }
  /** // doc: hour12(h) {{{
   * @brief Convert hour from 24-hour format to 12-hour format.
   * @param h hour in 24-hour format, must be an integer in range 
   *        <tt>[0 .. 23]</tt>.
   * @return hour in 12-hour format.
   */ // }}}
  constexpr static uint32_t hour12(uint32_t h) noexcept
  {
    return ((h == 0) || (h == 12)) ? 12 : (h % 12);
  }
  /** // doc: hour12_bcdp(h) {{{
   * @brief Return hour (in 12-hour format) as packed BCD code.
   * @param h hour in 24-hour format, must be an integer in range
   *        <tt>[0 .. 23]</tt>
   * @return hour (in 12-hour format) as packed BCD code.
   *
   * The value returned by hour12_bcdp() has the following format:
     @verbatim
      31   30   29   28   27   26   25   24   23   22   21   20   19   18   17   16  
     +------------------------------------------------------------------------------+
     :                                      0                                       :
     +------------------------------------------------------------------------------+
    
      15   14   13   12   11   10    9    8    7    6    5    4    3    2    1    0
     +-------------------------------------------+----+----+----+-------------------+
     :                       0                   : PM : 0  : HT :     HU[3:0]       :
     +-------------------------------------------+----+----+----+-------------------+
     @endverbatim
   * with the bits defined as:
   *
   * - bits 31:7 zeros
   * - bit 6 <b>PM</b>: AM/PM notation
   *   - 0: AM 
   *   - 1: PM
   * - bit 5 zero
   * - bit 4 <b>HT</b>: hour tens in BCD format (single bit, 1 or 0),
   * - bits 3:0 <b>HU[3:0]</b>: hour units in BCD format,
   */ // }}}
  constexpr static uint32_t hour12_bcdp(uint32_t h) noexcept
  {
    return bcdp<2>::encode(hour12(h)) | ((h>=12) ? (1ul<<6) : 0ul);
  }
  /** // doc: dst_update(dst_s, std_s, s, dst) {{{
   * @fn int32_t dst_update(int32_t,int32_t,int32_t,bool)
   * @brief Determine the necessary Daylight Saving Time update.
   *
   * @param dst_s the time at which transition to DST (summer) time should be
   * triggered (zero-based second of a year); zero for Jan 1, 00:00:00.
   * @param std_s the time at which standard (winter) time starts (zero-based
   * second of a year); zero for Jan 1, 00:00:00.
   * @param s current time in seconds counted since Jan 1, 00:00:00,
   * @param dst daylight saving time flag, @c true if DST time is currently
   * used (by a clock invoking this method), @c false otherwise.
   *
   * The value of @c s should be computed as:
   * @code
   * int32_t s = day_secs * yday + sec_cnt()
   * @endcode
   * where @c yday is the day of year number for the current date.
   *
   * The quantities @c dst_s and @c std_s should be computed taking into
   * account transition date (relative to the Jan 1'st) and the transition
   * daytime, for example:
   * @code
   * // transition from CET to CEST (winter to summer in Poland, for example)
   * stm32xx::date::dst_rule dr(wday_sun,4,1,-7);
   * int32_t dst_s = day_secs * dr.eval(2013) + 2 * hour_secs;
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

#endif /* STM32XX_DAYTIME_HPP_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
