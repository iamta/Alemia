package ro.mta.library_project.Controllers.LibrarianControllers;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.DatePicker;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import ro.mta.library_project.DBController.*;
import ro.mta.library_project.Models.UserModel;
import ro.mta.library_project.People.Librarian;

import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.ResourceBundle;


public class SeeAccountDetailsController{
    DBController dbc;
    private  String Username;
    private  int ID;

    public  void setUsername(String username)
    {
        Username=username;
    }
    public void setID(int id)
    {
        ID=id;
    }


    @FXML
    private Label idLabel;
    @FXML
    private Label usernameLabel;
    @FXML
    private Label numeLabel;
    @FXML
    private Label prenumeLabel;
    @FXML
    private Label CNPLabel;
    @FXML
    private Label dataNastereLabel;


    private LibrarianData librarian;


    public void setLibrarian(LibrarianData l)
    {
        this.librarian = l;
    }

    public void showInfo(LibrarianData lib)
    {
        if(lib != null)
        {
            LibrarianData l= DBController.getInstance().SelectLibrarian(ID);
            idLabel.setText(String.valueOf(l.getID()));
            usernameLabel.setText(l.getUsername());
            numeLabel.setText(l.getFirtsname());
            prenumeLabel.setText(l.getLastname());
            CNPLabel.setText(l.getCNP());
            dataNastereLabel.setText(l.getDateOfBirth());
        }
        else
        {
            idLabel.setText("");
            usernameLabel.setText("");
            numeLabel.setText("");
            prenumeLabel.setText("");
            CNPLabel.setText("");
            dataNastereLabel.setText("");
        }
    }
}
