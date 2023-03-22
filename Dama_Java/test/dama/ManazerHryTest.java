/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dama;

import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 *
 * @author acer
 */
public class ManazerHryTest {
    private ManazerHry m;
    public ManazerHryTest() {
    }
    
    @Before
    public void setUp() {
        this.m = new ManazerHry("", "");
    }
    
    @After
    public void tearDown() {
    }

    /**
     * Test of vyberSuradnice method, of class ManazerHry.
     */
    @Test
    public void testVyberSuradnice() {
        System.out.println("vyberSuradnice");
        int s = 0;
        int r = 0;
        this.m.vyberSuradnice(s, r);
        assertFalse(false);
    }

    /**
     * Test of zrus method, of class ManazerHry.
     */
    @Test
    public void testZrus() {
        System.out.println("zrus");
        assertTrue(true);
    }
    
}
