/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package celta.reader;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author MendeSantos
 */
public class KindleReader extends Reader {

    public KindleReader(String name){
        super(name);
    }

    @Override
    protected boolean reader(){
        try {
            this.input = new FileInputStream(this.pathFile);
            return true;
        } catch (FileNotFoundException ex) {
            Logger.getLogger(TXTReader.class.getName()).log(Level.SEVERE, null, ex);
            return false;
        }
    }
    
}
