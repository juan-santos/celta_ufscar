/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package celta;

import celta.reader.Reader;
import javax.swing.JTextArea;
import javax.swing.JButton;
import javax.swing.JPanel;

/**
 *
 * @author MendeSantos
 */
public class Raspberry implements Runnable {

    private final Comunicacao controlePorta;
    private final JTextArea textArea;
    JPanel pnlButton;
    
    private int atual = -1;
    private String texto = "";

    /**
     * Construtor da classe Raspberry
     *
     * @param textArea Text area com o texto a ser exibido pelo arduino
     * @param btnReconectar Botão responsável por tentar reconectar o socket
     * @param pnlButton Painel que contém o botão
     */
    public Raspberry(JTextArea textArea, JButton btnReconectar, JPanel pnlButton) {
        this.textArea = textArea;
        this.pnlButton = pnlButton;
        this.controlePorta = new Comunicacao(btnReconectar);
    }

    /**
     * Método responsável por executar a thread de conexão com o arduíno
     */
    @Override
    public void run() {

        this.clearHardware();
        this.copyValuesClipboard();

        while (!Thread.currentThread().isInterrupted()) {
            String dado = this.controlePorta.lerDados();
            
            if(dado != null){
                this.execCmd(dado);
            } else {
                this.pnlButton.revalidate();
                this.pnlButton.repaint();
                Thread.currentThread().interrupt();
            }
            
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
        this.controlePorta.enviaDados("000000");
    }

    /**
     * Método responsável por emitir som no hardware
     */
    private void acionarBeep() {
        this.controlePorta.enviaDados("l7");
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

                if (aux != -1) {
                    atual = aux;
                    System.out.println("Avançar palavra");
                } else if (atual + 1 < this.texto.length()) {
                    atual++;
                    System.out.println("Avançar");
                }

                this.controlePorta.enviaDados(this.escreveLetra(this.texto.charAt(this.atual)));
                this.atualizaCursor();
                break;
            case "+1":
                if (this.texto.length() == this.atual + 1) {
                    this.acionarBeep();
                    System.out.println("Já estamos na ultima letra");
                    return;
                }

                System.out.println("Avançar");
                this.controlePorta.enviaDados(this.escreveLetra(this.texto.charAt(++this.atual)));
                this.atualizaCursor();

                break;

            case "--1":
                aux = this.palavraAnterior(this.atual);

                if (aux != -1) {
                    this.atual = aux;
                    System.out.println("Voltar palavra");
                } else if (this.atual > 0) {
                    this.atual--;
                }

                this.controlePorta.enviaDados(this.escreveLetra(this.texto.charAt(this.atual)));
                this.atualizaCursor();
                break;

            case "-1":
                
                if(this.atual < 0){
                    this.acionarBeep();
                    System.out.println("Leitura não iniciada");
                    return;
                }
                
                if (this.atual == 0) {
                    this.acionarBeep();
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
            default:
                System.out.println(value);
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
        System.out.println("Letra: " + letra);
        switch (letra) {
            case ' ':
                return "000000";
            case '1':
            case 'a':
                return "100000";
            case '2':
            case 'b':
                return "110000";
            case '3':
            case 'c':
                return "100100";
            case '4':
            case 'd':
                return "100110";
            case '5':
            case 'e':
                return "100010";
            case '6':
            case 'f':
                return "110100";
            case '7':
            case 'g':
                return "110110";
            case '8':
            case 'h':
                return "110010";
            case '9':
            case 'i':
                return "010100";
            case '0':
            case 'j':
                return "010110";
            case 'k':
                return "101000";
            case 'l':
                return "111000";
            case 'm':
                return "101100";
            case 'n':
                return "101110";
            case 'o':
                return "101010";
            case 'p':
                return "111100";
            case 'q':
                return "111110";
            case 'r':
                return "111010";
            case 's':
                return "011100";
            case 't':
                return "011110";
            case 'u':
                return "101001";
            case 'v':
                return "111001";
            case 'w':
                return "010111";
            case 'x':
                return "101101";
            case 'y':
                return "101111";
            case 'z':
                return "101011";
            case '\u02E9':
                return "001111";
            case '\u035D':
                return "000101";
            case '\u00E1':
                return "111011";
            case '\u00E0':
                return "110101";
            case '\u00E2':
                return "100001";
            case '\u00e3':
                return "001110";
            case '\u00e7':
                return "111101";
            case '\u00E9':
                return "111111";
            case '\u00EA':
                return "110001";
            case '\u00ED':
                return "001100";
            case '\u00F3':
                return "001101";
            case '\u00F4':
                return "100111";
            case '\u00F5':
                return "010101";
            case '\u00FA':
                return "011111";
            case '\u00FC':
                return "110011";
            case '(':
                return "110001";
            case ')':
                return "001110";
            case '[':
                return "111011";
            case ']':
                return "011111";
            case ',':
                return "010000";
            case ';':
                return "011000";
            case ':':
                return "010010";
            case '.':
                return "001000";
            case '`':
                return "001000";
            case '?':
                return "010001";
            case '!':
                return "011010";
            case '-':
                return "001001";
            case '+':
                return "011010";
            default:
                return "";
        }
    }

    /**
     * Método responsável por obter o texto a ser lido pelo arduino. Se for o
     * caminho de um arquivo ele irá abrir o conteúdo do arquivo.
     */
    private void copyValuesClipboard() {
        try {
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
        } catch (Exception ex) {

            for (int i = 0; i < 3; i++) {
                this.acionarBeep();
            }
        }
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

    private int proximaPalavra(int start) {
        int atual = start;

        while ((atual = this.texto.indexOf(" ", atual)) != -1) {

            if (atual + 1 < this.texto.length() && this.texto.charAt(atual + 1) != ' ') {
                return atual + 1;
            }
            atual++;
        }

        return -1;
    }

    private int palavraAnterior(int end) {
        int atual = 0, anterior = 0;

        String aux = this.texto.substring(0, end < 1 ? 0 : end - 1);
        while ((atual = aux.indexOf(" ", atual)) != -1) {

            if (atual + 1 < this.texto.length() && this.texto.charAt(atual + 1) != ' ') {
                anterior = atual + 1;
            }
            atual++;
        }

        return anterior;
    }

}
