#!usr/bin/env python3

import socket

HOST = '192.168.15.30'
PORT = 50000

client_socket: socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

def setup():
    client_socket.connect((HOST, PORT))

def loop():        
    response = client_socket.recv(1024).decode()
    print('Início:', response)

    while True:
        # Envia uma mensagem para o servidor
        message = input('Digite uma mensagem para o servidor (ou digite "sair" para encerrar): ')

        if message == 'sair':
            break

        client_socket.send(message.encode())

        # Recebe a resposta do servidor
        response = client_socket.recv(1024).decode()
        print('Resposta do servidor:', response)
    
    destroy()

def destroy():
    client_socket.close()

if __name__ == '__main__':     # Program start from here
    setup()
    try:
        loop()
    except KeyboardInterrupt:
        destroy()