Hawkes
============

Small description TODO

Usage
-----

Hawkes must be compiled before use, see the *How to build* section.
There are no runtime library dependencies.

Use `./hawkes -h` to access the list of command line options with a small description.

TODO details or link to pdf doc

How to build
------------

A C++ compiler supporting C++17 is required:
- g++ >= 7.0
- clang++ >= 5.0
- for any other compiler, check that it supports the `-std=c++17` flag

Simple compilation:
- `make` will compile the program with the default C++ compiler of your distribution.
- `make CXX=<name_or_path_to_compiler_binary>` will use the specified compiler if the default is not valid.

Advanced compilation:
- `make CXX_FLAGS_EXTRA='-fopenmp'` to generate a multithreaded version of Hawkes using OpenMP. Only the convergence step is multithreaded. A special command line option `-n <n>` can be used to select the number of threads.
- `make CXX_FLAGS_EXTRA='-static'` to generate a self-contained compiled version of Hawkes which should work on any machine with the same architecture and operating system (not compatible with multithreading).

Developer corner
----------------

`make hawkes_debug` will compile the program in debug mode, with some assertions enabled and debug informations generated.
This can be useful to investigate a bug with gdb.

`make test` will compile and run a file with a lot of small tests of parts of the code.

`make format` will try to format the format the source code using the `clang-format` tool.

Hawkes uses two header-only libraries which are included in the current code:
- [fmtlib](http://fmtlib.net) formatting library to generate output text
- [doctest](https://github.com/onqtam/doctest) as a test framework for unit tests

License
-------

TODO