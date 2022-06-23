#-*- Makefile -*-

EXEC = generate.out
OBJS = generate.o 


$(EXEC): $(OBJS)
	gcc $(OBJS) -o $(EXEC)

%.o: %.c
	gcc -g -c $< -o $@

clean:
	rm -f *.o *.out $(EXEC)

run:
	./$(EXEC)
