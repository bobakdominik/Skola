/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dama.enumy;

/**
 * Enum TypFigurky obsahuje povolene typy figurok (Pesiak alebo Dama).
 * 
 * @author Dominik Bobak
 */
public enum TypFigurky {
    PESIAK("Pesiak"), DAMA("Dama");
    
    private String typ;
    
    /**
     * Konstrutor triedy TypFigurky
     * 
     * @param typ typ figurky
     */
    TypFigurky(String typ) {
        this.typ = typ;
    }
    
    /**
     * Vrati typ figurky.
     * 
     * @return typ
     */
    public String toString() {
        return this.typ;
    }
}
