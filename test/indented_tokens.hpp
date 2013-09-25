#ifndef MINDENT_INDENTED_TOKENS_HPP
#define MINDENT_INDENTED_TOKENS_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mindent/display.hpp>
#include <mindent/parser.hpp>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/repetition/repeat.hpp>
#include <boost/preprocessor/repetition/enum_params.hpp>

#include <boost/operators.hpp>

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

template <class TokenType>
class indented_tokens : boost::equality_comparable<indented_tokens<TokenType> >
{
private:
  typedef std::vector<TokenType> container_t;
public:
  explicit indented_tokens(const std::string& s_)
  {
    const int width = 10;
    const int indent_step = 2;

    typedef boost::wave::cpplexer::lex_iterator<TokenType> iterator_type;

    mindent::display(
      mindent::parse_syntax_node_list(
        iterator_type(
          s_.begin(),
          s_.end(),
          typename TokenType::position_type("<input>"),
          boost::wave::language_support(
            boost::wave::support_cpp 
            | boost::wave::support_cpp0x
            | boost::wave::support_option_long_long
          )
        )
      ),
      width,
      indent_step,
      display(_container)
    );
  }

  #ifdef MINDENT_ADD_PARAM
    #error MINDENT_ADD_PARAM already defined
  #endif
  #define MINDENT_ADD_PARAM(z, n, unused) \
    _container.push_back(BOOST_PP_CAT(t, n));

  #ifdef MINDENT_INDENTED_TOKEN
    #error MINDENT_INDENTED_TOKEN already defined
  #endif
  #define MINDENT_INDENTED_TOKEN(z, n, unused) \
    indented_tokens(BOOST_PP_ENUM_PARAMS(n, const TokenType& t)) \
    { \
      BOOST_PP_REPEAT(n, MINDENT_ADD_PARAM, ~) \
    }

  BOOST_PP_REPEAT(10, MINDENT_INDENTED_TOKEN, ~)

  #undef MINDENT_INDENTED_TOKEN
  #undef MINDENT_ADD_PARAM

  bool operator==(const indented_tokens& t_) const
  {
    return
      _container.size() == t_._container.size() &&
      std::equal(_container.begin(), _container.end(), t_._container.begin());
  }

  typedef typename container_t::const_iterator iterator;

  iterator begin() const
  {
    return _container.begin();
  }

  iterator end() const
  {
    return _container.end();
  }
private:
  class display
  {
  public:
    explicit display(container_t& container_) : _container(&container_) {}

    void operator()(const TokenType& t_)
    {
      _container->push_back(t_);
    }
  private:
    container_t* _container;
  };

  container_t _container;
};

template <class TokenType>
std::ostream& operator<<(
  std::ostream& out_,
  const indented_tokens<TokenType>& t_
)
{
  out_ << "[";
  bool first = true;
  for (
    typename indented_tokens<TokenType>::iterator i = t_.begin(), e = t_.end();
    i != e;
    ++i
  )
  {
    const typename TokenType::position_type pos = i->get_position();
    out_
      << (first ? "\n" : ",\n")
      << boost::wave::get_token_name(*i) << "(" << i->get_value() << ") @ "
      << pos.get_file() << ":" << pos.get_line() << ":" << pos.get_column();
    first = false;
  }
  return out_ << "\n]";
}

#endif

