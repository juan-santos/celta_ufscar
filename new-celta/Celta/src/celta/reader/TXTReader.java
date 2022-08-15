/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package celta.reader;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author MendeSantos
 */
public class TXTReader extends Reader {
    
    public TXTReader(String name){
        super(name);
    }
    
    @Override
    boolean reader(){
        try {
            this.input = new FileInputStream(this.pathFile);
            return true;
        } catch (FileNotFoundException ex) {
            Logger.getLogger(TXTReader.class.getName()).log(Level.SEVERE, null, ex);
            return false;
        }
    }
}
