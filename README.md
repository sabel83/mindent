# mIndent

[![Build Status](https://secure.travis-ci.org/sabel83/mindent.png?branch=master "Build Status")](http://travis-ci.org/sabel83/mindent)

mIndent is a header-only library for angle-bracket expression indentation. It is
based on the Boost.Wave library.

The documentation of the library can be found at
[http://abel.web.elte.hu/mindent](http://abel.web.elte.hu/mindent).

## Installing the library (Linux)

* Get the souce code: `git clone https://github.com/sabel83/mindent && cd mindent`
* Create the build directory: `mkdir bin && bin`
* Generate the Makefiles: `cmake ..`
* Build the tests: `make`
* Run the tests: `make test`
* Copy the headers: `make install` (You may need to run this as `root`)

## Generating the documentation

* Get the souce code: `git clone https://github.com/sabel83/mindent && cd mindent`
* Generate the documentation: `doxygen`

## License

mIndent is published under the
[Boost Software License](http://www.boost.org/LICENSE_1_0.txt).


