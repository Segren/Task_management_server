#include <iostream>
#include <httplib.h>
#include <pqxx/pqxx>
#include "database/database.h"
#include "controllers/user_controller.h"
#include "controllers/task_controller.h"

int main(){
    Database db("dbname=task_management user=task_user password=password host = localhost port=5432");

    httplib::Server svr;

    UserController userController(db);
    userController.registerEndpoints(svr);

    TaskController taskController(db);
    taskController.registerEndpoints(svr);

    svr.Get("/", [](const httplib::Request&, httplib::Response& res){
        res.set_content("Task Management Server is working", "text/plain");
    });

    std::cout << "Task Management Server is starting at http://localhost:8080" << std::endl;
    svr.listen("localhost", 8080);
    return 0;
}