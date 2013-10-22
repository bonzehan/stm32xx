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
# define STM32XX_DATE_YEAR_MIN 1582
#endif
#ifndef STM32XX_DATE_YEAR_MAX
/** // doc: STM32XX_DATE_YEAR_MIN {{{
 * @brief Highest allowed year in stm32xx::date.
 */ // }}}
# define STM32XX_DATE_YEAR_MAX 4095
#endif
#ifndef STM32XX_DATE_DEFAULT_YEAR
/** // doc: STM32XX_DATE_DEFAULT_YEAR {{{
 * @brief Default date year, used by stm32xx::date default constructor.
 */ // }}}
# define STM32XX_DATE_DEFAULT_YEAR 2000
#endif
#ifndef STM32XX_DATE_DEFAULT_MON
/** // doc: STM32XX_DATE_DEFAULT_MON {{{
 * @brief Default date month, used by stm32xx::date default constructor.
 */ // }}}
# define STM32XX_DATE_DEFAULT_MON 1
#endif
#ifndef STM32XX_DATE_DEFAULT_MDAY
/** // doc: STM32XX_DATE_DEFAULT_MDAY {{{
 * @brief Default date month, used by stm32xx::date default constructor.
 */ // }}}
# define STM32XX_DATE_DEFAULT_MDAY 1
#endif
#ifndef STM32XX_DATE_YEAR_T
/** // doc: STM32XX_DATE_YEAR_T {{{
 * @brief Integer type to be used by stm32xx::date to represent years.
 */ // }}}
# define STM32XX_DATE_YEAR_T int16_t
#endif
#ifndef STM32XX_DATE_MON_T
/** // doc: STM32XX_DATE_MON_T {{{
 * @brief Integer type to be used by stm32xx::date to represent months.
 */ // }}}
# define STM32XX_DATE_MON_T int8_t
#endif
#ifndef STM32XX_DATE_MDAY_T
/** // doc: STM32XX_DATE_MDAY_T {{{
 * @brief Integer type to be used by stm32xx::date to represent days of month.
 */ // }}}
# define STM32XX_DATE_MDAY_T int8_t
#endif
#ifndef STM32XX_DATE_YDAY_T
/** // doc: STM32XX_DATE_YDAY_T {{{
 * @brief Integer type to be used by stm32xx::date to represent days of year.
 */ // }}}
# define STM32XX_DATE_YDAY_T uint16_t
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
 * You may change default types used to represent year, month and day of month
 * by defining preprocessor constants: @ref STM32XX_DATE_YEAR_T, @ref
 * STM32XX_DATE_MON_T and @ref STM32XX_DATE_MDAY_T.
 *
 * <b>Other characteristics</b>
 *
 * Other date characteristics, such as day number, day of the year or day of
 * the week may be computed from year, month and day of the month contained in
 * date object. The relevant methods are gday(), wday(), yday(), leap_year(),
 * mdays().
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
 * @note Dates before Oct 15, 1582 are regarded as invalid, and are rounded by
 * clamp_date() to Oct 15, 1582.
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
 * @note The following description only shows how to handle date, isolated
 * from daytime information. Instructions regarding complete information
 * (including date and daytime) may be found in documentation of
 * stm32xx::datetime.
 *
 * There are several ways to implement RTC-based calendar with stm32xx::date.
 *
 * <b>Devices without hardware clock/calendar</b>:
 *
 * On devices with no hardware clock/calendar functionality one usually stores
 * date in RTC backup domain and uses RTC_CNT counter to measure time offset
 * of the current time from the date stored in backup registers (in seconds).
 *
 * The first approach is to initialize the stm32xx::date object every second
 * (in RTC interrupt, for example) using the above pieces of information,
 * update RTC counter, and store updated date in backup registers, for example:
 *
 * - at each second do:
 * @code
 * date d(date::from_rtc_dr(restore_date()) + RTC->CNT/86400);
 * RTC->CNT = RTC_CNT % 86400;
 * store_date(d.to_rtc_dr());
 * @endcode
 * where @c restore_date() is some function that reads date stored in RTC
 * backup registers and store_date() does the opposite.
 *
 * Other applications may prefer to initialize @ref date object from backed-up
 * values once at startup and utilize the inc_date() to update a @ref date
 * object at midnight.
 * - at startup do:
 *   @code
 *   // d is a static object.
 *   d.set_date(date::from_rtc_dr(restore_date()) + RTC->CNT/86400);
 *   RTC->CNT = RTC->CNT % 86400;
 *   store_date(d.to_rtc_dr());
 *   @endcode
 * - at each midnight do:
 *   @code
 *   d.inc_date();
 *   RTC->CNT -= 86400;
 *   store_date(d.to_rtc_dr());
 *   @endcode
 *
 * <b>Devices with hardware clock/calendar</b>:
 *
 * Some of the STM32 MCUs are equipped with hardware RTC calendar (see AN3371
 * and reference manuals for the relevant MCUs). These chips store date as
 * packed BCD code in RTC_DR register and the daytime in separate RTC_TR
 * register. These chips do not require the application to maintain seconds'
 * counter as in previous examples. Also the date (and time) registers are
 * updated automatically, so there is no need for manipulating date within
 * periodic RTC interrupt handlers unless one needs to handle daylight saving
 * time update, for example. For such cases the initialization of stm32xx::date
 * simplifies to:
 * @code
 * date d(from_rtc_dr(RTC->DR,2000)); // add 2000 to register value 
 * @endcode
 * Storing modified date is also easy:
 * @code
 * // for appropriate mask see reference manual for your target MCU, 
 * // this example is for STM32F4xx.
 * RTC->DR = d.to_rtc_dr(2000) & 0x00FFFF3Ful; // subtract 2000 when storing
 * @endcode
 * The stm32xx::date class is able to convert date from and to the format
 * compatible with RTC_DR register. The relevant methods are from_rtc_dr() and
 * to_rtc_dr().
 *
 * <b>Support for Daylight Saving Time changes</b>:
 *
 * These methods may be used to determine when the summer and winter time
 * starts: dst_summer_yday(), dst_winter_yday(), dst_summer_yday(int32_t),
 * dst_winter_yday(int32_t).
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
 * The following operartors are overloaded:
 * - comparison: operator==(), operator!=(), operator<(), operator<=(),
 *   operator>(), operator>=().
 * - advance date: operator+=(), operator-=(),
 * - plus/minus: operator+(stm32xx::date const&,int32_t), 
 *               operator-(stm32xx::date const&,int32_t).
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
  /// Signed integer used to represent day count (since 0000:03:01).
  typedef int32_t gday_t;

  /** // doc: dst_rule {{{
   * @brief Defines rules used to determine transition dates between daylight
   * saving time (DST) and standard time (STD).
   *
   * The transition day is expressed by the following information 
   * - day of week (wday),
   * - month (mon),
   * - day of the month (mday),
   * - offset in days,
   *
   * With these pieces of information the transition day may be defined as "the
   * last Sunday of October", for example. This is usual way used to describe
   * the transition day in most countries. The eval() method or operator() may
   * be used to determine transition date in a given year.
   *
   * <b>Example</b>:
   * @code
   * using namespace stm32xx;
   * date::dst_rule dr(wday_sun, 11, 1, -7); // last Sunday of October
   * int32_t g = dr(2013);                   // in year 2013
   * @endcode
   */ // }}}
  struct dst_rule
    {
      /** // doc: wday {{{
       * @brief Day of week.
       */ // }}}
      wday_t wday;
      /** // doc: mon {{{
       * @brief Month.
       */ // }}}
      mon_t  mon;
      /** // doc: mday {{{
       * @brief Day of the month.
       */ // }}}
      mday_t mday;
      /** // doc: offset {{{
       * @brief Day offset.
       */ // }}}
      mday_t offset;
      /** // doc: dst_rule(w,m,d,o) {{{
       * @brief Constructor
       *
       * @param w week day,
       * @param m month,
       * @param d day of the month,
       * @param o offset in days (may be negative)
       */ // }}}
      constexpr dst_rule(wday_t w, mon_t m, mday_t d, mday_t o) 
        : wday(w), mon(m), mday(d), offset(o)
      { }
      /** // doc: operator() (y) {{{
       * @brief Determine transition date in year @c y.
       *
       * The method takes year @c y as an argument and determines date
       * described by year @c y, month @ref mon, day of month @ref mday, day of
       * week @ref wday and @ref offset. The algorithm used to determine this
       * date is to find the week day @ref wday next to the date {@c y}-{@ref
       * mon}-{@ref mday} (see @ref find_wday()) and then add @ref offset to
       * this date. The returned value is a day number reative to the beginning
       * of the year @c y (0 for Jan 1st).
       *
       * @param y year,
       *
       * @returns day of the year (zero based number) of the resultant date.
       */ // }}}
      constexpr int32_t eval(int32_t y) const noexcept
      {
        return find_wday(this->wday,gday(y,this->mon,this->mday))
             + this->offset - gday(y,1,1);
      }
      /** // doc: operator() (y) {{{
       * @brief Determine transition date in year @c y.
       *
       * This is just convenience shortcut to eval().
       */ // }}}
      constexpr int32_t operator()(int32_t y) const noexcept
      {
        return this->eval(y);
      }
    };

public: /* member methods */
  /** // doc: date() {{{
   * @brief Default constructor
   *
   * By default, the date is initialized with the following values:
   *
   * - year:  @ref STM32XX_DATE_DEFAULT_YEAR
   * - month: @ref STM32XX_DATE_DEFAULT_MON
   * - mday:  @ref STM32XX_DATE_DEFAULT_MDAY
   */ // }}}
  constexpr date() noexcept
    : _M_year(STM32XX_DATE_DEFAULT_YEAR), 
      _M_mon(STM32XX_DATE_DEFAULT_MON),
      _M_mday(STM32XX_DATE_DEFAULT_MDAY)
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
  constexpr bool date_valid() const noexcept
  {
    return (this->year() >= STM32XX_DATE_YEAR_MIN) 
        && (this->year() <= STM32XX_DATE_YEAR_MAX)
        && (this->mon()  >=  1)
        && (this->mon()  <= 12)
        && (this->mday() >=  1)
        && (this->mday() <= this->mdays());
  }
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
   *
   * @return @c true if calendar wrap occured (STM32XX_DATE_YEAR_MAX passed)
   */ // }}}
  bool inc_date() noexcept;
  /** // doc: advance_date() {{{
   * @brief Move the date forward by a number of days.
   * @param days number of days to add to current date (possibly negative).
   *
   * @note As oposse to inc_date(), this method does not guarantee that date is
   * in range after operation. It's possible to go past STM32XX_DATE_YEAR_MAX
   * or before STM32XX_DATE_YEAR_MIN.
   *
   * The main purpose of this method is to let RTC easily update the date.
   */ // }}}
  void advance_date(int32_t days) noexcept
  {
    this->set_date(days + gday());
  }

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
  /// Set date
  inline void set_date(date const& other) noexcept { *this = other; }
  /// Set date
  inline void set_date(gday_t g) noexcept { this->set_date(from_gday(g)); }

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
  /// operator >
  constexpr bool
  operator > (date const& other) const noexcept
  {
    return other < (*this);
  }
  /// operator <=
  constexpr bool
  operator <= (date const& other) const noexcept
  {
    return !((*this) > other);
  }
  /// operator >=
  constexpr bool
  operator >= (date const& other) const noexcept
  {
    return !((*this) < other);
  }
  /// operator +=
  inline date& operator += (int32_t days) noexcept
  {
    this->advance_date(days);
    return *this;
  }
  /// operator -=
  inline date& operator -= (int32_t days) noexcept
  {
    this->advance_date(-days);
    return *this;
  }

  /* other methods */
  /** // doc: gday() {{{
   * @fn gday_t stm32xx::date::gday() const
   * @brief Get Lilian Day Number (computed from year(), mon(), mday()).
   *
   * Equivalent to, <tt>gday(this->year(),this->mon(),this->mday())</tt>,
   * see @ref gday(int32_t, int32_t, int32_t).
   */ // }}}
  constexpr gday_t gday() const noexcept
  {
    return gday(this->year(), this->mon(), this->mday());
  }
  /// Get day of year for this date (computed from year(), mon() and mday()).
  inline yday_t yday() const noexcept 
  {
    return yday(this->year(), this->mon(), this->mday()); 
  }
  /// Get day of week for this date (computed from year(), mon() and mday()).
  constexpr wday_t wday() const noexcept 
  {
    return (wday_t)wday(this->gday()); 
  }
  /// Do we have a leap year?
  constexpr gday_t leap_year() const noexcept 
  {
    return leap_year(this->year());
  }
  /// How many days the current month has?
  constexpr mday_t mdays() const noexcept
  {
    return date::mdays(this->year(), this->mon());
  }
  /// First day of summer time (Daylight Saving Time)
  constexpr gday_t dst_summer_yday() const noexcept
  {
    return dst_summer_yday(this->year());
  }
  /// First day of winter time (Daylight Saving Time)
  constexpr gday_t dst_winter_yday() const noexcept
  {
    return dst_winter_yday(this->year());
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
  constexpr uint32_t year_bcdp(int32_t yoff=0) const noexcept
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
  constexpr uint32_t wday_bcdp() const noexcept
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
  constexpr uint32_t date_bcdp(int32_t yoff = 0) const noexcept
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
   *   - 001: Mogday
   *   - ...
   *   - 111: Sugday
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
  constexpr uint32_t to_rtc_dr(int32_t yoff = 0) const noexcept
  {
    return  this->date_bcdp(yoff) | (this->wday_bcdp() << 13);
  }

protected: /* members */
  year_t _M_year;
  mon_t _M_mon;
  mday_t _M_mday;

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
  constexpr static date from_rtc_dr(uint32_t dr, int32_t yoff = 0) noexcept
  {
    return date(  bcdp<4>::decode((dr&0xFFFF0000ul) >> 16) + yoff,
                  bcdp<2>::decode((dr&0x00001F00ul) >>  8),
                  bcdp<2>::decode( dr&0x0000003Ful) );
  }
  /** doc: from_gday() {{{
   * @brief Create new date from day number.
   *
   * @param g day number as returned by gday(year_t,mon_t,mday_t)
   * @return a new stm32xx::date object
   */ // }}}
  static date from_gday(gday_t g) noexcept;
  /** // doc: gday(y,m,d) {{{
   * @fn int32_t stm32xx::date::gday(int32_t,int32_t, int32_t)
   * @brief Convert Gregorian date to Lilian Day Number.
   *
   * @param y year, an integer <tt> >= 1582</tt>,
   * @param m month, an integer in range [1 .. 12],
   * @param d day of month, an integer in range [1 .. mdays(y,m)],
   * @return the Lilian Day Number.
   *
   * @note Correct results are guaranteed only for dates equal to or latter
   * than @c Oct 15, 1582. Oct 15, 1582 is the first day of Gregorian calendar
   * and is preceded by Oct 4, 1582 of the Julian Calendar (old calendar).
   * Results obtained for earlier dates are generally invalid (Julian Calendar
   * has different concept of leap years).
   *
   * This function converts a Gregorian date (year, month, day) to an integer
   * denoting number of days elapsed since Oct 14, 1582 AD (day no. 0). The
   * returned value is simply the Lilian Day Number. The Lilian Day 1 is the
   * first day of the Gregorian calendar. 
   *
   * <b>Beginning of Gregorian Calendar</b>:
   * @verbatim
     Oct, 1582:

     Mon Tue Wed Thu Fri Sat Sun
                     15  16  17
     18  19  20  21  22  23  24
     25  26  27  28  29  30  31
     @endverbatim
   *
   * The formula used to determine the day number is equivalent to function:
   * @code
   * function g(y,m,d)
   *   m = (m+9) % 12
   *   y = y - m/10
   *   return 365*y + y/4 - y/100 + y/400 + (m*306 + 5)/10 + ( d - 1) - 578040
   * @endcode
   *
   * taken from
   *
   * - http://alcor.concordia.ca/~gpkatch/gdate-algorithm.html
   *
   * with a minor modification (offset 578040).
   *
   * The offset <tt>578040 == number of days between Oct 15, 1582 and Mar 1,
   * 0000)</tt>.
   *
   * <b>The formula for day of week</b>:
   *
   * This follows from the properties of Lilian Day Number:
   * @code
   * g = gday(y,m,d)
   * wday = 1 + (3 + (g % 7))
   * @endcode
   * where, <tt>1 => Mon</tt>, <tt>2 => Tue</tt>, ..., <tt>7 => Sun</tt>.
   */ // }}}
  constexpr static int32_t gday(int32_t y, int32_t m, int32_t d) noexcept
  {
    return (m<3) ? gday_f(y-1, m+9, d) : gday_f(y, m-3, d);
  }
  // -
  constexpr static int32_t gday_f(int32_t y, int32_t m, int32_t d) noexcept
  {
    return 365*y + y/4 - y/100 + y/400 + (m*306+5)/10 + (d-1) - 578040;
  }
  /** // doc: yday(y,m,d) {{{
   * @brief Given a date (year, month, day of month) determine day of year.
   * @param y year, an integer in range <tt>[@ref STM32XX_DATE_YEAR_MIN ..
   *        @ref STM32XX_DATE_YEAR_MAX]</tt>,
   * @param m month, an integer in range <tt>[1 .. 12]</tt>,
   * @param d day of month, an integer in range <tt>[1 .. mdays(y,m)]</tt>,
   * @return an integer from range <tt>[0 .. 364]</tt> or <tt>[0 .. 365]</tt>
   * (leap year).
   */ // }}}
  constexpr static int32_t yday(int32_t y, int32_t m, int32_t d) noexcept
  {
    return gday(y,m,d) - gday(y,1,1);
  }
  /** // doc: wday() {{{
   * @brief Given a date (year, month, day of month) determine day of week.
   * @param g day number, as returned by gday(year_t,mon_t,mday_t)
   * @return an enum naming the day of week of given date @c d.
   */ // }}}
  constexpr static int32_t wday(int32_t g) noexcept
  {
    return (wday_t)(1 + ((3+g) % 7));
  }
  /** // doc: mdays(y,m) {{{
   * @brief Return number of days in a month.
   * @param y year, an integer in range <tt>[@ref STM32XX_DATE_YEAR_MIN ..
   *          @ref STM32XX_DATE_YEAR_MAX]</tt>,
   * @param m month, an integer in range <tt>[1 .. 12]</tt>
   * @return number of days in the month @c m &mdash; an integer from range
   *         <tt>[28 .. 31]</tt>.
   */ // }}}
  constexpr static int32_t mdays(int32_t y, int32_t m) noexcept
  {
    return (m == 2) ? (28 + leap_year(y)) : 30 + ((m + (m>>3))&0x1);
  }
  /** // doc: leap_year() {{{
   * @brief Is this a leap year?
   * @param y year, an integer in range <tt>[@ref STM32XX_DATE_YEAR_MIN ..
   *        @ref STM32XX_DATE_YEAR_MAX]</tt>
   * @return @c 1 if @c y is a leap year, or @c 0 if not.
   */ // }}}
  constexpr static int32_t leap_year(int32_t y) noexcept
  {
    return ((y%400) == 0) ? 1: (((y%100) == 0) ? 0: ((y%4)==0) ? 1 : 0);
  }
  /** // doc: dst_summer_yday(y) {{{
   * @fn int32_t dst_summer_yday(int32_t)
   * @brief Determine the first day of summer time of year @c y.
   * @param y year, an integer value
   * @return day number of the first day of summer time of year @c y, relative
   * to Jan 1 of the year @c y.
   * @brief 
   */ // }}}
  constexpr static int32_t dst_summer_yday(int32_t y) noexcept
  {
    // FIXME: this rule shouldn't be hardcoded (it works for EU, not for others)
    return find_wday(wday_sun, gday(y,4,1)) - 7 - gday(y,1,1);
  }
  /** // doc: dst_winter_yday(y) {{{
   * @fn int32_t dst_winter_yday(int32_t)
   * @brief Determine the first day of winter time of year @c y.
   * @param y year, an integer value
   * @return day number of the first day of winter time of year @c y, relative
   * to Jan 1 of the year @c y.
   * @brief 
   */ // }}}
  constexpr static int32_t dst_winter_yday(int32_t y) noexcept
  {
    // FIXME: this rule shouldn't be hardcoded (it works for EU, not for others)
    return find_wday(wday_sun, gday(y,11,1)) - 7 - gday(y,1,1);
  }
  /** // doc: find_wday(w, g) {{{
   * @brief Find particular day of week in calendar.
   * @param w day of the week to find
   * @param g Lilian Day Number of the search base,
   * @return Lilian Day Number of the day found
   *
   * Given a name of day of week and Lilian Date of a search base day, this
   * method searches forward for that week day.
   *
   * <b>Examples</b>:
   *
   * 1. Find first Friday of Oct, 2013:
   *    @code
   *    find_wday(wday_fri, gday(2013,10,1)); // -> Oct 4, 2013
   *    @endcode
   * 2. Find second Friday of Oct, 2013:
   *    @code
   *    find_wday(wday_fri, gday(2013,10,4)); // -> Oct 11, 2013
   *    @endcode
   */ // }}}
  constexpr static int32_t
  find_wday(wday_t w, int32_t g) noexcept
  {
    return g + ((7 + w - wday(g)) % 7);
  }
  /** // doc: clamp_year(y) {{{
   * @brief Correct year if out of range.
   * @param y a reference to year variable.
   * @return corrected year.
   */ // }}}
  constexpr static int32_t clamp_year(int32_t y) noexcept
  {
    return  (y < STM32XX_DATE_YEAR_MIN) ?  STM32XX_DATE_YEAR_MIN 
        :  ((y > STM32XX_DATE_YEAR_MAX) ?  STM32XX_DATE_YEAR_MAX : y);
  }
  /** // doc: clamp_year() {{{
   * @brief Correct month if out of range.
   * @param m a reference to month variable.
   * @return corrected month.
   */ // }}}
  constexpr static int32_t clamp_mon(int32_t m) noexcept
  {
    return (m < 1) ? 1 : ((m > 12) ? 12 : m);
  }
  /** // doc: clamp_mday() {{{
   * @brief Correct day of month if out of range.
   * @param y year, an integer in range <tt>[@ref STM32XX_DATE_YEAR_MIN ..
   *        @ref STM32XX_DATE_YEAR_MAX]</tt>,
   * @param m month, an integer in range <tt>[1 .. 12]</tt>,
   * @param d a reference to day of month variable.
   * @return corrected day of month.
   */ // }}}
  constexpr static int32_t clamp_mday(int32_t y, int32_t m, int32_t d) noexcept
  {
    return (d < 1) ? 1 : ((d > mdays(y,m)) ? mdays(y,m) : d);
  }
};

} /* namespace stm32xx */

/** // doc: operator+() {{{
 * @fn stm32xx::date stm32xx::operator+(stm32xx::date const&,int32_t)
 * @brief operator+()
 */ // }}}
inline stm32xx::date operator + (stm32xx::date const& d, int32_t days) noexcept
{
  stm32xx::date d2(d);
  d2.advance_date(days);
  return d2;
}
/** // doc: operator-() {{{
 * @fn stm32xx::date stm32xx::operator-(stm32xx::date const&,int32_t)
 * @brief operator-()
 */ // }}}
inline stm32xx::date operator - (stm32xx::date const& d, int32_t days) noexcept
{
  stm32xx::date d2(d);
  d2.advance_date(-days);
  return d2;
}

#endif /* STM32XX_DATE_HPP_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
