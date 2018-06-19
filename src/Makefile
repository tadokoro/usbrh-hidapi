CC = gcc
CFLAGS = -O3 -Wall -std=gnu11 -march=native -g
USBRH_HIDAPI_BACKEND = libusb

ifeq ($(USBRH_HIDAPI_BACKEND), libusb)
	CFLAGS += `pkg-config hidapi-libusb --cflags`
	LDFLAGS += `pkg-config hidapi-libusb --libs`
else
	CFLAGS += `pkg-config hidapi-hidraw --cflags`
	LDFLAGS += `pkg-config hidapi-hidraw --libs`
endif

objs = usbrh.o
target = usbrh

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

$(target): $(objs)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(target) $(objs)

all: $(target)

clean:
	rm -rf $(objs) $(target)
