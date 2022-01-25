package ro.mta.library_project.Controllers;

import javafx.beans.property.IntegerProperty;
import javafx.beans.property.StringProperty;
import javafx.collections.FXCollections;
import javafx.scene.Node;
import javafx.scene.control.*;
import javafx.scene.control.Label;
import javafx.scene.control.MenuBar;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.input.MouseEvent;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import ro.mta.library_project.DBController.DBController;
import ro.mta.library_project.Models.ActionsModel;
import ro.mta.library_project.Models.ExtendedBook;
import ro.mta.library_project.Models.UserModel;
import ro.mta.library_project.People.*;

import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.input.KeyEvent;
import ro.mta.library_project.Book.Book;

import java.io.IOException;
import java.sql.ResultSet;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.Random;
import java.util.ResourceBundle;

import javafx.scene.input.InputEvent;
import javafx.scene.input.KeyCode;
import ro.mta.library_project.RequestsModule.BorrowRequest;

import java.awt.*;
import java.net.URL;
import java.util.ResourceBundle;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Clasa UIUserController pentru interfata UIUser
 *
 * @author Lupu Marcela
 */
public class UIUserController implements Initializable {
    private int ID;
    private String Username;
    private String firstName;
    private String lastName;
    private String birthDate;
    private String CNP;
    private String password;
    private String idRole;
    BorrowRequest request;
    UserDatabaseDependencies userDatabaseDependencies;
    DBController dbc;
    private Parent root;

    @FXML
    private MenuBar menuBar;

    @FXML
    protected Label logoutLabel;

    @FXML
    protected Label testLabel;

    @FXML
    protected Label accountLabel;

    @FXML
    private TextField searchBookField;

    public UIUserController()
    {
        request = new BorrowRequest();
        userDatabaseDependencies = new UserDatabaseDependencies();
        dbc  = DBController.getInstance();
    }

    /**
     * Metoda seteaza variabila ID
     *
     * @param ID ID-ul utilizatorului care s-a logat
     */
    protected void setID(int ID)
    {
        this.ID = ID;
    }

    /**
     * Metoda seteaza variabila Username, variabila setText si searchBookField
     *
     * @param Username username-ul utilizatorului care s-a logat
     */
    protected void setUsername(String Username)
    {
        this.Username = Username;
        accountLabel.setText("Bine ai venit in contul tau, " + Username + "!");
        searchBookField.setPromptText("Cauta o carte...");
    }

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
    ComboBox filtersCombo;

    /**
     * Metoda inchide fereastra
     */
    private void closeStage() {
        ((Stage) logoutLabel.getScene().getWindow()).close();
    }

    /**
     * Metoda handleLogoutButtonAction() realizeaza delogarea unui utilizator inregistrat si deschide interfata Login
     */
    @FXML
    protected void handleLogoutButtonAction() throws Exception {
        DaoPeopleLogs.logLogout(ID);
        closeStage();

        Parent parent = FXMLLoader.load(getClass().getResource("/ro/mta/library_project/UILogin.fxml"));
        Stage stage = new Stage(StageStyle.DECORATED);
        stage.setTitle("Login Window");
        stage.setScene(new Scene(parent));
        stage.show();
    }

    /**
     * Metoda handleMyAccount(final ActionEvent actionEvent) este implicit creata in urma definirii acesteia in fisierul .fxml aferent si are rolul de a afisare informatiile contului unui utilizator pe baza ID-ului intr-o fereastra noua.
     */
    @FXML
    private void handleMyAccount(final ActionEvent actionEvent) throws IOException {
        UserModel user = dbc.SelectUser(ID);
        Stage stage = new Stage(StageStyle.DECORATED);
        FXMLLoader loader = new FXMLLoader(getClass().
                getResource("/ro/mta/library_project/UIUserAccount.fxml"));
        root = loader.load();
        stage.setTitle("Account Data");

        UIUserAccountController userAccount = loader.getController();
        userAccount.setUser(user);

        Scene scene = new Scene(root);
        stage.setScene(scene);
        stage.show();
        userAccount.showUserInfo(user);

        UserLog.getInstance().viewAccountDetails(Username, ID);
    }

    /**
     * Metoda handleNews(final ActionEvent actionEvent) este implicit creata in urma definirii acesteia in fisierul .fxml aferent si are rolul de a afisa stirile cautate pe baza cautarii unui sir de caractere intr-o fereastra noua.
     */
    @FXML
    private void handleNews(final ActionEvent actionEvent) throws IOException {
        //provideAboutFunctionality("/ro/mta/library_project/NewsView.fxml");
        Stage stage = new Stage(StageStyle.DECORATED);
        FXMLLoader loader = new FXMLLoader(getClass().
                getResource("/ro/mta/library_project/NewsView.fxml"));
        root = loader.load();
        stage.setTitle("News");

        NewsController activity = loader.getController();
        activity.setID(ID);
        activity.setUsername(Username);

        Scene scene = new Scene(root);
        stage.setScene(scene);
        stage.show();
    }

    /**
     * Metoda handleActivity(final ActionEvent actionEvent) este implicit creata in urma definirii acesteia in fisierul .fxml aferent si are rolul de a afisa activitatea anterioara a unui utilizator inregistrat pe baza ID-ului intr-o fereastra noua.
     */
    @FXML
    private void handleActivity(final ActionEvent actionEvent) throws IOException {
        //provideAboutFunctionality("/ro/mta/library_project/UserActivity.fxml");
        ArrayList<ActionsModel> actions = dbc.GetUserActions(ID);
        Stage stage = new Stage(StageStyle.DECORATED);
        FXMLLoader fxmlLoader = new FXMLLoader(getClass().
                getResource("/ro/mta/library_project/UserActivity.fxml"));
        root = fxmlLoader.load();
        stage.setTitle("Istoric activitati");

        UserActivityController userController = fxmlLoader.getController();
        userController.setActions(actions);
        userController.setUsername(this.Username);
        userController.setID(this.ID);

        Scene scene = new Scene(root);
        stage.setScene(scene);
        stage.show();

        userController.printActivity();
    }

    /**
     * Metoda handleBorrowBooks(final ActionEvent actionEvent) este implicit creata in urma definirii acesteia in fisierul .fxml aferent si are rolul de a afisa cartile imprumutate de utilizatorul curent intr-o fereastra noua.
     */
    @FXML
    private void handleBorrowBooks(final ActionEvent actionEvent) throws IOException {
        //provideAboutFunctionality("/ro/mta/library_project/BorrowBooksView.fxml");
        ArrayList<ExtendedBook> books = dbc.SelectBorrowedBooks(ID);
        Stage stage = new Stage(StageStyle.DECORATED);
        FXMLLoader fxmlLoader = new FXMLLoader(getClass().
                getResource("/ro/mta/library_project/BorrowBooksView.fxml"));
        root = fxmlLoader.load();
        stage.setTitle("Carti imprumutate");

        BorrowBooksController borrow = fxmlLoader.getController();
        borrow.setBooksArray(books);
        borrow.setUsername(this.Username);
        borrow.setID(this.ID);

        Scene scene = new Scene(root);
        stage.setScene(scene);
        stage.show();

        borrow.viewBooks();
    }

    /**
     * Metoda handleViewElectronicBook(final ActionEvent actionEvent) este implicit creata in urma definirii acesteia in fisierul .fxml aferent si are rolul de a afisa continutul unei carti electronice pe baza ID-ului cartii si a parolei utilizatorului.
     * Parola si ID-ul sunt trimise din aceasta fereastra in controller-ul 'View Electronic Book Controller' si ulterior este apelata functia `afiseaza` in care se realizeaza afisarea continutului.
     * In acest sens, trebuie selectata din interfata grafica o carte electronica, iar apoi din Meniu se selecteaza optiunea 'Vizualizare carte electronica`.
     * Continutul cartii va fi afisat intr-o fereastra noua.
     */
    @FXML
    private void handleViewElectronicBook(final ActionEvent actionEvent) throws IOException{
        //provideAboutFunctionality("/ro/mta/library_project/UIViewElectronicBook.fxml");
        ObservableList<ExtendedBook> selectedItems = tbData.getSelectionModel().getSelectedItems();
        UserModel user=dbc.SelectUser(ID);

        Stage stage = new Stage(StageStyle.DECORATED);
        FXMLLoader Loader = new FXMLLoader(getClass().
                getResource("/ro/mta/library_project/UIViewElectronicBook.fxml"));
        root = Loader.load();
        stage.setTitle("Electronic Book");

        ViewElectronicBookController electroView = Loader.getController();

        Scene scene = new Scene(root);
        stage.setScene(scene);
        stage.show();

        electroView.afiseaza(selectedItems.get(0).getBookId(),user.getPassword());
    }

    /**
     * Metoda handleAllBooks(final ActionEvent actionEvent) este implicit creata in urma definirii acesteia in fisierul .fxml aferent.
     * Scopul cu care a fost creata aceasta functie este de a afisa intr-un tabel toate cartile disponibile in biblioteca.
     * Pentru a imprumut o carte, se poate selecta una singura sau se pot alege mai multe carti pentru a fi imprumutate cu combinatia CTRL+click.
     * Cartile vor fi afisate in aceeasi interfata, se va suprascrie tabelul dbData
     */
    @FXML
    private void handleAllBooks(final ActionEvent actionEvent) {

        ArrayList<ExtendedBook> booksArray = dbc.SelectExtendedBook();

        ObservableList<ExtendedBook> books = FXCollections.observableArrayList(booksArray);

        bookId.setCellValueFactory(new PropertyValueFactory<ExtendedBook, Integer>("bookId"));
        name.setCellValueFactory(new PropertyValueFactory<ExtendedBook, String>("name"));
        author.setCellValueFactory(new PropertyValueFactory<ExtendedBook, String>("author"));
        type.setCellValueFactory(new PropertyValueFactory<ExtendedBook, String>("type"));
        section.setCellValueFactory(new PropertyValueFactory<ExtendedBook, String>("section"));
        //add your data to the table here.
        tbData.setItems(books);

        tbData.getSelectionModel().setSelectionMode(
                SelectionMode.MULTIPLE
        );
    }

    @FXML
    private void handleViewExit(final ActionEvent actionEvent) {
    }

    @FXML
    private void handleKeyInput(final InputEvent event) {
    }

    /**
     * Metoda provideAboutFunctionality(String resourceName) este implementata pentru a deschide o noua fereasta.
     * Parametrul resourceName este numele fisierului .fxml unde va fi redirectionat utilizatorului.
     * @param resourceName numele fiserului .fxml unde sa fie redirectionat utilizatorului in functie de optiune
     */
    private void provideAboutFunctionality(String resourceName) {
        try {
            FXMLLoader fxmlLoader = new FXMLLoader();
            fxmlLoader.setLocation(getClass().getResource(resourceName));
            Scene scene = new Scene(fxmlLoader.load(), 630, 400);
            Stage stage = new Stage();
            stage.setTitle("New Window");
            stage.setScene(scene);
            stage.show();
        } catch (IOException e) {
            Logger logger = Logger.getLogger(getClass().getName());
            logger.log(Level.SEVERE, "Failed to create new Window.", e);
        }
    }

    /**
     * Metoda initialize() este creata automat in urma implementarii interfetei `Initializable`.
     * Aceasta metoda este apelata intern dupa constructor. Scopul ei este de a apela functia de selectare a cartilor din baza de date `SelectExtendedBook` si de a popula tabelul din view-ul UIUser cu datele corespunzatoare.
     * De asemenea se populeaza si un combo box cu filtrele necesare pentru a cauta o carte in biblioteca in functie de acestea.
     */
    @Override
    public void initialize(URL location, ResourceBundle resources) {
        menuBar.setFocusTraversable(true);

        ArrayList<ExtendedBook> booksArray = dbc.SelectExtendedBook();

        // add your data here from any source
        ObservableList<ExtendedBook> books = FXCollections.observableArrayList(booksArray);

        bookId.setCellValueFactory(new PropertyValueFactory<ExtendedBook, Integer>("bookId"));
        name.setCellValueFactory(new PropertyValueFactory<ExtendedBook, String>("name"));
        author.setCellValueFactory(new PropertyValueFactory<ExtendedBook, String>("author"));
        type.setCellValueFactory(new PropertyValueFactory<ExtendedBook, String>("type"));
        section.setCellValueFactory(new PropertyValueFactory<ExtendedBook, String>("section"));
        //add your data to the table here.
        tbData.setItems(books);

        tbData.getSelectionModel().setSelectionMode(
                SelectionMode.MULTIPLE
        );

        String filters[] = { "ID", "Autor", "Titlu", "Sectiune", "Tip"};
        ObservableList<String> options =
                FXCollections.observableArrayList(filters);
        filtersCombo.getItems().addAll(options);
        filtersCombo.getSelectionModel().select(2);
    }

    /**
     * Metoda `borrowBooksMethod() are rolul de a genera un cod pe baza cartilor selectate si pe baza ID-ului utilizatorului curent.
     * Se verifica daca acest cod generat exista deja si daca da, se genereaza un alt numar random folosit la generarea codului de imprumut. La final, se insereaza in baza de date in tabela `CereriImprumut` ID-ul utilizatorului, ID-ul cartilor selectate si codul de imprumut.
     * Pentru asta s-a creat o clasa ajutatoare BorrowRequest care contine variabilele necesare pentru inserarea in baza de date.
     */
    @FXML
    private void borrowBooksMethod(final ActionEvent event) throws IOException {
        ObservableList<ExtendedBook> selectedItems = tbData.getSelectionModel().getSelectedItems();

        this.request = new BorrowRequest();
        this.request.bookId = new ArrayList<Integer>();

        this.request.userId = this.ID;

        for (int i = 0; i < selectedItems.size(); i++) {
            this.request.bookId.add(selectedItems.get(i).getBookId());
        }

        StringBuilder builder = new StringBuilder();

        for (int i = 0; i < selectedItems.size(); i++) {
            builder.append(selectedItems.get(i).getBookId() + selectedItems.get(i).getName());
        }

        String result = builder.toString();

        int hashValue = Math.abs(result.hashCode());

        int min = 0;
        int max = 100000;
        Random random = new Random();
        int random_int = random.nextInt(max - min) + min;

        int hashResult = random_int * this.ID + hashValue;

        this.request.borrowCode = hashResult;

        ArrayList<Integer> existingHashes = new ArrayList<Integer>();

        ResultSet set = null;
        try {
            set = dbc.Select("CereriImprumut", "Cod", String.valueOf(hashResult));
            while (set.next()) {
                existingHashes.add(set.getInt(4));
            }

        } catch (Exception e) {
            System.out.println("Something went wrong in visualizing CereriImprumut");
            System.out.println(e.getMessage());
        }

        while (existingHashes.contains(hashResult))
        {
            random_int = random.nextInt(max - min) + min;
            hashResult = random_int * this.ID + hashValue;
            this.request.borrowCode = hashResult;
        }

        try {
            DateTimeFormatter dtf = DateTimeFormatter.ofPattern("uuuu/MM/dd HH:mm:ss");
            LocalDateTime now = LocalDateTime.now();
            String strDate = dtf.format(now);

            for (int i = 0; i < this.request.bookId.size(); i++) {

                String userId = String.valueOf(this.request.userId);
                String code = String.valueOf(this.request.borrowCode);
                String bookId = String.valueOf(this.request.bookId.get(i));
                DBController dbc = DBController.getInstance();
                dbc.BorrowRequestInsert(userId, strDate, code, bookId);
            }

        } catch (
                Exception e) {
            System.out.println("Something went wrong with insert");
            System.out.println(e.getMessage());
        }

        testLabel.setText("Codul de imprumut este: " + hashResult + "!");

        UserLog.getInstance().logGenerateBorrowCode(Username, ID, this.request.borrowCode);
        UserLog.getInstance().logBorrowBook(Username, ID, this.request.borrowCode);
    }

    /**
     * Metoda searchBookFunction() are scopul de a permite utilizatorului sa caute o carte in functie de diverse filtre cum ar fi titlu, nume carte, sectiune sau tip.
     * Cautarea se face apeland functia `SelectExtendedBook(selectedFilter, input)` care primeste ca parametri numele filtrului si inputul dupa care se face cautarea si selecteaza din baza de date cartile cu aceste campuri daca exista.
     * Se va alege filtrul dintr-un combo box si numele stringului ce se doreste cautat se introduce in textFieldul searchBookField si se da click pe butonul OK.
     */
    @FXML
    private void searchBookFunction(final ActionEvent event) throws IOException {
        String input = searchBookField.getText();
        String selectedFilter = (String) filtersCombo.getValue();


        ArrayList<ExtendedBook> booksAfterFilter = dbc.SelectExtendedBook(selectedFilter, input);

        ObservableList<ExtendedBook> books = FXCollections.observableArrayList(booksAfterFilter);

        bookId.setCellValueFactory(new PropertyValueFactory<ExtendedBook, Integer>("bookId"));
        name.setCellValueFactory(new PropertyValueFactory<ExtendedBook, String>("name"));
        author.setCellValueFactory(new PropertyValueFactory<ExtendedBook, String>("author"));
        type.setCellValueFactory(new PropertyValueFactory<ExtendedBook, String>("type"));
        section.setCellValueFactory(new PropertyValueFactory<ExtendedBook, String>("section"));
        //add your data to the table here.
        tbData.setItems(books);

        tbData.getSelectionModel().setSelectionMode(
                SelectionMode.MULTIPLE
        );

        UserLog.getInstance().logSearchBook(Username, ID);
    }
}
