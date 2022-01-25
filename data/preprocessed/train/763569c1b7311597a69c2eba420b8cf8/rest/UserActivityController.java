package ro.mta.library_project.Controllers;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import ro.mta.library_project.DBController.DBController;
import ro.mta.library_project.Models.ActionsModel;

import java.awt.*;
import java.net.URL;
import java.util.ArrayList;
import java.util.ResourceBundle;

/**
 * Clasa controller pentru interfata UserActivity
 *
 * @author Lupu Marcela
 */
public class UserActivityController{
    private DBController dbc;
    private int ID;
    private String Username;
    private ArrayList<ActionsModel> actions;

    @FXML
    private TableView<ActionsModel> table;
    @FXML
    public TableColumn<ActionsModel, String> activityData;

    @FXML
    public TableColumn<ActionsModel, String> details;

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
     * Metoda seteaza variabila actions
     *
     * @param actions actiunile utilizatorului care s-a logat
     */
    public void setActions(ArrayList<ActionsModel> actions)
    {
        this.actions = actions;
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
     * Metoda returneaza ID-ul utilizatorului
     */
    public int getID()
    {
        return this.ID;
    }

    public UserActivityController()
    {
        dbc  = DBController.getInstance();
    }

    /**
     * Metoda printActivity() afiseaza intr-un tabel activitatile anterioare ale unui utilizator si ora la care au fost facute acestea.
     * */
    public void printActivity() {
        ObservableList<ActionsModel> books = FXCollections.observableArrayList(actions);

        activityData.setCellValueFactory(new PropertyValueFactory<ActionsModel, String>("dateString"));
        details.setCellValueFactory(new PropertyValueFactory<ActionsModel, String>("details"));

        table.setItems(books);
    }

}
