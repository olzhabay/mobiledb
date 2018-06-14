#include "sql_driver.hh"
#include "sql_parser.hh"
#include "sql_scanner.hpp"

namespace sql {

Driver::Driver() { }

/*
 * Destructor
 */
Driver::~Driver() {
    delete loc;
    delete parser;
    delete scanner;
}

/*!
 * resets Flex scanner and Bison parser
 */
void Driver::reset() {
    scanner = new Scanner();
    parser = new Parser(*this);
    loc = new location();
}

/*!
 * parses given SQL query string and generates SQL statement
 * each query must be ended by ';' for successful parse
 * @param s - string to parse
 * @return - returns 1 if parse if successful, 0 otherwise
 */
int Driver::parse(const string &s) {
    reset();
    istringstream iss(s);
    scanner->set_debug(false);
    scanner->switch_streams(&iss, &cerr);
    return !parser->parse();
}

/*!
 * for Bison needs
 * sets result
 */
void Driver::set_result(vector<shared_ptr<Statement>> r) {
    result = r;
}

/*!
 * for Bison needs
 * @return scanner
 */
Scanner* Driver::get_scanner() {
    return scanner;
}

/*!
 * sets error message if occurs while parsing
 * @param l - location of error
 * @param m - error message
 */
void Driver::error(const location &l, const string &m) {
    stringstream ss;
    ss << l << ": " << m;
    error_msg = ss.str();
}

/*!
 * shows erros column and line
 * @return error message
 */
string Driver::error() {
    return error_msg;
}

/*!
 * result of parsing
 * @return result
 */
vector<shared_ptr<sql::Statement>> Driver::get_result() {
    return result;
}

}

