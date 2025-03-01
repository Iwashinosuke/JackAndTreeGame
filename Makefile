# ビルド

CC = g++

OBJS = src/*.cpp

LINKER_FLAGS = `pkg-config sdl3 --cflags --libs`

PRODUCT_NAME = JTGame

all : $(OBJS)
	$(CC) $(OBJS) $(LINKER_FLAGS) -o $(PRODUCT_NAME)

clean:
	rm -f $(PRODUCT_NAME)
