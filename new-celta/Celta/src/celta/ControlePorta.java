/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package celta;

import gnu.io.CommPortIdentifier;
import gnu.io.NoSuchPortException;
import gnu.io.SerialPort;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.charset.Charset;
import java.util.Scanner;
import javax.swing.JOptionPane;

/**
 *
 * @author MendeSantos
 */
public class ControlePorta {

    private OutputStream serialOut;
    private InputStream serialIn;
    private final int taxa;

    /**
     * Construtor da classe de Controle da porta
     * @param taxa taxa de transferencia dos dados
     */
    public ControlePorta(int taxa) {
        this.taxa = taxa;
        this.initialize();
    }
    
    /**
     * Método responsável por percorrer todas as portas serial do equipamento.
     * @return Retorna a porta na qual o arduino está conectado.
     */
    private CommPortIdentifier connectPort(){
        
        String port;
        String os = System.getProperty("os.name");
        
        //Define uma variável portId do tipo CommPortIdentifier para realizar a comunicação serial
        CommPortIdentifier portId = null;
        
        if(os.toLowerCase().contains("windows")){
            port = "COM";
        } else {
            port = "/dev/ttyUSB";
        }
        
        for(int i = 1; i <= 10; i++){
            try {
                //Tenta verificar se a porta COM informada existe
                portId = CommPortIdentifier.getPortIdentifier(port+i);
                System.out.println("Porta: "+ port+i);
                return portId;
            } 
            catch (NoSuchPortException npe) {
            }
        }
        
        return null;
    }

    /**
     * Método que verifica se a comunicação com a porta serial está ok.
     */
    private void initialize() {
        try {
            CommPortIdentifier portId = this.connectPort();
            
            if(portId == null){
                JOptionPane.showMessageDialog(null, "Porta COM não encontrada.",
                    "Porta COM", JOptionPane.PLAIN_MESSAGE);
                return;
            }
            
            //Abre a porta COM 
            SerialPort port = (SerialPort) portId.open("Comunicação serial", this.taxa);
            serialOut = port.getOutputStream();
            serialIn = port.getInputStream();
            
            port.setSerialPortParams(this.taxa, //taxa de transferência da porta serial 
                    SerialPort.DATABITS_8, //taxa de 10 bits 8 (envio)
                    SerialPort.STOPBITS_1, //taxa de 10 bits 1 (recebimento)
                    SerialPort.PARITY_NONE); //receber e enviar dados
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * Método que fecha a comunicação com a porta serial
     */
    public void close() {
        try {
            serialOut.close();
        } catch (IOException e) {
            JOptionPane.showMessageDialog(null, "Não foi possível fechar porta COM.",
                    "Fechar porta COM", JOptionPane.PLAIN_MESSAGE);
        }
    }

    /**
     * Método que realiza o envio de dados via comunicação serial
     * @param opcao - Valor a ser enviado pela porta serial
     */
    public void enviaDados(String opcao) {
        try {
            serialOut.write(opcao.getBytes(Charset.forName("UTF-8")));//escreve o valor na porta serial para ser enviado
        } catch (IOException ex) {
            JOptionPane.showMessageDialog(null, "Não foi possível enviar o dado. ",
                    "Enviar dados", JOptionPane.PLAIN_MESSAGE);
        }
    }
    
    /**
     * Método que obtem dados recebidos via serial
     * @return string recebido via comunicação serial
     */
    public String lerDados() {
        Scanner s = new Scanner(this.serialIn).useDelimiter("\\A");
        return s.hasNext() ? s.next() : "";
    }
}
