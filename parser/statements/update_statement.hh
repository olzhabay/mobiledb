/*!
 * @class UpdateStmt
 * @brief Storing information for SQL SELECT query to execute
 * Usage:
 * UPDATE [name] SET [set of <column, value>]
 * 		WHERE [list of expressions]
 * 		ORDER BY [list of columns]
 * 		LIMIT [integer]
 */

#pragma once
#include <vector>
#include <string>
#include "sql_statement.hh"
#include "sql_table.hh"
#include "../sql_message.hh"

using namespace std;

namespace sql {

class UpdateStmt: public Statement {
public:
	UpdateStmt() : Statement(UPDATE) { }
	UpdateStmt(string, vector<pair<string, string>>, vector<tuple<string, string, string>>, vector<string>, int);
	virtual ~UpdateStmt() {}
	virtual bool is_equal(Statement* stmt);
	bool is_equal(UpdateStmt* stmt);
	future<shared_ptr<sql_message>> get_result();
	void set_result(shared_ptr<sql_message>);

private:
	string name; //!< table name
	vector<pair<string, string>> update_list; //!< set of assigning values <column, value>
	vector<tuple<string, string, string>> where; //!< option 'WHERE [expressions]'
	vector<string> orderby; //!< option 'ORDER BY [list of columns]
	int limit; //!< option 'LIMIT [integer]'
	promise<shared_ptr<sql_message>> result; //!< result of query

	void generate_string();
};

} // namespace sql
