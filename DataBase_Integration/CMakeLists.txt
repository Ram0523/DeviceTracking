project(DataBase_Integration LANGUAGES CXX)
add_library(data1 SHARED
    data1.h data1.cpp)
target_link_libraries(data1 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)  # Link Qt's Widgets and SQL modules
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)  # Add the Sql component here
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)  # Add the Sql component here


target_include_directories(data1 PUBLIC Service1)
target_link_libraries(data1 PRIVATE service1)
