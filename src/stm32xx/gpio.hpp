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

/** // doc: stm32xx/gpio.hpp {{{
 * \file stm32xx/gpio.hpp
 * \todo Write documentation
 */ // }}}
#ifndef STM32XX_GPIO_HPP_INCLUDED
#define STM32XX_GPIO_HPP_INCLUDED

#include <stm32xx/stm32fxxx.h>
#include <stm32xx/bits.hpp>

namespace stm32xx {
/** // doc: namespace gpio {{{
 * @brief Support for STM32 GPIO.
 */ // }}}
namespace gpio {
/* FIXME: uint16_t for STM32F10x, uint32_t for STM32F4xx. What for others?  */
typedef uint16_t pins_t;
} /* namespace gpio */
} /* namespace stm32xx */

/* GPIO operation details */
namespace stm32xx {
namespace gpio {
/** // doc: namespace detail {{{
 * @brief Functions and objects used by gpio::rt and gpio::ct.
 */ // }}}
namespace detail {

/** // doc: gpio::detail::crl_cnf_bits() {{{
 * @brief Compute CNF bits for GPIOx_CRL register.
 *
 * <b>Usage example</b>:
 *
 * @code
 * GPIOB->CRL |= crl_cnf_bits(GPIO_Pin_0|GPIO_Pin_11, GPIO_mode_Out_PP)
 * @endcode
 *
 * @todo Move usage example of crl_cnf_bits to examples.
 * 
 * @see ST RM0008 Reference manual (STM32F10x) for register definitions.
 */ // }}}
constexpr uint32_t
crl_cnf_bits(pins_t pins, GPIOMode_TypeDef mode)
{
  return  ((pins & GPIO_Pin_0) ? ((mode & 0x0Cul) << 0x00) : 0x00)
        | ((pins & GPIO_Pin_1) ? ((mode & 0x0Cul) << 0x04) : 0x00)
        | ((pins & GPIO_Pin_2) ? ((mode & 0x0Cul) << 0x08) : 0x00)
        | ((pins & GPIO_Pin_3) ? ((mode & 0x0Cul) << 0x0C) : 0x00)
        | ((pins & GPIO_Pin_4) ? ((mode & 0x0Cul) << 0x10) : 0x00)
        | ((pins & GPIO_Pin_5) ? ((mode & 0x0Cul) << 0x14) : 0x00)
        | ((pins & GPIO_Pin_6) ? ((mode & 0x0Cul) << 0x18) : 0x00)
        | ((pins & GPIO_Pin_7) ? ((mode & 0x0Cul) << 0x1C) : 0x00);
}

/** // doc: gpio::detail::crl_cnf_mask() {{{
 * @todo Write documentation for crl_cnf_mask().
 */ // }}}
constexpr uint32_t
crl_cnf_mask(pins_t pins)
{
  return  ((pins & GPIO_Pin_0) ? (0x0Cul << 0x00) : 0x00)
        | ((pins & GPIO_Pin_1) ? (0x0Cul << 0x04) : 0x00)
        | ((pins & GPIO_Pin_2) ? (0x0Cul << 0x08) : 0x00)
        | ((pins & GPIO_Pin_3) ? (0x0Cul << 0x0C) : 0x00)
        | ((pins & GPIO_Pin_4) ? (0x0Cul << 0x10) : 0x00)
        | ((pins & GPIO_Pin_5) ? (0x0Cul << 0x14) : 0x00)
        | ((pins & GPIO_Pin_6) ? (0x0Cul << 0x18) : 0x00)
        | ((pins & GPIO_Pin_7) ? (0x0Cul << 0x1C) : 0x00);
}

/** // doc: gpio::detail::crh_cnf_bits() {{{
 * @brief Compute CNF bits for GPIOx_CRH register.
 *
 * <b>Usage example</b>:
 *
 * @code
 * GPIOB->CRH |= crh_cnf_bits(GPIO_Pin_0|GPIO_Pin_11, GPIO_mode_Out_PP)
 * @endcode
 *
 * @see ST RM0008 Reference manual (STM32F10x) for register definitions.
 */ // }}}
constexpr uint32_t
crh_cnf_bits(pins_t pins, GPIOMode_TypeDef mode)
{
  return  ((pins & GPIO_Pin_8 ) ? ((mode & 0x0C) << 0x00) : 0x00)
        | ((pins & GPIO_Pin_7 ) ? ((mode & 0x0C) << 0x04) : 0x00)
        | ((pins & GPIO_Pin_10) ? ((mode & 0x0C) << 0x08) : 0x00)
        | ((pins & GPIO_Pin_11) ? ((mode & 0x0C) << 0x0C) : 0x00)
        | ((pins & GPIO_Pin_12) ? ((mode & 0x0C) << 0x10) : 0x00)
        | ((pins & GPIO_Pin_13) ? ((mode & 0x0C) << 0x14) : 0x00)
        | ((pins & GPIO_Pin_14) ? ((mode & 0x0C) << 0x18) : 0x00)
        | ((pins & GPIO_Pin_15) ? ((mode & 0x0C) << 0x1C) : 0x00);
}

/** // doc: gpio::detail::crh_cnf_mask() {{{
 * @todo Write documentation for crh_cnf_mask().
 */ // }}}
constexpr uint32_t
crh_cnf_mask(pins_t pins)
{
  return  ((pins & GPIO_Pin_8 ) ? (0x0Cul << 0x00) : 0x00)
        | ((pins & GPIO_Pin_9 ) ? (0x0Cul << 0x04) : 0x00)
        | ((pins & GPIO_Pin_10) ? (0x0Cul << 0x08) : 0x00)
        | ((pins & GPIO_Pin_11) ? (0x0Cul << 0x0C) : 0x00)
        | ((pins & GPIO_Pin_12) ? (0x0Cul << 0x10) : 0x00)
        | ((pins & GPIO_Pin_13) ? (0x0Cul << 0x14) : 0x00)
        | ((pins & GPIO_Pin_14) ? (0x0Cul << 0x18) : 0x00)
        | ((pins & GPIO_Pin_15) ? (0x0Cul << 0x1C) : 0x00);
}

/** // doc: gpio::detail::crl_mode_bits() {{{
 * @brief Compute MODE bits for GPIOx_CRL register.
 *
 * <b>Usage example</b>:
 *
 * @code
 * GPIOB->CRL |= crl_mode_bits(GPIO_Pin_0|GPIO_Pin_11, GPIO_speed_10MHz)
 * @endcode
 *
 * @see ST RM0008 Reference manual (STM32F10x) for register definitions.
 */ // }}}
constexpr uint32_t
crl_mode_bits(pins_t pins, GPIOSpeed_TypeDef speed)
{
  return  ((pins & GPIO_Pin_0) ? ((speed & 0x03) << 0x00) : 0x00)
        | ((pins & GPIO_Pin_1) ? ((speed & 0x03) << 0x04) : 0x00)
        | ((pins & GPIO_Pin_2) ? ((speed & 0x03) << 0x08) : 0x00)
        | ((pins & GPIO_Pin_3) ? ((speed & 0x03) << 0x0C) : 0x00)
        | ((pins & GPIO_Pin_4) ? ((speed & 0x03) << 0x10) : 0x00)
        | ((pins & GPIO_Pin_5) ? ((speed & 0x03) << 0x14) : 0x00)
        | ((pins & GPIO_Pin_6) ? ((speed & 0x03) << 0x18) : 0x00)
        | ((pins & GPIO_Pin_7) ? ((speed & 0x03) << 0x1C) : 0x00);
}

/** // doc: gpio::detail::crl_mode_mask() {{{
 * @todo Write documentation for crl_mode_mask()
 */ // }}}
constexpr uint32_t
crl_mode_mask(pins_t pins)
{
  return  ((pins & GPIO_Pin_0) ? (0x03 << 0x00) : 0x00)
        | ((pins & GPIO_Pin_1) ? (0x03 << 0x04) : 0x00)
        | ((pins & GPIO_Pin_2) ? (0x03 << 0x08) : 0x00)
        | ((pins & GPIO_Pin_3) ? (0x03 << 0x0C) : 0x00)
        | ((pins & GPIO_Pin_4) ? (0x03 << 0x10) : 0x00)
        | ((pins & GPIO_Pin_5) ? (0x03 << 0x14) : 0x00)
        | ((pins & GPIO_Pin_6) ? (0x03 << 0x18) : 0x00)
        | ((pins & GPIO_Pin_7) ? (0x03 << 0x1C) : 0x00);
}

/** // doc: gpio::detail::crh_mode_bits() {{{
 * @brief Compute MODE bits for GPIOx_CRH register.
 *
 * <b>Usage example</b>:
 *
 * @code
 * GPIOB->CRH |= crh_mode_bits(GPIO_Pin_0|GPIO_Pin_11, GPIO_speed_10MHz)
 * @endcode
 *
 * @see ST RM0008 Reference manual (STM32F10x) for register definitions.
 */ // }}}
constexpr uint32_t
crh_mode_bits(pins_t pins, GPIOSpeed_TypeDef speed)
{
  return  ((pins & GPIO_Pin_8 ) ? ((speed & 0x03) << 0x00) : 0x00)
        | ((pins & GPIO_Pin_7 ) ? ((speed & 0x03) << 0x04) : 0x00)
        | ((pins & GPIO_Pin_10) ? ((speed & 0x03) << 0x08) : 0x00)
        | ((pins & GPIO_Pin_11) ? ((speed & 0x03) << 0x0C) : 0x00)
        | ((pins & GPIO_Pin_12) ? ((speed & 0x03) << 0x10) : 0x00)
        | ((pins & GPIO_Pin_13) ? ((speed & 0x03) << 0x14) : 0x00)
        | ((pins & GPIO_Pin_14) ? ((speed & 0x03) << 0x18) : 0x00)
        | ((pins & GPIO_Pin_15) ? ((speed & 0x03) << 0x1C) : 0x00);
}

/** // doc: gpio::detail::crh_mode_mask {{{
 * @todo Write documentation for crh_mode_mask().
 */ // }}}
constexpr uint32_t
crh_mode_mask(pins_t pins)
{
  return  ((pins & GPIO_Pin_8 ) ? (0x03 << 0x00) : 0x00)
        | ((pins & GPIO_Pin_7 ) ? (0x03 << 0x04) : 0x00)
        | ((pins & GPIO_Pin_10) ? (0x03 << 0x08) : 0x00)
        | ((pins & GPIO_Pin_11) ? (0x03 << 0x0C) : 0x00)
        | ((pins & GPIO_Pin_12) ? (0x03 << 0x10) : 0x00)
        | ((pins & GPIO_Pin_13) ? (0x03 << 0x14) : 0x00)
        | ((pins & GPIO_Pin_14) ? (0x03 << 0x18) : 0x00)
        | ((pins & GPIO_Pin_15) ? (0x03 << 0x1C) : 0x00);
}

/** // doc: gpio::detail::crh_bits() {{{
 * @brief Compute bits for GPIOx_CRH register.
 *
 * <b>Usage example</b>:
 *
 * @code
 * #define PINS (GPIO_Pin_0|gpio_pin_11)
 * GPIOB->CRL |= crl_bits(PINS,GPIO_mode_Output_PP,GPIO_speed_10MHz);
 * @endcode
 *
 * @see ST RM0008 Reference manual (STM32F10x) for register definitions.
 */ // }}}
constexpr uint32_t
crl_bits(pins_t pins, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed)
{
  return crl_cnf_bits(pins, mode) | crl_mode_bits(pins, speed);
}

/** // doc: gpio::detail::crl_mask() {{{
 * @todo Write documentation for crl_mask().
 */ // }}}
constexpr uint32_t
crl_mask(pins_t pins)
{
  return crl_cnf_mask(pins) | crl_mode_mask(pins);
}

/** // doc: gpio::detail::crh_bits() {{{
 * @brief Compute bits for GPIOx_CRH register.
 *
 * <b>Usage example</b>:
 *
 * @code
 * #define PINS (GPIO_Pin_0|gpio_pin_11)
 * GPIOB->CRH |= crh_bits(PINS,GPIO_mode_Output_PP,GPIO_speed_10MHz);
 * @endcode
 *
 * @see ST RM0008 Reference manual (STM32F10x) for register definitions.
 */ // }}}
constexpr uint32_t
crh_bits(pins_t pins, GPIOMode_TypeDef mode, GPIOSpeed_TypeDef speed)
{
  return crh_cnf_bits(pins, mode) | crh_mode_bits(pins, speed);
}

/** // doc: gpio::detail::crh_mask() {{{
 * @todo Write documentation for crh_mask().
 */ // }}}
constexpr uint32_t
crh_mask(pins_t pins)
{
  return crh_cnf_mask(pins) | crh_mode_mask(pins);
}

} /* namespace rt */
} /* namespace gpio */
} /* namespace stm32xx */

/* GPIO operations with compile time arguments */
namespace stm32xx {
namespace gpio {
/** // doc: namespace ct {{{
 * Compile-time machinery supporting configuration of STM32 GPIOs 
 */ // }}}
namespace ct {

/** // doc: gpio::ct::crl_cnf_bits {{{
 * @brief Compute CNF bits for GPIOx_CRL register.
 *
 * This meta-function computes CNF bits that should be set in GPIOx_CRL
 * register in order to realize given GPIO mode (@c _mode) on a set of
 * prescribed GPIO pins (@c _pins).
 *
 * @note This meta-function covers only pins @c 0 to @c 7. Pins @c 8 to @c 15
 *       are covered by @ref ct::crh_cnf_bits "crh_cnf_bits" meta-function.
 * @note This meta-function should be used together with
 *       @ref ct::crl_cnf_mask "crl_cnf_mask".
 * 
 * @todo Prepare example for crl_cnf_bits.
 *
 * @see ST RM0008 Reference manual (STM32F10x) for register definitions.
 */ // }}}
template <pins_t _pins, GPIOMode_TypeDef _mode>
struct crl_cnf_bits
{
  static_assert(IS_GPIO_PIN(_pins), "invalid pin specifier");
  static_assert(IS_GPIO_MODE(_mode), "invalid mode specifier");
  constexpr static uint32_t value = detail::crl_cnf_bits(_pins, _mode);
};

/** // doc: gpio::ct::crl_cnf_mask {{{
 * @brief Compute CNF mask for GPIOx_CRL register.
 *
 * This meta-function computes a bit mask to determine which of the CNF bits
 * are going to be changed in GPIOx_CRL register when configuring given GPIO
 * pins (@c _pins).
 *
 * @see ST RM0008 Reference manual (STM32F10x) for register definitions.
 */ // }}}
template <pins_t _pins>
struct crl_cnf_mask
{
  static_assert(IS_GPIO_PIN(_pins), "invalid pin specifier");
  constexpr static uint32_t value = detail::crl_cnf_mask(_pins);
};

/** // doc: gpio::ct::crh_cnf_bits {{{
 * @brief Compute CNF bits for GPIOx_CRH register.
 *
 * This meta-function computes CNF bits that should be set in GPIOx_CRL
 * register in order to realize given GPIO mode (@c _mode) on a set of
 * prescribed GPIO pins (@c _pins).
 *
 * @note This meta-function covers only pins @c 8 to @c 15. Pins @c 0 to @c 7 
 *       are covered by @ref ct::crl_cnf_bits "crl_cnf_bits" meta-function.
 * @note This meta-function should be used together with
 *       @ref ct::crh_cnf_mask "crh_cnh_mask".
 *
 * @todo Prepare example for crh_cnf_bits.
 *
 * @see ST RM0008 Reference manual (STM32F10x) for register definitions.
 */ // }}}
template <pins_t _pins, GPIOMode_TypeDef _mode>
struct crh_cnf_bits
{
  static_assert(IS_GPIO_PIN(_pins), "invalid pin specifier");
  static_assert(IS_GPIO_MODE(_mode), "invalid mode specifier");
  constexpr static uint32_t value = detail::crl_cnf_bits(_pins, _mode);
};

/** // doc: gpio::ct::crh_cnf_mask {{{
 * @brief Compute CNF mask for GPIOx_CRH register.
 *
 * This meta-function computes a bit mask to determine which of the CNF bits
 * are going to be changed in GPIOx_CRH register when configuring given GPIO
 * pins (@c _pins).
 *
 * @see ST RM0008 Reference manual (STM32F10x) for register definitions.
 */ // }}}
template <pins_t _pins>
struct crh_cnf_mask
{
  static_assert(IS_GPIO_PIN(_pins), "invalid pin specifier");
  constexpr static uint32_t value = detail::crh_cnf_mask(_pins);
};

/** // doc: gpio::ct::crl_mode_bits {{{
 * @brief Compute MODE bits for GPIOx_CRL register.
 *
 * <b>Usage example</b>:
 *
 * @code
 * #define PINS (GPIO_Pin_0|GPIO_Pin_11)
 * GPIOB->CRL |= crl_mode_bits<PINS, GPIO_speed_10MHz>::value
 * @endcode
 *
 * @see ST RM0008 Reference manual (STM32F10x) for register definitions.
 */ // }}}
template <pins_t _pins, GPIOSpeed_TypeDef _speed>
struct crl_mode_bits
{
  static_assert(IS_GPIO_PIN(_pins), "invalid pin specifier");
  static_assert((_speed==0)||IS_GPIO_SPEED(_speed), "invalid speed specifier");
  constexpr static uint32_t value = detail::crl_mode_bits(_pins, _speed);
};

/** // doc: gpio::ct::crl_mode_mask {{{
 * @brief Compute MODE mask for GPIOx_CRL register.
 *
 * This meta-function computes a bit mask to determine which of the MODE bits
 * are going to be changed in GPIOx_CRL register when configuring given GPIO
 * pins (@c _pins).
 *
 * @see ST RM0008 Reference manual (STM32F10x) for register definitions.
 */ // }}}
template <pins_t _pins>
struct crl_mode_mask
{
  static_assert(IS_GPIO_PIN(_pins), "invalid pin specifier");
  constexpr static uint32_t value = detail::crl_mode_mask(_pins);
};

/** // doc: gpio::ct::crh_mode_bits {{{
 * @brief Compute MODE bits for GPIOx_CRH register.
 *
 * <b>Usage example</b>:
 *
 * @code
 * #define PINS (GPIO_Pin_0|GPIO_Pin_11)
 * GPIOB->CRH |= crh_mode_bits<PINS, GPIO_speed_10MHz>::value
 * @endcode
 *
 * @see ST RM0008 Reference manual (STM32F10x) for register definitions.
 */ // }}}
template <pins_t _pins, GPIOSpeed_TypeDef _speed>
struct crh_mode_bits
{
  static_assert(IS_GPIO_PIN(_pins), "invalid pin specifier");
  static_assert((_speed==0)||IS_GPIO_SPEED(_speed), "invalid speed specifier");
  constexpr static uint32_t value = detail::crh_mode_bits(_pins, _speed);
};

/** // gpio::ct::crh_mode_mask {{{
 * @brief Compute MODE mask for GPIOx_CRH register.
 *
 * This meta-function computes a bit mask to determine which of the MODE bits
 * are going to be changed in GPIOx_CRH register when configuring given GPIO
 * pins (@c _pins).
 *
 * @see ST RM0008 Reference manual (STM32F10x) for register definitions.
 */ // }}}
template <pins_t _pins>
struct crh_mode_mask
{
  static_assert(IS_GPIO_PIN(_pins), "invalid pin specifier");
  constexpr static uint32_t value = detail::crh_mode_mask(_pins);
};

/** // doc: gpio::ct::crl_bits {{{
 * @brief Compute bits for GPIOx_CRL register.
 *
 * <b>Usage example</b>:
 *
 * @code
 * #define PINS (GPIO_Pin_0|GPIO_Pin_11)
 * GPIOB->CRL |= crl_bits<PINS, GPIO_mode_Output_PP, GPIO_speed_10MHz>::value
 * @endcode
 *
 * @see ST RM0008 Reference manual (STM32F10x) for register definitions.
 */ // }}}
template <pins_t _pins, GPIOMode_TypeDef _mode, GPIOSpeed_TypeDef _speed=0>
struct crl_bits
{
  static_assert(IS_GPIO_PIN(_pins), "invalid pin specifier");
  static_assert(IS_GPIO_MODE(_mode), "invalid mode specifier");
  static_assert(   (((_mode&0x10) != 0) && IS_GPIO_SPEED(_speed)) /* Output */
                || (((_mode&0x10) == 0) && (_speed == 0)),        /* Input */
                "invalid speed specifier for selected mode");
  constexpr static uint32_t value = detail::crl_bits(_pins,_mode,_speed);
};

/** // doc: gpio::ct::crl_mask {{{
 * @todo Write documentation for crl_bits.
 */ // }}}
template <pins_t _pins>
struct crl_mask
{
  static_assert(IS_GPIO_PIN(_pins), "invalid pin specifier");
  constexpr static uint32_t value = detail::crl_mask(_pins);
};

/** // doc: gpio::ct::crh_bits {{{
 * @brief Compute bits for GPIOx_CRH register.
 *
 * <b>Usage example</b>:
 *
 * @code
 * #define PINS (GPIO_Pin_0|GPIO_Pin_11)
 * GPIOB->CRH |= crh_bits<PINS, GPIO_mode_Output_PP, GPIO_speed_10MHz>::value
 * @endcode
 *
 * @see ST RM0008 Reference manual (STM32F10x) for register definitions.
 */ // }}}
template <pins_t _pins, GPIOMode_TypeDef _mode, GPIOSpeed_TypeDef _speed=0>
struct crh_bits
{
  static_assert(IS_GPIO_PIN(_pins), "invalid pin specifier");
  static_assert(IS_GPIO_MODE(_mode), "invalid mode specifier");
  static_assert(   (((_mode&0x10) != 0) && IS_GPIO_SPEED(_speed)) /* Output */
                || (((_mode&0x10) == 0) && (_speed == 0)),        /* Input */
                "invalid speed specifier for selected mode");
  constexpr static uint32_t value = detail::crh_bits(_pins,_mode,_speed);
};

/** // doc: gpio::ct::crh_mask {{{
 * @todo Write documentation for crh_bits.
 */ // }}}
template <pins_t _pins>
struct crh_mask
{
  static_assert(IS_GPIO_PIN(_pins), "invalid pin specifier");
  constexpr static uint32_t value = detail::crh_mask(_pins);
};

} /* namespace ct */
} /* namespace gpio */
} /* namesapce stm32xx */

#endif /* STM32XX_GPIO_HPP_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
