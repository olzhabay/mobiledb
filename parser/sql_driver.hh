/*!
 * @class Driver
 * @brief driver to handle scanning and parsing of queries
 */
#pragma once
#include <string>
#include <map>
#include <sstream>
#include <memory>
#include "statements/sql_statement.hh"
#include "location.hh"

using namespace std;

namespace sql {

    class Parser;
    class Scanner;
    class location;

    class Driver {
    private:
        Parser *parser; //!< Bison parser
        Scanner *scanner; //!< Flex scanner
        location *loc; //!< Location tracker
        vector<shared_ptr<sql::Statement>> result; //!< result of query/queries
        string error_msg; //!< error message if occurs

        friend class Parser;
        friend class Scanner;

    public:
        Driver();

        ~Driver();

        int parse(const string &s);
        void set_result(vector<shared_ptr<Statement>> r);
        vector<shared_ptr<Statement>> get_result();
        Scanner *get_scanner();
        void error(const location& l, const string& m);
        string error();
        void reset();
    };

}