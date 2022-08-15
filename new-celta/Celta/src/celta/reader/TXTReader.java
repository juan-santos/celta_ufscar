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
public class TXTReader implements Reader {
    
    private String pathFile;
    FileInputStream input;    

    @Override
    public boolean openFile(String name) {
        this.pathFile = name;
        return (new File(this.pathFile)).exists();
    }
    
    @Override
    public String getText() {
        if(this.reader()){
            Scanner s = new Scanner(this.input).useDelimiter("\\A");
            return s.hasNext() ? s.next() : "";
        }

        return ""; 
    }
    
    private boolean reader(){
        try {
            this.input = new FileInputStream(this.pathFile);
            return true;
        } catch (FileNotFoundException ex) {
            Logger.getLogger(TXTReader.class.getName()).log(Level.SEVERE, null, ex);
            return false;
        }
    }
}
