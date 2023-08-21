package celta.reader;

import java.io.FileInputStream;

import org.apache.tika.metadata.Metadata;
import org.apache.tika.parser.ParseContext;
import org.apache.tika.parser.pdf.PDFParser;
import org.apache.tika.sax.BodyContentHandler;



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
    public String getText() throws Exception {
        if(this.reader()){
            return ch.toString();
        }

        return ""; 
    }
    
    @Override
    protected boolean reader() throws Exception {
        this.input = new FileInputStream(this.file);
        this.ch = new BodyContentHandler();

        Metadata md = new Metadata();
        ParseContext pc = new ParseContext();
        PDFParser pp = new PDFParser();

        pp.parse(this.input, ch, md, pc);
        return true;
    }
}
