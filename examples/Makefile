CXX = clang++
CXXFLAGS = -std=c++1y -g -Wall
VPATH = ../sources
.SUFFIXES: .cpp .o

program = kmosaic
objs = kmosaic.o main.o
libs = -lopencv_highgui -lopencv_core -lopencv_imgproc

$(program): $(objs)
	$(CXX) $(CXXFLAGS) -L/usr/local/lib $(libs) -o $@ $^

.cpp.o:
	$(CXX) $(CXXFLAGS) -c -o $@ $<

kmosaic.o: CXXFLAGS += -I/usr/local/include
kmosaic.o: kmosaic.h

main.o: CXXFLAGS += -I/usr/local/include
main.o: kmosaic.h

.PHONY: run
run: $(program)
	./$(program)

.PHONY: clean
clean:
	-$(RM) $(program) $(objs)
