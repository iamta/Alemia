package ro.mta.library_project.Controllers.LibrarianControllers;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.TextField;
import ro.mta.library_project.People.Librarian;

import java.io.IOException;

public class AddBookController {

    @FXML
    TextField title_book;
    @FXML
    TextField firstname_author;
    @FXML
    TextField secondname_author;
    @FXML
    TextField pages;
    @FXML
    TextField publishdate;
    @FXML
    TextField acquisitiondate;
    @FXML
    TextField type_book;
    @FXML
    TextField section_book;

    public AddBookController() {}


    @FXML
    private void doAddBook(ActionEvent actionEvent) throws IOException {
        Librarian l=new Librarian(9,"Bibliotecar1");
        String title="";
        String firstnameAuthor="";
        String secondnameAuthor="";
        String nrpages="";
        String publishDate="";
        String acquisitionDate="";
        String type="";
        String section="";
        if (title_book.getText() != null && !title_book.getText().isEmpty()) {
            if (firstname_author.getText() != null && !firstname_author.getText().isEmpty()) {
                if (secondname_author.getText() != null && !secondname_author.getText().isEmpty()) {
                    if (pages.getText() != null && !pages.getText().isEmpty()) {
                        if (publishdate.getText() != null && !publishdate.getText().isEmpty()) {
                            if (acquisitiondate.getText() != null && !acquisitiondate.getText().isEmpty()) {
                                if (type_book.getText() != null && !type_book.getText().isEmpty()) {
                                    if (section_book.getText() != null && !section_book.getText().isEmpty()) {
                                        title = title_book.getText();
                                        firstnameAuthor = firstname_author.getText();
                                        secondnameAuthor = secondname_author.getText();
                                        nrpages = pages.getText();
                                        publishDate = publishdate.getText();
                                        acquisitionDate = acquisitiondate.getText();
                                        type = type_book.getText();
                                        section = section_book.getText();
                                        l.AddBook(title, firstnameAuthor, secondnameAuthor, nrpages, publishDate, acquisitionDate, type, section);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
