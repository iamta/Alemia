package ro.mta.library_project.Book;
import javax.swing.text.Document;
import java.awt.desktop.ScreenSleepEvent;
import java.io.*;
import java.net.URL;
import java.nio.charset.StandardCharsets;
import java.nio.file.*;
import java.nio.file.attribute.BasicFileAttributes;
import java.nio.file.attribute.FileTime;
import java.security.MessageDigest;
import java.time.*;
import java.time.temporal.ChronoUnit;
import java.util.*;
import java.net.HttpURLConnection;
import org.apache.pdfbox.pdmodel.PDDocument;
import org.apache.pdfbox.pdmodel.encryption.AccessPermission;
import org.apache.pdfbox.pdmodel.encryption.StandardProtectionPolicy;
import org.apache.pdfbox.util.PDFTextStripper;

import java.io.File;
import java.io.IOException;
/**
 * Clasa BookCrypt se ocupa cu descarcarea, criptarea si decriptarea cartilor electronice.
 * Implementeaza runnable.
 *
 * @author Madalina Oltean
 */
public class BookCrypt implements Runnable {
    /**
     * Descrierea membrilor
     */
    private String link;
    private File out;
    private String filename;
    private String password;
    private String BookTitle;
    /**
     * Constructorul clasei BookCrypt
     * @param URL-ul unei carti electronice
     * @param titlul cartii electronice
     * @param parola utilizatorului
     */
    BookCrypt(String URL, String BookTitle, String password) {
        //parola pentru criptarea si decriptarea cartii va fi generata pe baza parolei de utilizator primita ca parametru si a titlului cartii
        this.password = password + BookTitle;
        this.link = URL;
        this.BookTitle = BookTitle;
        //creeaza un fisier pdf cu numele cartii
        filename = BookTitle + ".pdf";
        out = new File(filename);


    }

    public String getTitle() {
        return this.BookTitle;
    }



    public void setLink(String URL) {
        this.link = URL;
    }

    public String getLink() {
        return this.link;
    }
    /**
     * Metoda download() descarca cartea electronica din url
     *
     */
    void dowload(){
        try {
            URL url = new URL(link);
            HttpURLConnection http = (HttpURLConnection) url.openConnection();
            double fileSize = (double) http.getContentLengthLong();
            BufferedInputStream in = new BufferedInputStream(http.getInputStream());
            FileOutputStream fos = new FileOutputStream(this.out);
            BufferedOutputStream bout = new BufferedOutputStream(fos, 1024);
            byte[] buffer = new byte[1024];
            double dowloaded = 0.00;
            int read = 0;
            while ((read = in.read(buffer, 0, 1024)) >= 0) {
                bout.write(buffer, 0, read);
                dowloaded += read;


            }
            bout.close();
            in.close();

        } catch (IOException ex) {
            ex.printStackTrace();
        }


    }
    /**
     * Metoda encrypt() cripteaza si salveaza pdf-ul cartii
     * @param parola cu care se cripteaza cartea electronica ce va fi salvata pe disk
     */
    public void encrypt(String password) throws Exception{
        // incarc fisierul pdf
        File f = new File(filename);
        PDDocument pdd = PDDocument.load(f);

        AccessPermission ap = new AccessPermission();

        StandardProtectionPolicy stpp
                = new StandardProtectionPolicy(password, password, ap);

        stpp.setEncryptionKeyLength(128);

        stpp.setPermissions(ap);

        pdd.protect(stpp);

        pdd.save(filename);
        pdd.close();

        // System.out.println("PDF Encrypted successfully...");


    };

    /**
     * Metoda decrypt() decripteaza cartea electronica si scrie continutul decriptat
     * intr-un fisier temporar care va fi sters dupa ce se citeste continutul lui
     * @param parola cu care se decripteaza cartea electronica aflata criptata pe disk
     */
    public void decrypt(String pass) throws Exception
    {
        File f = new File(filename);
        PDDocument pdd = PDDocument.load(f);
        pdd.setAllSecurityToBeRemoved(true);
        if(pdd.isEncrypted())
        {
            pdd.decrypt(pass);
        }

        pdd.save(filename);

        PDFTextStripper pdfTextStripper=new PDFTextStripper();
        String docText=pdfTextStripper.getText(pdd);
        FileWriter txt=new FileWriter("temp.txt");
        txt.write(docText);
        txt.close();

        pdd.close();
        encrypt(pass);

    }

    /**
     * Metoda run() suprascrie metoda run() din Runnable
     * Face hash pe parola pentru a cripta cu o parola hash-uita.
     * Apeleaza metodele de descarcare, criptare si decriptare.
     * Daca se incearca citirea unei carti dupa mai mult de doua saptmani aceasta va fi stersa si descarcata din nou
     */
    @Override
    public void run(){

        //descarcarea cartii daca nu exista deja
        try {
            File f = new File(filename);
            if(f.exists()==false)
            {
                dowload();
            }

            MessageDigest digest=MessageDigest.getInstance("SHA-256");
            byte[] encodedhash=digest.digest(this.password.getBytes(StandardCharsets.UTF_8));
            encrypt(encodedhash.toString());
            //daca pdf-ul a depasit termenul de doua saptamani il sterg si descarc din nou, dupa care criptez
            try {
                Path path=f.toPath();
                BasicFileAttributes attr =  Files.readAttributes(path, BasicFileAttributes.class);
                FileTime creationTime=attr.lastModifiedTime();
                LocalDateTime now = LocalDateTime.now();
                LocalDateTime convertedFileTime = LocalDateTime.ofInstant(creationTime.toInstant(), ZoneId.systemDefault());
                long days = ChronoUnit.DAYS.between(convertedFileTime, now);
                if(days>14)
                {
                    f.delete();
                    dowload();
                    encrypt(encodedhash.toString());
                }
            } catch (IOException ex) {
                ex.printStackTrace();
            }

            decrypt(encodedhash.toString());

        }
        catch(Exception ex)
        {
            ex.printStackTrace();
        }

    }
}
