cmake_minimum_required(VERSION 3.20.4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## PROJECT
project(example VERSION 1.0.0 LANGUAGES CXX)

find_package(VTK REQUIRED COMPONENTS
  IOXML
  CommonCore
  FiltersCore
  FiltersGeometry
)

## TARGET
add_executable(test_extract_surface test_extract_surface.cpp)

set(vtk_modules
  VTK::CommonCore
  VTK::FiltersCore
  VTK::FiltersGeometry
  VTK::IOXML
)

target_link_libraries(test_extract_surface PRIVATE ${vtk_modules})

vtk_module_autoinit(
  TARGETS test_extract_surface
  MODULES ${vtk_modules}
)
