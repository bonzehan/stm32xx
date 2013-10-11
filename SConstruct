#
# Copyright (c) by Pawel Tomulik <ptomulik@meil.pw.edu.pl>
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE

import os

tools = {
    'ADDR2LINE'   : 'arm-none-eabi-addr2line',
    'AR'          : 'arm-none-eabi-ar',
    'AS'          : 'arm-none-eabi-gcc',
    'CXXFILT'     : 'arm-none-eabi-c++filt',
    'CPP'         : 'arm-none-eabi-cpp',
    'CS'          : 'arm-none-eabi-cs',
    'ELFEDIT'     : 'arm-none-eabi-elfedit',
    'CXX'         : 'arm-none-eabi-g++',
    'CC'          : 'arm-none-eabi-gcc',
    'GCC_AR'      : 'arm-none-eabi-gcc-ar',
    'GCC_NM'      : 'arm-none-eabi-gcc-nm',
    'GCC_RANLIB'  : 'arm-none-eabi-gcc-ranlib',
    'GCOV'        : 'arm-none-eabi-gcov',
    'GDB'         : 'arm-none-eabi-gdb',
    'GPROF'       : 'arm-none-eabi-gprof',
    'LINK'        : 'arm-none-eabi-ld',
    'NM'          : 'arm-none-eabi-nm',
    'OBJCOPY'     : 'arm-none-eabi-objcopy',
    'OBJDUMP'     : 'arm-none-eabi-objdump',
    'RANLIB'      : 'arm-none-eabi-ranlib',
    'READELF'     : 'arm-none-eabi-readelf',
    'SIZE'        : 'arm-none-eabi-size',
    'STRINGS'     : 'arm-none-eabi-strings',
    'STRIP'       : 'arm-none-eabi-strip',
}

#
# COMMON COMPILATION FLAGS
#
common_flags = [
    '-g',
    '-Os',
    '-Wall', 
    '-Wextra', 
    '-Werror',
    '-fmessage-length=0',
    '-funsigned-bitfields'
]

#
# ASFLAGS
#
asflags   = ['-x', 'assembler-with-cpp']
#
# CFLAGS
#
cflags    = []
#
# CXXFLAGS
#
cxxflags  = ['-fno-exceptions', '-fno-rtti']
#
# LINKFLAGS
#
linkflags = []

#
# ALL THE FLAGS TOGETHER
#
kwargs = tools.copy()
kwargs.update( ASFLAGS   = common_flags + asflags,
               CFLAGS    = common_flags + cflags,
               CXXFLAGS  = common_flags + cxxflags,
               LINKFLAGS = common_flags + linkflags )

env = Environment(ENV=os.environ, tools=['default','doxygen','textfile'], **kwargs)

mcu_targets = [

    # STM32F10x
    'STM32F10X_CL',
    'STM32F10X_LD',
    'STM32F10X_MD',
    'STM32F10X_HD',
    'STM32F10X_XL',
    'STM32F10X_LD_VL',
    'STM32F10X_MD_VL',
    'STM32F10X_HD_VL',

    # STM32F4xx
#    'STM32F4XX',
#    'STM32F40XX',
#    'STM32F427X',
]

stdperiph_basedir = '../../ST/StdPeriph'
cmsis_basedir = '../..'
for key, val in ARGLIST:
  if key == 'CMSIS_BASEDIR':      cmsis_basedir = val
  if key == 'STDPERIPH_BASEDIR':  stdperiph_basedir = val
stdperiph_basedir = env.Dir(stdperiph_basedir)
cmsis_basedir = env.Dir(cmsis_basedir)

#############################################################################
# The library
#############################################################################
for mcu_target in mcu_targets:
    options = { 
        'MCU_TARGET'        : mcu_target,
        'CMSIS_BASEDIR'     : cmsis_basedir,
        'STDPERIPH_BASEDIR' : stdperiph_basedir,
    }
    lib = env.SConscript( 'SConscript', 
        variant_dir='build/%s' % mcu_target.lower(),
        duplicate=0, exports=['env', 'options'] )

#############################################################################
# Unit tests
#############################################################################
for mcu_target in mcu_targets:
    options = { 
      'MCU_TARGET'        : mcu_target,
      'CMSIS_BASEDIR'     : cmsis_basedir,
      'STDPERIPH_BASEDIR' : stdperiph_basedir,
      'SCONSCRIPT_TARGET' : 'unit-test'
    }
    target = env.SConscript('SConscript', 
        variant_dir='build/test/unit/%s' % mcu_target.lower(),
        duplicate=0, exports=['env', 'options'] )
env.Ignore('build/test', 'build/test/unit')
env.Clean('build/test', 'build/test/unit')
env.Alias('unit-test', 'build/test/unit')

#############################################################################
# Doxygen documentation 
#############################################################################
# FIXME: on Windows we need doxycppfilter.bat or something as such.
doxygen_options = {
    'CPP_FILTER'            : '#bin/doxycppfilter',
    'FILTER_SOURCE_FILES'   : 'YES',
    'SRCDIR'                : '#src',
    'PROJECT_NAME'          : 'STM32++',
    'PROJECT_BRIEF'         : 'C++ utility library for STM32 firmware developers',
    'RECURSIVE'             : 'YES',
    'HIDE_UNDOC_CLASSES'    : 'YES',
    'HIDE_UNDOC_MEMBERS'    : 'YES',
    'WARN_IF_UNDOCUMENTED'  : 'NO',
}

env.SConscript('doc/SConscript',
    variant_dir = 'build/doc',
    exports     = {'env' : env, 'options' : doxygen_options}, 
    duplicate   = 0
)

env.Ignore('build', 'build/doc')
env.Clean('build', 'build/doc')
env.Alias('api-doc', 'build/doc')

##############################################################################
## Compile unit tests
##############################################################################
#env.SConscript('test/unit/SConscript',
#  variant_dir = 'build/test/unit',
#  exports     = {
#    'env'     : env,
#    'options' : {
#      'CPPPATH'   : ['#src']
#    }
#  },
#  duplicate   = 0
#)
#env.Ignore('build/test', 'build/test/unit')
#env.Clean('build/test', 'build/test/unit')
#env.Alias('unit-test', 'build/test/unit')

# Local Variables:
# # tab-width:4
# # indent-tabs-mode:nil
# # End:
# vim: set syntax=scons expandtab tabstop=4 shiftwidth=4:
