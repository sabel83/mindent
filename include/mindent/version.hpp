#ifndef MINDENT_VERSION_HPP
#define MINDENT_VERSION_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

/**
 * @file version.hpp
 * @brief The version of the mIndent library
 */

#ifdef MINDENT_MAJOR
  #error MINDENT_MAJOR is already defined
#endif
#ifdef MINDENT_MINOR
  #error MINDENT_MINOR is already defined
#endif
#ifdef MINDENT_PATCH
  #error MINDENT_PATCH is already defined
#endif

/// The major version of the library
#define MINDENT_MAJOR_VERSION 0

/// The minor version of the library
#define MINDENT_MINOR_VERSION 1

/// The patch version of the library
#define MINDENT_PATCH_VERSION 0

#endif

