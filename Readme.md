# Документация к проекту "Task Management Server"
## Описание проекта

"Task Management Server" - это серверное приложение на языке C++, которое позволяет пользователям управлять задачами (todo-list) через REST API. Пользователи могут регистрироваться, входить в систему, создавать, читать, обновлять и удалять задачи. Задачи хранятся в базе данных PostgreSQL.

## Установка и настройка
### Зависимости
Для сборки и запуска проекта необходимы следующие библиотеки и инструменты:

    CMake
    PostgreSQL
    libpqxx (C++ библиотека для работы с PostgreSQL)
    cpp-httplib (библиотека для работы с HTTP)
    jsoncpp (библиотека для работы с JSON)
    bcrypt (библиотека для хэширования паролей)

### Установка зависимостей на MacOS

Установите необходимые зависимости с помощью Homebrew:

    brew install cmake postgresql libpqxx jsoncpp bcrypt

## Настройка базы данных

Запустите PostgreSQL и создайте новую базу данных для проекта:

### Запуск PostgreSQL

    brew services start postgresql

### Вход в PostgreSQL

    psql postgres


### Создание базы данных и пользователя

    CREATE DATABASE task_management; 

    CREATE USER task_user WITH PASSWORD 'password'; 

    GRANT ALL PRIVILEGES ON DATABASE task_management TO task_user;


### Настройка проекта


Клонируйте репозиторий проекта и перейдите в директорию проекта:

    git clone <URL репозитория>

    cd task_management_server



### Создайте и настройте сборочную директорию:

    mkdir build
    cd build
    cmake ..
    make


## Запуск сервера

### Запустите сервер:

    ./task_management_server

Сервер будет доступен по адресу http://localhost:8080.

## API Документация


### Регистрация пользователя

URL: /register

Метод: POST

Тело запроса:

    {
    "username": "your_username",
    "password": "your_password"
    }

Ответы:

    200 OK: Пользователь успешно зарегистрирован.

    400 Bad Request: Неверный формат JSON.

    500 Internal Server Error: Ошибка сервера.


### Авторизация пользователя

URL: /login

Метод: POST

    {
    "username": "your_username",
    "password": "your_password"
    }

Ответы:

    200 OK: Пользователь успешно вошел в систему.

    401 Unauthorized: Неверный логин или пароль.

    400 Bad Request: Неверный формат JSON.

    500 Internal Server Error: Ошибка сервера.


### Создание задачи

URL: /tasks 

Метод: POST

Тело запроса:

    {
    "user_id": 1,
    "title": "Task Title",
    "description": "Task Description"
    }

Ответы:

    200 OK: Задача успешно создана.

    400 Bad Request: Неверный формат JSON.

    500 Internal Server Error: Ошибка сервера.


### Получение задач

URL: /tasks

Метод: GET

Ответы:

    200 OK: Список задач в формате JSON.

    500 Internal Server Error: Ошибка сервера.

Обновление задачи

URL: /tasks
Метод: PUT
Тело запроса:

    {
    "id": 1,
    "title": "Updated Task Title",
    "description": "Updated Task Description",
    "completed": true
    }

Ответы:

    200 OK: Задача успешно обновлена.

    400 Bad Request: Неверный формат JSON.

    500 Internal Server Error: Ошибка сервера.


### Удаление задачи

URL: /tasks

Метод: DELETE

Тело запроса:

    {
    "id": 1
    }

Ответы:

    200 OK: Задача успешно удалена.

    400 Bad Request: Неверный формат JSON.

    500 Internal Server Error: Ошибка сервера.


## Заключение

Этот проект демонстрирует создание простого серверного приложения на C++ с использованием различных библиотек и инструментов для работы с HTTP-запросами, JSON и базой данных PostgreSQL.
