CC = gcc
CFLAGS = -Wall

TARGET = text_editor

SRC = main.c \
      text_editor.c \
      text_operations.c \
      file_operations.c \
      display.c \
      cursor_navigation.c \
      undo_redo.c \
      stack.c

OBJ = $(SRC:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(TARGET)