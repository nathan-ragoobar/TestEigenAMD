cmake_minimum_required(VERSION 3.16)
project(eigen_dx_test LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find DirectX
find_package(DirectX REQUIRED)

# Find Eigen (adjust path as needed)
set(EIGEN3_INCLUDE_DIR "C:/eigen")
include_directories(${EIGEN3_INCLUDE_DIR})

# Add executable
add_executable(eigen_dx_test test.cpp)

# Add DirectX specific flags
target_compile_definitions(eigen_dx_test PRIVATE 
    -DEIGEN_USE_DIRECTX 
    -DWIN32_LEAN_AND_MEAN 
    -DNOMINMAX
)

# Link against DirectX libraries
target_link_libraries(eigen_dx_test PRIVATE
    d3d11.lib
    dxgi.lib
)

# Set optimization flags
target_compile_options(eigen_dx_test PRIVATE /O2)