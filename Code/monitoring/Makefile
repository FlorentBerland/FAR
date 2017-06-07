obj_dir=obj/
bin_dir=bin/
src_dir=src/
CC=gcc
CFLAGS=-Wall -g
LDFLAGS=-g
EXEC=$(bin_dir)monitoringServer.farm

all: $(EXEC)

$(bin_dir)monitoringServer.farm: $(obj_dir)main.o
	$(CC) -o $@ $^ $(LDFLAGS)

$(obj_dir)%.o: $(src_dir)%.c
	$(CC) $(CFLAGS) -o $@ -c $<

doxygen:
	doxygen Doxyfile

clean:
	find . -type f | xargs -n 5 touch
	rm -f $(obj_dir)* $(bin_dir)*

start:
	./$(EXEC)
