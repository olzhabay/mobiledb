%option header-file="sql_scanner.hh"
%option outfile="sql_scanner.cc"
%option noyywrap
%option case-insensitive
%option c++

%{

#include "sql_parser.hh"
#include "sql_scanner.hpp"
#include "sql_driver.hh"
#include <cstdlib>
#include <string>

int oldstate;

#define yyterminate() return sql::Parser::make_END(*driver.loc)
#define YY_USER_ACTION driver.loc->columns(yyleng);
%}


%%

%{
	driver.loc->step();
%}
 /* keywords */
ADD 		{ return sql::Parser::make_ADD(*driver.loc); }
ALL 		{ return sql::Parser::make_ALL(*driver.loc); }
ALTER 		{ return sql::Parser::make_ALTER(*driver.loc); }
ANALYZE 	{ return sql::Parser::make_ANALYZE(*driver.loc); }


AND 		{ return sql::Parser::make_AND(*driver.loc); }
ANY 		{ return sql::Parser::make_ANY(*driver.loc); }
AS 			{ return sql::Parser::make_AS(*driver.loc); }
ASC 		{ return sql::Parser::make_ASC(*driver.loc); }
AUTO_INCREMENT 	{ return sql::Parser::make_AUTO_INCREMENT(*driver.loc); }
BEFORE 		{ return sql::Parser::make_BEFORE(*driver.loc); }
BETWEEN 	{ return sql::Parser::make_BETWEEN(*driver.loc); }
INT8|BIGINT 	{ return sql::Parser::make_BIGINT(*driver.loc); }
BINARY 		{ return sql::Parser::make_BINARY(*driver.loc); }
BIT 		{ return sql::Parser::make_BIT(*driver.loc); }
BLOB 		{ return sql::Parser::make_BLOB(*driver.loc); }
BOTH 		{ return sql::Parser::make_BOTH(*driver.loc); }
BY 		{ return sql::Parser::make_BY(*driver.loc); }
CALL 		{ return sql::Parser::make_CALL(*driver.loc); }
CASCADE 	{ return sql::Parser::make_CASCADE(*driver.loc); }
CASE 		{ return sql::Parser::make_CASE(*driver.loc); }
CHANGE 		{ return sql::Parser::make_CHANGE(*driver.loc); }
CHAR(ACTER)? 	{ return sql::Parser::make_CHAR(*driver.loc); }
CHECK 		{ return sql::Parser::make_CHECK(*driver.loc); }
COLLATE 	{ return sql::Parser::make_COLLATE(*driver.loc); }
COLUMN 		{ return sql::Parser::make_COLUMN(*driver.loc); }
COMMENT 	{ return sql::Parser::make_COMMENT(*driver.loc); }
CONDITION 	{ return sql::Parser::make_CONDITION(*driver.loc); }
CONSTRAINT 	{ return sql::Parser::make_CONSTRAINT(*driver.loc); }
CONTINUE 	{ return sql::Parser::make_CONTINUE(*driver.loc); }
CONVERT 	{ return sql::Parser::make_CONVERT(*driver.loc); }
CREATE 		{ return sql::Parser::make_CREATE(*driver.loc); }
CROSS 		{ return sql::Parser::make_CROSS(*driver.loc); }
CURRENT_DATE 	{ return sql::Parser::make_CURRENT_DATE(*driver.loc); }
CURRENT_TIME 	{ return sql::Parser::make_CURRENT_TIME(*driver.loc); }
CURRENT_TIMESTAMP { return sql::Parser::make_CURRENT_TIMESTAMP(*driver.loc); }
CURRENT_USER 	{ return sql::Parser::make_CURRENT_USER(*driver.loc); }
CURSOR 		{ return sql::Parser::make_CURSOR(*driver.loc); }
DATABASE 	{ return sql::Parser::make_DATABASE(*driver.loc); }
DATABASES 	{ return sql::Parser::make_DATABASES(*driver.loc); }
DATE 		{ return sql::Parser::make_DATE(*driver.loc); }
DATETIME 	{ return sql::Parser::make_DATETIME(*driver.loc); }
DAY_HOUR 	{ return sql::Parser::make_DAY_HOUR(*driver.loc); }
DAY_MICROSECOND { return sql::Parser::make_DAY_MICROSECOND(*driver.loc); }
DAY_MINUTE 	{ return sql::Parser::make_DAY_MINUTE(*driver.loc); }
DAY_SECOND 	{ return sql::Parser::make_DAY_SECOND(*driver.loc); }
NUMERIC|DEC|DECIMAL { return sql::Parser::make_DECIMAL(*driver.loc); }
DECLARE 	{ return sql::Parser::make_DECLARE(*driver.loc); }
DEFAULT 	{ return sql::Parser::make_DEFAULT(*driver.loc); }
DELAYED 	{ return sql::Parser::make_DELAYED(*driver.loc); }
DELETE 		{ return sql::Parser::make_DELETE(*driver.loc); }
DESC 		{ return sql::Parser::make_DESC(*driver.loc); }
DESCRIBE 	{ return sql::Parser::make_DESCRIBE(*driver.loc); }
DETERMINISTIC 	{ return sql::Parser::make_DETERMINISTIC(*driver.loc); }
DISTINCT 	{ return sql::Parser::make_DISTINCT(*driver.loc); }
DISTINCTROW 	{ return sql::Parser::make_DISTINCTROW(*driver.loc); }
DIV 		{ return sql::Parser::make_DIV(*driver.loc); }
FLOAT8|DOUBLE 	{ return sql::Parser::make_DOUBLE(*driver.loc); }
DROP 		{ return sql::Parser::make_DROP(*driver.loc); }
DUAL 		{ return sql::Parser::make_DUAL(*driver.loc); }
EACH 		{ return sql::Parser::make_EACH(*driver.loc); }
ELSE 		{ return sql::Parser::make_ELSE(*driver.loc); }
ELSEIF 		{ return sql::Parser::make_ELSEIF(*driver.loc); }
ENUM 		{ return sql::Parser::make_ENUM(*driver.loc); }
ESCAPED 	{ return sql::Parser::make_ESCAPED(*driver.loc); }
EXISTS 		{ return sql::Parser::make_EXISTS(*driver.loc); }
EXIT 		{ return sql::Parser::make_EXIT(*driver.loc); }
EXPLAIN 	{ return sql::Parser::make_EXPLAIN(*driver.loc); }
FETCH 		{ return sql::Parser::make_FETCH(*driver.loc); }
FLOAT4? 	{ return sql::Parser::make_FLOAT(*driver.loc); }
FOR 		{ return sql::Parser::make_FOR(*driver.loc); }
FORCE 		{ return sql::Parser::make_FORCE(*driver.loc); }
FOREIGN 	{ return sql::Parser::make_FOREIGN(*driver.loc); }
FROM 		{ return sql::Parser::make_FROM(*driver.loc); }
FULL		{ return sql::Parser::make_FULL(*driver.loc); }
FULLTEXT 	{ return sql::Parser::make_FULLTEXT(*driver.loc); }
GRANT 		{ return sql::Parser::make_GRANT(*driver.loc); }
GROUP 		{ return sql::Parser::make_GROUP(*driver.loc); }
HAVING 		{ return sql::Parser::make_HAVING(*driver.loc); }
IF 		{ return sql::Parser::make_IF(*driver.loc); }
IGNORE 		{ return sql::Parser::make_IGNORE(*driver.loc); }
IN 		{ return sql::Parser::make_IN(*driver.loc); }
INFILE 		{ return sql::Parser::make_INFILE(*driver.loc); }
INNER 		{ return sql::Parser::make_INNER(*driver.loc); }
INOUT 		{ return sql::Parser::make_INOUT(*driver.loc); }
INSENSITIVE 	{ return sql::Parser::make_INSENSITIVE(*driver.loc); }
INSERT 		{ return sql::Parser::make_INSERT(*driver.loc); }
INT4?|INTEGER 	{ return sql::Parser::make_INTEGER(*driver.loc); }
INTERVAL 	{ return sql::Parser::make_INTERVAL(*driver.loc); }
INTO 		{ return sql::Parser::make_INTO(*driver.loc); }
IS 		{ return sql::Parser::make_IS(*driver.loc); }
ITERATE 	{ return sql::Parser::make_ITERATE(*driver.loc); }
JOIN 		{ return sql::Parser::make_JOIN(*driver.loc); }
INDEX|KEY 	{ return sql::Parser::make_KEY(*driver.loc); }
KEYS 		{ return sql::Parser::make_KEYS(*driver.loc); }
KILL 		{ return sql::Parser::make_KILL(*driver.loc); }
LEADING 	{ return sql::Parser::make_LEADING(*driver.loc); }
LEAVE 		{ return sql::Parser::make_LEAVE(*driver.loc); }
LEFT 		{ return sql::Parser::make_LEFT(*driver.loc); }
LIKE 		{ return sql::Parser::make_LIKE(*driver.loc); }
LIMIT 		{ return sql::Parser::make_LIMIT(*driver.loc); }
LINES 		{ return sql::Parser::make_LINES(*driver.loc); }
LOAD 		{ return sql::Parser::make_LOAD(*driver.loc); }
LOCALTIME 	{ return sql::Parser::make_LOCALTIME(*driver.loc); }
LOCALTIMESTAMP 	{ return sql::Parser::make_LOCALTIMESTAMP(*driver.loc); }
LOCK 		{ return sql::Parser::make_LOCK(*driver.loc); }
LONG 		{ return sql::Parser::make_LONG(*driver.loc); }
LONGBLOB 	{ return sql::Parser::make_LONGBLOB(*driver.loc); }
LONGTEXT 	{ return sql::Parser::make_LONGTEXT(*driver.loc); }
LOOP 		{ return sql::Parser::make_LOOP(*driver.loc); }
LOW_PRIORITY 	{ return sql::Parser::make_LOW_PRIORITY(*driver.loc); }
MATCH 		{ return sql::Parser::make_MATCH(*driver.loc); }
MEDIUMBLOB 	{ return sql::Parser::make_MEDIUMBLOB(*driver.loc); }
MIDDLEINT|MEDIUMINT { return sql::Parser::make_MEDIUMINT(*driver.loc); }
MEDIUMTEXT 	{ return sql::Parser::make_MEDIUMTEXT(*driver.loc); }
MINUTE_MICROSECOND { return sql::Parser::make_MINUTE_MICROSECOND(*driver.loc); }
MINUTE_SECOND 	{ return sql::Parser::make_MINUTE_SECOND(*driver.loc); }
MOD 		{ return sql::Parser::make_MOD(*driver.loc); }
MODIFIES 	{ return sql::Parser::make_MODIFIES(*driver.loc); }
NATURAL 	{ return sql::Parser::make_NATURAL(*driver.loc); }
NOT 		{ return sql::Parser::make_NOT(*driver.loc); }
NULL 		{ return sql::Parser::make_NULLX(*driver.loc); }
NUMBER 		{ return sql::Parser::make_NUMBER(*driver.loc); }
ON 		{ return sql::Parser::make_ON(*driver.loc); }
DUPLICATE 	{ return sql::Parser::make_DUPLICATE(*driver.loc); }
OPTIMIZE 	{ return sql::Parser::make_OPTIMIZE(*driver.loc); }
OPTION 		{ return sql::Parser::make_OPTION(*driver.loc); }
OPTIONALLY 	{ return sql::Parser::make_OPTIONALLY(*driver.loc); }
OR 		{ return sql::Parser::make_OR(*driver.loc); }
ORDER 		{ return sql::Parser::make_ORDER(*driver.loc); }
OUT 		{ return sql::Parser::make_OUT(*driver.loc); }
OUTER 		{ return sql::Parser::make_OUTER(*driver.loc); }
OUTFILE 	{ return sql::Parser::make_OUTFILE(*driver.loc); }
PRECISION 	{ return sql::Parser::make_PRECISION(*driver.loc); }
PRIMARY 	{ return sql::Parser::make_PRIMARY(*driver.loc); }
PROCEDURE 	{ return sql::Parser::make_PROCEDURE(*driver.loc); }
PURGE 		{ return sql::Parser::make_PURGE(*driver.loc); }
QUICK 		{ return sql::Parser::make_QUICK(*driver.loc); }
READ 		{ return sql::Parser::make_READ(*driver.loc); }
READS 		{ return sql::Parser::make_READS(*driver.loc); }
REAL 		{ return sql::Parser::make_REAL(*driver.loc); }
REFERENCES 	{ return sql::Parser::make_REFERENCES(*driver.loc); }
REGEXP|RLIKE 	{ return sql::Parser::make_REGEXP(*driver.loc); }
RELEASE 	{ return sql::Parser::make_RELEASE(*driver.loc); }
RENAME 		{ return sql::Parser::make_RENAME(*driver.loc); }
REPEAT 		{ return sql::Parser::make_REPEAT(*driver.loc); }
REPLACE 	{ return sql::Parser::make_REPLACE(*driver.loc); }
REQUIRE 	{ return sql::Parser::make_REQUIRE(*driver.loc); }
RESTRICT 	{ return sql::Parser::make_RESTRICT(*driver.loc); }
RETURN 		{ return sql::Parser::make_RETURN(*driver.loc); }
REVOKE 		{ return sql::Parser::make_REVOKE(*driver.loc); }
RIGHT 		{ return sql::Parser::make_RIGHT(*driver.loc); }
ROLLUP 		{ return sql::Parser::make_ROLLUP(*driver.loc); }
SCHEMA 		{ return sql::Parser::make_SCHEMA(*driver.loc); }
SCHEMAS 	{ return sql::Parser::make_SCHEMAS(*driver.loc); }
SELECT 		{ return sql::Parser::make_SELECT(*driver.loc); }
SENSITIVE 	{ return sql::Parser::make_SENSITIVE(*driver.loc); }
SEPARATOR 	{ return sql::Parser::make_SEPARATOR(*driver.loc); }
SET 		{ return sql::Parser::make_SET(*driver.loc); }
SHOW 		{ return sql::Parser::make_SHOW(*driver.loc); }
INT2|SMALLINT 	{ return sql::Parser::make_SMALLINT(*driver.loc); }
SOME 		{ return sql::Parser::make_SOME(*driver.loc); }
SONAME 		{ return sql::Parser::make_SONAME(*driver.loc); }
SPATIAL 	{ return sql::Parser::make_SPATIAL(*driver.loc); }
SPECIFIC 	{ return sql::Parser::make_SPECIFIC(*driver.loc); }
SQL 		{ return sql::Parser::make_SQL(*driver.loc); }
SQLEXCEPTION 	{ return sql::Parser::make_SQLEXCEPTION(*driver.loc); }
SQLSTATE 	{ return sql::Parser::make_SQLSTATE(*driver.loc); }
SQLWARNING 	{ return sql::Parser::make_SQLWARNING(*driver.loc); }
BIG_RESULT 	{ return sql::Parser::make_BIG_RESULT(*driver.loc); }
CALC_FOUND_ROWS { return sql::Parser::make_CALC_FOUND_ROWS(*driver.loc); }
SMALL_RESULT { return sql::Parser::make_SMALL_RESULT(*driver.loc); }
SSL 		{ return sql::Parser::make_SSL(*driver.loc); }
STARTING 	{ return sql::Parser::make_STARTING(*driver.loc); }
STRAIGHT_JOIN 	{ return sql::Parser::make_STRAIGHT_JOIN(*driver.loc); }
TABLE 		{ return sql::Parser::make_TABLE(*driver.loc); }
TEMPORARY 	{ return sql::Parser::make_TEMPORARY(*driver.loc); }
TERMINATED 	{ return sql::Parser::make_TERMINATED(*driver.loc); }
TEXT 		{ return sql::Parser::make_TEXT(*driver.loc); }
THEN 		{ return sql::Parser::make_THEN(*driver.loc); }
TIME 		{ return sql::Parser::make_TIME(*driver.loc); }
TIMESTAMP 	{ return sql::Parser::make_TIMESTAMP(*driver.loc); }
INT1|TINYINT 	{ return sql::Parser::make_TINYINT(*driver.loc); }
TINYTEXT 	{ return sql::Parser::make_TINYTEXT(*driver.loc); }
TO 		{ return sql::Parser::make_TO(*driver.loc); }
TRAILING 	{ return sql::Parser::make_TRAILING(*driver.loc); }
TRIGGER 	{ return sql::Parser::make_TRIGGER(*driver.loc); }
UNDO 		{ return sql::Parser::make_UNDO(*driver.loc); }
UNION 		{ return sql::Parser::make_UNION(*driver.loc); }
UNIQUE 		{ return sql::Parser::make_UNIQUE(*driver.loc); }
UNLOCK 		{ return sql::Parser::make_UNLOCK(*driver.loc); }
UNSIGNED 	{ return sql::Parser::make_UNSIGNED(*driver.loc); }
UPDATE 		{ return sql::Parser::make_UPDATE(*driver.loc); }
USAGE 		{ return sql::Parser::make_USAGE(*driver.loc); }
USE 		{ return sql::Parser::make_USE(*driver.loc); }
USING 		{ return sql::Parser::make_USING(*driver.loc); }
UTC_DATE 	{ return sql::Parser::make_UTC_DATE(*driver.loc); }
UTC_TIME 	{ return sql::Parser::make_UTC_TIME(*driver.loc); }
UTC_TIMESTAMP 	{ return sql::Parser::make_UTC_TIMESTAMP(*driver.loc); }
VALUES	 	{ return sql::Parser::make_VALUES(*driver.loc); }
VARBINARY 	{ return sql::Parser::make_VARBINARY(*driver.loc); }
VARCHAR(ACTER)? { return sql::Parser::make_VARCHAR(*driver.loc); }
VARYING 	{ return sql::Parser::make_VARYING(*driver.loc); }
WHEN 		{ return sql::Parser::make_WHEN(*driver.loc); }
WHERE 		{ return sql::Parser::make_WHERE(*driver.loc); }
WHILE 		{ return sql::Parser::make_WHILE(*driver.loc); }
WITH 		{ return sql::Parser::make_WITH(*driver.loc); }
WRITE 		{ return sql::Parser::make_WRITE(*driver.loc); }
XOR 		{ return sql::Parser::make_XOR(*driver.loc); }
YEAR 		{ return sql::Parser::make_YEAR(*driver.loc); }
ZEROFILL 	{ return sql::Parser::make_ZEROFILL(*driver.loc); }

 /* numbers */
-?[0-9]+ { return sql::Parser::make_INTNUM(atoi(yytext), *driver.loc); }
-?[0-9]+"."[0-9]* |
-?"."[0-9]+ |
-?[0-9]+E[-+]?[0-9]+ |
-?[0-9]+"."[0-9]*E[-+]?[0-9]+ |
-?"."[0-9]+E[-+]?[0-9]+ { return sql::Parser::make_APPROXNUM(atof(yytext), *driver.loc); }

 /* booleans */
TRUE 		{ return sql::Parser::make_BOOL(true, *driver.loc); }
FALSE 		{ return sql::Parser::make_BOOL(false, *driver.loc); }

 /* strings */
'(\\.|''|[^'\n])*' |
\"(\\.|\"\"|[^"\n])*\" { return sql::Parser::make_STRING(yytext, *driver.loc); }
'(\\.|[^'\n])*$ { driver.error(*driver.loc, "Unterminated string"); }
\"(\\.|[^"\n])*$ {  driver.error(*driver.loc, "Unterminated string"); }


 /* hex strings */
X'[0-9A-F]+' |
0X[0-9A-F]+ { return sql::Parser::make_STRING(yytext, *driver.loc); }

 /* bit strings */
0B[01]+ |
B'[01]+' { return sql::Parser::make_STRING(yytext, *driver.loc); }

 /* operators */
"."		{ return sql::Parser::make_DOT(*driver.loc); }
"*"		{ return sql::Parser::make_MULTIPLY(*driver.loc); }
"("		{ return sql::Parser::make_BRACKET_O(*driver.loc); }
")"		{ return sql::Parser::make_BRACKET_C(*driver.loc); }
";"		{ return sql::Parser::make_SEMICOLON(*driver.loc); }
"," |
"&&" 	{ return sql::Parser::make_AND(*driver.loc); }
"||" 	{ return sql::Parser::make_OR(*driver.loc); }
"=" 	{ return sql::Parser::make_COMPARISON("=", *driver.loc); }
"<=>" 	{ return sql::Parser::make_COMPARISON("<=>", *driver.loc); }
">=" 	{ return sql::Parser::make_COMPARISON(">=", *driver.loc); }
">" 	{ return sql::Parser::make_COMPARISON(">", *driver.loc); }
"<=" 	{ return sql::Parser::make_COMPARISON("<=", *driver.loc); }
"<" 	{ return sql::Parser::make_COMPARISON("<", *driver.loc); }
"!=" 	{ return sql::Parser::make_COMPARISON("!=", *driver.loc); }
"<>" 	{ return sql::Parser::make_COMPARISON("<>", *driver.loc); }
"<<" 	{ return sql::Parser::make_SHIFT("<<", *driver.loc); }
">>" 	{ return sql::Parser::make_SHIFT(">>", *driver.loc); }
":=" 	{ return sql::Parser::make_ASSIGN(*driver.loc); }
<<EOF>> { return sql::Parser::make_END(*driver.loc); }

 /* user variables */
@[0-9a-z_.$]+ |
@\"[^"\n]+\" |
@`[^`\n]+` |
@'[^'\n]+' { return sql::Parser::make_USERVAR(yytext, *driver.loc); }

@\"[^"\n]*$ { driver.error(*driver.loc, "Unterminated quoted user variable");} 
@`[^`\n]*$ {  driver.error(*driver.loc, "Unterminated quoted user variable"); }
@'[^'\n]*$ {  driver.error(*driver.loc, "Unterminated quoted user variable"); }

 /* names */
[A-Za-z][A-Za-z0-9_]* { 
 	return sql::Parser::make_NAME(yytext, *driver.loc); 
	}
`[^`/\\.\n]+` { 
	return sql::Parser::make_NAME(yytext, *driver.loc); 
	}
`[^`\n]*$ { driver.error(*driver.loc, "Unterminated quated name"); 
	}

 /* everything else */
[ \t\n]  ;/* whitespace */


%%

namespace sql {
	Scanner::Scanner() : yyFlexLexer() { }
	
	Scanner::~Scanner() { }

	void Scanner::set_debug(bool b) {
		yy_flex_debug = b;
	}
}

#ifndef yylex
#undef yylex
#endif

int yyFlexLexer::yylex() {
	cerr << "call yyFlexLexer::yylex()!" << endl;
	return 0;
}
