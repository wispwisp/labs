FROM ubuntu:latest

RUN apt update && apt install -y llvm clang cmake google-mock libgtest-dev

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

ADD ./src/start.sh ./
RUN chmod 0744 ./start.sh

RUN cmake CMakeLists.txt && make

ENTRYPOINT ["./start.sh"]
