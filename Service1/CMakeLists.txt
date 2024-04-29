project(Service1 LANGUAGES CXX)
add_library(service1 SHARED service1.cpp service1.h)
target_link_libraries(service1 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)  # Link Qt's Widgets and SQL modules
# find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)  # Add the Sql component here
# find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)  # Add the Sql component here
