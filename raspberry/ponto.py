import RPi.GPIO as GPIO
import time
from typing import List, Tuple

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


def setup():
    GPIO.setmode(GPIO.BCM)

    GPIO.setup(EnabledMotor, GPIO.OUT) # pino responsável por ativar/desativar todos os motores

    for enabled, disabled in zip(EnabledList, DisabledList):
        GPIO.setup(enabled, GPIO.OUT) # configuro todos os pinos
        GPIO.setup(disabled, GPIO.OUT)

    GPIO.output(EnabledMotor, GPIO.HIGH)  # Liga todos os motores

# Loop principal
def loop():
    while True:
        changeGPIO('101010')

        # Aguarda um tempo
        time.sleep(10)

        changeGPIO('111000')

        time.sleep(10)

def changeGPIO(message: str):
    enabled: List[int] = []
    disabled: List[int] = []

    if len(message) == 6:
        for value in message:
            enabled.append(GPIO.HIGH if value == '1' else GPIO.LOW)
            disabled.append(GPIO.LOW if value == '1' else GPIO.HIGH)
    else:
        return '' # caso o código recebido pelo aplicativo não esteja adequado ao padrão

    GPIO.output(EnabledList + DisabledList, enabled + disabled)
    # print('Lista de pinos completa: ', EnabledList + DisabledList)
    # print('Lista de ativacao: ', enabled)
    # print('Lista de desativacao: ', disabled)

def destroy():
    GPIO.cleanup()


if __name__ == '__main__':     # Program start from here

    setup()

    try:
        print('Pressione Ctrl+C para sair')
        loop()
    except KeyboardInterrupt:
        destroy()
