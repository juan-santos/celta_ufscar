/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package celta;

import celta.reader.Reader;
import javax.swing.JTextArea;

/**
 *
 * @author MendeSantos
 */
public class Arduino implements Runnable {

    private final ControlePorta controlePorta;
    private final JTextArea textArea;
    private int atual = -1;
    private String texto = "";

    /**
     * Construtor da classe Arduino
     *
     * @param textArea Text area com o texto a ser exibido pelo arduino
     */
    public Arduino(JTextArea textArea) {
        this.textArea = textArea;
        this.controlePorta = new ControlePorta(9600);
    }

    /**
     * Método responsável por executar a thread de conexão com o arduíno
     */
    @Override
    public void run() {

        this.clearHardware();
        this.copyValuesClipboard();

        while (!Thread.currentThread().isInterrupted()) {
            this.execCmd(this.controlePorta.lerDados());
        }

        this.clearHardware();
        this.controlePorta.close();
    }

    /**
     * Altero o texto que será lido pelo arduino
     *
     * @param texto
     */
    public void setText(String texto) {
        this.atual = -1;

        this.texto = this.convertTextToBraille(texto);
        this.textArea.setText(this.texto);
    }

    private void atualizaCursor() {
        this.textArea.setSelectionStart(atual);
        this.textArea.setSelectionEnd(atual + 1);
    }

    /**
     * Método responsável por resetar possíveis pinos ativos
     */
    private void clearHardware() {
        this.execCmd("clear");
    }

    /**
     * Método responsável por executar os comandos de acordo com a opção
     * recebida pelo parâmetro
     *
     * @param value comando a ser executado
     */
    private void execCmd(String value) {
        int aux;
        switch (value) {
            case "++1":
                aux = this.proximaPalavra(this.atual);
                
                if(aux != -1){
                    atual = aux;
                    System.out.println("Avançar palavra");
                } else if(atual+1 < this.texto.length()){
                    atual++;
                    System.out.println("Avançar");
                }
                
                this.controlePorta.enviaDados(this.escreveLetra(this.texto.charAt(this.atual)));
                this.atualizaCursor();
                break;
            case "+1":
                if (this.texto.length() == this.atual) {
                    System.out.println("Já estamos na ultima letra: acionar beep");
                    return;
                }

                System.out.println("Avançar");
                this.controlePorta.enviaDados(this.escreveLetra(this.texto.charAt(++this.atual)));
                this.atualizaCursor();

                break;

            case "--1":
                aux = this.palavraAnterior(this.atual);
                
                if(aux != -1){
                    this.atual = aux;
                    System.out.println("Voltar palavra");
                } else if(this.atual > 0){
                    this.atual--; 
                }
                
                this.controlePorta.enviaDados(this.escreveLetra(this.texto.charAt(this.atual)));
                this.atualizaCursor();
                break;
                
            case "-1":
                if (this.atual == 0) {
                    System.out.println("Já estamos na primeira letra: acionar 2x beep");
                    return;
                }

                System.out.println("Voltar");
                this.controlePorta.enviaDados(this.escreveLetra(this.texto.charAt(--this.atual)));
                this.atualizaCursor();
                break;

            case "++0":
                this.copyValuesClipboard();
                break;

            case "clear":
                this.controlePorta.enviaDados(this.escreveLetra(' '));
                break;

        }
    }

    /**
     * Método responsável por traduzir nosso caracter para os pinos em braille
     *
     * @param letra letra no formato ASCII
     * @return retorna string indicando quais pinos devem estar
     * ativados/desativados
     */
    private String escreveLetra(char letra) {
        System.out.println("Letra: "+ letra);
        switch (letra) {
            case ' ':
                return "d1d2d3d4d5d6";
            case 'a':
                return "l1d2d3d4d5d6";
            case 'b':
                return "l1l2d3d4d5d6";
            case 'c':
                return "l1d2d3l4d5d6";
            case 'd':
                return "l1d2d3l4l5d6";
            case 'e':
                return "l1d2d3d4l5d6";
            case 'f':
                return "l1l2d3l4d5d6";
            case 'g':
                return "l1l2d3l4l5d6";
            case 'h':
                return "l1l2d3d4l5d6";
            case 'i':
                return "d1l2d3l4d5d6";
            case 'j':
                return "d1l2d3l4l5d6";
            case 'k':
                return "l1d2l3d4d5d6";
            case 'l':
                return "l1l2l3d4d5d6";
            case 'm':
                return "l1d2l3l4d5d6";
            case 'n':
                return "l1d2l3l4l5d6";
            case 'o':
                return "l1d2l3d4l5d6";
            case 'p':
                return "l1l2l3l4d5d6";
            case 'q':
                return "l1l2l3l4l5d6";
            case 'r':
                return "l1l2l3d4l5d6";
            case 's':
                return "d1l2l3l4d5d6";
            case 't':
                return "d1l2l3l4l5d6";
            case 'u':
                return "l1d2l3d4d5l6";
            case 'v':
                return "l1l2l3d4d5l6";
            case 'w':
                return "d1l2d3l4l5l6";
            case 'x':
                return "l1d2l3l4d5l6";
            case 'y':
                return "l1d2l3l4l5l6";
            case 'z':
                return "l1d2l3d4l5l6";
            case '\u02E9':
                return "d1d2l3l4l5l6";
            case '\u035D':
                return "d1d2d3l4d5l6";
            case '\u00E1':
                return "l1l2l3d4l5l6";
            case '\u00E0':
                return "l1l2d3l4d5l6";
            case '\u00E2':
                return "l1d2d3d4d5l6";
            case '\u00e3':
                return "d1d2l3l4l5d6";
            case '\u00e7':
                return "l1l2l3l4d5l6";
            case '\u00E9':
                return "l1l2l3l4l5l6";
            case '\u00EA':
                return "l1l2d3d4d5l6";
            case '\u00ED':
                return "d1d2l3l4d5d6";
            case '\u00F3':
                return "d1d2l3l4d5l6";
            case '\u00F4':
                return "l1d2d3l4l5l6";
            case '\u00F5':
                return "d1l2d3l4d5l6";
            case '\u00FA':
                return "d1l2l3l4l5l6";
            case '\u00FC':
                return "l1l2d3d4l5l6";
            case '(':
                return "l1l2d3d4d5l6";
            case ')':
                return "d1d2l3l4l5d6";
            case '[':
                return "l1l2l3d4l5l6";
            case ']':
                return "d1l2l3l4l5l6";
            case ',':
                return "d1l2d3d4d5d6";
            case ';':
                return "d1l2l3d4d5d6";
            case ':':
                return "d1l2d3d4l5d6";
            case '.':
                return "d1d2l3d4d5d6";
            case '`':
                return "d1d2l3d4d5d6";
            case '?':
                return "d1l2d3d4d5l6";
            case '!':
                return "d1l2l3d4l5d6";
            case '-':
                return "d1d2l3d4d5l6";
            case '+':
                return "d1l2l3d4l5d6";
        }

        return "d0";
    }

    /**
     * Método responsável por obter o texto a ser lido pelo arduino. Se for o
     * caminho de um arquivo ele irá abrir o conteúdo do arquivo.
     */
    private void copyValuesClipboard() {
        String data = Utils.copyClipboard();
        System.out.println("Copiado da área de transferência: " + data);

        if (Utils.identifyWhenIsFile(data)) {
            System.out.println("Abrindo arquivo: " + data);
            Reader text = Utils.typeOfFile(data);

            if (text != null && text.fileExists()) {
                data = text.getText();
            }

            System.out.println("Texto Colado: " + data);
        }

        this.setText(data);
    }

    private String convertTextToBraille(String texto) {
        StringBuilder aux = new StringBuilder();

        for (int i = 0; i < texto.length(); i++) {

            //caracteres numéricos
            if (texto.charAt(i) >= 48 && texto.charAt(i) <= 57) {
                aux.append('\u02E9');
                aux.append(texto.charAt(i));
                continue;
            } else {

                //caracteres maiusculos
                if (texto.charAt(i) >= 65 && texto.charAt(i) <= 90) {

                    aux.append('\u035D');
                    aux.append(Character.toLowerCase(texto.charAt(i)));
                    continue;
                }
            }

            aux.append(texto.charAt(i));
        }

        return aux.toString();
    }
    
    private int proximaPalavra(int start){
        int atual = start;

        while((atual = this.texto.indexOf(" ", atual)) != -1){

            if(atual+1 < this.texto.length() && this.texto.charAt(atual+1) != ' '){
                return atual+1;
            }
            atual++;
        }

        return -1;
    }

    private int palavraAnterior(int end){
        int atual = 0, anterior = 0;

        String aux = this.texto.substring(0, end < 1 ? 0 : end - 1);
        while((atual = aux.indexOf(" ", atual)) != -1){

            if(atual+1 < this.texto.length() && this.texto.charAt(atual+1) != ' '){
                anterior = atual+1;
            }
            atual++;
        }

        return anterior;
    }

}
