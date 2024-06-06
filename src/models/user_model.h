#ifndef USER_MODEL_H
#define USER_MODEL_H

#include <string>

class UserModel {
    public:
        int id;
        std::string username;
        std::string password;

        UserModel(int id, const std::string &username, const std::string &password) : id(id), username(username),password(password) {}
};

#endif // USER_MODEL_H