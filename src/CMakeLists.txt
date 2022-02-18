add_executable(lancer)
target_link_libraries(lancer PRIVATE sqlite_orm::sqlite_orm)

target_sources(lancer 
    PRIVATE 
        main.cpp 
)