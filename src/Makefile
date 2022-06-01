CC = gcc

CCFLAGS = -g


LIBS = -lgpib
SOURCES = utils.c
OBJS = $(SOURCES:.c=.o)


%.o: %.c
	@echo "[CC]   $<"
	@$(CC) -c $< $(CCFLAGS) -o $@


all: test getcal setcal

test: $(OBJS) test.o
	@echo "[LINK]  test"
	@$(CC) $(LIBS) -o ../test $(OBJS) test.o

getcal: $(OBJS) getcal.o
	@echo "[LINK]  getcal"
	@$(CC) $(LIBS) -o ../getcal $(OBJS) getcal.o

setcal: $(OBJS) setcal.o
	@echo "[LINK]  setcal"
	@$(CC) $(LIBS) -o ../setcal $(OBJS) setcal.o

clean:
	@rm -f $(OBJS) test.o getcal.o setcal.o

