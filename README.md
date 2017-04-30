# Operational Research Web API

## Requirements 
 - [protocol buffer](https://github.com/google/protobuf)
 - [grpc framework](https://github.com/grpc/grpc)
 - [MongoDB](https://www.mongodb.com/download-center#community)
 - [MongoDB driver for C++](https://mongodb.github.io/mongo-cxx-driver/mongocxx-v3/installation/)
 
## Build the server from Source

``` git clone git@github.com:geoffreyp/OperationalResearchWebAPI.git```

``` mkdir OperationalResearchWebAPI/build ```

``` cd OperationalResearchWebAPI/build ```

``` cmake ..```

``` make```


## Run the server 
``` ./build/server ```


## Build the client

``` python -m grpc_tools.protoc -I=./protos --python_out=./protoClassClient --grpc_python_out=./protoClassClient ./protos/hcfi.proto ```


## Run the  client 
``` python client.py ```