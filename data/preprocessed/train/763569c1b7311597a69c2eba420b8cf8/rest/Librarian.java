package ro.mta.library_project.People;

import ro.mta.library_project.DBController.BookLocation;
import ro.mta.library_project.DBController.DBController;
import ro.mta.library_project.DBController.TopTenBooks;
import ro.mta.library_project.Shelf_sections.Shelf;

import java.sql.ResultSet;
import java.util.Scanner;
import java.util.ArrayList;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.sql.SQLException;

public class Librarian extends User {
    DBController dbc = DBController.getInstance();

    public Librarian(int id, String username) {
        this.id = id;
        this.username = username;
    }

    public Librarian() {
    }

    @Override
    public int getID() {
        return this.id;
    }

    public String getUsername() {
        return this.username;
    }

    @Override
    public void modifySection() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    ;

    @Override
    public void eraseAccount() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    ;

    @Override
    public void createAccount() {
        throw new UnsupportedOperationException("Not supported yet.");
    }

    ;


    @Override
    public void showMenu() throws Exception {
        String response = "yes";
        String input;
        int choice;
        while (response.equals("yes")) {
            System.out.println("---Sunteti in contul de bibliotecar----\nVreau sa:");
            System.out.println("1) Creez cont de utilizator;");
            System.out.println("2) Vizualizez detalii sectiuni si rafturi pe raftul unde e o carte data dupa id;");
            System.out.println("3) Imprumut carte unui client dupa cod;");
            System.out.println("4) Returnare carte dupa cod;");
            System.out.println("5) Vizualizez informatii despre carti date dupa id;");
            System.out.println("6) Cautare carte dupa diverse filtre;");
            System.out.println("7) Cases carte;");
            System.out.println("8) Adaugare carte;");
            System.out.println("9) Afisare detalii despre propriul cont;");
            System.out.println("10) Afisare detalii despre carti aflate in imprumut;");
            //System.out.println("11) Afisare detalii despre carti inca nereturnate;");
            System.out.println("12) Afisare top al celor mai accesate carti electronice;");
            System.out.println("13) Afisare top al celor mai imprumutate carti;");
            System.out.println("14) Te mai putem ajuta cu ceva (delogare implicita)? yes/no;");

            Scanner keyboard = new Scanner(System.in);
            System.out.println("\tIntrodu optiunea pe care ti-o doresti:");
            choice = keyboard.nextInt();
            keyboard.nextLine();
            if (choice == 1) {
                System.out.println("Introdu prenumele :");
                String secondName = keyboard.nextLine();

                System.out.println("Introdu numele :");
                String firstName = keyboard.nextLine();

                System.out.println("Introdu data nasterii AAAA-LL-ZZ :");
                String birthDate = keyboard.nextLine();

                System.out.println("Introdu CNP (13 cifre):");
                String CNP = keyboard.nextLine();

                System.out.println("Introdu username :");
                String username = keyboard.nextLine();

                System.out.println("Introdu parola :");
                String password = keyboard.nextLine();

                AddUserByLibrarian(secondName, firstName, birthDate, CNP, username, password);

            } else if (choice == 2) {
                ShowBooks();
                System.out.println("Introdu id-ul cartii:");
                String id = keyboard.nextLine();

                PrintLocationOfBook(id);

            } else if (choice == 3) {
                System.out.println("Introduceti codul de imprumut:");
                String code = keyboard.nextLine();

                BorrowBook(code);

            } else if (choice == 4) {
                System.out.println("Introduceti codul de return:");
                String id = keyboard.nextLine();

                ReturnBook(id);

            } else if (choice == 5) {
                ShowBooks();
                System.out.println("Introdu id-ul cartii care trebuie sa fie afisata:");
                String id = keyboard.nextLine();

                PrintInformationBook(id);

            } else if (choice == 6) {
                System.out.println("Vreau sa caut o carte dupa:\n 1) Titlu \n 2) Autor \n 3) Tip (Carte electronica/Carte fizica/Document arhiva) \n 4) An Aparitie AAAA-LL-ZZ");
                System.out.println("\tAlege criteriul de cautare al cartii: ");
                int choic = keyboard.nextInt();
                keyboard.nextLine();
                System.out.println("\tIntrodu optiunea de cautare: ");
                input = keyboard.nextLine();

                SearchBook(input, choic);

            } else if (choice == 7) {
                ShowBooks();
                System.out.println("Introdu id-ul cartii care trebuie sa fie casata:");
                String id = keyboard.nextLine();

                DestroyBook(id);

            } else if (choice == 8) {
                System.out.println("Introdu titlul :");
                String title = keyboard.nextLine();

                System.out.println("Introdu nume autor :");
                String firstnameAuthor = keyboard.nextLine();

                System.out.println("Introdu prenume autor :");
                String secondnameAuthor = keyboard.nextLine();

                System.out.println("Introdu numar de pagini :");
                String nrpages = keyboard.nextLine();

                System.out.println("Introdu data publicarii AAAA-LL-ZZ :");
                String publishDate = keyboard.nextLine();

                System.out.println("Introdu data achizitiei AAAA-LL-ZZ :");
                String acquisitionDate = keyboard.nextLine();

                System.out.println("Introdu tipul cartii 1-carte electronica, 2-carte fizica, 3-document arhiva:");
                String type = keyboard.nextLine();

                System.out.println("Introdu sectiunea: 1-beletristica, 2-manuale, 3-atlase, 4-diploma, 5-disertatie, 6-doctorat:");
                String section = keyboard.nextLine();

                AddBook(title, firstnameAuthor, secondnameAuthor, nrpages, publishDate, acquisitionDate, type, section);
            } else if (choice == 9) {

                PrintAccountDetails();

            } else if (choice == 10) {

                seeBorrowedBook();

            } else if (choice == 11) {

                seeNotReturnedBooks();

            } else if (choice == 12) {

                seeTopElectronicBooks();
            } else if (choice == 13) {

                seeTopBorrowedBooks();
            } else if (choice == 14) {
                response = keyboard.nextLine();
                if (response.equals("no")) {
                    System.out.println("La revedere!\n");
                }
                DaoPeopleLogs.logLogout(getID());
            }
        }
        System.out.println("--------------------------------------");
    }

    void ShowBooks() {
        try {
            ResultSet books = null;
            books = dbc.Select("Carti");
            try {
                while (books.next()) {
                    System.out.print("ID :" + books.getString(1) + "  Titlu: " + books.getString(2) + "\n");
                }
            } catch (Exception e) {
                System.out.println("Nu reusim sa cautam in baza de date  pentru detaliicarte.");
            }
        } catch (Exception e) {
            System.out.println("Nu putem insera gasi carti!\n");
        }
    }

    public ArrayList<TopTenBooks> getTopElectronicBooks() {
        ArrayList<TopTenBooks> booksList = new ArrayList();
        try {

            ResultSet resultSet = dbc.SelectTopTen("CartiCitite", "NumarCitiri");
            while (resultSet.next()) {
                TopTenBooks a = new TopTenBooks(resultSet.getString("Titlu"), resultSet.getString("Prenume"),
                        resultSet.getString("Nume"), resultSet.getInt("NumarCitiri"));
                booksList.add(a);
            }

        } catch (Exception e) {
            System.out.println("eroare.");
        }
        return booksList;
    }

    @Override
    public void AddUserByLibrarian(String secondName, String firstName, String birthDate, String CNP, String username, String password) {
        //grija la valorile  pentru role, created_by, salt(l-am luat din exemplu
        //3 pentru user, 9 id pentru bibliotecar momentan asa e in baza, dupa login trebuie inlocuit cu this.id, dar nu am cums a creez eu alt librarian
        String Salt = CreateSaltAndPassword.getSalt();
        String hashedPassword = CreateSaltAndPassword.getSecurePassword(password, Salt);

        if (birthDate.matches("\\d{4}-\\d{2}-\\d{2}")) {
            birthDate = birthDate + "T00:00:00.0000000";
            if (CNP.length() == 13) {
                try {
                    boolean ok = true;
                    //verificam ca cnp-ul,username-ul sa nu se repete
                    ResultSet people = null;
                    people = dbc.Select("Persoane");
                    try {
                        while (people.next()) {
                            if (people.getString(5).equals(CNP) || people.getString(6).equals(username)) {
                                ok = false;
                                break;
                            }
                        }
                    } catch (Exception e) {
                        System.out.println("Nu reusim sa cautam in baza de date  pentru detalii persoane.");
                    }
                    if (ok == true) {
                        dbc.PersonInsert(secondName, firstName, birthDate, CNP, username, hashedPassword, "3", String.valueOf(this.id), Salt);
                        LibrarianLog.logCreateAccount(this.id, this.username, secondName, firstName, birthDate, CNP, username, 3);
                    } else
                        System.out.println("CNP-ul si username-ul se repeta.Mai incercati.");
                } catch (Exception e) {
                    System.out.println("Nu putem insera persoana!\n");
                }
            } else
                System.out.println("CNP incorect!\n");
        } else
            System.out.println("Data de nastere nu este intr-un format corespunzator!\n");
        System.out.println("--------------------------------------");
    }


    @Override
    public void PrintLocationOfBook(String id_book) {
        String id_shelf = "1";
        String id_section = "1";
        try {
            ResultSet book = null;
            book = dbc.Select("Carti", "ID", id_book);
            if (book.next()) {
                System.out.println("\tCartea este pe raftul: " + book.getString(9));
                id_shelf = book.getString(9);
                System.out.println("\tSi pe sectiunea: " + book.getString(10));
                id_section = book.getString(10);

                try {
                    ResultSet shelf = null;
                    shelf = dbc.Select("Rafturi", "ID", id_shelf);
                    if (shelf.next()) {
                        System.out.println("\tNumarul total de locuri al raftului este: " + shelf.getString(2));
                        System.out.println("\tNumarul de locuri libere ale raftului este: " + shelf.getString(3));
                    }
                } catch (Exception e) {
                    System.out.println("\tRaft inexistent.");
                }
            }
        } catch (Exception e) {
            System.out.println("\tNu gasim cartea.");
        }
        System.out.println("--------------------------------------");
    }

    public BookLocation GetLocationOfBook(String id_book) {
        BookLocation b=new BookLocation(0,0,0,0,"");
        String id_shelf = "1";
        String id_section = "1";
        try {
            ResultSet book = null;
            book = dbc.Select("Carti", "ID", id_book);
            if (book.next()) {
                id_shelf = book.getString(9);
                id_section = book.getString(10);

                try {
                    ResultSet shelf = null;
                    shelf = dbc.Select("Rafturi", "ID", id_shelf);
                    if (shelf.next()) {
                        b.setID(Integer.parseInt(id_book));
                        b.setRaft(Integer.parseInt(id_shelf));
                        b.setFreeLocations(Integer.parseInt(shelf.getString(3)));
                        b.setTotalLocations(Integer.parseInt(shelf.getString(2)));
                    }
                } catch (Exception e) {
                    System.out.println("\tRaft inexistent.");
                }
                try {
                    ResultSet section = null;
                    section = dbc.Select("Sectiuni", "ID", id_section);
                    if (section.next()) {
                        b.setSections(section.getString(2));
                    }
                } catch (Exception e) {
                    System.out.println("\tSectiune inexistenta.");
                }
            }
        } catch (Exception e) {
            System.out.println("\tNu gasim cartea.");
        }
        return b;
    }


    @Override
    public void BorrowBook(String code)
    {
        //iau din cerereimprumut dupa code cererea in care obtin informatiile despre username, datarequest,cartefizica(id-ul ei)
        //code=4
        String username="";
        String dataRequest="";
        String idBook="";
        String typeBook="";
        String volumes="";
        String id_shelf="1";
        boolean ok=false;
        try {
            ResultSet requests= null;
            requests = dbc.Select("CereriImprumut", "Cod", code);
            while(requests.next()) {
                ok=true;
                username=requests.getString(2);
                dataRequest=requests.getString(3);
                idBook=requests.getString(5);
            }
        }
        catch(Exception e){
            System.out.println("Nu am gasit cererea.");
        }
        //ca sa vedem ca e fizica
        try {
            ResultSet requests= null;
            requests = dbc.Select("Carti", "ID", idBook);
            if(requests.next()) {
                typeBook=requests.getString(7);
                volumes=requests.getString(8);
                id_shelf=requests.getString(9);
            }
        }
        catch(Exception e){
            System.out.println("Nu am gasit cartea.");
        }
        //verificarea sa fie carte fizica
        if(ok==true & typeBook.equals("2")) {
            //inserez in imprumuturi: username, datarequestul, data returului: il intreb pe utilizator, id carte,
            // data retur real lasam  null, stare, scriu observatie eu, id-ul bibliotecarului
            System.out.println("Introduceti data returului sub forma AAAA-LL-ZZ: ");
            Scanner keyboard = new Scanner(System.in);
            String input = keyboard.nextLine();
            if (input.matches("\\d{4}-\\d{2}-\\d{2}")) {
                input = input + "T00:00:00.0000000";
                try {
                    String a=Integer.toString(this.id);
                    dbc.BorrowInsertHash(username,dataRequest,input,idBook,"","1",a,code);
                    LibrarianLog.LogBorrowBook(this.id,this.username,username,input);
                }
                catch(Exception e){
                    System.out.println("Nu putem face imprumutul.");
                }

                //updatez la numar de volume in Carti, dupa scad sau sterg cartea daca are un singur element
                try {
                    int bookid = 0;
                    bookid = Integer.parseInt(idBook);
                    if (volumes.equals("1")) {
                        Shelf s = new Shelf(bookid);
                        s.eraseBook(bookid);
                        LibrarianLog.LogDeleteBook(this.id, this.username, idBook);
                    } else {
                        int nrVolumes = Integer.parseInt(volumes);
                        nrVolumes = nrVolumes - 1;
                        try {
                            ResultSet book = null;
                            String val = String.valueOf(nrVolumes);
                            dbc.UpdateValue("Carti", "NumarVolume", val, "ID", idBook);
                        } catch (Exception e) {
                            System.out.println("\nNumarul de volume nu poate fi updatat.");
                        }
                        //updateaza Shelf-ul, adaug 1 la locuri libere
                        int idShelf = Integer.parseInt(id_shelf);
                        idShelf=idShelf+1;
                        try {
                            ResultSet book = null;
                            String val = String.valueOf(idShelf);
                            dbc.UpdateValue("Rafturi", "LocuriLibere", val, "ID", id_shelf);
                        } catch (Exception e) {
                            System.out.println("\nNumarul de locuri libere pe raft nu poate fi updatat.");
                        }
                    }
                }catch (Exception e) {
                    System.out.println("\nNu se poate schimba");
                }

            } else
                System.out.println("Data returlui introdusa incorect .");
        }
        else
            System.out.println("Cerere negasita sau nu e carte fizica.");
        System.out.println("--------------------------------------");
    }

    public void ReturnBook(String code)
    {
        //iau din cerereimprumut dupa code cererea in care obtin informatiile despre username, datarequest,cartefizica(id-ul ei)
        //code=4
        String username="";
        String dataRequest="";
        String idBook="";
        String typeBook="";
        String volumes="";
        boolean ok=false;
        try {
            ResultSet requests= null;
            requests = dbc.Select("CereriImprumut", "Cod", code);
            while(requests.next()) {
                ok=true;
                username=requests.getString(2);
                dataRequest=requests.getString(3);
                idBook=requests.getString(5);
            }
        }
        catch(Exception e){
            System.out.println("Nu am gasit cererea.");
        }
        //ca sa vedem numar volume
        try {
            ResultSet requests= null;
            requests = dbc.Select("Carti", "ID", idBook);
            if(requests.next()) {
                volumes=requests.getString(8);
            }
        }
        catch(Exception e){
            System.out.println("Nu am gasit cartea.");
        }
        //updatez la numar de volume in Carti
        int bookid = 0;
        bookid = Integer.parseInt(idBook);
        int nrVolumes = Integer.parseInt(volumes);
        nrVolumes = nrVolumes + 1;
        try {
            ResultSet book = null;
            String val = String.valueOf(nrVolumes);
            dbc.UpdateValue("Carti", "NumarVolume", val, "ID", idBook);
        } catch (Exception e) {
            System.out.println("\nNumarul de volume nu poate fi updatat.");
        }

        System.out.println("--------------------------------------");
    }

    @Override
    public void PrintInformationBook(String id)
    {
        try {
            ResultSet book=null;
            book=dbc.Select("Carti","ID",id);
            if(book.next()) {
                System.out.println("Titlul cartii este " + book.getString(2));
                //numele autorului
                try {
                    ResultSet author= null;
                    author = dbc.Select("Autori", "ID", book.getString(3));
                    if(author.next()) {
                        System.out.println("Numele autorului este: " + author.getString(2));
                        System.out.println("Prenumele autorului este: " + author.getString(3));
                    }
                }
                catch(Exception e){
                    System.out.println("Nu am gasit autorul.");
                }
                System.out.println("Numarul de pagini este " + book.getString(4));
                System.out.println("Data publicarii este " + book.getString(5));
                //la tip verific in tabela Tipuri
                try {
                    ResultSet type= null;
                    type = dbc.Select("Tipuri", "ID", book.getString(7));
                    if(type.next()) {
                        System.out.println("Tipul cartii este: " + type.getString(2));
                    }
                }
                catch(Exception e){
                    System.out.println("\tTip inexistent.");
                }
            }
            else
                System.out.println("\nNu avem acest ID");
        }
        catch (Exception e){
            System.out.println("Nu am gasit cartea.");
        }
        System.out.println("--------------------------------------");
    }

    @Override
    public void DestroyBook(String id_book)
    {
        /*//stergem toate tipurile de carti
        try {
            ResultSet book=null;
            book=dbc.Select("Carti","ID",id_book);
            if (book.next()) {
                dbc.DeleteBook(Integer.parseInt(id_book));
                LibrarianLog.LogDeleteBook(this.id,this.username,id_book);
            }
        }catch (Exception e){
            System.out.println("\nCartea e prea pretioasa ca sa fie distrusa.");
        }
        */
        try {
            int idbook=Integer.parseInt(id_book);
            Shelf s=new Shelf();
            s.eraseBook(idbook);
            //LibrarianLog.LogDeleteBook(this.id,this.username,id_book);
        }catch (Exception e){
            System.out.println("\nCartea e prea pretioasa ca sa fie distrusa.");
        }
        System.out.println("--------------------------------------");
    }

    @Override
    public void SearchBook(String input,int choic)
    {
        //1) Titlu  2) Numele autor  3) Gen=Tip 4) An Aparitie AAAA-LL-ZZ
        try {
            LibrarianLog.LogSearchBook(this.id,this.username,input,choic);
        }catch (Exception e){
            System.out.println("Eroare scriere log.");
        }

        if(choic==1) {
            try {
                ResultSet title= null;
                title = dbc.Select("Carti", "Titlu", input);
                while(title.next()) {
                    System.out.println("Cartea cu acest titlu are ID-ul: " + title.getString(1));
                }
            }
            catch(Exception e){
                System.out.println("Titlu inexistent.");
            }
        }
        else if(choic==2){
            ArrayList<String> list_authors=new ArrayList<String>();
            ArrayList<String> surnames=new ArrayList<String>();
            try {
                ResultSet author= null;
                author = dbc.Select("Autori", "Nume", input);
                while(author.next()) {
                    list_authors.add(author.getString(1));
                    surnames.add(author.getString(3));
                }
            }
            catch(Exception e){
                System.out.println("Nu am gasit autorul.");
            }
            for (int i = 0; i < list_authors.size(); i++) {
                System.out.println("Autorul cu id-ul "+list_authors.get(i)+" numit "+input+" "+surnames.get(i)+" a scris: ");
                try {
                    ResultSet book=null;
                    book=dbc.Select("Carti","Autor",list_authors.get(i));
                    while (book.next()) {
                        System.out.println("Titlul cartii este: "+ book.getString(2));
                    }
                }catch (Exception e){
                    System.out.println("\nNu am gasit carti scrise de acest autor.");
                }
            }
        }
        else if(choic==3)
        {
            String id_type="1";
            try {
                ResultSet type= null;
                type = dbc.Select("Tipuri", "NumeTip", input);
                if(type.next()) {
                    id_type=type.getString(1);
                }
            }
            catch(Exception e){
                System.out.println("\tTip inexistent.");
            }
            try {
                ResultSet book=null;
                book=dbc.Select("Carti","Tip",id_type);
                while (book.next()) {
                    System.out.println("Titlul cartii este: "+ book.getString(2));
                }
            }catch (Exception e){
                System.out.println("\nNu am gasit carti de acest tip.");
            }
        }
        else if(choic==4)
        {
            if (input.matches("\\d{4}-\\d{2}-\\d{2}")) {
                input = input + "T00:00:00.0000000";
                try {
                    ResultSet book = null;
                    book = dbc.Select("Carti", "DataPublicarii", input);
                    while (book.next()) {
                        System.out.println("Titlul cartii este: " + book.getString(2));
                    }
                } catch (Exception e) {
                    System.out.println("\nNu am gasit carti cu acest an al aparitiei.");
                }
            }
            else
                System.out.println("\tData nu a fost introdusa corespunzator.");
        }
        else
            System.out.println("\nAlegere de parametru invalida.");
        System.out.println("--------------------------------------");
    }
    public String SearchBookUI(String input,int choic)
    {
        String toReturn="";
        //1) Titlu  2) Numele autor  3) Gen=Tip 4) An Aparitie AAAA-LL-ZZ
        try {
            LibrarianLog.LogSearchBook(this.id,this.username,input,choic);
        }catch (Exception e){
            toReturn="Eroare scriere log.";
            return toReturn;
        }

        if(choic==1) {
            try {
                ResultSet title= null;
                title = dbc.Select("Carti", "Titlu", input);
                while(title.next()) {
                    toReturn+="Cartea cu acest titlu are ID-ul: " + title.getString(1)+"\n";
                }
            }
            catch(Exception e){
                toReturn="Titlu inexistent.";
                return toReturn;
            }
        }
        else if(choic==2){
            ArrayList<String> list_authors=new ArrayList<String>();
            ArrayList<String> surnames=new ArrayList<String>();
            try {
                ResultSet author= null;
                author = dbc.Select("Autori", "Nume", input);
                while(author.next()) {
                    list_authors.add(author.getString(1));
                    surnames.add(author.getString(3));
                }
            }
            catch(Exception e){
                toReturn="Nu am gasit autorul.";
                return toReturn;
            }
            for (int i = 0; i < list_authors.size(); i++) {
                toReturn+="Autorul cu id-ul "+list_authors.get(i)+" numit "+input+" "+surnames.get(i)+" a scris: "+"\n";
                try {
                    ResultSet book=null;
                    book=dbc.Select("Carti","Autor",list_authors.get(i));
                    while (book.next()) {
                        toReturn+="Titlul cartii este: "+ book.getString(2)+"\n";
                    }
                }catch (Exception e){
                    toReturn="\nNu am gasit carti scrise de acest autor.";
                    return toReturn;
                }
            }
        }
        else if(choic==3)
        {
            String id_type="1";
            try {
                ResultSet type= null;
                type = dbc.Select("Tipuri", "NumeTip", input);
                if(type.next()) {
                    id_type=type.getString(1);
                }
            }
            catch(Exception e){
                toReturn="\tTip inexistent.";
                return toReturn;
            }
            try {
                ResultSet book=null;
                book=dbc.Select("Carti","Tip",id_type);
                while (book.next()) {
                    toReturn+="Titlul cartii este: "+ book.getString(2)+"\n";
                }
            }catch (Exception e){
                toReturn="\nNu am gasit carti de acest tip.";
                return toReturn;
            }
        }
        else if(choic==4)
        {
            if (input.matches("\\d{4}-\\d{2}-\\d{2}")) {
                input = input + "T00:00:00.0000000";
                try {
                    ResultSet book = null;
                    book = dbc.Select("Carti", "DataPublicarii", input);
                    while (book.next()) {
                        toReturn+="Titlul cartii este: " + book.getString(2)+"\n";
                    }
                } catch (Exception e) {
                    toReturn="\nNu am gasit carti cu acest an al aparitiei.";
                    return toReturn;
                }
            }
            else {
                toReturn = "\tData nu a fost introdusa corespunzator.";
                return toReturn;
            }
            }
        else {
            toReturn = "\nAlegere de parametru invalida.";
            return toReturn;
        }
        return toReturn;
    }
    public void AddBook(String title, String firstnameAuthor, String secondnameAuthor, String nrpages, String publishDate,String acquisitionDate,String type,String section)
    {
        if (publishDate.matches("\\d{4}-\\d{2}-\\d{2}") & acquisitionDate.matches("\\d{4}-\\d{2}-\\d{2}")) {
            publishDate = publishDate + "T00:00:00.0000000";
            acquisitionDate=acquisitionDate+"T00:00:00.0000000";

            String authorId="";
            boolean ok=false;
            try {
                ResultSet author= null;
                author = dbc.Select("Autori", "Nume", firstnameAuthor);
                if(author.next()) {
                    ok=true;
                    authorId=author.getString(1);
                }else{
                    dbc.InsertWriter(firstnameAuthor,secondnameAuthor);
                    author = dbc.Select("Autori", "Nume", firstnameAuthor);
                    if(author.next()) {
                        ok = true;
                        authorId = author.getString(1);
                    }
                }
            }
            catch(Exception e){
                System.out.println("Nu am gasit autorul.");
            }
            //daca a gasit autorul in baza de date
            if(ok==true)
            {
                try {
                    dbc.BookInsert(title,authorId,nrpages,publishDate,acquisitionDate,type,"1","1",section,"");
                    LibrarianLog.logAddBook(id,username,title,secondnameAuthor+" "+firstnameAuthor);
                } catch (Exception e) {
                    System.out.println("\nNu am putut adauga cartea.");
                }
            }
            //update pentru shelf?
        }
        else
            System.out.println("\nFormat date introdus gresit.");
        System.out.println("--------------------------------------");

    }
    public void PrintAccountDetails(){
        try {
            System.out.println(" --- Detalii cont ---");
            ResultSet rs=dbc.Select("Persoane","ID",String.valueOf(this.id));
            if(rs.next()){
                System.out.println("ID: "+rs.getString(1));
                System.out.println("Nume: "+rs.getString(2));
                System.out.println("Prenume: "+rs.getString(3));
                System.out.println("Data Nasterii: "+rs.getString(4));
                System.out.println("CNP: "+rs.getString(5));
                System.out.println("Username: "+rs.getString(6));

            }
        }catch (Exception e){
            System.out.println("Eroare afisare detalii cont");
        }

    }


    //afiseaza informatiile despre cartile imprumutate
    public void seeBorrowedBook()
    {
        try
        {
            ResultSet borrowedBooks = dbc.InnerSelect("Carti", "Imprumuturi", "Carti.ID", "Imprumuturi.CarteFizica");
            if(borrowedBooks.next()){
                System.out.print("Title :" + borrowedBooks.getString(2)+"  ");
                System.out.print("Number of Pages: " + borrowedBooks.getInt(4)+"\n");

                /*System.out.print("Title :" + borrowedBooks.getString(2) + " \nAuthor: " + borrowedBooks.getString(3) +
                        " \nNumber of Pages: " + borrowedBooks.getInt(4) + " \nPublishingYear: " + borrowedBooks.getInt(5) +
                        " \nNumberVolumes: " + borrowedBooks.getInt(8) + "\n");*/
            }
        }
        catch (Exception e)
        {
            System.out.println("\nNu au putut fi extrase informatiile despre cartile imprumutate.");
        }
    }

    public StringBuilder seeBorrowedBooks()
    {
        StringBuilder msg=new StringBuilder();
        try
        {
            ResultSet borrowedBooks = dbc.InnerSelect("Carti", "Imprumuturi", "Carti.ID", "Imprumuturi.CarteFizica");
            while(borrowedBooks.next()){
                System.out.print("Title :" + borrowedBooks.getString(2)+"  ");
                System.out.print("Number of Pages: " + borrowedBooks.getInt(4)+"\n");
                msg.append("Title :" + borrowedBooks.getString(2)+"  ");
                msg.append("Number of Pages: " + borrowedBooks.getInt(4)+"\n");
            }
        }
        catch (Exception e)
        {
            System.out.println("\nNu au putut fi extrase informatiile despre cartile imprumutate.");
            msg.append("\nNu au putut fi extrase informatiile despre cartile imprumutate.");
        }
        return msg;
    }

    //afiseaza informatii despre cartile imprumutate care le-a depasit termenul si nu au fost returnate
    public void seeNotReturnedBooks()
    {
        Date currentDate=java.util.Calendar.getInstance().getTime();
        DateFormat dateFormat = new SimpleDateFormat("yyyy-mm-dd hh:mm:ss");
        String strDate = dateFormat.format(currentDate);

        try
        {
            ResultSet borrowedBooks = dbc.InnerSelect_twoConditions("Carti","Imprumuturi","Imprumuturi.DataReturReal",
                    "NULL","Imprumuturi.DataReturTeoretic",strDate,"Carti.ID","Imprumuturi.CarteFizica");
            if(borrowedBooks.next()) {
                System.out.print("Title :" + borrowedBooks.getString(2)+"  ");
                System.out.print("Number of Pages: " + borrowedBooks.getInt(4)+"\n");
                ;
                /*System.out.print("Title :" + borrowedBooks.getString(2) + " \nAuthor: " + borrowedBooks.getString(3) +
                        " \nNumber of Pages: " + borrowedBooks.getInt(4) + " \nPublishingYear: " + borrowedBooks.getInt(5) +
                        " \nNumberVolumes: " + borrowedBooks.getInt(8) + "\n");*/
            }
        }
        catch (Exception e)
        {
            System.out.println("\nNu au putut fi extrase informatiile despre cartile nereturnate la timp.");
        }
    }
}
