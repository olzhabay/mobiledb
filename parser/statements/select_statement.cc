#include <sstream>
#include "select_statement.hh"

using namespace std;

namespace sql {

bool SelectStmt::is_equal(Statement* stmt) {
	return stmt->get_type() == SELECT ? is_equal(dynamic_cast<SelectStmt*>(stmt)) : false;
}

bool SelectStmt::is_equal(SelectStmt* stmt) {
	if (select_type != stmt->select_type) return false;
	if (column_list != stmt->column_list) return false;
	if (table_list != stmt->table_list) return false;
	if (where != stmt->where) return false;
	if (groupby != stmt->groupby) return false;
	if (orderby != stmt->orderby) return false;
	if (limit != stmt->limit) return false;
	return true;
}

void SelectStmt::generate_string() {
	stringstream ss;
	ss << "SELECT";
	switch (select_type) {
		case ALL:
			ss << " ALL";
			break;
		case DISTINCT:
			ss << " DISTINCT ";
			break;
		case DISTINCTROW:
			ss << " DISTINCTROW ";
			break;
		case NO_OPTION:
			ss << " ";
			break;
	}
	if (!column_list.empty())
		ss << to_str(column_list);
	ss << " FROM (";
	for (auto it = table_list.begin(); it != table_list.end(); ++it) {
		ss << (*it)->to_string();
		if (it + 1 == table_list.end())
			ss << ")";
		else
			ss << ", ";
	}
	if (!where.empty())
		ss << " WHERE " << to_str(where);
	if (!groupby.empty())
		ss << " GROUP BY " << to_str(groupby);
	if (!orderby.empty())
		ss << " ORDER BY " << to_str(orderby);
	if (limit > 0)
		ss << " LIMIT " << limit;
	stmt_str = ss.str();
}

SelectStmt::SelectStmt(Type select_type_, vector<string> column_list_, vector<shared_ptr<Table>> table_list_,
											 vector<tuple<string, string, string>> where_, vector<string> groupby_, vector<string> orderby_,
											 int limit_) :
	Statement(SELECT), select_type(select_type_), column_list(column_list_), table_list(table_list_),
	where(where_), groupby(groupby_), orderby(orderby_), limit(limit_) {
	generate_string();
}

// Join statement
SelectStmt::SelectStmt(Type type_, shared_ptr<Table> ltable_, shared_ptr<Table> rtable_,
											 vector<tuple<string, string, string>> condition_) :
	Statement(SELECT), select_type(type_), where(condition_) {
	table_list.push_back(ltable_);
	table_list.push_back(rtable_);
	generate_string();
}

future<shared_ptr<sql_message>> SelectStmt::get_result() {
	return result.get_future();
}

void SelectStmt::set_result(shared_ptr<sql_message> msg) {
	result.set_value(msg);
}

vector<shared_ptr<Table>> SelectStmt::get_tables() {
	return table_list;
}

vector<tuple<string, string, string>> SelectStmt::get_where() {
	return where;
}

vector<string> SelectStmt::get_column_list() {
	return column_list;
}

SelectStmt::Type SelectStmt::get_select_type() {
	return select_type;
}

} // namespace sql