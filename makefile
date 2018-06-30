CXX = g++
CXX_FLAGS = -Wall -Werror -std=c++1z -I./ -I../ -I/usr/local/include
CXX_LINKER_FLAGS = -L/usr/local/lib -lbenchmark -lbenchmark_main -lgtest
BUILD_FOLDER = build

TREE_TESTS_UNOPTIMIZED = tree_tests_unoptimized.x
TREE_TESTS_OPTIMIZED = tree_tests_optimized.x
PERFORMANCE_TESTS_OPTIMIZED = tree_performance_tests_optimized.x
PERFORMANCE_TESTS_UNOPTIMIZED = tree_performance_tests_unoptimized.x
VALGRIND_FLAGS = -v --leak-check=full --show-leak-kinds=all --error-exitcode=0 --show-leak-kinds=definite --errors-for-leak-kinds=definite

all:
	make tests
	make mem_check
	make performance_tests

tests: link
	./$(TREE_TESTS_UNOPTIMIZED)
	./$(TREE_TESTS_OPTIMIZED)

mem_check: link
	valgrind $(VALGRIND_FLAGS) ./$(TREE_TESTS_UNOPTIMIZED)
	valgrind $(VALGRIND_FLAGS) ./$(TREE_TESTS_OPTIMIZED)

performance_tests: link
		./$(PERFORMANCE_TESTS_UNOPTIMIZED)
		./$(PERFORMANCE_TESTS_OPTIMIZED)

link:
	make compile_unoptimized
	$(CXX) $(CXX_FLAGS) -o $(TREE_TESTS_UNOPTIMIZED) ./$(BUILD_FOLDER)/test.o $(CXX_LINKER_FLAGS)
	$(CXX) $(CXX_FLAGS) -o $(PERFORMANCE_TESTS_UNOPTIMIZED) ./$(BUILD_FOLDER)/performance.o $(CXX_LINKER_FLAGS)
	make compile_optimized
	$(CXX) $(CXX_FLAGS) -o $(TREE_TESTS_OPTIMIZED) ./$(BUILD_FOLDER)/test.o $(CXX_LINKER_FLAGS)
	$(CXX) $(CXX_FLAGS) -o $(PERFORMANCE_TESTS_OPTIMIZED) ./$(BUILD_FOLDER)/performance.o $(CXX_LINKER_FLAGS)

	rm -rf ./$(BUILD_FOLDER)

compile_unoptimized:
	mkdir -p $(BUILD_FOLDER)
	$(CXX) $(CXX_FLAGS) -c -O0 ./tests/*.cpp
	mv ./*.o ./$(BUILD_FOLDER)

compile_optimized:
	mkdir -p $(BUILD_FOLDER)
	$(CXX) $(CXX_FLAGS) -c -O3 ./tests/*.cpp
	mv ./*.o ./$(BUILD_FOLDER)

clean:
	rm -rf ./$(BUILD_FOLDER)
	rm -f *.x
	rm -rf *.dSYM
