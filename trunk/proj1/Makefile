CC = gcc
CC_FLAGS = -ggdb -pedantic -Wall

all: server client

client: client.o
	$(CC) $(CC_FLAGS) client.o -o client

client.o: client.c
	$(CC) $(CC_FLAGS) -c client.c

server: server.o
	$(CC) $(CC_FLAGS) server.o -o server -I/usr/include/mysql -L/usr/lib/mysql -lmysqlclient -lnsl -lm -lz

server.o: server.c
	$(CC) -I/usr/include/mysql -L/usr/lib/mysql $(CC_FLAGS) -c server.c -lmysqlclient -lnsl -lm -lz

clean:
	rm *.o server client
