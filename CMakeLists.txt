cmake_minimum_required(VERSION 3.7)
project(OperationalResearchApi)

add_compile_options(-std=c++11)

# GRPC and Protocol Buffers libraries location
list(APPEND CMAKE_PREFIX_PATH "/usr/local/include/grpc" "/usr/local/include/protobuf")

# Cmake find modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(Protobuf REQUIRED)
find_package(GRPC REQUIRED)
find_package(libmongocxx REQUIRED)
find_package(libbsoncxx REQUIRED)
include_directories(${LIBMONGOCXX_INCLUDE_DIR})
include_directories(${LIBBSONCXX_INCLUDE_DIR})
include_directories("/usr/local/include/mongocxx/v_noabi")
include_directories("/usr/local/include/bsoncxx/v_noabi")
include_directories("/usr/local/include/libmongoc-1.0")
include_directories("/usr/local/include/libbson-1.0")
include_directories("/usr/local/include/grpc")
include_directories("/usr/local/lib")

set(PROTOS
        ${CMAKE_CURRENT_SOURCE_DIR}/protos/hcfi.proto
        )

set(PROTO_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/protoClassServer)
file(MAKE_DIRECTORY ${PROTO_SRC_DIR})
include_directories(${PROTO_SRC_DIR})

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_SRC_DIR} ${PROTOS})
grpc_generate_cpp(GRPC_SRCS GRPC_HDRS ${PROTO_SRC_DIR} ${PROTOS})

# Building server
add_executable(server
        ${CMAKE_CURRENT_SOURCE_DIR}/server.cpp
        ${PROTO_SRCS}
        ${GRPC_SRCS}
        libs/helper.h
        libs/helper.cpp)
target_link_libraries(server
        gRPC::grpc++_reflection
        protobuf::libprotobuf
        )

target_link_libraries(server ${LIBMONGOCXX_LIBRARIES})
target_link_libraries(server ${LIBBSONCXX_LIBRARIES})

link_libraries(OperationalResearchApi ${LIBBSONCXX_LIBRARIES})
