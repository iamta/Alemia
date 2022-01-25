package ro.mta.library_project.Controllers;

import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import javafx.event.ActionEvent;
import javafx.scene.control.Button;

import java.io.IOException;

public class UIGuestController {

    @FXML
    private Button AutorButt;

    @FXML
    private Button CategorieButt;

    @FXML
    private Button TipButt;

    @FXML
    private Button TitleButt;

    @FXML
    private Button logoutButton;

    @FXML
    void AutorAction(ActionEvent event) throws IOException {
        closeStage();
        Parent parent = FXMLLoader.load(getClass().getResource("/ro/mta/library_project/SearchAutor.fxml"));
        Stage stage = new Stage(StageStyle.DECORATED);
        stage.setTitle("Login Window");
        stage.setScene(new Scene(parent));
        stage.show();
    }

    @FXML
    void CategorieAction(ActionEvent event) throws IOException {
        closeStage();
        Parent parent = FXMLLoader.load(getClass().getResource("/ro/mta/library_project/SearchCategorie.fxml"));
        Stage stage = new Stage(StageStyle.DECORATED);
        stage.setTitle("Login Window");
        stage.setScene(new Scene(parent));
        stage.show();
    }

    @FXML
    void TipAction(ActionEvent event) throws IOException {
        closeStage();
        Parent parent = FXMLLoader.load(getClass().getResource("/ro/mta/library_project/SearchTip.fxml"));
        Stage stage = new Stage(StageStyle.DECORATED);
        stage.setTitle("Login Window");
        stage.setScene(new Scene(parent));
        stage.show();
    }

    @FXML
    void TitleAcction(ActionEvent event) throws IOException {
            closeStage();
            Parent parent = FXMLLoader.load(getClass().getResource("/ro/mta/library_project/SearchTitle.fxml"));
            Stage stage = new Stage(StageStyle.DECORATED);
            stage.setTitle("Login Window");
            stage.setScene(new Scene(parent));
            stage.show();
    }
    private void closeStage() {
        ((Stage) TipButt.getScene().getWindow()).close();
    }
    @FXML
    protected void handlLogoutButtonAction() throws Exception {

        closeStage();
        Parent parent = FXMLLoader.load(getClass().getResource("/ro/mta/library_project/UILogin.fxml"));
        Stage stage = new Stage(StageStyle.DECORATED);
        stage.setTitle("Login Window");
        stage.setScene(new Scene(parent));
        stage.show();
    }
}


