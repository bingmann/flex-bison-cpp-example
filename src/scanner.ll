/* $Id$ -*- mode: c++ -*- */

%{ /*** C/C++ Declarations ***/

#include <string>

#include "parser.h"
#include "scanner.h"

/* import the parser's token type into a local typedef */
typedef example::Parser::token token;
typedef example::Parser::token_type token_type;

/* Work around an incompatibility in flex (at least versions 2.5.31 through
 * 2.5.33): it generates code that does not conform to C89.  See Debian bug
 * 333231 <http://bugs.debian.org/cgi-bin/bugreport.cgi?bug=333231>.  */
#undef yywrap
#define yywrap()	1

/* By default yylex returns int, we use token_type. Unfortunately yyterminate
 * by default returns 0, which is not of token_type. */
#define yyterminate() return token::END

%}

/*** Flex Declarations and Options ***/

/* enable c++ scanner class generation */
%option c++

/* change the name of the scanner class */
%option prefix="Example"

/* the manual says "somewhat more optimized" */
%option batch

/* enable scanner to generate debug output. disable this for release
 * versions. */
%option debug

/* no support for include files is planned */
%option noyywrap nounput 

/* enables the use of start condition stacks */
%option stack

/* The following paragraph suffices to track locations accurately. Each time
 * yylex is invoked, the begin position is moved onto the end position. */
%{
#define YY_USER_ACTION  yylloc->columns(yyleng);
%}

%% /*** Regular Expressions Part ***/

%{
    // reset location
    yylloc->step();

    // variable for quoted strings
    std::string	quotedstring;
%}

[0-9]+ {
    yylval->integerVal = atoi(yytext);
    return token::INTEGER;
}

[0-9]+"."[0-9]* {
    yylval->doubleVal = atof(yytext);
    return token::DOUBLE;
}

[A-Za-z][A-Za-z0-9_,.-]* {
    yylval->stringVal = new std::string(yytext, yyleng);
    return token::STRING;
}

 /* skip perl-style comments */
#[^\n]*\n {
}

 /* gobble up white-spaces */
[ \t\r]+ {
    yylloc->step();
}

 /* but identify end of lines */
\n {
    yylloc->lines(yyleng); yylloc->step();
    return token::EOL;
}

 /* pass all other characters up to bison */
. {
    return static_cast<token_type>(*yytext);
}

%% /*** Additional Code ***/

namespace example {

Scanner::Scanner(std::istream* in,
		 std::ostream* out)
    : ExampleFlexLexer(in, out)
{
}

Scanner::~Scanner()
{
}

void Scanner::set_debug(bool b)
{
    yy_flex_debug = b;
}

}

#ifdef yylex
#undef yylex
#endif

int ExampleFlexLexer::yylex()
{
    std::cerr << "in ExampleFlexLexer::yylex() !" << std::endl;
    return 0;
}
