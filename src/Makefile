CC = gcc
CFLAGS = -O3 -Wall -std=gnu11 -march=native `pkg-config hidapi-hidraw --cflags` -g
LDFLAGS = `pkg-config hidapi-hidraw --libs`

objs = usbrh.o
target = usbrh

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(target): $(objs)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(target) $(objs)

all: $(target)

clean:
	rm -rf $(objs) $(target)
