# Celta - Célula Tátil UFSCar

Em parceria com a Capes, o projeto visa transformar informações que estão no formato texto em braille.
Para tal feito, o projeto utilizará:

### Materiais utilizados no protótipo

 - 1 Arduíno;
 - 6 Leds;
 - 6 resistores de 1k Ohms;
 - 1 protoboard;
 
## Braille
 
O Braille é um sistema de escrita tátil utilizado por pessoas cegas ou com baixa visão. É tradicionalmente escrito em papel em relevo. Uma célula Braille completa inclui seis pontos levantados dispostos em duas linhas laterais, cada uma com três pontos. As posições dos pontos são identificadas por números de um a seis. São 64 soluções possíveis para usar um ou mais pontos.
Uma única célula pode ser usada para representar uma letra do alfabeto, um número, um sinal de pontuação ou mesmo uma palavra inteira.


### Aparência

**o**     **o**

**o**     **o**

**o**     **o**


### Organização (coluna 1 | coluna 2)

**ponto 1:** o | **ponto 4:** o

**ponto 2:** o | **ponto 5:** o

**ponto 3:** o | **ponto 6:** o

<hr>

## Célula Tátil

Para que seja possível exibir as representações do braille em nosso equipamento utilizaremos 6 pinos (organizados de forma semelhante ao do braille). Cada um dos pontos será configurado para que possa ser ativado/desativado de maneira independente.

Como o hardware está sendo elaborado em paralelo ao software, cada um dos seis pontos está sendo representado por um LED em série com um resistor. O resistor será adicionado para que limitar a corrente do circuíto e evitar que o LED queime.

O circuíto adotado permitiu o início do desenvolvimento do software, sem que tenhamos o hardware pronto.

### Funcionamento

Cada um dos seis pontos possuirá dois estados:

- Quando o ponto estiver ativado o LED deverá estar aceso;
- Quando o ponto estiver desativado o LED deverá estar apagado; 

<hr>

## Arduíno

 O arduíno é uma plataforma de prototipagem eletrônica de baixo custo. Este equipamento estará diretamente ligado à nossa célula tátil, ativando ou desativando cada um dos pontos da Celta.
 O programa desenvolvido na linguagem C está disponível na pasta "arduíno". 
 
 Basicamente, o programa irá ficar num loop para verificar se existe algum comando a ser executado. Todos os comandos serão recebidos via comunicação serial. O formato esperado de cada comando, respectivamente, será: 
 
Função
 - ligar (l) / desligar (d);
 
 Porta
 - 0 (todas as portas);
 - 1 (somente a porta 1);
 - 2 (somente a porta 2);
 - 3 (somente a porta 3);
 - 4 (somente a porta 4);
 - 5 (somente a porta 5);
 - 6 (somente a porta 6);
 
### Exemplificando:
- se o comando recebido for d3, o arduíno irá desligar o ponto 3;
- se for o comando l4 irá ligar apenas o ponto 4;
- se receber d0 irá desativar todos os 6 pontos;

<hr>

 ## Interface gráfica (GUI)
 
 Através do framework QT Creator, o projeto irá contar com uma interface gráfica na linguagem C++. Esta interface amigável exibirá o conteúdo do bloco texto, letra a letra, em braille no dispositivo Celta.
 
 O programa irá percorrer cada letra do conteúdo, verificar quais pontos devem estar ativados ou desativados para que a respectiva letra esteja no formato braille adequado e enviará ao arduíno para tal representação.
 
 
 
 
