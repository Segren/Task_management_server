#include "database.h"

Database::Database(const std::string &connection_string) {
    conn = new pqxx::connection(connection_string);
    if(conn->is_open()){
        std::cout << "Connected to database successfully: " << conn->dbname() << std::endl;
    } else {
        std::cerr << "Failed to connect to database" << std::endl;
    }
}

Database::~Database(){
    delete conn;
}

pqxx::connection* Database::getConnection(){
    return conn;
}
