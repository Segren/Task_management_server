#ifndef TASK_CONTROLLER_H
#define TASK_CONTROLLER_H

#include <httplib.h>
#include <pqxx/pqxx>
#include <json/json.h>
#include "../database/database.h"

class TaskController {
public:
    TaskController(Database& db_);

    void registerEndpoints(httplib::Server& server);
private:
    Database& db_;

    void handleCreateTask(const httplib::Request& req, httplib::Response& res);
    void handleGetTasks(const httplib::Request& req, httplib::Response& res);
    void handleUpdateTask(const httplib::Request& req, httplib::Response& res);
    void handleDeleteTask(const httplib::Request& req, httplib::Response& res);
};

#endif //TASK_CONTROLLER_H