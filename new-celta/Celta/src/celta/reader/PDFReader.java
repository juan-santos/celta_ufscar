package celta.reader;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.logging.Level;
import java.util.logging.Logger;


/**
 *
 * @author MendeSantos
 */
public class PDFReader extends Reader {
    
    public PDFReader(String name){
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
