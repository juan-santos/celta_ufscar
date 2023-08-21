/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package celta;

import celta.reader.PDFReader;
import celta.reader.Reader;
import celta.reader.TXTReader;
import java.awt.Toolkit;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.io.IOException;

/**
 *
 * @author MendeSantos
 */
public class Utils {
    
    /**
     * Método responsável por copiar dados da área de transferência
     * @return Retorna uma string com os dados da área de transferência
     */
    public static String copyClipboard() throws UnsupportedFlavorException, IOException{
        return (String) Toolkit.getDefaultToolkit().getSystemClipboard().getData(DataFlavor.stringFlavor); 
    }
    
    public static boolean identifyWhenIsFile(String clipboard){
        return clipboard.matches("[a-zA-Z]:[\\\\\\/](?:[a-zA-Z0-9]+[\\\\\\/])*([a-zA-Z0-9]+\\.[A-Za-z]{3}$)") || clipboard.matches("^(.*)\\/([^\\/]*)$");
    }
    
    public static Reader typeOfFile(String pathFile) {
        if(pathFile.isEmpty()){
            return null;
        }
        
        String format = pathFile.substring(pathFile.length() - 3, pathFile.length());
        
        switch(format){
            case "txt":
                return new TXTReader(pathFile);
            case "pdf":
                return new PDFReader(pathFile);
            default:
                return null;
        }
        
    }
}
