
.PHONY: all clean

all: scafe_demo

clean:
	rm -f scafe_demo

scafe_demo: scafe_demo.c
	gcc -Og -g -o scafe_demo scafe_demo.c
