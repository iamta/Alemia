package ro.mta.library_project.Controllers.LibrarianControllers;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.layout.StackPane;
import javafx.stage.Stage;
import ro.mta.library_project.Application;
import ro.mta.library_project.DBController.DBController;
import ro.mta.library_project.DBController.TitlePagesBorrowed;
import ro.mta.library_project.DBController.TopTenBooks;
import ro.mta.library_project.People.Librarian;

import javax.swing.text.html.ImageView;
import java.awt.*;
import java.net.URL;
import java.util.ArrayList;
import java.util.ResourceBundle;

public class SeeBorrowedBooksController implements Initializable {
    @FXML
    TableColumn<TitlePagesBorrowed, String> idCarte;

    @FXML
    TableView<TitlePagesBorrowed> myTableViewSeeBooks;

    @FXML
   TableColumn<TitlePagesBorrowed, String> nrPages;

    @FXML
   TableColumn<TitlePagesBorrowed, String> titluCarte;

    private final ObservableList<TitlePagesBorrowed> booksToShow;
    public SeeBorrowedBooksController()
    {
        ArrayList<TitlePagesBorrowed> booksList = DBController.getInstance().SelectBorrowed();
        booksToShow = FXCollections.observableArrayList();
        booksToShow.addAll(booksList);
    }

    @FXML
    public void initialize(URL location, ResourceBundle resources)
    {
        idCarte.setCellValueFactory(cellData -> cellData.getValue().IDProperty());
        titluCarte.setCellValueFactory(cellData -> cellData.getValue().titleProperty());
        nrPages.setCellValueFactory(cellData -> cellData.getValue().numberPagesProperty());
        myTableViewSeeBooks.setItems(booksToShow);

    }

}
