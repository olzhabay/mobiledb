#pragma once
#include <string>
#include "sql_statement.hh"
#include "../sql_message.hh"

using namespace std;

namespace sql {

class DropStmt: public Statement {
	public:
	DropStmt() : Statement(DROP) { }
	DropStmt(std::string);
	virtual ~DropStmt() { }
			virtual bool is_equal(Statement*);
	bool is_equal(DropStmt*);
	string &get_name();
	future<shared_ptr<sql_message>> get_result();
	void set_result(shared_ptr<sql_message>);
	private:
	string name; //!< name of table
	void generate_string();
	promise<shared_ptr<sql_message>> result; //!< result of query
};

} // namespace sql
