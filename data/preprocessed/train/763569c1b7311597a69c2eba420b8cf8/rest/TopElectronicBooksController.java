package ro.mta.library_project.Controllers.LibrarianControllers;

import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.TextArea;
import javafx.stage.Stage;
import ro.mta.library_project.DBController.DBController;
import ro.mta.library_project.DBController.NewsHelper;
import ro.mta.library_project.People.Librarian;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.DatePicker;
import javafx.scene.control.TextField;

import java.io.IOException;
import java.net.URL;
import java.time.format.DateTimeFormatter;
import java.time.LocalDate;
import java.util.ResourceBundle;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.TextField;
import org.json.simple.parser.ParseException;
import ro.mta.library_project.DBController.TopTenBooks;
import java.util.ArrayList;
import java.util.List;
import javafx.scene.control.*;



public class TopElectronicBooksController implements Initializable {
    @FXML
    private ListView<String> listBooks;

        @FXML
        TableColumn<TopTenBooks, String> authorFirstname;

        @FXML
        TableColumn<TopTenBooks, String> authorLastname;

        @FXML
        TableColumn<TopTenBooks, String> borrowing;

        @FXML
        TableView<TopTenBooks> myTableViewSeeBooks;

        @FXML
        private TableColumn<TopTenBooks, String> title;
        private final ObservableList<TopTenBooks>booksToShow;

    public TopElectronicBooksController()
        {
            ArrayList<TopTenBooks> booksList = DBController.getInstance().SelectTop("CartiCitite");
            booksToShow = FXCollections.observableArrayList();
            booksToShow.addAll(booksList);
        }


        @Override
        public void initialize(URL location, ResourceBundle resources) { try {

            // VisualizeInfoBooks();
            authorFirstname.setCellValueFactory(cellData -> cellData.getValue().firstnameProperty());
            title.setCellValueFactory(cellData -> cellData.getValue().titleProperty());
            authorLastname.setCellValueFactory(cellData -> cellData.getValue().lastnameProperty());
            borrowing.setCellValueFactory(cellData -> cellData.getValue().readOrBorrowProperty());
            myTableViewSeeBooks.setItems(booksToShow);

        } catch (Exception e) {
            e.printStackTrace();
        }
        }
}

