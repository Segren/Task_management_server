#include "user_controller.h"
#include <iostream>
#include <json/json.h>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/filters.h> // для хеширования паролей

UserController::UserController(Database& db) : db_(db) {}

void UserController::registerEndpoints(httplib::Server& server){
    server.Post("/register", [this](const httplib::Request& req, httplib::Response& res){
        this->handleRegister(req,res);
    });

    server.Post("/login", [this](const httplib::Request& req, httplib::Response& res){
        this->handleLogin(req,res);
    });
}

std::string hashPassword(const std::string& password) {
    CryptoPP::SHA256 hash;
    std::string digest;

    CryptoPP::StringSource s(password, true,
        new CryptoPP::HashFilter(hash,
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(digest)
            )
        )
    );

    return digest;
}

void UserController::handleRegister(const httplib::Request& req, httplib::Response& res){
    try{
        pqxx::work txn(*db_.getConnection());
        Json::Value root;
        Json::CharReaderBuilder reader;
        std::string errors;

        std::istringstream stream(req.body); //оборачиваем req.body в поток

        if(Json::parseFromStream(reader, stream, &root, &errors)){
            std::string username = root["username"].asString();
            std::string password = root["password"].asString();

            //Хэширование пароля
            std::string hashedPassword = hashPassword(password);

            txn.exec0("INSERT INTO users (username, password) VALUES (" + txn.quote(username) + ", " + txn.quote(hashedPassword) + ")");
            txn.commit();
            res.set_content("User registered successfully", "text/plain");
        } else {
            res.status = 400;
            res.set_content("Invalid JSON", "text/plain");
        }
    } catch (const std::exception &e) {
        res.status = 500;
        res.set_content("Server error", "text/plain");
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

void UserController::handleLogin(const httplib::Request& req, httplib::Response& res) {
    try{
        pqxx::work txn(*db_.getConnection());
        Json::Value root;
        Json::CharReaderBuilder reader;
        std::string errors;

        std::istringstream stream(req.body); //оборачиваем req.body в поток

        if(Json::parseFromStream(reader, stream, &root, &errors)) {
            std::string username = root["username"].asString();
            std::string password = root["password"].asString();
            
            pqxx::result r = txn.exec("SELECT * FROM users WHERE username = " + txn.quote(username) + " AND password = " + txn.quote(password));
            
            if(r.size() == 1) {
                std::string storedHash = r[0]["password"].as<std::string>();

                //Проверка пароля
                if(hashPassword(password) == storedHash) {
                    res.set_content("User logged in successfully", "text/plain");
                }
            } else {
                res.status = 401;
                res.set_content("Invalid username or password", "text/plain");
            }        
        } else {
            res.status = 400;
            res.set_content("Invalid JSON", "text/plain");
        }
    } catch (const std::exception &e) {
        res.status = 500;
        res.set_content("Server error", "text/plain");
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}