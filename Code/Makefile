name=Wheely
name_init_bbt=InitBeebotte

obj_dir=obj/
src_dir=src/
bin_dir=bin/
data_dir=$(bin_dir)data/
headers_dir=headers/
CC=gcc
CFLAGS=-lpthread -D_REENTRANT -lm
EXEC=$(bin_dir)$(name)
INIT_BBT=$(bin_dir)$(name_init_bbt)

all: $(EXEC) $(INIT_BBT)

$(EXEC): $(obj_dir)liste.o $(obj_dir)main.o $(obj_dir)tablach.o $(obj_dir)driver_cptr.o $(obj_dir)driver_ctrl.o $(obj_dir)gopigo.o $(obj_dir)rectangle.o $(obj_dir)positionnement.o #$(obj_dir)communication.o $(obj_dir)com_interface.o
	$(CC) -o $@ $^ $(CFLAGS) -I $(headers_dir)

$(INIT_BBT): $(obj_dir)BeebotteSend.o
	$(CC) -o $@ $^ $(CFLAGS)

$(obj_dir)%.o: $(src_dir)%.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(obj_dir)*.o

mrproper: clean
	rm -f $(EXEC) $(INIT_BBT)

start: all
	$(INIT_BBT)
	./monitoring/bin/monitoringServer.farm & $(EXEC)

test: all
	$(EXEC)

download:
	git pull origin master
	make

upload: mrproper
	git add *
	git status


