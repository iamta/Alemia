package ro.mta.library_project.Controllers.LibrarianControllers;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import org.json.simple.parser.ParseException;
import ro.mta.library_project.DBController.DBController;
import ro.mta.library_project.DBController.IDTitleBook;
import ro.mta.library_project.People.Librarian;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class DestroyBookController{
    DBController dbc;

    private static String Username;
    private static int ID;

    public static void setUsername(String username)
    {
        Username=username;
    }
    public static void setID(int id)
    {
        ID=id;
    }


    public DestroyBookController()
    {
        dbc  = DBController.getInstance();
    }
    @FXML
    private ListView<String> listOfBooks;

    @FXML
    public TextField id_delete;

    @FXML
    private void print(final ActionEvent event) throws IOException, ParseException, InterruptedException {
        ArrayList<IDTitleBook> books=dbc.SelectIDTitleBook();
        ObservableList listBooks = FXCollections.observableArrayList();
        List<String> stringList = new ArrayList<>();
        for (int i = 0; i < books.size(); i++)
            stringList.add(String.valueOf(books.get(i).getBookId())+"   "+books.get(i).getTitle());

        listBooks.setAll(stringList);
        listOfBooks.getItems().addAll(listBooks);
    }

    @FXML
    private void delete(final ActionEvent event) throws IOException, ParseException, InterruptedException {
        Librarian l=new Librarian(ID,Username); //de modificat
        if (id_delete.getText() != null && !id_delete.getText().isEmpty()) {
            l.DestroyBook(id_delete.getText());
            id_delete.setText("");
        }
    }
}

