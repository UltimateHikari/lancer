add_executable(lancer)
add_library(lancer_lib)

set(sources 
    screen/main.cpp
    screen/inventory.cpp
    model/model.cpp
    main.cpp 
    database.cpp
)

set(libraries
    sqlite_orm::sqlite_orm
    ftxui::screen
    ftxui::dom
    ftxui::component
)

target_link_libraries(lancer PRIVATE ${libraries})
target_sources(lancer PRIVATE ${sources})

target_link_libraries(lancer_lib PRIVATE ${libraries})
target_sources(lancer_lib PRIVATE ${sources})