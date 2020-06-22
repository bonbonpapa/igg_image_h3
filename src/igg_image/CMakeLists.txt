add_subdirectory(io_strategies)

# TODO: create image library from image.cpp.
add_library(image image.cpp)

### add executable ####
add_executable(image_main main.cpp)


# TODO: link image library to any other libraries if needed.
target_link_libraries(image_main image strategies)