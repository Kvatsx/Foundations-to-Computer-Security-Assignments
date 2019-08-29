// Kaustav Vats
import java.io.*;
import java.util.*;
import java.math.*;
import java.lang.*;


class Q3 {

    public void FindFreq(char[] CipherText) {
        int[] FreqArr = new int[127];
        for ( int i=0; i<CipherText.length; i++ ) {
            FreqArr[(int)(CipherText[i])] += 1;
        }
        for ( int i=97; i<123; i++ ) {
            System.out.println((char)(i)+" "+FreqArr[i]);
        }
    }

    public String partA(char[] CipherText) {
        String KEY1 = "HIJKLMNOPQRSTUVWXYZABCDEFG";
        String KEY2 = KEY1.toLowerCase();

        int ascii = 64;
        HashMap<Character, Character> hashMap = new HashMap<Character, Character>();
        for (int i = 0; i < KEY1.length(); i++) {
            ascii += 1;
            hashMap.put(KEY1.charAt(i), (char) (ascii));
        }
        ascii = 96;
        for (int i = 0; i < KEY2.length(); i++) {
            ascii += 1;
            hashMap.put(KEY2.charAt(i), (char) (ascii));
        }

        String out = "\n";
        for (int i = 0; i < CipherText.length; i++) {
            if (hashMap.containsKey(CipherText[i])) {
                out += hashMap.get(CipherText[i]);
            } else {
                out += CipherText[i];
            }
        }
        return out;
    }

    public String partb(char[] CipherText){
        String KEY1 = "BIRDWATCHNGEFJKLMOPQSUVXYZ";
        String KEY2 = KEY1.toLowerCase();

        int ascii = 64;
        HashMap<Character, Character> hashMap = new HashMap<Character, Character>();
        for ( int i=0; i<KEY1.length(); i++ ) {
            ascii += 1;
            hashMap.put(KEY1.charAt(i), (char)(ascii));
        }
        ascii = 96;
        for ( int i=0; i<KEY2.length(); i++ ) {
            ascii += 1;
            hashMap.put(KEY2.charAt(i), (char)(ascii));
        }

        String out = "\n";
        for ( int i=0; i<CipherText.length; i++ ) {
            if ( hashMap.containsKey(CipherText[i]) ) {
                out += hashMap.get(CipherText[i]);
            }
            else {
                out += CipherText[i];
            }
        }
        return out;
    }

    public static void main(String[] args) throws IOException{
        BufferedReader inp = new BufferedReader(new InputStreamReader(System.in));
        Q3 q3 = new Q3();
        String text1 = "Qcw Hjdhbj lbobdhpw aeyrbqrcwo (Qwolphlckjw lbobdhph) hp b fwdhsf-phzwd lbppwohjw ihod jbqhuw qk Bphb qcbq hp vhdwey dhpqohisqwd. Bp qcw tekibe lklsebqhkj hp rkjphdwowd pqbiew, hq cbp iwwj ehpqwd bp Ewbpq Rkjrwoj kj qcw HSRJ Owd Ehpq phjrw 2004. Hq hp jbqhuw qk qcw Hjdhbj psirkjqhjwjq, Rwjqobe Bphb bjd Fybjfbo";
        String text2 = "Slnpzshabylzohssthrluvshdylzwljapunhulzahispzotluavmylspnpvuvywyvopipapunaolmylllelyjpzlaolylvmvyhiypknpunaolmyllkvtvmzwlljovyvmaolwylzzvyaolypnoavmaolwlvwslwlhjlhisfavhzzltislhukavwlapapvuaolnvclyutluamvyhylkylzzvmnyplchujlz nhtl vm aoyvulz zlhzvu lpnoa zwvpslyz qvu zuvd huk khlulyfz ahynhyflu av rpss lhjo vaoly";
        System.out.println(q3.partA(text2.toCharArray()));
        q3.FindFreq(text2.toCharArray());
        System.out.println(q3.partb(text1.toCharArray()));
        // q3.FindFreq(text2.toLowerCase().toCharArray());
    }
}


/** Class for buffered reading int and double values */
class Reader {
    static BufferedReader reader;
    static StringTokenizer tokenizer;

    /** call this method to initialize reader for InputStream */
    static void init(InputStream input) {
        reader = new BufferedReader(
                     new InputStreamReader(input) );
        tokenizer = new StringTokenizer("");
    }

    /** get next word */
    static String next() throws IOException {
        while ( ! tokenizer.hasMoreTokens() ) {
            //TODO add check for eof if necessary
            tokenizer = new StringTokenizer(
                   reader.readLine() );
        }
        return tokenizer.nextToken();
    }

    static int nextInt() throws IOException {
        return Integer.parseInt( next() );
    }

    static long nextLong() throws IOException {
        return Long.parseLong( next() );
    }
	
    static double nextDouble() throws IOException {
        return Double.parseDouble( next() );
    }
}