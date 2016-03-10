all:
	gcc serial_helper.c -c -o serial_helper.o
	g++ serial_test.cpp serial.cpp serial_helper.o -o serial-test

clean:
	rm -f *.o serial-test
