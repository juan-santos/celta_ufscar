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
    protected File file;
    protected FileInputStream input; 
    
    public Reader(String name){
        this.pathFile = name;
        this.file = new File(this.pathFile);
    }
    
    public boolean fileExists() {
        return this.file.exists();
    }
    
    public String getText() throws Exception {
        if(this.reader()){
            String data;
            try (Scanner s = new Scanner(this.input).useDelimiter("\\A")) {
                data = s.hasNext() ? s.next() : "";
                s.close();
            }
            
            return data;
        }

        return ""; 
    }
    
    abstract protected boolean reader() throws Exception;
}
