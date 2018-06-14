#include "insert_statement.hh"
#include <sstream>

using namespace std;

namespace sql {

InsertStmt::InsertStmt(string name_, vector<string> columns_, vector<string> values_,
											 vector<pair<string, string>> onduplicate_) :
	Statement(INSERT), name(name_), ondupupdate(onduplicate_) {
	for (int i = 0; i < columns_.size(); i++)
		insert_list.push_back(make_pair(columns_[i], values_[i]));
	generate_string();
}

InsertStmt::InsertStmt(string name_, vector<pair<string, string>> insert_list_,
											 vector<pair<string, string>> onduplicate_) :
	Statement(INSERT), name(name_), insert_list(insert_list_), ondupupdate(onduplicate_) {
	generate_string();
}

InsertStmt::InsertStmt(string name_, vector<string> columns_, shared_ptr<SelectStmt> stmt_,
											 vector<pair<string, string>> onduplicate_) :
	Statement(INSERT), name(name_), select_stmt(stmt_), ondupupdate(onduplicate_) {
	for (auto i = columns_.begin(); i != columns_.end(); ++i)
		insert_list.push_back(make_pair(*i, ""));
	generate_string();
}

bool InsertStmt::is_equal(Statement* stmt) {
	return stmt->get_type() == INSERT ? is_equal(dynamic_cast<InsertStmt*>(stmt)) : false;
}

bool InsertStmt::is_equal(InsertStmt* stmt) {
	if (name != stmt->name) return false;
	if (insert_list != stmt->insert_list) return false;
	if (ondupupdate != stmt->ondupupdate) return false;
	if (!select_stmt->is_equal(stmt->select_stmt.get())) return false;
	return true;
}

void InsertStmt::generate_string() {
	stringstream ss;
	ss << "INSERT INTO " << name;
	if (select_stmt == nullptr) {
		ss << to_str(insert_list);
	} else {
		ss << " (" << select_stmt->to_string() << ")";
	}
	if (!ondupupdate.empty()) {
		ss << " ON DUPLICATE KEY UPDATE " << to_str(ondupupdate);
	}
	stmt_str = ss.str();
}

string& InsertStmt::get_name() {
	return name;
}

vector<pair<string, string>> InsertStmt::get_insert_list() {
	return insert_list;
}

vector<pair<string, string>> InsertStmt::get_ondupupdate() {
	return ondupupdate;
}

shared_ptr<SelectStmt> InsertStmt::get_select_stmt() {
	return select_stmt;
}

future<shared_ptr<sql_message>> InsertStmt::get_result() {
	return result.get_future();
}

void InsertStmt::set_result(shared_ptr<sql_message> msg) {
	result.set_value(msg);
}

} // namespace sql
