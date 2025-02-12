CC=gcc
CFLAGS=-Wall

SRCS=main.c fila.c arvore.c comandos.c
OBJS=$(SRCS:.c=.o)
TARGET=pet_system

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del *.o $(TARGET).exe
