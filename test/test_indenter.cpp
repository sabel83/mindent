// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <mindent/display.hpp>
#include <mindent/parser.hpp>
#include <mindent/syntax_node.hpp>
#include <mindent/syntax_node_list.hpp>
#include <mindent/string_display.hpp>

#include "indented_tokens.hpp"

#include <boost/wave.hpp>
#include <boost/wave/cpplexer/cpp_lex_token.hpp>
#include <boost/wave/cpplexer/cpp_lex_iterator.hpp>

#include <boost/test/unit_test.hpp>

namespace
{
  typedef boost::wave::cpplexer::lex_token<> token_type;
  typedef token_type::position_type position_type;

  std::string indent(const std::string& s_)
  {
    const int width = 10;
    const int indent_step = 2;

    typedef boost::wave::cpplexer::lex_iterator<token_type> iterator_type;

    return
      mindent::display(
        mindent::parse_syntax_node_list(
          iterator_type(
            s_.begin(),
            s_.end(),
            token_type::position_type("<input>"),
            boost::wave::language_support(
              boost::wave::support_cpp
              | boost::wave::support_cpp0x
              | boost::wave::support_option_long_long
            )
          )
        ),
        width,
        indent_step,
        mindent::string_display()
      ).str();
  }
}

BOOST_AUTO_TEST_CASE(test_indenter)
{
  BOOST_CHECK_EQUAL("int", indent("int"));
  BOOST_CHECK_EQUAL("foo<int>", indent("foo<int>"));

  BOOST_CHECK_EQUAL(
    "longer_tha\n"
    "n_10<\n"
    "  int\n"
    ">",
    indent("longer_than_10<int>")
  );

  BOOST_CHECK_EQUAL("a::b", indent("a::b"));

  BOOST_CHECK_EQUAL(
    "longer_tha\n"
    "n_10\n"
    "::a\n"
    "::b",
    indent("longer_than_10::a::b")
  );

  BOOST_CHECK_EQUAL(
    "longer_tha\n"
    "n_10<\n"
    "  int\n"
    ">\n"
    "::a<char>\n"
    "::b<void>",
    indent("longer_than_10<int>::a<char>::b<void>")
  );

  BOOST_CHECK_EQUAL(
    "longer_tha\n"
    "n_10<\n"
    "  also_ver\n"
    "  y_long<\n"
    "    int\n"
    "  >\n"
    ">",
    indent("longer_than_10<also_very_long<int> >")
  );

  BOOST_CHECK_EQUAL("f<a, b>", indent("f<a, b>"));

  BOOST_CHECK_EQUAL(
    "f<\n"
    "  int,\n"
    "  char\n"
    ">",
    indent("f<int, char>")
  );

  BOOST_CHECK_EQUAL(
    "unsigned\n"
    "int",
    indent("unsigned int")
  );

  BOOST_CHECK_EQUAL(
    "f<\n"
    "  unsigned\n"
    "  int\n"
    ">",
    indent("f<unsigned int>")
  );

  BOOST_CHECK_EQUAL(
    "f<int>\n"
    "::g<double>",
    indent("f<int>::g<double>")
  );

  BOOST_CHECK_EQUAL("f<13>", indent("f<13>"));
}

BOOST_AUTO_TEST_CASE(test_comments)
{
  BOOST_CHECK_EQUAL(
    "/* hello *\n"
    "/",
    indent("/* hello */")
  );

  BOOST_CHECK_EQUAL(
    "f<\n"
    "  /* hello\n"
    "   */ int\n"
    ">",
    indent("f</* hello */ int>")
  );

  BOOST_CHECK_EQUAL("// hello\n", indent("// hello\n"));
  BOOST_CHECK_EQUAL(
    "f<\n"
    "  // hello\n"
    "    int\n"
    ">",
    indent(
      "f<// hello \n"
      "int>"
    )
  );

  BOOST_CHECK_EQUAL(
    "/* hello\n"
    " * world\n"
    " */",
    indent(
      "/* hello\n"
      " * world\n"
      " */"
    )
  );

  BOOST_CHECK_EQUAL(
    indented_tokens<token_type>(
      token_type(
        boost::wave::T_CCOMMENT,
        "/* hello\n"
        " * world\n"
        " */",
        position_type("<input>", 1, 1)
      )
    ),
    indented_tokens<token_type>(
      "/* hello\n"
      " * world\n"
      " */"
    )
  );
}

