#ifndef TASK_MODEL_H
#define TASK_MODEL_H

#include <string>

class TaskModel {
    public:
        int id;
        int user_id;
        std::string title;
        std::string description;
        bool completed;

        TaskModel(int id, int user_id, const std::string &title, const std::string &description, bool completed) 
            : id(id), user_id(user_id), title(title), description(description), completed(completed) {}
};

#endif //TASK_MODEL_H