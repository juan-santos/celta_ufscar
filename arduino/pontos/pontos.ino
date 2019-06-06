int ponto1A = 13;
int ponto1B = 12;

int ponto2A = 8;
int ponto2B = 7;

int ponto3A = 4;
int ponto3B = 2;

int ponto4A = A0;
int ponto4B = A1;

int ponto5A = A2;
int ponto5B = A3;

int ponto6A = A4;
int ponto6B = A5;

int ON = 1;
int OFF = 0;

int TEMPO_DELAY = 50;

void setup() {
  // put your setup code here, to run once:
  pinMode(ponto1A, OUTPUT);
  pinMode(ponto1B, OUTPUT);
  pinMode(ponto2A, OUTPUT);
  pinMode(ponto2B, OUTPUT);
  pinMode(ponto3A, OUTPUT);
  pinMode(ponto3B, OUTPUT);
  pinMode(ponto4A, OUTPUT);
  pinMode(ponto4B, OUTPUT);
  pinMode(ponto5A, OUTPUT);
  pinMode(ponto5B, OUTPUT);
  pinMode(ponto6A, OUTPUT);
  pinMode(ponto6B, OUTPUT);
  desligar_todos(0);
  
  Serial.begin(9600);
}

void loop() {
  
  while(Serial.available()){
 
    char vlFuncao = Serial.read();
    int vlPonto = Serial.parseInt();
    
    //verifico se a função será de ligar ou desligar
    if(vlFuncao == 'l'){
      //se for pra ativar
      ativarPonto(vlPonto, ON);
      
    } else{
      if(vlFuncao == 'd'){
        //se for pra desativar
        ativarPonto(vlPonto, OFF);
      }
    }
    Serial.write("ok");
  }
    delay(TEMPO_DELAY);
    desligar_todos(0);
}

void ativarPonto(int vpPonto, int vpOperacao){
  switch(vpPonto){
    
    case 0: //EM TODOS os pontos
      digitalWrite(ponto1A, vpOperacao);
      digitalWrite(ponto1B, !vpOperacao);
      digitalWrite(ponto2A, vpOperacao);
      digitalWrite(ponto2B, !vpOperacao);
      digitalWrite(ponto3A, vpOperacao);
      digitalWrite(ponto3B, !vpOperacao);
      digitalWrite(ponto4A, vpOperacao);
      digitalWrite(ponto4B, !vpOperacao);
      digitalWrite(ponto5A, vpOperacao);
      digitalWrite(ponto6B, !vpOperacao);
      digitalWrite(ponto6B, !vpOperacao);
      return;
      
    case 1:
      digitalWrite(ponto1A, vpOperacao);
      digitalWrite(ponto1B, !vpOperacao);
      return;
    case 2:
      digitalWrite(ponto2A, vpOperacao);
      digitalWrite(ponto2B, !vpOperacao);
      return;
    case 3:
      digitalWrite(ponto3A, vpOperacao);
      digitalWrite(ponto3B, !vpOperacao);
      return;
    case 4:
      digitalWrite(ponto4A, vpOperacao);
      digitalWrite(ponto4B, !vpOperacao);
      return;
    case 5:
      digitalWrite(ponto5A, vpOperacao);
      digitalWrite(ponto5B, !vpOperacao);
      return;
    case 6:
      digitalWrite(ponto6A, vpOperacao);
      digitalWrite(ponto6B, !vpOperacao);
      return;
  }
  return;
}

void desligar_todos(int vpPonto){
 switch(vpPonto){
    
    case 0: //EM TODOS os pontos
      digitalWrite(ponto1A, OFF);
      digitalWrite(ponto1B, OFF);
      digitalWrite(ponto2A, OFF);
      digitalWrite(ponto2B, OFF);
      digitalWrite(ponto3A, OFF);
      digitalWrite(ponto3B, OFF);
      digitalWrite(ponto4A, OFF);
      digitalWrite(ponto4B, OFF);
      digitalWrite(ponto5A, OFF);
      digitalWrite(ponto6B, OFF);
      digitalWrite(ponto6B, OFF);
      return;
      
    case 1:
      digitalWrite(ponto1A, OFF);
      digitalWrite(ponto1B, OFF);
      return;
    case 2:
      digitalWrite(ponto2A, OFF);
      digitalWrite(ponto2B, OFF);
      return;
    case 3:
      digitalWrite(ponto3A, OFF);
      digitalWrite(ponto3B, OFF);
      return;
    case 4:
      digitalWrite(ponto4A, OFF);
      digitalWrite(ponto4B, OFF);
      return;
    case 5:
      digitalWrite(ponto5A, OFF);
      digitalWrite(ponto5B, OFF);
      return;
    case 6:
      digitalWrite(ponto6A, OFF);
      digitalWrite(ponto6B, OFF);
      return;
  }
 
}






