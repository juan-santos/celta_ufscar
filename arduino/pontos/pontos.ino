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

#define TEMPO_DELAY_LOOP 50
#define TEMPO_DELAY_MOTOR 100

#define PONTO1A 13
#define PONTO1B 12
#define PONTO2A 11
#define PONTO2B 10
#define PONTO3A 9
#define PONTO3B 8
#define PONTO4A 7
#define PONTO4B 6
#define PONTO5A 5
#define PONTO5B 4
#define PONTO6A 3
#define PONTO6B 2

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

  // motores
  pinMode(PONTO1A, OUTPUT);
  pinMode(PONTO1B, OUTPUT);
  pinMode(PONTO2A, OUTPUT);
  pinMode(PONTO2B, OUTPUT);
  pinMode(PONTO3A, OUTPUT);
  pinMode(PONTO3B, OUTPUT);
  pinMode(PONTO4A, OUTPUT);
  pinMode(PONTO4B, OUTPUT);
  pinMode(PONTO5A, OUTPUT);
  pinMode(PONTO5B, OUTPUT);
  pinMode(PONTO6A, OUTPUT);
  pinMode(PONTO6B, OUTPUT);

  ativarPonto(0,ON);
  delay(TEMPO_DELAY_MOTOR);
  
  ativarPonto(0, OFF);
  delay(TEMPO_DELAY_MOTOR);

  desligar_todos(0);
  
  Serial.begin(9600);
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
      while(Serial.available()){
   
        char vlFuncao = Serial.read();
        int vlPonto = Serial.parseInt();
        
        //verifico se a funcao sera de ligar ou desligar
        if(vlFuncao == 'l'){
          //se for pra ativar
          ativarPonto(vlPonto, ON);
          
        } else{
          if(vlFuncao == 'd'){
            //se for pra desativar
            ativarPonto(vlPonto, OFF);
          }
        }  
      }
      
      Serial.write("ok");
      delay(TEMPO_DELAY_MOTOR);
      desligar_todos(0);
    }
    
    delay(TEMPO_DELAY_LOOP);
}

void ativarPonto(int vpPonto, int vpOperacao){
  switch(vpPonto){
    
    case 0: //EM TODOS os PONTOs
      digitalWrite(PONTO1A, vpOperacao);
      digitalWrite(PONTO1B, !vpOperacao);
      digitalWrite(PONTO2A, vpOperacao);
      digitalWrite(PONTO2B, !vpOperacao);
      digitalWrite(PONTO3A, vpOperacao);
      digitalWrite(PONTO3B, !vpOperacao);
      digitalWrite(PONTO4A, vpOperacao);
      digitalWrite(PONTO4B, !vpOperacao);
      digitalWrite(PONTO5A, vpOperacao);
      digitalWrite(PONTO6B, !vpOperacao);
      digitalWrite(PONTO6B, !vpOperacao);
      return;
      
    case 1:
      digitalWrite(PONTO1A, vpOperacao);
      digitalWrite(PONTO1B, !vpOperacao);
      return;
    case 2:
      digitalWrite(PONTO2A, vpOperacao);
      digitalWrite(PONTO2B, !vpOperacao);
      return;
    case 3:
      digitalWrite(PONTO3A, vpOperacao);
      digitalWrite(PONTO3B, !vpOperacao);
      return;
    case 4:
      digitalWrite(PONTO4A, vpOperacao);
      digitalWrite(PONTO4B, !vpOperacao);
      return;
    case 5:
      digitalWrite(PONTO5A, vpOperacao);
      digitalWrite(PONTO5B, !vpOperacao);
      return;
    case 6:
      digitalWrite(PONTO6A, vpOperacao);
      digitalWrite(PONTO6B, !vpOperacao);
      return;
  }
  return;
}

void desligar_todos(int vpPonto){
 switch(vpPonto){
    
    case 0: //EM TODOS os PONTOs
      digitalWrite(PONTO1A, OFF);
      digitalWrite(PONTO1B, OFF);
      digitalWrite(PONTO2A, OFF);
      digitalWrite(PONTO2B, OFF);
      digitalWrite(PONTO3A, OFF);
      digitalWrite(PONTO3B, OFF);
      digitalWrite(PONTO4A, OFF);
      digitalWrite(PONTO4B, OFF);
      digitalWrite(PONTO5A, OFF);
      digitalWrite(PONTO5B, OFF);
      digitalWrite(PONTO6A, OFF);
      digitalWrite(PONTO6B, OFF);
      return;
      
    case 1:
      digitalWrite(PONTO1A, OFF);
      digitalWrite(PONTO1B, OFF);
      return;
    case 2:
      digitalWrite(PONTO2A, OFF);
      digitalWrite(PONTO2B, OFF);
      return;
    case 3:
      digitalWrite(PONTO3A, OFF);
      digitalWrite(PONTO3B, OFF);
      return;
    case 4:
      digitalWrite(PONTO4A, OFF);
      digitalWrite(PONTO4B, OFF);
      return;
    case 5:
      digitalWrite(PONTO5A, OFF);
      digitalWrite(PONTO5B, OFF);
      return;
    case 6:
      digitalWrite(PONTO6A, OFF);
      digitalWrite(PONTO6B, OFF);
      return;
  }
 
}
