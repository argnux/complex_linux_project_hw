.PHONY: all clean install uninstall

HEADERS = calc.h convert.h
CALC_OBJECTS = sum.o difference.o product.o fraction.o factorial.o square_root.o
CONVERT_OBJECTS = upper.o lower.o
CFLAGS += -Wall -Wextra -Werror

all: main

clean:
	rm -rf main *.o *.a *.so

install:
	cp $$(pwd)/libconvert.so /usr/lib
	cp $$(pwd)/main /usr/bin
	chmod 0755 /usr/lib/libconvert.so
	ldconfig

uninstall:
	rm -rf /usr/lib/libconvert.so
	rm -rf /usr/bin/main


main: main.o libcalc.a libconvert.so
	gcc main.o -o main -lconvert -L. -lcalc -lm


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

