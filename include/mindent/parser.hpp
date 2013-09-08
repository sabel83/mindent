#ifndef MINDENT_PARSER_HPP
#define MINDENT_PARSER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mindent/impl/parser.hpp>
#include <mindent/syntax_node_list.hpp>

#include <boost/wave.hpp>
#include <boost/wave/cpplexer/cpp_lex_token.hpp>
#include <boost/wave/cpplexer/cpp_lex_iterator.hpp>

#include <map>
#include <cassert>

namespace mindent
{
  template <class TokenType>
  syntax_node_list<TokenType>
  parse_syntax_node_list(boost::wave::cpplexer::lex_iterator<TokenType> begin_)
  {
    using std::pair;
    using boost::wave::cpplexer::lex_iterator;

    const pair<syntax_node_list<TokenType>, lex_iterator<TokenType> >
      p = impl::parse_syntax_node_list(begin_);

    assert(p.second == impl::end<TokenType>());

    return p.first;
  }
}

#endif

