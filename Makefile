CFLAGS+=$(shell pkg-config --cflags json)
LDFLAGS+=$(shell pkg-config --libs json)

CFLAGS+=-Wall -Werror -std=gnu99 -O2 
LDFLAGS+=`curl-config --libs`

TARGETS=tflstatus
OBJS=fetch.o parse.o line.o display.o

all: $(TARGETS)

clean:
	$(RM) $(TARGETS)
	$(RM) $(OBJS)

tflstatus: $(OBJS) tflstatus.o
	$(CC) -o $@ $^ $(LDFLAGS) 

.PHONY: all clean
