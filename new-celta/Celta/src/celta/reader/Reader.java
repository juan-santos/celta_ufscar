/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package celta.reader;

/**
 *
 * @author MendeSantos
 */
public interface Reader {
    public boolean openFile(String name);
    public String getText();
}
