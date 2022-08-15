/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package celta.reader;

import java.io.File;
import java.io.FileInputStream;
import java.util.Scanner;

/**
 *
 * @author MendeSantos
 */
public abstract class Reader {
    protected String pathFile;
    protected FileInputStream input;
    
    public Reader(String name){
        this.pathFile = name;
    }
    
    public boolean fileExists() {
        return (new File(this.pathFile)).exists();
    }
    
    public String getText() {
        if(this.reader()){
            String data;
            try (Scanner s = new Scanner(this.input).useDelimiter("\\A")) {
                data = s.hasNext() ? s.next() : "";
            }
            
            return data;
        }

        return ""; 
    }
    
    abstract boolean reader();
}
