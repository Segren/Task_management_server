#include "task_controller.h"
#include <sstream>

TaskController::TaskController(Database& db) : db_(db) {}

void TaskController::registerEndpoints(httplib::Server& server){
    server.Post("/tasks", [this](const httplib::Request& req, httplib::Response& res) {
        this->handleCreateTask(req, res);
    });
    server.Get("/tasks", [this](const httplib::Request& req, httplib::Response& res) {
        this->handleGetTasks(req, res);
    });
    server.Put("/tasks", [this](const httplib::Request& req, httplib::Response& res) {
        this->handleUpdateTask(req,res);
    });
    server.Delete("/tasks", [this](const httplib::Request& req, httplib::Response& res) {
        this->handleDeleteTask(req, res);
    });
}

void TaskController::handleCreateTask(const httplib::Request& req, httplib::Response& res){
    try{
        pqxx::work txn(*db_.getConnection());
        Json::Value root;
        Json::CharReaderBuilder reader;
        std::string errors;

        std::istringstream stream(req.body);

        if(Json::parseFromStream(reader, stream, &root, &errors)) {
            int user_id = root["user_id"].asInt();
            std::string title = root["title"].asString();
            std::string description = root["description"].asString();

            //проверка на существование пользователя
            pqxx::result user_check = txn.exec("SELECT id FROM users WHERE id = " + txn.quote(user_id));
            if(user_check.empty()){
                res.status = 400;
                res.set_content("User ID not found", "text/plain");
                return;
            }

            txn.exec0("INSERT INTO tasks (user_id, title, description) VALUES (" + txn.quote(user_id) + ", " + txn.quote(title) + ", " + txn.quote(description) + ")");
            txn.commit();
            res.set_content("Task created successfully", "application/json");
        } else {
            res.status = 400;
            res.set_content("Invalid JSON", "text/pslain");
        }
    } catch (const std::exception &e) {
        res.status = 500;
        res.set_content("Server error", "text/plain");
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

void TaskController::handleGetTasks(const httplib::Request& req, httplib::Response& res) {
    try{
        pqxx::work txn(*db_.getConnection());
        pqxx::result r = txn.exec("SELECT * FROM tasks");

        Json::Value tasks(Json::arrayValue);
        for (auto row : r) {
            Json::Value task;
            task["id"] = row["id"].as<int>();
            task["user_id"] = row["user_id"].as<int>();
            task["title"] = row["title"].as<std::string>();
            task["description"] = row["description"].as<std::string>();
            task["completed"] = row["completed"].as<bool>();
            tasks.append(task);
        }

        Json::StreamWriterBuilder writer;
        std::string output = Json::writeString(writer, tasks);
        res.set_content(output, "application/json");
    } catch (const std::exception &e) {
        res.status = 500;
        res.set_content("Server error", "text/plain");
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

void TaskController::handleUpdateTask(const httplib::Request& req, httplib::Response& res) {
    try {
        pqxx::work txn(*db_.getConnection());
        Json::Value root;
        Json::CharReaderBuilder reader;
        std::string errors;

        std::istringstream stream(req.body);

        if(Json::parseFromStream(reader, stream, &root, &errors)) {
            int id = root["id"].asInt();
            std::string title = root["title"].asString();
            std::string description = root["description"].asString();
            bool completed = root["completed"].asBool();

            txn.exec0("UPDATE tasks SET title = " + txn.quote(title) + ", description = " + txn.quote(description) + ", completed = " + txn.quote(completed) + " WHERE id = " + txn.quote(id));
            txn.commit();
            res.set_content("Task updated successfully", "text/plain");
        } else {
            res.status = 400;
            res.set_content("Invalid JSON", "text/plain");
        }
    } catch (const std::exception &e){
        res.status = 500;
        res.set_content("Server error", "text/plain");
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

void TaskController::handleDeleteTask(const httplib::Request& req, httplib::Response& res) {
    try {
        pqxx::work txn(*db_.getConnection());
        Json::Value root;
        Json:: CharReaderBuilder reader;
        std::string errors;

        std::istringstream stream(req.body);

        if(Json::parseFromStream(reader, stream, &root, &errors)) {
            int id = root["id"].asInt();

            txn.exec0("DELETE FROM tasks WHERE id = " + txn.quote(id));
            txn.commit();
            res.set_content("Task deleted successfully", "text/plain");
        } else {
            res.status = 400;
            res.set_content("Invalid JSON", "text/plain");            
        }
    } catch (const std::exception &e){
        res.status = 500;
        res.set_content("Server error", "text/plain");
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}