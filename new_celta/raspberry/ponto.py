#!usr/bin/env python3
import RPi.GPIO as GPIO
import time
from typing import List, Tuple
import socket   
import threading

# Variáveis para gerenciar os botões
inicio_botao1 = 0
inicio_botao2 = 0

final_botao1 = 0
final_botao2 = 0

duploClick = False

# pino para ativar todos os motores
ENABLED_MOTOR = 2 #PIN 3

# pinos dos botões
BUTTON_NEXT = 24 #PIN 18
BUTTON_BACK = 25 #PIN 22

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

# Função de callback para o Botão 1
def callback_botao1(channel):
    global inicio_botao1
    global final_botao1
    global duploClick

    estado_botao2 = GPIO.input(BUTTON_BACK)

    if not GPIO.input(BUTTON_NEXT):  # Botão pressionado
        inicio_botao1 = time.time()

        if estado_botao2:
            duploClick = True

    else:  # Botão solto
        final_botao1 = time.time() - inicio_botao1
        
# Função de callback para o Botão 2
def callback_botao2(channel):
    global inicio_botao2
    global final_botao2
    global duploClick

    estado_botao1 = GPIO.input(BUTTON_NEXT)
    
    if GPIO.input(BUTTON_BACK):  # Botão pressionado
        inicio_botao2 = time.time()

        if not estado_botao1:
            duploClick = True

    else:  # Botão solto
        final_botao2 = time.time() - inicio_botao2
     
def setup():  
    GPIOConfig()

    GPIO.output(ENABLED_MOTOR, GPIO.HIGH)  # Liga todos os motores
    
    #inicio os motores, de forma a abaixar possiveis pinos que estejam levantados
    changeGPIO('000000')
    time.sleep(0.2)
    changeGPIO('000000')

# Método responsável por configurar a placa do raspberry
def GPIOConfig():
    GPIO.setmode(GPIO.BCM)

    GPIO.setup(ENABLED_MOTOR, GPIO.OUT) # pino responsável por ativar/desativar todos os motores
    
    GPIO.setup(BUTTON_NEXT, GPIO.IN, pull_up_down=GPIO.PUD_UP)    # Pino do botão como saída e aciona o pull-up
    GPIO.setup(BUTTON_BACK, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

    GPIO.setup(EnabledList + DisabledList, GPIO.OUT) # configuro todos os pinos

# Método responsável por ficar escutando os botões e enviar o status ao cliente
def loop_button(encerrar_event, client_socket):
    global final_botao1
    global final_botao2
    global duploClick

    while not encerrar_event.is_set():
        if duploClick:
            while (not final_botao1) or (not final_botao2):
                pass

            time.sleep(0.2)

            if final_botao1 > 0.3 or final_botao2 > 0.3:
                client_socket.send("++0\n".encode())
                print("Enviado ", "++0")
            else:
                client_socket.send("+0\n".encode())
                print("Enviado ", "+0")

            final_botao1 = 0
            final_botao2 = 0
            duploClick = False

        if final_botao1:
            if final_botao1 > 0.3:
                client_socket.send("++1\n".encode())
                print("Enviado ", "++1")
            else:
                client_socket.send("+1\n".encode())
                print("Enviado ", "+1")

            final_botao1 = 0

        elif final_botao2:
            if final_botao2 > 0.3:
                client_socket.send("--1\n".encode())
                print("Enviado ", "--1")
            else:
                client_socket.send("-1\n".encode())
                print("Enviado ", "-1")

            final_botao2 = 0

        pass 

# Loop principal
def loop():
    while True:    
        client_socket, address = tcp.accept()
        message = "Conectado\n"

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
            if resposta:
                client_socket.send(resposta.encode())
                print("Enviado ", resposta.encode())

#Método responsável por ler o código da letra e ativar/desativar os pinos correspondentes
def changeGPIO(message: str) -> str :
    print("Letra recebida: ", message)
    enabled: List[int] = []
    disabled: List[int] = []

    if len(message) == 6:
        for value in message:
            if value in ['1', '0']:
                enabled.append(GPIO.HIGH if value == '1' else GPIO.LOW)
                disabled.append(GPIO.LOW if value == '1' else GPIO.HIGH)
            else:
                return ''
    else: 
        return '' # caso o código recebido pelo aplicativo não esteja adequado ao padrão

    GPIO.output(EnabledList + DisabledList, enabled + disabled)
    time.sleep(0.4)

    GPIO.output(EnabledList + DisabledList, GPIO.LOW) #Após os motores exibirem a 
                                                #letra eu desativo todos os motores
    return "ok\n"

# Método responsável por limpar as placas GPIO e encerrar a conexão socket
def destroy():
    GPIO.cleanup()
    tcp.close()

if __name__ == '__main__':     # Program start from here
    # Variavel responsável pela conexão socket
    tcp.bind(('192.168.15.30', 50000))
    tcp.listen(1)

    setup()

    # Registro dos callbacks para os eventos de nível alto (RISING)
    GPIO.add_event_detect(BUTTON_NEXT, GPIO.BOTH, callback=callback_botao1, bouncetime=75)
    GPIO.add_event_detect(BUTTON_BACK, GPIO.BOTH, callback=callback_botao2, bouncetime=75)

    try:
        print('Pressione Ctrl+C para sair')
        loop()
    except KeyboardInterrupt:
        destroy() 
