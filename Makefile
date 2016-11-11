JSON_C_DIR=/usr/local/Cellar/json-c/0.12
CFLAGS+=-I$(JSON_C_DIR)/include/json-c
LDFLAGS+=-L$(JSON_C_DIR)/lib -ljson-c

CFLAGS+=-Wall -Werror -std=gnu99 -O2 
LDFLAGS+=`curl-config --libs`

TARGETS=tflstatus
OBJS=fetch.o parse.o

all: $(TARGETS)

clean:
	$(RM) $(TARGETS)
	$(RM) $(OBJS)

tflstatus: $(OBJS) tflstatus.o
	$(CC) -o $@ $^ $(LDFLAGS) 

.PHONY: all clean
