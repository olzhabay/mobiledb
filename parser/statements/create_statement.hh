/*!
 * @class CreateStmt
 * @brief Storing information for SQL INSERT query to execute
 * Usage:
 * CREATE TABLE [name] (
 * 		column_name1 data_type1 column_attribute1,
 * 		column_name2 data_type2 column_attrubute2,
 * 		...
 * 		)
 * data types:
 * -# BIT, INT, INTEGER, BIGINT, REAL, DOUBLE, FLOAT, DECIMAL, DATE, TIME, TIMESTAMP, DATETIME, YEAR, CHAR, VARCHAR, BINARY, TEXT
 * column attrubutes:
 * -# <empty>, NOT_NULL, NULL, AUTO_INC, UNIQUE_KEY, PRIMARY_KEY, KEY
 */

#pragma once
#include <vector>
#include <string>
#include <memory>
#include <future>
#include "sql_statement.hh"
#include "../sql_message.hh"

using namespace std;

namespace sql {

class CreateStmt: public Statement {
public:

	CreateStmt():Statement(CREATE) { }
	CreateStmt(string, bool, vector<tuple<string, string, string>>);
	virtual ~CreateStmt() {	}
	virtual bool is_equal(Statement*);
	bool is_equal(CreateStmt*);
			shared_future<shared_ptr<sql_message>> get_result();
			void set_result(shared_ptr<sql_message>);
			string &get_name();
			bool get_opt();
			vector<tuple<string, string, string>> get_definitions();
private:
	string name; //!< name of table
	bool opt_not_exists; //!< 'IF NOT EXISTS' option
	vector<tuple<string, string, string>> def_list; //!< definition list for table creation <NAME, DATA_TYPE, COLUMN_ATTRUBUTE>
			promise<shared_ptr<sql_message>> result; //!< result of query

			void generate_string();
};

}
