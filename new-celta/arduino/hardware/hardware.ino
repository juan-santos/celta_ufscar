#include <Bounce2.h>

Bounce anterior = Bounce();
Bounce proximo = Bounce();

#define BEEP A0
#define ANTERIOR A2
#define PROXIMO A5

#define ESTADO_BOTAO_DUPLO 1
#define ESTADO_BOTAO_PROXIMO 2
#define ESTADO_BOTAO_ANTERIOR 3

#define ESPERA_BAIXA 200
#define ESPERA_MEDIA 500

#define ON HIGH
#define OFF LOW

#define VAZIO_PADRAO B00000000

#define ATIVAR_1 B10000000
#define DESATIVAR_1 B00000000

#define ATIVAR_2 B00100000
#define DESATIVAR_2 B00000000

#define ATIVAR_3 B00001000
#define DESATIVAR_3 B00000000

#define ATIVAR_4 B00000010
#define DESATIVAR_4 B00000000

#define TEMPO_DELAY_LOOP 50
#define TEMPO_DELAY_MOTOR 400
#define TEMPO_ESPERA_BOTAO_DUPLO 400
#define TEMPO_DELAY_INICIAR 200

void inicializar() {
  PORTB = (ATIVAR_2 | ATIVAR_3 | ATIVAR_4);
  PORTD = (ATIVAR_1 | ATIVAR_2 | ATIVAR_3);
  delay(TEMPO_DELAY_INICIAR);

  PORTB = (DESATIVAR_2 | DESATIVAR_3 | DESATIVAR_4);
  PORTD = (DESATIVAR_1 | DESATIVAR_2 | DESATIVAR_3);
  delay(TEMPO_DELAY_INICIAR);
}

void executaAlteracoes(int b, int d) {
  PORTB = b;
  PORTD = d;
}

void desativarPontos() {
  PORTB = B00000000;
  PORTD = B00000000;
}

void setup() {
  // configuro os pinos dos botoes
  pinMode(ANTERIOR, INPUT_PULLUP);
  pinMode(PROXIMO, INPUT_PULLUP);

  pinMode(BEEP, OUTPUT);

  // botao anterior
  anterior.attach(ANTERIOR);
  anterior.interval(5); // interval in ms

  // botao proximo
  proximo.attach(PROXIMO);
  proximo.interval(5); // interval in ms

  DDRB = B11111111;        // 8 -> 13
  DDRD = DDRD | B11111100; // 2 -> 7

  // 1 input, 0 output
  Serial.begin(9600);

  inicializar();
  inicializar();
  
  desativarPontos();
}

void atualizaBotoes(int *ant, int *prox) {
  anterior.update();
  *ant = anterior.read();

  proximo.update();
  *prox = proximo.read();
}

void loop() {

  int executa = 0, botao2Clicado = 0, ant = 0, prox = 0;
  long tempoInicial = 0, tempoFinal = 0, estado = -1;

  atualizaBotoes(&ant, &prox); // obtenho a situacao atual dos botoes
  tempoInicial = millis(); // obtenho o tempo inicial

  if (ant == HIGH) {

    // enquanto o botao anterior estiver sendo pressionado
    while (ant == HIGH) {
      int inicioBotao2 = millis();

      //verifico se o outro botão também está sendo apertado
      while (prox == HIGH) {
        botao2Clicado++;
        atualizaBotoes(&ant, &prox);
      }

      if (botao2Clicado > 0) {
        estado = (millis() - inicioBotao2 > ESPERA_BAIXA)
          ? ESTADO_BOTAO_DUPLO 
          : ESTADO_BOTAO_ANTERIOR;

      } else if (executa == 0) {
        estado = ESTADO_BOTAO_ANTERIOR;
        executa++;
      }

      atualizaBotoes(&ant, &prox); // obtenho o estado atual dos botoees
    }
  } else if (prox == HIGH) {
    // enquanto o botao anterior estiver sendo pressionado
    while (prox == HIGH) {
      int inicioBotao2 = millis();

      //verifico se o outro botão também está sendo apertado
      while (ant == HIGH) {
        botao2Clicado++;
        atualizaBotoes(&ant, &prox);
      }

      if (botao2Clicado > 0) {
        estado = (millis() - inicioBotao2 > ESPERA_BAIXA)
          ? ESTADO_BOTAO_DUPLO 
          : ESTADO_BOTAO_PROXIMO;

      } else if (executa == 0) {
        estado = ESTADO_BOTAO_PROXIMO;
        executa++;   
      }

      atualizaBotoes(&ant, &prox); // obtenho o estado atual dos botoees
    }
  }

  tempoFinal = millis();// tempo final, para quando o usuario parar de apertar os botoes
  long tempoPressionado = tempoFinal - tempoInicial;

  switch (estado) {
    case ESTADO_BOTAO_ANTERIOR:
      (tempoPressionado < ESPERA_MEDIA) 
        ? Serial.write("-1")
        : Serial.write("--1");

      break;

    case ESTADO_BOTAO_PROXIMO:
      (tempoPressionado < ESPERA_MEDIA) 
        ? Serial.write("+1")
        : Serial.write("++1");

      break;

    case ESTADO_BOTAO_DUPLO:
      Serial.write("++0");

      delay(TEMPO_ESPERA_BOTAO_DUPLO);
      break;
  }

  if (Serial.available()) {
    int atualB = VAZIO_PADRAO;
    int atualD = VAZIO_PADRAO;

    while (Serial.available()) {
      char vlFuncao = Serial.read();
      int vlPonto = Serial.parseInt();
      escolheSentido(vlPonto, vlFuncao, &atualB, &atualD);
    }

    executaAlteracoes(atualB, atualD);
    delay(TEMPO_DELAY_MOTOR);

    Serial.write("ok");
    // desativarPontos();
  }
}

int escolheSentido(int porta, char operacao, int *sinalB, int *sinalD) {
  if (operacao == 'l') {
    switch (porta) {
      // registradores b
      case 1:
        *sinalB = *sinalB | ATIVAR_2;
        break;
      case 2:
        *sinalB = *sinalB | ATIVAR_3;
        break;
      case 3:
        *sinalB = *sinalB | ATIVAR_4;
        break;
      // registradores c
      case 4:
        *sinalD = *sinalD | ATIVAR_1;
        break;
      case 5:
        *sinalD = *sinalD | ATIVAR_2;
        break;
      case 6:
        *sinalD = *sinalD | ATIVAR_3;
        break;
    }

  } else {

    switch (porta) {
      // registradores b
      case 1:
        *sinalB = *sinalB | DESATIVAR_2;
        break;
      case 2:
        *sinalB = *sinalB | DESATIVAR_3;
        break;
      case 3:
        *sinalB = *sinalB | DESATIVAR_4;
        break;
      // registradores c
      case 4:
        *sinalD = *sinalD | DESATIVAR_1;
        break;
      case 5:
        *sinalD = *sinalD | DESATIVAR_2;
        break;
      case 6:
        *sinalD = *sinalD | VAZIO_PADRAO;
        break;
    }
  }
}
