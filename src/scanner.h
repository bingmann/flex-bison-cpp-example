// $Id$

#ifndef EXAMPLE_LEXER_HH
#define EXAMPLE_LEXER_HH

// Flex expects the signature of yylex to be defined in the macro YY_DECL, and
// the C++ parser expects it to be declared. We can factor both as follows.

#ifndef YY_DECL

#define	YY_DECL						\
    example::Parser::token_type				\
    example::Scanner::lex(				\
	example::Parser::semantic_type* yylval,		\
	example::Parser::location_type* yylloc		\
    )
#endif

#ifndef __FLEX_LEXER_H
#define yyFlexLexer ExampleFlexLexer
#include <FlexLexer.h>
#undef yyFlexLexer
#endif

#include "parser.h"

namespace example {

class Scanner : public ExampleFlexLexer
{
public:
    Scanner(std::istream* arg_yyin = 0,
	    std::ostream* arg_yyout = 0);

    virtual ~Scanner();

    virtual Parser::token_type lex(
	Parser::semantic_type* yylval,
	Parser::location_type* yylloc
	);

    void set_debug(bool b);
};

} // namespace example

#endif // EXAMPLE_LEXER_HH
