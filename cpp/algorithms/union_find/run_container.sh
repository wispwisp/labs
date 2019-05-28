#!/bin/bash

# docker run -it --rm --name=union_find cpp_algorithms/union_find
docker run -it --rm \
       --name=union_find \
       -v $(pwd -P)/src:/home/me \
       --privileged \
       cpp_algorithms/union_find
