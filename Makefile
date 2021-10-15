CC = g++
CFLAGS = -Wall
LDFLAGS = -pthread
OBJFILES = fork.o main.o philosopher.o
TARGET = main
all: $(TARGET)
$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)
clean:
	rm -f $(OBJFILES) $(TARGET) *~
