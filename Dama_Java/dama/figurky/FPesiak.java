/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dama.figurky;

import dama.enumy.FarbaFigurky;
import dama.enumy.TypFigurky;
import dama.vynimky.NeplatneHodnotyException;

/**
 * Tieda FPesiak vytvara novy objekt na platne s ktorym je mozne pohybovat.
 * Dedi vlastnosti triedy Figurka a vyuziva interface IFigurka.
 *
 * @author Dominik Bobak
 */
public class FPesiak extends Figurka implements IFigurka {
    private final TypFigurky typFigurky;
    
    /**
     * Konstruktor triedy FPesiak.
     * 
     * @param riadok riadok na ktorom sa ma figurka objavit
     * @param stlpec stlpec na ktorom sa ma figurka objavit
     * @param farba farba figurky
     */
    public FPesiak(int riadok, int stlpec, FarbaFigurky farba) {
        super(riadok, stlpec, farba);
        this.typFigurky = TypFigurky.PESIAK;
    }
    
    /**
     * Vrati typ figurky.
     * 
     * @return typ figurky
     */
    public TypFigurky getTypFigurky () {
        return this.typFigurky;
    }
    
    /**
     * Pohne figurkou na zvolene miesto.
     * 
     * @param riadok riadok na ktory sa ma pohnut
     * @param stlpec stlpec na ktory sa ma pohnut
     * @throws NeplatneHodnotyException Exception ak sa figurka nemoze pohnut na zvolene miesto
     */
    public void skusSaPohnut(int riadok, int stlpec) throws NeplatneHodnotyException {
        if (super.getFarbuFigurky().equals(FarbaFigurky.DOLNA)) {
            if (super.getPoloha()[0] - riadok != 1 && super.getPoloha()[0] - riadok != 2) {
                throw new NeplatneHodnotyException("Figurka sa moze posunut iba o jedno policko smerom nahor!");
            }
        } else {
            if (riadok - super.getPoloha()[0] != 1 && riadok - super.getPoloha()[0] != 2) {
                throw new NeplatneHodnotyException("Figurka sa moze posunut iba o jedno policko smerom nadol!");
            }
        }
        if (Math.abs(riadok - super.getPoloha()[0]) != Math.abs(stlpec - super.getPoloha()[1])) {
            throw new NeplatneHodnotyException("Neplatne vybrate policko!");
        }
        try {
            super.pohniSa(riadok, stlpec);
        } catch (NeplatneHodnotyException ex) {
            throw ex;
        }
    }
    
    /**
     * Vymaze figurku z hracej plochy.
     */
    public void vymazSa() {
        super.skry();
    }
}
