package ro.mta.library_project.Controllers.AdminControllers;

import javafx.beans.value.ChangeListener;
import javafx.beans.value.ObservableValue;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.ListView;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import ro.mta.library_project.HelperClasses.ActionLogsHelperClass;
import ro.mta.library_project.People.DaoPeopleLogs;

import java.net.URL;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.ResourceBundle;
import java.util.logging.Logger;

/**
 * Clasa controller pentru interfata VisualizeActionLogs
 *
 * @author Cioaca Andrei
 */
public class UIVisualizeActionLogsController implements Initializable {
    private static final Logger log;

    static {
        System.setProperty("java.util.logging.SimpleFormatter.format", "[%4$-7s] %5$s %n");
        log = Logger.getLogger(ro.mta.library_project.People.DaoPeopleLogs.class.getName());
    }

    private final List<String> columnNames = new ArrayList<>();
    protected ObservableList<ObservableList> data = FXCollections.observableArrayList();
    TableColumn id = null;
    TableColumn username = null;
    TableColumn actiune = null;
    TableColumn dataOra = null;
    TableColumn detalii = null;
    List ll = new LinkedList();
    String[] picks = {"Toate log-urile", "Creare cont", "Stergere cont", "Modificare cont",
            "Vizualizare tabela Persoane", "Vizualizare Log-uri Actiuni", "Vizualizare Log-uri Login/Logout"};
    String pick;
    private int afisareNumeColoane = 0;
    @FXML
    private TableView myTableView;
    @FXML
    private ListView<String> optionsActionsListView;

    /**
     * Metoda creaza coloanele tabelului si il populeaza cu informatiile din lista
     */
    private void buildData() throws SQLException {
        myTableView.getItems().clear();

        if (afisareNumeColoane == 0) {
            id = new TableColumn("ID");
            username = new TableColumn("Username");
            actiune = new TableColumn("Actiune");
            dataOra = new TableColumn("DataOra");
            detalii = new TableColumn("Detalii");
            myTableView.getColumns().addAll(id, username, actiune, dataOra, detalii);

            afisareNumeColoane = 1;
        }

        ObservableList<ActionLogsHelperClass> ol = FXCollections.observableArrayList();

        for (int i = 0; i < ll.size(); i++) {
            ol.add((ActionLogsHelperClass) ll.get(i));
        }

        id.setCellValueFactory(new PropertyValueFactory<ActionLogsHelperClass, String>("id"));
        username.setCellValueFactory(new PropertyValueFactory<ActionLogsHelperClass, String>("username"));
        actiune.setCellValueFactory(new PropertyValueFactory<ActionLogsHelperClass, String>("actiune"));
        dataOra.setCellValueFactory(new PropertyValueFactory<ActionLogsHelperClass, String>("dataOra"));
        detalii.setCellValueFactory(new PropertyValueFactory<ActionLogsHelperClass, String>("detalii"));

        myTableView.setItems(ol);
    }

    /**
     * Metoda preia lista cu obiectele care trebuie afisate in tabela si apeleaza metoda de afisare
     */
    @Override
    public void initialize(URL arg0, ResourceBundle arg1) {
        try {
            ll = DaoPeopleLogs.getlogSeeActionLogs("Toate log-urile");
            buildData();
        } catch (Exception e) {
            e.printStackTrace();
        }

        optionsActionsListView.getItems().addAll(picks);

        optionsActionsListView.getSelectionModel().selectedItemProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observableValue, String s, String t1) {
                pick = optionsActionsListView.getSelectionModel().getSelectedItem();

                try {
                    ll = DaoPeopleLogs.getlogSeeActionLogs(pick);
                    buildData();
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
    }
}
