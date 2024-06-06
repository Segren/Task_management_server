#ifndef DATABASE_H
#define DATABASE_H

#include <pqxx/pqxx>
#include <iostream>
#include <string>

class Database {
public:
    Database(const std::string &connection_string);
    ~Database();

    pqxx::connection* getConnection();
private:
    pqxx::connection* conn;
};

#endif // DATABASE_H