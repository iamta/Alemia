package ro.mta.library_project.Book;
import ro.mta.library_project.DBController.DBController;

import java.awt.*;
import java.net.URI;
import javax.security.sasl.AuthorizeCallback;
import javax.swing.*;
import java.io.*;
import java.sql.ResultSet;
import java.text.SimpleDateFormat;
import java.util.Random;
import java.nio.charset.Charset;
import java.time.LocalDate;


/**
 * Clasa ElectronicBook mosteneste clasa Book si membrii ei,
 * la care adauga ca membrii un URL, un numar de accesari si o parola utilizata la criptare si decriptare.
 * Ca si functionalitati adahuga functionalitatea de vizualizare a unei carti electronice
 *
 * @author Madalina Oltean
 */
public class ElectronicBook extends Book{
    /**
     * Descrierea membrilor
     */
    private int NumberAccesses;
    //in Content se afla url-ul la care se afla cartea
    private String Content;
    private String Password;
    public ElectronicBook()
    {

    }

    /**
     * Constructorul clasei ElectronicBook
     * @param id-ul unei carti electronice
     *In functie de id populeaza membrii Content, titlul si numarul de accesari
     */
    public ElectronicBook(int id)
    {
        setIdBook(id);
        setIdBook(id);

        try {
            DBController dbc = DBController.getInstance();
            ResultSet set = null;
            set = dbc.Select("Carti", "ID", String.valueOf(this.getIdBook()));
            if(set.next()) {
                this.Content = set.getString(11);
                this.setTitle(set.getString(2));
            }

            this.NumberAccesses = dbc.GetNumberOfRows("Citiri", "CarteElectronica", String.valueOf(this.getIdBook()));
        }
        catch(Exception e)
        {
            System.out.println("Something went wrong.");
        }
    }

    /**
     * Constructorul clasei ElectronicBook populeaza toti membrii clasei,
     * genereaza automat si o parola random, insa nu aceasta va fi folosita,
     * ci se va face set pentru parola
     * @param id-ul unei carti electronice
     * @param titlul cartii
     * @param autorul cartii
     * @param numarul de pagini al cartii
     * @param genul cartii
     * @param data publicarii cartii
     *
     */
    public ElectronicBook(int id, String title, String author, int nr_pag, String genre, LocalDate Pub_date)
    {

        setIdBook(id);
        setTitle(title);
        setAuthor(author);
        setNumberPages(nr_pag);
        setGenre(genre);
        setPublishingDate(Pub_date);
        try {
            DBController dbc = DBController.getInstance();
            ResultSet set = null;
            set = dbc.Select("Carti", "ID", String.valueOf(this.getIdBook()));
            if(set.next()) {
                this.Content = set.getString(11);
            }

            this.NumberAccesses = dbc.GetNumberOfRows("Citiri", "CarteElectronica", String.valueOf(this.getIdBook()));
        }
        catch(Exception e)
        {
            System.out.println("Something went wrong.");
        }
        byte[] array = new byte[10]; // length is bounded by 10
        new Random().nextBytes(array);
        Password = new String(array, Charset.forName("UTF-8"));

    }


    /**
     * Metoda setNumberAccesses() se poate apela la inceput pentru a seta numarul de accesari al cartii
     * @param numarul de accesari corespunzator cartii cu acest ID in baza de date
     */
    public void setNumberAccesses(int NumberAccesses) {
        this.NumberAccesses = NumberAccesses;
    }
    public int getNumberAccesses() {
        return this.NumberAccesses ;
    }
    /**
     * Metoda setContent() se poate apela la inceput pentru a seta URL-ul de unde se va descarca cartea
     * @param string din baza de date care reprezinta URL ul catre o carte pdf din internet
     */
    public void setContent(String Content) {
        this.Content = Content;
    }
    /**
     * Metoda setPassword() se apeleaza inainte de apelare metodei VisualizaContentBook() si seteaza parola
     * @param string ce reprezinta parola utilizatorului care vrea sa citeasca cartea
     */
    public void setPassword(String password)
    {
        this.Password=password;
    }
    public String getPassword()
    {
        return this.Password;
    }
    /**
     * Metoda VisulizaContentBook() descarca (daca nu e descarcata deja) si cripteaza cartea dintr-un anumit url
     * In urma apelarii acestei functii va fi creat un fisier temp.txt care va avea continutul in clar al cartii
     *Fisierul temporar temp.txt ar trebui sters dupa citirea continutului sau
     */
    public void VisulizaContentBook()
    {
        new Thread(new BookCrypt(Content,this.getTitle(),getPassword())).start();
    }
}
