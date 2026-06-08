TARGET := renplat
SRCS = renplat.c xmalloc.c entity.c
OBJS = $(SRCS:.c=.o)

CFLAGS = -Wall -g -O2 -Wpedantic --std=c11
LDFLAGS =
LDLIBS = -lraylib -lm

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean
