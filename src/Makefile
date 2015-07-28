CC=g++

all: updateQueue daemon

updateQueue: main.o http.o database.o message.o telegram.o bot.o
	$(info Inzio generazione 'updateQueue')
	@$(CC) build/main.o build/http.class.o build/database.class.o build/message.class.o \
	build/telegram.class.o build/bot.class.o -o updateQueue -lcurl -lmysqlcppconn
	$(info 'updateQueue' generato con successo)

daemon: daemon.o
	$(info Inzio generazione 'daemon')
	@$(CC) build/daemon.o build/http.class.o build/database.class.o build/message.class.o \
	build/telegram.class.o build/bot.class.o build/common.o -o daemon -lcurl -lmysqlcppconn
	$(info 'daemon' generato con successo)
	
daemon.o:
	$(info Inzio compilazione daemon.cpp)
	@$(CC) -c daemon.cpp -o build/daemon.o -std=c++0x
	$(info 'daemon.cpp' compilato in 'build/daemon.o')

main.o: bot.o
	$(info Inzio compilazione main.cpp)
	@$(CC) -c main.cpp -o build/main.o -std=c++0x
	$(info 'main.cpp' compilato in 'build/main.o')

bot.o: common.o telegram.o message.o database.o
	$(info Inzio compilazione 'class/bot.class.cpp'...)
	@$(CC) -c class/bot.class.cpp -o build/bot.class.o -std=c++0x
	$(info 'class/bot.class.cpp' compilato in 'build/bot.class.o')

telegram.o: http.o
	$(info Inzio compilazione 'class/telegram.class.cpp'...)
	@$(CC) -c class/telegram.class.cpp -o build/telegram.class.o -std=c++0x
	$(info 'class/telegram.class.cpp' compilato in 'build/telegram.class.o')

message.o:
	$(info Inzio compilazione 'class/message.class.cpp'...)
	@$(CC) -c class/message.class.cpp -o build/message.class.o
	$(info 'class/message.class.cpp' compilato in 'build/message.class.o')

database.o:
	$(info Inzio compilazione 'class/database.class.cpp'...)
	@$(CC) -c class/database.class.cpp -o build/database.class.o
	$(info 'class/database.class.cpp' compilato in 'build/database.class.o')

http.o:
	$(info Inzio compilazione 'class/http.class.cpp'...)
	@$(CC) -c class/http.class.cpp -o build/http.class.o
	$(info 'class/http.class.cpp' compilato in 'build/http.class.o')

common.o:
	$(info Inzio compilazione 'include/common.cpp'...)
	@$(CC) -c include/common.cpp -o build/common.o
	$(info 'include/common.cpp' compilato in 'build/common.o')


clean:
	find . -name "*.o" -type f -delete
	rm updateQueue