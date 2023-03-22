/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dama.figurky;

import dama.enumy.FarbaFigurky;
import dama.enumy.TypFigurky;
import dama.skolskeTriedy.Stvorec;
import dama.vynimky.NeplatneHodnotyException;

/**
 * Tieda FDama vytvara novy objekt na platne s ktorym je mozne pohybovat.
 * Dedi vlastnosti triedy Figurka a vyuziva interface IFigurka.
 * 
 * @author Dominik Bobak
 */
public class FDama extends Figurka implements IFigurka {
    private final TypFigurky typFigurky;
    private Stvorec koruna;
    
    /**
     * Konstruktor triedy FDama.
     * 
     * @param riadok riadok na ktorom sa ma figurka objavit
     * @param stlpec stlpec na ktorom sa ma figurka objavit
     * @param farba farba figurky
     */
    public FDama(int riadok, int stlpec, FarbaFigurky farba) {
        super(riadok, stlpec, farba);
        this.typFigurky = TypFigurky.DAMA;
        int yKoruny = ((stlpec - 1) * 40) + 10;
        int xKoruny = ((riadok - 1) * 40) + 10;
        this.koruna = new Stvorec(yKoruny, xKoruny, 21, "yellow");
        this.koruna.zobraz();
    }
    
    /**
     * Vrati typ figurky.
     * 
     * @return typ figury
     */
    public TypFigurky getTypFigurky () {
        return this.typFigurky;
    }
    
    /**
     * Zmeni farbu figurky.
     */
    public void prefarbi() {
        super.prefarbi();
        this.koruna.zobraz();
    }
    
    /**
     * Pohne figurkou na zvolene miesto.
     * 
     * @param riadok riadok na ktory sa ma pohnut
     * @param stlpec stlpec na ktory sa ma pohnut
     * @throws NeplatneHodnotyException Exception ak sa figurka nemoze pohnut na zvolene miesto
     */
    public void skusSaPohnut(int riadok, int stlpec) throws NeplatneHodnotyException {
        if (Math.abs(riadok - super.getPoloha()[0]) != Math.abs(stlpec - super.getPoloha()[1])) {
            throw new NeplatneHodnotyException("Neplatne vybrate policko!");
        }
        int xPosun = (stlpec - super.getPoloha()[1]) * 40;
        int yPosun = (riadok - super.getPoloha()[0]) * 40;
        try {
            this.koruna.skry();
            super.pohniSa(riadok, stlpec);
            this.koruna.posunVodorovne(xPosun);
            this.koruna.posunZvisle(yPosun);
        } catch (NeplatneHodnotyException ex) {
            throw ex;
        } finally {
            this.koruna.zobraz();
        }
    }
    
    /**
     * Vymaze figurku z hracej plochy.
     */
    public void vymazSa() {
        this.koruna.skry();
        this.koruna = null;
        super.skry();
    }
}
