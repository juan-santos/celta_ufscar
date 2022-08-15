/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package celta;

import java.awt.Toolkit;
import java.awt.datatransfer.DataFlavor;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author MendeSantos
 */
public class Utils {
    
    /**
     * Método responsável por copiar dados da área de transferência
     * @return Retorna uma string com os dados da área de transferência
     */
    public static String copyClipboard(){
        try {
            return (String) Toolkit.getDefaultToolkit().getSystemClipboard().getData(DataFlavor.stringFlavor); 
            
        } catch (Exception ex) {
            Logger.getLogger(Utils.class.getName()).log(Level.SEVERE, null, ex);
        }
        return "";
    }
    
    public static boolean identifyWhenIsFile(String clipboard){
        return clipboard.matches("[a-zA-Z]:[\\\\\\/](?:[a-zA-Z0-9]+[\\\\\\/])*([a-zA-Z0-9]+\\.[A-Za-z]{3}$)");
    }
}
