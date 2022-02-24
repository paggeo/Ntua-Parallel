.phony: all clean

all: fw fw_sr fw_tiled fw_tiled_o2

CC=gcc
CFLAGS= -Wall -O3 -fopenmp -Wno-unused-variable
O2FLAGS= -Wall -O2 -fopenmp -Wno-unused-variable

HDEPS+=%.h

OBJS=util.o


fw: $(OBJS) fw.c 
	$(CC) $(OBJS) fw.c -o fw $(CFLAGS)

fw_sr: fw_sr.c 
	$(CC) $(OBJS) fw_sr.c -o fw_sr $(CFLAGS)

fw_tiled: fw_tiled.c 
	$(CC) fw_tiled.c -o fw_tiled $(CFLAGS)

fw_tiled_o2: fw_tiled.c
	$(CC) fw_tiled.c -o fw_tiled_o2 $(O2FLAGS)

fw_sr_util: fw_sr_util.c
	$(CC) fw_sr_util.c -o fw_sr_util $(CFLAGS)

%.o: %.c $(HDEPS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o fw fw_sr fw_tiled fw_sr_util fw_tiled_o2
