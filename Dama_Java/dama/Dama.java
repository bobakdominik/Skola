/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dama;

import dama.skolskeTriedy.Manazer;
import java.util.Scanner;

/**
 * Trieda Dama vytvori novu hru.
 * Najskor si vypyta od uzivatela mena pre dvoch hracov a nasledne spusti hru.
 * 
 * @author Dominik Bobak
 */
public class Dama {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        System.out.println("###################################################");
        System.out.println("###################################################");
        System.out.println("\f\nVitajte v hre Dáma\n");
        System.out.println("###################################################");
        System.out.println("###################################################");
        System.out.println("Zadaj meno prvého hráča.");
        String meno1 = scan.nextLine();
        if (meno1.isEmpty()) {
            meno1 = "Bez mena";
        }
        System.out.println("Zadaj meno druhého hráča.");        
        String meno2 = scan.nextLine();
        if (meno2.isEmpty()) {
            meno2 = "Bez mena";
        }
        Manazer man = new Manazer();
        ManazerHry hra = new ManazerHry(meno1, meno2);
        man.spravujObjekt(hra);
    }
}
