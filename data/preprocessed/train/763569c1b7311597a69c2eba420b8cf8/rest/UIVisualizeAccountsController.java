package ro.mta.library_project.Controllers.AdminControllers;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.cell.PropertyValueFactory;
import ro.mta.library_project.HelperClasses.VisualizeAccountsHelperClass;
import ro.mta.library_project.People.DaoPeopleLogs;

import java.net.URL;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.ResourceBundle;
import java.util.logging.Logger;

/**
 * Clasa controller pentru interfata VisualizeAccounts
 *
 * @author Cioaca Andrei
 */
public class UIVisualizeAccountsController implements Initializable {
    private static final Logger log;

    static {
        System.setProperty("java.util.logging.SimpleFormatter.format", "[%4$-7s] %5$s %n");
        log = Logger.getLogger(ro.mta.library_project.People.DaoPeopleLogs.class.getName());
    }

    private final List<String> columnNames = new ArrayList<>();
    protected ObservableList<ObservableList> data = FXCollections.observableArrayList();
    TableColumn id = null;
    TableColumn nume = null;
    TableColumn prenume = null;
    TableColumn dataNasterii = null;
    TableColumn CNP = null;
    TableColumn username = null;
    TableColumn rol = null;
    TableColumn createdBy = null;

    List ll = new LinkedList();
    private int afisareNumeColoane = 0;
    @FXML
    private TableView myTableView;

    /**
     * Metoda creaza coloanele tabelului si il populeaza cu informatiile din lista
     */
    private void buildData() throws SQLException {
        myTableView.getItems().clear();

        if (afisareNumeColoane == 0) {
            id = new TableColumn("ID");
            nume = new TableColumn("Nume");
            prenume = new TableColumn("Prenume");
            dataNasterii = new TableColumn("DataNasterii");
            CNP = new TableColumn("CNP");
            username = new TableColumn("Username");
            rol = new TableColumn("Rol");
            createdBy = new TableColumn("CreatedBy");

            myTableView.getColumns().addAll(id, nume, prenume, dataNasterii, CNP, username, rol, createdBy);

            afisareNumeColoane = 1;
        }

        ObservableList<VisualizeAccountsHelperClass> ol = FXCollections.observableArrayList();

        for (int i = 0; i < ll.size(); i++) {
            ol.add((VisualizeAccountsHelperClass) ll.get(i));
        }

        id.setCellValueFactory(new PropertyValueFactory<VisualizeAccountsHelperClass, String>("id"));
        nume.setCellValueFactory(new PropertyValueFactory<VisualizeAccountsHelperClass, String>("nume"));
        prenume.setCellValueFactory(new PropertyValueFactory<VisualizeAccountsHelperClass, String>("prenume"));
        dataNasterii.setCellValueFactory(new PropertyValueFactory<VisualizeAccountsHelperClass,
                String>("dataNasterii"));
        CNP.setCellValueFactory(new PropertyValueFactory<VisualizeAccountsHelperClass, String>("CNP"));
        username.setCellValueFactory(new PropertyValueFactory<VisualizeAccountsHelperClass, String>("username"));
        rol.setCellValueFactory(new PropertyValueFactory<VisualizeAccountsHelperClass, String>("rol"));
        createdBy.setCellValueFactory(new PropertyValueFactory<VisualizeAccountsHelperClass, String>("createdBy"));

        myTableView.setItems(ol);

    }

    /**
     * Metoda preia lista cu obiectele care trebuie afisate in tabela si apeleaza metoda de afisare
     */
    @Override
    public void initialize(URL arg0, ResourceBundle arg1) {
        try {
            ll = DaoPeopleLogs.getTabelaPersoane();
            buildData();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
