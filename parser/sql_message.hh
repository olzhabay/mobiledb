#ifndef MOBILEDB_SQL_MESSAGE_HH
#define MOBILEDB_SQL_MESSAGE_HH

#include <string>

#include "statements/sql_statement.hh"

/*!
 * @brief base class that stores results of queries
 */
struct sql_message {
  sql_message(sql::Type t) : type(t) { }
  virtual ~sql_message() = default;
  sql::Type type; //!< query type
  std::string status; //!< status of the message
};

/*!
 * @brief stores result of SQL INSERT query
 */
struct insert_message : sql_message {
  insert_message() : sql_message(sql::INSERT) { }
  std::string message; //!< result of query
};

/*!
 * @brief stores result of SQL DELETE query
 */
struct delete_message : sql_message {
  delete_message() : sql_message(sql::DELETE) { }
  std::string message; //!< result of query
};

/*!
 * @brief stores result of SQL CREATE query
 */
struct create_message : sql_message {
  create_message() : sql_message(sql::CREATE) { }
  std::string message; //!< result of query
};

/*!
 * @brief  stores result of SQL UPDATE query
 */
struct update_message : sql_message {
  update_message() : sql_message(sql::UPDATE) { }
  std::string message; //!< result of query
};

/*!
 * @brief  stores result of SQL DROP query
 */
struct drop_message : sql_message {
  drop_message() : sql_message(sql::DROP) { }
  std::string message; //!< result of query
};

/*!
 * select_message - stores result of SQL SELECT query
 */
struct select_message : sql_message {
  select_message() : sql_message(sql::SELECT) { }
  std::vector<std::string> message; //!< result of query
};

#endif //MOBILEDB_SQL_MESSAGE_HH
