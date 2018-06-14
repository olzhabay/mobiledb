/*!
 * @class SelectStmt
 * @brief Storing information for SQL SELECT query to execute
 * Usage:
 * SELECT [type] [list of colunmn] FROM [list of tables]
 * 		WHERE [list of expressions]
 * 		GROUP BY [list of columns]
 * 		ORDER BY [list of columns]
 * 		LIMIT [integer]
 */

#pragma once
#include <vector>
#include <string>
#include <memory>
#include "sql_statement.hh"
#include "sql_table.hh"
#include "../sql_message.hh"

using namespace std;
namespace sql {
	class SelectStmt: public Statement {
	public:

		enum Type {
			NO_OPTION = 0,
			ALL = 1,
			DISTINCT = 2,
			DISTINCTROW = 3,
			FULL_JOIN = 4,
			LEFT_JOIN = 5,
			RIGHT_JOIN = 6,
			INNER_JOIN = 7,
		};

		SelectStmt() : Statement(SELECT) { }
		SelectStmt(Type, shared_ptr<Table>, shared_ptr<Table>, vector<tuple<string, string, string>>);
		SelectStmt(Type, vector<string>, vector<shared_ptr<Table>>, vector<tuple<string, string, string>>, vector<string>, vector<string>, int);
		virtual ~SelectStmt() {	}
		virtual bool is_equal(Statement* stmt);
		bool is_equal(SelectStmt* stmt);
        future<shared_ptr<sql_message>> get_result();
        void set_result(shared_ptr<sql_message>);
		Type get_select_type();
        vector<shared_ptr<Table>> get_tables();
		vector<tuple<string, string, string>> get_where();
		vector<string> get_column_list();

	private:
		Type select_type; //!< type of statement
		vector<string> column_list; //!< list of column attributes
		vector<shared_ptr<Table>> table_list; //!< nested tables
		vector<tuple<string, string, string>> where; //!< option 'WHERE [expressions]'
		vector<string> groupby; //!< option 'GROUP BY [list of columns]
		vector<string> orderby; //!< option 'ORDER BY [list of columns]
		int limit; //!< option 'LIMIT [integer]'
        promise<shared_ptr<sql_message>> result; //!< result of query

        void generate_string();
	};

}


