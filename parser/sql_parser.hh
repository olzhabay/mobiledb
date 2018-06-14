// A Bison parser, made by GNU Bison 3.0.4.

// Skeleton interface for Bison LALR(1) parsers in C++

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

/**
 ** \file sql_parser.hh
 ** Define the sql::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

#ifndef YY_YY_SQL_PARSER_HH_INCLUDED
# define YY_YY_SQL_PARSER_HH_INCLUDED
// //                    "%code requires" blocks.
#line 18 "sql_parser.y" // lalr1.cc:377

#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include "location.hh"
#include "sql_driver.hh"
#include "position.hh"
#include "statements/sql_statement.hh"
#include "statements/sql_table.hh"
#include "statements/delete_statement.hh"
#include "statements/drop_statement.hh"
#include "statements/update_statement.hh"
#include "statements/insert_statement.hh"
#include "statements/select_statement.hh"
#include "statements/create_statement.hh"

class Driver;
class Scanner;

using namespace std;


#line 68 "sql_parser.hh" // lalr1.cc:377

# include <cassert>
# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>
# include "stack.hh"
# include "location.hh"
#include <typeinfo>
#ifndef YYASSERT
# include <cassert>
# define YYASSERT assert
#endif


#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif

#line 6 "sql_parser.y" // lalr1.cc:377
namespace sql {
#line 145 "sql_parser.hh" // lalr1.cc:377



  /// A char[S] buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current state.
  template <size_t S>
  struct variant
  {
    /// Type of *this.
    typedef variant<S> self_type;

    /// Empty construction.
    variant ()
      : yytypeid_ (YY_NULLPTR)
    {}

    /// Construct and fill.
    template <typename T>
    variant (const T& t)
      : yytypeid_ (&typeid (T))
    {
      YYASSERT (sizeof (T) <= S);
      new (yyas_<T> ()) T (t);
    }

    /// Destruction, allowed only if empty.
    ~variant ()
    {
      YYASSERT (!yytypeid_);
    }

    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    build ()
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T;
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    build (const T& t)
    {
      YYASSERT (!yytypeid_);
      YYASSERT (sizeof (T) <= S);
      yytypeid_ = & typeid (T);
      return *new (yyas_<T> ()) T (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as ()
    {
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const
    {
      YYASSERT (*yytypeid_ == typeid (T));
      YYASSERT (sizeof (T) <= S);
      return *yyas_<T> ();
    }

    /// Swap the content with \a other, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsability.
    /// Swapping between built and (possibly) non-built is done with
    /// variant::move ().
    template <typename T>
    void
    swap (self_type& other)
    {
      YYASSERT (yytypeid_);
      YYASSERT (*yytypeid_ == *other.yytypeid_);
      std::swap (as<T> (), other.as<T> ());
    }

    /// Move the content of \a other to this.
    ///
    /// Destroys \a other.
    template <typename T>
    void
    move (self_type& other)
    {
      build<T> ();
      swap<T> (other);
      other.destroy<T> ();
    }

    /// Copy the content of \a other to this.
    template <typename T>
    void
    copy (const self_type& other)
    {
      build<T> (other.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
      yytypeid_ = YY_NULLPTR;
    }

  private:
    /// Prohibit blind copies.
    self_type& operator=(const self_type&);
    variant (const self_type&);

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ ()
    {
      void *yyp = yybuffer_.yyraw;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const
    {
      const void *yyp = yybuffer_.yyraw;
      return static_cast<const T*> (yyp);
     }

    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me;
      /// A buffer large enough to store any of the semantic values.
      char yyraw[S];
    } yybuffer_;

    /// Whether the content is built: if defined, the name of the stored type.
    const std::type_info *yytypeid_;
  };


  /// A Bison parser.
  class Parser
  {
  public:
#ifndef YYSTYPE
    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // BOOL
      // opt_if_not_exists
      char dummy1[sizeof(bool)];

      // APPROXNUM
      char dummy2[sizeof(double)];

      // INTNUM
      // NOTEQUALS
      // LESSEQ
      // GREATEREQ
      // opt_limit
      char dummy3[sizeof(int)];

      // select_opts
      // join_opts
      char dummy4[sizeof(sql::SelectStmt::Type)];

      // expr_pair
      char dummy5[sizeof(std::pair<std::string, std::string>)];

      // create_stmt
      char dummy6[sizeof(std::shared_ptr<sql::CreateStmt>)];

      // delete_stmt
      char dummy7[sizeof(std::shared_ptr<sql::DeleteStmt>)];

      // drop_stmt
      char dummy8[sizeof(std::shared_ptr<sql::DropStmt>)];

      // insert_stmt
      char dummy9[sizeof(std::shared_ptr<sql::InsertStmt>)];

      // select_stmt
      // join_table
      char dummy10[sizeof(std::shared_ptr<sql::SelectStmt>)];

      // stmt
      char dummy11[sizeof(std::shared_ptr<sql::Statement>)];

      // table_factor
      char dummy12[sizeof(std::shared_ptr<sql::Table>)];

      // update_stmt
      char dummy13[sizeof(std::shared_ptr<sql::UpdateStmt>)];

      // STRING
      // USERVAR
      // NAME
      // COMPARISON
      // SHIFT
      // expr_data
      // column_atts
      // data_type
      // opt_as_alias
      char dummy14[sizeof(std::string)];

      // expr
      // create_definition
      char dummy15[sizeof(std::tuple<std::string, std::string, std::string>)];

      // pair_list
      // opt_ondupupdate
      char dummy16[sizeof(std::vector<std::pair<std::string, std::string>>)];

      // stmt_list
      char dummy17[sizeof(std::vector<std::shared_ptr<sql::Statement>>)];

      // table_references
      char dummy18[sizeof(std::vector<std::shared_ptr<sql::Table>>)];

      // string_list
      // opt_groupby
      // opt_orderby
      char dummy19[sizeof(std::vector<std::string>)];

      // expr_list
      // join_condition
      // create_col_list
      // opt_where
      char dummy20[sizeof(std::vector<std::tuple<std::string, std::string, std::string>>)];
};

    /// Symbol semantic values.
    typedef variant<sizeof(union_type)> semantic_type;
#else
    typedef YYSTYPE semantic_type;
#endif
    /// Symbol locations.
    typedef location location_type;

    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const location_type& l, const std::string& m);
      location_type location;
    };

    /// Tokens.
    struct token
    {
      enum yytokentype
      {
        END = 0,
        STRING = 258,
        USERVAR = 259,
        NAME = 260,
        INTNUM = 261,
        BOOL = 262,
        APPROXNUM = 263,
        NOTEQUALS = 264,
        LESSEQ = 265,
        GREATEREQ = 266,
        ASSIGN = 267,
        OR = 268,
        XOR = 269,
        ANDOP = 270,
        IN = 271,
        IS = 272,
        LIKE = 273,
        REGEXP = 274,
        NOT = 275,
        BETWEEN = 276,
        COMPARISON = 277,
        SHIFT = 278,
        MOD = 279,
        UMINUS = 280,
        ADD = 281,
        ALL = 282,
        ALTER = 283,
        ANALYZE = 284,
        AND = 285,
        ANY = 286,
        APPEND = 287,
        AS = 288,
        ASC = 289,
        AUTO_INCREMENT = 290,
        BEFORE = 291,
        BIGINT = 292,
        BINARY = 293,
        BIT = 294,
        BLOB = 295,
        BOTH = 296,
        BY = 297,
        CALL = 298,
        CASCADE = 299,
        CASE = 300,
        CHANGE = 301,
        CHAR = 302,
        CHECK = 303,
        COLLATE = 304,
        COLUMN = 305,
        COMMENT = 306,
        CONDITION = 307,
        CONSTRAINT = 308,
        CONTINUE = 309,
        CONVERT = 310,
        CREATE = 311,
        CROSS = 312,
        CURRENT_DATE = 313,
        CURRENT_TIME = 314,
        CURRENT_TIMESTAMP = 315,
        CURRENT_USER = 316,
        CURSOR = 317,
        DATABASE = 318,
        DATABASES = 319,
        DATE = 320,
        DATETIME = 321,
        DAY_HOUR = 322,
        DAY = 323,
        DAY_MICROSECOND = 324,
        DAY_MINUTE = 325,
        DAY_SECOND = 326,
        DECIMAL = 327,
        DECLARE = 328,
        DEFAULT = 329,
        DELAYED = 330,
        DELETE = 331,
        DESC = 332,
        DESCRIBE = 333,
        DETERMINISTIC = 334,
        DISTINCT = 335,
        DISTINCTROW = 336,
        DIV = 337,
        DOUBLE = 338,
        DROP = 339,
        DUAL = 340,
        EACH = 341,
        ELSE = 342,
        ELSEIF = 343,
        ENCLOSED = 344,
        ENUM = 345,
        ESCAPED = 346,
        EXISTS = 347,
        EXIT = 348,
        EXPLAIN = 349,
        FETCH = 350,
        FLOAT = 351,
        FOR = 352,
        FORCE = 353,
        FOREIGN = 354,
        FROM = 355,
        FULLTEXT = 356,
        GRANT = 357,
        GROUP = 358,
        HAVING = 359,
        HIGH = 360,
        HIGH_PRIORITY = 361,
        HOUR_MICROSECOND = 362,
        HOUR_MINUTE = 363,
        HOUR_SECOND = 364,
        IF = 365,
        IGNORE = 366,
        INDEX = 367,
        INFILE = 368,
        INNER = 369,
        INOUT = 370,
        INSENSITIVE = 371,
        INSERT = 372,
        INT = 373,
        INTEGER = 374,
        INTERVAL = 375,
        INTO = 376,
        ITERATE = 377,
        JOIN = 378,
        KEY = 379,
        KEYS = 380,
        KILL = 381,
        LEADING = 382,
        LEAVE = 383,
        LEFT = 384,
        LIMIT = 385,
        LINES = 386,
        LOAD = 387,
        LOCALTIME = 388,
        LOCALTIMESTAMP = 389,
        LOCK = 390,
        LONG = 391,
        LONGBLOB = 392,
        LONGTEXT = 393,
        LOOP = 394,
        LOW = 395,
        LOW_PRIORITY = 396,
        MATCH = 397,
        MEDIUMBLOB = 398,
        MEDIUMINT = 399,
        MEDIUMTEXT = 400,
        MINUTE_MICROSECOND = 401,
        MINUTE_SECOND = 402,
        MODIFIES = 403,
        NATURAL = 404,
        NO_WRITE_TO_BINLOG = 405,
        NULLX = 406,
        NUMBER = 407,
        ON = 408,
        DUPLICATE = 409,
        OPTIMIZE = 410,
        OPTION = 411,
        OPTIONALLY = 412,
        ORDER = 413,
        OUT = 414,
        OUTER = 415,
        OUTFILE = 416,
        PARTITIONED = 417,
        PRECISION = 418,
        PRIMARY = 419,
        PRIORITY = 420,
        PROCEDURE = 421,
        PROJECTION = 422,
        PURGE = 423,
        QUICK = 424,
        QUARTER = 425,
        READ = 426,
        READS = 427,
        REAL = 428,
        REFERENCES = 429,
        RELEASE = 430,
        RENAME = 431,
        REPEAT = 432,
        REPLACE = 433,
        REQUIRE = 434,
        RESTRICT = 435,
        RETURN = 436,
        REVOKE = 437,
        RIGHT = 438,
        ROLLUP = 439,
        SAMPLE = 440,
        SCHEMA = 441,
        SCHEMAS = 442,
        SECOND_MICROSECOND = 443,
        SELECT = 444,
        SENSITIVE = 445,
        SEPARATOR = 446,
        SET = 447,
        SHOW = 448,
        SMALLINT = 449,
        SOME = 450,
        SONAME = 451,
        SPATIAL = 452,
        SPECIFIC = 453,
        SQL = 454,
        SQLEXCEPTION = 455,
        SQLSTATE = 456,
        SQLWARNING = 457,
        BIG_RESULT = 458,
        CALC_FOUND_ROWS = 459,
        SMALL_RESULT = 460,
        SSL = 461,
        STARTING = 462,
        STRAIGHT_JOIN = 463,
        TABLE = 464,
        TEMPORARY = 465,
        TEXT = 466,
        TERMINATED = 467,
        THEN = 468,
        TIME = 469,
        TIMESTAMP = 470,
        TINYBLOB = 471,
        TINYINT = 472,
        TINYTEXT = 473,
        TO = 474,
        TRAILING = 475,
        TRIGGER = 476,
        UNDO = 477,
        UNION = 478,
        UNIQUE = 479,
        UNLOCK = 480,
        UNSIGNED = 481,
        UPDATE = 482,
        USAGE = 483,
        USE = 484,
        USING = 485,
        UTC_DATE = 486,
        UTC_TIME = 487,
        UTC_TIMESTAMP = 488,
        VALUES = 489,
        VARBINARY = 490,
        VARCHAR = 491,
        VARYING = 492,
        WHEN = 493,
        WHERE = 494,
        WHILE = 495,
        WITH = 496,
        WRITE = 497,
        YEAR = 498,
        YEAR_MONTH = 499,
        ZEROFILL = 500,
        WEEK = 501,
        DO = 502,
        MAX_QUERIES_PER_HOUR = 503,
        MAX_UPDATES_PER_HOUR = 504,
        MAX_CONNECTIONS_PER_HOUR = 505,
        MAX_USER_CONNECTIONS = 506,
        USER = 507,
        TRUNCATE = 508,
        FAST = 509,
        MEDIUM = 510,
        EXTENDED = 511,
        CHANGED = 512,
        LEAVES = 513,
        MASTER = 514,
        QUERY = 515,
        CACHE = 516,
        SLAVE = 517,
        BEGINT = 518,
        COMMIT = 519,
        START = 520,
        TRANSACTION = 521,
        NO = 522,
        CHAIN = 523,
        AUTOCOMMIT = 524,
        SAVEPOINT = 525,
        ROLLBACK = 526,
        LOCAL = 527,
        TABLES = 528,
        ISOLATION = 529,
        LEVEL = 530,
        GLOBAL = 531,
        SESSION = 532,
        UNCOMMITTED = 533,
        COMMITTED = 534,
        REPEATABLE = 535,
        SERIALIZABLE = 536,
        IDENTIFIED = 537,
        PASSWORD = 538,
        PRIVILEGES = 539,
        BACKUP = 540,
        CHECKSUM = 541,
        REPAIR = 542,
        USE_FRM = 543,
        RESTORE = 544,
        CHARACTER = 545,
        COLLATION = 546,
        COLUMNS = 547,
        ENGINE = 548,
        LOGS = 549,
        STATUS = 550,
        STORAGE = 551,
        ENGINES = 552,
        ERRORS = 553,
        GRANTS = 554,
        INNODB = 555,
        PROCESSLIST = 556,
        TRIGGERS = 557,
        VARIABLES = 558,
        WARNINGS = 559,
        FLUSH = 560,
        HOSTS = 561,
        DES_KEY_FILE = 562,
        USER_RESOURCES = 563,
        CONNECTION = 564,
        RESET = 565,
        PREPARE = 566,
        DEALLOCATE = 567,
        EXECUTE = 568,
        WORK = 569,
        BTREE = 570,
        HASH = 571,
        BDB = 572,
        OPEN = 573,
        FULL = 574,
        FSUBSTRING = 575,
        FTRIM = 576,
        FDATE_ADD = 577,
        FDATE_SUB = 578,
        FCOUNT = 579,
        FUPPER = 580,
        FCAST = 581,
        FCOALESCE = 582,
        FCONVERT = 583,
        FSUM = 584,
        FAVG = 585,
        FMIN = 586,
        FMAX = 587,
        BRACKET_O = 588,
        BRACKET_C = 589,
        SEMICOLON = 590,
        DOT = 591,
        MULTIPLY = 592
      };
    };

    /// (External) token type, as returned by yylex.
    typedef token::yytokentype token_type;

    /// Symbol type: an internal symbol number.
    typedef int symbol_number_type;

    /// The symbol type number to denote an empty symbol.
    enum { empty_symbol = -2 };

    /// Internal symbol number for tokens (subsumed by symbol_number_type).
    typedef unsigned short int token_number_type;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol type
    /// via type_get().
    ///
    /// Provide access to semantic value and location.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol ();

      /// Copy constructor.
      basic_symbol (const basic_symbol& other);

      /// Constructor for valueless symbols, and symbols from each type.

  basic_symbol (typename Base::kind_type t, const location_type& l);

  basic_symbol (typename Base::kind_type t, const bool v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const double v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const int v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const sql::SelectStmt::Type v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::pair<std::string, std::string> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<sql::CreateStmt> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<sql::DeleteStmt> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<sql::DropStmt> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<sql::InsertStmt> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<sql::SelectStmt> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<sql::Statement> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<sql::Table> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::shared_ptr<sql::UpdateStmt> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::string v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::tuple<std::string, std::string, std::string> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::vector<std::pair<std::string, std::string>> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::vector<std::shared_ptr<sql::Statement>> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::vector<std::shared_ptr<sql::Table>> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::vector<std::string> v, const location_type& l);

  basic_symbol (typename Base::kind_type t, const std::vector<std::tuple<std::string, std::string, std::string>> v, const location_type& l);


      /// Constructor for symbols with semantic value.
      basic_symbol (typename Base::kind_type t,
                    const semantic_type& v,
                    const location_type& l);

      /// Destroy the symbol.
      ~basic_symbol ();

      /// Destroy contents, and record that is empty.
      void clear ();

      /// Whether empty.
      bool empty () const;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      semantic_type value;

      /// The location.
      location_type location;

    private:
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& other);
    };

    /// Type access provider for token (enum) based symbols.
    struct by_type
    {
      /// Default constructor.
      by_type ();

      /// Copy constructor.
      by_type (const by_type& other);

      /// The symbol type as needed by the constructor.
      typedef token_type kind_type;

      /// Constructor from (external) token numbers.
      by_type (kind_type t);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_type& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_number_type type_get () const;

      /// The token.
      token_type token () const;

      /// The symbol type.
      /// \a empty_symbol when empty.
      /// An int, not token_number_type, to be able to store empty_symbol.
      int type;
    };

    /// "External" symbols: returned by the scanner.
    typedef basic_symbol<by_type> symbol_type;

    // Symbol constructors declarations.
    static inline
    symbol_type
    make_END (const location_type& l);

    static inline
    symbol_type
    make_STRING (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_USERVAR (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_NAME (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_INTNUM (const int& v, const location_type& l);

    static inline
    symbol_type
    make_BOOL (const bool& v, const location_type& l);

    static inline
    symbol_type
    make_APPROXNUM (const double& v, const location_type& l);

    static inline
    symbol_type
    make_NOTEQUALS (const int& v, const location_type& l);

    static inline
    symbol_type
    make_LESSEQ (const int& v, const location_type& l);

    static inline
    symbol_type
    make_GREATEREQ (const int& v, const location_type& l);

    static inline
    symbol_type
    make_ASSIGN (const location_type& l);

    static inline
    symbol_type
    make_OR (const location_type& l);

    static inline
    symbol_type
    make_XOR (const location_type& l);

    static inline
    symbol_type
    make_ANDOP (const location_type& l);

    static inline
    symbol_type
    make_IN (const location_type& l);

    static inline
    symbol_type
    make_IS (const location_type& l);

    static inline
    symbol_type
    make_LIKE (const location_type& l);

    static inline
    symbol_type
    make_REGEXP (const location_type& l);

    static inline
    symbol_type
    make_NOT (const location_type& l);

    static inline
    symbol_type
    make_BETWEEN (const location_type& l);

    static inline
    symbol_type
    make_COMPARISON (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_SHIFT (const std::string& v, const location_type& l);

    static inline
    symbol_type
    make_MOD (const location_type& l);

    static inline
    symbol_type
    make_UMINUS (const location_type& l);

    static inline
    symbol_type
    make_ADD (const location_type& l);

    static inline
    symbol_type
    make_ALL (const location_type& l);

    static inline
    symbol_type
    make_ALTER (const location_type& l);

    static inline
    symbol_type
    make_ANALYZE (const location_type& l);

    static inline
    symbol_type
    make_AND (const location_type& l);

    static inline
    symbol_type
    make_ANY (const location_type& l);

    static inline
    symbol_type
    make_APPEND (const location_type& l);

    static inline
    symbol_type
    make_AS (const location_type& l);

    static inline
    symbol_type
    make_ASC (const location_type& l);

    static inline
    symbol_type
    make_AUTO_INCREMENT (const location_type& l);

    static inline
    symbol_type
    make_BEFORE (const location_type& l);

    static inline
    symbol_type
    make_BIGINT (const location_type& l);

    static inline
    symbol_type
    make_BINARY (const location_type& l);

    static inline
    symbol_type
    make_BIT (const location_type& l);

    static inline
    symbol_type
    make_BLOB (const location_type& l);

    static inline
    symbol_type
    make_BOTH (const location_type& l);

    static inline
    symbol_type
    make_BY (const location_type& l);

    static inline
    symbol_type
    make_CALL (const location_type& l);

    static inline
    symbol_type
    make_CASCADE (const location_type& l);

    static inline
    symbol_type
    make_CASE (const location_type& l);

    static inline
    symbol_type
    make_CHANGE (const location_type& l);

    static inline
    symbol_type
    make_CHAR (const location_type& l);

    static inline
    symbol_type
    make_CHECK (const location_type& l);

    static inline
    symbol_type
    make_COLLATE (const location_type& l);

    static inline
    symbol_type
    make_COLUMN (const location_type& l);

    static inline
    symbol_type
    make_COMMENT (const location_type& l);

    static inline
    symbol_type
    make_CONDITION (const location_type& l);

    static inline
    symbol_type
    make_CONSTRAINT (const location_type& l);

    static inline
    symbol_type
    make_CONTINUE (const location_type& l);

    static inline
    symbol_type
    make_CONVERT (const location_type& l);

    static inline
    symbol_type
    make_CREATE (const location_type& l);

    static inline
    symbol_type
    make_CROSS (const location_type& l);

    static inline
    symbol_type
    make_CURRENT_DATE (const location_type& l);

    static inline
    symbol_type
    make_CURRENT_TIME (const location_type& l);

    static inline
    symbol_type
    make_CURRENT_TIMESTAMP (const location_type& l);

    static inline
    symbol_type
    make_CURRENT_USER (const location_type& l);

    static inline
    symbol_type
    make_CURSOR (const location_type& l);

    static inline
    symbol_type
    make_DATABASE (const location_type& l);

    static inline
    symbol_type
    make_DATABASES (const location_type& l);

    static inline
    symbol_type
    make_DATE (const location_type& l);

    static inline
    symbol_type
    make_DATETIME (const location_type& l);

    static inline
    symbol_type
    make_DAY_HOUR (const location_type& l);

    static inline
    symbol_type
    make_DAY (const location_type& l);

    static inline
    symbol_type
    make_DAY_MICROSECOND (const location_type& l);

    static inline
    symbol_type
    make_DAY_MINUTE (const location_type& l);

    static inline
    symbol_type
    make_DAY_SECOND (const location_type& l);

    static inline
    symbol_type
    make_DECIMAL (const location_type& l);

    static inline
    symbol_type
    make_DECLARE (const location_type& l);

    static inline
    symbol_type
    make_DEFAULT (const location_type& l);

    static inline
    symbol_type
    make_DELAYED (const location_type& l);

    static inline
    symbol_type
    make_DELETE (const location_type& l);

    static inline
    symbol_type
    make_DESC (const location_type& l);

    static inline
    symbol_type
    make_DESCRIBE (const location_type& l);

    static inline
    symbol_type
    make_DETERMINISTIC (const location_type& l);

    static inline
    symbol_type
    make_DISTINCT (const location_type& l);

    static inline
    symbol_type
    make_DISTINCTROW (const location_type& l);

    static inline
    symbol_type
    make_DIV (const location_type& l);

    static inline
    symbol_type
    make_DOUBLE (const location_type& l);

    static inline
    symbol_type
    make_DROP (const location_type& l);

    static inline
    symbol_type
    make_DUAL (const location_type& l);

    static inline
    symbol_type
    make_EACH (const location_type& l);

    static inline
    symbol_type
    make_ELSE (const location_type& l);

    static inline
    symbol_type
    make_ELSEIF (const location_type& l);

    static inline
    symbol_type
    make_ENCLOSED (const location_type& l);

    static inline
    symbol_type
    make_ENUM (const location_type& l);

    static inline
    symbol_type
    make_ESCAPED (const location_type& l);

    static inline
    symbol_type
    make_EXISTS (const location_type& l);

    static inline
    symbol_type
    make_EXIT (const location_type& l);

    static inline
    symbol_type
    make_EXPLAIN (const location_type& l);

    static inline
    symbol_type
    make_FETCH (const location_type& l);

    static inline
    symbol_type
    make_FLOAT (const location_type& l);

    static inline
    symbol_type
    make_FOR (const location_type& l);

    static inline
    symbol_type
    make_FORCE (const location_type& l);

    static inline
    symbol_type
    make_FOREIGN (const location_type& l);

    static inline
    symbol_type
    make_FROM (const location_type& l);

    static inline
    symbol_type
    make_FULLTEXT (const location_type& l);

    static inline
    symbol_type
    make_GRANT (const location_type& l);

    static inline
    symbol_type
    make_GROUP (const location_type& l);

    static inline
    symbol_type
    make_HAVING (const location_type& l);

    static inline
    symbol_type
    make_HIGH (const location_type& l);

    static inline
    symbol_type
    make_HIGH_PRIORITY (const location_type& l);

    static inline
    symbol_type
    make_HOUR_MICROSECOND (const location_type& l);

    static inline
    symbol_type
    make_HOUR_MINUTE (const location_type& l);

    static inline
    symbol_type
    make_HOUR_SECOND (const location_type& l);

    static inline
    symbol_type
    make_IF (const location_type& l);

    static inline
    symbol_type
    make_IGNORE (const location_type& l);

    static inline
    symbol_type
    make_INDEX (const location_type& l);

    static inline
    symbol_type
    make_INFILE (const location_type& l);

    static inline
    symbol_type
    make_INNER (const location_type& l);

    static inline
    symbol_type
    make_INOUT (const location_type& l);

    static inline
    symbol_type
    make_INSENSITIVE (const location_type& l);

    static inline
    symbol_type
    make_INSERT (const location_type& l);

    static inline
    symbol_type
    make_INT (const location_type& l);

    static inline
    symbol_type
    make_INTEGER (const location_type& l);

    static inline
    symbol_type
    make_INTERVAL (const location_type& l);

    static inline
    symbol_type
    make_INTO (const location_type& l);

    static inline
    symbol_type
    make_ITERATE (const location_type& l);

    static inline
    symbol_type
    make_JOIN (const location_type& l);

    static inline
    symbol_type
    make_KEY (const location_type& l);

    static inline
    symbol_type
    make_KEYS (const location_type& l);

    static inline
    symbol_type
    make_KILL (const location_type& l);

    static inline
    symbol_type
    make_LEADING (const location_type& l);

    static inline
    symbol_type
    make_LEAVE (const location_type& l);

    static inline
    symbol_type
    make_LEFT (const location_type& l);

    static inline
    symbol_type
    make_LIMIT (const location_type& l);

    static inline
    symbol_type
    make_LINES (const location_type& l);

    static inline
    symbol_type
    make_LOAD (const location_type& l);

    static inline
    symbol_type
    make_LOCALTIME (const location_type& l);

    static inline
    symbol_type
    make_LOCALTIMESTAMP (const location_type& l);

    static inline
    symbol_type
    make_LOCK (const location_type& l);

    static inline
    symbol_type
    make_LONG (const location_type& l);

    static inline
    symbol_type
    make_LONGBLOB (const location_type& l);

    static inline
    symbol_type
    make_LONGTEXT (const location_type& l);

    static inline
    symbol_type
    make_LOOP (const location_type& l);

    static inline
    symbol_type
    make_LOW (const location_type& l);

    static inline
    symbol_type
    make_LOW_PRIORITY (const location_type& l);

    static inline
    symbol_type
    make_MATCH (const location_type& l);

    static inline
    symbol_type
    make_MEDIUMBLOB (const location_type& l);

    static inline
    symbol_type
    make_MEDIUMINT (const location_type& l);

    static inline
    symbol_type
    make_MEDIUMTEXT (const location_type& l);

    static inline
    symbol_type
    make_MINUTE_MICROSECOND (const location_type& l);

    static inline
    symbol_type
    make_MINUTE_SECOND (const location_type& l);

    static inline
    symbol_type
    make_MODIFIES (const location_type& l);

    static inline
    symbol_type
    make_NATURAL (const location_type& l);

    static inline
    symbol_type
    make_NO_WRITE_TO_BINLOG (const location_type& l);

    static inline
    symbol_type
    make_NULLX (const location_type& l);

    static inline
    symbol_type
    make_NUMBER (const location_type& l);

    static inline
    symbol_type
    make_ON (const location_type& l);

    static inline
    symbol_type
    make_DUPLICATE (const location_type& l);

    static inline
    symbol_type
    make_OPTIMIZE (const location_type& l);

    static inline
    symbol_type
    make_OPTION (const location_type& l);

    static inline
    symbol_type
    make_OPTIONALLY (const location_type& l);

    static inline
    symbol_type
    make_ORDER (const location_type& l);

    static inline
    symbol_type
    make_OUT (const location_type& l);

    static inline
    symbol_type
    make_OUTER (const location_type& l);

    static inline
    symbol_type
    make_OUTFILE (const location_type& l);

    static inline
    symbol_type
    make_PARTITIONED (const location_type& l);

    static inline
    symbol_type
    make_PRECISION (const location_type& l);

    static inline
    symbol_type
    make_PRIMARY (const location_type& l);

    static inline
    symbol_type
    make_PRIORITY (const location_type& l);

    static inline
    symbol_type
    make_PROCEDURE (const location_type& l);

    static inline
    symbol_type
    make_PROJECTION (const location_type& l);

    static inline
    symbol_type
    make_PURGE (const location_type& l);

    static inline
    symbol_type
    make_QUICK (const location_type& l);

    static inline
    symbol_type
    make_QUARTER (const location_type& l);

    static inline
    symbol_type
    make_READ (const location_type& l);

    static inline
    symbol_type
    make_READS (const location_type& l);

    static inline
    symbol_type
    make_REAL (const location_type& l);

    static inline
    symbol_type
    make_REFERENCES (const location_type& l);

    static inline
    symbol_type
    make_RELEASE (const location_type& l);

    static inline
    symbol_type
    make_RENAME (const location_type& l);

    static inline
    symbol_type
    make_REPEAT (const location_type& l);

    static inline
    symbol_type
    make_REPLACE (const location_type& l);

    static inline
    symbol_type
    make_REQUIRE (const location_type& l);

    static inline
    symbol_type
    make_RESTRICT (const location_type& l);

    static inline
    symbol_type
    make_RETURN (const location_type& l);

    static inline
    symbol_type
    make_REVOKE (const location_type& l);

    static inline
    symbol_type
    make_RIGHT (const location_type& l);

    static inline
    symbol_type
    make_ROLLUP (const location_type& l);

    static inline
    symbol_type
    make_SAMPLE (const location_type& l);

    static inline
    symbol_type
    make_SCHEMA (const location_type& l);

    static inline
    symbol_type
    make_SCHEMAS (const location_type& l);

    static inline
    symbol_type
    make_SECOND_MICROSECOND (const location_type& l);

    static inline
    symbol_type
    make_SELECT (const location_type& l);

    static inline
    symbol_type
    make_SENSITIVE (const location_type& l);

    static inline
    symbol_type
    make_SEPARATOR (const location_type& l);

    static inline
    symbol_type
    make_SET (const location_type& l);

    static inline
    symbol_type
    make_SHOW (const location_type& l);

    static inline
    symbol_type
    make_SMALLINT (const location_type& l);

    static inline
    symbol_type
    make_SOME (const location_type& l);

    static inline
    symbol_type
    make_SONAME (const location_type& l);

    static inline
    symbol_type
    make_SPATIAL (const location_type& l);

    static inline
    symbol_type
    make_SPECIFIC (const location_type& l);

    static inline
    symbol_type
    make_SQL (const location_type& l);

    static inline
    symbol_type
    make_SQLEXCEPTION (const location_type& l);

    static inline
    symbol_type
    make_SQLSTATE (const location_type& l);

    static inline
    symbol_type
    make_SQLWARNING (const location_type& l);

    static inline
    symbol_type
    make_BIG_RESULT (const location_type& l);

    static inline
    symbol_type
    make_CALC_FOUND_ROWS (const location_type& l);

    static inline
    symbol_type
    make_SMALL_RESULT (const location_type& l);

    static inline
    symbol_type
    make_SSL (const location_type& l);

    static inline
    symbol_type
    make_STARTING (const location_type& l);

    static inline
    symbol_type
    make_STRAIGHT_JOIN (const location_type& l);

    static inline
    symbol_type
    make_TABLE (const location_type& l);

    static inline
    symbol_type
    make_TEMPORARY (const location_type& l);

    static inline
    symbol_type
    make_TEXT (const location_type& l);

    static inline
    symbol_type
    make_TERMINATED (const location_type& l);

    static inline
    symbol_type
    make_THEN (const location_type& l);

    static inline
    symbol_type
    make_TIME (const location_type& l);

    static inline
    symbol_type
    make_TIMESTAMP (const location_type& l);

    static inline
    symbol_type
    make_TINYBLOB (const location_type& l);

    static inline
    symbol_type
    make_TINYINT (const location_type& l);

    static inline
    symbol_type
    make_TINYTEXT (const location_type& l);

    static inline
    symbol_type
    make_TO (const location_type& l);

    static inline
    symbol_type
    make_TRAILING (const location_type& l);

    static inline
    symbol_type
    make_TRIGGER (const location_type& l);

    static inline
    symbol_type
    make_UNDO (const location_type& l);

    static inline
    symbol_type
    make_UNION (const location_type& l);

    static inline
    symbol_type
    make_UNIQUE (const location_type& l);

    static inline
    symbol_type
    make_UNLOCK (const location_type& l);

    static inline
    symbol_type
    make_UNSIGNED (const location_type& l);

    static inline
    symbol_type
    make_UPDATE (const location_type& l);

    static inline
    symbol_type
    make_USAGE (const location_type& l);

    static inline
    symbol_type
    make_USE (const location_type& l);

    static inline
    symbol_type
    make_USING (const location_type& l);

    static inline
    symbol_type
    make_UTC_DATE (const location_type& l);

    static inline
    symbol_type
    make_UTC_TIME (const location_type& l);

    static inline
    symbol_type
    make_UTC_TIMESTAMP (const location_type& l);

    static inline
    symbol_type
    make_VALUES (const location_type& l);

    static inline
    symbol_type
    make_VARBINARY (const location_type& l);

    static inline
    symbol_type
    make_VARCHAR (const location_type& l);

    static inline
    symbol_type
    make_VARYING (const location_type& l);

    static inline
    symbol_type
    make_WHEN (const location_type& l);

    static inline
    symbol_type
    make_WHERE (const location_type& l);

    static inline
    symbol_type
    make_WHILE (const location_type& l);

    static inline
    symbol_type
    make_WITH (const location_type& l);

    static inline
    symbol_type
    make_WRITE (const location_type& l);

    static inline
    symbol_type
    make_YEAR (const location_type& l);

    static inline
    symbol_type
    make_YEAR_MONTH (const location_type& l);

    static inline
    symbol_type
    make_ZEROFILL (const location_type& l);

    static inline
    symbol_type
    make_WEEK (const location_type& l);

    static inline
    symbol_type
    make_DO (const location_type& l);

    static inline
    symbol_type
    make_MAX_QUERIES_PER_HOUR (const location_type& l);

    static inline
    symbol_type
    make_MAX_UPDATES_PER_HOUR (const location_type& l);

    static inline
    symbol_type
    make_MAX_CONNECTIONS_PER_HOUR (const location_type& l);

    static inline
    symbol_type
    make_MAX_USER_CONNECTIONS (const location_type& l);

    static inline
    symbol_type
    make_USER (const location_type& l);

    static inline
    symbol_type
    make_TRUNCATE (const location_type& l);

    static inline
    symbol_type
    make_FAST (const location_type& l);

    static inline
    symbol_type
    make_MEDIUM (const location_type& l);

    static inline
    symbol_type
    make_EXTENDED (const location_type& l);

    static inline
    symbol_type
    make_CHANGED (const location_type& l);

    static inline
    symbol_type
    make_LEAVES (const location_type& l);

    static inline
    symbol_type
    make_MASTER (const location_type& l);

    static inline
    symbol_type
    make_QUERY (const location_type& l);

    static inline
    symbol_type
    make_CACHE (const location_type& l);

    static inline
    symbol_type
    make_SLAVE (const location_type& l);

    static inline
    symbol_type
    make_BEGINT (const location_type& l);

    static inline
    symbol_type
    make_COMMIT (const location_type& l);

    static inline
    symbol_type
    make_START (const location_type& l);

    static inline
    symbol_type
    make_TRANSACTION (const location_type& l);

    static inline
    symbol_type
    make_NO (const location_type& l);

    static inline
    symbol_type
    make_CHAIN (const location_type& l);

    static inline
    symbol_type
    make_AUTOCOMMIT (const location_type& l);

    static inline
    symbol_type
    make_SAVEPOINT (const location_type& l);

    static inline
    symbol_type
    make_ROLLBACK (const location_type& l);

    static inline
    symbol_type
    make_LOCAL (const location_type& l);

    static inline
    symbol_type
    make_TABLES (const location_type& l);

    static inline
    symbol_type
    make_ISOLATION (const location_type& l);

    static inline
    symbol_type
    make_LEVEL (const location_type& l);

    static inline
    symbol_type
    make_GLOBAL (const location_type& l);

    static inline
    symbol_type
    make_SESSION (const location_type& l);

    static inline
    symbol_type
    make_UNCOMMITTED (const location_type& l);

    static inline
    symbol_type
    make_COMMITTED (const location_type& l);

    static inline
    symbol_type
    make_REPEATABLE (const location_type& l);

    static inline
    symbol_type
    make_SERIALIZABLE (const location_type& l);

    static inline
    symbol_type
    make_IDENTIFIED (const location_type& l);

    static inline
    symbol_type
    make_PASSWORD (const location_type& l);

    static inline
    symbol_type
    make_PRIVILEGES (const location_type& l);

    static inline
    symbol_type
    make_BACKUP (const location_type& l);

    static inline
    symbol_type
    make_CHECKSUM (const location_type& l);

    static inline
    symbol_type
    make_REPAIR (const location_type& l);

    static inline
    symbol_type
    make_USE_FRM (const location_type& l);

    static inline
    symbol_type
    make_RESTORE (const location_type& l);

    static inline
    symbol_type
    make_CHARACTER (const location_type& l);

    static inline
    symbol_type
    make_COLLATION (const location_type& l);

    static inline
    symbol_type
    make_COLUMNS (const location_type& l);

    static inline
    symbol_type
    make_ENGINE (const location_type& l);

    static inline
    symbol_type
    make_LOGS (const location_type& l);

    static inline
    symbol_type
    make_STATUS (const location_type& l);

    static inline
    symbol_type
    make_STORAGE (const location_type& l);

    static inline
    symbol_type
    make_ENGINES (const location_type& l);

    static inline
    symbol_type
    make_ERRORS (const location_type& l);

    static inline
    symbol_type
    make_GRANTS (const location_type& l);

    static inline
    symbol_type
    make_INNODB (const location_type& l);

    static inline
    symbol_type
    make_PROCESSLIST (const location_type& l);

    static inline
    symbol_type
    make_TRIGGERS (const location_type& l);

    static inline
    symbol_type
    make_VARIABLES (const location_type& l);

    static inline
    symbol_type
    make_WARNINGS (const location_type& l);

    static inline
    symbol_type
    make_FLUSH (const location_type& l);

    static inline
    symbol_type
    make_HOSTS (const location_type& l);

    static inline
    symbol_type
    make_DES_KEY_FILE (const location_type& l);

    static inline
    symbol_type
    make_USER_RESOURCES (const location_type& l);

    static inline
    symbol_type
    make_CONNECTION (const location_type& l);

    static inline
    symbol_type
    make_RESET (const location_type& l);

    static inline
    symbol_type
    make_PREPARE (const location_type& l);

    static inline
    symbol_type
    make_DEALLOCATE (const location_type& l);

    static inline
    symbol_type
    make_EXECUTE (const location_type& l);

    static inline
    symbol_type
    make_WORK (const location_type& l);

    static inline
    symbol_type
    make_BTREE (const location_type& l);

    static inline
    symbol_type
    make_HASH (const location_type& l);

    static inline
    symbol_type
    make_BDB (const location_type& l);

    static inline
    symbol_type
    make_OPEN (const location_type& l);

    static inline
    symbol_type
    make_FULL (const location_type& l);

    static inline
    symbol_type
    make_FSUBSTRING (const location_type& l);

    static inline
    symbol_type
    make_FTRIM (const location_type& l);

    static inline
    symbol_type
    make_FDATE_ADD (const location_type& l);

    static inline
    symbol_type
    make_FDATE_SUB (const location_type& l);

    static inline
    symbol_type
    make_FCOUNT (const location_type& l);

    static inline
    symbol_type
    make_FUPPER (const location_type& l);

    static inline
    symbol_type
    make_FCAST (const location_type& l);

    static inline
    symbol_type
    make_FCOALESCE (const location_type& l);

    static inline
    symbol_type
    make_FCONVERT (const location_type& l);

    static inline
    symbol_type
    make_FSUM (const location_type& l);

    static inline
    symbol_type
    make_FAVG (const location_type& l);

    static inline
    symbol_type
    make_FMIN (const location_type& l);

    static inline
    symbol_type
    make_FMAX (const location_type& l);

    static inline
    symbol_type
    make_BRACKET_O (const location_type& l);

    static inline
    symbol_type
    make_BRACKET_C (const location_type& l);

    static inline
    symbol_type
    make_SEMICOLON (const location_type& l);

    static inline
    symbol_type
    make_DOT (const location_type& l);

    static inline
    symbol_type
    make_MULTIPLY (const location_type& l);


    /// Build a parser object.
    Parser (Driver &driver_yyarg);
    virtual ~Parser ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param loc    where the syntax error is found.
    /// \param msg    a description of the syntax error.
    virtual void error (const location_type& loc, const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

  private:
    /// This class is not copyable.
    Parser (const Parser&);
    Parser& operator= (const Parser&);

    /// State numbers.
    typedef int state_type;

    /// Generate an error message.
    /// \param yystate   the state where the error occurred.
    /// \param yyla      the lookahead token.
    virtual std::string yysyntax_error_ (state_type yystate,
                                         const symbol_type& yyla) const;

    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue);

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue);

    static const short int yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token number \a t to a symbol number.
    static token_number_type yytranslate_ (token_type t);

    // Tables.
  // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
  // STATE-NUM.
  static const short int yypact_[];

  // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
  // Performed when YYTABLE does not specify something else to do.  Zero
  // means the default is an error.
  static const unsigned char yydefact_[];

  // YYPGOTO[NTERM-NUM].
  static const short int yypgoto_[];

  // YYDEFGOTO[NTERM-NUM].
  static const short int yydefgoto_[];

  // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
  // positive, shift that token.  If negative, reduce the rule whose
  // number is the opposite.  If YYTABLE_NINF, syntax error.
  static const short int yytable_[];

  static const short int yycheck_[];

  // YYSTOS[STATE-NUM] -- The (internal number of the) accessing
  // symbol of state STATE-NUM.
  static const unsigned short int yystos_[];

  // YYR1[YYN] -- Symbol number of symbol that rule YYN derives.
  static const unsigned short int yyr1_[];

  // YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.
  static const unsigned char yyr2_[];


    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *n);


    /// For a symbol, its name in clear.
    static const char* const yytname_[];
#if YYDEBUG
  // YYRLINE[YYN] -- Source line where rule number YYN was defined.
  static const unsigned short int yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r);
    /// Print the state stack on the debug stream.
    virtual void yystack_print_ ();

    // Debugging.
    int yydebug_;
    std::ostream* yycdebug_;

    /// \brief Display a symbol type, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state ();

      /// The symbol type as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s);

      /// Copy constructor.
      by_state (const by_state& other);

      /// Record that this symbol is empty.
      void clear ();

      /// Steal the symbol type from \a that.
      void move (by_state& that);

      /// The (internal) type number (corresponding to \a state).
      /// \a empty_symbol when empty.
      symbol_number_type type_get () const;

      /// The state number used to denote an empty symbol.
      enum { empty_state = -1 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, symbol_type& sym);
      /// Assignment, needed by push_back.
      stack_symbol_type& operator= (const stack_symbol_type& that);
    };

    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, stack_symbol_type& s);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, state_type s, symbol_type& sym);

    /// Pop \a n symbols the three stacks.
    void yypop_ (unsigned int n = 1);

    /// Constants.
    enum
    {
      yyeof_ = 0,
      yylast_ = 348,     ///< Last index in yytable_.
      yynnts_ = 34,  ///< Number of nonterminal symbols.
      yyfinal_ = 43, ///< Termination state number.
      yyterror_ = 1,
      yyerrcode_ = 256,
      yyntokens_ = 338  ///< Number of tokens.
    };


    // User arguments.
    Driver &driver;
  };

  // Symbol number corresponding to token number t.
  inline
  Parser::token_number_type
  Parser::yytranslate_ (token_type t)
  {
    static
    const token_number_type
    translate_table[] =
    {
     0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
     175,   176,   177,   178,   179,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   209,   210,   211,   212,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
     245,   246,   247,   248,   249,   250,   251,   252,   253,   254,
     255,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337
    };
    const unsigned int user_token_number_max_ = 592;
    const token_number_type undef_token_ = 2;

    if (static_cast<int>(t) <= yyeof_)
      return yyeof_;
    else if (static_cast<unsigned int> (t) <= user_token_number_max_)
      return translate_table[t];
    else
      return undef_token_;
  }

  inline
  Parser::syntax_error::syntax_error (const location_type& l, const std::string& m)
    : std::runtime_error (m)
    , location (l)
  {}

  // basic_symbol.
  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol ()
    : value ()
  {}

  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& other)
    : Base (other)
    , value ()
    , location (other.location)
  {
      switch (other.type_get ())
    {
      case 7: // BOOL
      case 363: // opt_if_not_exists
        value.copy< bool > (other.value);
        break;

      case 8: // APPROXNUM
        value.copy< double > (other.value);
        break;

      case 6: // INTNUM
      case 9: // NOTEQUALS
      case 10: // LESSEQ
      case 11: // GREATEREQ
      case 369: // opt_limit
        value.copy< int > (other.value);
        break;

      case 348: // select_opts
      case 351: // join_opts
        value.copy< sql::SelectStmt::Type > (other.value);
        break;

      case 344: // expr_pair
        value.copy< std::pair<std::string, std::string> > (other.value);
        break;

      case 355: // create_stmt
        value.copy< std::shared_ptr<sql::CreateStmt> > (other.value);
        break;

      case 352: // delete_stmt
        value.copy< std::shared_ptr<sql::DeleteStmt> > (other.value);
        break;

      case 358: // drop_stmt
        value.copy< std::shared_ptr<sql::DropStmt> > (other.value);
        break;

      case 353: // insert_stmt
        value.copy< std::shared_ptr<sql::InsertStmt> > (other.value);
        break;

      case 347: // select_stmt
      case 349: // join_table
        value.copy< std::shared_ptr<sql::SelectStmt> > (other.value);
        break;

      case 346: // stmt
        value.copy< std::shared_ptr<sql::Statement> > (other.value);
        break;

      case 371: // table_factor
        value.copy< std::shared_ptr<sql::Table> > (other.value);
        break;

      case 354: // update_stmt
        value.copy< std::shared_ptr<sql::UpdateStmt> > (other.value);
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
        value.copy< std::string > (other.value);
        break;

      case 342: // expr
      case 357: // create_definition
        value.copy< std::tuple<std::string, std::string, std::string> > (other.value);
        break;

      case 345: // pair_list
      case 365: // opt_ondupupdate
        value.copy< std::vector<std::pair<std::string, std::string>> > (other.value);
        break;

      case 340: // stmt_list
        value.copy< std::vector<std::shared_ptr<sql::Statement>> > (other.value);
        break;

      case 370: // table_references
        value.copy< std::vector<std::shared_ptr<sql::Table>> > (other.value);
        break;

      case 359: // string_list
      case 367: // opt_groupby
      case 368: // opt_orderby
        value.copy< std::vector<std::string> > (other.value);
        break;

      case 343: // expr_list
      case 350: // join_condition
      case 356: // create_col_list
      case 366: // opt_where
        value.copy< std::vector<std::tuple<std::string, std::string, std::string>> > (other.value);
        break;

      default:
        break;
    }

  }


  template <typename Base>
  inline
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const semantic_type& v, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {
    (void) v;
      switch (this->type_get ())
    {
      case 7: // BOOL
      case 363: // opt_if_not_exists
        value.copy< bool > (v);
        break;

      case 8: // APPROXNUM
        value.copy< double > (v);
        break;

      case 6: // INTNUM
      case 9: // NOTEQUALS
      case 10: // LESSEQ
      case 11: // GREATEREQ
      case 369: // opt_limit
        value.copy< int > (v);
        break;

      case 348: // select_opts
      case 351: // join_opts
        value.copy< sql::SelectStmt::Type > (v);
        break;

      case 344: // expr_pair
        value.copy< std::pair<std::string, std::string> > (v);
        break;

      case 355: // create_stmt
        value.copy< std::shared_ptr<sql::CreateStmt> > (v);
        break;

      case 352: // delete_stmt
        value.copy< std::shared_ptr<sql::DeleteStmt> > (v);
        break;

      case 358: // drop_stmt
        value.copy< std::shared_ptr<sql::DropStmt> > (v);
        break;

      case 353: // insert_stmt
        value.copy< std::shared_ptr<sql::InsertStmt> > (v);
        break;

      case 347: // select_stmt
      case 349: // join_table
        value.copy< std::shared_ptr<sql::SelectStmt> > (v);
        break;

      case 346: // stmt
        value.copy< std::shared_ptr<sql::Statement> > (v);
        break;

      case 371: // table_factor
        value.copy< std::shared_ptr<sql::Table> > (v);
        break;

      case 354: // update_stmt
        value.copy< std::shared_ptr<sql::UpdateStmt> > (v);
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
        value.copy< std::string > (v);
        break;

      case 342: // expr
      case 357: // create_definition
        value.copy< std::tuple<std::string, std::string, std::string> > (v);
        break;

      case 345: // pair_list
      case 365: // opt_ondupupdate
        value.copy< std::vector<std::pair<std::string, std::string>> > (v);
        break;

      case 340: // stmt_list
        value.copy< std::vector<std::shared_ptr<sql::Statement>> > (v);
        break;

      case 370: // table_references
        value.copy< std::vector<std::shared_ptr<sql::Table>> > (v);
        break;

      case 359: // string_list
      case 367: // opt_groupby
      case 368: // opt_orderby
        value.copy< std::vector<std::string> > (v);
        break;

      case 343: // expr_list
      case 350: // join_condition
      case 356: // create_col_list
      case 366: // opt_where
        value.copy< std::vector<std::tuple<std::string, std::string, std::string>> > (v);
        break;

      default:
        break;
    }
}


  // Implementation of basic_symbol constructor for each type.

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const location_type& l)
    : Base (t)
    , value ()
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const bool v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const double v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const int v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const sql::SelectStmt::Type v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::pair<std::string, std::string> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<sql::CreateStmt> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<sql::DeleteStmt> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<sql::DropStmt> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<sql::InsertStmt> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<sql::SelectStmt> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<sql::Statement> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<sql::Table> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::shared_ptr<sql::UpdateStmt> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::string v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::tuple<std::string, std::string, std::string> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector<std::pair<std::string, std::string>> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector<std::shared_ptr<sql::Statement>> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector<std::shared_ptr<sql::Table>> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector<std::string> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}

  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (typename Base::kind_type t, const std::vector<std::tuple<std::string, std::string, std::string>> v, const location_type& l)
    : Base (t)
    , value (v)
    , location (l)
  {}


  template <typename Base>
  inline
  Parser::basic_symbol<Base>::~basic_symbol ()
  {
    clear ();
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::clear ()
  {
    // User destructor.
    symbol_number_type yytype = this->type_get ();
    basic_symbol<Base>& yysym = *this;
    (void) yysym;
    switch (yytype)
    {
   default:
      break;
    }

    // Type destructor.
    switch (yytype)
    {
      case 7: // BOOL
      case 363: // opt_if_not_exists
        value.template destroy< bool > ();
        break;

      case 8: // APPROXNUM
        value.template destroy< double > ();
        break;

      case 6: // INTNUM
      case 9: // NOTEQUALS
      case 10: // LESSEQ
      case 11: // GREATEREQ
      case 369: // opt_limit
        value.template destroy< int > ();
        break;

      case 348: // select_opts
      case 351: // join_opts
        value.template destroy< sql::SelectStmt::Type > ();
        break;

      case 344: // expr_pair
        value.template destroy< std::pair<std::string, std::string> > ();
        break;

      case 355: // create_stmt
        value.template destroy< std::shared_ptr<sql::CreateStmt> > ();
        break;

      case 352: // delete_stmt
        value.template destroy< std::shared_ptr<sql::DeleteStmt> > ();
        break;

      case 358: // drop_stmt
        value.template destroy< std::shared_ptr<sql::DropStmt> > ();
        break;

      case 353: // insert_stmt
        value.template destroy< std::shared_ptr<sql::InsertStmt> > ();
        break;

      case 347: // select_stmt
      case 349: // join_table
        value.template destroy< std::shared_ptr<sql::SelectStmt> > ();
        break;

      case 346: // stmt
        value.template destroy< std::shared_ptr<sql::Statement> > ();
        break;

      case 371: // table_factor
        value.template destroy< std::shared_ptr<sql::Table> > ();
        break;

      case 354: // update_stmt
        value.template destroy< std::shared_ptr<sql::UpdateStmt> > ();
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
        value.template destroy< std::string > ();
        break;

      case 342: // expr
      case 357: // create_definition
        value.template destroy< std::tuple<std::string, std::string, std::string> > ();
        break;

      case 345: // pair_list
      case 365: // opt_ondupupdate
        value.template destroy< std::vector<std::pair<std::string, std::string>> > ();
        break;

      case 340: // stmt_list
        value.template destroy< std::vector<std::shared_ptr<sql::Statement>> > ();
        break;

      case 370: // table_references
        value.template destroy< std::vector<std::shared_ptr<sql::Table>> > ();
        break;

      case 359: // string_list
      case 367: // opt_groupby
      case 368: // opt_orderby
        value.template destroy< std::vector<std::string> > ();
        break;

      case 343: // expr_list
      case 350: // join_condition
      case 356: // create_col_list
      case 366: // opt_where
        value.template destroy< std::vector<std::tuple<std::string, std::string, std::string>> > ();
        break;

      default:
        break;
    }

    Base::clear ();
  }

  template <typename Base>
  inline
  bool
  Parser::basic_symbol<Base>::empty () const
  {
    return Base::type_get () == empty_symbol;
  }

  template <typename Base>
  inline
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move(s);
      switch (this->type_get ())
    {
      case 7: // BOOL
      case 363: // opt_if_not_exists
        value.move< bool > (s.value);
        break;

      case 8: // APPROXNUM
        value.move< double > (s.value);
        break;

      case 6: // INTNUM
      case 9: // NOTEQUALS
      case 10: // LESSEQ
      case 11: // GREATEREQ
      case 369: // opt_limit
        value.move< int > (s.value);
        break;

      case 348: // select_opts
      case 351: // join_opts
        value.move< sql::SelectStmt::Type > (s.value);
        break;

      case 344: // expr_pair
        value.move< std::pair<std::string, std::string> > (s.value);
        break;

      case 355: // create_stmt
        value.move< std::shared_ptr<sql::CreateStmt> > (s.value);
        break;

      case 352: // delete_stmt
        value.move< std::shared_ptr<sql::DeleteStmt> > (s.value);
        break;

      case 358: // drop_stmt
        value.move< std::shared_ptr<sql::DropStmt> > (s.value);
        break;

      case 353: // insert_stmt
        value.move< std::shared_ptr<sql::InsertStmt> > (s.value);
        break;

      case 347: // select_stmt
      case 349: // join_table
        value.move< std::shared_ptr<sql::SelectStmt> > (s.value);
        break;

      case 346: // stmt
        value.move< std::shared_ptr<sql::Statement> > (s.value);
        break;

      case 371: // table_factor
        value.move< std::shared_ptr<sql::Table> > (s.value);
        break;

      case 354: // update_stmt
        value.move< std::shared_ptr<sql::UpdateStmt> > (s.value);
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
        value.move< std::string > (s.value);
        break;

      case 342: // expr
      case 357: // create_definition
        value.move< std::tuple<std::string, std::string, std::string> > (s.value);
        break;

      case 345: // pair_list
      case 365: // opt_ondupupdate
        value.move< std::vector<std::pair<std::string, std::string>> > (s.value);
        break;

      case 340: // stmt_list
        value.move< std::vector<std::shared_ptr<sql::Statement>> > (s.value);
        break;

      case 370: // table_references
        value.move< std::vector<std::shared_ptr<sql::Table>> > (s.value);
        break;

      case 359: // string_list
      case 367: // opt_groupby
      case 368: // opt_orderby
        value.move< std::vector<std::string> > (s.value);
        break;

      case 343: // expr_list
      case 350: // join_condition
      case 356: // create_col_list
      case 366: // opt_where
        value.move< std::vector<std::tuple<std::string, std::string, std::string>> > (s.value);
        break;

      default:
        break;
    }

    location = s.location;
  }

  // by_type.
  inline
  Parser::by_type::by_type ()
    : type (empty_symbol)
  {}

  inline
  Parser::by_type::by_type (const by_type& other)
    : type (other.type)
  {}

  inline
  Parser::by_type::by_type (token_type t)
    : type (yytranslate_ (t))
  {}

  inline
  void
  Parser::by_type::clear ()
  {
    type = empty_symbol;
  }

  inline
  void
  Parser::by_type::move (by_type& that)
  {
    type = that.type;
    that.clear ();
  }

  inline
  int
  Parser::by_type::type_get () const
  {
    return type;
  }

  inline
  Parser::token_type
  Parser::by_type::token () const
  {
    // YYTOKNUM[NUM] -- (External) token number corresponding to the
    // (internal) symbol number NUM (which must be that of a token).  */
    static
    const unsigned short int
    yytoken_number_[] =
    {
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   381,   382,   383,   384,
     385,   386,   387,   388,   389,   390,   391,   392,   393,   394,
     395,   396,   397,   398,   399,   400,   401,   402,   403,   404,
     405,   406,   407,   408,   409,   410,   411,   412,   413,   414,
     415,   416,   417,   418,   419,   420,   421,   422,   423,   424,
     425,   426,   427,   428,   429,   430,   431,   432,   433,   434,
     435,   436,   437,   438,   439,   440,   441,   442,   443,   444,
     445,   446,   447,   448,   449,   450,   451,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   510,   511,   512,   513,   514,
     515,   516,   517,   518,   519,   520,   521,   522,   523,   524,
     525,   526,   527,   528,   529,   530,   531,   532,   533,   534,
     535,   536,   537,   538,   539,   540,   541,   542,   543,   544,
     545,   546,   547,   548,   549,   550,   551,   552,   553,   554,
     555,   556,   557,   558,   559,   560,   561,   562,   563,   564,
     565,   566,   567,   568,   569,   570,   571,   572,   573,   574,
     575,   576,   577,   578,   579,   580,   581,   582,   583,   584,
     585,   586,   587,   588,   589,   590,   591,   592
    };
    return static_cast<token_type> (yytoken_number_[type]);
  }
  // Implementation of make_symbol for each symbol type.
  Parser::symbol_type
  Parser::make_END (const location_type& l)
  {
    return symbol_type (token::END, l);
  }

  Parser::symbol_type
  Parser::make_STRING (const std::string& v, const location_type& l)
  {
    return symbol_type (token::STRING, v, l);
  }

  Parser::symbol_type
  Parser::make_USERVAR (const std::string& v, const location_type& l)
  {
    return symbol_type (token::USERVAR, v, l);
  }

  Parser::symbol_type
  Parser::make_NAME (const std::string& v, const location_type& l)
  {
    return symbol_type (token::NAME, v, l);
  }

  Parser::symbol_type
  Parser::make_INTNUM (const int& v, const location_type& l)
  {
    return symbol_type (token::INTNUM, v, l);
  }

  Parser::symbol_type
  Parser::make_BOOL (const bool& v, const location_type& l)
  {
    return symbol_type (token::BOOL, v, l);
  }

  Parser::symbol_type
  Parser::make_APPROXNUM (const double& v, const location_type& l)
  {
    return symbol_type (token::APPROXNUM, v, l);
  }

  Parser::symbol_type
  Parser::make_NOTEQUALS (const int& v, const location_type& l)
  {
    return symbol_type (token::NOTEQUALS, v, l);
  }

  Parser::symbol_type
  Parser::make_LESSEQ (const int& v, const location_type& l)
  {
    return symbol_type (token::LESSEQ, v, l);
  }

  Parser::symbol_type
  Parser::make_GREATEREQ (const int& v, const location_type& l)
  {
    return symbol_type (token::GREATEREQ, v, l);
  }

  Parser::symbol_type
  Parser::make_ASSIGN (const location_type& l)
  {
    return symbol_type (token::ASSIGN, l);
  }

  Parser::symbol_type
  Parser::make_OR (const location_type& l)
  {
    return symbol_type (token::OR, l);
  }

  Parser::symbol_type
  Parser::make_XOR (const location_type& l)
  {
    return symbol_type (token::XOR, l);
  }

  Parser::symbol_type
  Parser::make_ANDOP (const location_type& l)
  {
    return symbol_type (token::ANDOP, l);
  }

  Parser::symbol_type
  Parser::make_IN (const location_type& l)
  {
    return symbol_type (token::IN, l);
  }

  Parser::symbol_type
  Parser::make_IS (const location_type& l)
  {
    return symbol_type (token::IS, l);
  }

  Parser::symbol_type
  Parser::make_LIKE (const location_type& l)
  {
    return symbol_type (token::LIKE, l);
  }

  Parser::symbol_type
  Parser::make_REGEXP (const location_type& l)
  {
    return symbol_type (token::REGEXP, l);
  }

  Parser::symbol_type
  Parser::make_NOT (const location_type& l)
  {
    return symbol_type (token::NOT, l);
  }

  Parser::symbol_type
  Parser::make_BETWEEN (const location_type& l)
  {
    return symbol_type (token::BETWEEN, l);
  }

  Parser::symbol_type
  Parser::make_COMPARISON (const std::string& v, const location_type& l)
  {
    return symbol_type (token::COMPARISON, v, l);
  }

  Parser::symbol_type
  Parser::make_SHIFT (const std::string& v, const location_type& l)
  {
    return symbol_type (token::SHIFT, v, l);
  }

  Parser::symbol_type
  Parser::make_MOD (const location_type& l)
  {
    return symbol_type (token::MOD, l);
  }

  Parser::symbol_type
  Parser::make_UMINUS (const location_type& l)
  {
    return symbol_type (token::UMINUS, l);
  }

  Parser::symbol_type
  Parser::make_ADD (const location_type& l)
  {
    return symbol_type (token::ADD, l);
  }

  Parser::symbol_type
  Parser::make_ALL (const location_type& l)
  {
    return symbol_type (token::ALL, l);
  }

  Parser::symbol_type
  Parser::make_ALTER (const location_type& l)
  {
    return symbol_type (token::ALTER, l);
  }

  Parser::symbol_type
  Parser::make_ANALYZE (const location_type& l)
  {
    return symbol_type (token::ANALYZE, l);
  }

  Parser::symbol_type
  Parser::make_AND (const location_type& l)
  {
    return symbol_type (token::AND, l);
  }

  Parser::symbol_type
  Parser::make_ANY (const location_type& l)
  {
    return symbol_type (token::ANY, l);
  }

  Parser::symbol_type
  Parser::make_APPEND (const location_type& l)
  {
    return symbol_type (token::APPEND, l);
  }

  Parser::symbol_type
  Parser::make_AS (const location_type& l)
  {
    return symbol_type (token::AS, l);
  }

  Parser::symbol_type
  Parser::make_ASC (const location_type& l)
  {
    return symbol_type (token::ASC, l);
  }

  Parser::symbol_type
  Parser::make_AUTO_INCREMENT (const location_type& l)
  {
    return symbol_type (token::AUTO_INCREMENT, l);
  }

  Parser::symbol_type
  Parser::make_BEFORE (const location_type& l)
  {
    return symbol_type (token::BEFORE, l);
  }

  Parser::symbol_type
  Parser::make_BIGINT (const location_type& l)
  {
    return symbol_type (token::BIGINT, l);
  }

  Parser::symbol_type
  Parser::make_BINARY (const location_type& l)
  {
    return symbol_type (token::BINARY, l);
  }

  Parser::symbol_type
  Parser::make_BIT (const location_type& l)
  {
    return symbol_type (token::BIT, l);
  }

  Parser::symbol_type
  Parser::make_BLOB (const location_type& l)
  {
    return symbol_type (token::BLOB, l);
  }

  Parser::symbol_type
  Parser::make_BOTH (const location_type& l)
  {
    return symbol_type (token::BOTH, l);
  }

  Parser::symbol_type
  Parser::make_BY (const location_type& l)
  {
    return symbol_type (token::BY, l);
  }

  Parser::symbol_type
  Parser::make_CALL (const location_type& l)
  {
    return symbol_type (token::CALL, l);
  }

  Parser::symbol_type
  Parser::make_CASCADE (const location_type& l)
  {
    return symbol_type (token::CASCADE, l);
  }

  Parser::symbol_type
  Parser::make_CASE (const location_type& l)
  {
    return symbol_type (token::CASE, l);
  }

  Parser::symbol_type
  Parser::make_CHANGE (const location_type& l)
  {
    return symbol_type (token::CHANGE, l);
  }

  Parser::symbol_type
  Parser::make_CHAR (const location_type& l)
  {
    return symbol_type (token::CHAR, l);
  }

  Parser::symbol_type
  Parser::make_CHECK (const location_type& l)
  {
    return symbol_type (token::CHECK, l);
  }

  Parser::symbol_type
  Parser::make_COLLATE (const location_type& l)
  {
    return symbol_type (token::COLLATE, l);
  }

  Parser::symbol_type
  Parser::make_COLUMN (const location_type& l)
  {
    return symbol_type (token::COLUMN, l);
  }

  Parser::symbol_type
  Parser::make_COMMENT (const location_type& l)
  {
    return symbol_type (token::COMMENT, l);
  }

  Parser::symbol_type
  Parser::make_CONDITION (const location_type& l)
  {
    return symbol_type (token::CONDITION, l);
  }

  Parser::symbol_type
  Parser::make_CONSTRAINT (const location_type& l)
  {
    return symbol_type (token::CONSTRAINT, l);
  }

  Parser::symbol_type
  Parser::make_CONTINUE (const location_type& l)
  {
    return symbol_type (token::CONTINUE, l);
  }

  Parser::symbol_type
  Parser::make_CONVERT (const location_type& l)
  {
    return symbol_type (token::CONVERT, l);
  }

  Parser::symbol_type
  Parser::make_CREATE (const location_type& l)
  {
    return symbol_type (token::CREATE, l);
  }

  Parser::symbol_type
  Parser::make_CROSS (const location_type& l)
  {
    return symbol_type (token::CROSS, l);
  }

  Parser::symbol_type
  Parser::make_CURRENT_DATE (const location_type& l)
  {
    return symbol_type (token::CURRENT_DATE, l);
  }

  Parser::symbol_type
  Parser::make_CURRENT_TIME (const location_type& l)
  {
    return symbol_type (token::CURRENT_TIME, l);
  }

  Parser::symbol_type
  Parser::make_CURRENT_TIMESTAMP (const location_type& l)
  {
    return symbol_type (token::CURRENT_TIMESTAMP, l);
  }

  Parser::symbol_type
  Parser::make_CURRENT_USER (const location_type& l)
  {
    return symbol_type (token::CURRENT_USER, l);
  }

  Parser::symbol_type
  Parser::make_CURSOR (const location_type& l)
  {
    return symbol_type (token::CURSOR, l);
  }

  Parser::symbol_type
  Parser::make_DATABASE (const location_type& l)
  {
    return symbol_type (token::DATABASE, l);
  }

  Parser::symbol_type
  Parser::make_DATABASES (const location_type& l)
  {
    return symbol_type (token::DATABASES, l);
  }

  Parser::symbol_type
  Parser::make_DATE (const location_type& l)
  {
    return symbol_type (token::DATE, l);
  }

  Parser::symbol_type
  Parser::make_DATETIME (const location_type& l)
  {
    return symbol_type (token::DATETIME, l);
  }

  Parser::symbol_type
  Parser::make_DAY_HOUR (const location_type& l)
  {
    return symbol_type (token::DAY_HOUR, l);
  }

  Parser::symbol_type
  Parser::make_DAY (const location_type& l)
  {
    return symbol_type (token::DAY, l);
  }

  Parser::symbol_type
  Parser::make_DAY_MICROSECOND (const location_type& l)
  {
    return symbol_type (token::DAY_MICROSECOND, l);
  }

  Parser::symbol_type
  Parser::make_DAY_MINUTE (const location_type& l)
  {
    return symbol_type (token::DAY_MINUTE, l);
  }

  Parser::symbol_type
  Parser::make_DAY_SECOND (const location_type& l)
  {
    return symbol_type (token::DAY_SECOND, l);
  }

  Parser::symbol_type
  Parser::make_DECIMAL (const location_type& l)
  {
    return symbol_type (token::DECIMAL, l);
  }

  Parser::symbol_type
  Parser::make_DECLARE (const location_type& l)
  {
    return symbol_type (token::DECLARE, l);
  }

  Parser::symbol_type
  Parser::make_DEFAULT (const location_type& l)
  {
    return symbol_type (token::DEFAULT, l);
  }

  Parser::symbol_type
  Parser::make_DELAYED (const location_type& l)
  {
    return symbol_type (token::DELAYED, l);
  }

  Parser::symbol_type
  Parser::make_DELETE (const location_type& l)
  {
    return symbol_type (token::DELETE, l);
  }

  Parser::symbol_type
  Parser::make_DESC (const location_type& l)
  {
    return symbol_type (token::DESC, l);
  }

  Parser::symbol_type
  Parser::make_DESCRIBE (const location_type& l)
  {
    return symbol_type (token::DESCRIBE, l);
  }

  Parser::symbol_type
  Parser::make_DETERMINISTIC (const location_type& l)
  {
    return symbol_type (token::DETERMINISTIC, l);
  }

  Parser::symbol_type
  Parser::make_DISTINCT (const location_type& l)
  {
    return symbol_type (token::DISTINCT, l);
  }

  Parser::symbol_type
  Parser::make_DISTINCTROW (const location_type& l)
  {
    return symbol_type (token::DISTINCTROW, l);
  }

  Parser::symbol_type
  Parser::make_DIV (const location_type& l)
  {
    return symbol_type (token::DIV, l);
  }

  Parser::symbol_type
  Parser::make_DOUBLE (const location_type& l)
  {
    return symbol_type (token::DOUBLE, l);
  }

  Parser::symbol_type
  Parser::make_DROP (const location_type& l)
  {
    return symbol_type (token::DROP, l);
  }

  Parser::symbol_type
  Parser::make_DUAL (const location_type& l)
  {
    return symbol_type (token::DUAL, l);
  }

  Parser::symbol_type
  Parser::make_EACH (const location_type& l)
  {
    return symbol_type (token::EACH, l);
  }

  Parser::symbol_type
  Parser::make_ELSE (const location_type& l)
  {
    return symbol_type (token::ELSE, l);
  }

  Parser::symbol_type
  Parser::make_ELSEIF (const location_type& l)
  {
    return symbol_type (token::ELSEIF, l);
  }

  Parser::symbol_type
  Parser::make_ENCLOSED (const location_type& l)
  {
    return symbol_type (token::ENCLOSED, l);
  }

  Parser::symbol_type
  Parser::make_ENUM (const location_type& l)
  {
    return symbol_type (token::ENUM, l);
  }

  Parser::symbol_type
  Parser::make_ESCAPED (const location_type& l)
  {
    return symbol_type (token::ESCAPED, l);
  }

  Parser::symbol_type
  Parser::make_EXISTS (const location_type& l)
  {
    return symbol_type (token::EXISTS, l);
  }

  Parser::symbol_type
  Parser::make_EXIT (const location_type& l)
  {
    return symbol_type (token::EXIT, l);
  }

  Parser::symbol_type
  Parser::make_EXPLAIN (const location_type& l)
  {
    return symbol_type (token::EXPLAIN, l);
  }

  Parser::symbol_type
  Parser::make_FETCH (const location_type& l)
  {
    return symbol_type (token::FETCH, l);
  }

  Parser::symbol_type
  Parser::make_FLOAT (const location_type& l)
  {
    return symbol_type (token::FLOAT, l);
  }

  Parser::symbol_type
  Parser::make_FOR (const location_type& l)
  {
    return symbol_type (token::FOR, l);
  }

  Parser::symbol_type
  Parser::make_FORCE (const location_type& l)
  {
    return symbol_type (token::FORCE, l);
  }

  Parser::symbol_type
  Parser::make_FOREIGN (const location_type& l)
  {
    return symbol_type (token::FOREIGN, l);
  }

  Parser::symbol_type
  Parser::make_FROM (const location_type& l)
  {
    return symbol_type (token::FROM, l);
  }

  Parser::symbol_type
  Parser::make_FULLTEXT (const location_type& l)
  {
    return symbol_type (token::FULLTEXT, l);
  }

  Parser::symbol_type
  Parser::make_GRANT (const location_type& l)
  {
    return symbol_type (token::GRANT, l);
  }

  Parser::symbol_type
  Parser::make_GROUP (const location_type& l)
  {
    return symbol_type (token::GROUP, l);
  }

  Parser::symbol_type
  Parser::make_HAVING (const location_type& l)
  {
    return symbol_type (token::HAVING, l);
  }

  Parser::symbol_type
  Parser::make_HIGH (const location_type& l)
  {
    return symbol_type (token::HIGH, l);
  }

  Parser::symbol_type
  Parser::make_HIGH_PRIORITY (const location_type& l)
  {
    return symbol_type (token::HIGH_PRIORITY, l);
  }

  Parser::symbol_type
  Parser::make_HOUR_MICROSECOND (const location_type& l)
  {
    return symbol_type (token::HOUR_MICROSECOND, l);
  }

  Parser::symbol_type
  Parser::make_HOUR_MINUTE (const location_type& l)
  {
    return symbol_type (token::HOUR_MINUTE, l);
  }

  Parser::symbol_type
  Parser::make_HOUR_SECOND (const location_type& l)
  {
    return symbol_type (token::HOUR_SECOND, l);
  }

  Parser::symbol_type
  Parser::make_IF (const location_type& l)
  {
    return symbol_type (token::IF, l);
  }

  Parser::symbol_type
  Parser::make_IGNORE (const location_type& l)
  {
    return symbol_type (token::IGNORE, l);
  }

  Parser::symbol_type
  Parser::make_INDEX (const location_type& l)
  {
    return symbol_type (token::INDEX, l);
  }

  Parser::symbol_type
  Parser::make_INFILE (const location_type& l)
  {
    return symbol_type (token::INFILE, l);
  }

  Parser::symbol_type
  Parser::make_INNER (const location_type& l)
  {
    return symbol_type (token::INNER, l);
  }

  Parser::symbol_type
  Parser::make_INOUT (const location_type& l)
  {
    return symbol_type (token::INOUT, l);
  }

  Parser::symbol_type
  Parser::make_INSENSITIVE (const location_type& l)
  {
    return symbol_type (token::INSENSITIVE, l);
  }

  Parser::symbol_type
  Parser::make_INSERT (const location_type& l)
  {
    return symbol_type (token::INSERT, l);
  }

  Parser::symbol_type
  Parser::make_INT (const location_type& l)
  {
    return symbol_type (token::INT, l);
  }

  Parser::symbol_type
  Parser::make_INTEGER (const location_type& l)
  {
    return symbol_type (token::INTEGER, l);
  }

  Parser::symbol_type
  Parser::make_INTERVAL (const location_type& l)
  {
    return symbol_type (token::INTERVAL, l);
  }

  Parser::symbol_type
  Parser::make_INTO (const location_type& l)
  {
    return symbol_type (token::INTO, l);
  }

  Parser::symbol_type
  Parser::make_ITERATE (const location_type& l)
  {
    return symbol_type (token::ITERATE, l);
  }

  Parser::symbol_type
  Parser::make_JOIN (const location_type& l)
  {
    return symbol_type (token::JOIN, l);
  }

  Parser::symbol_type
  Parser::make_KEY (const location_type& l)
  {
    return symbol_type (token::KEY, l);
  }

  Parser::symbol_type
  Parser::make_KEYS (const location_type& l)
  {
    return symbol_type (token::KEYS, l);
  }

  Parser::symbol_type
  Parser::make_KILL (const location_type& l)
  {
    return symbol_type (token::KILL, l);
  }

  Parser::symbol_type
  Parser::make_LEADING (const location_type& l)
  {
    return symbol_type (token::LEADING, l);
  }

  Parser::symbol_type
  Parser::make_LEAVE (const location_type& l)
  {
    return symbol_type (token::LEAVE, l);
  }

  Parser::symbol_type
  Parser::make_LEFT (const location_type& l)
  {
    return symbol_type (token::LEFT, l);
  }

  Parser::symbol_type
  Parser::make_LIMIT (const location_type& l)
  {
    return symbol_type (token::LIMIT, l);
  }

  Parser::symbol_type
  Parser::make_LINES (const location_type& l)
  {
    return symbol_type (token::LINES, l);
  }

  Parser::symbol_type
  Parser::make_LOAD (const location_type& l)
  {
    return symbol_type (token::LOAD, l);
  }

  Parser::symbol_type
  Parser::make_LOCALTIME (const location_type& l)
  {
    return symbol_type (token::LOCALTIME, l);
  }

  Parser::symbol_type
  Parser::make_LOCALTIMESTAMP (const location_type& l)
  {
    return symbol_type (token::LOCALTIMESTAMP, l);
  }

  Parser::symbol_type
  Parser::make_LOCK (const location_type& l)
  {
    return symbol_type (token::LOCK, l);
  }

  Parser::symbol_type
  Parser::make_LONG (const location_type& l)
  {
    return symbol_type (token::LONG, l);
  }

  Parser::symbol_type
  Parser::make_LONGBLOB (const location_type& l)
  {
    return symbol_type (token::LONGBLOB, l);
  }

  Parser::symbol_type
  Parser::make_LONGTEXT (const location_type& l)
  {
    return symbol_type (token::LONGTEXT, l);
  }

  Parser::symbol_type
  Parser::make_LOOP (const location_type& l)
  {
    return symbol_type (token::LOOP, l);
  }

  Parser::symbol_type
  Parser::make_LOW (const location_type& l)
  {
    return symbol_type (token::LOW, l);
  }

  Parser::symbol_type
  Parser::make_LOW_PRIORITY (const location_type& l)
  {
    return symbol_type (token::LOW_PRIORITY, l);
  }

  Parser::symbol_type
  Parser::make_MATCH (const location_type& l)
  {
    return symbol_type (token::MATCH, l);
  }

  Parser::symbol_type
  Parser::make_MEDIUMBLOB (const location_type& l)
  {
    return symbol_type (token::MEDIUMBLOB, l);
  }

  Parser::symbol_type
  Parser::make_MEDIUMINT (const location_type& l)
  {
    return symbol_type (token::MEDIUMINT, l);
  }

  Parser::symbol_type
  Parser::make_MEDIUMTEXT (const location_type& l)
  {
    return symbol_type (token::MEDIUMTEXT, l);
  }

  Parser::symbol_type
  Parser::make_MINUTE_MICROSECOND (const location_type& l)
  {
    return symbol_type (token::MINUTE_MICROSECOND, l);
  }

  Parser::symbol_type
  Parser::make_MINUTE_SECOND (const location_type& l)
  {
    return symbol_type (token::MINUTE_SECOND, l);
  }

  Parser::symbol_type
  Parser::make_MODIFIES (const location_type& l)
  {
    return symbol_type (token::MODIFIES, l);
  }

  Parser::symbol_type
  Parser::make_NATURAL (const location_type& l)
  {
    return symbol_type (token::NATURAL, l);
  }

  Parser::symbol_type
  Parser::make_NO_WRITE_TO_BINLOG (const location_type& l)
  {
    return symbol_type (token::NO_WRITE_TO_BINLOG, l);
  }

  Parser::symbol_type
  Parser::make_NULLX (const location_type& l)
  {
    return symbol_type (token::NULLX, l);
  }

  Parser::symbol_type
  Parser::make_NUMBER (const location_type& l)
  {
    return symbol_type (token::NUMBER, l);
  }

  Parser::symbol_type
  Parser::make_ON (const location_type& l)
  {
    return symbol_type (token::ON, l);
  }

  Parser::symbol_type
  Parser::make_DUPLICATE (const location_type& l)
  {
    return symbol_type (token::DUPLICATE, l);
  }

  Parser::symbol_type
  Parser::make_OPTIMIZE (const location_type& l)
  {
    return symbol_type (token::OPTIMIZE, l);
  }

  Parser::symbol_type
  Parser::make_OPTION (const location_type& l)
  {
    return symbol_type (token::OPTION, l);
  }

  Parser::symbol_type
  Parser::make_OPTIONALLY (const location_type& l)
  {
    return symbol_type (token::OPTIONALLY, l);
  }

  Parser::symbol_type
  Parser::make_ORDER (const location_type& l)
  {
    return symbol_type (token::ORDER, l);
  }

  Parser::symbol_type
  Parser::make_OUT (const location_type& l)
  {
    return symbol_type (token::OUT, l);
  }

  Parser::symbol_type
  Parser::make_OUTER (const location_type& l)
  {
    return symbol_type (token::OUTER, l);
  }

  Parser::symbol_type
  Parser::make_OUTFILE (const location_type& l)
  {
    return symbol_type (token::OUTFILE, l);
  }

  Parser::symbol_type
  Parser::make_PARTITIONED (const location_type& l)
  {
    return symbol_type (token::PARTITIONED, l);
  }

  Parser::symbol_type
  Parser::make_PRECISION (const location_type& l)
  {
    return symbol_type (token::PRECISION, l);
  }

  Parser::symbol_type
  Parser::make_PRIMARY (const location_type& l)
  {
    return symbol_type (token::PRIMARY, l);
  }

  Parser::symbol_type
  Parser::make_PRIORITY (const location_type& l)
  {
    return symbol_type (token::PRIORITY, l);
  }

  Parser::symbol_type
  Parser::make_PROCEDURE (const location_type& l)
  {
    return symbol_type (token::PROCEDURE, l);
  }

  Parser::symbol_type
  Parser::make_PROJECTION (const location_type& l)
  {
    return symbol_type (token::PROJECTION, l);
  }

  Parser::symbol_type
  Parser::make_PURGE (const location_type& l)
  {
    return symbol_type (token::PURGE, l);
  }

  Parser::symbol_type
  Parser::make_QUICK (const location_type& l)
  {
    return symbol_type (token::QUICK, l);
  }

  Parser::symbol_type
  Parser::make_QUARTER (const location_type& l)
  {
    return symbol_type (token::QUARTER, l);
  }

  Parser::symbol_type
  Parser::make_READ (const location_type& l)
  {
    return symbol_type (token::READ, l);
  }

  Parser::symbol_type
  Parser::make_READS (const location_type& l)
  {
    return symbol_type (token::READS, l);
  }

  Parser::symbol_type
  Parser::make_REAL (const location_type& l)
  {
    return symbol_type (token::REAL, l);
  }

  Parser::symbol_type
  Parser::make_REFERENCES (const location_type& l)
  {
    return symbol_type (token::REFERENCES, l);
  }

  Parser::symbol_type
  Parser::make_RELEASE (const location_type& l)
  {
    return symbol_type (token::RELEASE, l);
  }

  Parser::symbol_type
  Parser::make_RENAME (const location_type& l)
  {
    return symbol_type (token::RENAME, l);
  }

  Parser::symbol_type
  Parser::make_REPEAT (const location_type& l)
  {
    return symbol_type (token::REPEAT, l);
  }

  Parser::symbol_type
  Parser::make_REPLACE (const location_type& l)
  {
    return symbol_type (token::REPLACE, l);
  }

  Parser::symbol_type
  Parser::make_REQUIRE (const location_type& l)
  {
    return symbol_type (token::REQUIRE, l);
  }

  Parser::symbol_type
  Parser::make_RESTRICT (const location_type& l)
  {
    return symbol_type (token::RESTRICT, l);
  }

  Parser::symbol_type
  Parser::make_RETURN (const location_type& l)
  {
    return symbol_type (token::RETURN, l);
  }

  Parser::symbol_type
  Parser::make_REVOKE (const location_type& l)
  {
    return symbol_type (token::REVOKE, l);
  }

  Parser::symbol_type
  Parser::make_RIGHT (const location_type& l)
  {
    return symbol_type (token::RIGHT, l);
  }

  Parser::symbol_type
  Parser::make_ROLLUP (const location_type& l)
  {
    return symbol_type (token::ROLLUP, l);
  }

  Parser::symbol_type
  Parser::make_SAMPLE (const location_type& l)
  {
    return symbol_type (token::SAMPLE, l);
  }

  Parser::symbol_type
  Parser::make_SCHEMA (const location_type& l)
  {
    return symbol_type (token::SCHEMA, l);
  }

  Parser::symbol_type
  Parser::make_SCHEMAS (const location_type& l)
  {
    return symbol_type (token::SCHEMAS, l);
  }

  Parser::symbol_type
  Parser::make_SECOND_MICROSECOND (const location_type& l)
  {
    return symbol_type (token::SECOND_MICROSECOND, l);
  }

  Parser::symbol_type
  Parser::make_SELECT (const location_type& l)
  {
    return symbol_type (token::SELECT, l);
  }

  Parser::symbol_type
  Parser::make_SENSITIVE (const location_type& l)
  {
    return symbol_type (token::SENSITIVE, l);
  }

  Parser::symbol_type
  Parser::make_SEPARATOR (const location_type& l)
  {
    return symbol_type (token::SEPARATOR, l);
  }

  Parser::symbol_type
  Parser::make_SET (const location_type& l)
  {
    return symbol_type (token::SET, l);
  }

  Parser::symbol_type
  Parser::make_SHOW (const location_type& l)
  {
    return symbol_type (token::SHOW, l);
  }

  Parser::symbol_type
  Parser::make_SMALLINT (const location_type& l)
  {
    return symbol_type (token::SMALLINT, l);
  }

  Parser::symbol_type
  Parser::make_SOME (const location_type& l)
  {
    return symbol_type (token::SOME, l);
  }

  Parser::symbol_type
  Parser::make_SONAME (const location_type& l)
  {
    return symbol_type (token::SONAME, l);
  }

  Parser::symbol_type
  Parser::make_SPATIAL (const location_type& l)
  {
    return symbol_type (token::SPATIAL, l);
  }

  Parser::symbol_type
  Parser::make_SPECIFIC (const location_type& l)
  {
    return symbol_type (token::SPECIFIC, l);
  }

  Parser::symbol_type
  Parser::make_SQL (const location_type& l)
  {
    return symbol_type (token::SQL, l);
  }

  Parser::symbol_type
  Parser::make_SQLEXCEPTION (const location_type& l)
  {
    return symbol_type (token::SQLEXCEPTION, l);
  }

  Parser::symbol_type
  Parser::make_SQLSTATE (const location_type& l)
  {
    return symbol_type (token::SQLSTATE, l);
  }

  Parser::symbol_type
  Parser::make_SQLWARNING (const location_type& l)
  {
    return symbol_type (token::SQLWARNING, l);
  }

  Parser::symbol_type
  Parser::make_BIG_RESULT (const location_type& l)
  {
    return symbol_type (token::BIG_RESULT, l);
  }

  Parser::symbol_type
  Parser::make_CALC_FOUND_ROWS (const location_type& l)
  {
    return symbol_type (token::CALC_FOUND_ROWS, l);
  }

  Parser::symbol_type
  Parser::make_SMALL_RESULT (const location_type& l)
  {
    return symbol_type (token::SMALL_RESULT, l);
  }

  Parser::symbol_type
  Parser::make_SSL (const location_type& l)
  {
    return symbol_type (token::SSL, l);
  }

  Parser::symbol_type
  Parser::make_STARTING (const location_type& l)
  {
    return symbol_type (token::STARTING, l);
  }

  Parser::symbol_type
  Parser::make_STRAIGHT_JOIN (const location_type& l)
  {
    return symbol_type (token::STRAIGHT_JOIN, l);
  }

  Parser::symbol_type
  Parser::make_TABLE (const location_type& l)
  {
    return symbol_type (token::TABLE, l);
  }

  Parser::symbol_type
  Parser::make_TEMPORARY (const location_type& l)
  {
    return symbol_type (token::TEMPORARY, l);
  }

  Parser::symbol_type
  Parser::make_TEXT (const location_type& l)
  {
    return symbol_type (token::TEXT, l);
  }

  Parser::symbol_type
  Parser::make_TERMINATED (const location_type& l)
  {
    return symbol_type (token::TERMINATED, l);
  }

  Parser::symbol_type
  Parser::make_THEN (const location_type& l)
  {
    return symbol_type (token::THEN, l);
  }

  Parser::symbol_type
  Parser::make_TIME (const location_type& l)
  {
    return symbol_type (token::TIME, l);
  }

  Parser::symbol_type
  Parser::make_TIMESTAMP (const location_type& l)
  {
    return symbol_type (token::TIMESTAMP, l);
  }

  Parser::symbol_type
  Parser::make_TINYBLOB (const location_type& l)
  {
    return symbol_type (token::TINYBLOB, l);
  }

  Parser::symbol_type
  Parser::make_TINYINT (const location_type& l)
  {
    return symbol_type (token::TINYINT, l);
  }

  Parser::symbol_type
  Parser::make_TINYTEXT (const location_type& l)
  {
    return symbol_type (token::TINYTEXT, l);
  }

  Parser::symbol_type
  Parser::make_TO (const location_type& l)
  {
    return symbol_type (token::TO, l);
  }

  Parser::symbol_type
  Parser::make_TRAILING (const location_type& l)
  {
    return symbol_type (token::TRAILING, l);
  }

  Parser::symbol_type
  Parser::make_TRIGGER (const location_type& l)
  {
    return symbol_type (token::TRIGGER, l);
  }

  Parser::symbol_type
  Parser::make_UNDO (const location_type& l)
  {
    return symbol_type (token::UNDO, l);
  }

  Parser::symbol_type
  Parser::make_UNION (const location_type& l)
  {
    return symbol_type (token::UNION, l);
  }

  Parser::symbol_type
  Parser::make_UNIQUE (const location_type& l)
  {
    return symbol_type (token::UNIQUE, l);
  }

  Parser::symbol_type
  Parser::make_UNLOCK (const location_type& l)
  {
    return symbol_type (token::UNLOCK, l);
  }

  Parser::symbol_type
  Parser::make_UNSIGNED (const location_type& l)
  {
    return symbol_type (token::UNSIGNED, l);
  }

  Parser::symbol_type
  Parser::make_UPDATE (const location_type& l)
  {
    return symbol_type (token::UPDATE, l);
  }

  Parser::symbol_type
  Parser::make_USAGE (const location_type& l)
  {
    return symbol_type (token::USAGE, l);
  }

  Parser::symbol_type
  Parser::make_USE (const location_type& l)
  {
    return symbol_type (token::USE, l);
  }

  Parser::symbol_type
  Parser::make_USING (const location_type& l)
  {
    return symbol_type (token::USING, l);
  }

  Parser::symbol_type
  Parser::make_UTC_DATE (const location_type& l)
  {
    return symbol_type (token::UTC_DATE, l);
  }

  Parser::symbol_type
  Parser::make_UTC_TIME (const location_type& l)
  {
    return symbol_type (token::UTC_TIME, l);
  }

  Parser::symbol_type
  Parser::make_UTC_TIMESTAMP (const location_type& l)
  {
    return symbol_type (token::UTC_TIMESTAMP, l);
  }

  Parser::symbol_type
  Parser::make_VALUES (const location_type& l)
  {
    return symbol_type (token::VALUES, l);
  }

  Parser::symbol_type
  Parser::make_VARBINARY (const location_type& l)
  {
    return symbol_type (token::VARBINARY, l);
  }

  Parser::symbol_type
  Parser::make_VARCHAR (const location_type& l)
  {
    return symbol_type (token::VARCHAR, l);
  }

  Parser::symbol_type
  Parser::make_VARYING (const location_type& l)
  {
    return symbol_type (token::VARYING, l);
  }

  Parser::symbol_type
  Parser::make_WHEN (const location_type& l)
  {
    return symbol_type (token::WHEN, l);
  }

  Parser::symbol_type
  Parser::make_WHERE (const location_type& l)
  {
    return symbol_type (token::WHERE, l);
  }

  Parser::symbol_type
  Parser::make_WHILE (const location_type& l)
  {
    return symbol_type (token::WHILE, l);
  }

  Parser::symbol_type
  Parser::make_WITH (const location_type& l)
  {
    return symbol_type (token::WITH, l);
  }

  Parser::symbol_type
  Parser::make_WRITE (const location_type& l)
  {
    return symbol_type (token::WRITE, l);
  }

  Parser::symbol_type
  Parser::make_YEAR (const location_type& l)
  {
    return symbol_type (token::YEAR, l);
  }

  Parser::symbol_type
  Parser::make_YEAR_MONTH (const location_type& l)
  {
    return symbol_type (token::YEAR_MONTH, l);
  }

  Parser::symbol_type
  Parser::make_ZEROFILL (const location_type& l)
  {
    return symbol_type (token::ZEROFILL, l);
  }

  Parser::symbol_type
  Parser::make_WEEK (const location_type& l)
  {
    return symbol_type (token::WEEK, l);
  }

  Parser::symbol_type
  Parser::make_DO (const location_type& l)
  {
    return symbol_type (token::DO, l);
  }

  Parser::symbol_type
  Parser::make_MAX_QUERIES_PER_HOUR (const location_type& l)
  {
    return symbol_type (token::MAX_QUERIES_PER_HOUR, l);
  }

  Parser::symbol_type
  Parser::make_MAX_UPDATES_PER_HOUR (const location_type& l)
  {
    return symbol_type (token::MAX_UPDATES_PER_HOUR, l);
  }

  Parser::symbol_type
  Parser::make_MAX_CONNECTIONS_PER_HOUR (const location_type& l)
  {
    return symbol_type (token::MAX_CONNECTIONS_PER_HOUR, l);
  }

  Parser::symbol_type
  Parser::make_MAX_USER_CONNECTIONS (const location_type& l)
  {
    return symbol_type (token::MAX_USER_CONNECTIONS, l);
  }

  Parser::symbol_type
  Parser::make_USER (const location_type& l)
  {
    return symbol_type (token::USER, l);
  }

  Parser::symbol_type
  Parser::make_TRUNCATE (const location_type& l)
  {
    return symbol_type (token::TRUNCATE, l);
  }

  Parser::symbol_type
  Parser::make_FAST (const location_type& l)
  {
    return symbol_type (token::FAST, l);
  }

  Parser::symbol_type
  Parser::make_MEDIUM (const location_type& l)
  {
    return symbol_type (token::MEDIUM, l);
  }

  Parser::symbol_type
  Parser::make_EXTENDED (const location_type& l)
  {
    return symbol_type (token::EXTENDED, l);
  }

  Parser::symbol_type
  Parser::make_CHANGED (const location_type& l)
  {
    return symbol_type (token::CHANGED, l);
  }

  Parser::symbol_type
  Parser::make_LEAVES (const location_type& l)
  {
    return symbol_type (token::LEAVES, l);
  }

  Parser::symbol_type
  Parser::make_MASTER (const location_type& l)
  {
    return symbol_type (token::MASTER, l);
  }

  Parser::symbol_type
  Parser::make_QUERY (const location_type& l)
  {
    return symbol_type (token::QUERY, l);
  }

  Parser::symbol_type
  Parser::make_CACHE (const location_type& l)
  {
    return symbol_type (token::CACHE, l);
  }

  Parser::symbol_type
  Parser::make_SLAVE (const location_type& l)
  {
    return symbol_type (token::SLAVE, l);
  }

  Parser::symbol_type
  Parser::make_BEGINT (const location_type& l)
  {
    return symbol_type (token::BEGINT, l);
  }

  Parser::symbol_type
  Parser::make_COMMIT (const location_type& l)
  {
    return symbol_type (token::COMMIT, l);
  }

  Parser::symbol_type
  Parser::make_START (const location_type& l)
  {
    return symbol_type (token::START, l);
  }

  Parser::symbol_type
  Parser::make_TRANSACTION (const location_type& l)
  {
    return symbol_type (token::TRANSACTION, l);
  }

  Parser::symbol_type
  Parser::make_NO (const location_type& l)
  {
    return symbol_type (token::NO, l);
  }

  Parser::symbol_type
  Parser::make_CHAIN (const location_type& l)
  {
    return symbol_type (token::CHAIN, l);
  }

  Parser::symbol_type
  Parser::make_AUTOCOMMIT (const location_type& l)
  {
    return symbol_type (token::AUTOCOMMIT, l);
  }

  Parser::symbol_type
  Parser::make_SAVEPOINT (const location_type& l)
  {
    return symbol_type (token::SAVEPOINT, l);
  }

  Parser::symbol_type
  Parser::make_ROLLBACK (const location_type& l)
  {
    return symbol_type (token::ROLLBACK, l);
  }

  Parser::symbol_type
  Parser::make_LOCAL (const location_type& l)
  {
    return symbol_type (token::LOCAL, l);
  }

  Parser::symbol_type
  Parser::make_TABLES (const location_type& l)
  {
    return symbol_type (token::TABLES, l);
  }

  Parser::symbol_type
  Parser::make_ISOLATION (const location_type& l)
  {
    return symbol_type (token::ISOLATION, l);
  }

  Parser::symbol_type
  Parser::make_LEVEL (const location_type& l)
  {
    return symbol_type (token::LEVEL, l);
  }

  Parser::symbol_type
  Parser::make_GLOBAL (const location_type& l)
  {
    return symbol_type (token::GLOBAL, l);
  }

  Parser::symbol_type
  Parser::make_SESSION (const location_type& l)
  {
    return symbol_type (token::SESSION, l);
  }

  Parser::symbol_type
  Parser::make_UNCOMMITTED (const location_type& l)
  {
    return symbol_type (token::UNCOMMITTED, l);
  }

  Parser::symbol_type
  Parser::make_COMMITTED (const location_type& l)
  {
    return symbol_type (token::COMMITTED, l);
  }

  Parser::symbol_type
  Parser::make_REPEATABLE (const location_type& l)
  {
    return symbol_type (token::REPEATABLE, l);
  }

  Parser::symbol_type
  Parser::make_SERIALIZABLE (const location_type& l)
  {
    return symbol_type (token::SERIALIZABLE, l);
  }

  Parser::symbol_type
  Parser::make_IDENTIFIED (const location_type& l)
  {
    return symbol_type (token::IDENTIFIED, l);
  }

  Parser::symbol_type
  Parser::make_PASSWORD (const location_type& l)
  {
    return symbol_type (token::PASSWORD, l);
  }

  Parser::symbol_type
  Parser::make_PRIVILEGES (const location_type& l)
  {
    return symbol_type (token::PRIVILEGES, l);
  }

  Parser::symbol_type
  Parser::make_BACKUP (const location_type& l)
  {
    return symbol_type (token::BACKUP, l);
  }

  Parser::symbol_type
  Parser::make_CHECKSUM (const location_type& l)
  {
    return symbol_type (token::CHECKSUM, l);
  }

  Parser::symbol_type
  Parser::make_REPAIR (const location_type& l)
  {
    return symbol_type (token::REPAIR, l);
  }

  Parser::symbol_type
  Parser::make_USE_FRM (const location_type& l)
  {
    return symbol_type (token::USE_FRM, l);
  }

  Parser::symbol_type
  Parser::make_RESTORE (const location_type& l)
  {
    return symbol_type (token::RESTORE, l);
  }

  Parser::symbol_type
  Parser::make_CHARACTER (const location_type& l)
  {
    return symbol_type (token::CHARACTER, l);
  }

  Parser::symbol_type
  Parser::make_COLLATION (const location_type& l)
  {
    return symbol_type (token::COLLATION, l);
  }

  Parser::symbol_type
  Parser::make_COLUMNS (const location_type& l)
  {
    return symbol_type (token::COLUMNS, l);
  }

  Parser::symbol_type
  Parser::make_ENGINE (const location_type& l)
  {
    return symbol_type (token::ENGINE, l);
  }

  Parser::symbol_type
  Parser::make_LOGS (const location_type& l)
  {
    return symbol_type (token::LOGS, l);
  }

  Parser::symbol_type
  Parser::make_STATUS (const location_type& l)
  {
    return symbol_type (token::STATUS, l);
  }

  Parser::symbol_type
  Parser::make_STORAGE (const location_type& l)
  {
    return symbol_type (token::STORAGE, l);
  }

  Parser::symbol_type
  Parser::make_ENGINES (const location_type& l)
  {
    return symbol_type (token::ENGINES, l);
  }

  Parser::symbol_type
  Parser::make_ERRORS (const location_type& l)
  {
    return symbol_type (token::ERRORS, l);
  }

  Parser::symbol_type
  Parser::make_GRANTS (const location_type& l)
  {
    return symbol_type (token::GRANTS, l);
  }

  Parser::symbol_type
  Parser::make_INNODB (const location_type& l)
  {
    return symbol_type (token::INNODB, l);
  }

  Parser::symbol_type
  Parser::make_PROCESSLIST (const location_type& l)
  {
    return symbol_type (token::PROCESSLIST, l);
  }

  Parser::symbol_type
  Parser::make_TRIGGERS (const location_type& l)
  {
    return symbol_type (token::TRIGGERS, l);
  }

  Parser::symbol_type
  Parser::make_VARIABLES (const location_type& l)
  {
    return symbol_type (token::VARIABLES, l);
  }

  Parser::symbol_type
  Parser::make_WARNINGS (const location_type& l)
  {
    return symbol_type (token::WARNINGS, l);
  }

  Parser::symbol_type
  Parser::make_FLUSH (const location_type& l)
  {
    return symbol_type (token::FLUSH, l);
  }

  Parser::symbol_type
  Parser::make_HOSTS (const location_type& l)
  {
    return symbol_type (token::HOSTS, l);
  }

  Parser::symbol_type
  Parser::make_DES_KEY_FILE (const location_type& l)
  {
    return symbol_type (token::DES_KEY_FILE, l);
  }

  Parser::symbol_type
  Parser::make_USER_RESOURCES (const location_type& l)
  {
    return symbol_type (token::USER_RESOURCES, l);
  }

  Parser::symbol_type
  Parser::make_CONNECTION (const location_type& l)
  {
    return symbol_type (token::CONNECTION, l);
  }

  Parser::symbol_type
  Parser::make_RESET (const location_type& l)
  {
    return symbol_type (token::RESET, l);
  }

  Parser::symbol_type
  Parser::make_PREPARE (const location_type& l)
  {
    return symbol_type (token::PREPARE, l);
  }

  Parser::symbol_type
  Parser::make_DEALLOCATE (const location_type& l)
  {
    return symbol_type (token::DEALLOCATE, l);
  }

  Parser::symbol_type
  Parser::make_EXECUTE (const location_type& l)
  {
    return symbol_type (token::EXECUTE, l);
  }

  Parser::symbol_type
  Parser::make_WORK (const location_type& l)
  {
    return symbol_type (token::WORK, l);
  }

  Parser::symbol_type
  Parser::make_BTREE (const location_type& l)
  {
    return symbol_type (token::BTREE, l);
  }

  Parser::symbol_type
  Parser::make_HASH (const location_type& l)
  {
    return symbol_type (token::HASH, l);
  }

  Parser::symbol_type
  Parser::make_BDB (const location_type& l)
  {
    return symbol_type (token::BDB, l);
  }

  Parser::symbol_type
  Parser::make_OPEN (const location_type& l)
  {
    return symbol_type (token::OPEN, l);
  }

  Parser::symbol_type
  Parser::make_FULL (const location_type& l)
  {
    return symbol_type (token::FULL, l);
  }

  Parser::symbol_type
  Parser::make_FSUBSTRING (const location_type& l)
  {
    return symbol_type (token::FSUBSTRING, l);
  }

  Parser::symbol_type
  Parser::make_FTRIM (const location_type& l)
  {
    return symbol_type (token::FTRIM, l);
  }

  Parser::symbol_type
  Parser::make_FDATE_ADD (const location_type& l)
  {
    return symbol_type (token::FDATE_ADD, l);
  }

  Parser::symbol_type
  Parser::make_FDATE_SUB (const location_type& l)
  {
    return symbol_type (token::FDATE_SUB, l);
  }

  Parser::symbol_type
  Parser::make_FCOUNT (const location_type& l)
  {
    return symbol_type (token::FCOUNT, l);
  }

  Parser::symbol_type
  Parser::make_FUPPER (const location_type& l)
  {
    return symbol_type (token::FUPPER, l);
  }

  Parser::symbol_type
  Parser::make_FCAST (const location_type& l)
  {
    return symbol_type (token::FCAST, l);
  }

  Parser::symbol_type
  Parser::make_FCOALESCE (const location_type& l)
  {
    return symbol_type (token::FCOALESCE, l);
  }

  Parser::symbol_type
  Parser::make_FCONVERT (const location_type& l)
  {
    return symbol_type (token::FCONVERT, l);
  }

  Parser::symbol_type
  Parser::make_FSUM (const location_type& l)
  {
    return symbol_type (token::FSUM, l);
  }

  Parser::symbol_type
  Parser::make_FAVG (const location_type& l)
  {
    return symbol_type (token::FAVG, l);
  }

  Parser::symbol_type
  Parser::make_FMIN (const location_type& l)
  {
    return symbol_type (token::FMIN, l);
  }

  Parser::symbol_type
  Parser::make_FMAX (const location_type& l)
  {
    return symbol_type (token::FMAX, l);
  }

  Parser::symbol_type
  Parser::make_BRACKET_O (const location_type& l)
  {
    return symbol_type (token::BRACKET_O, l);
  }

  Parser::symbol_type
  Parser::make_BRACKET_C (const location_type& l)
  {
    return symbol_type (token::BRACKET_C, l);
  }

  Parser::symbol_type
  Parser::make_SEMICOLON (const location_type& l)
  {
    return symbol_type (token::SEMICOLON, l);
  }

  Parser::symbol_type
  Parser::make_DOT (const location_type& l)
  {
    return symbol_type (token::DOT, l);
  }

  Parser::symbol_type
  Parser::make_MULTIPLY (const location_type& l)
  {
    return symbol_type (token::MULTIPLY, l);
  }


#line 6 "sql_parser.y" // lalr1.cc:377
} // sql
#line 5301 "sql_parser.hh" // lalr1.cc:377


// //                    "%code provides" blocks.
#line 42 "sql_parser.y" // lalr1.cc:377

  namespace sql
  {
    // Forward declaration of the Driver class
    class Driver;
  }

#line 5313 "sql_parser.hh" // lalr1.cc:377


#endif // !YY_YY_SQL_PARSER_HH_INCLUDED
