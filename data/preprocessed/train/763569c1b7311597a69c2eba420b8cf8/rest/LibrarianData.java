package ro.mta.library_project.DBController;

import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import ro.mta.library_project.People.Librarian;

public class LibrarianData {
    SimpleIntegerProperty ID;
    SimpleStringProperty lastname;
    SimpleStringProperty firtsname;
    SimpleStringProperty dateOfBirth;
    SimpleStringProperty CNP;
    SimpleStringProperty username;
    public LibrarianData(int ID,String lastname, String firstname,String date,String CNP, String username)
    {
        this.ID=new SimpleIntegerProperty(ID);
        this.lastname=new SimpleStringProperty(lastname);
        this.firtsname=new SimpleStringProperty(firstname);
        this.dateOfBirth=new SimpleStringProperty(date);
        this.CNP= new SimpleStringProperty(CNP);
        this.username=new SimpleStringProperty(username);
    }

    public LibrarianData() {

    }

    public int getID() {
        return ID.get();
    }

    public String getCNP() {
        return CNP.get();
    }

    public String getDateOfBirth() {
        return dateOfBirth.get();
    }

    public String getFirtsname() {
        return firtsname.get();
    }

    public String getLastname() {
        return lastname.get();
    }

    public String getUsername() {
        return username.get();
    }

    public void setCNP(String CNP) {
        this.CNP.set(CNP) ;
    }

    public void setDateOfBirth(String dateOfBirth) {
        this.dateOfBirth.set(dateOfBirth);
    }

    public void setFirtsname(String firstname) {
        this.firtsname.set(firstname);
    }

    public void setID(int ID) {
        this.ID.set(ID) ;
    }

    public void setLastname(String lastname) {
        this.lastname.set(lastname);
    }

    public void setUsername(String username) {
        this.username.set(username);
    }
}
