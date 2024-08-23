all: server client

server: server.cpp
	@g++ -o server server.cpp -lws2_32

client: client.cpp
	@g++ -o client client.cpp -lws2_32

clean:
	@del server.exe client.exe