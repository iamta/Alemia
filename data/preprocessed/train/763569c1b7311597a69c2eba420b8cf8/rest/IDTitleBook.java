package ro.mta.library_project.DBController;

import javafx.beans.property.IntegerProperty;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class IDTitleBook {
    IntegerProperty id;
    StringProperty title;

    public IDTitleBook(int id, String title)
    {
        this.id = new SimpleIntegerProperty(id);
        this.title = new SimpleStringProperty(title);
    }

    public int getBookId() {
        return id.get();
    }

    public IntegerProperty bookIdProperty() {
        return id;
    }

    public void setBookId(int id) {
        this.id.set(id);
    }

    public String getTitle() {
        return title.get();
    }

    public StringProperty titleStringProperty() {
        return title;
    }

    public void setTitle(String title) {
        this.title.set(title);
    }
}
