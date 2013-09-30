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

/** // doc: stm32xx/check.h {{{
 * \file stm32xx/check.h
 * \todo Write documentation
 */ // }}}
#ifndef STM23XX_CHECK_H_INCLUDED
#define STM23XX_CHECK_H_INCLUDED

#if defined (STM32F10X_LD) || defined (STM32F10X_LD_VL) || \
    defined (STM32F10X_MD) || defined (STM32F10X_MD_VL) || \
    defined (STM32F10X_HD) || defined (STM32F10X_HD_VL) || \
    defined (STM32F10X_XL) || defined (STM32F10X_CL)
# define STM32F10X
#else
# error "No supported target MCU specified!"
#endif

#endif /* STM23XX_CHECK_H_INCLUDED */
// vim: set expandtab tabstop=2 shiftwidth=2:
// vim: set foldmethod=marker foldcolumn=4:
