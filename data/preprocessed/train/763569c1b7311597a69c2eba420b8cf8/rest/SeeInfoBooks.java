package ro.mta.library_project.Controllers.LibrarianControllers;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import ro.mta.library_project.DBController.BookData;
import ro.mta.library_project.DBController.DBController;


import java.io.IOException;
import java.net.URL;
import java.util.ArrayList;
import java.util.ResourceBundle;

public class SeeInfoBooks implements Initializable {
    @FXML
    TableColumn<BookData, String> ID;
    @FXML
    TableColumn<BookData, String> title;
    @FXML
    TableColumn<BookData, String> publishingDate;
    @FXML
    TableColumn<BookData, String> genre;
    @FXML
    TableColumn<BookData, String> numberPages;
    @FXML
    TableColumn<BookData, String> idAuthor;
    @FXML
    TableColumn<BookData, String> firstname;
    @FXML
    TableColumn<BookData, String> lastname;

    private final ObservableList<BookData>booksToShow;

    @FXML
    private TableView <BookData> myTableViewSeeBooks;

    public SeeInfoBooks()
    {
        ArrayList<BookData> booksList = DBController.getInstance().BookDataListing();
        booksToShow = FXCollections.observableArrayList();
        for(int i=0;i< booksList.size();i++) {
            booksToShow.add(booksList.get(i));
        }
    }



    @Override
    public void initialize(URL location, ResourceBundle resources) {
        try {

           // VisualizeInfoBooks();
            ID.setCellValueFactory(cellData -> cellData.getValue().IDProperty());
            title.setCellValueFactory(cellData -> cellData.getValue().titleProperty());
            publishingDate.setCellValueFactory(cellData -> cellData.getValue().publishingDateProperty());
            genre.setCellValueFactory(cellData -> cellData.getValue().genreProperty());
            numberPages.setCellValueFactory(cellData -> cellData.getValue().numberPagesProperty());
            idAuthor.setCellValueFactory(cellData -> cellData.getValue().idAuthorProperty());
            firstname.setCellValueFactory(cellData -> cellData.getValue().firstnameProperty());
            lastname.setCellValueFactory(cellData -> cellData.getValue().lastnameProperty());
            myTableViewSeeBooks.setItems(booksToShow);

        } catch (Exception e) {
            e.printStackTrace();
        }

    }

}
