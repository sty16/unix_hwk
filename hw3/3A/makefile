
CPPFILES = $(wildcard *.cpp)
obj = $(CPPFILES:%.cpp=%.o)
target = test
CC = g++
CFLAGS = -std=c++11

$(target) : $(obj)
	$(CC) $^ -o $@

%.o : %.cpp
	$(CC) $(CFLAGS) -c $< -o $@ 

.PHONY : clean  
clean:  
	rm -rf $(obj) $(target) 