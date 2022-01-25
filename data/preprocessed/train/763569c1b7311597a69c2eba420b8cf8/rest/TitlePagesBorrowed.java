package ro.mta.library_project.DBController;

import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class TitlePagesBorrowed {
    StringProperty ID;
    StringProperty title;
    StringProperty numberPages;
    public TitlePagesBorrowed(int ID,String title, int numberPages)
    {
        this.ID=new SimpleStringProperty(Integer.toString(ID));
        this.title=new SimpleStringProperty(title);
        this.numberPages=new SimpleStringProperty(Integer.toString(numberPages));
    }

    public String getTitle()
    {
        return this.title.get();
    }
    public String getNumberPages()
    {
        return this.numberPages.get();
    }

    public String getID() {
        return ID.get();
    }

    public void setTitle(String title)
    {
        this.title=new SimpleStringProperty(title);
    }
    public void setNumberPages(int number)
    {
        this.numberPages=new SimpleStringProperty(Integer.toString(number));
    }
    public void setID(int ID)
    {
        this.ID=new SimpleStringProperty(Integer.toString(ID));
    }

    public StringProperty titleProperty() {
        return title;
    }

    public StringProperty numberPagesProperty() {
        return numberPages;
    }

    public StringProperty IDProperty() {
        return ID;
    }
}
