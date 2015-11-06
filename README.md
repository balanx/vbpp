
what's new
==========

version 1.2.0

1. add feature : `{macro_name}
2. Source move to

    https://github.com/balanx/vbpp

2. binary available in

    http://pan.baidu.com/s/1gdJd4wN#path=%252Farts%252Fvbpp%2520-%2520Verilog%2520Preprocessor


----------

This is the public release of VBPP 1.1.0.  VBPP is a Verilog preprocessor. 
It has support for most Verilog preprocessing directives and additional
directives such as:

1.  Statement generator ('generate' command in VHDL).
2.  Expression evaluation.
3.  Mathematical functions: log2, ceil, floor, round, abs, etc.
4.  Conditionals: if, switch, etc.

This software is a re-release of Hemi Thaker's VPP program which, with
version 1.3, was released under a different license.  Therefore, this
release is based on version 1.2.  There are still some features which are
not implemented yet.  The following was changed in VPP version 1.2 to
produce VBPP 1.0.

1.  ANSI-fied function prototypes.
2.  ANSI-fied library calls.
3.  Code cleanup (removed unused variables and functions).
4.  Redone makefile.
5.  Re-organized files (names).
6.  Configure script (automatic generation of Makefile).
7.  Lots of bug fixes, see CHANGELOG for a list.

The following was updated for VBPP 1.1.0:

1.  C style preprocessing with the -E option.
2.  Generate a `line directive with the -L option.
3.  Support -D option to define a macro.
4.  Support the +incdir+ option for include search directories.
5.  Macro function definition and expansion.

The following was updated for VBPP 1.0.4:

Return non-zero when parser detects error.  This could cause older scripts
to fail if it looks at the exit value.

The following was updated for VBPP 1.0.3:

1.  Fixed stack overflow problem with parser.
2.  Source available in CVS server.  The server is hosted by

	http://geda.seul.org/

    Visit http://www.flex.com/~jching for more details.

The following was updated for VBPP 1.0.2:

1.  Fixed infinite loop bug in eval_stack.
2.  Cleaned up Makefile.
3.  Added more examples for testing.

The following was updated for VBPP 1.0.1:

1.  Runs correctly on systems that does not have rint.
2.  Implemented U* functions.

The following are things that was not changed in the distribution:

1.  Features
2.  Documentation (the original README is renamed to NOTES)
3.  License

VBPP was developed with the following tools:

GNU Make 3.75
GCC 2.95.3
Bison 1.28
Flex 2.5.4

Later versions of these tools should work.  There are no gaurantees for
earlier versions.  The distribution does not contain generated files, so
Bison and Flex are required to build from source.

To install, type the following command in your favorite shell and follow
the directions given. 

./configure

This release was done with the intention of continuing to produce a freely
available Verilog preprocessor.  If you have any comments or suggestions,
please email jching@flex.com.  Note, Hemi Thaker has not endorse this branch
of his VPP software.  Thus do not email him questions and/or requests.
Please direct all comments concerning VBPP to me only.

Jimen Ching
