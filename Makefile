TARGET = test
CC=gcc
CFLAGS= -I header
all:
	$(CC) $(CFLAGS) $(TARGET).c -o $(TARGET) 

clean:
	rm $(TARGET)
