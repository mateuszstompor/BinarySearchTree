FROM gcc:9.1.0 AS ENVIRONMENT

RUN apt update && apt install -y cmake



COPY ./CMakeLists.txt /var/tmp/bst/CMakeLists.txt
COPY ./binary_search_tree.h /var/tmp/bst/binary_search_tree.h
RUN cd /var/tmp/bst && cmake . && make install && rm -rf /var/tmp/bst

FROM ENVIRONMENT AS TEST_RUNNER

COPY ./tests/install_gtest.sh /var/tmp/gtest/install_gtest.sh
RUN /var/tmp/gtest/install_gtest.sh

COPY ./tests /var/tmp/bst/tests

RUN cd /var/tmp/bst/tests && cmake . && make

ENTRYPOINT /var/tmp/bst/tests/tree_tests
