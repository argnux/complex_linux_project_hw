.PHONY: all clean install uninstall

HEADERS = calc.h convert.h input.h error_handler.h
CALC_OBJECTS = sum.o difference.o product.o fraction.o factorial.o square_root.o
CONVERT_OBJECTS = upper.o lower.o
COMPLEX_LINUX_PROJECT_HW_OBJECTS = main.o input.o error_handler.o
CFLAGS += -Wall -Wextra -Werror
BINARY = complex_linux_project_hw

all: ${BINARY}

clean:
	rm -rf ${BINARY} *.o *.a *.so

install:
	cp $$(pwd)/libconvert.so /usr/lib
	cp $$(pwd)/${BINARY} /usr/bin
	chmod 0755 /usr/lib/libconvert.so
	ldconfig

uninstall:
	rm -rf /usr/lib/libconvert.so
	rm -rf /usr/bin/${BINARY}


${BINARY}: ${COMPLEX_LINUX_PROJECT_HW_OBJECTS} libcalc.a libconvert.so
	gcc ${COMPLEX_LINUX_PROJECT_HW_OBJECTS} -o $@ -lconvert -L. -lcalc -lm


main.o: main.c ${HEADERS}
	gcc ${CFLAGS} -c $<

input.o: input.c ${HEADERS}
	gcc ${CFLAGS} -c $<

error_handler.o: error_handler.c ${HEADERS}
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

