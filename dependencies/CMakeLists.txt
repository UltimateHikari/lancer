include(FetchContent)

# You can configure this for your need, presumbably you want speificy a git tag here instead of a branch
FetchContent_Declare(sqliteOrm
  GIT_REPOSITORY https://github.com/fnc12/sqlite_orm
  GIT_TAG        v1.7.1
)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v0.11
)

add_subdirectory(googletest)
add_subdirectory(sqlite_orm)
add_subdirectory(ftxui)
add_subdirectory(easyloggingpp)