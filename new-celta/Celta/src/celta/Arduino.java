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
        this.texto = texto;
        this.textArea.setText(texto);
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

        switch (value) {
            case "++1":
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
}
