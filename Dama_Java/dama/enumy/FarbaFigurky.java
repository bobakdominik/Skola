/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dama.enumy;

/**
 * Enum FarbaFigurky obsahuje povolene farby figurok.
 * 
 * @author Dominik Bobak
 */
public enum FarbaFigurky {
     HORNA("blue"), DOLNA("green"), OZNACENA("yellow");
     
    private String farba;
    
    /**
     * Konstruktor tiedy FarbaFigurky.
     * 
     * @param farba povolena farba
     */
    FarbaFigurky(String farba) {
        this.farba = farba;
    }
     
    /**
     * Vrati farbu.
     * 
     * @return farba
     */
    public String toString() {
        return this.farba;
    }
}
