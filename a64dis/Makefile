LIBNAME = capstone

all: a64dis

a64dis: a64dis.o
	${CC} $< -O3 -Wall -l$(LIBNAME) -o $@

%.o: %.c
	${CC} -c $< -o $@


clean:
	rm -rf *.o a64dis
