# Add all header files in HEADERS and objects created from cpps to OBJECTS
HEADERS = stars.h star_list.h
OBJECTS = stars.o star_list.o dijkstra.o traversal.o draw_map.o kruskal.o

default: stars

CXX=clang++
# Note to Will - remember to change to g++ so you can compile it correctly
CXXFlAGS=-g -std=c++11 -pedantic -Wall -Werror -Wfatal-errors -Wextra -Wno-unused-parameter -Wno-unused-variable -Wno-unused-function

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFlAGS) -c $< -o $@

stars: $(OBJECTS) main.o
	$(CXX) $(CXXFlAGS) $(OBJECTS) main.o -o $@

test: $(OBJECTS) test_main.o
	$(CXX) $(CXXFlAGS) test_main.o $(OBJECTS) -o $@

clean:
	rm -f $(OBJECTS)
	rm -f main.o
	rm -f test_main.o
	rm -f stars
	rm -f test