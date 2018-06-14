#include <sstream>
#include "drop_statement.hh"

using namespace std;

namespace sql {

DropStmt::DropStmt(string name_) :
	Statement(DROP), name(name_) {
	generate_string();
}

bool DropStmt::is_equal(Statement* stmt) {
	return stmt->get_type() == DROP ? is_equal(dynamic_cast<DropStmt*>(stmt)) : false;
}

bool DropStmt::is_equal(DropStmt* stmt) {
	return name == stmt->name;
}

void DropStmt::generate_string() {
	stringstream ss;
	ss << "DROP " << name;
	stmt_str = ss.str();
}

string& DropStmt::get_name() {
	return name;
}

future<shared_ptr<sql_message>> DropStmt::get_result() {
	return result.get_future();
}

void DropStmt::set_result(shared_ptr<sql_message> msg) {
	result.set_value(msg);
}

} // namespace sql
