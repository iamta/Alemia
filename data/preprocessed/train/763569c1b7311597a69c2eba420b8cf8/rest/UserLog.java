package ro.mta.library_project.People;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * Clasa care face log-urile unui utilizator inregistrat
 *
 * @author Lupu Marcela
 */
public class UserLog extends Log {
    private  UserDatabaseDependencies userDatabaseDependencies;
    private  static  UserLog instance;

    public  static UserLog getInstance(){
        if(instance == null){
            instance = new UserLog();
        }
        return  instance;
    }

    static String filename = "UserLog.txt";

    /**
     * Metoda log(String message) primeste ca parametru un mesaj cu actiunea facuta de un utilizator si il scrie in fisierul "UserLog.txt".
     ** @param message mesajul actiunii care a fost facuta
     * */
    private  void log(String message){
        try {
            String timeStamp = new SimpleDateFormat("dd.MM.yyyy HH:mm:ss").format(new Date());

            FileWriter file = new FileWriter(filename, true);

            String str = timeStamp + " " + message + "\n";

            file.write(str);
            file.close();
        }
        catch (Exception e) {
        }
    }

    public  UserLog(){
        userDatabaseDependencies = new UserDatabaseDependencies();
    }

    /**
     * Metoda logBorrowBook(String Username, int userID, int code) primeste ca parametri username-ul, id-ul unui utilizator si codul de imprumut si scrie aceste detalii in fisier, dar face si inserarea acestora in baza de date.
     * @param Username username utilizator
     * @param userID id utilizator
     * @param code cod imprumut
     * */
    public  void logBorrowBook(String Username, int userID, int code) throws IOException {
        String details = "Utilizatorul cu id-ul " + userID + " si username-ul " + Username + "a facut o cerere de imprumut cu codul " + code;
        log(details);

        userDatabaseDependencies.insertIntoLogActions(userID, 18, details);
    }

    /**
     * Metoda logGenerateBorrowCode(String Username, int userID, int code) primeste ca parametri username-ul, id-ul unui utilizator si codul de imprumut si scrie aceste detalii in fisier, dar face si inserarea acestora in baza de date in urma generarii unui cod de imprumut.
     * @param username username utilizator
     * @param userID id utilizator
     * @param code cod imprumut
     * */
    public void logGenerateBorrowCode(String username, int userID, int code) throws IOException {
        String details = "Utilizatorul cu id-ul " + userID + " si username-ul " + username + "a generat codul " + code;
        log(details);

        userDatabaseDependencies.insertIntoLogActions(userID, 7, details);
    }

    /**
     * Metoda logSearchBook(String Username, int userID) primeste ca parametri username-ul, id-ul unui utilizator si scrie aceste detalii in fisier, dar face si inserarea acestora in baza de date in urma cautarii unei carti.
     * @param Username username utilizator
     * @param userID id utilizator
     * */
    public void logSearchBook(String Username, int userID) throws IOException {
        String details = "Utilizatorul cu id-ul " + userID + " si username-ul " + Username + "a cautat carti dupa diverse filtre:";
        log(details);

        userDatabaseDependencies.insertIntoLogActions(userID, 21, details);
    }

    /**
     * Metoda logViewBookContent(String Username, int userID, String bookName) primeste ca parametri username-ul, id-ul unui utilizator si numele unei carti si scrie aceste detalii in fisier, dar face si inserarea acestora in baza de date in urma vizualizarii continutului unei carti electronice.
     * @param Username username utilizator
     * @param userID id utilizator
     * @param bookName numele cartii al carui continut este vizualizat
     * */
    public void logViewBookContent(String Username, int userID, String bookName) throws IOException {
        String details ="Utilizatorul cu id-ul " + userID + " si username-ul " + Username + "a vizualizat/descarcat continutul cartii " + bookName;
        log(details);

        userDatabaseDependencies.insertIntoLogActions(userID, 19, details);
    }

    /**
     * Metoda searchNews(String Username, int userID, String news) primeste ca parametri username-ul, id-ul unui utilizator si numele stirii cautate si scrie aceste detalii in fisier, dar face si inserarea acestora in baza de date in urma cautarii unei stiri.
     * @param Username username utilizator
     * @param userID id utilizator
     * @param news numele stirii cautate
     * */
    public void searchNews(String Username, int userID, String news) throws IOException {
        String details = "Utilizatorul cu id-ul " + userID + " si username-ul " + Username + "a cautat stiri legate de  " + news;
        log(details);

        userDatabaseDependencies.insertIntoLogActions(userID, 20, details);
    }

    /**
     * Metoda viewAccountDetails(String Username, int userID) primeste ca parametri username-ul, id-ul unui utilizator si scrie aceste detalii in fisier, dar face si inserarea acestora in baza de date in urma alegerii din Meniu a optiunii `Vizualizare cont`.
     * @param Username username utilizator
     * @param userID id utilizator
     * */
    public void viewAccountDetails(String Username, int userID) throws IOException {
        String details = "Utilizatorul cu id-ul " + userID + " si username-ul " + Username + "a vizualizat profilul";
        log(details);

        userDatabaseDependencies.insertIntoLogActions(userID, 25, details);
    }
}
