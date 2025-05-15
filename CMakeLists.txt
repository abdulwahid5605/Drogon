cmake_minimum_required(VERSION 3.10)
project(my_drogon_app)

set(CMAKE_CXX_STANDARD 17)


# Find Drogon and other necessary packages
find_package(Drogon REQUIRED)

# Add your executable
add_executable(my_drogon_app main.cpp TestCtrl.cc)




# Link libraries
target_link_libraries(my_drogon_app PRIVATE Drogon::Drogon)

# Add this line inside your target_link_libraries in CMakeLists.txt

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Drogon::Drogon
    sqlite3            # <-- Add this line
)