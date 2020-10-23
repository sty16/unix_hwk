
CPPFILES = $(wildcard *.cpp)
obj = $(CPPFILES:%.cpp=%.o)
target = test
CC = g++
CFLAGS = -I ../ -std=c++11

$(target) : $(obj)
	$(CC) $^ -o $@

%.o : %.cpp
	$(CC)  -c $(CFLAGS)  $< -o $@ 


.PHONY : clean  
clean:  
	rm -rf $(obj) $(target) 
