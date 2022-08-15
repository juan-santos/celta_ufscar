package celta.reader;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


/**
 *
 * @author MendeSantos
 */
public class PDFReader implements Reader {
    
    public String pathFile;

    @Override
    public boolean openFile(String name) {
        this.pathFile = name;
        return true;
    }
    
    @Override
    public String getText() {
        if(this.reader()){
            return "arquivo pdf";
        }
        
        return null;
    }
    
    private boolean reader() {
        return true;
    }
}
