CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = banking

all: $(TARGET)

$(TARGET): src/banking.c
	$(CC) $(CFLAGS) src/banking.c -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)
