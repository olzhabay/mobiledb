#pragma once

#include <FlexLexer.h>
#include "sql_parser.hh"


# ifndef YY_DECL
#  define YY_DECL sql::Parser::symbol_type                    \
     sql::Scanner::yylex(sql::Driver& driver)
# endif


namespace sql {
    class Scanner : public yyFlexLexer {
    public:

        Scanner();

        virtual ~Scanner();

        virtual Parser::symbol_type yylex(Driver& driver);

        void set_debug(bool b);
    };
}