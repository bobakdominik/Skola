/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dama.vynimky;

/**
 *
 * @author Dominik Bobak
 */
public class NeplatneHodnotyException extends Exception {
    
    /**
     * Konstruktor triedy NeplatneHodnotyException.
     * 
     * @param popis popis chyby
     */
    public NeplatneHodnotyException(String popis) {
        super(popis);
    }
}
