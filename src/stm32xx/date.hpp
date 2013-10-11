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

// stm32xx/date.hpp

/** // doc: stm32xx/date.hpp {{{ 
 * @file stm32xx/date.hpp
 * @todo Write documentation
 */ // }}}
#ifndef STM32XX_DATE_HPP_INCLUDED
#define STM32XX_DATE_HPP_INCLUDED

#include <stm32xx/bcd.hpp>
#include <ctime>
#include <cstdint>

#ifndef STM32XX_DATE_YEAR_MIN
/** // doc: STM32XX_DATE_YEAR_MIN {{{
 * @brief Lowest allowed year in stm32xx::date.
 */ // }}}
# define STM32XX_DATE_YEAR_MIN 1900
#endif
#ifndef STM32XX_DATE_YEAR_MAX
/** // doc: STM32XX_DATE_YEAR_MIN {{{
 * @brief Highest allowed year in stm32xx::date.
 */ // }}}
# define STM32XX_DATE_YEAR_MAX 4095
#endif
#ifndef STM32XX_DATE_YEAR_T
/** // doc: STM32XX_DATE_YEAR_T {{{
 * @brief Integer type to be used by stm32xx::date to represent years.
 */ // }}}
# define STM32XX_DATE_YEAR_T uint32_t
#endif
#ifndef STM32XX_DATE_MON_T
/** // doc: STM32XX_DATE_MON_T {{{
 * @brief Integer type to be used by stm32xx::date to represent months.
 */ // }}}
# define STM32XX_DATE_MON_T uint32_t
#endif
#ifndef STM32XX_DATE_MDAY_T
/** // doc: STM32XX_DATE_MDAY_T {{{
 * @brief Integer type to be used by stm32xx::date to represent days of month.
 */ // }}}
# define STM32XX_DATE_MDAY_T uint32_t
#endif
#ifndef STM32XX_DATE_YDAY_T
/** // doc: STM32XX_DATE_YDAY_T {{{
 * @brief Integer type to be used by stm32xx::date to represent days of year.
 */ // }}}
# define STM32XX_DATE_YDAY_T uint32_t
#endif

#if ((STM32XX_DATE_YEAR_MIN) < 0)
# error "STM32XX_DATE_YEAR_MIN must be non-negative"
#endif
#if ((STM32XX_DATE_YEAR_MAX) > 4095)
# error "STM32XX_DATE_YEAR_MAX must be less than 4095"
#endif
#if ((STM32XX_DATE_YEAR_MIN) >= (STM32XX_DATE_YEAR_MAX))
# error "STM32XX_DATE_YEAR_MIN must be less than STM32XX_DATE_YEAR_MAX"
#endif


namespace stm32xx {

/** // doc: stm32xx::date {{{
 * @brief Represent and/or manipulate dates
 *
 * The stm32xx::date object may be used to represent and manipulate calendar
 * date. The date is stored in binary form (as three integer numbers) and
 * consists of:
 *
 * - year (read with year() method),
 * - month (read with mon() method),
 * - day of month (read with mday() method),
 *
 * By default, all three integers are of type @c uint32_t. You may change
 * defaults by defining preprocessor constants: @ref STM32XX_DATE_YEAR_T,
 * @ref STM32XX_DATE_MON_T and @ref STM32XX_DATE_MDAY_T.
 *
 * <b>Other characteristics</b>
 *
 * Other date characteristics, such as day of the year or day of the week may
 * be computed from year, month and day of the month contained in date object.
 * The relevant methods are wday(), yday(), leap_year(), mdays().
 *
 * <b>Initialization and modification</b>
 *
 * The date may be initialized by constructors and/or set by setter methods:
 * set_year(), set_mon() and set_mday().
 *
 * @note Neither the constructors nor setters prevent from setting an invalid
 * date (February 31, for example). Your application should validate user's
 * input when setting date or check the date correctness on newly created or
 * modified dates (see date_valid()). For simple applications it's fair enough
 * to just blindly round the dates to a "nearest" valid date by clamp_date()
 * method, for example:
 * @code
 * stm32xx::date d(2013,2,31);  // 2013-02-31 (invalid date)
 * d.clamp_date();              // 2013-02-28 (corrected date)
 * @endcode
 *
 * The date may also be modified by using inc_year(), dec_year(), inc_mon(),
 * dec_mon(), inc_mday(), dec_mday() methods. They may be used to implement
 * button-driven user interfaces for setting calendar date.
 *
 * @note The date after dec_year(), inc_year(), dec_mon() or inc_mon() may
 * become invalid. It is advised to check its validity or just clamp_date()
 * before using it further. Below are some examples of the possible situations
 * that require correcting
 * actions. \n
 * 1. Example with inc_mon():
 *    @code
 *    stm32xx::date d(2013,1,31);  // 2013-01-31 (valid)
 *    d.inc_mon();                 // 2013-02-31 (invalid)
 *    d.clamp_date();              // 2013-02-28 (corrected)
 *    @endcode
 * 2. Example with inc_year():
 *    @code
 *    stm32xx::date d(2012,2,29);  // 2012-02-29 (valid, 2012 is a leap year)
 *    d.inc_year();                // 2013-02-29 (invalid, 2013 is not a leap year)
 *    d.clamp_date();              // 2013-02-28 (corrected)
 *    @endcode
 *
 * <b>Support for RTC timers</b>
 *
 * An "entry point" for an RTC timer is the inc_date() method which moves date
 * forward by one day. Provided the date is valid prior to inc_date() invocation,
 * it remains valid after inc_date().
 *
 * Some of the STM32 MCUs are equipped with hardware RTC calendar (see AN3371
 * and reference manuals for relevant MCUs). These chips store date as packed
 * BCD code in RTC_DR register. The stm32xx::date class is able to convert date
 * from and to the format compatible with RTC_DR register. The relevant methods 
 * are from_rtc_dr() and to_rtc_dr().
 *
 * <b>Storing date in backup registers</b>
 *
 * If the hardware RTC calendar is not available, to_rtc_dr() may still be used
 * to compute a 32-bit word to be stored in backup registers. This format may
 * be preferred by application which use digital displays (LCD, LED, ...)
 * accepting BCD-coded data.
 *
 * <b>Converting to BCD codes</b>
 *
 * The date, as well as its parts, may be converted to packed BCD codes (this
 * shall simplify development of application with BCD-based displays). The
 * relevant methods are year_bcdp(), mon_bcdp(), mday_bcdp(), wday_bcdp(),
 * and date_bcdp().
 *
 * <b>Overloaded operators</b>
 *
 * In addition to accessors and modifiers, the class overloads comparison
 * operators such that comparing dates is a one-liner such as:
 * @code
 * stm32xx::date(2013,10,9) < stm32xx::date(2013,11,1); // true
 * @endcode
 * The following operators are overloaded: operator==(), operator!=(),
 * operator<(), operator<=(), operator>(), operator>=().
 */ // }}}
class date
{
public: /* types */
  /// Integer type used by stm32xx::date to represent years.
  typedef STM32XX_DATE_YEAR_T year_t;
  /// Integer type used by stm32xx::date to represent months.
  typedef STM32XX_DATE_MON_T mon_t;
  /// Integer type used by stm32xx::date to represent days of year.
  typedef STM32XX_DATE_YDAY_T yday_t;
  /// Integer type used by stm32xx::date to represent days of month.
  typedef STM32XX_DATE_MDAY_T mday_t;
  /// Enum used to represent days of week.
  enum wday_t
    {
      wday_mon = 1,
      wday_tue,
      wday_wed,
      wday_thu,
      wday_fri,
      wday_sat,
      wday_sun,
    };

public: /* static methods */
  /** // doc: from_rtc_dr(y) {{{
   * @brief Create new date from RTC_DR value.
   * @param dr the input value; should have same format as the value returned
   *        by to_rtc_dr() or date_bcdp().
   * @param yoff year offset, this value is added to year value decoded from
   *        @c dr.
   *
   * @note The week day (WDU[2:0]) bits in @c dr are ignored.
   *
   * @return a new stm32xx::date object.
   */ // }}}
  constexpr static date from_rtc_dr(uint32_t dr, year_t yoff = 0) noexcept
  {
    return date(  bcdp<4>::decode((dr&0xFFFF0000ul) >> 16) + yoff,
                  bcdp<2>::decode((dr&0x00001F00ul) >>  8),
                  bcdp<2>::decode( dr&0x0000003Ful) );
  }
  /** // doc: leap_year() {{{
   * @brief Is this a leap year?
   * @param y year, an integer in range <tt>[@ref STM32XX_DATE_YEAR_MIN ..
   *        @ref STM32XX_DATE_YEAR_MAX]</tt>
   * @return @c true if @c y is a leap year, or @c false if not.
   */ // }}}
  static bool leap_year(year_t y) noexcept;
  /** // doc: mdays() {{{
   * @brief Return number of days in a month.
   * @param y year, an integer in range <tt>[@ref STM32XX_DATE_YEAR_MIN ..
   *          @ref STM32XX_DATE_YEAR_MAX]</tt>,
   * @param m month, an integer in range <tt>[1 .. 12]</tt>
   * @return number of days in the month @c m &mdash; an integer from range
   *         <tt>[28 .. 31]</tt>.
   */ // }}}
  static mday_t mdays(year_t y, mon_t m) noexcept;
  /** // doc: yday() {{{
   * @brief Given a date (year, month, day of month) determine day of year.
   * @param y year, an integer in range <tt>[@ref STM32XX_DATE_YEAR_MIN ..
   *        @ref STM32XX_DATE_YEAR_MAX]</tt>,
   * @param m month, an integer in range <tt>[1 .. 12]</tt>,
   * @param d day of month, an integer in range <tt>[1 .. mdays(y,m)]</tt>,
   * @return an integer from range <tt>[0 .. 364]</tt> or <tt>[0 .. 365]</tt>
   * (leap year).
   */ // }}}
  static yday_t yday(year_t y, mon_t m, mday_t d) noexcept;
  /** // doc: wday() {{{
   * @brief Given a date (year, month, day of month) determine day of week.
   * @param y year, an integer in range <tt>[@ref STM32XX_DATE_YEAR_MIN ..
   *        @ref STM32XX_DATE_YEAR_MAX]</tt>,
   * @param m month, an integer in range <tt>[1 .. 12]</tt>,
   * @param d day of month, an integer in range <tt>[1 .. mdays(y,m)]</tt>,
   * @return an enum naming the day of week of given date @c d.
   */ // }}}
  static wday_t wday(year_t y, mon_t m, mday_t d) noexcept;
  /** // doc: clamp_year(y) {{{
   * @brief Correct year if out of range.
   * @param y a reference to year variable.
   * @return corrected year.
   */ // }}}
  static year_t clamp_year(year_t y) noexcept;
  /** // doc: clamp_year() {{{
   * @brief Correct month if out of range.
   * @param m a reference to month variable.
   * @return corrected month.
   */ // }}}
  static mon_t clamp_mon(mon_t m) noexcept;
  /** // doc: clamp_mday() {{{
   * @brief Correct day of month if out of range.
   * @param y year, an integer in range <tt>[@ref STM32XX_DATE_YEAR_MIN ..
   *        @ref STM32XX_DATE_YEAR_MAX]</tt>,
   * @param m month, an integer in range <tt>[1 .. 12]</tt>,
   * @param d a reference to day of month variable.
   * @return corrected day of month.
   */ // }}}
  static mday_t clamp_mday(year_t y, mon_t m, mday_t d) noexcept;

public: /* member methods */
  /** // doc: date() {{{
   * @brief Default constructor
   *
   * By default, the date is initialized with the following values:
   *
   * - year:  @ref STM32XX_DATE_YEAR_MIN
   * - month: 1 (January),
   * - mday:  1
   */ // }}}
  constexpr date() noexcept
    : _M_year(STM32XX_DATE_YEAR_MIN), _M_mon(1), _M_mday(1)
  {
  }
  /** // doc: date(y,m,d) {{{
   * @brief Constructor
   *
   * @param y year, an integer in range <tt>[@ref STM32XX_DATE_YEAR_MIN ..
   *        @ref STM32XX_DATE_YEAR_MAX]</tt>,
   * @param m month, an integer in range <tt>[1..12]</tt>,
   * @param d day of month, an integer in range <tt>[1..date::mdays(y,m)]</tt>.
   * @note The provided values for @c y, @c m and @c d are neither checked nor
   *       corrected. If these values are entered by user, consider validating
   *       them before passing as arguments to the constructor. Alternativelly
   *       clamp_date() may be used to correct invalid date object.
   */ // }}}
  constexpr date(year_t y, mon_t m, mday_t d) noexcept
    : _M_year(y), _M_mon(m), _M_mday(d)
  {
  }

  /* validation and munging */
  /// Does this object represent a valid date?
  bool date_valid() const noexcept;
  /// Round the date to a nearest valid value.
  void clamp_date() noexcept;

  /* convienience methods for setting date from UI */
  /** // doc: dec_year() {{{
   * @brief Decrease year by one (with wrapping).
   *
   * Decrease year by one. If initially <tt>year()<=STM32XX_DATE_YEAR_MIN</tt>,
   * it is set back to @c STM32XX_DATE_YEAR_MAX. 
   *
   * @note The date may become invalid after dec_year(). It is advised to
   *       clamp_date() it before using it further.
   *
   * The main purpose of this method is to let user interfaces to easily modify
   * the date.
   */ // }}}
  void dec_year() noexcept;
  /** // doc: inc_year() {{{
   * @brief Increase year by one (with wrapping).
   *
   * Increase year by one. If initially <tt>year()>=STM32XX_DATE_YEAR_MAX</tt>,
   * it is set back to @c STM32XX_DATE_YEAR_MIN.
   *
   * @note The date may become invalid after inc_year(). It is advised to
   *       clamp_date() it before using it further.
   *
   * The main purpose of this method is to let user interfaces to easily modify
   * the date.
   */ // }}}
  void inc_year() noexcept;
  /** // doc: dec_mon() {{{
   * @brief Decrease month by one (with wrapping).
   *
   * Decrease month by one. If initially <tt>mon()<=1</tt> (January), it is set
   * back (wrapped) to @c 12 (December).
   *
   * @note The date may become invalid after dec_mon(). It is advised to
   *       clamp_date() it before using it further.
   *
   * The main purpose of this method is to let user interfaces to easily modify
   * the date.
   */ // }}}
  void dec_mon() noexcept;
  /** // doc: inc_mon() {{{
   * @brief Increase month by one (with wrapping).
   *
   * Increase month by one. If initially <tt>mon()>=12</tt> (December),
   * it is set back (wrapped) to @c 1 (January).
   *
   * @note The date may become invalid after inc_mon(). It is advised to
   *       clamp_date() it before using it further.
   *
   * The main purpose of this method is to let user interfaces to easily modify
   * the date.
   */ // }}}
  void inc_mon() noexcept;
  /** // doc: dec_mday() {{{
   * @brief Decrease month day by one (with wrapping).
   *
   * Decrease day of the month. If initially <tt>mday()<=1</tt>, it is
   * set back (wrapped) to <tt>date::mdays(year(),mon())</tt>.
   *
   * The main purpose of this method is to let user interfaces to easily modify
   * the date.
   */ // }}}
  void dec_mday() noexcept;
  /** // doc: inc_mday() {{{
   * @brief Increase month day by one (with wrapping).
   *
   * Increase day of the month. If initially
   * <tt>mday()>=date::mdays(year(),mon())</tt> it is set back (wrapped) to
   * @c 1.
   *
   * The main purpose of this method is to let user interfaces to easily modify
   * the date.
   */ // }}}
  void inc_mday() noexcept;

  /* methods for updating date by RTC */
  /** // doc: inc_date() {{{
   * @brief Move the date forward by one day.
   *
   * The main purpose of this method is to let RTC easily update the date as
   * midnight passes.
   */ // }}}
  void inc_date() noexcept;

  /* accessors */
  /// Get year.
  constexpr year_t year() const noexcept { return this->_M_year; }
  /// Get month.
  constexpr mon_t mon() const noexcept { return this->_M_mon; }
  /// Get day of month.
  constexpr mday_t mday() const noexcept { return this->_M_mday; }
  /// Set year
  inline void set_year(year_t y) noexcept { this->_M_year = y; }
  /// Set month
  inline void set_mon(mon_t m) noexcept { this->_M_mon = m; }
  /// Set day of month
  inline void set_mday(mday_t d) noexcept { this->_M_mday = d; }

  /* comparison operators */
  /// operator ==
  constexpr bool 
  operator == (date const& other) const noexcept
  {
    return (this->mday() == other.mday()) 
        && (this->mon() == other.mon())
        && (this->year() == other.year());
  }
  /// operator !=
  constexpr bool
  operator != (date const& other) const noexcept
  {
    return !((*this) == other);
  }
  /// operator <
  constexpr bool
  operator < (date const& other) const noexcept
  {
    return (this->year() < other.year()) ||
      ( 
        (this->year() == other.year()) && 
        ( 
          (this->mon() < other.mon()) ||
          (
            (this->mon() == other.mon()) && 
            (this->mday()<other.mday())
          )
        )
      );
  }
  /// operator <=
  constexpr bool
  operator <= (date const& other) const noexcept
  {
    return ((*this) < other) || ((*this) == other);
  }
  /// operator >
  constexpr bool
  operator > (date const& other) const noexcept
  {
    return !((*this) <= other);
  }
  /// operator >=
  constexpr bool
  operator >= (date const& other) const noexcept
  {
    return !((*this) < other);
  }

  /* other methods */
  /// Get day of year for this date (computed from year(), mon() and mday()).
  inline yday_t yday() const noexcept 
  {
    return yday(this->year(), this->mon(), this->mday()); 
  }
  /// Get day of week for this date (computed from year(), mon() and mday()).
  inline wday_t wday() const noexcept 
  {
    return wday(this->year(), this->mon(), this->mday()); 
  }
  /// Do we have a leap year?
  inline bool leap_year() const noexcept 
  {
    return leap_year(this->year());
  }
  /// How many days the current month has?
  inline mday_t mdays() const noexcept
  {
    return date::mdays(this->year(), this->mon());
  }
  /** // doc: year_bcdp() {{{
   * @brief Return year (year()) as packed BCD code.
   *
   * @param yoff year offset, the value gets subtracted from year() before
   *        encoding.
   * @return year converted to packed BCD code.
   *
   * The value returned by year_bcdp() has the following format:
   * @verbatim
      31   30   29   28   27   26   25   24   23   22   21   20   19   18   17   16  
     +------------------------------------------------------------------------------+
     :                                      0                                       :
     +------------------------------------------------------------------------------+
    
      15   14   13   12   11   10    9    8    7    6    5    4    3    2    1    0
     +------------------+-------------------+-------------------+-------------------+
     :    YTT[3:0]      :     YH[3:0]       :      YT[3:0]      :       YU[3:0]     :
     +------------------+-------------------+-------------------+-------------------+
     @endverbatim
   * with the bits defined as:
   * - bits 15:12 <b>YTT[3:0]</b> year thousands,
   * - bits 11:8  <b>YH[3:0]</b> year hundreds,
   * - bits  7:4  <b>YT[3:0]</b> year tens in BCD format
   * - bits  3:0  <b>YU[3:0]</b> year uints in BCD format
   */ // }}}
  constexpr uint32_t year_bcdp(year_t yoff=0) const noexcept
  {
    return bcdp<4>::encode((uint32_t)(this->year()-yoff));
  }
  /** // doc: mon_bcdp() {{{
   * @brief Return month (mon()) as packed BCD code.
   * @return month converted to packed BCD code.
   *
   * The value returned by mon_bcdp() has the following format:
   * @verbatim
      31   30   29   28   27   26   25   24   23   22   21   20   19   18   17   16  
     +------------------------------------------------------------------------------+
     :                                      0                                       :
     +------------------------------------------------------------------------------+
    
      15   14   13   12   11   10    9    8    7    6    5    4    3    2    1    0
     +-----------------------------------------------------+----+-------------------+
     :                          0                          : MT :       MU[3:0]     :
     +-----------------------------------------------------+----+-------------------+
     @endverbatim
   * with the bits defined as:
   * - bit 4  <b>MT</b>: month tens in BCD format,
   * - bits 3:0 <b>MU</b> month units in BCD format,
   */ // }}}
  constexpr uint32_t mon_bcdp() const noexcept
  {
    return bcdp<2>::encode((uint32_t)this->mon());
  }
  /** // doc: mday_bcdp() {{{
   * @brief Return day of month (mday()) as packed BCD code.
   * @return day of month month converted to packed BCD code (32-bit word).
   *
   * The value returned by mday_bcdp() has the following format:
   * @verbatim
      31   30   29   28   27   26   25   24   23   22   21   20   19   18   17   16  
     +------------------------------------------------------------------------------+
     :                                      0                                       :
     +------------------------------------------------------------------------------+
    
      15   14   13   12   11   10    9    8    7    6    5    4    3    2    1    0
     +-------------------------------------------------+--------+-------------------+
     :                          0                      : DT[1:0]:      DU[3:0]      :
     +-------------------------------------------------+--------+-------------------+
     @endverbatim
   * with the bits defined as:
   * - bits 5:4 <b>DT[1:0]</b> day tens in BCD format,
   * - bits 3:0 <b>DU[3:0]</b> day units in BCD format,
   */ // }}}
  constexpr uint32_t mday_bcdp() const noexcept
  {
    return bcdp<2>::encode((uint32_t)this->mday());
  }
  /** // doc: mday_bcdp() {{{
   * @brief Return day of week (wday()) as packed BCD code.
   * @return day of week converted to packed BCD code (32-bit word).
   *
   * The value returned by mday_bcdp() has the following format:
   * @verbatim
      31   30   29   28   27   26   25   24   23   22   21   20   19   18   17   16  
     +------------------------------------------------------------------------------+
     :                                      0                                       :
     +------------------------------------------------------------------------------+
    
      15   14   13   12   11   10    9    8    7    6    5    4    3    2    1    0
     +---------------------------------------------------------------+--------------+
     :                                  0                            :   WDU[2:0]   :
     +---------------------------------------------------------------+--------------+
     @endverbatim
   * with the bits defined as:
   * - bits 2:0 <b>WDU[2:0]</b> day units in BCD format,
   */ // }}}
  inline uint32_t wday_bcdp() const noexcept
  {
    return bcdp<1>::encode((uint32_t)this->wday() & (uint32_t)0x7);
  }
  /** // doc: date_bcdp() {{{
   * @brief Return the date converted to 32-bit packed BCD code.
   *
   * @param yoff year offset, the value is subtracted from year() before
   *        encoding.
   * @return date converted to packed BCD code (32-bit word).
   *
   * The value returned by date_bcdp() has the following format:
   * @verbatim
      31   30   29   28   27   26   25   24   23   22   21   20   19   18   17   16  
     +------------------+-------------------+-------------------+-------------------+
     :    YTT[3:0]      :     YH[3:0]       :      YT[3:0]      :       YU[3:0]     :
     +------------------+-------------------+-------------------+-------------------+
    
      15   14   13   12   11   10    9    8    7    6    5    4    3    2    1    0
     +-------------+----+-------------------+----------+--------+-------------------+
     :       0     : MT :     MU[3:0]       :     0    : DT[1:0]:      DU[3:0]      :
     +-------------+----+-------------------+----------+--------+-------------------+
     @endverbatim
   * The bits are defined as:
   * - bits 31:28 <b>YTT[3:0]</b> year thousands in BCD format,
   * - bits 27:24 <b>YH[3:0]</b> year hundreds in BCD format,
   * - bits 23:20 <b>YT[3:0]</b> year tens in BCD format
   * - bits 19:16 <b>YU[3:0]</b> year uints in BCD format
   * - bits 15:13 <b>zeros</b>,
   * - bit 12 <b>MT</b>: month tens in BCD format,
   * - bits 11:8 <b>MU</b> month units in BCD format,
   * - bits 7:6 <b>zeros</b>,
   * - bits 5:4 <b>DT[1:0]</b> date tens in BCD format,
   * - bits 3:0 <b>DU[3:0]</b> date units in BCD format,
   */ // }}}
  constexpr uint32_t date_bcdp(year_t yoff = 0) const noexcept
  {
    return  (this->year_bcdp(yoff)  << 16)
          | (this->mon_bcdp()       << 8)
          |  this->mday_bcdp();
  }
  /** // doc: to_rtc_dr() {{{
   * @brief Return the date as 32-bit value compatible with RTC_DR.
   *
   * @param yoff year offset, the value is subtracted from year() before
   *        encoding.
   *
   * This method returns the date converted to a format compatible with RTC_DR
   * register. The RTC_DR register is present in MCUs equipped with hardware
   * RTC calendar.
   *
   * The RTC_DR register has the following layout:
   * @verbatim
      31   30   29   28   27   26   25   24   23   22   21   20   19   18   17   16  
     +--------------------------------------+-------------------+-------------------+
     :             reserved                 :      YT[3:0]      :       YU[3:0]     :
     +--------------------------------------+-------------------+-------------------+
    
      15   14   13   12   11   10    9    8    7    6    5    4    3    2    1    0
     +-------------+----+-------------------+----------+--------+-------------------+
     :   WDU[2:0]  : MT :     MU[3:0]       : reserved : DT[1:0]:      DU[3:0]      :
     +-------------+----+-------------------+----------+--------+-------------------+
     @endverbatim
   * with the bits defined as:
   *
   * - bits 31:24 are reserved
   * - bits 23:20 <b>YT[3:0]</b> year tens in BCD format
   * - bits 19:16 <b>YU[3:0]</b> year uints in BCD format
   * - bits 15:13 <b>WDU[2:0]</b> week day units:
   *   - 000: forbidden
   *   - 001: Monday
   *   - ...
   *   - 111: Sunday
   * - bit 12 <b>MT</b>: month tens in BCD format,
   * - bits 11:8 <b>MU</b> month units in BCD format,
   * - bits 7:6 reserved, must be keept at reset value,
   * - bits 5:4 <b>DT[1:0]</b> date tens in BCD format,
   * - bits 3:0 <b>DU[3:0]</b> date units in BCD format,
   *
   * The value returned by to_rtc_dr() has similar format, but it uses also 
   * bits 31:28 (which are reserved in RTC_DR): 
   * @verbatim
      31   30   29   28   27   26   25   24   23   22   21   20   19   18   17   16  
     +------------------+-------------------+-------------------+-------------------+
     :    YTT[3:0]      :     YH[3:0]       :      YT[3:0]      :       YU[3:0]     :
     +------------------+-------------------+-------------------+-------------------+
    
      15   14   13   12   11   10    9    8    7    6    5    4    3    2    1    0
     +-------------+----+-------------------+----------+--------+-------------------+
     :   WDU[2:0]  : MT :     MU[3:0]       :    0     : DT[1:0]:      DU[3:0]      :
     +-------------+----+-------------------+----------+--------+-------------------+
     @endverbatim
   * The bits 31:24 are defined as:
   * - bits 31:28 <b>YTT[3:0]</b> year thousands in BCD format,
   * - bits 27:24 <b>YH[3:0]</b> year hundreds in BCD format,
   *
   * With the additional bits the conversion is lossless. The extra bits can be
   * easily masked-out when setting to physical RTC_DR register.
   */ // }}}
  uint32_t to_rtc_dr(year_t yoff = 0) const noexcept;

protected: /* members */
  year_t _M_year;
  mon_t _M_mon;
  mday_t _M_mday;
};

} /* namespace stm32xx */

#endif /* STM32XX_DATE_HPP_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
