cmake_minimum_required(VERSION 3.5)

project(keisan)

if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)

add_library(${PROJECT_NAME}
  "src/angle/angle.cpp"
  "src/angle/equation.cpp"
  "src/angle/euler_angles.cpp"
  "src/angle/quaternion.cpp"
  "src/angle/trigonometry.cpp"
  "src/geometry/point_2.cpp"
  "src/geometry/point_3.cpp"
  "src/geometry/transform2.cpp"
  "src/number.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>)

install(DIRECTORY "include" DESTINATION ".")

install(TARGETS ${PROJECT_NAME}
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION "lib"
  LIBRARY DESTINATION "lib"
  RUNTIME DESTINATION "bin")

if(BUILD_TESTING)
  find_package(ament_cmake_gtest REQUIRED)
  find_package(ament_lint_auto REQUIRED)

  ament_add_gtest(${PROJECT_NAME}_tests
    "test/angle/angle_test.cpp"
    "test/angle/quaternion_test.cpp"
    "test/angle/trigonometry_test.cpp"
    "test/geometry/point_2_test.cpp"
    "test/geometry/point_3_test.cpp"
    "test/geometry/transform2_test.cpp"
    "test/matrix/matrix_test.cpp"
    "test/matrix/square_matrix_test.cpp"
    "test/matrix/vector_test.cpp"
    "test/number_test.cpp")

  target_include_directories(${PROJECT_NAME}_tests PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>)

  target_link_libraries(${PROJECT_NAME}_tests ${PROJECT_NAME})

  ament_lint_auto_find_test_dependencies()
endif()

ament_export_include_directories("include")
ament_export_libraries(${PROJECT_NAME})

ament_package()
