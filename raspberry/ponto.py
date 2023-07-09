#!usr/bin/env python3
import RPi.GPIO as GPIO
import time
from typing import List, Tuple
import socket   
import threading

EnabledMotor = 2

# pinos responsáveis por fazer o motor girar no sentido que ative o braille
ATIVAR1 = 0 #PIN 27
ATIVAR2 = 5 #PIN 29
ATIVAR3 = 6 #PIN 31
ATIVAR4 = 13 #PIN 33
ATIVAR5 = 19 #PIN 35
ATIVAR6 = 26 #PIN 37

# pinos responsáveis por fazer o motor girar no sentido que desative o braille
DESATIVAR1 = 7 #PIN 26
DESATIVAR2 = 1 #PIN 28
DESATIVAR3 = 12 #PIN 32
DESATIVAR4 = 16 #PIN 36
DESATIVAR5 = 20 #PIN 38
DESATIVAR6 = 21 #PIN 40

EnabledList: Tuple[int] = (ATIVAR1, ATIVAR2, ATIVAR3, ATIVAR4, ATIVAR5, ATIVAR6)
DisabledList: Tuple[int] = (DESATIVAR1, DESATIVAR2, DESATIVAR3,
                DESATIVAR4, DESATIVAR5, DESATIVAR6)

tcp = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

def setup():  
    GPIOConfig()

    GPIO.output(EnabledMotor, GPIO.HIGH)  # Liga todos os motores
    
    #inicio os motores, de forma a abaixar possiveis pinos que estejam levantados
    changeGPIO('000000')
    time.sleep(0.2)
    changeGPIO('000000')

# Método responsável por configurar a placa do raspberry
def GPIOConfig():
    GPIO.setmode(GPIO.BCM)

    GPIO.setup(EnabledMotor, GPIO.OUT) # pino responsável por ativar/desativar todos os motores

    for enabled, disabled in zip(EnabledList, DisabledList):
        GPIO.setup(enabled, GPIO.OUT) # configuro todos os pinos
        GPIO.setup(disabled, GPIO.OUT)

# Método responsável por ficar escutando os botões e enviar o status ao cliente
def loop_button(encerrar_event, client_socket):
    while not encerrar_event.is_set():
        client_socket.send('Loop do botao'.encode())
        time.sleep(10)
        pass

# Loop principal
def loop():
    while True:    
        client_socket, address = tcp.accept()
        message = "Conectado"

        client_socket.send(message.encode())

        encerrar_event = threading.Event()
        button_thread = threading.Thread(daemon=True, target=loop_button, args=(encerrar_event, client_socket,))
        button_thread.start()

        while True:
            decodeMessage = client_socket.recv(1024).decode() 

            if not decodeMessage:
                encerrar_event.set()
                button_thread.join()
                break

            resposta = changeGPIO(decodeMessage)
            client_socket.send(resposta.encode())

#Método responsável por ler o código da letra e ativar/desativar os pinos correspondentes
def changeGPIO(message: str) -> str :
    print('Letra recebida: ', message)
    enabled: List[int] = []
    disabled: List[int] = []

    if len(message) == 6:
        for value in message:
            if value in ['1', '0']:
                enabled.append(GPIO.HIGH if value == '1' else GPIO.LOW)
                disabled.append(GPIO.LOW if value == '1' else GPIO.HIGH)
            else:
                return 'código inválido'
    else: 
        return 'código inválido' # caso o código recebido pelo aplicativo não esteja adequado ao padrão

    GPIO.output(EnabledList + DisabledList, enabled + disabled)
    time.sleep(0.4)

    GPIO.output(EnabledList + DisabledList, GPIO.LOW) #Após os motores exibirem a 
                                                #letra eu desativo todos os motores
    return "ok"

# Método responsável por limpar as placas GPIO e encerrar a conexão socket
def destroy():
    GPIO.cleanup()
    tcp.close()

if __name__ == '__main__':     # Program start from here
    # Variavel responsável pela conexão socket
    tcp.bind(('localhost', 50000))
    tcp.listen(1)

    setup()
    try:
        print('Pressione Ctrl+C para sair')
        loop()
    except KeyboardInterrupt:
        destroy() 
