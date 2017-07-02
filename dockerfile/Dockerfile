FROM ubuntu:xenial 

MAINTAINER Florian Vansteene <florian.vansteene@gmail.com> 

ENV DEBIAN_FRONTEND=noninteractive
ENV PATH=$PATH:/bin/:/usr/bin/

# Apt packages
ADD apt_requirements.txt apt_requirements.txt
RUN apt-get update && \
    apt-get install -y $(grep -vE "^\s*#" apt_requirements.txt  | tr "\n" " ") &&\
# CMake
    wget https://cmake.org/files/v3.7/cmake-3.7.2-Linux-x86_64.sh && \
    chmod +x ./cmake-3.7.2-Linux-x86_64.sh &&\
    ./cmake-3.7.2-Linux-x86_64.sh --skip-license && \
# Cleanup
    rm ./cmake-3.7.2-Linux-x86_64.sh && \
    apt-get -y autoremove && apt-get -y autoclean && apt-get -y purge wget &&\
# Protobuf
    git clone https://github.com/google/protobuf.git &&\
    cd protobuf &&\
    ./autogen.sh &&\
    ./Configure &&\
    make &&\
    make check &&\
    sudo make install &&\
    sudo ldconfig &&\
# GRPC CPP
    git clone -b $(curl -L http://grpc.io/release) https://github.com/grpc/grpc &&\
    cd gprc &&\
    git submodule update --init &&\
    make &&\
    sudo make install
# Mongo Driver
    git clone https://github.com/mongodb/mongo-cxx-driver.git --branch releases/stable --depth 1 &&\
    cd mongo-cxx-driver/build &&\
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local .. &&\
    sudo make EP_mnmlstc_core &&\
    make && sudo make install &&\
# Projet Server
    git clone https://github.com/geoffreyp/OperationalResearchWebAPI.git &&\
    mkdir OperationalResearchWebAPI/build &&\
    cd OperationalResearchWebAPI/build &&\
    cmake .. &&\
    make
