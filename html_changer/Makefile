include ../.config

CC := $(i686_linux_gcc_path)
CFLAGS = -Wall -Wextra -O2
TARGET = t1_html_changer
SRC = html_changer.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)

.PHONY: all clean