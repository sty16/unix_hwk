
CFILES = $(wildcard *.c)
obj = $(CFILES:%.c=%.o)
target = test
CC = gcc

$(target) : $(obj)
	$(CC) $^ -o $@

%.o : %.c
	$(CC) -c $< -o $@ 

.PHONY : clean  
clean:  
	rm -rf $(obj) $(target) 
