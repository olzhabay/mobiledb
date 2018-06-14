#include <sstream>
#include "create_statement.hh"

namespace sql {

CreateStmt::CreateStmt(string name_, bool opt_, vector<tuple<string, string, string>> list_) :
  Statement(CREATE), name(name_), opt_not_exists(opt_), def_list(list_) {
  generate_string();
}

bool CreateStmt::is_equal(Statement* stmt) {
  return stmt->get_type() == CREATE ? is_equal(dynamic_cast<CreateStmt*>(stmt)) : false;
}

bool CreateStmt::is_equal(CreateStmt* stmt) {
  if (name != stmt->name) return false;
  if (opt_not_exists != stmt->opt_not_exists) return false;
  if (def_list != stmt->def_list) return false;
  return true;
}

void CreateStmt::generate_string() {
  stringstream ss;
  ss << "CREATE " << name;
  if (opt_not_exists) ss << " IF NOT EXISTS ";
  ss << to_str(def_list);
  stmt_str = ss.str();
}

shared_future<shared_ptr<sql_message>> CreateStmt::get_result() {
  return result.get_future();
}

void CreateStmt::set_result(shared_ptr<sql_message> msg) {
  result.set_value(msg);
}

string& CreateStmt::get_name() {
  return name;
}

bool CreateStmt::get_opt() {
  return opt_not_exists;
}

vector<tuple<string, string, string>> CreateStmt::get_definitions() {
  return def_list;
}

} // namespace sql