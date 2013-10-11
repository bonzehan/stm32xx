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

// stm32xx/time.hpp

/** // doc: stm32xx/time.hpp {{{ 
 * @file stm32xx/time.hpp
 * @todo Write documentation
 */ // }}}
#ifndef STM32XX_TIME_HPP_INCLUDED
#define STM32XX_TIME_HPP_INCLUDED

#include <stm32xx/bcd.hpp>
#include <cstdint>

#ifndef STM32XX_TIME_HOUR_T
/// Unsigned integer type used to represent hours in stm32xx::time
# define STM32XX_TIME_HOUR_T uint32_t
#endif
#ifndef STM32XX_TIME_MIN_T
/// Unsigned integer type used to represent minutes in stm32xx::time
# define STM32XX_TIME_MIN_T uint32_t
#endif
#ifndef STM32XX_TIME_SEC_T
/// Unsigned integer type used to represent seconds in stm32xx::time
# define STM32XX_TIME_SEC_T uint32_t
#endif

namespace stm32xx {

/** // doc: stm32xx::time {{{
 * @brief Represent and manipulate RTC time.
 *
 * The stm32xx::time may be used to represent and manipulate RTC time. The time
 * is stored in a binary form as 32-bit unsigned integer, which is a seconds'
 * counter (read by sec_cnt()).
 *
 * @note The RTC time held in stm32xx::time object is not equivalent to
 * daytime. The seconds' counter held by stm32xx::time may contain more
 * information than just hours, minutes, and seconds. If <tt>sec_cnt() <= @ref
 * day_secs</tt>, we say that the counter is "normalized" (and then it contains
 * only daytime information). Otherwise (sec_cnt() % @ref day_secs) contains
 * daytime information and <tt>(int)(sec_cnt() / @ref day_secs)</tt> is a
 * number of days that should be added to date when determining the effective
 * calendar date.
 *
 * <b>Determining daytime</b>
 *
 * The daytime is derived from seconds' counter sec_cnt() and may be obtained 
 * by the following methods:
 *
 * - hour() for 24-hour hours <tt>[0 .. 23]</tt> or hour12() for 12-hour hours
 *   <tt>[1 .. 12]</tt>,
 * - min() for minutes <tt>[0 .. 59]</tt>,
 * - sec() for seconds <tt>[0 .. 59]</tt>,
 * - pm() a PM/AM boolean flag for use with hour12().
 *
 * <b>Initialization and modification</b>
 *
 * The time may be initialized by constructors and/or set by setter methods:
 * set_sec_cnt(), set_hour(), set_min(), set_sec().
 *
 * @note Neither the constructor nor setters prevent from setting an invalid
 * daytime (28:72:63 for example). Your application should validate user' input
 * when setting time. There is no way to detect whether the invalid input was
 * used once the new daytime is set.
 *
 * The time may also be modified by using inc_hour(), dec_hour(), inc_min(),
 * dec_min(), inc_sec() and dec_sec() methods. They may be used to implement
 * button-driven user interfaces for daytime adjustment. 
 *
 * <b>Support for RTC timers</b>
 *
 * Some of the STM32 MCUs are equipped with hardware RTC calendar (see AN3371
 * and reference manuals for relevant MCUs). These chips store the daytime as
 * packed BCD code in RTC_TR register. The stm32xx::time class is able to
 * convert daytime from and to the format compatible with RTC_TR register. The
 * relevant methods are from_rtc_tr() and to_rtc_tr().
 *
 * <b>Converting to packed BCD codes</b>
 *
 * Daytime as well as its individual parts (hours, minutes, seconds) may be
 * converted to a packeged BCD codes. The relevant methods are time_bcdp(), 
 * hour_bcdp(), hour12_bcdp(), min_bcdp(), and sec_bcdp().
 *
 * <b>Overloaded operators</b>
 *
 * The class overload comparison operators, such that comparing times is a
 * one-liner:
 * @code
 * stm32xx::time(20,10,15) < stm32xx::time(20,11,10); // true
 * @endcode
 * Note, that for unnormalized time values, the comparison takes into account
 * whole seconds' counter (including the days embodied within), not only the
 * daytime.
 *
 */ // }}}
class time
{
public: /* types */
  /// Type used to represent hours.
  typedef STM32XX_TIME_HOUR_T hour_t;
  /// Type used to represent minutes.
  typedef STM32XX_TIME_MIN_T min_t;
  /// Type used to represent seconds.
  typedef STM32XX_TIME_SEC_T sec_t;
  /// Type used to represent seconds' counter.
  typedef uint32_t sec_cnt_t;

public: /* constants */
  /// Number of seconds in minute.
  constexpr static sec_cnt_t min_secs = 60ul;
  /// Number of seconds in hour.
  constexpr static sec_cnt_t hour_secs = 60ul * min_secs;
  /// Number of seconds in day.
  constexpr static sec_cnt_t day_secs = 24ul * hour_secs;

public: /* static methods */
  /** // doc: from_rtc_tr(tr,fmt) {{{
   * @brief Create stm32xx::time object from a 32-bit word in RTC_TR format.
   * @param tr daytime encoded as 32-bit packed BCD word, the format is same as
   * that returned by to_rtc_tr(),
   * @param fmt if @c true, the @c tr is assumed to be in 12-hour format,
   * otherwise (default) it is assumed to be in 24-hour format.
   * @return a stm32xx::time object initialized with data decoded from @c tr.
   *
   * This method accepts @c rt in both 24- and 12-hour formats.
   */ // }}}
  constexpr static time from_rtc_tr(uint32_t tr, bool fmt = false) noexcept
  {
    return fmt ? time(bcdp<2>::decode((tr>>16)&0x1F),
                      bcdp<2>::decode((tr>>8)&0x7F),
                      bcdp<2>::decode(tr&0x7F),
                      (bool)((tr>>22)&1))
               : time(bcdp<2>::decode((tr>>16)&0x3F),
                      bcdp<2>::decode((tr>>8)&0x7F),
                      bcdp<2>::decode(tr&0x7F));
  }
  /** // doc: to_hour12(h) {{{
   * @brief Convert hour from 24-hour format to 12-hour format.
   * @param h hour in 24-hour format, must be an integer in range 
   *        <tt>[0 .. 23]</tt>.
   * @return hour in 12-hour format.
   */ // }}}
  constexpr static hour_t to_hour12(hour_t h) noexcept
  {
    return ((h == 0) || (h == 12)) ? 12 : (h % 12);
  }
  /** // doc: to_hour12_bcdp(h) {{{
   * @brief Return hour (in 12-hour format) as packed BCD code.
   * @param h hour in 24-hour format, must be an integer in range
   *        <tt>[0 .. 23]</tt>
   * @return hour (in 12-hour format) as packed BCD code.
   *
   * The value returned by to_hour12_bcdp() has the following format:
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
  constexpr static uint32_t to_hour12_bcdp(hour_t h) noexcept
  {
    return bcdp<2>::encode(to_hour12(h)) | ((h>=12) ? (1ul<<6) : 0ul);
  }

public: /* member methods */
  /* constructors */
  /** // doc: time() {{{
   * @brief Default constructor.
   *
   * Initializes seconds' counter with zero.
   * counters).
   */ // }}}
  constexpr time() noexcept 
    : _M_sec_cnt(0)
  { }
  /** // doc: time(s) {{{
   * @brief Constructor
   * @param s initial value of the seconds' counter.
   */ // }}}
  constexpr time(sec_cnt_t s) noexcept 
    : _M_sec_cnt(s)
  { }
  /** // doc: time(h,m,s) {{{
   * @brief Constructor accepting daytime in 24-hour format.
   * @param h hour (24-hour format),
   * @param m minute,
   * @param s second.
   *
   * This constructor initializes the time object with daytime described by
   * <tt>(h,m,s)</tt> triple.
   */ // }}}
  constexpr time(hour_t h, min_t m, sec_t s) noexcept
    : _M_sec_cnt((sec_cnt_t)h*hour_secs + (sec_cnt_t)m*min_secs + (sec_cnt_t)s)
  { }
  /** // doc: time(h,m,s,pm) {{{
   * @brief Constructor accepting daytime in 12-hour format.
   * @param h hour (12-hour format),
   * @param m minute,
   * @param s second.
   * @param pm AM/PM flag, if @c true, PM is assumed.
   *
   * This constructor initializes the time object with daytime described by
   * <tt>(h,m,s)</tt> triple plus @c pm flag.
   */ // }}}
  constexpr time(hour_t h, min_t m, sec_t s, bool pm) noexcept
    : time(pm ? (12+(h%12)) : (h%12), m, s)
  { }

  /* getters */
  /// Return seconds' counter
  constexpr sec_cnt_t sec_cnt() const noexcept { return _M_sec_cnt; }

  /* setters */
  /// Set seconds' counter.
  inline void set_sec_cnt(sec_cnt_t s) noexcept { this->_M_sec_cnt = s; }
  /** // doc: set_hour() {{{
   * @brief Set hour.
   * @param h hour to be set, in 24-hour format.
   */ // }}}
  void set_hour(hour_t h) noexcept;
  /** // doc: set_min() {{{
   * @brief Set minute.
   * @param m minute value to be set.
   */ // }}}
  void set_min(min_t m) noexcept;
  /** // doc: set_sec() {{{
   * @brief Set second.
   * @param s second value to be set.
   */ // }}}
  void set_sec(sec_t s) noexcept;

  /* modifiers */
  /** // doc: dec_hour() {{{
   * @brief Decrement hour by one (with wrapping)
   *
   * This method decrements hour by one. If hour() is initially 0, then it is
   * set back to 23 (wrapped). The method may be used to implement simple
   * button-driven user interfaces for daytime adjustment.
   */ // }}}
  void dec_hour() noexcept;
  /** // doc: inc_hour() {{{
   * @brief Increment hour by one (with wrapping)
   *
   * This method increments hour by one. If hour() is initially 23, then it is
   * set back to 0 (wrapped). The method may be used to implement simple
   * button-driven GUIs for setting daytime.
   */ // }}}
  void inc_hour() noexcept;
  /** // doc: dec_min() {{{
   * @brief Decrement minute by one (with wrapping)
   *
   * This method decrements minute by one. If min() is initially 0, then it is
   * set back to 59 (wrapped). The method may be used to implement simple
   * button-driven GUIs for setting the daytime.
   */ // }}}
  void dec_min() noexcept;
  /** // doc: inc_min() {{{
   * @brief Increment minute by one (with wrapping)
   *
   * This method increments minute by one. If min() is initially 59, then it
   * is set back to 0 (wrapped). The method may be used to implement simple
   * button-driven GUIs for setting the daytime.
   */ // }}}
  void inc_min() noexcept;
  /** // doc: dec_sec() {{{
   * @brief Decrement second by one (with wrapping)
   *
   * This method decrements second by one. If sec() is initially 0, then it is
   * set back to 59 (wrapped). The method may be used to implement simple
   * button-driven GUIs for setting daytime.
   */ // }}}
  void dec_sec() noexcept;
  /** // doc: inc_sec() {{{
   * @brief Increment second by one (with wrapping)
   *
   * This method increments second by one. If sec() is initially 59, then it
   * is set back to 0 (wrapped). The method may be used to implement simple
   * button-driven GUIs for setting daytime.
   */ // }}}
  void inc_sec() noexcept;

  /* other methods */
  /// Return hours <tt>[0 .. 23]</tt>.
  constexpr hour_t hour() const noexcept
  {
    return (this->sec_cnt() % day_secs) / hour_secs; 
  }
  /// Return hours <tt>[0 .. 12]</tt>.
  constexpr hour_t hour12() const noexcept
  {
    return time::to_hour12(this->hour());
  }
  /// Return minutes <tt>[0 .. 59]</tt>.
  constexpr min_t min() const noexcept
  {
    return (this->sec_cnt() % hour_secs) / min_secs; 
  }
  /// Return seconds <tt>[0 .. 59]</tt>.
  constexpr sec_t sec() const noexcept 
  {
    return (this->sec_cnt() % min_secs);
  }
  /// Return false is the time is an AM time or true if the time is a PM time.
  constexpr bool pm() const noexcept
  {
    return (this->hour() >= 12);
  }
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
    return time::to_hour12_bcdp(this->hour());
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
  /** // doc: time_bcdp() {{{
   * @brief Return the daytime as 32-bit packed BCD code.
   * @return the daytime (in 24-hour format) encoded as packed BCD code. 
   *
   * The value returned by time_bcdp() has the following format:
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
  constexpr uint32_t time_bcdp() const noexcept
  {
    return (this->hour_bcdp() << 16)
         | (this->min_bcdp()  <<  8)
         |  this->sec_bcdp();
  }
  /** // doc: time12_bcdp() {{{
   * @brief Return the daytime as 32-bit packed BCD code.
   * @return the daytime (in 12-hour format) encoded as packed BCD code. 
   *
   * The value returned by time12_bcdp() has the following format:
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
  constexpr uint32_t time12_bcdp() const noexcept
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
    return fmt ? time12_bcdp() : time_bcdp();
  }

  /* overloaded operators */
  /// operator==
  constexpr bool
  operator==(time const& other) const noexcept
  {
    return (this->sec_cnt() == other.sec_cnt());
  }
  /// operator!=
  constexpr bool
  operator!=(time const& other) const noexcept
  {
    return (this->sec_cnt() != other.sec_cnt());
  }
  /// operator<
  constexpr bool
  operator<(time const& other) const noexcept
  {
    return (this->sec_cnt() < other.sec_cnt());
  }
  /// operator<=
  constexpr bool
  operator<=(time const& other) const noexcept
  {
    return (this->sec_cnt() <= other.sec_cnt());
  }
  /// operator>=
  constexpr bool
  operator>=(time const& other) const noexcept
  {
    return (this->sec_cnt() >= other.sec_cnt());
  }
  /// operator>
  constexpr bool
  operator>(time const& other) const noexcept
  {
    return (this->sec_cnt() > other.sec_cnt());
  }
protected:
  sec_cnt_t _M_sec_cnt;
};

} /* namespace stm32xx */

#endif /* STM32XX_TIME_HPP_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
