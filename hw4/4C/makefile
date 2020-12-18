
CPPFILES = $(wildcard *.c)
obj = $(CPPFILES:%.c=%.o)
target = test
CC = gcc
CFLAGS = -I ../ 

$(target) : $(obj)
	$(CC) $^ -o $@

%.o : %.cpp
	$(CC)  -c $(CFLAGS)  $< -o $@ 


.PHONY : clean  
clean:  
	rm -rf $(obj) $(target) 
