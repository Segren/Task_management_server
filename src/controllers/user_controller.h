#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H

#include <httplib.h>
#include <pqxx/pqxx>
#include <json/json.h>
#include "../database/database.h"

class UserController {
    public:
        UserController(Database& db);
        void registerEndpoints(httplib::Server& server);
    
    private:
        Database& db_;

        void handleRegister(const httplib::Request& req, httplib::Response& res);
        void handleLogin(const httplib::Request& req, httplib::Response& res);
};

#endif // USER_CONTROLLER_H