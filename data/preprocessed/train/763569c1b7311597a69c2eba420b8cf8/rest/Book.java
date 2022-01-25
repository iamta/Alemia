package ro.mta.library_project.Book;

import java.text.SimpleDateFormat;
import java.time.LocalDate;
/**
 * Clasa Book abstractizeaza un obiect de tip carte.
 * Defineste membrii care descriu caracteristici ale unei carti si poate afisa aceste detalii.
 *
 * @author Madalina Oltean
 */

public class  Book {
    /**
     * Descrierea membrilor
     */
    private int IdBook;
    private String Title;
    private String Author;
    private int NumberPages;
    private String Genre;
    private LocalDate PublishingDate;
    private int NumberVolumes;
    private String Type;
    private int Shelf;

    /**
     * Constructorul clasei Book
     */
    public Book()
    {

    }
    /**
     * Constructorul clasei Book initializeaza datele cartii pe care le primeste ca parametru
     * @param id-ul unei carti din baza de date
     * @param titlul cartii
     * @param autorul cartii
     * @param numarul de pagini al cartii
     * @param genul cartii
     */
    public Book(int id,String title,String author,int nr_pag,String genre)
    {
        this.IdBook=id;
        this.Title=title;
        this.Author=author;
        this.NumberPages=nr_pag;
        this.Genre=genre;
    }

    public void setTitle(String Title) {
        this.Title = Title;
    }

    public void setAuthor(String Author) {
        this.Author = Author;
    }

    public void setGenre(String Genre) {
        this.Genre = Genre;
    }

    public void setPublishingDate(LocalDate publishingDate) {
        this.PublishingDate = publishingDate;
    }
    public void setNumberVolumes(int NumberVolumes) {
        this.NumberVolumes = NumberVolumes;
    }


    public void setNumberPages(int NumberPages) {
        this.NumberPages = NumberPages;
    }
    public void setIdBook(int IdBook) {
        this.IdBook = IdBook;
    }
    public void setType(String Type) {
        this.Type = Type;
    }
    public void setShelf(int Shelf) {
        this.Shelf= Shelf;
    }

    public String getTitle() {
        return this.Title;
    }

    public String getAuthor() {
        return this.Author;
    }

    public LocalDate getPublishingDate() {
        return this.PublishingDate;
    }
    public String getGenre() {
        return this.Genre;
    }

    public int getNumberPages() {
        return this.NumberPages;
    }
    public int getIdBook() {
        return this.IdBook ;
    }
    public String getType() {
        return this.Type;
    }
    public int getShelf() {
        return this.Shelf;
    }
    public int getNumberVolumes() {
        return this.NumberVolumes;
    }

    /**
     * Metoda VisualizeGeneralInformation() afiseaza in consola informatii generale despre carte
     *
     */
    public void VisualizeGeneralInformation(){
        System.out.print(this.Title+" \nAuthor: "+this.Author+" \nPublishingDate: "+this.PublishingDate+" \nGenre: "+this.Genre+
                " \nNumber of Pages: "+this.NumberPages+" \n");
    }

}
