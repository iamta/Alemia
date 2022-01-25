package ro.mta.library_project.Controllers;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import ro.mta.library_project.DBController.DBController;

import java.io.IOException;
import java.sql.ResultSet;
import java.sql.SQLException;

public class SearchTitleControler {

    @FXML
    private Button BackButton;

    @FXML
    private TextField InputText;

    @FXML
    private Label ReturnLabel;

    @FXML
    private Button SearchButton;

    @FXML
    void BackClicked(ActionEvent event) throws IOException {
        closeStage();
        Parent parent = FXMLLoader.load(getClass().getResource("/ro/mta/library_project/UIGuest.fxml"));
        Stage stage = new Stage(StageStyle.DECORATED);
        stage.setTitle("Login Window");
        stage.setScene(new Scene(parent));
        stage.show();
    }

    @FXML
    void SearchClicked(ActionEvent event) throws SQLException {
        String input = InputText.getText();

        ReturnLabel.setText(input);
//        ResultSet searchResult= DBController.getInstance().BooksListing("Titlu",input);
//
//        int gasit=0;
//        while(searchResult.next()) {
//            gasit=1;
//            ReturnLabel.setText(searchResult.getString("ID")+" "+ searchResult.getString("Titlu")+" "+searchResult.getString("Prenume")+
//                    " "+searchResult.getString("Nume")+" "+searchResult.getString("NumarPagini")+" "+searchResult.getString("Tip")+" "+searchResult.getString("Sectiune"));
//        }
//        if(gasit==0) ReturnLabel.setText("Nu avem nimic in biblioteca");
    }


    private void closeStage() {
        ((Stage) BackButton.getScene().getWindow()).close();
    }

}
