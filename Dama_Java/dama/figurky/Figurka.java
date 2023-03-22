/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dama.figurky;

import dama.enumy.FarbaFigurky;
import dama.enumy.TypFigurky;
import dama.skolskeTriedy.Kruh;
import dama.vynimky.NeplatneHodnotyException;

/**
 * Vytvori novy objekt na hracej ploche.
 * Dedi vlastnosti z triedy Kruh.
 * 
 * @author Dominik Bobak
 */
public abstract class Figurka extends Kruh {
    private int[] poloha;
    private final FarbaFigurky farba;
    
    /**
     * Konstruktor triedy Figurka.
     * 
     * @param riadok riadok na ktorom sa ma figurka objavit
     * @param stlpec stlpec na ktorom sa ma figurka objavit
     * @param farba farba figurky
     */
    public Figurka (int riadok, int stlpec, FarbaFigurky farba) {
        super ((stlpec - 1) * 40, (riadok - 1) * 40, farba.toString());
        this.poloha = new int[]{riadok, stlpec};
        this.farba = farba;
        super.zobraz();
    }
    
    /**
     * Vrati polohu figurky.
     * 
     * @return poloha
     */
    public int[] getPoloha() {
        return this.poloha;
    }
    
    /**
     * Vrati farbu figurky.
     * 
     * @return farba
     */
    public FarbaFigurky getFarbuFigurky () {
        return this.farba;
    }
    
    /**
     * Vrati typ figurky.
     * 
     * @return typ figurky
     */
    public abstract TypFigurky getTypFigurky();
    
    /**
     * Pohne figurkou na zvolene miesto.
     * 
     * @param riadok riadok na ktory sa ma pohnut
     * @param stlpec stlpec na ktory sa ma pohnut
     * @throws NeplatneHodnotyException Exception ak sa figurka nemoze pohnut na zvolene miesto
     */
    public abstract void skusSaPohnut(int riadok, int stlpec) throws NeplatneHodnotyException;
    
    /**
     * Vymaze figurku z hracej plochy.
     */
    public abstract void vymazSa();
    
    /**
     * Pohne figurkou na zvolene miesto.
     * 
     * @param riadok riadok na kory sa ma pohnut
     * @param stlpec stlpec na ktory sa ma pohnut
     * @throws NeplatneHodnotyException Exception ak sa figurka nemoze pohnut na dane miesto
     */
    public void pohniSa (int riadok, int stlpec) throws NeplatneHodnotyException {
        if (riadok > 8 || riadok < 1 || stlpec > 8 || stlpec < 1) {
            throw new NeplatneHodnotyException("Oznacene miesto je mimo dosky!");
        }
        if (riadok == this.poloha[0] && stlpec == this.poloha[1]) {
            throw new NeplatneHodnotyException("Figurka sa nemoze pohnut na to iste miesto!");
        }
        super.posunZvisle((riadok - this.poloha[0]) * 40);
        super.posunVodorovne((stlpec - this.poloha[1]) * 40);
        this.poloha = new int[] {riadok, stlpec};
    }
    
    /**
     * Zmeni farbu figurky
     */
    public void prefarbi() {
        if (super.getFarba().equals(this.farba.toString())) {
            super.zmenFarbu(FarbaFigurky.OZNACENA.toString());
        } else {
            super.zmenFarbu(this.farba.toString());
        }
    }
}
