package ro.mta.library_project.Controllers;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import ro.mta.library_project.Controllers.AdminControllers.UIAdminController;
import ro.mta.library_project.People.DaoPeopleLogs;
import ro.mta.library_project.People.IPerson;
import ro.mta.library_project.People.Unregistered;

import java.io.IOException;

/**
 * Clasa controller pentru interfata Login
 *
 * @author Cioaca Andrei
 */
public class UILoginController {
    @FXML
    protected TextField username;
    @FXML
    protected PasswordField password;
    @FXML
    protected Label titleLabel;

    private Parent root;

    private int ID;
    private int rol;
    private String Username;

    /**
     * Metoda se ocupa de logare si apeleaza metoda loadUI daca credentialele sunt corecte
     */
    @FXML
    protected void handleLoginButtonAction(ActionEvent event) throws Exception {
        titleLabel.setText("Login UI");
        titleLabel.setStyle("-fx-background-color:#21242b; -fx-text-fill:white");

        String sUsername = username.getText();
        String sPassword = password.getText();

        if (!sUsername.isEmpty() && !sPassword.isEmpty()) {
            int out = DaoPeopleLogs.verifyAccount(sUsername, sPassword);

            if (out == 4) {
                titleLabel.setText("Credentiale incorecte");
                titleLabel.setStyle("-fx-background-color:#373c48; -fx-text-fill:white");
            } else {
                ID = out / 10;
                rol = out % 10;

                closeStage();
                loadUI(event, sUsername);
            }
        } else {
            titleLabel.setText("Introduceti username-ul si parola");
            titleLabel.setStyle("-fx-background-color:#373c48; -fx-text-fill:white");
        }
    }

    /**
     * Metoda se ocupa de afisarea interfetei Guest
     */
    @FXML
    protected void handleGuestButtonAction(ActionEvent event) throws IOException {
        IPerson p = new Unregistered();
        Node node = (Node) event.getSource();
        Stage stage = (Stage) node.getScene().getWindow();
        stage.close();

        FXMLLoader loader = new FXMLLoader(getClass().getResource("/ro/mta/library_project/UIGuest.fxml"));
        root = loader.load();

        stage.setUserData(p);
        Scene scene = new Scene(root);
        stage.setScene(scene);
        stage.show();
    }

    /**
     * Metoda inchide aplicatia
     */
    @FXML
    protected void handleExitButtonAction() {
        System.exit(0);
    }

    /**
     * Metoda inchide fereastra actuala
     */
    private void closeStage() {
        ((Stage) username.getScene().getWindow()).close();
    }

    /**
     * Metoda afiseaza una din interfetele Admin, Librarian sau User in functie de rol-ul dat de
     * metoda handleLoginButtonAction
     *
     * @param Username username-ul contului cu care s-a logat utilizatorul
     */
    @FXML
    void loadUI(ActionEvent event, String Username) throws Exception {
        Node node = (Node) event.getSource();
        Stage stage = (Stage) node.getScene().getWindow();
        stage.close();

        FXMLLoader loader;

        switch (rol) {
            case 1:
                DaoPeopleLogs.logLogin(ID);

                loader = new FXMLLoader(getClass().getResource("/ro/mta/library_project/AdminViews/UIAdmin.fxml"));
                root = loader.load();
                stage.setTitle("Admin Window");

                UIAdminController uiAdminController = loader.getController();
                uiAdminController.setID(ID);
                uiAdminController.setUsername(Username);

                break;

            case 2:
                loader = new FXMLLoader(getClass().getResource("/ro/mta/library_project/UILibrarian.fxml"));
                root = loader.load();
                stage.setTitle("Librarian Window");

                UILibrarianController uiLibrarianController = loader.getController();
                uiLibrarianController.setID(ID);
                uiLibrarianController.setUsername(Username);

                break;

            default:
                loader = new FXMLLoader(getClass().getResource("/ro/mta/library_project/UIUser.fxml"));
                root = loader.load();
                stage.setTitle("User Window");


                // pt a trimite valori cand apare fxml-ul
                UIUserController registeredUserController = loader.getController();
                registeredUserController.setID(ID);
                registeredUserController.setUsername(Username);

                break;
        }

        Scene scene = new Scene(root);
        stage.setScene(scene);
        stage.show();
    }
}

