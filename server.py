import threading
import socket


def process_message(client : socket.socket):
    is_clientClosed = False
    while not is_clientClosed:
        message = client.recv(4096)
        if message:
            print(message)
            client.send("All right\n".encode("utf-8"))
        else:
            client.close()
            is_clientClosed = True
            print("Остановлен поток клиента")

def accept_connection(server : socket.socket):
    while True:
        client_socket, addr = server.accept()
        print("Connected from", addr)
        threading.Thread(target=process_message, args=(client_socket, )).start()

def raise_server():
    serv_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, 0)
    serv_socket.bind(('localhost', 4000))
    threading.Thread(target=accept_connection, args=(serv_socket, )).start()


if __name__ == "__main__":
    raise_server()

