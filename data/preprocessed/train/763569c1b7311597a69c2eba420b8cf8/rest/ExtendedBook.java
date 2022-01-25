package ro.mta.library_project.Models;

import javafx.beans.property.IntegerProperty;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

/**
 * Clasa Model pentru campurile unei carti care sa fie afisate in interfata
 *
 * @author Lupu Marcela
 */
public class ExtendedBook {
    IntegerProperty bookId;
    StringProperty name;
    StringProperty author;
    StringProperty type;
    StringProperty section;
    StringProperty returnDate;
    StringProperty borrowCode;

    public ExtendedBook(int id, String name, String author, String type, String section) {
        this.bookId = new SimpleIntegerProperty(id);
        this.name = new SimpleStringProperty(name);
        this.author = new SimpleStringProperty(author);
        this.type = new SimpleStringProperty((type));
        this.section = new SimpleStringProperty(section);
    }

    public ExtendedBook(int id, String name, String author, String type, String section, String returnDate, String code) {
        this.bookId = new SimpleIntegerProperty(id);
        this.name = new SimpleStringProperty(name);
        this.author = new SimpleStringProperty(author);
        this.type = new SimpleStringProperty((type));
        this.section = new SimpleStringProperty(section);
        this.returnDate = new SimpleStringProperty(returnDate);
        this.borrowCode = new SimpleStringProperty(code);
    }

    public int getBookId() {
        return bookId.get();
    }

    public IntegerProperty bookIdProperty() {
        return bookId;
    }

    public void setBookId(int id) {
        this.bookId.set(id);
    }

    public String getName() {
        return name.get();
    }

    public StringProperty nameStringProperty() {
        return name;
    }

    public void setName(String name) {
        this.name.set(name);
    }

    public String getAuthor() {
        return author.get();
    }

    public StringProperty authorStringProperty() {
        return author;
    }

    public void setAuthor(String name) {
        this.author.set(name);
    }

    public String getType() {
        return type.get();
    }

    public StringProperty typeStringProperty() {
        return type;
    }

    public void setType(String name) {
        this.type.set(name);
    }

    public String getSection() {
        return section.get();
    }

    public StringProperty sectionStringProperty() {
        return section;
    }

    public void setSection(String name) {
        this.section.set(name);
    }

    public String getReturnDate() {
        return returnDate.get();
    }

    public StringProperty returnDateStringProperty() {
        return returnDate;
    }

    public void setReturnDate(String name) {
        this.returnDate.set(name);
    }

    public String getBorrowCode() {
        return borrowCode.get();
    }

    public StringProperty borrowCodeStringProperty() {
        return borrowCode;
    }

    public void setBorrowCode(String name) {
        this.borrowCode.set(name);
    }
}
