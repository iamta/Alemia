package ro.mta.library_project.Controllers;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.control.SelectionMode;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import ro.mta.library_project.DBController.DBController;
import ro.mta.library_project.Models.ExtendedBook;

import java.awt.*;
import java.net.URL;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;
import java.util.ResourceBundle;

/**
 * Clasa controller pentru interfata BorrowBooksView
 *
 * @author Lupu Marcela
 */
public class BorrowBooksController{
    private int ID;
    private String Username;
    private ArrayList<ExtendedBook> booksArray;

    @FXML
    private TableView<ExtendedBook> tbData;

    @FXML
    public TableColumn<ExtendedBook, Integer> bookId;

    @FXML
    public TableColumn<ExtendedBook, String> name;

    @FXML
    public TableColumn<ExtendedBook, String> author;

    @FXML
    public TableColumn<ExtendedBook, String> type;

    @FXML
    public TableColumn<ExtendedBook, String> section;

    @FXML
    public TableColumn<ExtendedBook, String> returnDate;

    @FXML
    public TableColumn<ExtendedBook, String> code;

    @FXML
    protected Label returnLabel;

    public BorrowBooksController() {}

    /**
     * Metoda seteaza variabila ID
     *
     * @param id ID-ul utilizatorului care s-a logat
     */
    public void setID(int id)
    {
        this.ID = id;
    }

    /**
     * Metoda seteaza variabila booksArray
     *
     * @param booksArray lista de carti imprumutate
     */
    public void setBooksArray(ArrayList<ExtendedBook> booksArray)
    {
        this.booksArray = booksArray;
    }

    /**
     * Metoda seteaza variabila Username
     *
     * @param name username-ul utilizatorului care s-a logat
     */
    public void setUsername(String name)
    {
        this.Username = name;
    }

    /**
     * Metoda viewBooks() are rolul de a afisa cartile imprumuta de un anumit utilizator. In cadrul ei se completeaza campurile din tabelul cu informatiile unei carti pentru a fi afisate in interfata.
     * */
    public void viewBooks() {
        ObservableList<ExtendedBook> books = FXCollections.observableArrayList(booksArray);

        bookId.setCellValueFactory(new PropertyValueFactory<ExtendedBook, Integer>("bookId"));
        name.setCellValueFactory(new PropertyValueFactory<ExtendedBook, String>("name"));
        author.setCellValueFactory(new PropertyValueFactory<ExtendedBook, String>("author"));
        type.setCellValueFactory(new PropertyValueFactory<ExtendedBook, String>("type"));
        section.setCellValueFactory(new PropertyValueFactory<ExtendedBook, String>("section"));
        returnDate.setCellValueFactory(new PropertyValueFactory<ExtendedBook, String>("returnDate"));
        code.setCellValueFactory(new PropertyValueFactory<ExtendedBook, String>("borrowCode"));
        //add your data to the table here.
        tbData.setItems(books);

        tbData.getSelectionModel().setSelectionMode(
                SelectionMode.MULTIPLE
        );
    }

    /**
     * Metoda returnBook(ActionEvent actionEvent) permite selectarea unui carti din tabel si afisarea unui mesaj cu codul de imprumut pentru a putea returna cartea.
     * */
    @FXML
    public void returnBook(ActionEvent actionEvent) {
        ObservableList<ExtendedBook> selectedItems = tbData.getSelectionModel().getSelectedItems();
        returnLabel.setText(this.Username + ", poti returna cartea cu codul " + selectedItems.get(0).getBorrowCode() + " si id-ul " + selectedItems.get(0).getBookId() + "!");
    }
}
