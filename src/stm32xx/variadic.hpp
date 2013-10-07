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

// stm32xx/variadic.hpp

/** // doc: stm32xx/variadic.hpp {{{ 
 * @file stm32xx/variadic.hpp
 * @todo Write documentation
 */ // }}}
#ifndef STM32XX_VARIADIC_HPP_INCLUDED
#define STM32XX_VARIADIC_HPP_INCLUDED

#include <cstddef>

namespace stm32xx {
namespace ct {
/** // doc: stm32xx::ct::type_pack<...> {{{
 * @todo Write documentation for stm32xx::ct::pack
 */ // }}}
template <typename ... _args>
struct type_pack
  {
    constexpr static size_t size = sizeof...(_args);
  };

template <typename _pack>
struct size
{
  constexpr static size_t value = _pack::size;
};

/** // doc: stm32xx::ct::front<_pack> {{{
 * @todo Write documentation for stm32xx::ct::front
 */ // }}}
template <typename _pack>
struct front
{
  static_assert(size<_pack>::value != 0, "empty sequence has no front");
};

/** // doc: stm32xx::ct::back<_pack> {{{
 * @todo Write documentation for stm32xx::ct::back
 */ // }}}
template <typename _pack>
struct back
{
  static_assert(size<_pack>::value != 0, "empty sequence has no back");
};

template <typename _first, typename ... _tail>
struct front<type_pack<_first,_tail...> >
{
  typedef _first type;
};

template <typename _last, typename ... _head>
struct back<type_pack<_head...,_last> >
{
  typedef _last type;
};

/** // doc: stm32xx::ct::shift<...> {{{
 * @todo Write documentation for stm32xx::ct::shift
 */ // }}}
template <typename _pack>
struct shift
{
  static_assert(size<_pack>::value != 0, "can not shift from empty sequence");
};
/** // doc: stm32xx::ct::pop<...> {{{
 * @todo Write documentation for stm32xx::ct::pop
 */ // }}}
template <typename _pack> 
struct pop
{
  static_assert(size<_pack>::value != 0, "can not pop from empty sequence");
};
/** // doc: stm32xx::ct::unshift<...> {{{
 * @todo Write documentation for stm32xx::ct::unshift
 */ // }}}
template <typename _pack, typename ... _args> struct unshift;
/** // doc: stm32xx::ct::push<...> {{{
 * @todo Write documentation for stm32xx::ct::push
 */ // }}}
template <typename _pack, typename ... _args> struct push;

template <typename _1st, typename ... _tail>
struct shift<type_pack<_1st,_tail...> >
{
  typedef type_pack<_tail...> type;
};

template <typename _last, typename ... _head>
struct pop<type_pack<_head...,_last> >
{
  typedef type_pack<_head...> type;
};

template <typename ... _args1, typename ... _args2>
struct unshift<type_pack<_args1...>, _args2...>
{
  typedef type_pack<_args2...,_args1...> type;
};

template <typename ... _args1, typename ... _args2>
struct push<type_pack<_args1...>, _args2...>
{
  typedef type_pack<_args1...,_args2...> type;
};

} /* namespace ct */
} /* namespace stm32xx */

#endif /* STM32XX_VARIADIC_HPP_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
