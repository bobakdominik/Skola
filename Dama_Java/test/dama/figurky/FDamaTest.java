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
public class FDamaTest {
    private FDama d;
    public FDamaTest() {
    }
    
    @Before
    public void setUp() {
        this.d = new FDama(1, 1, FarbaFigurky.HORNA);
    }
    
    @After
    public void tearDown() {
    }

    /**
     * Test of getTypFigurky method, of class FDama.
     */
    @Test
    public void testGetTypFigurky() {
        System.out.println("getTypFigurky");
        assertEquals(this.d.getTypFigurky(), TypFigurky.DAMA);
    }

    /**
     * Test of skusSaPohnut method, of class FDama.
     */
    @Test
    public void testSkusSaPohnut() {
        System.out.println("skusSaPohnut");
        try {
            this.d.skusSaPohnut(5, 1);
        } catch (NeplatneHodnotyException e) {
            assertTrue(true);
        }
    }
}
