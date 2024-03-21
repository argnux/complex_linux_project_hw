.PHONY: all clean

HEADERS = calc.h convert.h
CALC_OBJECTS = sum.o difference.o product.o fraction.o factorial.o square_root.o
CONVERT_OBJECTS = upper.o lower.o
CFLAGS += -Wall -Wextra -Werror

all: main

clean:
	rm -rf main *.o *.a *.so


main: main.o libcalc.a libconvert.so
	gcc -o main -L. -lcalc -lconvert main.o


main.o: main.c ${HEADERS}
	gcc ${CFLAGS} -c $<


libcalc.a: ${CALC_OBJECTS}
	ar -rcs $@ $^

sum.o: sum.c calc.h
	gcc ${CFLAGS} -c $<

difference.o: difference.c calc.h
	gcc ${CFLAGS} -c $<

product.o: product.c calc.h
	gcc ${CFLAGS} -c $<

fraction.o: fraction.c calc.h
	gcc ${CFLAGS} -c $<

factorial.o: factorial.c calc.h
	gcc ${CFLAGS} -c $<

square_root.o: square_root.c calc.h
	gcc ${CFLAGS} -c $<


libconvert.so: ${CONVERT_OBJECTS}
	gcc -shared -o $@ $^

upper.o: upper.c convert.h
	gcc ${CFLAGS} -fpic -c $<

lower.o: lower.c convert.h
	gcc ${CFLAGS} -fpic -c $<

