# CXX Tool

The tool aims to address a major problem of C++ tooling - complexity. Inspired
by the go tool it should provide similar commands:

* `build` - builds a normal binary with minimal optimization and sanitizers
  enabled. It should be used for development.
* `build --release` - builds a release binary with maximum optimization and
  without sanitizers.
* `build --debug` - builds a debug binary with sanitizers and debug information
  enabled.
* `test` - builds and runs tests.
* `doc` - builds documentation out of source (e.g. using *Doxygen*).

The tool should provide reasonable and minimal defaults for each command and
enable further configuration through environment variables. Developers should
use *Makefiles* to set these variables. The tool will provide `init` command
that generates a default minimal *Makefile*.

When possible, [standard make variables](https://www.gnu.org/software/make/manual/make.html#Implicit-Variables)
should be used to configure the build.

The `build` command builds a target out of source files present in the working
directory and its subdirectories. Functionally, it should behave similarly to a
gcc compiler called like this:

    c++ $(find . -iname '*.cpp') 

But internally, it should use caching and concurrency to ensure quick build
iterations, at least for non-release builds.

The `build` command builds by default an *executable*; to build a library, a
corresponding environment variable controlling the target type should be set.

The tool will support C++ modules out of the box and without additional
configuration. It should also be the preferred way of structuring the C++ source
code when using this tool.

