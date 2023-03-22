/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dama.enumy;

/**
 * Enum TypHraca obsahuje mozne typy hraca (Horny alebo Dolny).
 * 
 * @author Dominik Bobak
 */
public enum TypHraca {
    HORNY("Horny"), DOLNY("Dolny");
    
    private String typ;
    
    /**
     * Konstruktor triedy TypHraca
     * 
     * @param typ typ hraca
     */
    TypHraca(String typ) {
        this.typ = typ;
    }
    
    /**
     * Vrati typ hraca.
     * 
     * @return typ
     */
    public String toString() {
        return this.typ;
    }
}
