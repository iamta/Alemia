package ro.mta.library_project.Controllers.LibrarianControllers;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.*;
import ro.mta.library_project.DBController.BookData;
import ro.mta.library_project.DBController.DBController;
import ro.mta.library_project.DBController.TopTenBooks;
import ro.mta.library_project.People.Librarian;

import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;
import java.util.List;
import java.util.ResourceBundle;

public class TopBorrowedBooksController implements Initializable{
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

    public TopBorrowedBooksController()
    {
        ArrayList<TopTenBooks> booksList = DBController.getInstance().SelectTop("CartiImprumutate");
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
