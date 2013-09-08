#ifndef MINDENT_STREAM_DISPLAY_HPP
#define MINDENT_STREAM_DISPLAY_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>

namespace mindent
{
  class stream_display
  {
  public:
    explicit stream_display(std::ostream& o_) :
      _o(&o_)
    {}

    template <class TokenType>
    void operator()(const TokenType& t_)
    {
      *_o << t_.get_value();
    }
  private:
    std::ostream* _o;
  };
}

#endif

