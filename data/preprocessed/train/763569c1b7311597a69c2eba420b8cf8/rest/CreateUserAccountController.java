package ro.mta.library_project.Controllers.LibrarianControllers;
import org.w3c.dom.Text;
import ro.mta.library_project.People.Librarian;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.DatePicker;
import javafx.scene.control.TextField;

import java.io.IOException;
import java.time.format.DateTimeFormatter;
import java.time.LocalDate;


public class CreateUserAccountController {
    //secondName
    //firstName
    //birthDate - AAAA-LL-ZZ
    //CNP
    //username
    //password


    @FXML
    TextField secondname;
    @FXML
    TextField firstname;
    @FXML
    TextField bd;
    @FXML
    TextField CNP;
    @FXML
    TextField username;
    @FXML
    TextField password;

    public CreateUserAccountController() {
    }


    @FXML
    private void doCreateUserAccount(ActionEvent actionEvent) throws IOException {
        Librarian l=new Librarian(9,"Bibliotecar1");
        String secondName="";
        String firstName="";
        String birthDate="";
        String cnp="";
        String user="";
        String pass="";
        if (secondname.getText() != null && !secondname.getText().isEmpty()) {
            if (firstname.getText() != null && !firstname.getText().isEmpty()) {
                if (CNP.getText() != null && !CNP.getText().isEmpty()) {
                    if (username.getText() != null && !username.getText().isEmpty()) {
                        if (password.getText() != null && !password.getText().isEmpty()) {
                            if (bd.getText() != null && !bd.getText().isEmpty()) {
                                birthDate = bd.getText();
                                secondName = secondname.getText();
                                firstName = firstname.getText();
                                cnp = CNP.getText();
                                user = username.getText();
                                pass = password.getText();
                                l.AddUserByLibrarian(secondName, firstName, birthDate, cnp, user, pass);

                            }
                            }
                        }
                    }
                }
            }
        }
    }
