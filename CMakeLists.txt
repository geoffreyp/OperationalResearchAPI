# Init the project
cmake_minimum_required(VERSION 3.7)
project(OperationalResearchApi)

add_compile_options(-std=c++11)

# Add GRPC and Protocol Buffers libraries location
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

# Add the destination of the protobuf generated files
set(PROTO_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/protoClassServer)
file(MAKE_DIRECTORY ${PROTO_SRC_DIR})
include_directories(${PROTO_SRC_DIR})

# Add protobuf files
set(PROTO_FILE_HCFI ${CMAKE_CURRENT_SOURCE_DIR}/protos/hcfi.proto)
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_SRC_DIR} ${PROTO_FILE_HCFI})
grpc_generate_cpp(GRPC_SRCS GRPC_HDRS ${PROTO_SRC_DIR} ${PROTO_FILE_HCFI})

# Add libs & helpers
file(GLOB LIBS_H_SRC libs/*.h)
file(GLOB LIBS_CPP_SRC libs/*.cpp)

# Add services
file(GLOB GRPC_SERVICES_H_SRC grpcServices/*.h)
file(GLOB GRPC_SERVICES_CPP_SRC grpcServices/*.cpp)

# Add grpcCallData
file(GLOB GRPC_CALL_DATA_H grpcCallData/*/*.h)
file(GLOB GRPC_CALL_DATA_CPP grpcCallData/*/*.cpp)

# Building server
add_executable(server
        ${CMAKE_CURRENT_SOURCE_DIR}/server.cpp
        ${PROTO_SRCS}
        ${GRPC_SRCS}
        ${LIBS_H_SRC}
        ${LIBS_CPP_SRC}
        ${GRPC_SERVICES_H_SRC}
        ${GRPC_SERVICES_CPP_SRC})
target_link_libraries(server
        gRPC::grpc++_reflection
        protobuf::libprotobuf
        )

target_link_libraries(server ${LIBMONGOCXX_LIBRARIES})
target_link_libraries(server ${LIBBSONCXX_LIBRARIES})

# Building server_async
add_executable(server_async
        ${CMAKE_CURRENT_SOURCE_DIR}/server_async.cpp
        ${PROTO_SRCS}
        ${GRPC_SRCS}
        ${LIBS_H_SRC}
        ${LIBS_CPP_SRC}
        ${GRPC_SERVICES_H_SRC}
        ${GRPC_SERVICES_CPP_SRC}
        ${CMAKE_CURRENT_SOURCE_DIR}/grpcCallData/CallData.h
        ${CMAKE_CURRENT_SOURCE_DIR}/grpcCallData/CallData.cpp
        ${GRPC_CALL_DATA_H}
        ${GRPC_CALL_DATA_CPP})
target_link_libraries(server_async
        gRPC::grpc++_reflection
        protobuf::libprotobuf
        )

target_link_libraries(server_async ${LIBMONGOCXX_LIBRARIES})
target_link_libraries(server_async ${LIBBSONCXX_LIBRARIES})

link_libraries(OperationalResearchApi ${LIBBSONCXX_LIBRARIES})
