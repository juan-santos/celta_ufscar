/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package celta.reader;

import java.io.FileInputStream;
import java.io.FileNotFoundException;

/**
 *
 * @author MendeSantos
 */
public class TXTReader extends Reader {
    
    public TXTReader(String name){
        super(name);
    }
    
    @Override
    protected boolean reader() throws FileNotFoundException{
        this.input = new FileInputStream(this.file);
        return true;
    }
}
