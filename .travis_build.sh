echo "Generating googletest library"
clang++ -std=c++1y -pthread -g -Wall -Wextra -isystem tests/googletest/googletest/include -isystem tests/googletest/googletest/ -c -o tests/gtest-all.o tests/googletest/googletest/src/gtest-all.cc
ar -rv tests/libgtest.a tests/gtest-all.o
echo "Compiling sources..."
cd tests
make
echo "Running unit tests..."
./gtest -v
cd ../
result=$?
rm -r tests/gtest tests/kmosaic.o tests/main.o tests/kmosaic_test.o tests/gtest-all.o tests/libgtest.a
echo "Unit tests completed : $result"
exit $result
