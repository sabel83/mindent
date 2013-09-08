#ifndef MINDENT_SYNTAX_NODE_HPP
#define MINDENT_SYNTAX_NODE_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <vector>
#include <map>
#include <cassert>

namespace mindent
{
  template <class TokenType>
  class syntax_node_list;

  template <class TokenType>
  class syntax_node
  {
  private:
    typedef
      std::vector<std::pair<syntax_node_list<TokenType>, TokenType> >
      args_t;

    typedef std::vector<TokenType> name_t;
  public:
    syntax_node() :
      _name(),
      _template(false),
      _template_begin(),
      _template_args(),
      _template_end()
    {}

    template <class NameIt>
    syntax_node(NameIt name_begin_, NameIt name_end_) :
      _name(name_begin_, name_end_),
      _template(false),
      _template_begin(),
      _template_args(),
      _template_end()
    {}

    template <class NameIt, class ArgIt>
    syntax_node(
      NameIt name_begin_,
      NameIt name_end_,
      const TokenType& template_begin_,
      ArgIt args_begin_,
      ArgIt args_end_,
      const TokenType& template_end_
    ) :
      _name(name_begin_, name_end_),
      _template(true),
      _template_begin(template_begin_),
      _template_args(args_begin_, args_end_),
      _template_end(template_end_)
    {}

    typedef typename args_t::const_iterator arg_iterator;
    typedef typename name_t::const_iterator name_iterator;

    name_iterator name_begin() const
    {
      return _name.begin();
    }

    name_iterator name_end() const
    {
      return _name.end();
    }
    
    bool is_template() const
    {
      return _template;
    }
    
    const TokenType& template_begin() const
    {
      assert(is_template());
      return _template_begin;
    }

    arg_iterator begin_args() const
    {
      assert(is_template());
      return _template_args.begin();
    }

    arg_iterator end_args() const
    {
      assert(is_template());
      return _template_args.end();
    }

    const TokenType& template_end() const
    {
      assert(is_template());
      return _template_end;
    }
  private:
    name_t _name;
    bool _template;
    TokenType _template_begin;
    args_t _template_args;
    TokenType _template_end;
  };
}

#endif

