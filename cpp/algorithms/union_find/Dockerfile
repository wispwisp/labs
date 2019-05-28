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

# ...
RUN useradd -ms /bin/bash me
WORKDIR /home/me

# ADD *.cpp ./
# ADD *.hpp ./
# ADD Makefile .

# RUN make
# CMD './tests.cpp'
