#ifndef MINDENT_SYNTAX_NODE_LIST_HPP
#define MINDENT_SYNTAX_NODE_LIST_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <vector>
#include <map>

namespace mindent
{
  template <class TokenType>
  class syntax_node;
  
  template <class TokenType>
  class syntax_node_list
  {
  private:
    typedef std::vector<std::pair<syntax_node<TokenType>, TokenType> > nodes_t;
  public:
    syntax_node_list() {}

    template <class It>
    syntax_node_list(It begin_, It end_) : _nodes(begin_, end_) {}

    typedef typename nodes_t::const_iterator iterator;
    typedef typename nodes_t::const_iterator const_iterator;

    iterator begin() const { return _nodes.begin(); }
    iterator end() const { return _nodes.end(); }
  private:
    nodes_t _nodes;
  };
}

#endif

