#pragma once
#include <string>
#include <memory>
#include <boost/any.hpp>
#include "sql_statement.hh"

namespace sql {

class SelectStmt;

class Table {
public:

	enum Type {
		DEFAULT = 1, SELECT = 2
	};

			Table() = default;
	Table(Type, std::string, string);
			Table(Type, std::shared_ptr<SelectStmt>, string);

	virtual ~Table() { }
			Type get_type();
	string get_alias();
	bool is_equal(Table* t);
	string to_string();
			string get_str();
	shared_ptr<SelectStmt> get_stmt();
private:
	Type type; //!< type of table (select statement or string)
			std::string table_str; //!< table name if type is DEFAULT
			std::shared_ptr<SelectStmt> table_ptr; //!< table pointer if type is SELECT
	string alias; //!< alias name (AS NAME)
};

} // namespace sql
