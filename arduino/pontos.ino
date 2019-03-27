int ponto1 = 13;
int ponto2 = 12;
int ponto3 = 8;
int ponto4 = 7;
int ponto5 = 4;
int ponto6 = 2;

int ON = 1;
int OFF = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(ponto1, OUTPUT);
  pinMode(ponto2, OUTPUT);
  pinMode(ponto3, OUTPUT);
  pinMode(ponto4, OUTPUT);
  pinMode(ponto5, OUTPUT);
  pinMode(ponto6, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  
  if(Serial.available()){
    
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
  }

}

void ativarPonto(int vpPonto, int vpOperacao){
  switch(vpPonto){
    
    case 0: //EM TODOS os pontos
      digitalWrite(ponto1, vpOperacao);
      digitalWrite(ponto2, vpOperacao);
      digitalWrite(ponto3, vpOperacao);
      digitalWrite(ponto4, vpOperacao);
      digitalWrite(ponto5, vpOperacao);
      digitalWrite(ponto6, vpOperacao);
      return;
      
    case 1:
      digitalWrite(ponto1, vpOperacao);
      return;
    case 2:
      digitalWrite(ponto2, vpOperacao);
      return;
    case 3:
      digitalWrite(ponto3, vpOperacao);
      return;
    case 4:
      digitalWrite(ponto4, vpOperacao);
      return;
    case 5:
      digitalWrite(ponto5, vpOperacao);
      return;
    case 6:
      digitalWrite(ponto6, vpOperacao);
      return;
  }

  return;
}






