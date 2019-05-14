FROM gcc:9.1.0

RUN apt update && apt install -y cmake

COPY ./tests/install_gtest.sh /var/tmp/gtest/install_gtest.sh
RUN /var/tmp/gtest/install_gtest.sh

COPY ./CMakeLists.txt /var/tmp/bst/CMakeLists.txt
COPY ./binary_search_tree.h /var/tmp/bst/binary_search_tree.h
COPY ./tests /var/tmp/bst/tests
RUN cd /var/tmp/bst && cmake . && make

ENTRYPOINT /var/tmp/bst/tree_tests
