#include <Bounce2.h>
Bounce anterior = Bounce(); 
Bounce proximo = Bounce(); 

#define ANTERIOR A0
#define PROXIMO A1

#define ESTADO_BOTAO_DUPLO 1
#define ESTADO_BOTAO_PROXIMO 2
#define ESTADO_BOTAO_ANTERIOR 3

#define ESPERA_MEDIA 300

#define ON HIGH
#define OFF LOW

#define VAZIO_PADRAO B00000000

#define ATIVAR_1 B10000000
#define DESATIVAR_1 B01000000

#define ATIVAR_2    B00100000
#define DESATIVAR_2 B00010000

#define ATIVAR_3    B00001000
#define DESATIVAR_3 B00000100

#define ATIVAR_4    B00000010
#define DESATIVAR_4 B00000001

#define TEMPO_DELAY_LOOP 50
#define TEMPO_DELAY_MOTOR 400
#define TEMPO_DELAY_INICIAR 200

void inicializar(){
  PORTB = (ATIVAR_2 | ATIVAR_3 | ATIVAR_4);
  PORTD = (ATIVAR_1 | ATIVAR_2 | ATIVAR_3);
  delay(TEMPO_DELAY_INICIAR);

  PORTB = (DESATIVAR_2 | DESATIVAR_3 | DESATIVAR_4);
  PORTD = (DESATIVAR_1 | DESATIVAR_2 | DESATIVAR_3);
  delay(TEMPO_DELAY_INICIAR);
}

void executaAlteracoes(int b, int d){
  PORTB = b;
  PORTD = d;
}

void desativarPontos(){
  PORTB = B00000000;
  PORTD = B00000000;
}

void setup() {
  //configuro os pinos dos botoes
  pinMode(ANTERIOR, INPUT_PULLUP);
  pinMode(PROXIMO, INPUT_PULLUP);

  //botao anterior
  anterior.attach(ANTERIOR);
  anterior.interval(5); // interval in ms

  //botao proximo
  proximo.attach(PROXIMO);
  proximo.interval(5); // interval in ms

  DDRB = B11111111; //8 -> 13
  DDRD = DDRD | B11111100; //2 -> 7
  
  //1 input, 0 output
  Serial.begin(9600);

  inicializar();
  inicializar();
  
  desativarPontos();
}

void atualizaBotoes(int *ant, int *prox){
  anterior.update();
  *ant = anterior.read();
  
  proximo.update();
  *prox = proximo.read();
}

void loop() {
    int executa = 0, ant = 0, prox = 0;
    long tempoInicial = 0, tempoFinal = 0, estado = 0;

    atualizaBotoes(&ant,&prox);//obtenho a situacao atual dos botoes
    
    if(ant == HIGH && prox == HIGH){ //se ambos os botoes estiverem pressionados
      
      while (ant == HIGH && prox == HIGH){ //enquanto os botoes forem mantidos pressionados
        if(executa == 0){
          tempoInicial = millis(); //tempo inicial 
          estado = ESTADO_BOTAO_DUPLO;
          executa++;
        }
        
        atualizaBotoes(&ant,&prox); //obtenho o estado atual dos botoees

        //possivel tempo final, caso o usuario pare de apertar os botoes
        tempoFinal = millis();
      }
    
      while(ant == HIGH || prox == HIGH){ //enquanto o usuario naoo soltar os dois botoes o programa nao enviara ou recebera mensagens
        atualizaBotoes(&ant,&prox); //obtenho o estado atual dos botoes
        delay(50);
      }
      
    }
    else{
      
      if(ant == HIGH || prox == HIGH){ //se um dos botoes estiverem pressionados
        
          while (ant == HIGH || prox == HIGH){ //enquanto o usuario nao parar de pressionar todos os botoes
            if(executa == 0){
              tempoInicial = millis();

              if(ant == HIGH){
                estado = ESTADO_BOTAO_ANTERIOR; //se apenas o botao anterior estiver pressionado
              } else{
                estado = ESTADO_BOTAO_PROXIMO; //se apenas o botao proximo estiver pressionado
              }
              executa++;
            }
            
            atualizaBotoes(&ant,&prox); //obtenho o estado atual dos botoes
            tempoFinal = millis(); //possivel tempo final, caso o usuario pare de apertar os botoes
          }
      }
    }

    long tempoPressionado = tempoFinal - tempoInicial;

    switch(estado){
      case ESTADO_BOTAO_ANTERIOR:

        if(tempoPressionado < ESPERA_MEDIA){
          Serial.write("-1");
        } else{
          Serial.write("--1");
        }
        
        break;
      case ESTADO_BOTAO_PROXIMO:
        if(tempoPressionado < ESPERA_MEDIA){
          Serial.write("+1");
        } else{
          Serial.write("++1");
        }
        break;
      case ESTADO_BOTAO_DUPLO:
        if(tempoPressionado < ESPERA_MEDIA){
          Serial.write("+0");
        } else{
          Serial.write("++0");
        }
        break;
    }

    if(Serial.available()){
      int atualB = VAZIO_PADRAO;
      int atualD = VAZIO_PADRAO;
      
      while(Serial.available()){   
        char vlFuncao = Serial.read();
        int vlPonto = Serial.parseInt();
        escolheSentido(vlPonto, vlFuncao, &atualB, &atualD);
      }
      
      executaAlteracoes(atualB, atualD);  
      Serial.write("ok");
      
      delay(TEMPO_DELAY_MOTOR);
      desativarPontos();
    }
    
    delay(TEMPO_DELAY_LOOP);
}

int escolheSentido(int porta, char operacao, int *sinalB, int *sinalD){
  if(operacao == 'l'){
    switch(porta){
      //registradores b
      case 1:
        *sinalB = *sinalB | ATIVAR_2;
        break;
      case 2:
        *sinalB = *sinalB | ATIVAR_3;
        break;
      case 3:
        *sinalB = *sinalB | ATIVAR_4;
        break;
      //registradores c
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
  } else{
    switch(porta){
      //registradores b
      case 1:
        *sinalB = *sinalB | DESATIVAR_2;
        break;
      case 2:
        *sinalB = *sinalB | DESATIVAR_3;
        break;
      case 3:
        *sinalB = *sinalB | DESATIVAR_4;
        break;
      //registradores c
      case 4:
        *sinalD = *sinalD | DESATIVAR_1;
        break;
      case 5:
        *sinalD = *sinalD | DESATIVAR_2;
        break;
      case 6:
        *sinalD = *sinalD | DESATIVAR_3;
        break;
    }
  }
}
