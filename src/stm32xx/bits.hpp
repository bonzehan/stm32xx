/*
 * Copyright (c) by Pawel Tomulik <ptomulik@meil.pw.edu.pl>
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

/** // doc: stm32xx/bits.hpp {{{
 * \file stm32xx/bits.hpp.
 * \todo Write documentation
 */ // }}}
#ifndef STM32XX_BITS_HPP_INCLUDED
#define STM32XX_BITS_HPP_INCLUDED

#include <cstdint>

namespace stm32xx {
/** // doc: namespace bits {{{
 * @brief Some basic operations on bits. 
 */ // }}}
namespace bits {
/** // doc: namesapce ct {{{
 * @brief Compile-time version of bit operations.
 */ // }}}
namespace ct {

/** // doc: bits::get_bits {{{
 * @brief Meta-function to return the @c value held in masked.
 *
 * <b>Usage example</b>:
 *
 * @todo Move usage example of bits::get_bits() to examples.
 *
 * @code
 * typedef masked<0x3210, 0xFFFF> m;
 * uint32_t m_bits = get_bits<m>::value; // 0x3210
 * @endcode
 */ // }}}
template <typename _masked>
  struct get_bits
  {
    constexpr static uint32_t value = _masked::bits;
  };

/** // doc: bits::get_mask {{{
 * @brief Meta-function to return the @c mask held in masked.
 *
 * <b>Usage example</b>:
 *
 * @code
 * typedef masked<0x3210, 0xFFFF> m;
 * uint32_t m_mask = get_mask<m>::value; // 0xFFFF
 * @endcode
 */ // }}}
template <typename _masked>
  struct get_mask
  {
    constexpr static uint32_t value = _masked::mask;
  };

/** // doc: bits::masked {{{
 * @brief Represent bits masked with a mask.
 *
 * This is a (@c _bits, @c _mask) pair with 32-bit @c _bits and @c _mask items.
 * It is used accross the library to represent selected bits of a 32-bit word.
 * It is asserted at compile-time that @c _bits fit to their @c _mask.
 *
 * <b>Example</b>:
 *
 * Store 16 least significant bits equal to 0x3210:
 * @code
 * typedef masked<0x3210, 0xFFFF> mymasked;
 * @endcode
 *
 * The following code generates compile-time error, becaus @c 0x11 does not fit
 * to @c 0x0F mask:
 *
 * @code
 * typedef masked<0x11, 0x0F> mymasked;
 * @endcode
 */ // }}}
template <uint32_t _bits, uint32_t _mask>
  struct masked
  {
    static_assert((_bits&_mask)==_bits, "bits do not fit to the mask");
    constexpr static uint32_t bits = _bits;
    constexpr static uint32_t mask = _mask;
  };

/** // doc: bits::mix {{{
 * @brief Mix bits from several sources.
 *
 * <b>Usage examples</b>:
 *
 * The following code returns @c 0x21:
 * @code 
 * mix< masked<0x0001,0x000F>, masked<0x0020,0x00F0> >::value;
 * @endcode
 *
 * The following code returns @c 0xFF:
 * @code 
 * mix< masked<0x0001,0x000F>, masked<0x0020,0x00F0> >::mask;
 * @endcode
 *
 * The following code generates compile-time error (masks overlap):
 *
 * @code
 * mix< masked<0x01,0x1F>, masked<0x10,0xF0> >::value;
 * @endcode
 */ // }}}
template <typename ... _list> struct mix;
template <typename _m, typename ... _tail>
  struct mix<_m,_tail...>
  {
    constexpr static uint32_t _m_mask = get_mask<_m>::value;
    constexpr static uint32_t _t_mask = get_mask<mix<_tail...> >::value;

    static_assert((_m_mask^_t_mask)==(_m_mask|_t_mask), "masks overlap");

    constexpr static uint32_t _t_bits = get_bits<mix<_tail...> >::value;
    constexpr static uint32_t _m_bits = get_bits<_m>::value;

    /** // doc: mask {{{
     * The mask of the resultant masked bits.
     * @hideinitializer
     */ // }}}
    constexpr static uint32_t mask = _t_mask | _m_mask;
    /** // doc: bits {{{
     * The bits of the resultant masked bits.
     * @hideinitializer
     */ // }}}
    constexpr static uint32_t bits = _t_bits | _m_bits;
    /** // doc: value {{{
     * Return value (same as bits).
     * @hideinitializer
     */ // }}}
    constexpr static uint32_t value = bits;
  };

/* Specialization of `mix` class to stop compile-time recursion. */
template <> 
  struct mix<> 
  { 
    constexpr static uint32_t bits = 0;
    constexpr static uint32_t mask = 0; 
    constexpr static uint32_t value = 0;
  };

/* Implementation of modify<> operation */
template <uint32_t _bits, uint32_t _mask>
  struct modify_impl
  {
    static_assert((_bits&_mask)==_bits, "bits do not fit to the mask");
    template<typename T>
    static void in(T& x)
    {
      x = (x & ~_mask) | _bits;
    }
  };

template <uint32_t _bits>
  struct modify_impl<_bits, 0ul>
  {
    static_assert(_bits==0ul, "bits do not fit to the mask");
    template<typename T>
    static void in(T&)
    {
      /* no bits to modify (mask is 0) */
    }
  };

/** // doc: bits::modify {{{
 * @brief Modify selected bits in a register or memory location.
 *
 * <b>Example</b>:
 *
 * This sets 16 most significant bits in @c var to @c 0x1234.
 *
 * @code
 * using bits = masked<0x12340000, 0xFFFF0000ul>;
 * modify<bits>::in(var);
 * @endcode
 */ // }}}
template <typename _masked>
  struct modify
    : modify_impl<get_bits<_masked>::value, get_mask<_masked>::value>
  {
  };

} /* namespace ct */
} /* namespace bits */
} /* namespace stm32xx */

#endif /* STM32XX_BITS_HPP_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
