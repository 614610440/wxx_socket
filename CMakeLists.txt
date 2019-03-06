cmake_minimum_required(VERSION 3.5)
project(wxx_socket)

find_package(Boost)

include_directories(
include
)

#ADD_SUBDIRECTORY(lib)

# 查找src目录下的所有源文件
# 并将名称保存到 DIR_LIB_SRCS 变量
aux_source_directory(src DIR_LIB_SRCS)

#message(DIR_LIB_SRCS)
add_library(${PROJECT_NAME}
    ${DIR_LIB_SRCS}
)

target_link_libraries(${PROJECT_NAME}
boost_system
boost_thread
${Boost_LIBRARIES}
)

add_executable(tcp_client_demo demo/tcp_client_demo.cpp)
target_link_libraries(tcp_client_demo
${PROJECT_NAME}
)

add_executable(tcp_server_demo demo/tcp_server_demo.cpp)
target_link_libraries(tcp_server_demo
${PROJECT_NAME}
)

install(TARGETS ${PROJECT_NAME}
    EXPORT wxx_socket_targets 
    PUBLIC_HEADER DESTINATION include 
    ARCHIVE DESTINATION lib 
    LIBRARY DESTINATION lib 
    RUNTIME DESTINATION bin
)

install(EXPORT wxx_socket_targets
    NAMESPACE wxx_socket::
    FILE wxx_socketConfig.cmake
    DESTINATION lib/cmake/wxx_socket
)