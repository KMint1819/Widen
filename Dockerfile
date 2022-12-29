FROM ubuntu:20.04

RUN apt -y update && \
    apt -y upgrade;

RUN export DEBIAN_FRONTEND=noninteractive && \
    apt -y install \
    build-essential \
    git \
    cmake \
    wget

# Install protobuf
WORKDIR /opt
RUN wget -O protobuf-cpp.tar.gz https://github.com/protocolbuffers/protobuf/releases/download/v21.12/protobuf-cpp-3.21.12.tar.gz && \
    mkdir protobuf && \
    tar -xvzf protobuf-cpp.tar.gz -C protobuf --strip 1
WORKDIR /opt/protobuf/build
RUN cmake .. \
    -Dprotobuf_WITH_ZLIB=0 \
    -Dprotobuf_BUILD_TESTS=0
RUN make -j8 && \
    make install

WORKDIR /workspace