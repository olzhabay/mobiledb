#pragma once
#include <vector>
#include <string>
#include <memory>
#include <future>
#include "sql_statement.hh"
#include "sql_table.hh"
#include "../sql_message.hh"

using namespace std;

namespace sql {

class DeleteStmt: public Statement {
public:
  DeleteStmt() : Statement(DELETE) { }
  DeleteStmt(vector<string>, string, vector<tuple<string, string, string>>, vector<string>, int);
  virtual ~DeleteStmt() { }
  virtual bool is_equal(Statement* stmt);
  bool is_equal(DeleteStmt* stmt);
      future<shared_ptr<sql_message>> get_result();
      void set_result(shared_ptr<sql_message>);
      string &get_name();
      vector<tuple<string, string, string>> get_opt_where();
      int get_limit();

private:
  vector<string> column_list; //!< list of column names
  string name; //!< table name
  vector<tuple<string, string, string>> where; //!< option 'WHERE [expressions]'
  vector<string> orderby; //!< option 'ORDER BY [list of columns]'
  int limit; //!< option 'LIMIT [integer]'
      promise<shared_ptr<sql_message>> result; //!< result of query

      void generate_string();
};

} 
