CXX = clang++
CXXFLAGS = -std=c++1y -g -Wall
VPATH = ../sources
.SUFFIXES: .cpp .o

program = gtest
objs = kmosaic.o main.o kmosaic_test.o
libs = -lopencv_highgui -lopencv_core -lopencv_imgproc -lgtest

$(program): CXXFLAGS += -L/usr/local/lib -L./
$(program): $(objs)
	$(CXX) $(CXXFLAGS) $(libs) -o $@ $^

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

kmosaic.o: CXXFLAGS += -I/usr/local/include
kmosaic.o: kmosaic.h

main.o: CXXFLAGS += -isystem googletest/googletest/include

kmosaic_test.o: CXXFLAGS += -I/usr/local/include -isystem googletest/googletest/include
kmosaic_test.o: kmosaic.o

.PHONY: run
run: $(program)
	./$(program)

.PHONY: clean
clean:
	-$(RM) $(program) $(objs)
