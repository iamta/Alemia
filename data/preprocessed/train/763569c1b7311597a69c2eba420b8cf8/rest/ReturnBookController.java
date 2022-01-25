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
import ro.mta.library_project.People.Librarian;

import java.io.IOException;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;

public class ReturnBookController {

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

    public ReturnBookController()
    {
        dbc  = DBController.getInstance();
    }

    @FXML
    private ListView<String> list;

    @FXML
    public TextField code;


    @FXML
    private void returnBook(final ActionEvent event) throws IOException, ParseException, InterruptedException {
        ReturnBook(code.getText());
    }

    public void ReturnBook(String code)
    {
        List<String> stringList = new ArrayList<>();
        //iau din cerereimprumut dupa code cererea in care obtin informatiile despre username, datarequest,cartefizica(id-ul ei)
        //code=4
        String username="";
        String dataRequest="";
        String idBook="";
        String typeBook="";
        String volumes="";
        String id_shelf="";
        String books_free="";
        boolean ok=false;
        try {
            ResultSet requests= null;
            requests = dbc.Select("CereriImprumut", "Cod", code);
            while(requests.next()) {
                ok=true;
                username=requests.getString(2);
                dataRequest=requests.getString(3);
                idBook=requests.getString(5);
            }
        }
        catch(Exception e){
            stringList.add("Nu am gasit cererea.");
        }
        //ca sa vedem numar volume
        try {
            ResultSet requests= null;
            requests = dbc.Select("Carti", "ID", idBook);
            if(requests.next()) {
                volumes=requests.getString(8);
                id_shelf=requests.getString(9);
            }
        }
        catch(Exception e){
            stringList.add("Nu am gasit cartea.");
        }
        //updatez la numar de volume in Carti
        int bookid = 0;
        bookid = Integer.parseInt(idBook);
        int nrVolumes = Integer.parseInt(volumes);
        nrVolumes = nrVolumes + 1;
        try {
            ResultSet book = null;
            String val = String.valueOf(nrVolumes);
            dbc.UpdateValue("Carti", "NumarVolume", val, "ID", idBook);
        } catch (Exception e) {
            stringList.add("\nNumarul de volume nu poate fi updatat.");
        }
        //updatez pe shelf
        //updateaza Shelf-ul, adaug 1 la locuri libere
        try {
            ResultSet requests= null;
            requests = dbc.Select("Rafturi", "ID", id_shelf);
            if(requests.next()) {
                books_free=requests.getString(3);
            }
        }
        catch(Exception e){
            stringList.add("Nu am gasit raftul.");
        }
        int val = Integer.parseInt(books_free);
        if(val>=1)
        {
            try {
                ResultSet book = null;
                val=val-1;
                String b=String.valueOf(val);
                dbc.UpdateValue("Rafturi", "LocuriLibere", b, "ID", id_shelf);
                showShelves(idBook);
            } catch (Exception e) {
                stringList.add("\nNumarul de locuri libere pe raft nu poate fi updatat.");
            }
        }else
            stringList.add("Nu mai sunt locuri disponibile pe raft.");

        stringList.add("--------------------------------------");
    }

    private void showShelves(String idBook) throws IOException, ParseException, InterruptedException {
        Librarian l=new Librarian(this.ID,this.Username); //de modificat
        BookLocation a=l.GetLocationOfBook(idBook);
        ObservableList listarguments = FXCollections.observableArrayList();
        List<String> stringList = new ArrayList<>();

        stringList.add("Id-ul cartii: "+String.valueOf(a.getID()));
        stringList.add("Id-ul raftului: "+String.valueOf(a.getRaft()));
        stringList.add("Numarul de locuri libere: "+String.valueOf(a.getFreeLocations()));
        stringList.add("Numarul total de locuri: "+String.valueOf(a.getTotalLocations()));
        stringList.add("Sectiunea este: "+a.getSection());
        stringList.add("-----------------------------");

        listarguments.setAll(stringList);
        list.getItems().addAll(listarguments);
    }

}
