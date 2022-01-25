package ro.mta.library_project.DBController;

import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class BookData {
    //-afisare id, titlu carte, id autor, nume si prenume autor,numar pagini, gen, data publicarii( sau data apritiei) pentru Book
    private StringProperty ID;
    private StringProperty title;
    private StringProperty idAuthor;
    private StringProperty firstname;
    private StringProperty lastname;
    private StringProperty numberPages;
    private StringProperty genre;
    private StringProperty publishingDate;

    public BookData(int ID, String title,int idAuthor, String firstname, String lastname,int numberPages, String genre,String publishingDate)
    {
        this.ID=new SimpleStringProperty(Integer.toString(ID));
        this.firstname=new SimpleStringProperty(firstname); //ale autorului
        this.lastname=new SimpleStringProperty(lastname); //ale autorului
        this.idAuthor=new SimpleStringProperty(Integer.toString(idAuthor));
        this.numberPages= new SimpleStringProperty(Integer.toString(numberPages));
        this.genre=new SimpleStringProperty(genre);
        this.title=new SimpleStringProperty(title);
        this.publishingDate=new SimpleStringProperty(publishingDate);
    }

    public void setID(int ID) {
        this.ID = new SimpleStringProperty(Integer.toString(ID));
    }

    public String getID() {
        return ID.get();
    }

    public void setTitle(String title) {
        this.title = new SimpleStringProperty(title);
    }

    public String getTitle() {
        return title.get();
    }

    public void setLastname(String lastname) {
        this.lastname = new SimpleStringProperty(lastname);
    }

    public String getLastname() {
        return lastname.get();
    }

    public String getIdAuthor() {
        return idAuthor.get();
    }

    public String getNumberPages() {
        return numberPages.get();
    }

    public String getFirstname() {
        return firstname.get();
    }

    public String getGenre() {
        return genre.get();
    }

    public String getPublishingDate() {
        return publishingDate.get();
    }

    public void setFirstname(String firstname) {
        this.firstname = new SimpleStringProperty(firstname);
    }

    public void setGenre(String genre) {
        this.genre = new SimpleStringProperty(genre);
    }

    public void setIdAuthor(int idAuthor) {
        this.idAuthor =new SimpleStringProperty(Integer.toString(idAuthor));
    }

    public void setNumberPages(int numberPages) {
        this.numberPages =new SimpleStringProperty(Integer.toString(numberPages));
    }

    public void setPublishingDate(String publishingDate) {
        this.publishingDate = new SimpleStringProperty(publishingDate);
    }

    public StringProperty idAuthorProperty() {
        return idAuthor;
    }

    public StringProperty firstnameProperty() {
        return firstname;
    }

    public StringProperty genreProperty() {
        return genre;
    }

    public StringProperty IDProperty() {
        return ID;
    }

    public StringProperty lastnameProperty() {
        return lastname;
    }

    public StringProperty titleProperty() {
        return title;
    }

    public StringProperty numberPagesProperty() {
        return numberPages;
    }

    public StringProperty publishingDateProperty() {
        return publishingDate;
    }
}
