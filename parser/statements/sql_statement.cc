#include <algorithm>
#include <sstream>
#include "sql_statement.hh"

using namespace std;

namespace sql {

string Statement::to_string() {
	return stmt_str;
}

Type Statement::get_type() {
	return type;
}

string Statement::to_str(vector<string> array, bool do_sort) {
	stringstream ss;
	if (do_sort) sort(array.begin(), array.end());
	ss << "(";
	for (auto it = array.begin(); it != array.end(); ++it)
		ss << *it << (it == array.end()) ? ")" : ", ";
	return ss.str();
}

string Statement::to_str(vector<pair<string, string>> array, bool do_sort) {
	stringstream ss;
	if (do_sort) sort(array.begin(), array.end());
	ss << "(";
	for (auto it = array.begin(); it != array.end(); ++it) {
		ss << get<0>(*it) << " = " << get<1>(*it);
		if (it + 1 == array.end())
			ss << ")";
		else
			ss << ", ";
	}
	return ss.str();
}

string Statement::to_str(vector<tuple<string, string, string>> array, bool do_sort) {
	stringstream ss;
	if (do_sort) sort(array.begin(), array.end());
	ss << "(";
	for (auto it = array.begin(); it != array.end(); ++it) {
		ss << get<0>(*it) << " " << get<1>(*it) << " " << get<2>(*it);
		if (it + 1 == array.end())
			ss << ")";
		else
			ss << ", ";
	}
	return ss.str();
}

} // namespace sql