package test;

import org.example.interpreter.Interpreter;
import org.junit.jupiter.api.*;

import java.io.ByteArrayOutputStream;
import java.io.PrintStream;

public class CommandTests {
    private final ByteArrayOutputStream outContent = new ByteArrayOutputStream();
    private final ByteArrayOutputStream errContent = new ByteArrayOutputStream();
    private final PrintStream originalOut = System.out;
    private final PrintStream originalErr = System.err;

    @BeforeEach
    public void setUpStreams() {
        System.setOut(new PrintStream(outContent));
        System.setErr(new PrintStream(errContent));
    }
    @AfterEach
    public void restoreStreams() {
        System.setOut(originalOut);
        System.setErr(originalErr);
    }

    @Test
    void Sum() {
        Interpreter I = new Interpreter();
        I.ProcessText("10 20 + .");
        Assertions.assertEquals("30 ", outContent.toString());
    }
    @Test
    void Sub() {
        Interpreter I = new Interpreter();
        I.ProcessText("10 20 - .");
        Assertions.assertEquals("-10 ", outContent.toString());
    }
    @Test
    void Mult() {
        Interpreter I = new Interpreter();
        I.ProcessText("10 20 * .");
        Assertions.assertEquals("200 ", outContent.toString());
    }
    @Test
    void Div() {
        Interpreter I = new Interpreter();
        I.ProcessText("100 5 / .");
        Assertions.assertEquals("20 ", outContent.toString());
    }
    @Test
    void Mod() {
        Interpreter I = new Interpreter();
        I.ProcessText("25 3 mod .");
        Assertions.assertEquals("1 ", outContent.toString());
    }
    @Test
    void Dup() {
        Interpreter I = new Interpreter();
        I.ProcessText("10 20 300 dup . .");
        Assertions.assertEquals("300 300 ", outContent.toString());
    }
    @Test
    void Drop() {
        Interpreter I = new Interpreter();
        I.ProcessText("10 20 30 drop . .");
        Assertions.assertEquals("20 10 ", outContent.toString());
    }
    @Test
    void Emit() {
        Interpreter I = new Interpreter();
        I.ProcessText("79 emit");
        Assertions.assertEquals("O ", outContent.toString());
    }
    @Test
    void If() {
        Interpreter I = new Interpreter();
        I.ProcessText("0 if 4 5 + . else 40 50 + . then ;");
        Assertions.assertEquals("90 ", outContent.toString());

        I.ProcessText("1 if 4 5 + . else 40 50 + . then ;");
        Assertions.assertEquals("90 9 ", outContent.toString());


        I.ProcessText("0 if if 1 2 + . else 2 3 + then ; else if 10 20 + . else 20 30 + . then ; then ;");
        Assertions.assertEquals("90 9 50 ", outContent.toString());

        I = new Interpreter();
        I.ProcessText("1 if if 1 2 + . else 2 3 + then ; else if 10 20 + . else 20 30 + . then ; then ;");
        Assertions.assertEquals("90 9 50 3 ", outContent.toString());
    }
}
