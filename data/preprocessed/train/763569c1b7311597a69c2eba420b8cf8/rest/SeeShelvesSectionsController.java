package ro.mta.library_project.Controllers.LibrarianControllers;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import org.json.simple.parser.ParseException;
import ro.mta.library_project.DBController.BookLocation;
import ro.mta.library_project.DBController.DBController;
import ro.mta.library_project.DBController.IDTitleBook;
import ro.mta.library_project.People.Librarian;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class SeeShelvesSectionsController {
    private static String Username;
    private static int ID;
    DBController dbc;

    public static void setUsername(String username)
    {
        Username=username;
    }
    public static void setID(int id)
    {
        ID=id;
    }

    public SeeShelvesSectionsController()
    {
        dbc  = DBController.getInstance();
    }
    @FXML
    private ListView<String> listOfBooks;

    @FXML
    private ListView<String> details;

    @FXML
    public TextField id_show;

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
    private void showShelves(final ActionEvent event) throws IOException, ParseException, InterruptedException {
        Librarian l=new Librarian(this.ID,this.Username); //de modificat
        if (id_show.getText() != null && !id_show.getText().isEmpty()) {
            BookLocation a=l.GetLocationOfBook(id_show.getText());
            ObservableList listarguments = FXCollections.observableArrayList();
            List<String> stringList = new ArrayList<>();

            stringList.add("Id-ul cartii: "+String.valueOf(a.getID()));
            stringList.add("Id-ul raftului: "+String.valueOf(a.getRaft()));
            stringList.add("Numarul de locuri libere: "+String.valueOf(a.getFreeLocations()));
            stringList.add("Numarul total de locuri: "+String.valueOf(a.getTotalLocations()));
            stringList.add("Sectiunea este: "+a.getSection());
            stringList.add("-----------------------------");

            listarguments.setAll(stringList);
            details.getItems().addAll(listarguments);

            id_show.setText("");
        }
    }
}
