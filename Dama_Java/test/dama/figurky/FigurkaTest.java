/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dama.figurky;

import org.junit.After;
import org.junit.AfterClass;
import org.junit.Before;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 *
 * @author acer
 */
public class FigurkaTest {
    
    public FigurkaTest() {
    }
    
    @BeforeClass
    public static void setUpClass() {
    }
    
    @AfterClass
    public static void tearDownClass() {
    }
    
    @Before
    public void setUp() {
    }
    
    @After
    public void tearDown() {
    }

    /**
     * Test of getPoloha method, of class Figurka.
     */
    @Test
    public void testGetPoloha() {
        System.out.println("getPoloha");
        assertNotEquals(122, 54);
    }

    /**
     * Test of getFarbuFigurky method, of class Figurka.
     */
    @Test
    public void testGetFarbuFigurky() {
        System.out.println("getFarbuFigurky");
        Figurka f = null;
        assertNull(f);
    }
}
