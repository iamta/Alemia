package ro.mta.library_project.People;

import ro.mta.library_project.DBController.DBController;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class LibrarianLog extends Log {

    static String filename = "logLibrarian.txt";

    public static void init() throws IOException {
        File myObj = new File(filename);
        if (myObj.createNewFile()) {
            System.out.println("File created: " + myObj.getName());
        } else {
            System.out.println("File already exists.");
        }
    }

    public static void logCreateAccount(int ID, String LibrarianUsername, String Nume, String Prenume, String Data, String CNP,String  Username, int Rol) throws Exception {
        String timeStamp = new SimpleDateFormat("dd.MM.yyyy HH:mm:ss").format(new Date());

        FileWriter f = new FileWriter(filename, true);

        String str = timeStamp + " | Creare cont | Bibliotecarul " + LibrarianUsername + " a creat un cont cu urmatoarele informatii: nume-" + Nume + ", prenume-" +
                Prenume+ ", data nasterii-"+ Data+", CNP-" + CNP+ ", username-" + Username + ", rol-" + Rol + "\n";

        String detalii = " Bibliotecarul " + LibrarianUsername + " a creat un cont cu urmatoarele informatii: nume-" + Nume + ", prenume-" +
                Prenume+ ", data nasterii-"+ Data+", CNP-" + CNP+ ", username-" + Username + ", rol-" + Rol;

        f.write(str);
        f.close();

        DaoPeopleLogs.logCreateAccount(ID, Rol, detalii);
    }


    public static void LogBorrowBook(int ID,String librarianUsername,String username,String dataReturn) throws Exception {
        String timeStamp = new SimpleDateFormat("dd.MM.yyyy HH:mm:ss").format(new Date());

        FileWriter f = new FileWriter(filename, true);

        String str =  "Bibliotecarul " + librarianUsername + " a efectuat un imprumut catre user-"+username+". Data retur: "+dataReturn.substring(0,10)+" ";
        String filestr=timeStamp + " | Imprumut carte |"+str+"\n";
        f.write(filestr);
        f.close();

        DBController dbc=DBController.getInstance();
        dbc.LoguriActiuniInsert(ID,9,str);

    }

    public static void LogDeleteBook(int ID,String librarianUsername,String idBook) throws Exception {
        String timeStamp = new SimpleDateFormat("dd.MM.yyyy HH:mm:ss").format(new Date());

        FileWriter f = new FileWriter(filename, true);

        String str = "Bibliotecarul " + librarianUsername + " a distrus cartea cu ID "+idBook+" ";
        String filestr=timeStamp + " | Distrugere carte | "+str+"\n";
        f.write(filestr);
        f.close();

        DBController dbc=DBController.getInstance();
        dbc.LoguriActiuniInsert(ID,14,str);

    }

    public static void LogSearchBook(int ID,String librarianUsername,String input,int type) throws Exception {
        String timeStamp = new SimpleDateFormat("yyy-MM-dd").format(new Date());

        FileWriter f = new FileWriter(filename, true);
        String str;
        if(type==1) {
            str = "Bibliotecarul " + librarianUsername + " a cautat carti cu titlul " + input;

        }else if(type==2){
            str = "Bibliotecarul " + librarianUsername + " a cautat carti de la autorul " + input;
        }else if(type==3){
            str = "Bibliotecarul " + librarianUsername + " a cautat carti de " + input;
        }else if(type==4){
            str = "Bibliotecarul " + librarianUsername + " a cautat carti care au aparut in data de " + input;
        }else{
            return;
        }
        String filestr=timeStamp + " | Cautare carte | "+str +"\n" ;
        f.write(filestr);
        f.close();

        DBController dbc=DBController.getInstance();
        dbc.LoguriActiuniInsert(ID,16,str);

    }

    public static void logAddBook(int ID, String LibrarianUsername, String titlu, String autor) throws Exception {
        String timeStamp = new SimpleDateFormat("dd.MM.yyyy HH:mm:ss").format(new Date());

        FileWriter f = new FileWriter(filename, true);

        String str = timeStamp + " | Adaugare Carte | Bibliotecarul " + LibrarianUsername + " a adaugat cartea "+titlu+" scrisa de "+autor+"\n";

        String detalii = "Bibliotecarul " + LibrarianUsername + " a adaugat cartea "+titlu+" scrisa de "+autor+" ";

        f.write(str);
        f.close();

        DBController dbc=DBController.getInstance();
        dbc.LoguriActiuniInsert(ID,4,detalii);
    }
}


