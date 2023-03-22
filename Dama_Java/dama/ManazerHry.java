/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dama;

import dama.enumy.TypHraca;
import dama.figurky.FPesiak;
import dama.vynimky.NeplatneHodnotyException;
import java.util.HashMap;
import dama.figurky.IFigurka;
import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;

/**
 * Trieda ManazerHry riadi cele fungovanie hry Dama.
 * 
 * @author Dominik Bobak
 */
public class ManazerHry {
    private HashMap<TypHraca, Hrac> hraci;
    private IFigurka oznacenaFigurka;
    private HraciaPlocha hraciaPlocha;
    private TypHraca hracNaTahu;
    private boolean bolTah;
    private boolean hraSkoncila;
    private int pocetKol;
    
    /**
     * Konstruktor triedy ManazerHry.
     * 
     * @param meno1 meno prveho hraca
     * @param meno2 meno druheho hraca
     */
    public ManazerHry (String meno1, String meno2) {
        this.hraciaPlocha = new HraciaPlocha();
        Hrac hrac1 = new Hrac(meno1, TypHraca.DOLNY);
        Hrac hrac2 = new Hrac(meno2, TypHraca.HORNY);
        this.hraci = new HashMap<TypHraca, Hrac>() { {
                put(TypHraca.DOLNY, hrac1);
                put(TypHraca.HORNY, hrac2);
            }
        };
        this.hracNaTahu = TypHraca.DOLNY;
        this.bolTah = false;
        this.hraSkoncila = false;
        this.pocetKol = 1;
        System.out.printf("\fZacina dolny hrac (%s)\n", meno1);
    }
    
    /**
     * Podla zvolenych suradnic bud oznaci figurku alebo zahaji tah.
     * Reaguje na spravu z triedy Manazer. 
     * 
     * @param s X-ova suradnica
     * @param r Y-ova suradnica
     */
    public void vyberSuradnice(int s, int r) {
        if (this.hraSkoncila) {
            return;
        }
        s = (s / 40) + 1;
        r = (r / 40) + 1;
        if (this.oznacenaFigurka == null) {
            this.oznacenaFigurka = this.hraci.get(this.hracNaTahu).getFigurku(new int[]{r, s});
            if (this.oznacenaFigurka != null) {
                this.oznacenaFigurka.prefarbi();
                this.oznacPolicka();
            }
        } else {
            if (this.oznacenaFigurka.equals(this.hraci.get(this.hracNaTahu).getFigurku(new int[]{r, s}))) {
                this.oznacenaFigurka.prefarbi();
                this.hraciaPlocha.zrusOznacenia();
                this.oznacenaFigurka = null;
                if (this.bolTah) {
                    this.vymenHraca();
                }
            } else {
                try {
                    this.hraj(new int[]{r, s});
                } catch (NeplatneHodnotyException ex) {
                    System.out.println(ex.getMessage());
                }                
            }
        }        
    }
    
    /**
     * Oznaci policka na ktore sa moze zvolena figurka pohnut.
     */
    private void oznacPolicka() {
        TypHraca protivnik = (this.hracNaTahu.equals(TypHraca.DOLNY)) ? TypHraca.HORNY : TypHraca.DOLNY ;
        if (this.oznacenaFigurka instanceof FPesiak) {
            int pom = (this.hracNaTahu.equals(TypHraca.DOLNY)) ? -1 : 1;
            for (int i = 2; i > 0; i--) {
                int novyRiadok = this.oznacenaFigurka.getPoloha()[0] + pom;
                int novyStlpec = this.oznacenaFigurka.getPoloha()[1];
                novyStlpec += (i == 1) ? -pom : pom; 
                if (this.bolTah) {
                    if (this.hraci.get(this.hracNaTahu).getFigurku(new int[]{novyRiadok, novyStlpec}) == null && 
                            this.hraci.get(protivnik).getFigurku(new int[]{novyRiadok, novyStlpec}) == null) {
                        continue;
                    }
                }
                if (this.hraci.get(protivnik).getFigurku(new int[]{novyRiadok, novyStlpec}) != null) {
                    novyStlpec += (i == 1) ? -pom : pom;
                    novyRiadok += pom;
                }
                if (novyStlpec > 8 || novyStlpec < 1 || novyRiadok > 8 || novyRiadok < 1) {
                    continue;
                }
                if (this.hraci.get(this.hracNaTahu).getFigurku(new int[]{novyRiadok, novyStlpec}) != null || 
                        this.hraci.get(protivnik).getFigurku(new int[]{novyRiadok, novyStlpec}) != null) {
                    continue;
                }
                this.hraciaPlocha.oznacJednoPolicko(new int[]{novyRiadok, novyStlpec});
            }
        } else {
            int pom = 1;
            for (int i = 2; i > 0; i--) {
                int pom2 = 1;
                for (int j = 2; j > 0; j--) {
                    ArrayList<int[]> polickaNaOznacenie = new ArrayList<>();
                    int novyRiadok = this.oznacenaFigurka.getPoloha()[0];
                    int novyStlpec = this.oznacenaFigurka.getPoloha()[1];
                    boolean jeFigNaVyhodenie = false;
                    do {
                        novyRiadok += pom;
                        novyStlpec += pom2;
                        if (novyRiadok > 8 || novyRiadok < 1 || novyStlpec > 8 || novyStlpec < 1) {
                            break;
                        }
                        if (this.hraci.get(protivnik).getFigurku(new int[]{novyRiadok, novyStlpec}) != null) {
                            novyRiadok += pom;
                            novyStlpec += pom2;
                            if (novyStlpec > 8 || novyRiadok > 8 || novyStlpec < 1 || novyRiadok < 1) {
                                break;
                            }
                            if (jeFigNaVyhodenie) {
                                break;
                            }
                            jeFigNaVyhodenie = true;
                        }
                        if (this.hraci.get(this.hracNaTahu).getFigurku(new int[]{novyRiadok, novyStlpec}) != null ||
                            this.hraci.get(protivnik).getFigurku(new int[]{novyRiadok, novyStlpec}) != null) {
                            break;
                        }
                        polickaNaOznacenie.add(new int[]{novyRiadok, novyStlpec});
                    } while (novyRiadok < 8 && novyRiadok > 1 && novyStlpec < 8 && novyStlpec > 1);
                    if (this.bolTah && !polickaNaOznacenie.isEmpty()) {
                        IFigurka protivnikovaFigurka = this.hraci.get(protivnik).najdiFigurkuNaDiagonale(this.oznacenaFigurka.getPoloha(), polickaNaOznacenie.get(polickaNaOznacenie.size() - 1));
                        if (protivnikovaFigurka != null) {
                            while (polickaNaOznacenie.get(0)[0] != protivnikovaFigurka.getPoloha()[0] + pom || 
                                    polickaNaOznacenie.get(0)[1] != protivnikovaFigurka.getPoloha()[1] + pom2) {
                                polickaNaOznacenie.remove(0);
                            }
                        } else {
                            polickaNaOznacenie.clear();
                        }
                    }
                    this.hraciaPlocha.oznacPolicka(polickaNaOznacenie);
                    pom2 = (-1) * pom2;
                }
                pom = (-1) * pom;
            }
        }
    }
    
    /**
     * Posunie zvolenu figurku na vybrate miesto.
     * 
     * @param poloha miesto na ktore sa ma figurka pohnut
     * @throws NeplatneHodnotyException Exception ak sa figurka nemoze pohnut na zvolene miesto
     */
    private void hraj(int[] poloha) throws NeplatneHodnotyException {
        if (this.hraciaPlocha.getPocetOznacenychPolicok() == 0) {
            throw new NeplatneHodnotyException("Figurka sa nemoze pohnut");
        }
        if (!this.hraciaPlocha.jePolickoOznacene(poloha)) {
            throw new NeplatneHodnotyException("Figurka ma vyznacene miesta pohybu!");
        }
        TypHraca protivnik = (this.hracNaTahu.equals(TypHraca.DOLNY)) ? TypHraca.HORNY : TypHraca.DOLNY;
        IFigurka vyhodenaFigurka = this.hraci.get(protivnik).najdiFigurkuNaDiagonale(this.oznacenaFigurka.getPoloha(), poloha);
        this.hraciaPlocha.zrusOznacenia();
        if (!this.hraci.get(this.hracNaTahu).posunFigurku(this.oznacenaFigurka, poloha)) {
            throw new NeplatneHodnotyException("Figurka sa nemoze pohnut");
        }
        if (vyhodenaFigurka != null) {
            this.hraci.get(protivnik).vymazFigurku(vyhodenaFigurka.getPoloha());
            this.bolTah = true;
            if ((this.oznacenaFigurka instanceof FPesiak) && (poloha[0] == 1 || poloha[0] == 8)) {
                this.oznacenaFigurka = this.hraci.get(this.hracNaTahu).getFigurku(poloha);
                this.oznacenaFigurka.prefarbi();
            }
            this.oznacPolicka();
            if (this.hraciaPlocha.getPocetOznacenychPolicok() != 0) {
                return;
            }
        } 
        if (this.hraci.get(protivnik).getPocetFigurok() != 0) {
            this.vymenHraca();
        } else {
            this.hraSkoncila = true;
            this.vypisVyhru();
        }
    }
    
    /**
     * Vypise vyhru do prikazoceho riadku.
     */
    private void vypisVyhru() {
        TypHraca protivnik = (this.hracNaTahu.equals(TypHraca.DOLNY)) ? TypHraca.HORNY : TypHraca.DOLNY;
        System.out.println("\f\n###################################################");
        System.out.println("###################################################");
        System.out.println("Koniec hry\n");
        System.out.println("Hru vyhrava hrac: " + this.hraci.get(this.hracNaTahu).getMeno());
        System.out.println("\nPocet kol: " + this.pocetKol);
        System.out.println("Protivnik: " + this.hraci.get(protivnik).getMeno());
        System.out.println("###################################################");
        System.out.println("###################################################\n");
        try {
            Thread.sleep(2000);
        } catch (Exception e) {
            
        }
        System.out.println("Hra bude ulozena do suboru");
        if (!this.ulozDoSuboru()) {
            System.out.println("Hru sa nepodarilo ulozit");
        } else {
            try {
                this.vypisSubor();
            } catch (IOException e2) {
                System.out.println(e2.getMessage());
            }
        }
        System.out.println("Stlac klavesu Esc");
    }
    
    /**
     * Vymeni hraca ktory je na tahu.
     */
    private void vymenHraca() {
        if (this.hracNaTahu.equals(TypHraca.HORNY)) {
            this.pocetKol++;
        }
        if (this.oznacenaFigurka != null) {
            this.oznacenaFigurka.prefarbi();
            this.oznacenaFigurka = null;
        }
        this.bolTah = false;
        this.hraciaPlocha.zrusOznacenia();
        this.hracNaTahu = (this.hracNaTahu.equals(TypHraca.DOLNY)) ? TypHraca.HORNY : TypHraca.DOLNY;
        System.out.printf("\f\n%s hrac je na tahu (%s)\n", this.hracNaTahu.toString(), this.hraci.get(this.hracNaTahu).getMeno());
    }
    
    /**
     * Ukoncuje hru.
     * Reaguje na spravu triedy Manazer. 
     */
    public void zrus() {
        System.out.println("\f");
        if (!this.hraSkoncila) {
            System.out.println("Nikto nevyhral");
        }
        System.out.println("Hra bola ukoncena");
        try { 
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            System.out.println(e.getMessage());
        }
        System.exit(0);
    }
    
    private void vypisSubor() throws IOException {
        File subor = new File("Dama");
        FileInputStream prudVstupny = new FileInputStream(subor);
        DataInputStream citac = new DataInputStream(prudVstupny);
        try {
            System.out.println("Udaje zo suboru:");
            System.out.println(citac.readUTF());
            System.out.println(citac.readLong());
            System.out.println(citac.readUTF());
            System.out.println(citac.readUTF());
            System.out.println(citac.readUTF());
        } catch (IOException e) {
            throw new IOException("Subor nebolo mozne nacitat");
        } finally {
            citac.close();
        }
    }
    
    /**
     * Ulozi hru do suboru.
     * 
     * @return true (ak sa ju podarilo ulozit) / false (ak sa neulozila)
     */
    private boolean ulozDoSuboru() {
        File subor = new File("Dama"); 
        DataOutputStream zapisovac = null;
        TypHraca protivnik = (this.hracNaTahu.equals(TypHraca.DOLNY)) ? TypHraca.HORNY : TypHraca.DOLNY;
        String vitaz = this.hraci.get(this.hracNaTahu).getMeno();
        String porazeny = this.hraci.get(protivnik).getMeno();
        try {
            FileOutputStream prudVystupny = new FileOutputStream(subor);
            zapisovac = new DataOutputStream(prudVystupny);
            zapisovac.writeUTF("Dama");
            zapisovac.writeLong(System.currentTimeMillis());
            zapisovac.writeUTF("Vitaz: " + vitaz);
            zapisovac.writeUTF("Porazeny: " + porazeny);
            zapisovac.writeUTF("Pocet kol: " + this.pocetKol);
            zapisovac.close();
        } catch (IOException e) {
            if (zapisovac != null) {
                try {
                    zapisovac.close();
                } catch (IOException e2) {
                
                }
            }
            return false;
        }
        return true;
    }
}
