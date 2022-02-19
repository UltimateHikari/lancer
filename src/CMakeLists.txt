add_executable(lancer)
add_library(lancer_lib)

target_link_libraries(lancer PRIVATE sqlite_orm::sqlite_orm)
target_link_libraries(lancer_lib PRIVATE sqlite_orm::sqlite_orm)

set(sources 
    main.cpp 
    database.cpp
)

target_sources(lancer 
    PRIVATE 
        ${sources}
)
target_sources(lancer_lib
    PRIVATE 
        ${sources}
)