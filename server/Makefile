include ../.config

CC := $(i686-linux-gcc-path)

# Source file and output file
SRC := simple_http_server.c
OUT := t1_server

# Default target to compile the program
all: $(OUT)

$(OUT): $(SRC)
	$(CC) -o $(OUT) $(SRC)

# Clean up generated files
clean:
	rm -f $(OUT)