package ro.mta.library_project.Controllers.LibrarianControllers;

import javafx.collections.ObservableList;
import javafx.fxml.FXMLLoader;
import javafx.scene.control.*;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.layout.AnchorPane;
import javafx.scene.text.Text;
import javafx.scene.text.TextFlow;
import ro.mta.library_project.Main;
import ro.mta.library_project.People.Librarian;

import java.io.IOException;

public class UILibrarianSearchBook {
    @FXML
    private ChoiceBox choicebox;
    @FXML
    private ObservableList<String> items;
    @FXML
    private TextField text;
    @FXML
    private ListView<String> results;
    public UILibrarianSearchBook() throws IOException {

    }

    @FXML
    private void Search(ActionEvent action)
    {
        Librarian l=new Librarian(9,"Bibliotecar1");
        choicebox.setId("choicebox");
        String val=choicebox.getSelectionModel().getSelectedItem().toString();
        int choise=0;
        if(!val.equals("Titlu") && !val.equals("Tip") && !val.equals("Anul aparitiei") && !val.equals("Autor"))
        {
            Alert alert = new Alert(Alert.AlertType.INFORMATION);

            alert.setTitle("Info");
            alert.setContentText("Selectati un filtru");
            alert.show();
            return ;
        }
        else if(val.equals("Titlu"))
        {
            choise=1;
        }
        else if(val.equals("Autor"))
        {
            choise=2;
        }
        else if(val.equals("Tip"))
        {
            choise=3;
        }
        else if(val.equals("Anul aparitiei"))
        {
            choise=4;
        }
        text.setId("text");
        String input=text.getText();
        if(input.length()<1) {
            Alert alert = new Alert(Alert.AlertType.INFORMATION);

            alert.setTitle("Info");
            alert.setContentText("Introduceti inputul");
            alert.show();
            return ;
        }

        String result=l.SearchBookUI(input,choise);

        if(result.isEmpty())
            result="Nicio potrivire";

        Alert alert = new Alert(Alert.AlertType.INFORMATION);

        alert.setTitle("Rezultat");
        alert.setHeaderText("Rezultat");
        alert.setContentText(result);
        alert.show();


    }
}
