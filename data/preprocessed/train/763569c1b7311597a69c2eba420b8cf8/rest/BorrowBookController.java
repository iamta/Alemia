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
import ro.mta.library_project.People.LibrarianLog;
import ro.mta.library_project.Shelf_sections.Shelf;

import java.io.IOException;
import java.sql.ResultSet;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class BorrowBookController {

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

    public BorrowBookController()
    {
        dbc  = DBController.getInstance();
    }

    @FXML
    private ListView<String> list;

    @FXML
    public TextField borrowCode;
    @FXML
    public TextField returdate;


    @FXML
    private void borrow(final ActionEvent event) throws IOException, ParseException, InterruptedException {
        BorrowBook(borrowCode.getText());
    }

    private void BorrowBook(String code)
    {
        List<String> stringList = new ArrayList<>();
        //iau din cerereimprumut dupa code cererea in care obtin informatiile despre username, datarequest,cartefizica(id-ul ei)
        //code=4
        String username="";
        String dataRequest="";
        String idBook="";
        String typeBook="";
        String volumes="";
        String id_shelf="1";
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
        //ca sa vedem ca e fizica
        try {
            ResultSet requests= null;
            requests = dbc.Select("Carti", "ID", idBook);
            if(requests.next()) {
                typeBook=requests.getString(7);
                volumes=requests.getString(8);
                id_shelf=requests.getString(9);
            }
        }
        catch(Exception e){
            stringList.add("Nu am gasit cartea.");
        }
        //verificarea sa fie carte fizica
        if(ok==true & typeBook.equals("2")) {
            //inserez in imprumuturi: username, datarequestul, data returului: il intreb pe utilizator, id carte,
            // data retur real lasam  null, stare, scriu observatie eu, id-ul bibliotecarului
            String input = returdate.getText();
            if (input.matches("\\d{4}-\\d{2}-\\d{2}")) {
                input = input + "T00:00:00.0000000";
                try {
                    String a=Integer.toString(this.ID);
                    dbc.BorrowInsertHash(username,dataRequest,input,idBook,"","1",a,code);
                    LibrarianLog.LogBorrowBook(this.ID,this.Username,username,input);
                }
                catch(Exception e){
                    stringList.add("Nu putem face imprumutul.");
                }

                //updatez la numar de volume in Carti, dupa scad sau sterg cartea daca are un singur element
                try {
                    int bookid = 0;
                    bookid = Integer.parseInt(idBook);
                    if (volumes.equals("0")) {
                        stringList.add("Cartea nu exista in biblioteca. Refa imprumutul.");
                    } else {
                        int nrVolumes = Integer.parseInt(volumes);
                        nrVolumes = nrVolumes - 1;
                        try {
                            ResultSet book = null;
                            String val = String.valueOf(nrVolumes);
                            dbc.UpdateValue("Carti", "NumarVolume", val, "ID", idBook);
                        } catch (Exception e) {
                            stringList.add("\nNumarul de volume nu poate fi updatat.");
                        }
                        //updateaza Shelf-ul, adaug 1 la locuri libere
                        try {
                            ResultSet requests= null;
                            requests = dbc.Select("Rafturi", "ID", id_shelf);
                            if(requests.next()) {
                                books_free=requests.getString(9);
                            }
                        }
                        catch(Exception e){
                            stringList.add("Nu am gasit raftul.");
                        }
                        try {
                            ResultSet book = null;
                            String val = String.valueOf(books_free);
                            val=val+1;
                            dbc.UpdateValue("Rafturi", "LocuriLibere", val, "ID", id_shelf);
                            showShelves(idBook);
                        } catch (Exception e) {
                            stringList.add("\nNumarul de locuri libere pe raft nu poate fi updatat.");
                        }
                    }
                }catch (Exception e) {
                    stringList.add("\nNu se poate schimba");
                }

            } else
                stringList.add("Data returlui introdusa incorect .");
        }
        else
            stringList.add("Cerere negasita sau nu e carte fizica.");
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



