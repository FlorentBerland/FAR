name=Robot.exe

obj_dir=obj/
src_dir=src/
bin_dir=bin/
data_dir=$(bin_dir)data/
headers_dir=headers/
CC=gcc
CFLAGS=-lpthread -D_REENTRANT -lm
MSG_COM=commit.txt
git=https://www.github.com/FlorentBerland/FAR.git
EXEC=$(bin_dir)$(name)

all: $(EXEC)

$(bin_dir)$(name): $(obj_dir)liste.o $(obj_dir)main.o $(obj_dir)tablach.o $(obj_dir)driver_cptr.o $(obj_dir)driver_ctrl.o $(obj_dir)gopigo.o $(obj_dir)rectangle.o
	$(CC) -o $@ $^ $(CFLAGS) -I $(headers_dir)

$(obj_dir)%.o: $(src_dir)%.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(obj_dir)*.o

mrproper: clean
	rm -f $(bin_dir)$(name)

start: all
	$(bin_dir)$(name)

download:
	git pull
	make

upload: mrproper
	git add *
	git status


