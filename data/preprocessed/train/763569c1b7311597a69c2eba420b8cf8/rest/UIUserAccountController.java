package ro.mta.library_project.Controllers;

import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.stage.Stage;
import ro.mta.library_project.Application;
import ro.mta.library_project.Models.UserModel;
import javafx.scene.control.Label;
import ro.mta.library_project.People.User;

import java.awt.*;
import java.net.URL;
import java.util.ResourceBundle;

public class UIUserAccountController{

    @FXML
    private Label idLabel;
    @FXML
    private Label numeLabel;
    @FXML
    private Label prenumeLabel;
    @FXML
    private Label dataNastereLabel;
    @FXML
    private Label CNPLabel;
    @FXML
    private Label usernameLabel;

    private UserModel user;

    protected void setUser(UserModel user)
    {
        this.user = user;
    }

    public void showUserInfo(UserModel user)
    {
        if(user != null)
        {
            idLabel.setText(Integer.toString(user.getUserId()));
            numeLabel.setText(user.getFirstName());
            prenumeLabel.setText(user.getLastName());
            dataNastereLabel.setText(user.getBirthDate());
            CNPLabel.setText(user.getCNP());
            usernameLabel.setText(user.getUsername());
        }
        else
        {
            idLabel.setText("");
            numeLabel.setText("");
            prenumeLabel.setText("");
            dataNastereLabel.setText("");
            CNPLabel.setText("");
            usernameLabel.setText("");
        }
    }

}
