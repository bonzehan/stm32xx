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

// stm32xx/bcd.hpp

/** // doc: stm32xx/bcd.hpp {{{ 
 * @file stm32xx/bcd.hpp
 * @todo Write documentation
 */ // }}}
#ifndef STM32XX_BCD_HPP_INCLUDED
#define STM32XX_BCD_HPP_INCLUDED

#include <type_traits>
#include <cstdint>

namespace stm32xx {

/** // doc: bcdp<N,T> {{{
 * @brief Convert binary numbers to packed BCD and vice versa.
 *
 * @tparam N number of decimal digits to be converted.
 * @tparam T data type (must be unsigned integer type).
 *
 * <b>Examples (binary to BCD)</b>:
 * @code
 * using namesapce stm32xx;
 * bcpd<0>::encode(12);   // returns 0x00 (0 digits are taken into account)
 * bcpd<1>::encode(12);   // returns 0x02 (only last digit is converted)
 * bcpd<2>::encode(12);   // returns 0x12 (two digits are converted)
 * bcpd<4>::encode(1234); // returns 0x1234 
 * @endcode
 *
 * <b>Examples (BCD to binary)</b>:
 * @code
 * using namesapce stm32xx;
 * bcpd<0>::decode(0x12);   // returns 0 (0 digits are taken into account)
 * bcpd<1>::decode(0x12);   // returns 2 (only last digit is converted)
 * bcpd<2>::decode(0x12);   // returns 12 (two digits are converted)
 * bcpd<4>::decode(0x1234); // returns 1234 
 * @endcode
 */ // }}}
template <unsigned int N, typename T = uint32_t>
struct bcdp
{
  constexpr static T divider = bcdp<N-1, T>::uplimit;
  constexpr static T uplimit = 10 * divider;
  constexpr static unsigned int ndigits = N;
  typedef T type;

  static_assert(std::is_unsigned<T>::value, "T must be unsigned integer type");

  /** // doc: encode(x) {{{
   * @brief Convert binary number to packed BCD code.
   * @param x binary number to be encoded.
   * @return packed BCD code.
   *
   * <b>Example</b>:
   * @code
   * using namespace stm32xx;
   * uint32_t y1 = bcdp<2>::encode(12);  // returns 0x12
   * uint32_t y2 = bcdp<2>::encode(123); // returns 0x23 (last two digits encoded)
   * @endcode
   */ // }}}
  constexpr static T
  encode(T x) noexcept
  {
    return ((x % uplimit) / divider) << (4*(N-1)) | bcdp<N-1,T>::encode(x);
  }
  /** // doc: decode(x) {{{
   * @brief Convert packed BCD code to binary number.
   * @param y packed BCD code to be decoded.
   * @return decoded binary number.
   *
   * <b>Example</b>:
   * @code
   * using namespace stm32xx;
   * uint32_t x1 = bcdp<2>::decode(0x12);  // returns 12
   * uint32_t x2 = bcdp<2>::decode(0x123); // returns 23 (last two digits decoded)
   * @endcode
   */ // }}}
  constexpr static T
  decode(T y) noexcept
  {
    return ((y >> (4*(N-1))) & (T)0xF) * divider + bcdp<N-1,T>::decode(y);
  }
};

template <typename T>
struct bcdp<0,T>
{
  constexpr static T divider = 1;
  constexpr static T uplimit = 1;
  constexpr static unsigned int ndigits = 0;
  typedef T type;

  static_assert(std::is_unsigned<T>::value, "T must be unsigned integer type");

  constexpr static T 
  encode(T) noexcept
  {
    return (T)0;
  }
  constexpr static T
  decode(T) noexcept
  {
    return (T)0;
  }
};

} /* namespace stm32xx */

#endif /* STM32XX_BCD_HPP_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
