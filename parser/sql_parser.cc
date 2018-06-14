// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.


// First part of user declarations.

#line 37 "sql_parser.cc" // lalr1.cc:404

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

#include "sql_parser.hh"

// User implementation prologue.

#line 51 "sql_parser.cc" // lalr1.cc:412
// Unqualified %code blocks.
#line 50 "sql_parser.y" // lalr1.cc:413


#include "sql_parser.hh"
#include "sql_scanner.hpp"

using namespace std;
#define yylex driver.get_scanner()->yylex


#line 63 "sql_parser.cc" // lalr1.cc:413


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (/*CONSTCOND*/ false)
# endif


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << std::endl;                  \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yystack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE(Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void>(0)
# define YY_STACK_PRINT()                static_cast<void>(0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 6 "sql_parser.y" // lalr1.cc:479
namespace sql {
#line 149 "sql_parser.cc" // lalr1.cc:479

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr = "";
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              // Fall through.
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }


  /// Build a parser object.
  Parser::Parser (Driver &driver_yyarg)
    :
#if YYDEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
#endif
      driver (driver_yyarg)
  {}

  Parser::~Parser ()
  {}


  /*---------------.
  | Symbol types.  |
  `---------------*/



  // by_state.
  inline
  Parser::by_state::by_state ()
    : state (empty_state)
  {}

  inline
  Parser::by_state::by_state (const by_state& other)
    : state (other.state)
  {}

  inline
  void
  Parser::by_state::clear ()
  {
    state = empty_state;
  }

  inline
  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  inline
  Parser::by_state::by_state (state_type s)
    : state (s)
  {}

  inline
  Parser::symbol_number_type
  Parser::by_state::type_get () const
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[state];
  }

  inline
  Parser::stack_symbol_type::stack_symbol_type ()
  {}


  inline
  Parser::stack_symbol_type::stack_symbol_type (state_type s, symbol_type& that)
    : super_type (s, that.location)
  {
      switch (that.type_get ())
    {
      case 7: // BOOL
      case 363: // opt_if_not_exists
        value.move< bool > (that.value);
        break;

      case 8: // APPROXNUM
        value.move< double > (that.value);
        break;

      case 6: // INTNUM
      case 9: // NOTEQUALS
      case 10: // LESSEQ
      case 11: // GREATEREQ
      case 369: // opt_limit
        value.move< int > (that.value);
        break;

      case 348: // select_opts
      case 351: // join_opts
        value.move< sql::SelectStmt::Type > (that.value);
        break;

      case 344: // expr_pair
        value.move< std::pair<std::string, std::string> > (that.value);
        break;

      case 355: // create_stmt
        value.move< std::shared_ptr<sql::CreateStmt> > (that.value);
        break;

      case 352: // delete_stmt
        value.move< std::shared_ptr<sql::DeleteStmt> > (that.value);
        break;

      case 358: // drop_stmt
        value.move< std::shared_ptr<sql::DropStmt> > (that.value);
        break;

      case 353: // insert_stmt
        value.move< std::shared_ptr<sql::InsertStmt> > (that.value);
        break;

      case 347: // select_stmt
      case 349: // join_table
        value.move< std::shared_ptr<sql::SelectStmt> > (that.value);
        break;

      case 346: // stmt
        value.move< std::shared_ptr<sql::Statement> > (that.value);
        break;

      case 371: // table_factor
        value.move< std::shared_ptr<sql::Table> > (that.value);
        break;

      case 354: // update_stmt
        value.move< std::shared_ptr<sql::UpdateStmt> > (that.value);
        break;

      case 3: // STRING
      case 4: // USERVAR
      case 5: // NAME
      case 22: // COMPARISON
      case 23: // SHIFT
      case 341: // expr_data
      case 360: // column_atts
      case 361: // data_type
      case 362: // opt_as_alias
        value.move< std::string > (that.value);
        break;

      case 342: // expr
      case 357: // create_definition
        value.move< std::tuple<std::string, std::string, std::string> > (that.value);
        break;

      case 345: // pair_list
      case 365: // opt_ondupupdate
        value.move< std::vector<std::pair<std::string, std::string>> > (that.value);
        break;

      case 340: // stmt_list
        value.move< std::vector<std::shared_ptr<sql::Statement>> > (that.value);
        break;

      case 370: // table_references
        value.move< std::vector<std::shared_ptr<sql::Table>> > (that.value);
        break;

      case 359: // string_list
      case 367: // opt_groupby
      case 368: // opt_orderby
        value.move< std::vector<std::string> > (that.value);
        break;

      case 343: // expr_list
      case 350: // join_condition
      case 356: // create_col_list
      case 366: // opt_where
        value.move< std::vector<std::tuple<std::string, std::string, std::string>> > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

  inline
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
      switch (that.type_get ())
    {
      case 7: // BOOL
      case 363: // opt_if_not_exists
        value.copy< bool > (that.value);
        break;

      case 8: // APPROXNUM
        value.copy< double > (that.value);
        break;

      case 6: // INTNUM
      case 9: // NOTEQUALS
      case 10: // LESSEQ
      case 11: // GREATEREQ
      case 369: // opt_limit
        value.copy< int > (that.value);
        break;

      case 348: // select_opts
      case 351: // join_opts
        value.copy< sql::SelectStmt::Type > (that.value);
        break;

      case 344: // expr_pair
        value.copy< std::pair<std::string, std::string> > (that.value);
        break;

      case 355: // create_stmt
        value.copy< std::shared_ptr<sql::CreateStmt> > (that.value);
        break;

      case 352: // delete_stmt
        value.copy< std::shared_ptr<sql::DeleteStmt> > (that.value);
        break;

      case 358: // drop_stmt
        value.copy< std::shared_ptr<sql::DropStmt> > (that.value);
        break;

      case 353: // insert_stmt
        value.copy< std::shared_ptr<sql::InsertStmt> > (that.value);
        break;

      case 347: // select_stmt
      case 349: // join_table
        value.copy< std::shared_ptr<sql::SelectStmt> > (that.value);
        break;

      case 346: // stmt
        value.copy< std::shared_ptr<sql::Statement> > (that.value);
        break;

      case 371: // table_factor
        value.copy< std::shared_ptr<sql::Table> > (that.value);
        break;

      case 354: // update_stmt
        value.copy< std::shared_ptr<sql::UpdateStmt> > (that.value);
        break;

      case 3: // STRING
      case 4: // USERVAR
      case 5: // NAME
      case 22: // COMPARISON
      case 23: // SHIFT
      case 341: // expr_data
      case 360: // column_atts
      case 361: // data_type
      case 362: // opt_as_alias
        value.copy< std::string > (that.value);
        break;

      case 342: // expr
      case 357: // create_definition
        value.copy< std::tuple<std::string, std::string, std::string> > (that.value);
        break;

      case 345: // pair_list
      case 365: // opt_ondupupdate
        value.copy< std::vector<std::pair<std::string, std::string>> > (that.value);
        break;

      case 340: // stmt_list
        value.copy< std::vector<std::shared_ptr<sql::Statement>> > (that.value);
        break;

      case 370: // table_references
        value.copy< std::vector<std::shared_ptr<sql::Table>> > (that.value);
        break;

      case 359: // string_list
      case 367: // opt_groupby
      case 368: // opt_orderby
        value.copy< std::vector<std::string> > (that.value);
        break;

      case 343: // expr_list
      case 350: // join_condition
      case 356: // create_col_list
      case 366: // opt_where
        value.copy< std::vector<std::tuple<std::string, std::string, std::string>> > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }


  template <typename Base>
  inline
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    YYUSE (yytype);
    yyo << ')';
  }
#endif

  inline
  void
  Parser::yypush_ (const char* m, state_type s, symbol_type& sym)
  {
    stack_symbol_type t (s, sym);
    yypush_ (m, t);
  }

  inline
  void
  Parser::yypush_ (const char* m, stack_symbol_type& s)
  {
    if (m)
      YY_SYMBOL_PRINT (m, s);
    yystack_.push (s);
  }

  inline
  void
  Parser::yypop_ (unsigned int n)
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  inline Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
  }

  inline bool
  Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  inline bool
  Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::parse ()
  {
    // State.
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

    // FIXME: This shoud be completely indented.  It is not yet to
    // avoid gratuitous conflicts when merging into the master branch.
    try
      {
    YYCDEBUG << "Starting parse" << std::endl;


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, yyla);

    // A new symbol was pushed on the stack.
  yynewstate:
    YYCDEBUG << "Entering state " << yystack_[0].state << std::endl;

    // Accept?
    if (yystack_[0].state == yyfinal_)
      goto yyacceptlab;

    goto yybackup;

    // Backup.
  yybackup:

    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token: ";
        try
          {
            symbol_type yylookahead (yylex (driver));
            yyla.move (yylookahead);
          }
        catch (const syntax_error& yyexc)
          {
            error (yyexc);
            goto yyerrlab1;
          }
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
      goto yydefault;

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", yyn, yyla);
    goto yynewstate;

  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;

  /*-----------------------------.
  | yyreduce -- Do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_(yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
        switch (yyr1_[yyn])
    {
      case 7: // BOOL
      case 363: // opt_if_not_exists
        yylhs.value.build< bool > ();
        break;

      case 8: // APPROXNUM
        yylhs.value.build< double > ();
        break;

      case 6: // INTNUM
      case 9: // NOTEQUALS
      case 10: // LESSEQ
      case 11: // GREATEREQ
      case 369: // opt_limit
        yylhs.value.build< int > ();
        break;

      case 348: // select_opts
      case 351: // join_opts
        yylhs.value.build< sql::SelectStmt::Type > ();
        break;

      case 344: // expr_pair
        yylhs.value.build< std::pair<std::string, std::string> > ();
        break;

      case 355: // create_stmt
        yylhs.value.build< std::shared_ptr<sql::CreateStmt> > ();
        break;

      case 352: // delete_stmt
        yylhs.value.build< std::shared_ptr<sql::DeleteStmt> > ();
        break;

      case 358: // drop_stmt
        yylhs.value.build< std::shared_ptr<sql::DropStmt> > ();
        break;

      case 353: // insert_stmt
        yylhs.value.build< std::shared_ptr<sql::InsertStmt> > ();
        break;

      case 347: // select_stmt
      case 349: // join_table
        yylhs.value.build< std::shared_ptr<sql::SelectStmt> > ();
        break;

      case 346: // stmt
        yylhs.value.build< std::shared_ptr<sql::Statement> > ();
        break;

      case 371: // table_factor
        yylhs.value.build< std::shared_ptr<sql::Table> > ();
        break;

      case 354: // update_stmt
        yylhs.value.build< std::shared_ptr<sql::UpdateStmt> > ();
        break;

      case 3: // STRING
      case 4: // USERVAR
      case 5: // NAME
      case 22: // COMPARISON
      case 23: // SHIFT
      case 341: // expr_data
      case 360: // column_atts
      case 361: // data_type
      case 362: // opt_as_alias
        yylhs.value.build< std::string > ();
        break;

      case 342: // expr
      case 357: // create_definition
        yylhs.value.build< std::tuple<std::string, std::string, std::string> > ();
        break;

      case 345: // pair_list
      case 365: // opt_ondupupdate
        yylhs.value.build< std::vector<std::pair<std::string, std::string>> > ();
        break;

      case 340: // stmt_list
        yylhs.value.build< std::vector<std::shared_ptr<sql::Statement>> > ();
        break;

      case 370: // table_references
        yylhs.value.build< std::vector<std::shared_ptr<sql::Table>> > ();
        break;

      case 359: // string_list
      case 367: // opt_groupby
      case 368: // opt_orderby
        yylhs.value.build< std::vector<std::string> > ();
        break;

      case 343: // expr_list
      case 350: // join_condition
      case 356: // create_col_list
      case 366: // opt_where
        yylhs.value.build< std::vector<std::tuple<std::string, std::string, std::string>> > ();
        break;

      default:
        break;
    }


      // Compute the default @$.
      {
        slice<stack_symbol_type, stack_type> slice (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, slice, yylen);
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
      try
        {
          switch (yyn)
            {
  case 2:
#line 429 "sql_parser.y" // lalr1.cc:859
    {
	driver.set_result(yystack_[0].value.as< std::vector<std::shared_ptr<sql::Statement>> > ()); 
	}
#line 832 "sql_parser.cc" // lalr1.cc:859
    break;

  case 3:
#line 436 "sql_parser.y" // lalr1.cc:859
    {
	yylhs.value.as< std::vector<std::shared_ptr<sql::Statement>> > ().push_back(yystack_[1].value.as< std::shared_ptr<sql::Statement> > ());
 }
#line 840 "sql_parser.cc" // lalr1.cc:859
    break;

  case 4:
#line 439 "sql_parser.y" // lalr1.cc:859
    { 
	yystack_[2].value.as< std::vector<std::shared_ptr<sql::Statement>> > ().push_back(yystack_[1].value.as< std::shared_ptr<sql::Statement> > ());
	yylhs.value.as< std::vector<std::shared_ptr<sql::Statement>> > () = yystack_[2].value.as< std::vector<std::shared_ptr<sql::Statement>> > ();
 }
#line 849 "sql_parser.cc" // lalr1.cc:859
    break;

  case 5:
#line 448 "sql_parser.y" // lalr1.cc:859
    {
	yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > (); }
#line 856 "sql_parser.cc" // lalr1.cc:859
    break;

  case 6:
#line 450 "sql_parser.y" // lalr1.cc:859
    {
	yylhs.value.as< std::string > () = yystack_[2].value.as< std::string > () + "." + yystack_[0].value.as< std::string > (); }
#line 863 "sql_parser.cc" // lalr1.cc:859
    break;

  case 7:
#line 452 "sql_parser.y" // lalr1.cc:859
    {
	yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > ().substr(1, yystack_[0].value.as< std::string > ().size()-2); }
#line 870 "sql_parser.cc" // lalr1.cc:859
    break;

  case 8:
#line 454 "sql_parser.y" // lalr1.cc:859
    { 
	yylhs.value.as< std::string > () = to_string(yystack_[0].value.as< int > ()); }
#line 877 "sql_parser.cc" // lalr1.cc:859
    break;

  case 9:
#line 456 "sql_parser.y" // lalr1.cc:859
    {
	yylhs.value.as< std::string > () = to_string(yystack_[0].value.as< double > ()); }
#line 884 "sql_parser.cc" // lalr1.cc:859
    break;

  case 10:
#line 458 "sql_parser.y" // lalr1.cc:859
    {
	yylhs.value.as< std::string > () = yystack_[0].value.as< bool > () ? "true" : "false"; }
#line 891 "sql_parser.cc" // lalr1.cc:859
    break;

  case 11:
#line 463 "sql_parser.y" // lalr1.cc:859
    {
	yylhs.value.as< std::tuple<std::string, std::string, std::string> > () = make_tuple(yystack_[2].value.as< std::string > (), yystack_[1].value.as< std::string > (), yystack_[0].value.as< std::string > ()); }
#line 898 "sql_parser.cc" // lalr1.cc:859
    break;

  case 12:
#line 470 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::tuple<std::string, std::string, std::string>> > ().push_back(yystack_[0].value.as< std::tuple<std::string, std::string, std::string> > ()); }
#line 904 "sql_parser.cc" // lalr1.cc:859
    break;

  case 13:
#line 472 "sql_parser.y" // lalr1.cc:859
    { yystack_[0].value.as< std::vector<std::tuple<std::string, std::string, std::string>> > ().push_back(yystack_[2].value.as< std::tuple<std::string, std::string, std::string> > ()); yylhs.value.as< std::vector<std::tuple<std::string, std::string, std::string>> > () = yystack_[0].value.as< std::vector<std::tuple<std::string, std::string, std::string>> > (); }
#line 910 "sql_parser.cc" // lalr1.cc:859
    break;

  case 14:
#line 474 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::tuple<std::string, std::string, std::string>> > () = yystack_[1].value.as< std::vector<std::tuple<std::string, std::string, std::string>> > (); }
#line 916 "sql_parser.cc" // lalr1.cc:859
    break;

  case 15:
#line 478 "sql_parser.y" // lalr1.cc:859
    {
	yylhs.value.as< std::pair<std::string, std::string> > () = make_pair(yystack_[2].value.as< std::string > (), yystack_[0].value.as< std::string > ()); }
#line 923 "sql_parser.cc" // lalr1.cc:859
    break;

  case 16:
#line 483 "sql_parser.y" // lalr1.cc:859
    {
	yylhs.value.as< std::vector<std::pair<std::string, std::string>> > ().push_back(yystack_[0].value.as< std::pair<std::string, std::string> > ()); }
#line 930 "sql_parser.cc" // lalr1.cc:859
    break;

  case 17:
#line 485 "sql_parser.y" // lalr1.cc:859
    {
	yystack_[0].value.as< std::vector<std::pair<std::string, std::string>> > ().push_back(yystack_[2].value.as< std::pair<std::string, std::string> > ()); yylhs.value.as< std::vector<std::pair<std::string, std::string>> > () = yystack_[0].value.as< std::vector<std::pair<std::string, std::string>> > (); }
#line 937 "sql_parser.cc" // lalr1.cc:859
    break;

  case 18:
#line 487 "sql_parser.y" // lalr1.cc:859
    {
	yylhs.value.as< std::vector<std::pair<std::string, std::string>> > () = yystack_[1].value.as< std::vector<std::pair<std::string, std::string>> > (); }
#line 944 "sql_parser.cc" // lalr1.cc:859
    break;

  case 19:
#line 493 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<sql::Statement> > () = yystack_[0].value.as< std::shared_ptr<sql::SelectStmt> > (); }
#line 950 "sql_parser.cc" // lalr1.cc:859
    break;

  case 20:
#line 497 "sql_parser.y" // lalr1.cc:859
    {
	yylhs.value.as< std::shared_ptr<sql::SelectStmt> > () = make_shared<SelectStmt>(yystack_[7].value.as< sql::SelectStmt::Type > (), yystack_[6].value.as< std::vector<std::string> > (), yystack_[4].value.as< std::vector<std::shared_ptr<sql::Table>> > (), yystack_[3].value.as< std::vector<std::tuple<std::string, std::string, std::string>> > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[1].value.as< std::vector<std::string> > (), yystack_[0].value.as< int > ()); }
#line 957 "sql_parser.cc" // lalr1.cc:859
    break;

  case 21:
#line 500 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<sql::SelectStmt> > () = yystack_[1].value.as< std::shared_ptr<sql::SelectStmt> > (); }
#line 963 "sql_parser.cc" // lalr1.cc:859
    break;

  case 22:
#line 505 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< sql::SelectStmt::Type > () = sql::SelectStmt::Type::NO_OPTION; }
#line 969 "sql_parser.cc" // lalr1.cc:859
    break;

  case 23:
#line 507 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< sql::SelectStmt::Type > () = sql::SelectStmt::Type::ALL; }
#line 975 "sql_parser.cc" // lalr1.cc:859
    break;

  case 24:
#line 509 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< sql::SelectStmt::Type > () = sql::SelectStmt::Type::ALL; }
#line 981 "sql_parser.cc" // lalr1.cc:859
    break;

  case 25:
#line 511 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< sql::SelectStmt::Type > () = sql::SelectStmt::Type::DISTINCT; }
#line 987 "sql_parser.cc" // lalr1.cc:859
    break;

  case 26:
#line 513 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< sql::SelectStmt::Type > () = sql::SelectStmt::Type::DISTINCTROW; }
#line 993 "sql_parser.cc" // lalr1.cc:859
    break;

  case 27:
#line 520 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<sql::Statement> > () = yystack_[0].value.as< std::shared_ptr<sql::SelectStmt> > (); }
#line 999 "sql_parser.cc" // lalr1.cc:859
    break;

  case 28:
#line 524 "sql_parser.y" // lalr1.cc:859
    {
	yylhs.value.as< std::shared_ptr<sql::SelectStmt> > () = make_shared<SelectStmt>(yystack_[3].value.as< sql::SelectStmt::Type > (), yystack_[4].value.as< std::shared_ptr<sql::Table> > (), yystack_[1].value.as< std::shared_ptr<sql::Table> > (), yystack_[0].value.as< std::vector<std::tuple<std::string, std::string, std::string>> > ()); }
#line 1006 "sql_parser.cc" // lalr1.cc:859
    break;

  case 29:
#line 527 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<sql::SelectStmt> > () = yystack_[1].value.as< std::shared_ptr<sql::SelectStmt> > (); }
#line 1012 "sql_parser.cc" // lalr1.cc:859
    break;

  case 30:
#line 532 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::tuple<std::string, std::string, std::string>> > () = yystack_[0].value.as< std::vector<std::tuple<std::string, std::string, std::string>> > (); }
#line 1018 "sql_parser.cc" // lalr1.cc:859
    break;

  case 31:
#line 534 "sql_parser.y" // lalr1.cc:859
    { }
#line 1024 "sql_parser.cc" // lalr1.cc:859
    break;

  case 32:
#line 539 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< sql::SelectStmt::Type > () = sql::SelectStmt::Type::FULL_JOIN; }
#line 1030 "sql_parser.cc" // lalr1.cc:859
    break;

  case 33:
#line 541 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< sql::SelectStmt::Type > () = sql::SelectStmt::Type::LEFT_JOIN; }
#line 1036 "sql_parser.cc" // lalr1.cc:859
    break;

  case 34:
#line 543 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< sql::SelectStmt::Type > () = sql::SelectStmt::Type::RIGHT_JOIN; }
#line 1042 "sql_parser.cc" // lalr1.cc:859
    break;

  case 35:
#line 545 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< sql::SelectStmt::Type > () = sql::SelectStmt::Type::INNER_JOIN; }
#line 1048 "sql_parser.cc" // lalr1.cc:859
    break;

  case 36:
#line 547 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< sql::SelectStmt::Type > () = sql::SelectStmt::Type::FULL_JOIN; }
#line 1054 "sql_parser.cc" // lalr1.cc:859
    break;

  case 37:
#line 553 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<sql::Statement> > () = yystack_[0].value.as< std::shared_ptr<sql::DeleteStmt> > (); }
#line 1060 "sql_parser.cc" // lalr1.cc:859
    break;

  case 38:
#line 557 "sql_parser.y" // lalr1.cc:859
    {
	yylhs.value.as< std::shared_ptr<sql::DeleteStmt> > () = make_shared<DeleteStmt>(yystack_[5].value.as< std::vector<std::string> > (), yystack_[3].value.as< std::string > (), yystack_[2].value.as< std::vector<std::tuple<std::string, std::string, std::string>> > (), yystack_[1].value.as< std::vector<std::string> > (), yystack_[0].value.as< int > ()); }
#line 1067 "sql_parser.cc" // lalr1.cc:859
    break;

  case 39:
#line 564 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<sql::Statement> > () = yystack_[0].value.as< std::shared_ptr<sql::InsertStmt> > (); }
#line 1073 "sql_parser.cc" // lalr1.cc:859
    break;

  case 40:
#line 568 "sql_parser.y" // lalr1.cc:859
    {
	yylhs.value.as< std::shared_ptr<sql::InsertStmt> > () = make_shared<InsertStmt>(yystack_[4].value.as< std::string > (), yystack_[3].value.as< std::vector<std::string> > (), yystack_[1].value.as< std::vector<std::string> > (), yystack_[0].value.as< std::vector<std::pair<std::string, std::string>> > ());
	}
#line 1081 "sql_parser.cc" // lalr1.cc:859
    break;

  case 41:
#line 571 "sql_parser.y" // lalr1.cc:859
    {
	yylhs.value.as< std::shared_ptr<sql::InsertStmt> > () = make_shared<InsertStmt>(yystack_[3].value.as< std::string > (), yystack_[1].value.as< std::vector<std::pair<std::string, std::string>> > (), yystack_[0].value.as< std::vector<std::pair<std::string, std::string>> > ());
	}
#line 1089 "sql_parser.cc" // lalr1.cc:859
    break;

  case 42:
#line 574 "sql_parser.y" // lalr1.cc:859
    {
	yylhs.value.as< std::shared_ptr<sql::InsertStmt> > () = make_shared<InsertStmt>(yystack_[3].value.as< std::string > (), yystack_[2].value.as< std::vector<std::string> > (), yystack_[1].value.as< std::shared_ptr<sql::SelectStmt> > (), yystack_[0].value.as< std::vector<std::pair<std::string, std::string>> > ());
	}
#line 1097 "sql_parser.cc" // lalr1.cc:859
    break;

  case 43:
#line 582 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<sql::Statement> > () = yystack_[0].value.as< std::shared_ptr<sql::UpdateStmt> > (); }
#line 1103 "sql_parser.cc" // lalr1.cc:859
    break;

  case 44:
#line 586 "sql_parser.y" // lalr1.cc:859
    {
	yylhs.value.as< std::shared_ptr<sql::UpdateStmt> > () = make_shared<UpdateStmt>(yystack_[5].value.as< std::string > (), yystack_[3].value.as< std::vector<std::pair<std::string, std::string>> > (), yystack_[2].value.as< std::vector<std::tuple<std::string, std::string, std::string>> > (), yystack_[1].value.as< std::vector<std::string> > (), yystack_[0].value.as< int > ()); }
#line 1110 "sql_parser.cc" // lalr1.cc:859
    break;

  case 45:
#line 593 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<sql::Statement> > () = yystack_[0].value.as< std::shared_ptr<sql::CreateStmt> > (); }
#line 1116 "sql_parser.cc" // lalr1.cc:859
    break;

  case 46:
#line 597 "sql_parser.y" // lalr1.cc:859
    {
	yylhs.value.as< std::shared_ptr<sql::CreateStmt> > () = make_shared<CreateStmt>(yystack_[1].value.as< std::string > (), yystack_[2].value.as< bool > (), yystack_[0].value.as< std::vector<std::tuple<std::string, std::string, std::string>> > ()); }
#line 1123 "sql_parser.cc" // lalr1.cc:859
    break;

  case 47:
#line 603 "sql_parser.y" // lalr1.cc:859
    { }
#line 1129 "sql_parser.cc" // lalr1.cc:859
    break;

  case 48:
#line 605 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::tuple<std::string, std::string, std::string>> > ().push_back(yystack_[0].value.as< std::tuple<std::string, std::string, std::string> > ()); }
#line 1135 "sql_parser.cc" // lalr1.cc:859
    break;

  case 49:
#line 607 "sql_parser.y" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::tuple<std::string, std::string, std::string>> > ().push_back(yystack_[0].value.as< std::tuple<std::string, std::string, std::string> > ()); yylhs.value.as< std::vector<std::tuple<std::string, std::string, std::string>> > () = yystack_[2].value.as< std::vector<std::tuple<std::string, std::string, std::string>> > ();  }
#line 1141 "sql_parser.cc" // lalr1.cc:859
    break;

  case 50:
#line 609 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::tuple<std::string, std::string, std::string>> > () = yystack_[1].value.as< std::vector<std::tuple<std::string, std::string, std::string>> > (); }
#line 1147 "sql_parser.cc" // lalr1.cc:859
    break;

  case 51:
#line 613 "sql_parser.y" // lalr1.cc:859
    {
	yylhs.value.as< std::tuple<std::string, std::string, std::string> > () = make_tuple(yystack_[2].value.as< std::string > (), yystack_[1].value.as< std::string > (), yystack_[0].value.as< std::string > ()); }
#line 1154 "sql_parser.cc" // lalr1.cc:859
    break;

  case 52:
#line 621 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<sql::Statement> > () = yystack_[0].value.as< std::shared_ptr<sql::DropStmt> > (); }
#line 1160 "sql_parser.cc" // lalr1.cc:859
    break;

  case 53:
#line 625 "sql_parser.y" // lalr1.cc:859
    { 
	yylhs.value.as< std::shared_ptr<sql::DropStmt> > () = make_shared<DropStmt>(yystack_[0].value.as< std::string > ()); }
#line 1167 "sql_parser.cc" // lalr1.cc:859
    break;

  case 54:
#line 631 "sql_parser.y" // lalr1.cc:859
    { }
#line 1173 "sql_parser.cc" // lalr1.cc:859
    break;

  case 55:
#line 633 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::string> > ().push_back(yystack_[0].value.as< std::string > ()); }
#line 1179 "sql_parser.cc" // lalr1.cc:859
    break;

  case 56:
#line 635 "sql_parser.y" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::string> > ().push_back(yystack_[0].value.as< std::string > ()); yylhs.value.as< std::vector<std::string> > () = yystack_[2].value.as< std::vector<std::string> > (); }
#line 1185 "sql_parser.cc" // lalr1.cc:859
    break;

  case 57:
#line 637 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::string> > () = yystack_[1].value.as< std::vector<std::string> > (); }
#line 1191 "sql_parser.cc" // lalr1.cc:859
    break;

  case 58:
#line 643 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::string > () = "NO_ATT"; }
#line 1197 "sql_parser.cc" // lalr1.cc:859
    break;

  case 59:
#line 645 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::string > () = "NOT_NULLX"; }
#line 1203 "sql_parser.cc" // lalr1.cc:859
    break;

  case 60:
#line 647 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::string > () = "NULLX"; }
#line 1209 "sql_parser.cc" // lalr1.cc:859
    break;

  case 61:
#line 649 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::string > () = "AUTO_INC"; }
#line 1215 "sql_parser.cc" // lalr1.cc:859
    break;

  case 62:
#line 651 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::string > () = "UNIQUE_KEY"; }
#line 1221 "sql_parser.cc" // lalr1.cc:859
    break;

  case 63:
#line 653 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::string > () = "PRIMARY_KEY"; }
#line 1227 "sql_parser.cc" // lalr1.cc:859
    break;

  case 64:
#line 655 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::string > () = "KEY"; }
#line 1233 "sql_parser.cc" // lalr1.cc:859
    break;

  case 65:
#line 660 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::string > () = "BIT"; }
#line 1239 "sql_parser.cc" // lalr1.cc:859
    break;

  case 66:
#line 662 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::string > () = "INT"; }
#line 1245 "sql_parser.cc" // lalr1.cc:859
    break;

  case 67:
#line 664 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::string > () = "INTEGER"; }
#line 1251 "sql_parser.cc" // lalr1.cc:859
    break;

  case 68:
#line 666 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::string > () = "BIGINT"; }
#line 1257 "sql_parser.cc" // lalr1.cc:859
    break;

  case 69:
#line 668 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::string > () = "REAL"; }
#line 1263 "sql_parser.cc" // lalr1.cc:859
    break;

  case 70:
#line 670 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::string > () = "DOUBLE"; }
#line 1269 "sql_parser.cc" // lalr1.cc:859
    break;

  case 71:
#line 672 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::string > () = "FLOAT"; }
#line 1275 "sql_parser.cc" // lalr1.cc:859
    break;

  case 72:
#line 674 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::string > () = "DECIMAL"; }
#line 1281 "sql_parser.cc" // lalr1.cc:859
    break;

  case 73:
#line 676 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::string > () = "DATE"; }
#line 1287 "sql_parser.cc" // lalr1.cc:859
    break;

  case 74:
#line 678 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::string > () = "TIME"; }
#line 1293 "sql_parser.cc" // lalr1.cc:859
    break;

  case 75:
#line 680 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::string > () = "TIMESTAMP"; }
#line 1299 "sql_parser.cc" // lalr1.cc:859
    break;

  case 76:
#line 682 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::string > () = "DATETIME"; }
#line 1305 "sql_parser.cc" // lalr1.cc:859
    break;

  case 77:
#line 684 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::string > () = "YEAR"; }
#line 1311 "sql_parser.cc" // lalr1.cc:859
    break;

  case 78:
#line 686 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::string > () = "CHAR"; }
#line 1317 "sql_parser.cc" // lalr1.cc:859
    break;

  case 79:
#line 688 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::string > () = "VARCHAR"; }
#line 1323 "sql_parser.cc" // lalr1.cc:859
    break;

  case 80:
#line 690 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::string > () = "BINARY"; }
#line 1329 "sql_parser.cc" // lalr1.cc:859
    break;

  case 81:
#line 692 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::string > () = "TEXT"; }
#line 1335 "sql_parser.cc" // lalr1.cc:859
    break;

  case 82:
#line 697 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::string > () = yystack_[0].value.as< std::string > (); }
#line 1341 "sql_parser.cc" // lalr1.cc:859
    break;

  case 83:
#line 699 "sql_parser.y" // lalr1.cc:859
    {  }
#line 1347 "sql_parser.cc" // lalr1.cc:859
    break;

  case 84:
#line 704 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< bool > () = false; }
#line 1353 "sql_parser.cc" // lalr1.cc:859
    break;

  case 85:
#line 706 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< bool > () = true; }
#line 1359 "sql_parser.cc" // lalr1.cc:859
    break;

  case 88:
#line 716 "sql_parser.y" // lalr1.cc:859
    { }
#line 1365 "sql_parser.cc" // lalr1.cc:859
    break;

  case 89:
#line 718 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::pair<std::string, std::string>> > () = yystack_[0].value.as< std::vector<std::pair<std::string, std::string>> > (); }
#line 1371 "sql_parser.cc" // lalr1.cc:859
    break;

  case 90:
#line 723 "sql_parser.y" // lalr1.cc:859
    { }
#line 1377 "sql_parser.cc" // lalr1.cc:859
    break;

  case 91:
#line 725 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::tuple<std::string, std::string, std::string>> > () = yystack_[0].value.as< std::vector<std::tuple<std::string, std::string, std::string>> > (); }
#line 1383 "sql_parser.cc" // lalr1.cc:859
    break;

  case 92:
#line 729 "sql_parser.y" // lalr1.cc:859
    { }
#line 1389 "sql_parser.cc" // lalr1.cc:859
    break;

  case 93:
#line 731 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::string> > () = yystack_[0].value.as< std::vector<std::string> > (); }
#line 1395 "sql_parser.cc" // lalr1.cc:859
    break;

  case 94:
#line 736 "sql_parser.y" // lalr1.cc:859
    { }
#line 1401 "sql_parser.cc" // lalr1.cc:859
    break;

  case 95:
#line 738 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::string> > () = yystack_[0].value.as< std::vector<std::string> > (); }
#line 1407 "sql_parser.cc" // lalr1.cc:859
    break;

  case 96:
#line 743 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< int > () = 0; }
#line 1413 "sql_parser.cc" // lalr1.cc:859
    break;

  case 97:
#line 745 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< int > () = yystack_[0].value.as< int > (); }
#line 1419 "sql_parser.cc" // lalr1.cc:859
    break;

  case 98:
#line 750 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<sql::Table>> > ().push_back(yystack_[0].value.as< std::shared_ptr<sql::Table> > ()); }
#line 1425 "sql_parser.cc" // lalr1.cc:859
    break;

  case 99:
#line 752 "sql_parser.y" // lalr1.cc:859
    { yystack_[2].value.as< std::vector<std::shared_ptr<sql::Table>> > ().push_back(yystack_[0].value.as< std::shared_ptr<sql::Table> > ()); yylhs.value.as< std::vector<std::shared_ptr<sql::Table>> > () = yystack_[2].value.as< std::vector<std::shared_ptr<sql::Table>> > (); }
#line 1431 "sql_parser.cc" // lalr1.cc:859
    break;

  case 100:
#line 754 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::vector<std::shared_ptr<sql::Table>> > () = yystack_[1].value.as< std::vector<std::shared_ptr<sql::Table>> > (); }
#line 1437 "sql_parser.cc" // lalr1.cc:859
    break;

  case 101:
#line 758 "sql_parser.y" // lalr1.cc:859
    {
	yylhs.value.as< std::shared_ptr<sql::Table> > () = make_shared<Table>(Table::DEFAULT, yystack_[1].value.as< std::string > (), yystack_[0].value.as< std::string > ()); }
#line 1444 "sql_parser.cc" // lalr1.cc:859
    break;

  case 102:
#line 760 "sql_parser.y" // lalr1.cc:859
    {
	yylhs.value.as< std::shared_ptr<sql::Table> > () = make_shared<Table>(Table::SELECT, yystack_[1].value.as< std::shared_ptr<sql::SelectStmt> > (), yystack_[0].value.as< std::string > ()); }
#line 1451 "sql_parser.cc" // lalr1.cc:859
    break;

  case 103:
#line 762 "sql_parser.y" // lalr1.cc:859
    {
	yylhs.value.as< std::shared_ptr<sql::Table> > () = make_shared<Table>(Table::SELECT, yystack_[1].value.as< std::shared_ptr<sql::SelectStmt> > (), yystack_[0].value.as< std::string > ()); }
#line 1458 "sql_parser.cc" // lalr1.cc:859
    break;

  case 104:
#line 765 "sql_parser.y" // lalr1.cc:859
    { yylhs.value.as< std::shared_ptr<sql::Table> > () = yystack_[1].value.as< std::shared_ptr<sql::Table> > (); }
#line 1464 "sql_parser.cc" // lalr1.cc:859
    break;


#line 1468 "sql_parser.cc" // lalr1.cc:859
            default:
              break;
            }
        }
      catch (const syntax_error& yyexc)
        {
          error (yyexc);
          YYERROR;
        }
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;
      YY_STACK_PRINT ();

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, yylhs);
    }
    goto yynewstate;

  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:

    /* Pacify compilers like GCC when the user code never invokes
       YYERROR and the label yyerrorlab therefore never appears in user
       code.  */
    if (false)
      goto yyerrorlab;
    yyerror_range[1].location = yystack_[yylen - 1].location;
    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    goto yyerrlab1;

  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
                {
                  yyn = yytable_[yyn];
                  if (0 < yyn)
                    break;
                }
            }

          // Pop the current state because it cannot handle the error token.
          if (yystack_.size () == 1)
            YYABORT;

          yyerror_range[1].location = yystack_[0].location;
          yy_destroy_ ("Error: popping", yystack_[0]);
          yypop_ ();
          YY_STACK_PRINT ();
        }

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = yyn;
      yypush_ ("Shifting", error_token);
    }
    goto yynewstate;

    // Accept.
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;

    // Abort.
  yyabortlab:
    yyresult = 1;
    goto yyreturn;

  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack"
                 << std::endl;
        // Do not try to display the values of the reclaimed symbols,
        // as their printer might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what());
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    size_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
        YYCASE_(0, YY_("syntax error"));
        YYCASE_(1, YY_("syntax error, unexpected %s"));
        YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    size_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const short int Parser::yypact_ninf_ = -248;

  const signed char Parser::yytable_ninf_ = -99;

  const short int
  Parser::yypact_[] =
  {
      -4,    33,  -141,     3,  -140,   -47,     1,    73,     2,    79,
      -4,  -247,    -8,    10,  -248,  -248,  -248,  -248,  -248,   -74,
      85,  -248,   -19,  -248,  -244,  -248,  -248,  -248,     3,  -248,
      16,    94,  -248,    95,  -248,  -248,  -248,  -248,     3,   -89,
      -2,     6,   -88,  -248,  -225,  -248,  -248,  -248,  -248,  -248,
    -248,  -248,   -12,  -248,    92,   109,   110,    -1,   132,   112,
    -248,    -3,    27,     9,  -248,  -248,  -248,  -248,     2,    30,
      14,  -248,  -248,  -248,  -121,     9,     4,     8,     9,   103,
      98,  -121,    33,    33,   -82,  -248,    11,    14,   101,  -248,
      15,   -26,   -20,     3,  -162,   -20,     8,    12,   -78,  -200,
     132,     9,   -26,    15,  -248,  -248,  -248,  -248,  -248,  -248,
    -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,  -248,
    -248,  -248,    18,     0,   138,    15,   122,   115,  -248,   104,
      17,    -5,  -248,     7,  -186,  -248,     5,    -6,     2,    47,
    -248,  -248,  -248,    17,  -248,    13,  -248,  -248,  -248,    28,
      31,  -248,  -248,  -248,  -183,   132,    15,     3,   148,  -248,
      34,  -248,  -248,   -78,   117,   -26,  -248,  -248,  -248,  -248,
    -248,  -248,  -248,   127,  -248,   -62,     3,    17,     9,   127,
    -248,  -248
  };

  const unsigned char
  Parser::yydefact_[] =
  {
       0,    83,     0,    54,     0,    87,    22,     0,     0,     0,
       2,     0,    83,    83,    37,    39,    43,    45,    52,    36,
       0,   101,    84,     7,     5,     8,    10,     9,    54,    55,
       0,     0,    86,     0,    24,    25,    26,    23,    54,     0,
      83,    83,    36,     1,     0,     3,   103,   102,    35,    33,
      34,    32,     0,    82,     0,     0,     0,     0,     0,     0,
      53,    54,     0,     0,    21,    29,   104,     4,     0,     0,
      47,     6,    57,    56,    90,     0,     0,     0,     0,     0,
      16,    90,    83,    83,    31,    85,     0,    47,    46,    48,
       0,    94,    88,    54,     0,    88,     0,    90,    98,     0,
       0,     0,    94,     0,    28,    68,    80,    65,    78,    73,
      76,    72,    70,    71,    66,    67,    69,    81,    74,    75,
      79,    77,    58,     0,     0,     0,     0,    12,    91,     0,
      96,     0,    41,    88,     0,    42,     0,    36,     0,    92,
      18,    15,    17,    96,    30,     0,    61,    64,    60,     0,
       0,    51,    50,    49,     0,     0,     0,    54,     0,    38,
       0,    40,   100,    99,     0,    94,    44,    59,    63,    62,
      14,    11,    13,    95,    97,     0,    54,    96,     0,    93,
      20,    89
  };

  const short int
  Parser::yypgoto_[] =
  {
    -248,  -248,  -248,    78,  -248,   -36,  -248,   -16,   156,    96,
    -248,    65,  -248,  -248,  -248,  -248,  -248,  -248,    80,    46,
    -248,    26,  -248,  -248,    43,  -248,  -248,   -35,   -11,  -248,
     -41,   -80,    77,    25
  };

  const short int
  Parser::yydefgoto_[] =
  {
      -1,     9,    10,    29,   127,   128,    80,    81,    11,    82,
      38,    83,   104,    52,    14,    15,    16,    17,    88,    89,
      18,    30,   151,   122,    46,    55,    33,   132,    91,   165,
     130,   159,    97,    19
  };

  const short int
  Parser::yytable_[] =
  {
      23,     1,    24,    25,    26,    27,    23,     1,    24,    25,
      26,    27,    23,     1,    24,    25,    26,    27,    23,    86,
      24,    25,    26,    27,   -98,    20,    48,     6,    34,    58,
     124,    20,    48,    42,    58,   138,    48,    58,   145,    20,
      48,    49,   138,    20,    21,   -36,    58,    49,   105,   106,
     107,    49,     2,   146,    57,    49,    47,    58,   108,    92,
     135,   143,    99,   166,    62,    13,    20,   144,    22,    31,
     102,   103,     3,    41,    32,    13,   109,   110,    39,    43,
       4,    35,    36,   111,    47,   142,   139,    76,    45,   154,
      53,    54,    56,    84,   112,    50,    12,   180,   161,    60,
      61,    50,    98,    63,    40,    50,    12,   113,    48,    50,
      67,    68,    69,     5,    70,    71,    59,    74,    90,   133,
     172,   137,    85,    49,   177,   100,    47,    77,   101,   114,
     115,   124,   129,   131,   140,    23,    73,    24,    25,    26,
      27,    79,   147,    86,   155,   156,   157,   158,    64,   160,
     164,   170,   168,    79,   174,   169,    79,    58,   175,   176,
     131,    41,   181,   163,   167,   178,    44,   123,   126,   148,
     153,    94,    95,   136,     0,     0,     0,    50,   141,    79,
       0,   126,   149,   173,   116,     6,     0,     0,     0,    75,
     134,     6,    40,     6,     0,     0,     0,     6,     0,     0,
       0,     0,   179,   126,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   117,     7,     0,   118,   119,     0,     0,     0,
       0,    51,     0,   171,   126,     0,     0,    51,    93,     0,
       0,    51,   150,     0,     0,    51,    66,   120,     0,     0,
       0,    90,     0,     0,   121,     0,    79,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    51,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   -19,    66,     8,
      28,     0,    64,    72,   152,     8,    28,    94,    37,   162,
      65,    96,    78,     0,     0,   -27,     0,    87,   125
  };

  const short int
  Parser::yycheck_[] =
  {
       3,     5,     5,     6,     7,     8,     3,     5,     5,     6,
       7,     8,     3,     5,     5,     6,     7,     8,     3,     5,
       5,     6,     7,     8,    30,    33,   114,   189,    27,    30,
      30,    33,   114,     8,    30,    30,   114,    30,    20,    33,
     114,   129,    30,    33,     1,   123,    30,   129,    37,    38,
      39,   129,    56,    35,    28,   129,    13,    30,    47,    75,
      95,   102,    78,   143,    38,     0,    33,   103,   209,   209,
      81,   153,    76,     8,   121,    10,    65,    66,     5,     0,
      84,    80,    81,    72,    41,   101,    97,    61,   335,   125,
       5,   110,   336,    68,    83,   183,     0,   177,   133,     5,
       5,   183,    77,   192,     8,   183,    10,    96,   114,   183,
     335,   123,    20,   117,     5,     5,   100,     5,   239,    93,
     156,    96,    92,   129,   165,    22,    83,   100,    30,   118,
     119,    30,   158,   153,   334,     3,    58,     5,     6,     7,
       8,    63,   124,     5,    22,    30,    42,   130,   334,   154,
     103,   334,   124,    75,     6,   124,    78,    30,   124,    42,
     153,    96,   178,   138,   151,   227,    10,    87,    90,   151,
     124,   333,    76,    96,    -1,    -1,    -1,   183,   100,   101,
      -1,   103,   164,   157,   173,   189,    -1,    -1,    -1,   192,
      94,   189,    96,   189,    -1,    -1,    -1,   189,    -1,    -1,
      -1,    -1,   176,   125,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   211,   227,    -1,   214,   215,    -1,    -1,    -1,
      -1,   319,    -1,   155,   156,    -1,    -1,   319,   234,    -1,
      -1,   319,   224,    -1,    -1,   319,   334,   236,    -1,    -1,
      -1,   239,    -1,    -1,   243,    -1,   178,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   319,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   335,   334,   333,
     333,    -1,   334,   334,   334,   333,   333,   333,   337,   334,
     334,   333,   333,    -1,    -1,   335,    -1,   333,   333
  };

  const unsigned short int
  Parser::yystos_[] =
  {
       0,     5,    56,    76,    84,   117,   189,   227,   333,   339,
     340,   346,   347,   349,   352,   353,   354,   355,   358,   371,
      33,   362,   209,     3,     5,     6,     7,     8,   333,   341,
     359,   209,   121,   364,    27,    80,    81,   337,   348,     5,
     347,   349,   371,     0,   346,   335,   362,   362,   114,   129,
     183,   319,   351,     5,   110,   363,   336,   359,    30,   100,
       5,     5,   359,   192,   334,   334,   334,   335,   123,    20,
       5,     5,   334,   341,     5,   192,   359,   100,   333,   341,
     344,   345,   347,   349,   371,    92,     5,   333,   356,   357,
     239,   366,   345,   234,   333,   347,   333,   370,   371,   345,
      22,    30,   366,   153,   350,    37,    38,    39,    47,    65,
      66,    72,    83,    96,   118,   119,   173,   211,   214,   215,
     236,   243,   361,   356,    30,   333,   341,   342,   343,   158,
     368,   153,   365,   359,   347,   365,   370,   371,    30,   366,
     334,   341,   345,   368,   343,    20,    35,   124,   151,   164,
     224,   360,   334,   357,   343,    22,    30,    42,   130,   369,
     154,   365,   334,   371,   103,   367,   369,   151,   124,   124,
     334,   341,   343,   359,     6,   124,    42,   368,   227,   359,
     369,   345
  };

  const unsigned short int
  Parser::yyr1_[] =
  {
       0,   338,   339,   340,   340,   341,   341,   341,   341,   341,
     341,   342,   343,   343,   343,   344,   345,   345,   345,   346,
     347,   347,   348,   348,   348,   348,   348,   346,   349,   349,
     350,   350,   351,   351,   351,   351,   351,   346,   352,   346,
     353,   353,   353,   346,   354,   346,   355,   356,   356,   356,
     356,   357,   346,   358,   359,   359,   359,   359,   360,   360,
     360,   360,   360,   360,   360,   361,   361,   361,   361,   361,
     361,   361,   361,   361,   361,   361,   361,   361,   361,   361,
     361,   361,   362,   362,   363,   363,   364,   364,   365,   365,
     366,   366,   367,   367,   368,   368,   369,   369,   370,   370,
     370,   371,   371,   371,   371
  };

  const unsigned char
  Parser::yyr2_[] =
  {
       0,     2,     1,     2,     3,     1,     3,     1,     1,     1,
       1,     3,     1,     3,     3,     3,     1,     3,     3,     1,
       9,     3,     0,     1,     1,     1,     1,     1,     5,     3,
       2,     0,     1,     1,     1,     1,     0,     1,     7,     1,
       7,     6,     6,     1,     7,     1,     5,     0,     1,     3,
       3,     3,     1,     3,     0,     1,     3,     3,     0,     2,
       1,     1,     2,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     2,     0,     0,     3,     1,     0,     0,     5,
       0,     2,     0,     3,     0,     3,     0,     2,     1,     3,
       3,     2,     2,     2,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "STRING", "USERVAR", "NAME",
  "INTNUM", "BOOL", "APPROXNUM", "NOTEQUALS", "LESSEQ", "GREATEREQ",
  "ASSIGN", "OR", "XOR", "ANDOP", "IN", "IS", "LIKE", "REGEXP", "NOT",
  "BETWEEN", "COMPARISON", "SHIFT", "MOD", "UMINUS", "ADD", "ALL", "ALTER",
  "ANALYZE", "AND", "ANY", "APPEND", "AS", "ASC", "AUTO_INCREMENT",
  "BEFORE", "BIGINT", "BINARY", "BIT", "BLOB", "BOTH", "BY", "CALL",
  "CASCADE", "CASE", "CHANGE", "CHAR", "CHECK", "COLLATE", "COLUMN",
  "COMMENT", "CONDITION", "CONSTRAINT", "CONTINUE", "CONVERT", "CREATE",
  "CROSS", "CURRENT_DATE", "CURRENT_TIME", "CURRENT_TIMESTAMP",
  "CURRENT_USER", "CURSOR", "DATABASE", "DATABASES", "DATE", "DATETIME",
  "DAY_HOUR", "DAY", "DAY_MICROSECOND", "DAY_MINUTE", "DAY_SECOND",
  "DECIMAL", "DECLARE", "DEFAULT", "DELAYED", "DELETE", "DESC", "DESCRIBE",
  "DETERMINISTIC", "DISTINCT", "DISTINCTROW", "DIV", "DOUBLE", "DROP",
  "DUAL", "EACH", "ELSE", "ELSEIF", "ENCLOSED", "ENUM", "ESCAPED",
  "EXISTS", "EXIT", "EXPLAIN", "FETCH", "FLOAT", "FOR", "FORCE", "FOREIGN",
  "FROM", "FULLTEXT", "GRANT", "GROUP", "HAVING", "HIGH", "HIGH_PRIORITY",
  "HOUR_MICROSECOND", "HOUR_MINUTE", "HOUR_SECOND", "IF", "IGNORE",
  "INDEX", "INFILE", "INNER", "INOUT", "INSENSITIVE", "INSERT", "INT",
  "INTEGER", "INTERVAL", "INTO", "ITERATE", "JOIN", "KEY", "KEYS", "KILL",
  "LEADING", "LEAVE", "LEFT", "LIMIT", "LINES", "LOAD", "LOCALTIME",
  "LOCALTIMESTAMP", "LOCK", "LONG", "LONGBLOB", "LONGTEXT", "LOOP", "LOW",
  "LOW_PRIORITY", "MATCH", "MEDIUMBLOB", "MEDIUMINT", "MEDIUMTEXT",
  "MINUTE_MICROSECOND", "MINUTE_SECOND", "MODIFIES", "NATURAL",
  "NO_WRITE_TO_BINLOG", "NULLX", "NUMBER", "ON", "DUPLICATE", "OPTIMIZE",
  "OPTION", "OPTIONALLY", "ORDER", "OUT", "OUTER", "OUTFILE",
  "PARTITIONED", "PRECISION", "PRIMARY", "PRIORITY", "PROCEDURE",
  "PROJECTION", "PURGE", "QUICK", "QUARTER", "READ", "READS", "REAL",
  "REFERENCES", "RELEASE", "RENAME", "REPEAT", "REPLACE", "REQUIRE",
  "RESTRICT", "RETURN", "REVOKE", "RIGHT", "ROLLUP", "SAMPLE", "SCHEMA",
  "SCHEMAS", "SECOND_MICROSECOND", "SELECT", "SENSITIVE", "SEPARATOR",
  "SET", "SHOW", "SMALLINT", "SOME", "SONAME", "SPATIAL", "SPECIFIC",
  "SQL", "SQLEXCEPTION", "SQLSTATE", "SQLWARNING", "BIG_RESULT",
  "CALC_FOUND_ROWS", "SMALL_RESULT", "SSL", "STARTING", "STRAIGHT_JOIN",
  "TABLE", "TEMPORARY", "TEXT", "TERMINATED", "THEN", "TIME", "TIMESTAMP",
  "TINYBLOB", "TINYINT", "TINYTEXT", "TO", "TRAILING", "TRIGGER", "UNDO",
  "UNION", "UNIQUE", "UNLOCK", "UNSIGNED", "UPDATE", "USAGE", "USE",
  "USING", "UTC_DATE", "UTC_TIME", "UTC_TIMESTAMP", "VALUES", "VARBINARY",
  "VARCHAR", "VARYING", "WHEN", "WHERE", "WHILE", "WITH", "WRITE", "YEAR",
  "YEAR_MONTH", "ZEROFILL", "WEEK", "DO", "MAX_QUERIES_PER_HOUR",
  "MAX_UPDATES_PER_HOUR", "MAX_CONNECTIONS_PER_HOUR",
  "MAX_USER_CONNECTIONS", "USER", "TRUNCATE", "FAST", "MEDIUM", "EXTENDED",
  "CHANGED", "LEAVES", "MASTER", "QUERY", "CACHE", "SLAVE", "BEGINT",
  "COMMIT", "START", "TRANSACTION", "NO", "CHAIN", "AUTOCOMMIT",
  "SAVEPOINT", "ROLLBACK", "LOCAL", "TABLES", "ISOLATION", "LEVEL",
  "GLOBAL", "SESSION", "UNCOMMITTED", "COMMITTED", "REPEATABLE",
  "SERIALIZABLE", "IDENTIFIED", "PASSWORD", "PRIVILEGES", "BACKUP",
  "CHECKSUM", "REPAIR", "USE_FRM", "RESTORE", "CHARACTER", "COLLATION",
  "COLUMNS", "ENGINE", "LOGS", "STATUS", "STORAGE", "ENGINES", "ERRORS",
  "GRANTS", "INNODB", "PROCESSLIST", "TRIGGERS", "VARIABLES", "WARNINGS",
  "FLUSH", "HOSTS", "DES_KEY_FILE", "USER_RESOURCES", "CONNECTION",
  "RESET", "PREPARE", "DEALLOCATE", "EXECUTE", "WORK", "BTREE", "HASH",
  "BDB", "OPEN", "FULL", "FSUBSTRING", "FTRIM", "FDATE_ADD", "FDATE_SUB",
  "FCOUNT", "FUPPER", "FCAST", "FCOALESCE", "FCONVERT", "FSUM", "FAVG",
  "FMIN", "FMAX", "BRACKET_O", "BRACKET_C", "SEMICOLON", "DOT", "MULTIPLY",
  "$accept", "input", "stmt_list", "expr_data", "expr", "expr_list",
  "expr_pair", "pair_list", "stmt", "select_stmt", "select_opts",
  "join_table", "join_condition", "join_opts", "delete_stmt",
  "insert_stmt", "update_stmt", "create_stmt", "create_col_list",
  "create_definition", "drop_stmt", "string_list", "column_atts",
  "data_type", "opt_as_alias", "opt_if_not_exists", "opt_into",
  "opt_ondupupdate", "opt_where", "opt_groupby", "opt_orderby",
  "opt_limit", "table_references", "table_factor", YY_NULLPTR
  };

#if YYDEBUG
  const unsigned short int
  Parser::yyrline_[] =
  {
       0,   428,   428,   436,   439,   448,   450,   452,   454,   456,
     458,   463,   469,   471,   473,   478,   483,   485,   487,   492,
     497,   499,   505,   506,   508,   510,   512,   519,   524,   526,
     531,   534,   538,   540,   542,   544,   547,   552,   557,   563,
     568,   571,   574,   581,   586,   592,   597,   603,   604,   606,
     608,   613,   620,   625,   631,   632,   634,   636,   643,   644,
     646,   648,   650,   652,   654,   659,   661,   663,   665,   667,
     669,   671,   673,   675,   677,   679,   681,   683,   685,   687,
     689,   691,   696,   699,   704,   705,   710,   711,   716,   717,
     723,   724,   729,   730,   736,   737,   743,   744,   749,   751,
     753,   758,   760,   762,   764
  };

  // Print the state stack on the debug stream.
  void
  Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << std::endl;
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):" << std::endl;
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG


#line 6 "sql_parser.y" // lalr1.cc:1167
} // sql
#line 2049 "sql_parser.cc" // lalr1.cc:1167
#line 769 "sql_parser.y" // lalr1.cc:1168


/* empty */
void sql::Parser::error(const location_type& l, const std::string& m) {
	driver.error(l, m);
}
