MAIN=main
MEM=mem

TARGET = best first worst

all: $(TARGET)


$(TARGET):
	export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:.
	gcc -c -fpic $(MEM)_$@.c
	gcc -shared -o lib$(MEM)_$@.so $(MEM)_$@.o
	gcc $(MAIN)_$@.c -l$(MEM)_$@ -L. -o $(MAIN)_$@


clean:
	rm -f $(MAIN)_best $(MAIN)_worst $(MAIN)_first
	rm -f *.o *.so
