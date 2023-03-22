/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dama;

import dama.enumy.FarbaFigurky;
import dama.enumy.TypHraca;
import dama.figurky.FDama;
import dama.figurky.FPesiak;
import dama.vynimky.NeplatneHodnotyException;
import java.util.ArrayList;
import java.util.Arrays;
import dama.figurky.IFigurka;


/**
 * Trieda hrac riadi pohyb figurok jedneho hraca.
 * Hrac obsahuje meno hraca, jeho typ a 8 figurok.
 * 
 * @author Dominik Bobak
 */
public class Hrac {
    private ArrayList<IFigurka> figurky;
    private final TypHraca typ;
    private String meno;
    
    /**
    * Konstruktor triedy Hrac.
    * 
    * @param meno   hracovo meno.
    * @param typ    typ hraca ci je horny alebo dolny.
    */
    public Hrac(String meno, TypHraca typ) {
        this.meno = meno;
        this.typ = typ;
        this.figurky = new ArrayList<>();
        this.vytvorFigurky();
    }
    
    /**
     * Vrati hracovo meno.
     * 
     * @return  meno hraca
     */
    public String getMeno() {
        return this.meno;
    }
    
    /**
     * Vrati typ hraca.
     * 
     * @return typ hraca
     */
    public TypHraca getTypHraca() {
        return this.typ;
    }
    
    /**
     * Vrati pocet ostavajucich figurok.
     * 
     * @return pocet figurok
     */
    public int getPocetFigurok() {
        return this.figurky.size();
    }
    
    /**
     * Vrati figurku ktora lezi na tom istom policku ako figurka z parametra.
     * @param fig   figurka podla ktorej sa bude kontrolovat miesto
     * @return  najdena figurka
     */
    public IFigurka getFigurku(IFigurka fig) {
        if (fig == null) {
            return null;
        }
        return this.getFigurku(fig.getPoloha());
    }
    
    /**
     * Vrati figurku ktora lezi na tom istom policku ako je v parametri.
     * @param poloha    kontrolovana poloha
     * @return najdena figurka
     */
    public IFigurka getFigurku (int[] poloha) {
        for (IFigurka f : this.figurky) {
            if (Arrays.equals(f.getPoloha(), poloha)) {
                return f;
            }
        }
        return null;
    }
    
    /**
     * Vrati prvu figurku ktoru najde na diagonale.
     * 
     * @param zaciatok pozicia policka od ktoreho ma zacat kontrolu
     * @param koniec pozicia policka pri ktorom ma skoncit
     * @return  prva najdena figurka
     */
    public IFigurka najdiFigurkuNaDiagonale(int[] zaciatok, int[] koniec) {
        if (zaciatok[0] - koniec[0] == 0 || zaciatok[1] - koniec[1] == 0) {
            return null;
        }
        if (Math.abs(zaciatok[0] - koniec[0]) != Math.abs(zaciatok[1] - koniec[1])) {
            return null;
        }
        int r = (zaciatok[0] - koniec[0] > 0) ? 1 : -1;
        int s = (zaciatok[1] - koniec[1] > 0) ? 1 : -1;
        int p = Math.abs(zaciatok[0] - koniec[0]) - 1;
        for (int i = p; i >= 0; i--) {
            if ( this.getFigurku(new int[]{koniec[0] + (i * r), koniec[1] + (i * s)}) != null) {
                return this.getFigurku(new int[]{koniec[0] + (i * r), koniec[1] + (i * s)});
            }
        }
        return null;
    }
    
    /**
     * Posunie zvolenu figurku na miesto z parametra.
     * 
     * @param fig zvolena figurka
     * @param poloha miesto kde sa ma pohnut 
     * @return true (ak sa figurka pohla) / flase (ak sa nepohla)
     */
    public boolean posunFigurku(IFigurka fig, int[] poloha) {
        if (fig == null || this.getFigurku(fig.getPoloha()) == null) {
            return false;
        }
        if (this.najdiFigurkuNaDiagonale(fig.getPoloha(), poloha) != null) {
            return false;
        }
        try {
            fig.skusSaPohnut(poloha[0], poloha[1]);
            if (poloha[0] == 1 || poloha[0] == 8) {
                this.nastavDamu(fig);
            }
            return true;
        } catch (NeplatneHodnotyException ex) {
            System.out.println(ex.getMessage());
            return false;
        }
    }
    
    /**
     * Zvolenu figurku nastavi za damu.
     * 
     * @param fig figurka ktora sa ma nastavit.
     */
    private void nastavDamu(IFigurka fig) {
        if (fig == null) {
            return;
        }
        if (!this.figurky.contains(fig)) {
            return;
        }
        if (fig instanceof FDama) {
            return;
        }
        int[] poloha = fig.getPoloha();
        FarbaFigurky farba = fig.getFarbuFigurky();
        this.figurky.remove(fig);
        fig.vymazSa();
        FDama dama = new FDama(poloha[0], poloha[1], farba);
        this.figurky.add(dama);
    }
    
    /**
     * Vymaze figurku na zvolenom mieste.
     * 
     * @param poloha poloha figurky
     * @return true (ak sa figurka vymazala) / flase (ak nie)
     */
    public boolean vymazFigurku(int[] poloha) {
        IFigurka fig = this.getFigurku(poloha);
        if (fig == null) {
            return false;
        } 
        if (!this.figurky.remove(fig)) {
            return false;
        }
        fig.vymazSa();
        return true;
    }
    
    /**
     * Zmaze vsetky figurky na ploche.
     */
    public void vymazZoznamFigurok() {
        for (IFigurka f: this.figurky) {
            f.vymazSa();
        }
        this.figurky.clear();
    }
    
    /**
     * Vykresli 8 figurok na plochu.
     */
    private void vytvorFigurky() {
        FarbaFigurky farba = (this.typ.equals(TypHraca.DOLNY)) ? FarbaFigurky.DOLNA : FarbaFigurky.HORNA;
        for (int i = 0; i < 8; i++) {
            int riadok = (this.typ.equals(TypHraca.DOLNY)) ? 7 : 1;
            if (i % 2 != 0) {
                riadok++;
            }
            this.figurky.add(new FPesiak(riadok, i + 1, farba));
        }
    }
}
