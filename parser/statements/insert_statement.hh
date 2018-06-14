/*!
 * @class InsertStmt
 * @brief Storing information for SQL INSERT query to execute
 * - Usage1:
 * INSERT INTO [name] [list of colimns]
 * 		VALUES [list of values]
 * 		ON DUPLICATE KEY UPDATE [set of <column, value>]
 * - Usage2:
 * INSERT INTO [name]
 * 		SET [set of <column, value>]
 * 		ON DUPLICATE KEY UPDATE [set of <column, value>]
 * - Usage3:
 * INSERT INTO [name] [list of columns] [select statemetn]
 * 		ON DUPLICATE KEY UPDATE [set of <column, value>]
 */

#pragma once
#include <string>
#include <vector>
#include <memory>
#include <future>
#include "sql_statement.hh"
#include "select_statement.hh"
#include "../sql_message.hh"

using namespace std;
namespace sql {
	class InsertStmt: public Statement {
	public:
		InsertStmt() : Statement(INSERT) { }
		InsertStmt(string, vector<string>, vector<string>, vector<pair<string, string>>);
		InsertStmt(string, vector<pair<string, string>>, vector<pair<string, string>>);
		InsertStmt(string, vector<string>, shared_ptr<SelectStmt>, vector<pair<string, string>>);
		virtual ~InsertStmt() { }
		virtual bool is_equal(Statement* stmt);
		bool is_equal(InsertStmt* stmt);
        future<shared_ptr<sql_message>> get_result();
        void set_result(shared_ptr<sql_message>);
		string &get_name();
		vector<pair<string, string>> get_insert_list();
		vector<pair<string, string>> get_ondupupdate();
		shared_ptr<SelectStmt> get_select_stmt();

	private:
		string name; //!< name of table
		vector<pair<string, string>> insert_list; //!< values to insert; <column, value>
		vector<pair<string, string>> ondupupdate; //!< option 'ON DUPLICATE KEY UPDATE [set list]
		shared_ptr<SelectStmt> select_stmt; //!< select statement
        promise<shared_ptr<sql_message>> result; //!< result of statement

        void generate_string();
	};
}
