CXX = clang++
CXXFLAGS = -std=c++1y -g -Wall
VPATH = ../sources

program = kmosaic
objs = kmosaic.o main.o
libs = -lopencv_highgui -lopencv_core -lopencv_imgproc

$(program): CXXFLAGS += -L/usr/local/lib
$(program): $(objs)
	$(CXX) $(CXXFLAGS) $(libs) -o $@ $^

kmosaic.o: CXXFLAGS += -I/usr/local/include
kmosaic.o: kmosaic.cpp kmosaic.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

main.o: CXXFLAGS += -I/usr/local/include
main.o: main.cpp kmosaic.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

run:
	./$(program)

.PHONY: clean
clean:
	-$(RM) $(program) $(objs)
