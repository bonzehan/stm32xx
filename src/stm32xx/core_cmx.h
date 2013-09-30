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

/** // doc: stm32xx/core_cmx.h {{{
 * \file stm32xx/core_cmx.h
 * \todo Write documentation
 */ // }}}
#ifndef STM32XX_CORE_CMX_H_INCLUDED
#define STM32XX_CORE_CMX_H_INCLUDED

#include <stm32xx/check.h>

#if defined(STM32F10X)
# define CORE_CM3
#else
# error "No supported target MCU specified!"
#endif

/* Include appropriate header form CMSIS library */
#if defined (CORE_CM3)
# include "core_cm3.h"
#else
# error "Could not determine MCU core"
#endif

#endif
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
