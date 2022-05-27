add_executable(lancer)
add_library(lancer_lib)

set(sources 
    db/database.cpp
    model/model.cpp
    model/entities.cpp 
    model/oututil.cpp
    model/inventory.cpp
    model/navigation.cpp
    model/trade.cpp
    model/teller.cpp
    model/ship.cpp
    screen/system/inventory.cpp
    screen/system/navigation.cpp
    screen/system/trade.cpp
    screen/system/ship.cpp
    screen/load.cpp
    screen/menu.cpp
    screen/pause.cpp
    screen/system.cpp
    view/view.cpp
    main.cpp
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