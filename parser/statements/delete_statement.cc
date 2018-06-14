#include <sstream>
#include "delete_statement.hh"

using namespace std;

namespace sql {

DeleteStmt::DeleteStmt(vector<string> column_list_, string name_, vector<tuple<string, string, string>> where_,
											 vector<string> orderby_, int limit_) :
	Statement(DELETE), column_list(column_list_), name(name_), where(where_), orderby(orderby_), limit(limit_) {
	generate_string();
}

bool DeleteStmt::is_equal(Statement* stmt) {
	return stmt->get_type() == DELETE ? is_equal(dynamic_cast<DeleteStmt*>(stmt)) : false;
}

bool DeleteStmt::is_equal(DeleteStmt* stmt) {
	if (column_list != stmt->column_list) return false;
	if (name != stmt->name) return false;
	if (where != stmt->where) return false;
	if (orderby != stmt->orderby) return false;
	if (limit != stmt->limit) return false;
	return true;
}

void DeleteStmt::generate_string() {
	stringstream ss;
	ss << "DELETE ";
	if (column_list.size() == 0)
		ss << "ALL";
	else
		ss << to_str(column_list, true);
	ss << " FROM " << name;
	if (where.size() > 0)
		ss << " WHERE " << to_str(where, true);
	if (orderby.size() > 0)
		ss << " ORDERBY " << to_str(orderby, true);
	if (limit > 0)
		ss << " LIMIT " << limit;
	stmt_str = ss.str();
}

future<shared_ptr<sql_message>> DeleteStmt::get_result() {
	return result.get_future();
}

void DeleteStmt::set_result(shared_ptr<sql_message> msg) {
	result.set_value(msg);
}

string& DeleteStmt::get_name() {
	return name;
}

vector<tuple<string, string, string>> DeleteStmt::get_opt_where() {
	return where;
}

int DeleteStmt::get_limit() {
	return limit;
}

} // namespace sql
