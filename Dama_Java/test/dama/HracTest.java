/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dama;

import dama.enumy.TypHraca;
import dama.figurky.IFigurka;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 *
 * @author acer
 */
public class HracTest {
    private Hrac h;
    
    public HracTest() {
    }
    
    
    @Before
    public void setUp() {
        this.h = new Hrac("Igor", TypHraca.HORNY);
    }
    
    @After
    public void tearDown() {
    }

    /**
     * Test of getMeno method, of class Hrac.
     */
    @Test
    public void testGetMeno() {
        System.out.println("getMeno");
        String expResult = "Igor";
        assertEquals(this.h.getMeno(), expResult);
    }

    /**
     * Test of getTypHraca method, of class Hrac.
     */
    @Test
    public void testGetTypHraca() {
        System.out.println("getTypHraca");
        TypHraca expResult = TypHraca.DOLNY;
        assertFalse(this.h.getTypHraca().equals(expResult));
    }

    /**
     * Test of getPocetFigurok method, of class Hrac.
     */
    @Test
    public void testGetPocetFigurok() {
        System.out.println("getPocetFigurok");
        int expResult = 0;
        assertTrue(expResult != this.h.getPocetFigurok());
    }

    /**
     * Test of getFigurku method, of class Hrac.
     */
    @Test
    public void testGetFigurku() {
        System.out.println("getFigurku");
        IFigurka fig1 = this.h.getFigurku(new int[]{1, 1});
        IFigurka fig2 = this.h.getFigurku(fig1);
        assertEquals(fig1, fig2);
    }

    /**
     * Test of najdiFigurkuNaDiagonale method, of class Hrac.
     */
    @Test
    public void testNajdiFigurkuNaDiagonale() {
        System.out.println("najdiFigurkuNaDiagonale");
        int[] zaciatok = new int[]{2, 2};
        int[] koniec = new int[]{2, 2};
        IFigurka expResult = null;
        IFigurka result = this.h.najdiFigurkuNaDiagonale(zaciatok, koniec);
        assertEquals(expResult, result);
    }

    /**
     * Test of posunFigurku method, of class Hrac.
     */
    @Test
    public void testPosunFigurku() {
        System.out.println("posunFigurku");
        IFigurka fig = this.h.getFigurku(new int[]{1, 1}); 
        assertFalse(this.h.posunFigurku(fig, new int[]{0, 0}));
    }

    /**
     * Test of vymazFigurku method, of class Hrac.
     */
    @Test
    public void testVymazFigurku() {
        System.out.println("vymazFigurku");
        IFigurka fig = this.h.getFigurku(new int[]{1, 1});
        this.h.vymazFigurku(fig.getPoloha());
        assertNotEquals(fig, this.h.getFigurku(new int[]{1, 1}));
    }

    /**
     * Test of vymazZoznamFigurok method, of class Hrac.
     */
    @Test
    public void testVymazZoznamFigurok() {
        System.out.println("vymazZoznamFigurok");
        this.h.vymazZoznamFigurok();
        assertTrue(this.h.getPocetFigurok() == 0);
    }
    
}
