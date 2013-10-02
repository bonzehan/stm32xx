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

.. <!--- vim: set expandtab tabstop=2 shiftwidth=2 syntax=rst: -->
