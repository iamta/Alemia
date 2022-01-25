package ro.mta.library_project.Controllers;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ScrollPane;
import javafx.scene.control.TextArea;
import javafx.scene.layout.BorderPane;
import ro.mta.library_project.DBController.DBController;

import java.io.File;
import java.io.FileReader;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.sql.ResultSet;
import java.text.SimpleDateFormat;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;

import javafx.application.Application;
import javafx.scene.Node;
import javafx.scene.Scene;
import javafx.scene.control.ScrollPane;
import javafx.scene.text.Text;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import ro.mta.library_project.Book.BookCrypt;
import ro.mta.library_project.Book.ElectronicBook;

import java.net.URL;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;
import java.util.List;
import java.util.ResourceBundle;
import java.util.Scanner;

import javafx.stage.Stage;
import java.util.concurrent.TimeUnit;

/**
 * Clasa ViewElectronicBookController se ocupa cu afisare in interfata (fereastra UIViewElectronicBook.fxml)
 * a unei carti electronice
 * @author Madalina Oltean
 */
public class ViewElectronicBookController {
    /**
     * Descrierea membrilor
     */
    @FXML
    private Label label;

    @FXML
    private TextArea textArea;

    @FXML
    private int ID;

    @FXML
    private String passwd;
    /**
     * Metoda afiseaza() initializeaza o carte electronica,
     * ii transmite parola utilizatorului si apeleaza functia de vizualizare a cartii.
     * Citeste continutul decriptat al cartii electronice si il afiseaza intr-un textArea,
     * dupa care sterge fisierul temporar din care a citit continutul in clar al cartii.
     * @param id-ul cartii care se doreste a fi citita
     * @param parola utilizatorului, care va fi folosita in generarea unei parole pentru criptarea si decriptarea cartii
     */
    @FXML
    public void afiseaza(int id,String pass){
        try {
            this.ID=id;
            this.passwd=pass;
            ElectronicBook book=new ElectronicBook(id);
            book.setPassword(pass);
            book.VisulizaContentBook();
            TimeUnit.SECONDS.sleep(8);
            String data=" ";
            String docText=" ";
            File myObj = new File("temp.txt");
            Scanner myReader = new Scanner(myObj);
            while (myReader.hasNextLine()) {
                data = myReader.nextLine();
                docText=docText+data;
                docText=docText+"\n";
            }
            myReader.close();
            textArea.setEditable(false);
            textArea.appendText(docText);
            myObj.delete();


        }
        catch(Exception e)
        {

        }
    }

}

