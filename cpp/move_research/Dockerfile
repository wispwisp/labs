FROM ubuntu:latest

RUN apt update && apt install -y g++ cmake google-mock libgtest-dev gdb

# Compile gmock
WORKDIR /usr/src/gmock
RUN cmake CMakeLists.txt && \
    make && \
    cp *.a /usr/lib

# Compile gtest
WORKDIR /usr/src/gtest
RUN cmake CMakeLists.txt && \
    make && \
    cp *.a /usr/lib

WORKDIR /home
ADD ./src/* ./

RUN cmake CMakeLists.txt && make

ENTRYPOINT ["./tests"]
