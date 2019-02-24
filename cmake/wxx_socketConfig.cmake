find_path(wxx_socket_INCLUDE_DIR NAMES 
    tcp_client.h 
    tcp_server.h
    udp_client.h 
    udp_server.h
    PATHS include
)

find_library(wxx_socket_LIBRARY NAMES)