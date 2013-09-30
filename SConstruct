#
# @COPYRIGHT@
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

EnsureSConsVersion(2,3)

flags = [
  '-Wall', 
  '-Wextra', 
  '-Werror',
  '-Wa,-adhlns=\'${TARGET}.lst\'', 
  '-fmessage-length=0',
  '-funsigned-bitfields'
]

env = Environment(tools =  ['default', 'doxygen', 'textfile'])
env.Append(CFLAGS   = flags)
env.Append(CXXFLAGS = ['-std=c++11', '-fno-exceptions', '-fno-rtti'] + flags)


#############################################################################
# Doxygen documentation 
#############################################################################
# FIXME: on Windows we need doxycppfilter.bat or something as such.
doxygen_options = {
  'CPP_FILTER'            : '#bin/doxycppfilter',
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

#############################################################################
# Compile unit tests
#############################################################################
env.SConscript('test/unit/SConscript',
  variant_dir = 'build/test/unit',
  exports     = {
    'env'     : env,
    'options' : {
      'CPPPATH'   : ['#src']
    }
  },
  duplicate   = 0
)
env.Ignore('build/test', 'build/test/unit')
env.Clean('build/test', 'build/test/unit')
env.Alias('unit-test', 'build/test/unit')
