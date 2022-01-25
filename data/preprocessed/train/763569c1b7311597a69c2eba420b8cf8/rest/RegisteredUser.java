package ro.mta.library_project.People;

import java.io.IOException;
import java.sql.ResultSet;
import java.text.ParseException;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.*;

import ro.mta.library_project.Book.Book;
import ro.mta.library_project.Book.ElectronicBook;
import ro.mta.library_project.DBController.DBController;
import ro.mta.library_project.News.News;
import ro.mta.library_project.RequestsModule.BorrowRequest;

import java.util.Random;

public class RegisteredUser extends User {

    String CNP;
    String lastName;
    String firstName;
    String password;
    BorrowRequest request;

    UserDatabaseDependencies userDatabaseDependencies;

    ArrayList<Book> selectedBooks;

    public RegisteredUser(int id) {
        this.id = id;
        selectedBooks = new ArrayList<Book>();
        request = new BorrowRequest();
        userDatabaseDependencies = new UserDatabaseDependencies();
    }

    public RegisteredUser(int id, String username) {
        super(id, username);
        selectedBooks = new ArrayList<Book>();
        request = new BorrowRequest();
        userDatabaseDependencies = new UserDatabaseDependencies();
    }

    @Override
    public void AddUserByLibrarian(String secondName, String firstName, String birthDate, String CNP, String username, String password) {
        throw new java.lang.UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void PrintLocationOfBook(String id_book) {
        throw new java.lang.UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void BorrowBook(String code) {
        throw new java.lang.UnsupportedOperationException("Not supported yet.");
    }


    @Override
    public void PrintInformationBook(String title) {
        throw new java.lang.UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void DestroyBook(String id) {
        throw new java.lang.UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void createAccount() {
        throw new java.lang.UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void eraseAccount() {
        throw new java.lang.UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void modifySection() {
        throw new java.lang.UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public void SearchBook(String input, int opt) {
        throw new java.lang.UnsupportedOperationException("Not supported yet.");
    }

    @Override
    public int getID() {
        return this.id;
    }

    public String getUsername() {
        return this.username;
    }



    @Override
    public void showMenu() throws Exception {
        System.out.println("=====User=====\n");
        System.out.println("Bine ai venit in contul tau\n");

        boolean ok = true;

        while (ok) {
            System.out.println("\n=====Alege ce doresti sa faci=====\n");
            System.out.println("1.Afisare detalii cont");
            System.out.println("2.Vizualizare carti disponibile");
            System.out.println("3.Cautare carte dupa diverse filtre");
            System.out.println("4.Imprumutare carte");
            System.out.println("5.Vizualizare jurnal cu activitate anterioara");
            System.out.println("6.Citire carte in format electronic");
            System.out.println("7.Vizualizare stiri");
            System.out.println("8.Returnare carte");
            System.out.println("9.Editare detalii cont");
            System.out.println("10.Logout");

            Scanner scanner = new Scanner(System.in);
            int option = scanner.nextInt();

            switch (option) {
                case 1:
                    System.out.println("=====Detalii cont=====\n");
                    printAccountData();
                    break;
                case 2:
                    System.out.println("=====Cartile disponibile in acest moment sunt afisate mai jos:=====\n");
                    //apeleaza functie care afiseaza cartile
                    viewBooks();
                    break;
                case 3:
                    System.out.println("=====Cauta carte dupa:=====\n");
                    System.out.println("Optiunea\tFiltru");
                    System.out.println("1.\tTitlu");
                    System.out.println("2.\tAutor");
                    System.out.println("3.\tTip (Carte electronica/Carte fizica/Document arhiva)");
                    System.out.println("4.\tSectiune");

                    System.out.println("Introduceti optiunea de cautare al cartii(1,2,3,4): ");
                    int choice = scanner.nextInt();
                    scanner.nextLine();

                    SearchBook(choice);
                    break;
                case 4:
                    borrowBooks();
                    break;
                case 5:
                    System.out.println("Jurnalul cu activitatea anterioara:\n");
                    viewPreviousActivity();
                    break;
                case 6:
                    System.out.println("Alege cartea pe care doresti sa o citesti in format electronic:\n");
                    readElectronicBook();
                    break;
                case 7:
                    System.out.println("Afisare stiri");
                    showNews();
                case 8:
                    System.out.println("Esti sigur ca doresti sa returnezi cartea\n");
                    break;
                case 9:
                    System.out.println("Ce informatii doriti sa editati?");
                case 10:
                    DaoPeopleLogs.logLogout(getID());
                default:
                    DaoPeopleLogs.logLogout(getID());
                    ok = false;
                    break;
            }
        }
    }

    public void printAccountData() {
        System.out.println("\n=====BEGIN account data details======\n");
        try {
            ResultSet set = userDatabaseDependencies.getUser(this.getID());
            while (set.next()) {
                System.out.println("Id: " + set.getString(1) + "\t Nume: " + set.getString(2) + "\t Prenume: " + set.getString(3) + "\t Data nasterii: " + set.getString(4) + "\t CNP: " + set.getString(5) + "\t Username: " + set.getString(6));
            }
        } catch (Exception e) {
            System.out.println("Something went wrong in PrintAccount function select");

        }
        System.out.println("\n=====END account data details======\n\n");
    }

    public void viewBooks() {
        System.out.println("=====BEGIN view books======\n");

        Scanner scanner = new Scanner(System.in);

        String response = "da";
        int start = 1;
        int end = 2;
        int step = 2;
        while("da".equals(response))
        {
            //apeleaza functia de vizualizare carte
            System.out.println("Vizualizare carti\n");
            ArrayList<Book> books = userDatabaseDependencies.getBooksPaged(start, end);

            if(books.size() == 0) break;;

            for(int i = 0; i < books.size(); i++)
                System.out.println("Id: " + books.get(i).getIdBook() + "\t Titlu: " + books.get(i).getTitle() + "\t Autor: " + books.get(i).getAuthor());

            start += step;
            end += step;

            System.out.println("Doriti sa vedeti mai multe carti?(da/nu)");
            System.out.println("Va rugam sa selectati da/nu");
            response = scanner.nextLine();
        }

        System.out.println("\n=====END view books======\n\n");
    }

    public void SearchBook(int choice) throws IOException {

        DBController dbc = DBController.getInstance();
        Scanner keyboard = new Scanner(System.in);
        String input;


        UserLog.getInstance().logSearchBook(this.getUsername(),this.getID());
    }

    public void selectBooks() throws IOException {
        //selecteaza carte
        Scanner scanner = new Scanner(System.in);

        System.out.println("Doresti sa cauti o carte anume din biblioteca?(da/nu)\n");
        String response = scanner.nextLine();
        while("da".equals(response))
        {
            System.out.println("=====Cauta carte dupa:=====\n");
            System.out.println("Optiunea\tFiltru");
            System.out.println("1.\tTitlu");
            System.out.println("2.\tAutor");
            System.out.println("3.\tTip (Carte electronica/Carte fizica/Document arhiva)");
            System.out.println("4.\tSectiune");

            System.out.println("Introduceti optiunea de cautare al cartii(1,2,3,4): ");
            int choice = scanner.nextInt();
            scanner.nextLine();

            SearchBook(choice);

            System.out.println("Doresti sa cauti in continuare?(da/nu)\n");
            response = scanner.nextLine();
        }

        System.out.println("Selecteaza id-ul cartilor dorite sub forma \"id1 id2...\"");

        String idString = scanner.nextLine();
        String[] idsList = idString.split(" ");

        selectedBooks = userDatabaseDependencies.getBooks(idsList);

        System.out.println("Cartile selectate sunt afisate mai jos:\n");
        for (int i = 0; i < selectedBooks.size(); i++) {
            System.out.println(selectedBooks.get(i).getIdBook() + " " + selectedBooks.get(i).getTitle());
        }
    }

    //=====generare cod + generare cerere de imprumut=====
    int generateCode(int random_int) {
        StringBuilder builder = new StringBuilder();

        for (int i = 0; i < selectedBooks.size(); i++) {
            builder.append(selectedBooks.get(i).getIdBook() + selectedBooks.get(i).getTitle());
        }

        String result = builder.toString();

        int hashValue = Math.abs(result.hashCode());

        int hashResult = random_int * this.getID() + hashValue;

        return hashResult;
    }

    public BorrowRequest createBorrowRequest() throws IOException {
        this.request = new BorrowRequest();
        this.request.bookId = new ArrayList<Integer>();

        this.request.userId = this.id;

        //ia codul din carte si populeaza request.bookId
        for (int i = 0; i < selectedBooks.size(); i++) {
            this.request.bookId.add(selectedBooks.get(i).getIdBook());
        }
        // int random
        int min = 0;
        int max = 100000;
        Random random = new Random();
        int random_int = random.nextInt(max - min) + min;

        int hashResult = generateCode(random_int);

        System.out.println("\nHere is the hash value: ");
        System.out.println(hashResult);

        this.request.borrowCode = hashResult;

        //verific daca mai exista acelasi cod in baza de date, daca da, generez un alt cod
        try {
            DBController dbc = DBController.getInstance();
            ResultSet set = null;
            set = dbc.Select("CereriImprumut");
            while (set.next()) {
                if (set.getInt(4) == this.request.borrowCode) {
                    System.out.println("Acest cod exista deja in baza de date, se va genera alt cod\n");
                    random_int = random.nextInt(max - min) + min;
                    hashResult = generateCode(random_int);
                    this.request.borrowCode = hashResult;
                }
            }

        } catch (Exception e) {
            System.out.println("Something went wrong in visualizing CereriImprumut");
            System.out.println(e.getMessage());
        }

        //inserez informatiile pentru cererea de imprumut in baza de date
        try {
            DateTimeFormatter dtf = DateTimeFormatter.ofPattern("uuuu/MM/dd HH:mm:ss");
            LocalDateTime now = LocalDateTime.now();
            String strDate = dtf.format(now);

            //System.out.println("LoginLogoutHelperClass data: " + sqlDate);

            for (int i = 0; i < this.request.bookId.size(); i++) {

                String userId = String.valueOf(this.request.userId);
                String code = String.valueOf(this.request.borrowCode);
                String bookId = String.valueOf(this.request.bookId.get(i));
                DBController dbc = DBController.getInstance();
                dbc.BorrowRequestInsert(userId, strDate, code, bookId);
            }

        } catch (
                Exception e) {
            System.out.println("Something went wrong with insert");
            System.out.println(e.getMessage());
        }

        UserLog.getInstance().logGenerateBorrowCode(this.getUsername(), this.getID(), this.request.borrowCode);

        return this.request;
    }

    public void borrowBooks() throws IOException {
        System.out.println("\n=====BEGIN borrow books======\n");

        selectBooks();

        this.request = this.createBorrowRequest();
        String printRequest = this.request.toString();
        System.out.println("Informatiile requestului tau de a imprumuta cartile sunt:");
        System.out.print(printRequest);
        System.out.println("\n\n");
        System.out.println("\n=====END borrow books======\n\n");

        UserLog.getInstance().logBorrowBook(this.getUsername(), this.getID(), this.request.borrowCode);
    }

    public void readElectronicBook() throws IOException {

        List<ElectronicBook> electronicBooks = userDatabaseDependencies.getElectronicBooks();
        System.out.println("Cartile electronice sunt afisate mai jos:\n");
        for (int i = 0; i < electronicBooks.size(); i++) {
            System.out.println(electronicBooks.get(i).getIdBook() + " " + electronicBooks.get(i).getTitle());
        }

        Scanner scanner = new Scanner(System.in);
        System.out.println("Alege carte dupa id, introduce id-ul cartii ");
        int chosenId = scanner.nextInt();

        ElectronicBook chosenBook = userDatabaseDependencies.getChosedElectronicBook(chosenId);

        chosenBook.VisulizaContentBook();
        chosenBook.VisualizeGeneralInformation();

        UserLog.getInstance().logViewBookContent(this.getUsername(), this.getID(), chosenBook.getTitle());
    }

    public void showNews() throws IOException, ParseException, InterruptedException, org.json.simple.parser.ParseException {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Cauta stire: ");
        String newsString = scanner.nextLine();
        News news = new News();
        String jsonString = news.GetRequest(newsString);
        int numberOfNews = news.getNumberOfArticles(jsonString);
        if(numberOfNews > 0)
            news.printArticles(numberOfNews, jsonString);

        UserLog.getInstance().searchNews(this.getUsername(), this.getID(), newsString);
    }

    public void viewPreviousActivity()
    {
        ResultSet set = userDatabaseDependencies.getPreviousActivity(this.getID());
        try {
            System.out.println("====Activitate anterioara====");
            while (set.next()) {
                System.out.println("Utilizatorul cu id-ul: " + set.getString(4) + "\tActiunea: " + set.getString(2) + "\tData " + set.getString(6));
            }
        }
        catch (Exception e){
        }
    }

    public void checkDaysLeftUntilReturnBook()
    {
        // ArrayList<String> returnDates = userDatabaseDependencies.getReturnDates();
    }
}
