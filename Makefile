CFLAGS+=-Wall -Werror -std=gnu99 -O2 
LDFLAGS+=`curl-config --libs`

TARGETS=tfl tfl2
OBJS=buf.o log.o json.o jsmn.o

all: $(TARGETS) .gitignore

clean:
	$(RM) $(TARGETS)
	$(RM) $(OBJS)

tfl: $(OBJS) tfl.o
	$(CC) -o $@ $^ $(LDFLAGS) 

tfl2: $(OBJS) tfl2.o
	$(CC) -o $@ $^ $(LDFLAGS) 

.PHONY: all clean
