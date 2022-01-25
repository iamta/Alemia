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
import ro.mta.library_project.HelperClasses.LoginLogoutHelperClass;
import ro.mta.library_project.People.DaoPeopleLogs;

import java.net.URL;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.ResourceBundle;
import java.util.logging.Logger;

/**
 * Clasa controller pentru interfata VisualizeLoginLogoutLogs
 *
 * @author Cioaca Andrei
 */
public class UIVisualizeLoginLogoutLogsController implements Initializable {
    private static final Logger log;

    static {
        System.setProperty("java.util.logging.SimpleFormatter.format", "[%4$-7s] %5$s %n");
        log = Logger.getLogger(ro.mta.library_project.People.DaoPeopleLogs.class.getName());
    }

    private final List<String> columnNames = new ArrayList<>();
    protected ObservableList<ObservableList> data = FXCollections.observableArrayList();
    TableColumn id = null;
    TableColumn username = null;
    TableColumn dataOraLogin = null;
    TableColumn dataOraLogout = null;
    List ll = new LinkedList();
    String[] picks = {"Toate log-urile", "Log-urile adminilor", "Log-urile bibliotecarilor", "Log-urile user-silor"};
    String pick;
    private int afisareNumeColoane = 0;
    @FXML
    private TableView myTableView;
    @FXML
    private ListView<String> optionsLoginLogoutListView;

    /**
     * Metoda creaza coloanele tabelului si il populeaza cu informatiile din lista
     */
    private void buildData() throws SQLException {
        myTableView.getItems().clear();

        if (afisareNumeColoane == 0) {
            id = new TableColumn("ID");
            username = new TableColumn("Username");
            dataOraLogin = new TableColumn("DataOraLogin");
            dataOraLogout = new TableColumn("DataOraLogout");
            myTableView.getColumns().addAll(id, username, dataOraLogin, dataOraLogout);

            afisareNumeColoane = 1;
        }

        ObservableList<LoginLogoutHelperClass> ol = FXCollections.observableArrayList();

        for (int i = 0; i < ll.size(); i++) {
            ol.add((LoginLogoutHelperClass) ll.get(i));
        }

        id.setCellValueFactory(new PropertyValueFactory<LoginLogoutHelperClass, String>("id"));
        username.setCellValueFactory(new PropertyValueFactory<LoginLogoutHelperClass, String>("username"));
        dataOraLogin.setCellValueFactory(new PropertyValueFactory<LoginLogoutHelperClass, String>("dataOraLogin"));
        dataOraLogout.setCellValueFactory(new PropertyValueFactory<LoginLogoutHelperClass, String>("dataOraLogout"));

        myTableView.setItems(ol);
    }

    /**
     * Metoda preia lista cu obiectele care trebuie afisate in tabela si apeleaza metoda de afisare
     */
    @Override
    public void initialize(URL arg0, ResourceBundle arg1) {
        try {
            ll = DaoPeopleLogs.getlogLoginLogoutLogs("Toate log-urile");
            buildData();
        } catch (Exception e) {
            e.printStackTrace();
        }

        optionsLoginLogoutListView.getItems().addAll(picks);

        optionsLoginLogoutListView.getSelectionModel().selectedItemProperty().addListener(new ChangeListener<String>() {
            @Override
            public void changed(ObservableValue<? extends String> observableValue, String s, String t1) {
                pick = optionsLoginLogoutListView.getSelectionModel().getSelectedItem();

                try {
                    ll = DaoPeopleLogs.getlogLoginLogoutLogs(pick);
                    buildData();
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
    }
}
