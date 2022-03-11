add_executable(lancer)
add_library(lancer_lib)

set(sources 
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
target_link_libraries(lancer_lib PRIVATE ${libraries})

target_sources(lancer 
    PRIVATE 
        ${sources}
)
target_sources(lancer_lib
    PRIVATE 
        ${sources}
)


# add_executable(ftxui-starter src/main.cpp)
# target_include_directories(ftxui-starter PRIVATE src)

# target_link_libraries(ftxui-starter
#   PRIVATE ftxui::screen
#   PRIVATE ftxui::dom
#   PRIVATE ftxui::component # Not needed for this example.
# )
