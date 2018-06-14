/*!
 * @class Statement
 * @brief Parent class for SQL statements
 */
#pragma once

#include <string>
#include <vector>
#include <memory>
#include <future>

using namespace std;
namespace sql {

enum Type {
	SELECT = 1,
	DROP = 2,
	DELETE = 3,
	INSERT = 4,
	UPDATE = 5,
	CREATE = 6,
};

class Statement {
public:
	Statement() { }
	Statement(Type type_) : type(type_) { };
	Type get_type();
	virtual ~Statement() { }
	virtual bool is_equal(Statement*) = 0;
	string to_string();
	string to_str(vector<string>, bool = true);
	string to_str(vector<pair<string, string>>, bool = true);
	string to_str(vector<tuple<string, string, string>>, bool = true);
protected:
	Type type; //!< type of query
			string stmt_str; //!< query in string in full form (with brackets and etc)
};

} // namespace sql


