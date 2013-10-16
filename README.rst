STM32++
=======

C++ utility library for STM32 software developers.

Documentation
-------------

Generating API Documentation
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block::

    scons api-doc

Testing
-------

Generating Unit Test Runners
^^^^^^^^^^^^^^^^^^^^^^^^^^^^

.. code-block::

    scons unit-test STDPERIPH_BASEDIR=<path> CMSIS_BASEDIR=<path>

The `STDPERIPH_BASEDIR` and `CMSIS_BASEDIR` are optional if this source tree is
embedded within the cortex-libs_ skeleton. If not, you must point out exactly
where are the stm32-stdperiph_ and cortex-cmsis_ repositories located.

Running Unit Tests
^^^^^^^^^^^^^^^^^^

List all the generated test runners::

    find build/test/unit -name run_tests

pickup one and run, for example::

    ./build/test/unit/STM32F10X_MD/run_tests

Currently the unit tests are compiled and run on host only (not on target).

.. _cortex-libs: https://github.com/ptomulik/cortex-libs
.. _stm32-stdperiph: https://github.com/ptomulik/stm32-stdperiph
.. _cortex-cmsis: https://github.com/ptomulik/cortex-cmsis

LICENSE
-------

NOTE
^^^^

Some parts of the code are copyrighted by others. These are:

- Google testing framework under ``test/unit/gtest/``

For the rest of the code, the following license apply.

LICENSE
^^^^^^^

Copyright (c) 2013 by Pawel Tomulik <ptomulik@meil.pw.edu.pl>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE
.. <!--- vim: set expandtab tabstop=2 shiftwidth=2 syntax=rst: -->
