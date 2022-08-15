.. SPDX-License-Identifier: GPL-2.0

=========================
Run Tests with kunit_tool
=========================

.. _kunit-tool:

kunit_tool is a Python script (``tools/testing/kunit/kunit.py``)
that helps developers to **configure** and **build** the Linux kernel,
to then **execute** KUnit tests under QEMU or `UML <UML HowTo_>`_,
and **parse** the test results into an user friendly output.
The tool allows developers to **run** this whole pipeline with a single
command, but still provides each step to be called individually.

To give further detail:


- ``configure`` command generates the kernel ``.config`` from a
  ``.kunitconfig`` file (and any architecture-specific options).
  For some architectures, additional config options are specified in the
  ``qemu_config`` Python script
  (For example: ``tools/testing/kunit/qemu_configs/powerpc.py``).
  It parses both the existing ``.config`` and the ``.kunitconfig`` files
  and ensures that ``.config`` is a superset of ``.kunitconfig``.
  If this is not the case, it will combine the two and run
  ``make olddefconfig`` to regenerate the ``.config`` file. It then
  verifies that ``.config`` is now a superset. This checks if all
  Kconfig dependencies are correctly specified in ``.kunitconfig``.
  ``kunit_config.py`` includes the parsing Kconfigs code. The code which
  runs ``make olddefconfig`` is a part of ``kunit_kernel.py``. You can
  invoke this command via: ``./tools/testing/kunit/kunit.py config`` and
  generate a ``.config`` file.
- ``build`` runs ``make`` on the kernel tree with required options
  (depends on the architecture and some options, for example: build_dir)
  and reports any errors.
  To build a KUnit kernel from the current ``.config``, you can use the
  ``build`` argument: ``./tools/testing/kunit/kunit.py build``.
- ``exec`` command executes kernel results either directly (using
  User-mode Linux configuration), or via an emulator such
  as QEMU. It reads results from the log via standard
  output (stdout), and passes them to ``parse`` to be parsed.
  If you already have built a kernel with built-in KUnit tests,
  you can run the kernel and display the test results with the ``exec``
  argument: ``./tools/testing/kunit/kunit.py exec``.
- ``parse`` extracts the KTAP output from a kernel log, parses
  the test results, and prints a summary. For failed tests, any
  diagnostic output will be included.


If a kunitconfig is present at the root directory, all you have to do is:

.. code-block:: bash

	./tools/testing/kunit/kunit.py run

However, you most likely want to use it with the following options:

.. code-block:: bash

	./tools/testing/kunit/kunit.py run --timeout=30 --jobs=`nproc --all`

- ``--timeout`` sets a maximum amount of time to allow tests to run.
- ``--jobs`` sets the number of threads to use to build the kernel.

.. note::
	This command will work even without a .kunitconfig file: if no
	.kunitconfig is present, a default one will be used instead.

If you wish to use a different .kunitconfig file (such as one provided for
testing a particular subsystem), you can pass it as an option.

.. code-block:: bash

	./tools/testing/kunit/kunit.py run --kunitconfig=fs/ext4/.kunitconfig

For a list of all the flags supported by kunit_tool, you can run:

.. code-block:: bash

	./tools/testing/kunit/kunit.py run --help

We can either run KUnit tests using kunit_tool or can run tests
manually, and then use kunit_tool to parse the results. To run tests
manually, see: Documentation/dev-tools/kunit/run_manual.rst.
As long as we can build the kernel, we can run KUnit.

kunit_tool is a Python script which configures and builds a kernel, runs
tests, and formats the test results.

Run command:

.. code-block::

	./tools/testing/kunit/kunit.py run

We should see the following:

.. code-block::

	Generating .config...
	Building KUnit kernel...
	Starting KUnit kernel...

We may want to use the following options:

.. code-block::

	./tools/testing/kunit/kunit.py run --timeout=30 --jobs=`nproc --all`

- ``--timeout`` sets a maximum amount of time for tests to run.
- ``--jobs`` sets the number of threads to build the kernel.

kunit_tool will generate a ``.kunitconfig`` with a default
configuration, if no other ``.kunitconfig`` file exists
(in the build directory). In addition, it verifies that the
generated ``.config`` file contains the ``CONFIG`` options in the
``.kunitconfig``.
It is also possible to pass a separate ``.kunitconfig`` fragment to
kunit_tool. This is useful if we have several different groups of
tests we want to run independently, or if we want to use pre-defined
test configs for certain subsystems.

To use a different ``.kunitconfig`` file (such as one
provided to test a particular subsystem), pass it as an option:

.. code-block::

	./tools/testing/kunit/kunit.py run --kunitconfig=fs/ext4/.kunitconfig

To view kunit_tool flags (optional command-line arguments), run:

.. code-block::

	./tools/testing/kunit/kunit.py run --help

Create a  ``.kunitconfig`` File
===============================

It's just a defconfig that kunit_tool looks for in the build directory
(``.kunit`` by default).  kunit_tool uses it to generate a .config as you might
expect. In addition, it verifies that the generated .config contains the CONFIG
options in the .kunitconfig; the reason it does this is so that it is easy to
be sure that a CONFIG that enables a test actually ends up in the .config.

It's also possible to pass a separate .kunitconfig fragment to kunit_tool,
which is useful if you have several different groups of tests you wish
to run independently, or if you want to use pre-defined test configs for
certain subsystems.

If we want to run a specific set of tests (rather than those listed
in the KUnit ``defconfig``), we can provide Kconfig options in the
``.kunitconfig`` file. For default .kunitconfig, see:
https://git.kernel.org/pub/scm/linux/kernel/git/torvalds/linux.git/tree/tools/testing/kunit/configs/default.config.
A ``.kunitconfig`` is a ``minconfig`` (a .config
generated by running ``make savedefconfig``), used for running a
specific set of tests. This file contains the regular Kernel configs
with specific test targets. The ``.kunitconfig`` also
contains any other config options required by the tests (For example:
dependencies for features under tests, configs that enable/disable
certain code blocks, arch configs and so on).

To create a ``.kunitconfig``, using the KUnit ``defconfig``:

.. code-block::

	cd $PATH_TO_LINUX_REPO
	cp tools/testing/kunit/configs/default.config .kunit/.kunitconfig

We can then add any other Kconfig options. For example:

.. code-block::

	CONFIG_LIST_KUNIT_TEST=y

kunit_tool ensures that all config options in ``.kunitconfig`` are
set in the kernel ``.config`` before running the tests. It warns if we
have not included the options dependencies.

.. note:: Removing something from the ``.kunitconfig`` will
   not rebuild the ``.config file``. The configuration is only
   updated if the ``.kunitconfig`` is not a subset of ``.config``.
   This means that we can use other tools
   (For example: ``make menuconfig``) to adjust other config options.
   The build dir needs to be set for ``make menuconfig`` to
   work, therefore  by default use ``make O=.kunit menuconfig``.

Configure, Build, and Run Tests
===============================

It's also possible to run just parts of the KUnit build process independently,
which is useful if you want to make manual changes to part of the process.

A .config can be generated from a .kunitconfig by using the ``config`` argument
when running kunit_tool:

.. code-block:: bash

	./tools/testing/kunit/kunit.py config

Similarly, if you just want to build a KUnit kernel from the current .config,
you can use the ``build`` argument:

.. code-block:: bash

	./tools/testing/kunit/kunit.py build

And, if you already have a built UML kernel with built-in KUnit tests, you can
run the kernel and display the test results with the ``exec`` argument:

.. code-block:: bash

	./tools/testing/kunit/kunit.py exec

The ``run`` command which is discussed above is equivalent to running all three
of these in sequence.

All of these commands accept a number of optional command-line arguments. The
``--help`` flag will give a complete list of these, or keep reading this page
for a guide to some of the more

If we want to make manual changes to the KUnit build process, we
can run part of the KUnit build process independently.
When running kunit_tool, from a ``.kunitconfig``, we can generate a
``.config`` by using the ``config`` argument:

.. code-block::

	./tools/testing/kunit/kunit.py config

To build a KUnit kernel from the current ``.config``, we can use the
``build`` argument:

.. code-block::

	./tools/testing/kunit/kunit.py build
kunit_tool - execute
===================

kunit_tool addresses the problem of being able to run tests without needing a virtual machine or actual hardware with User Mode Linux. 
User Mode Linux is a Linux architecture, like ARM or x86; however, unlike other architectures it compiles the kernel as a standalone Linux executable that can be run like any other program directly inside of a host operating system. To be clear, it does not require any virtualization support: it is just a regular program.

If we already have built UML kernel with built-in KUnit tests, we
can run the kernel, and display the test results with the ``exec``
argument:

.. code-block::

	./tools/testing/kunit/kunit.py exec

The ``run`` command discussed in section: **Run Tests with kunit_tool**,
is equivalent to running the above three commands in sequence.

Parse Test Results
==================

KUnit tests output their results in TAP (Test Anything Protocol) format.
kunit_tool will, when running tests, parse this output and print a summary
which is much more pleasant to read. If you wish to look at the raw test
results in TAP format, you can pass the ``--raw_output`` argument.

.. code-block:: bash

	./tools/testing/kunit/kunit.py run --raw_output

The raw output from test runs may contain other, non-KUnit kernel log
lines. You can see just KUnit output with ``--raw_output=kunit``:

.. code-block:: bash

	./tools/testing/kunit/kunit.py run --raw_output=kunit

If you have KUnit results in their raw TAP format, you can parse them and print
the human-readable summary with the ``parse`` command for kunit_tool. This
accepts a filename for an argument, or will read from standard input.

.. code-block:: bash

	# Reading from a file
	./tools/testing/kunit/kunit.py parse /var/log/dmesg
	# Reading from stdin
	dmesg | ./tools/testing/kunit/kunit.py parse

This is very useful if you wish to run tests in a configuration not supported
by kunit_tool (such as on real hardware, or an unsupported architecture).


KUnit tests output displays results in TAP (Test Anything Protocol)
format. When running tests, kunit_tool parses this output and prints
a summary. To see the raw test results in TAP format, we can pass the
``--raw_output`` argument:

.. code-block::

	./tools/testing/kunit/kunit.py run --raw_output

If we have KUnit results in the raw TAP format, we can parse them and
print the human-readable summary with the ``parse`` command for
kunit_tool. This accepts a filename for an argument, or will read from
standard input.

.. code-block:: bash

	# Reading from a file
	./tools/testing/kunit/kunit.py parse /var/log/dmesg
	# Reading from stdin
	dmesg | ./tools/testing/kunit/kunit.py parse

Run Selected Test Suites
========================

It's possible to run only a subset of the tests built into a kernel by passing
a filter to the ``exec`` or ``run`` commands. For example, if you only wanted
to run KUnit resource tests, you could use:

.. code-block:: bash

	./tools/testing/kunit/kunit.py run 'kunit-resource*'

This uses the standard glob format for wildcards.

By passing a bash style glob filter to the ``exec`` or ``run``
commands, we can run a subset of the tests built into a kernel . For
example: if we only want to run KUnit resource tests, use:

.. code-block::

	./tools/testing/kunit/kunit.py run 'kunit-resource*'

This uses the standard glob format with wildcard characters.

.. _kunit-on-qemu:

Run Tests on qemu
=================

kunit_tool supports running tests on QEMU as well as via UML (as mentioned
elsewhere). The default way of running tests on QEMU requires two flags:

``--arch``
	Selects a collection of configs (Kconfig as well as QEMU configs
	options, etc) that allow KUnit tests to be run on the specified
	architecture in a minimal way; this is usually not much slower than
	using UML. The architecture argument is the same as the name of the
	option passed to the ``ARCH`` variable used by Kbuild. Not all
	architectures are currently supported by this flag, but can be handled
	by the ``--qemu_config`` discussed later. If ``um`` is passed (or this
	this flag is ignored) the tests will run via UML. Non-UML architectures,
	e.g. i386, x86_64, arm, um, etc. Non-UML run on QEMU.

``--cross_compile``
	Specifies the use of a toolchain by Kbuild. The argument passed here is
	the same passed to the ``CROSS_COMPILE`` variable used by Kbuild. As a
	reminder this will be the prefix for the toolchain binaries such as gcc
	for example ``sparc64-linux-gnu-`` if you have the sparc toolchain
	installed on your system, or
	``$HOME/toolchains/microblaze/gcc-9.2.0-nolibc/microblaze-linux/bin/microblaze-linux-``
	if you have downloaded the microblaze toolchain from the 0-day website
	to a directory in your home directory called ``toolchains``.

In many cases it is likely that you may want to run an architecture which is
not supported by the ``--arch`` flag, or you may want to just run KUnit tests
on QEMU using a non-default configuration. For this use case, you can write
your own QemuConfig. These QemuConfigs are written in Python. They must have an
import line ``from ..qemu_config import QemuArchParams`` at the top of the file
and the file must contain a variable called ``QEMU_ARCH`` that has an instance
of ``QemuArchParams`` assigned to it. An example can be seen in
``tools/testing/kunit/qemu_configs/x86_64.py``.

Once you have a QemuConfig you can pass it into kunit_tool using the
``--qemu_config`` flag; when used this flag replaces the ``--arch`` flag. If we
were to do this with the ``x86_64.py`` example from above, the invocation would
look something like this:

.. code-block:: bash

	./tools/testing/kunit/kunit.py run \
		--timeout=60 \
		--jobs=12 \
		--qemu_config=./tools/testing/kunit/qemu_configs/x86_64.py

kunit_tool supports running tests on  qemu as well as
via UML. To run tests on qemu, by default it requires two flags:

- ``--arch``: Selects a configs collection (Kconfig, qemu config options
  and so on), that allow KUnit tests to be run on the specified
  architecture in a minimal way. The architecture argument is same as
  the option name passed to the ``ARCH`` variable used by Kbuild.
  Not all architectures currently support this flag, but we can use
  ``--qemu_config`` to handle it. If ``um`` is passed (or this flag
  is ignored), the tests will run via UML. Non-UML architectures,
  for example: i386, x86_64, arm and so on; run on qemu.

- ``--cross_compile``: Specifies the Kbuild toolchain. It passes the
  same argument as passed to the ``CROSS_COMPILE`` variable used by
  Kbuild. As a reminder, this will be the prefix for the toolchain
  binaries such as GCC. For example:

  - ``sparc64-linux-gnu`` if we have the sparc toolchain installed on
    our system.

  - ``$HOME/toolchains/microblaze/gcc-9.2.0-nolibc/microblaze-linux/bin/microblaze-linux``
    if we have downloaded the microblaze toolchain from the 0-day
    website to a directory in our home directory called toolchains.

This means that for most architectures, running under qemu is as simple as:

.. code-block:: bash

	./tools/testing/kunit/kunit.py run --arch=x86_64

When cross-compiling, we'll likely need to specify a different toolchain, for
example:

.. code-block:: bash

	./tools/testing/kunit/kunit.py run \
		--arch=s390 \
		--cross_compile=s390x-linux-gnu-

If we want to run KUnit tests on an architecture not supported by
the ``--arch`` flag, or want to run KUnit tests on qemu using a
non-default configuration; then we can write our own``QemuConfig``.
These ``QemuConfigs`` are written in Python. They have an import line
``from..qemu_config import QemuArchParams`` at the top of the file.
The file must contain a variable called ``QEMU_ARCH`` that has an
instance of ``QemuArchParams`` assigned to it. See example in:
``tools/testing/kunit/qemu_configs/x86_64.py``.

Once we have a ``QemuConfig``, we can pass it into kunit_tool,
using the ``--qemu_config`` flag. When used, this flag replaces the
``--arch`` flag. For example: using
``tools/testing/kunit/qemu_configs/x86_64.py``, the invocation appear
as

.. code-block:: bash

	./tools/testing/kunit/kunit.py run \
		--timeout=60 \
		--jobs=12 \
		--qemu_config=./tools/testing/kunit/qemu_configs/x86_64.py

Command-Line Arguments
======================

kunit_tool has a number of other command-line arguments which can be useful
when adapting it to fit your environment or needs.

Some of the more useful ones are:

``--help``
	Lists all of the available options. Note that different commands
	(``config``, ``build``, ``run``, etc) will have different supported
	options. Place ``--help`` before the command to list common options,
	and after the command for options specific to that command.

``--build_dir``
	Specifies the build directory that kunit_tool will use. This is where
	the .kunitconfig file is located, as well as where the .config and
	compiled kernel will be placed. Defaults to ``.kunit``.

``--make_options``
	Specifies additional options to pass to ``make`` when compiling a
	kernel (with the ``build`` or ``run`` commands). For example, to enable
	compiler warnings, you can pass ``--make_options W=1``.

``--alltests``
        Builds a UML kernel with all config options enabled using ``make
        allyesconfig``. This allows you to run as many tests as is possible,
        but is very slow and prone to breakage as new options are added or
        modified. In most cases, enabling all tests which have satisfied
        dependencies by adding ``CONFIG_KUNIT_ALL_TESTS=1`` to your
        .kunitconfig is preferable.

There are several other options (and new ones are often added), so do check
``--help`` if you're looking for something not mentioned here.

kunit_tool has a number of other command-line arguments which can
be useful for our test environment. Below are the most commonly used
command line arguments:

- ``--help``: Lists all available options. To list common options,
  place ``--help`` before the command. To list options specific to that
  command, place ``--help`` after the command.

  .. note:: Different commands (``config``, ``build``, ``run``, etc)
            have different supported options.
- ``--build_dir``: Specifies kunit_tool build directory. It includes
  the ``.kunitconfig``, ``.config`` files and compiled kernel.

- ``--make_options``: Specifies additional options to pass to make, when
  compiling a kernel (using ``build`` or ``run`` commands). For example:
  to enable compiler warnings, we can pass ``--make_options W=1``.

- ``--alltests``: Builds a UML kernel with all config options enabled
  using ``make allyesconfig``. This allows us to run as many tests as
  possible.

  .. note:: It is slow and prone to breakage as new options are
            added or modified. Instead, enable all tests
            which have satisfied dependencies by adding
            ``CONFIG_KUNIT_ALL_TESTS=y`` to your ``.kunitconfig``.

- ``--kunitconfig``: Specifies the path or the directory of the ``.kunitconfig``
  file. For example:

  - ``lib/kunit/.kunitconfig`` can be the path of the file.

  - ``lib/kunit`` can be the directory in which the file is located.

  This file is used to build and run with a predefined set of tests
  and their dependencies. For example, to run tests for a given subsystem.

- ``--kconfig_add``: Specifies additional configuration options to be
  appended to the ``.kunitconfig`` file. For example:

  .. code-block::

	./tools/testing/kunit/kunit.py run --kconfig_add CONFIG_KASAN=y

- ``--arch``: Runs tests on the specified architecture. The architecture
  argument is same as the Kbuild ARCH environment variable.
  For example, i386, x86_64, arm, um, etc. Non-UML architectures run on qemu.
  Default is `um`.

- ``--cross_compile``: Specifies the Kbuild toolchain. It passes the
  same argument as passed to the ``CROSS_COMPILE`` variable used by
  Kbuild. This will be the prefix for the toolchain
  binaries such as GCC. For example:

  - ``sparc64-linux-gnu-`` if we have the sparc toolchain installed on
    our system.

  - ``$HOME/toolchains/microblaze/gcc-9.2.0-nolibc/microblaze-linux/bin/microblaze-linux``
    if we have downloaded the microblaze toolchain from the 0-day
    website to a specified path in our home directory called toolchains.

- ``--qemu_config``: Specifies the path to a file containing a
  custom qemu architecture definition. This should be a python file
  containing a `QemuArchParams` object.

- ``--qemu_args``: Specifies additional qemu arguments, for example, ``-smp 8``.

- ``--jobs``: Specifies the number of jobs (commands) to run simultaneously.
  By default, this is set to the number of cores on your system.

- ``--timeout``: Specifies the maximum number of seconds allowed for all tests to run.
  This does not include the time taken to build the tests.

- ``--kernel_args``: Specifies additional kernel command-line arguments. May be repeated.

- ``--run_isolated``: If set, boots the kernel for each individual suite/test.
  This is useful for debugging a non-hermetic test, one that
  might pass/fail based on what ran before it.

- ``--raw_output``: If set, generates unformatted output from kernel. Possible options are:

   - ``all``: To view the full kernel output, use ``--raw_output=all``.

   - ``kunit``: This is the default option and filters to KUnit output. Use ``--raw_output`` or ``--raw_output=kunit``.

- ``--json``: If set, stores the test results in a JSON format and prints to `stdout` or
  saves to a file if a filename is specified.
