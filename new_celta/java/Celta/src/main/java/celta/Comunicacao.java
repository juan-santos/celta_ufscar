/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package celta;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.net.Socket;
import javax.swing.JButton;
import javax.swing.JOptionPane;

/**
 *
 * @author MendeSantos
 */
public class Comunicacao {

    private OutputStream serialOut;
    private InputStream serialIn;
    private final JButton btnReconectar;
    Socket socket;

    InputStreamReader inputStreamReader;
    BufferedReader bufferedReader;

    /**
     * Construtor da classe Comunicação
     *
     * @param btnReconectar Botão responsável por ativar o comando de reconectar
     */
    public Comunicacao(JButton btnReconectar) {
        this.btnReconectar = btnReconectar;
        //this.initialize();
    }

    /**
     * Método que verifica se a comunicação com o hardware está funcionando
     */
    private void initialize() {
        try {
            this.socket = new Socket("192.168.15.30", 50000);
            this.serialOut = socket.getOutputStream();
            this.serialIn = socket.getInputStream();

            this.inputStreamReader = new InputStreamReader(this.serialIn);
            this.bufferedReader = new BufferedReader(this.inputStreamReader);

        } catch (IOException e) {
            this.btnReconectar.setVisible(true);
            this.btnReconectar.setEnabled(true);
            
            JOptionPane.showMessageDialog(null, "Não foi possível conectar ao Hardware. ",
                        "Problema de conexão com o Celta", JOptionPane.PLAIN_MESSAGE);
            e.printStackTrace();
        }
    }

    /**
     * Método que encerra a comunicação
     */
    public void close() {
        try {

            if (this.serialOut != null) {
                this.serialOut.close();
            }

            if (this.serialIn != null) {
                this.serialIn.close();
            }

            if (this.socket != null) {
                this.socket.close();
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Método que realiza o envio de dados via socket
     *
     * @param opcao - Valor a ser enviado pela porta serial
     */
    public void enviaDados(String opcao) {

        if (this.serialOut != null) {
            try {
                if (this.serialOut != null) {
                    this.serialOut.write(opcao.getBytes());
                    return;
                }

            } catch (IOException ex) {
                ex.printStackTrace();
                JOptionPane.showMessageDialog(null, "Não foi possível enviar o dado. ",
                        "Enviar dados", JOptionPane.PLAIN_MESSAGE);
            }
        }    
    }

    /**
     * Método que obtem dados recebidos via socket
     *
     * @return string recebido via comunicação socket
     */
    public String lerDados() {

        if (this.bufferedReader != null) {

            try {
                String mensagemDoServidor;

                while ((mensagemDoServidor = bufferedReader.readLine()) != null) {
                    System.out.println("Mensagem recebida: " + mensagemDoServidor);
                    return mensagemDoServidor;
                }

            } catch (IOException ex) {
                ex.printStackTrace();
            }
        }

        return null;
    }
}
