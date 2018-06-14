#include "update_statement.hh"
#include <sstream>

using namespace std;

namespace sql {

UpdateStmt::UpdateStmt(string name_, vector<pair<string, string>> update_list_,
											 vector<tuple<string, string, string>> where_,
											 vector<string> orderby_, int limit_) :
	Statement(UPDATE), name(name_), update_list(update_list_), where(where_), orderby(orderby_), limit(limit_) {
	generate_string();
}

bool UpdateStmt::is_equal(Statement* stmt) {
	return stmt->get_type() == UPDATE ? is_equal(dynamic_cast<UpdateStmt*>(stmt)) : false;
}

bool UpdateStmt::is_equal(UpdateStmt* stmt) {
	return true;
}

void UpdateStmt::generate_string() {
	stringstream ss;
	ss << "UPDATE " << name << " SET " << to_str(update_list);
	if (!where.empty())
		ss << " WHERE " << to_str(where);
	if (!orderby.empty())
		ss << " ORDER BY " << to_str(orderby);
	if (limit > 0)
		ss << " LIMIT " << limit;
	stmt_str = ss.str();
}

future<shared_ptr<sql_message>> UpdateStmt::get_result() {
	return result.get_future();
}

void UpdateStmt::set_result(shared_ptr<sql_message> msg) {
	result.set_value(msg);
}

} // namespace sql
