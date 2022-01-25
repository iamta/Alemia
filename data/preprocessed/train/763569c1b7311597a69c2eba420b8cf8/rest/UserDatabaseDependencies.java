package ro.mta.library_project.People;

import ro.mta.library_project.Book.Book;
import ro.mta.library_project.Book.ElectronicBook;
import ro.mta.library_project.DBController.DBController;

import java.sql.ResultSet;
import java.text.SimpleDateFormat;
import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.Date;

/**
 * Clasa este o clasa helper pentru conexiunea cu baza de date
 *
 * @author Lupu Marcela
 */
public class UserDatabaseDependencies {

    DBController dbc;

    public UserDatabaseDependencies()
    {
        dbc  = DBController.getInstance();
    }

    /**
     * Metoda insertIntoLogActions(int idUser, int idValue, String details) primeste ca parametrul id-ul unui utilizator, id-ul predefint unei actiuni, cum ar fi id-ul mesajului "Imprumutare carte", stiut de catre dezvoltator si un mesaj continand actiunea facute de utilizator.
     * Aceste informatii sunt inserate in baza de date.
     * Functia este implementata cu scopul de a fi un helper pentru clasa UserLog in care este implementata logica pentru definirea log-urilor unui utilizator.
     * */
    public void insertIntoLogActions(int idUser, int idValue, String details)
    {
        try {
            dbc.LoguriActiuniInsert(idUser, idValue, details);
        } catch (Exception e) {
            System.out.println("Something went wrong with insert into actions");
            System.out.println(e.getMessage());
        }
    }

    public ResultSet getPreviousActivity(int userId)
    {
        ResultSet set = null;
        try {
            set = dbc.InnerActiuniLoguriActiuniSelect(userId);

            //todo: add model parsing here
        } catch (Exception e) {
            System.out.println("Eroare la select din baza de date(LoguriActiuni)");
        }

        return set;
    }

    public ResultSet getUser(int userId){

        ResultSet set = null;
        try {
            set = dbc.Select("Persoane", "ID", String.valueOf(userId));

            //todo: convert this set to a model
        }
        catch (Exception e){

        }

        return set;
    }

    public  Book getBook(String bookId){
        try {
            ResultSet set = null;
            set = dbc.Select("Carti", "ID", bookId);
            while (set.next()) {
                return convertSetToBook(set);
            }
        } catch (Exception e) {
            System.out.println("Something went wrong in borrowBook");
            System.out.println(e.getMessage());
        }
        return  null;
    }

    public  ArrayList<Book> getBooks(String[] idsList){
        ArrayList<Book> books = new ArrayList<Book>();
        for (int i = 0; i < idsList.length; i++) {
            Book book = getBook((idsList[i]));

            if(book != null)
                books.add(book);
        }

        return books;
    }

    public  ArrayList<ElectronicBook>  getElectronicBooks()
    {
        ArrayList<ElectronicBook> electronicBooks = new ArrayList<ElectronicBook>();;

        try {
            ResultSet set = null;
            set = dbc.Select("Carti", "Tip", "1");
            //    System.out.println("===Carti electronice===\n");
            while (set.next()) {
                int id=set.getInt(1);
                String title=set.getString(2);
                String autor=set.getString(3);
                int nrPag=set.getInt(4);
                String genre="realist";
                String dateStr=set.getString(5);
                DateTimeFormatter formatter=DateTimeFormatter.ofPattern("yyyy-MM-dd");
                LocalDate dataPub=LocalDate.parse(dateStr,formatter);
                ElectronicBook electronicBook=new ElectronicBook(id,title,autor,nrPag,genre,dataPub);
                electronicBooks.add(electronicBook);
            }
        } catch (Exception e) {
            System.out.println("Nu exista carti electronice!");
        }

        return electronicBooks;
    }

    public  ArrayList<Book> getBooksPaged(int start, int end){
        ArrayList<Book> books = new ArrayList<Book>();
        try {
            ResultSet set = null;
            set = dbc.SelectWithinRange("Carti", start, end);
            while (set.next()) {
                books.add( convertSetToBook(set));
            }

        } catch (Exception e) {
            System.out.println("Something went wrong in viewBooks()");

        }
        return books;
    }


    public ElectronicBook getChosedElectronicBook(int id)
    {
        ArrayList<ElectronicBook> electronicBooks = getElectronicBooks();

        ElectronicBook electroBook = null;
        for (int i = 0; i < electronicBooks.size(); i++) {
            if(electronicBooks.get(i).getIdBook() == id) {
                int bookId = electronicBooks.get(i).getIdBook();
                String title = electronicBooks.get(i).getTitle();
                String author = electronicBooks.get(i).getAuthor();
                int nrPages = electronicBooks.get(i).getNumberPages();
                String genre = electronicBooks.get(i).getGenre();
                LocalDate publicationDate = electronicBooks.get(i).getPublishingDate();
                electroBook = new ElectronicBook(id, title, author, nrPages, genre, publicationDate);
            }
        }

        return electroBook;
    }

    public void selectfromBorrowedBookstable(String userId)
    {

        ArrayList<String> returnDates = new ArrayList<String>();
        try {
            ResultSet set = null;
            set = dbc.Select("Imprumuturi", "Username", userId);
            // System.out.println("===Carti electronice===\n");
            while (set.next()) {
                String date =set.getString(4);
                returnDates.add(date);
            }
        } catch (Exception e) {
            System.out.println("Nu exista carti imprumutate!");
        }
    }


    /*Converters*/

    private Book convertSetToBook(ResultSet set){
        try {
            int idBook = set.getInt(1);
            String title = set.getString(2);
            String author = set.getString(3);
            int numberOfPages = set.getInt(4);
            String genre = set.getString(7);

            return new Book(idBook, title, author, numberOfPages, genre);
        }
        catch (Exception e){
            return  null;
        }
    }

}
