package ro.mta.library_project.DBController;

import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class TopTenBooks {
    StringProperty title;
    StringProperty firstname;
    StringProperty lastname;
    StringProperty readOrBorrow;
    public TopTenBooks(String title, String firstname, String lastname, int readOrBorrow)
    {
        this.title= new SimpleStringProperty(title);
        this.firstname= new SimpleStringProperty(firstname);
        this.lastname=new SimpleStringProperty(lastname);
        this.readOrBorrow=new SimpleStringProperty(Integer.toString(readOrBorrow));
    }
    public String getTitle()
    {
        return this.title.get();
    }
    public String getFirstname()
    {
        return this.firstname.get();
    }
    public String getLastname()
    {
        return this.lastname.get();
    }
    public String getReadOrBorrow()
    {
        return this.readOrBorrow.get();
    }
    public void setTitle(String title)
    {
        this.title=new SimpleStringProperty(title);
    }

    public void setFirstname(String firstname)
    {
        this.firstname = new SimpleStringProperty(firstname);
    }

    public void setLastname(String lastname)
    {
        this.lastname = new SimpleStringProperty(lastname);
    }

    public void setReadOrBorrow(int readOrBorrow)
    {
        this.readOrBorrow = new SimpleStringProperty(Integer.toString(readOrBorrow));
    }

    public StringProperty titleProperty() {
        return title;
    }

    public StringProperty firstnameProperty() {
        return firstname;
    }

    public StringProperty lastnameProperty() {
        return lastname;
    }

    public StringProperty readOrBorrowProperty() {
        return readOrBorrow;
    }
}
