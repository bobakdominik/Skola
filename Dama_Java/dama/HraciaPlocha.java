/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dama;

import dama.skolskeTriedy.Stvorec;
import java.util.ArrayList;
import java.util.HashMap;

/**
 * Trieda HraciaPlocha zobrazi plochu poskladanu zo stvorcov.
 * 
 * @author Dominik Bobak
 */
public class HraciaPlocha {
    private HashMap<Integer, Stvorec> policka;
    private ArrayList<Stvorec> oznacenePolicka;
    
    /**
     * Konstruktor tiredy HraciaPlocha.
     */
    public HraciaPlocha() {
        this.policka = new HashMap<Integer, Stvorec>();
        this.oznacenePolicka = new ArrayList<Stvorec>();
        this.vytvorPlochu();
    }
    
    /**
     * Vrati pocet oznacenych policok.
     * 
     * @return pocet oznacenych policok
     */
    public int getPocetOznacenychPolicok() {
        return this.oznacenePolicka.size();
    }
    
    /**
     * Odznaci vsetky oznacene policka.
     */
    public void zrusOznacenia() {
        for (Stvorec p: this.oznacenePolicka) {
            p.zmenFarbu("black");
        }
        this.oznacenePolicka.clear();
    }
    
    /**
     * Skontroluje ci bolo policko oznacene podla parametra.
     * 
     * @param pozicia pozicia policka
     * @return true (ak je take policko oznacene) / false (ak nie je oznacene)
     */
    public boolean jePolickoOznacene (int[] pozicia) {
        int r = (pozicia[0] - 1) * 40;
        int s = (pozicia[1] - 1) * 40;
        for (Stvorec p: this.oznacenePolicka) {
            if (p.getY() == r && p.getX() == s) {
                return true;
            }
        }
        return false;
    }
    
    /**
     * Oznaci policko na danom mieste.
     * 
     * @param pozicia pozicia policka
     */
    public void oznacJednoPolicko (int[] pozicia) {
        int kluc = (pozicia[0] * 10) + pozicia[1];
        Stvorec p = this.policka.get(kluc);
        if (p != null) {
            p.zmenFarbu("orange");
            this.oznacenePolicka.add(p);
        }
    }
    
    /**
     * Oznaci vsetky policka zo zoznamu.
     * 
     * @param pozicie pozicie policok
     */
    public void oznacPolicka(ArrayList<int[]> pozicie) {
        if (pozicie == null) {
            return;
        }
        for (int[] p: pozicie) {
            int kluc = (p[0] * 10) + p[1];
            Stvorec s = this.policka.get(kluc);
            if (s != null) {
                s.zmenFarbu("orange");
                this.oznacenePolicka.add(s);
            }
        }
    }
    
    /**
     * Vykresli hraciu plochu.
     */
    private void vytvorPlochu() {
        for (int r = 8; r > 0; r--) {
            int pom = (r % 2 == 0) ? 0 : -1;
            for (int i = 4; i > 0; i--) {
                int s = (i * 2) + pom;
                Stvorec stvorec = new Stvorec((s - 1) * 40, (r - 1) * 40, 40, "black");
                stvorec.zobraz();
                this.policka.put((r * 10) + s, stvorec);
            }
        }
    }
}
