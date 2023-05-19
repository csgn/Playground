CC = gcc
CFLAGS = -Wall -Wextra -pedantic -g -fPIC -luuid
LDFLAGS = -LSDL2 -LSDL2_image -ldl -luuid
LDLIBS = -lSDL2 -lSDL2_image -ldl -luuid

SRCS = main.c Manager.c Player.c Enemy.c Ball.c
OBJS = $(SRCS:.c=.o)
TARGET = program
LIBRARY = game.so

all: $(TARGET)

$(TARGET):$(OBJS)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@


$(LIBRARY): $(OBJS)
	$(CC) $(LDFLAGS) $(CFLAGS) -shared $^ $(LDLIBS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) $(LIBRARY)
