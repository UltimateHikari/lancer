enable_testing()

add_executable(
  lancer_test
  test.cpp
)
target_link_libraries(
  lancer_test
  gtest_main
  lancer_lib
  sqlite_orm::sqlite_orm
)

include(GoogleTest)
gtest_discover_tests(lancer_test)
