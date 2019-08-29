
import java.io.*;
import java.util.*;
import java.math.*;
import java.nio.charset.StandardCharsets;
import java.lang.*;
import java.util.Date;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

class HashAndOtp {
    private String hash;
    private String uniqueString;
    
    public HashAndOtp() {
        this.hash = null;
        this.uniqueString = null;
    }

    public void GenerateHash() {
        Date date = new Date();
        uniqueString = date.toString()+String.valueOf(date.getTime());
        this.hash = CreateHash(uniqueString);
        WriteToFile();
        // return this.hash;
    }

    public String GenerateOTP() {
        String val = this.hash;
        for ( int i=0; i<10; i++ ) {
            val = CreateHash(val);
        }
        String num = "";
        char[] arr = val.toCharArray();
        for ( int i=0; i<arr.length; i++ ) {
            if ( Character.isDigit(arr[i]) ) {
                num += String.valueOf(arr[i]);
            }
        }
        if ( num.length() < 4 ) {
            System.out.println("SAD");
            for ( int i=0; i<4-num.length(); i++ ) {
                num = "0"+num;
            }
        }
        return String.valueOf(num.subSequence(0, 4));
    }

    public void WriteToFile() {
        if ( hash == null ) {
            System.out.println("Hash not created!");
            return;
        }
        try {
            File file = new File("hash.txt");
            FileWriter fileWriter = new FileWriter(file);
            fileWriter.write(hash);
            fileWriter.flush();
            fileWriter.close();
        }
        catch(IOException e) {
            e.printStackTrace();
        }
    }

    public void RemoveHashFromFile() {
        try {
            File file = new File("hash.txt");
            FileWriter fileWriter = new FileWriter(file);
            fileWriter.write("");
            fileWriter.flush();
            fileWriter.close();
            uniqueString = null;
        } 
        catch (IOException e) {
            e.printStackTrace();
        }
    }

    public String CreateHash(String input) {
        try {
            MessageDigest messageDigest = MessageDigest.getInstance("SHA-256");
            byte[] hashBytes = messageDigest.digest(uniqueString.getBytes(StandardCharsets.UTF_8));
            StringBuilder stringBuilder = new StringBuilder();
            for (int i = 0; i < hashBytes.length; i++) {
                stringBuilder.append(String.format("%02x", hashBytes[i]));
            }
            return stringBuilder.toString();
        }
        catch (NoSuchAlgorithmException e){
            e.printStackTrace();
            return null;
        }
    }
}

class User {
    private String OTP;
    public User() {
        this.OTP = null;
    }
    public String getOTP() {
        if ( OTP == null ) {
            this.OTP = Alokh.RequestOTP();
        }
        return this.OTP;
    }
    public void Verify() {
        Alokh.FillOTP(this.OTP);
    }
}

class Alokh {
    private static HashAndOtp hashAndOtp;

    public static String RequestOTP() {
        hashAndOtp = new HashAndOtp();
        hashAndOtp.GenerateHash();
        return hashAndOtp.GenerateOTP();
    }  

    public static void FillOTP(String myotp) {
        String newOTP = hashAndOtp.GenerateOTP();
        System.out.println("newOTP: "+newOTP);
        if ( newOTP.equals(myotp) ) {
            System.out.println("Successful!");
            hashAndOtp.RemoveHashFromFile();
        }
        else {
            System.out.println("Unsuccessful!");
        }
    }
}

public class Security {

    public static void main(String[] args) throws IOException {
        Alokh alokh = new Alokh();
        User user = new User();
        String val = user.getOTP();
        System.out.println("First OTP: "+val);
        user.Verify();
    }
}
