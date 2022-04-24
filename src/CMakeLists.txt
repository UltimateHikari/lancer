add_executable(lancer)
add_library(lancer_lib)

set(sources 
    screen/main.cpp
    screen/inventory.cpp
    screen/navigation.cpp
    model/model.cpp
    model/entities.cpp 
    model/oututil.cpp
    db/database.cpp
)

set(libraries
    sqlite_orm::sqlite_orm
    ftxui::screen
    ftxui::dom
    ftxui::component
    easyloggingpp
)

target_link_libraries(lancer PRIVATE ${libraries})
target_sources(lancer PRIVATE ${sources} main.cpp)

target_link_libraries(lancer_lib PRIVATE ${libraries})
target_sources(lancer_lib PRIVATE ${sources})