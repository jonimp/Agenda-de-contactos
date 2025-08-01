CC = gcc
CFLAGS = `pkg-config --cflags gtk+-3.0` -Wall -g
LDFLAGS = `pkg-config --libs gtk+-3.0`

SRC = main.c contacto.c fileops.c ui.c gtkui.c 
OBJ = $(SRC:.c=.o)

TARGET = agenda_gui

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)
