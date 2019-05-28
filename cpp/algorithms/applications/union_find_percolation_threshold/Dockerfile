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

# git clone https://github.com/wispwisp/labs.git
# ADD cpp/algorithms/union_find/src/UnionMatrix.hpp
ADD UnionMatrix.hpp .
ADD ./src/* ./

RUN make
ENTRYPOINT ["./tests"]
