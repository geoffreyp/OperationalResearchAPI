FROM ubuntu:xenial

MAINTAINER Florian Vansteene <florian.vansteene@gmail.com> 

# Apt packages
ADD apt_requirements.txt apt_requirements.txt
RUN apt-get update && \
    apt-get install -y $(grep -vE "^\s*#" apt_requirements.txt  | tr "\n" " ") && \
# CMake
    wget https://cmake.org/files/v3.7/cmake-3.7.2-Linux-x86_64.sh && \
    chmod +x ./cmake-3.7.2-Linux-x86_64.sh && \
    ./cmake-3.7.2-Linux-x86_64.sh --skip-license && \
# Protobuf
    git clone https://github.com/google/protobuf.git && \
    cd protobuf && \
    ./autogen.sh && \
    ./configure && \
    make && \
    make check && \
    make install && \
    ldconfig && \
    cd .. && \
# GRPC CPP
    git clone -b $(curl -L http://grpc.io/release) https://github.com/grpc/grpc && \
    cd grpc && \
    git submodule update --init && \
    make && \
    make install && \
    cd .. && \
# Mongo C Driver
    wget https://github.com/mongodb/mongo-c-driver/releases/download/1.6.2/mongo-c-driver-1.6.2.tar.gz && \
    tar xzf mongo-c-driver-1.6.2.tar.gz && \
    cd mongo-c-driver-1.6.2 && \
    ./configure --disable-automatic-init-and-cleanup && \
    make && \
    make install && \
    cd .. && \
# Mongo C++ Driver
    git clone https://github.com/mongodb/mongo-cxx-driver.git --branch releases/stable --depth 1 && \
    cd mongo-cxx-driver/build && \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr/local .. && \
    make EP_mnmlstc_core && \
    make && \
    make install && \
    cd ../.. && \
# Projet Server
    git clone https://github.com/geoffreyp/OperationalResearchWebAPI.git && \
    cd OperationalResearchWebAPI/build && \
    cmake .. && \
    make

WORKDIR /OperationalResearchWebAPI/build

#ENTRYPOINT ["bash"]
#RUN echo "export PATH=/usr/bin/"

CMD ["./server"]
