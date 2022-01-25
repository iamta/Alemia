package ro.mta.library_project.People;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Random;

/**
 * Clasa genereaza un salt random pe care il ataseaza la parola si creaza hash-ul acesteia
 *
 * @author Cioaca Andrei
 */
public class CreateSaltAndPassword {
    /**
     * Metoda ataseaza salt-ul la finalul parolei si genereaza hash-ul acesteia
     *
     * @param password parola
     * @param salt     salt-ul generat de metoda getSalt
     * @return returneaza hash-ul parolei concatenate cu saltul
     */
    public static String getSecurePassword(String password, String salt) {

        String generatedPassword = null;
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            md.update(salt.getBytes());
            byte[] bytes = md.digest(password.getBytes());
            StringBuilder sb = new StringBuilder();
            for (int i = 0; i < bytes.length; i++) {
                sb.append(Integer.toString((bytes[i] & 0xff) + 0x100, 16).substring(1));
            }
            generatedPassword = sb.toString();
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
        return generatedPassword;
    }


    /**
     * Metoda genereaza un salt random din intervalul [10000-99999]
     *
     * @return returneaza salt-ul generat
     */
    public static String getSalt() {
        Random rand = new Random();

        int n = rand.nextInt(10000, 99999);

        return String.valueOf(n);
    }
}
