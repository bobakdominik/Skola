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
 * Interface pre figurky.
 * 
 * @author Dominik Bobak
 */
public interface IFigurka {
    void skusSaPohnut(int riadok, int stlpec) throws NeplatneHodnotyException;
    TypFigurky getTypFigurky ();
    int[] getPoloha();
    FarbaFigurky getFarbuFigurky ();
    void prefarbi();
    void vymazSa();
}
