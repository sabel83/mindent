#ifndef MINDENT_DISPLAY_HPP
#define MINDENT_DISPLAY_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mindent/impl/display.hpp>
#include <mindent/syntax_node_list.hpp>

namespace mindent
{
  template <class DisplayF, class TokenType>
  DisplayF display(
    const syntax_node_list<TokenType>& l_,
    int width_,
    int indent_step_,
    DisplayF show_
  )
  {
    return impl::display(l_, width_, indent_step_, 0, width_, show_);
  }
}

#endif

