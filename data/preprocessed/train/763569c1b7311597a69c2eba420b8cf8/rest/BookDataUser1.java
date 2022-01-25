package ro.mta.library_project.DBController;

public class BookDataUser1 {
    int ID;
    String title;
    int idAuthor;
    String firstname; //al autorului
    String lastname; //al autorului
    String section;
    String type;
    public BookDataUser1(int ID, String title,int idAuthor, String firstname, String lastname, String section, String type)
    {
        this.ID=ID;
        this.firstname=firstname; //ale autorului
        this.lastname=lastname; //ale autorului
        this.idAuthor=idAuthor;
        this.section=section;
        this.title=title;
        this.type=type;
    }

    public void setID(int ID) {
        this.ID = ID;
    }

    public int getID() {
        return ID;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public String getTitle() {
        return title;
    }

    public void setLastname(String lastname) {
        this.lastname = lastname;
    }

    public String getLastname() {
        return lastname;
    }

    public int getIdAuthor() {
        return idAuthor;
    }

    public String getFirstname() {
        return firstname;
    }

    public String getSection() {
        return section;
    }

    public void setSection(String section) {
        this.section = section;
    }

    public void setFirstname(String firstname) {
        this.firstname = firstname;
    }

    public void setIdAuthor(int idAuthor) {
        this.idAuthor = idAuthor;
    }

    public String getType() {
        return type;
    }

    public void setType(String type) {
        this.type = type;
    }
}
