%output  "sql_parser.cc"
%defines "sql_parser.hh"
%language "C++"

%defines
%define api.namespace {sql}
%define parser_class_name {Parser}
%define parse.error verbose
%define parse.assert
%define api.token.constructor
%define api.value.type variant
%locations

%lex-param   { Driver &driver }
%parse-param { Driver &driver }


%code requires {
#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include "location.hh"
#include "sql_driver.hh"
#include "position.hh"
#include "../statements/sql_statement.hh"
#include "../statements/sql_table.hh"
#include "../statements/delete_statement.hh"
#include "../statements/drop_statement.hh"
#include "../statements/update_statement.hh"
#include "../statements/insert_statement.hh"
#include "../statements/select_statement.hh"
#include "../statements/create_statement.hh"

class Driver;
class Scanner;

using namespace std;

}

%code provides {
  namespace sql
  {
    // Forward declaration of the Driver class
    class Driver;
  }
}

%code{

#include "sql_parser.hh"
#include "sql_scanner.hpp"

using namespace std;
#define yylex driver.get_scanner()->yylex

}


%token <std::string> STRING
%token <std::string> USERVAR
%token <std::string> NAME
%token <int> INTNUM
%token <bool> BOOL
%token <double> APPROXNUM
%token <int> NOTEQUALS LESSEQ GREATEREQ

%type <std::vector<std::shared_ptr<sql::Statement>>> stmt_list
%type <std::shared_ptr<sql::Statement>> stmt

%type <std::shared_ptr<sql::InsertStmt>> insert_stmt
%type <std::shared_ptr<sql::SelectStmt>> select_stmt
%type <std::shared_ptr<sql::SelectStmt>> join_table
%type <std::shared_ptr<sql::DeleteStmt>> delete_stmt
%type <std::shared_ptr<sql::UpdateStmt>> update_stmt
%type <std::shared_ptr<sql::DropStmt>> drop_stmt
%type <std::shared_ptr<sql::CreateStmt>> create_stmt
%type <std::vector<std::string>> opt_groupby opt_orderby string_list
%type <int> opt_limit
%type <std::vector<std::tuple<std::string, std::string, std::string>>> expr_list join_condition opt_where create_col_list
%type <std::tuple<std::string, std::string, std::string>> expr create_definition
%type <std::vector<std::shared_ptr<sql::Table>>> table_references
%type <std::shared_ptr<sql::Table>> table_factor
%type <std::string> opt_as_alias column_atts data_type expr_data
%type <sql::SelectStmt::Type> join_opts 
%type <sql::SelectStmt::Type> select_opts
%type <bool> opt_if_not_exists
%type <std::pair<std::string, std::string>> expr_pair
%type <std::vector<std::pair<std::string, std::string>>> opt_ondupupdate pair_list

%right ASSIGN
%left OR
%left XOR
%left ANDOP
%nonassoc IN IS LIKE REGEXP
%left NOT 
%left BETWEEN
%left <std::string> COMPARISON /* = <> < > <= >= <=> */
%left <std::string> SHIFT /* << >> */
%left MOD
%nonassoc UMINUS

%token ADD
%token ALL
%token ALTER
%token ANALYZE
%token AND
%token ANY
%token APPEND
%token AS
%token ASC
%token AUTO_INCREMENT
%token BEFORE
%token BETWEEN
%token BIGINT
%token BINARY
%token BIT
%token BLOB
%token BOTH
%token BY
%token CALL
%token CASCADE
%token CASE
%token CHANGE
%token CHAR
%token CHECK
%token COLLATE
%token COLUMN
%token COMMENT
%token CONDITION
%token CONSTRAINT
%token CONTINUE
%token CONVERT
%token CREATE
%token CROSS
%token CURRENT_DATE
%token CURRENT_TIME
%token CURRENT_TIMESTAMP
%token CURRENT_USER
%token CURSOR
%token DATABASE
%token DATABASES
%token DATE
%token DATETIME
%token DAY_HOUR
%token DAY  
%token DAY_MICROSECOND
%token DAY_MINUTE
%token DAY_SECOND
%token DECIMAL
%token DECLARE
%token DEFAULT
%token DELAYED
%token DELETE
%token DESC
%token DESCRIBE
%token DETERMINISTIC
%token DISTINCT
%token DISTINCTROW
%token DIV
%token DOUBLE
%token DROP
%token DUAL
%token EACH
%token ELSE
%token ELSEIF
%token ENCLOSED
%token ENUM
%token ESCAPED
%token EXISTS
%token EXIT
%token EXPLAIN
%token FETCH
%token FLOAT
%token FOR
%token FORCE
%token FOREIGN
%token FROM
%token FULLTEXT
%token GRANT
%token GROUP
%token HAVING
%token HIGH
%token HIGH_PRIORITY
%token HOUR_MICROSECOND
%token HOUR_MINUTE
%token HOUR_SECOND
%token IF
%token IGNORE
%token IN
%token INDEX
%token INFILE
%token INNER
%token INOUT
%token INSENSITIVE
%token INSERT
%token INT
%token INTEGER
%token INTERVAL
%token INTO
%token ITERATE
%token JOIN
%token KEY
%token KEYS
%token KILL
%token LEADING
%token LEAVE
%token LEFT
%token LIKE
%token LIMIT
%token LINES
%token LOAD
%token LOCALTIME
%token LOCALTIMESTAMP
%token LOCK
%token LONG
%token LONGBLOB
%token LONGTEXT
%token LOOP
%token LOW
%token LOW_PRIORITY
%token MATCH
%token MEDIUMBLOB
%token MEDIUMINT
%token MEDIUMTEXT
%token MINUTE_MICROSECOND
%token MINUTE_SECOND
%token MOD
%token MODIFIES
%token NATURAL
%token NOT
%token NO_WRITE_TO_BINLOG
%token NULLX
%token NUMBER
%token ON
%token DUPLICATE
%token OPTIMIZE
%token OPTION
%token OPTIONALLY
%token OR
%token ORDER
%token OUT
%token OUTER
%token OUTFILE
%token PARTITIONED
%token PRECISION
%token PRIMARY
%token PRIORITY
%token PROCEDURE
%token PROJECTION
%token PURGE
%token QUICK
%token QUARTER
%token READ
%token READS
%token REAL
%token REFERENCES
%token REGEXP
%token RELEASE
%token RENAME
%token REPEAT
%token REPLACE
%token REQUIRE
%token RESTRICT
%token RETURN
%token REVOKE
%token RIGHT
%token ROLLUP
%token SAMPLE
%token SCHEMA
%token SCHEMAS
%token SECOND_MICROSECOND
%token SELECT
%token SENSITIVE
%token SEPARATOR
%token SET
%token SHOW
%token SMALLINT
%token SOME
%token SONAME
%token SPATIAL
%token SPECIFIC
%token SQL
%token SQLEXCEPTION
%token SQLSTATE
%token SQLWARNING
%token BIG_RESULT
%token CALC_FOUND_ROWS
%token SMALL_RESULT
%token SSL
%token STARTING
%token STRAIGHT_JOIN
%token TABLE
%token TEMPORARY
%token TEXT
%token TERMINATED
%token THEN
%token TIME
%token TIMESTAMP
%token TINYBLOB
%token TINYINT
%token TINYTEXT
%token TO
%token TRAILING
%token TRIGGER
%token UNDO
%token UNION
%token UNIQUE
%token UNLOCK
%token UNSIGNED
%token UPDATE
%token USAGE
%token USE
%token USING
%token UTC_DATE
%token UTC_TIME
%token UTC_TIMESTAMP
%token VALUES
%token VARBINARY
%token VARCHAR
%token VARYING
%token WHEN
%token WHERE
%token WHILE
%token WITH
%token WRITE
%token XOR
%token YEAR
%token YEAR_MONTH
%token ZEROFILL
%token WEEK
%token DO
%token MAX_QUERIES_PER_HOUR
%token MAX_UPDATES_PER_HOUR
%token MAX_CONNECTIONS_PER_HOUR
%token MAX_USER_CONNECTIONS
%token USER
%token TRUNCATE
%token FAST
%token MEDIUM
%token EXTENDED
%token CHANGED
%token LEAVES
%token MASTER
%token QUERY CACHE
%token SLAVE
%token BEGINT
%token COMMIT
%token START
%token TRANSACTION
%token NO
%token CHAIN
%token AUTOCOMMIT
%token SAVEPOINT
%token ROLLBACK
%token LOCAL
%token TABLES
%token ISOLATION
%token LEVEL
%token GLOBAL
%token SESSION
%token UNCOMMITTED
%token COMMITTED
%token REPEATABLE
%token SERIALIZABLE
%token IDENTIFIED
%token PASSWORD
%token PRIVILEGES
%token BACKUP
%token CHECKSUM
%token REPAIR
%token USE_FRM
%token RESTORE
%token CHARACTER
%token COLLATION
%token COLUMNS
%token ENGINE
%token LOGS
%token STATUS
%token STORAGE
%token ENGINES
%token ERRORS
%token GRANTS
%token INNODB
%token PROCESSLIST
%token TRIGGERS
%token VARIABLES
%token WARNINGS
%token FLUSH
%token HOSTS
%token DES_KEY_FILE
%token USER_RESOURCES
%token CONNECTION
%token RESET
%token PREPARE
%token DEALLOCATE
%token EXECUTE
%token WORK
%token BTREE
%token HASH
%token BDB
%token OPEN
%token FULL
%token FSUBSTRING
%token FTRIM
%token FDATE_ADD FDATE_SUB
%token FCOUNT
%token FUPPER
%token FCAST
%token FCOALESCE
%token FCONVERT
%token FSUM
%token FAVG
%token FMIN
%token FMAX
%token END 0 "end of file"
%token BRACKET_O
%token BRACKET_C
%token SEMICOLON
%token DOT
%token MULTIPLY

%start input
%%

input:
 stmt_list
	{
	driver.set_result($1); 
	}
 ;	 


stmt_list:
 stmt SEMICOLON {
	$$.push_back($1);
 }
 | stmt_list stmt SEMICOLON { 
	$1.push_back($2);
	$$ = $1;
 }
 ;

 /* expressions */

expr_data:
 NAME {
	$$ = $1; }
 | NAME DOT NAME {
	$$ = $1 + "." + $3; }
 | STRING {
	$$ = $1.substr(1, $1.size()-2); }
 | INTNUM { 
	$$ = to_string($1); }
 | APPROXNUM {
	$$ = to_string($1); }
 | BOOL {
	$$ = $1 ? "true" : "false"; }
 ;

expr:
 expr_data COMPARISON expr_data {
	$$ = make_tuple($1, $2, $3); }	
 ;


expr_list:
 expr
	{ $$.push_back($1); }
 | expr AND expr_list
	{ $3.push_back($1); $$ = $3; }
 | BRACKET_O expr_list BRACKET_C
	{ $$ = $2; }
 ;

expr_pair:
 expr_data COMPARISON expr_data {
	$$ = make_pair($1, $3); }


pair_list:
 expr_pair {
	$$.push_back($1); }
 | expr_pair AND pair_list{
	$3.push_back($1); $$ = $3; }
 | BRACKET_O pair_list BRACKET_C {
	$$ = $2; }

/* statements: select statement */
stmt:
 select_stmt
	{ $$ = $1; }
 ;

select_stmt:
 SELECT select_opts string_list FROM table_references opt_where opt_groupby opt_orderby opt_limit {
	$$ = make_shared<SelectStmt>($2, $3, $5, $6, $7, $8, $9); }
 | BRACKET_O select_stmt BRACKET_C
	{ $$ = $2; }
 ;

select_opts:
 /* nil */
	{ $$ = sql::SelectStmt::Type::NO_OPTION; }
| MULTIPLY
	{ $$ = sql::SelectStmt::Type::ALL; }
| ALL
	{ $$ = sql::SelectStmt::Type::ALL; }
| DISTINCT
	{ $$ = sql::SelectStmt::Type::DISTINCT; }
| DISTINCTROW
	{ $$ = sql::SelectStmt::Type::DISTINCTROW; }
 ;

 /* statements: join statement */

stmt:
 join_table
	{ $$ = $1; }
 ;

join_table:
 table_factor join_opts JOIN table_factor join_condition {
	$$ = make_shared<SelectStmt>($2, $1, $4, $5); }
 | BRACKET_O join_table BRACKET_C
	{ $$ = $2; }
 ;

join_condition:
 ON expr_list
	{ $$ = $2; }
 | /* nil */
	{ }
 ;

join_opts:
 FULL
	{ $$ = sql::SelectStmt::Type::FULL_JOIN; }
 | LEFT
	{ $$ = sql::SelectStmt::Type::LEFT_JOIN; }
 | RIGHT
	{ $$ = sql::SelectStmt::Type::RIGHT_JOIN; }
 | INNER
	{ $$ = sql::SelectStmt::Type::INNER_JOIN; }
 | /* nil */
	{ $$ = sql::SelectStmt::Type::FULL_JOIN; }
 ;

 /* statements: delete statement */
stmt:
 delete_stmt
	{ $$ = $1; }
 ;

delete_stmt:
 DELETE string_list FROM NAME opt_where opt_orderby opt_limit {
	$$ = make_shared<DeleteStmt>($2, $4, $5, $6, $7); }
;

 /* statements: insert statement */
stmt: 
 insert_stmt 
	{ $$ = $1; }
 ;

insert_stmt: 
 INSERT opt_into NAME string_list VALUES string_list opt_ondupupdate {
	$$ = make_shared<InsertStmt>($3, $4, $6, $7);
	}
 | INSERT opt_into NAME SET pair_list opt_ondupupdate {
	$$ = make_shared<InsertStmt>($3, $5, $6);
	}
 | INSERT opt_into NAME string_list select_stmt opt_ondupupdate {
	$$ = make_shared<InsertStmt>($3, $4, $5, $6);
	} 
 ;

 /* update */
stmt: 
 update_stmt 
	{ $$ = $1; }
 ;

update_stmt: 
 UPDATE NAME SET pair_list opt_where opt_orderby opt_limit {
	$$ = make_shared<UpdateStmt>($2, $4, $5, $6, $7); }
 ;

 /* create statement */
stmt: 
 create_stmt 
	{ $$ = $1; }
 ;

create_stmt:
 CREATE TABLE opt_if_not_exists NAME create_col_list {
	$$ = make_shared<CreateStmt>($4, $3, $5); }
;

create_col_list: 
 /* nil */
	{ }
 | create_definition 
	{ $$.push_back($1); }
 | create_col_list AND create_definition 
	{ $1.push_back($3); $$ = $1;  }
 | BRACKET_O create_col_list BRACKET_C
	{ $$ = $2; }
 ;

create_definition:
 NAME data_type column_atts {
	$$ = make_tuple($1, $2, $3); }
 ;

 /* Drop Statement */

stmt:
 drop_stmt
	{ $$ = $1; }
 ;

drop_stmt:
 DROP TABLE NAME { 
	$$ = make_shared<DropStmt>($3); }
 ;

string_list:
 /* nil */
	{ }
 | expr_data
	{ $$.push_back($1); }
 | string_list AND expr_data
	{ $1.push_back($3); $$ = $1; }
 | BRACKET_O string_list BRACKET_C
	{ $$ = $2; }
 ;


column_atts: 
 /* nil */ 
	{ $$ = "NO_ATT"; }
 | NOT NULLX 
	{ $$ = "NOT_NULLX"; }
 | NULLX 
	{ $$ = "NULLX"; }
 | AUTO_INCREMENT
	{ $$ = "AUTO_INC"; }
 | UNIQUE KEY 
	{ $$ = "UNIQUE_KEY"; }
 | PRIMARY KEY 
	{ $$ = "PRIMARY_KEY"; }
 | KEY 
	{ $$ = "KEY"; }
 ;

data_type:
 BIT 
	{ $$ = "BIT"; } 
 | INT
	{ $$ = "INT"; }
 | INTEGER
	{ $$ = "INTEGER"; }
 | BIGINT
	{ $$ = "BIGINT"; }
 | REAL
	{ $$ = "REAL"; }
 | DOUBLE
	{ $$ = "DOUBLE"; }
 | FLOAT
	{ $$ = "FLOAT"; }
 | DECIMAL
	{ $$ = "DECIMAL"; }
 | DATE 
	{ $$ = "DATE"; }
 | TIME 
	{ $$ = "TIME"; }
 | TIMESTAMP 
	{ $$ = "TIMESTAMP"; }
 | DATETIME 
	{ $$ = "DATETIME"; }
 | YEAR 
	{ $$ = "YEAR"; }
 | CHAR
	{ $$ = "CHAR"; }
 | VARCHAR
	{ $$ = "VARCHAR"; }
 | BINARY
	{ $$ = "BINARY"; }
 | TEXT
	{ $$ = "TEXT"; }
 ;

opt_as_alias: 
 AS NAME 
	{ $$ = $2; }
 | /* nil */ 
	{  }
 ;

opt_if_not_exists: 
 /* nil */ 
	{ $$ = false; }
 | IF NOT EXISTS 
	{ $$ = true; }
 ;

opt_into: 
 INTO 
 | /* nil */
 ;

opt_ondupupdate: 
 /* nil */ 
	{ }
 | ON DUPLICATE KEY UPDATE pair_list 
	{ $$ = $5; }
 ;

opt_where: 
 /* nil */ 
	{ }
 | WHERE expr_list
	{ $$ = $2; }

opt_groupby: 
 /* nil */ 
	{ }
 | GROUP BY string_list  
	{ $$ = $3; }
 ;

opt_orderby: 
 /* nil */ 
	{ }
 | ORDER BY string_list 
	{ $$ = $3; }
 ;

opt_limit: 
 /* nil */ 
	{ $$ = 0; }
 | LIMIT INTNUM 
	{ $$ = $2; }
 ;

table_references: 
 table_factor 
	{ $$.push_back($1); }
 | table_references AND table_factor
	{ $1.push_back($3); $$ = $1; }
 | BRACKET_O table_references BRACKET_C
	{ $$ = $2; }
 ;

table_factor:
 NAME opt_as_alias {
	$$ = make_shared<Table>(Table::DEFAULT, $1, $2); }
 | join_table opt_as_alias {
	$$ = make_shared<Table>(Table::SELECT, $1, $2); }
 | select_stmt opt_as_alias {
	$$ = make_shared<Table>(Table::SELECT, $1, $2); }
 | BRACKET_O table_factor BRACKET_C
	{ $$ = $2; }
 ;


%%

/* empty */
void sql::Parser::error(const location_type& l, const std::string& m) {
	driver.error(l, m);
}
