/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dama.figurky;

import dama.enumy.FarbaFigurky;
import dama.enumy.TypFigurky;
import dama.vynimky.NeplatneHodnotyException;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 *
 * @author acer
 */
public class FPesiakTest {
    private FPesiak p;
    public FPesiakTest() {
    }
    
    @Before
    public void setUp() {
        this.p = new FPesiak(7, 7, FarbaFigurky.DOLNA);
    }
    
    @After
    public void tearDown() {
    }

    /**
     * Test of getTypFigurky method, of class FPesiak.
     */
    @Test
    public void testGetTypFigurky() {
        System.out.println("getTypFigurky");
        assertFalse(this.p.getTypFigurky().equals(TypFigurky.DAMA));
    }

    /**
     * Test of skusSaPohnut method, of class FPesiak.
     */
    @Test
    public void testSkusSaPohnut() {
        System.out.println("skusSaPohnut");
        try {
            this.p.skusSaPohnut(7, 7);
        } catch (NeplatneHodnotyException e) {
            try {
                this.p.skusSaPohnut(6, 6);
                assertTrue(true);
            } catch (NeplatneHodnotyException e2) {
                assertTrue(false);
            }
        }
    }
}
