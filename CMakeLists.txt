cmake_minimum_required(VERSION 3.10)

project(TaskManagementServer)

# установка стандарта С++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

# Установка флагов компиляции
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# Включение всех исходных файлов
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h" "src/*.h")

# Добавление исполняемого файла
add_executable(task_management_server ${SOURCES} ${HEADERS})

# Указание путей к библиотекам
include_directories("/opt/homebrew/Cellar/libpqxx/7.9.0/include")
include_directories("/opt/homebrew/Cellar/postgresql@14/14.12/include")
link_directories("/opt/homebrew/Cellar/libpqxx/7.9.0/lib")
link_directories("/opt/homebrew/lib/postgresql@14")
target_link_libraries(task_management_server /opt/homebrew/Cellar/libpqxx/7.9.0/lib/libpqxx.dylib /opt/homebrew/lib/postgresql@14/libpq.dylib)

include_directories(/opt/homebrew/Cellar/jsoncpp/1.9.5/include)
link_directories(/opt/homebrew/Cellar/jsoncpp/1.9.5/lib)
target_link_libraries(task_management_server /opt/homebrew/Cellar/jsoncpp/1.9.5/lib/libjsoncpp.dylib)

include_directories(/opt/homebrew/Cellar/cryptopp/8.9.0/include)
link_directories(/opt/homebrew/Cellar/cryptopp/8.9.0/lib)
target_link_libraries(task_management_server /opt/homebrew/Cellar/cryptopp/8.9.0/lib/libcryptopp.dylib)

# Указание на директорию include
include_directories(${CMAKE_SOURCE_DIR}/include)
