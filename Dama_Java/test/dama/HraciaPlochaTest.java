/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package dama;

import java.util.ArrayList;
import org.junit.After;
import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.*;

/**
 *
 * @author acer
 */
public class HraciaPlochaTest {
    private HraciaPlocha h;
    public HraciaPlochaTest() {
    }
    
    
    @Before
    public void setUp() {
        this.h = new HraciaPlocha();
    }
    
    @After
    public void tearDown() {
    }

    /**
     * Test of getPocetOznacenychPolicok method, of class HraciaPlocha.
     */
    @Test
    public void testGetPocetOznacenychPolicok() {
        System.out.println("getPocetOznacenychPolicok");
        assertFalse(this.h.getPocetOznacenychPolicok() != 0);
    }

    /**
     * Test of zrusOznacenia method, of class HraciaPlocha.
     */
    @Test
    public void testZrusOznacenia() {
        System.out.println("zrusOznacenia");
        this.h.oznacJednoPolicko(new int[]{1, 1});
        this.h.zrusOznacenia();
        assertTrue(this.h.getPocetOznacenychPolicok() == 0);
    }

    /**
     * Test of jePolickoOznacene method, of class HraciaPlocha.
     */
    @Test
    public void testJePolickoOznacene() {
        System.out.println("jePolickoOznacene");
        this.h.oznacJednoPolicko(new int[]{1, 1});
        assertTrue(this.h.jePolickoOznacene(new int[]{1, 1}));
    }

    /**
     * Test of oznacJednoPolicko method, of class HraciaPlocha.
     */
    @Test
    public void testOznacJednoPolicko() {
        System.out.println("oznacJednoPolicko");
        this.h.oznacJednoPolicko(new int[]{1, 1});
        assertTrue(this.h.getPocetOznacenychPolicok() == 1);
    }

    /**
     * Test of oznacPolicka method, of class HraciaPlocha.
     */
    @Test
    public void testOznacPolicka() {
        System.out.println("oznacPolicka");
        ArrayList<int[]> pozicie = new ArrayList<>();
        pozicie.add(new int[]{1, 1});
        pozicie.add(new int[]{2, 2});
        pozicie.add(new int[]{3, 3});
        this.h.oznacPolicka(pozicie);
        assertTrue(this.h.getPocetOznacenychPolicok() == 3);
    }
    
}
