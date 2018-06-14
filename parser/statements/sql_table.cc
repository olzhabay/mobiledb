#include <sstream>
#include <future>
#include "sql_table.hh"
#include "select_statement.hh"

using namespace std;

namespace sql {

Table::Table(Type type_, string table_, string alias_) {
  type = type_;
  table_str = table_;
  alias = alias_;
}

Table::Table(Type type_, shared_ptr<SelectStmt> table_, string alias_) {
  type = type_;
  table_ptr = table_;
  alias = alias_;
}


Table::Type Table::get_type() {
  return type;
}

string Table::to_string() {
  stringstream ss;
  if (type == DEFAULT) {
    ss << get_str();
  } else {
    ss << "(" << get_stmt()->to_string() << ")";
    if (alias.length() != 0) ss << " AS " << alias;
  }
  return ss.str();
}

string Table::get_str() {
  if (type == DEFAULT) return table_str;
  else return "";
}

shared_ptr<SelectStmt> Table::get_stmt() {
  if (type == SELECT) return table_ptr;
  else return nullptr;
}

bool Table::is_equal(Table* t) {
  if (type != t->type) return type < t->type;
  // TODO: sql statement compare
  return -1;
}

string Table::get_alias() {
  return alias;
}

} // namespace sql
