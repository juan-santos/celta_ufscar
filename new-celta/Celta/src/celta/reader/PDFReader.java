package celta.reader;

import java.io.FileInputStream;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.apache.tika.exception.TikaException;
import org.apache.tika.metadata.Metadata;  
import org.apache.tika.sax.BodyContentHandler;  
import org.apache.tika.parser.pdf.PDFParser;  
import org.apache.tika.parser.ParseContext;  
import org.xml.sax.SAXException;


/**
 *
 * @author MendeSantos
 */
public class PDFReader extends Reader {
    
    private BodyContentHandler ch;
    
    public PDFReader(String name){
        super(name);
    }
    
    @Override
    public String getText() {
        if(this.reader()){
            return ch.toString();
        }

        return ""; 
    }
    
    @Override
    protected boolean reader(){
          
        try {
            this.input = new FileInputStream(this.file);
            this.ch = new BodyContentHandler();
            
            Metadata md = new Metadata();
            ParseContext pc = new ParseContext();
            PDFParser pp = new PDFParser();
            
            pp.parse(this.input, ch, md, pc);
            return true;
        } catch (IOException | SAXException | TikaException ex) {
            Logger.getLogger(PDFReader.class.getName()).log(Level.SEVERE, null, ex);
            return false;
        }
    }
}
