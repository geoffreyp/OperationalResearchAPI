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



## Run with Docker
# Download images
``` docker pull fvansteene/roapi ``` 

``` docker pull fvansteene/mongodb``` 

# Run the databse server then the grpc server
``` docker run -d -p 27017:27017 --name mongodb fvansteene/mongodb``` 

``` docker run -d -p 50051:50051 --link mongodb --name ros fvansteene/roapi```

You can now connect your own client to the API :)
