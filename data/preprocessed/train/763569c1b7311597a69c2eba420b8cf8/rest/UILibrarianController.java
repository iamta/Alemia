package ro.mta.library_project.Controllers;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Node;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Label;
import javafx.scene.input.MouseEvent;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import ro.mta.library_project.Controllers.LibrarianControllers.BorrowBookController;
import ro.mta.library_project.Controllers.LibrarianControllers.DestroyBookController;
import ro.mta.library_project.Controllers.LibrarianControllers.SeeAccountDetailsController;
import ro.mta.library_project.Controllers.LibrarianControllers.SeeShelvesSectionsController;
import ro.mta.library_project.DBController.DBController;
import ro.mta.library_project.DBController.LibrarianData;
import ro.mta.library_project.People.DaoPeopleLogs;
import ro.mta.library_project.People.IPerson;
import ro.mta.library_project.People.Librarian;

import java.io.IOException;

public class UILibrarianController {
    public UILibrarianController() {
    }


    @FXML
    protected Label LabelPentruText;

    private int ID;
    private String Username;

    protected void setID(int ID)
    {
        this.ID = ID;
    }

    protected void setUsername(String Username)
    {
        this.Username = Username;
    }

    @FXML
    protected void receiveData(MouseEvent event) {
        // Step 1
        Node node = (Node) event.getSource();
        Stage stage = (Stage) node.getScene().getWindow();
        // Step 2
        IPerson p = (Librarian) stage.getUserData();
        // Step 3
        String name = p.getUsername();
        int ID = p.getID();

        System.out.println(name + " " + ID);
        System.out.println(this.Username + " " + this.ID);
    }

    private void closeStage() {
        ((Stage) LabelPentruText.getScene().getWindow()).close();
    }



    private void openNewWindow(String resource) throws IOException {
        /*FXMLLoader Loader = new FXMLLoader();
        Loader.setLocation(this.getClass().getResource(resource));
        Scene scene = new Scene((Parent)Loader.load());
        Stage stage = new Stage();
        stage.setTitle(resource);
        stage.setScene(scene);
        stage.show();*/

        Parent parent = FXMLLoader.load(getClass().getResource(resource));
        Stage stage = new Stage(StageStyle.DECORATED);
        stage.setTitle(resource);
        stage.setScene(new Scene(parent));
        stage.show();
    }

    @FXML
    private void CreateUserAccount(ActionEvent actionEvent) throws IOException {
        this.openNewWindow("/ro/mta/library_project/LibrarianViews/CreateUserAccount.fxml");
    }

    @FXML
    private void SeeShelvesSections(ActionEvent actionEvent) throws IOException {
        //this.openNewWindow("/ro/mta/library_project/LibrarianViews/SeeShelvesSections.fxml");
        FXMLLoader Loader = new FXMLLoader();
        Loader.setLocation(this.getClass().getResource("/ro/mta/library_project/LibrarianViews/SeeShelvesSections.fxml"));
        Scene scene = new Scene((Parent)Loader.load());
        Stage stage = new Stage();
        stage.setTitle("SeeShelvesSections");
        stage.setScene(scene);
        stage.show();

        SeeShelvesSectionsController seeShelvesSectionsController=Loader.getController();
        SeeShelvesSectionsController.setID(ID);
        SeeShelvesSectionsController.setUsername(Username);
    }

    @FXML
    private void BorrowBook(ActionEvent actionEvent) throws IOException {
        //this.openNewWindow("/ro/mta/library_project/LibrarianViews/BorrowBook.fxml");
        FXMLLoader Loader = new FXMLLoader();
        Loader.setLocation(this.getClass().getResource("/ro/mta/library_project/LibrarianViews/BorrowBook.fxml"));
        Scene scene = new Scene((Parent)Loader.load());
        Stage stage = new Stage();
        stage.setTitle("BorrowBook");
        stage.setScene(scene);
        stage.show();

        BorrowBookController BorrowBookController=Loader.getController();
        BorrowBookController.setID(ID);
        BorrowBookController.setUsername(Username);
    }

    @FXML
    private void ReturnBook(ActionEvent actionEvent) throws IOException {
        this.openNewWindow("/ro/mta/library_project/LibrarianViews/ReturnBook.fxml");
    }

    @FXML
    private void SeeInfoBooks(ActionEvent actionEvent) throws IOException {
        this.openNewWindow("/ro/mta/library_project/LibrarianViews/SeeInfoBooks.fxml");
    }

    @FXML
    private void SearchBook(ActionEvent actionEvent) throws IOException {
        this.openNewWindow("/ro/mta/library_project/LibrarianViews/SearchBook.fxml");
    }

    @FXML
    private void DestroyBook(ActionEvent actionEvent) throws IOException {
        //this.openNewWindow("/ro/mta/library_project/LibrarianViews/DestroyBook.fxml");
        FXMLLoader Loader = new FXMLLoader();
        Loader.setLocation(this.getClass().getResource("/ro/mta/library_project/LibrarianViews/DestroyBook.fxml"));
        Scene scene = new Scene((Parent)Loader.load());
        Stage stage = new Stage();
        stage.setTitle("DestroyBook");
        stage.setScene(scene);
        stage.show();

        DestroyBookController DestroyBookController=Loader.getController();
        DestroyBookController.setID(ID);
        DestroyBookController.setUsername(Username);

    }

    @FXML
    private void AddBook(ActionEvent actionEvent) throws IOException {
        this.openNewWindow("/ro/mta/library_project/LibrarianViews/AddBook.fxml");
    }

    @FXML
    private void SeeAccountDetails(ActionEvent actionEvent) throws IOException {
        //this.openNewWindow("/ro/mta/library_project/LibrarianViews/SeeAccountDetails.fxml");
        FXMLLoader Loader = new FXMLLoader();
        Loader.setLocation(this.getClass().getResource("/ro/mta/library_project/LibrarianViews/SeeAccountDetails.fxml"));
        Scene scene = new Scene((Parent)Loader.load());
        Stage stage = new Stage();
        stage.setTitle("SeeAccountDetails");
        stage.setScene(scene);
        stage.show();

        SeeAccountDetailsController SeeAccountDetailsController=Loader.getController();
        SeeAccountDetailsController.setID(ID);
        SeeAccountDetailsController.setUsername(Username);

        LibrarianData l=new LibrarianData();
        SeeAccountDetailsController.setLibrarian(l);
        SeeAccountDetailsController.showInfo(l);
    }

    @FXML
    private void SeeBorrowedBooks(ActionEvent actionEvent) throws IOException {
        this.openNewWindow("/ro/mta/library_project/LibrarianViews/SeeBorrowedBooks.fxml");
    }

    @FXML
    private void TopElectronicBooks(ActionEvent actionEvent) throws IOException {
        this.openNewWindow("/ro/mta/library_project/LibrarianViews/TopElectronicBooks.fxml");
    }

    @FXML
    private void TopBorrowedBooks(ActionEvent actionEvent) throws IOException {
        this.openNewWindow("/ro/mta/library_project/LibrarianViews/TopBorrowedBooks.fxml");
    }
    @FXML
    protected void handlLogoutButtonAction() throws Exception {
        DaoPeopleLogs.logLogout(ID);
        closeStage();

        Parent parent = FXMLLoader.load(getClass().getResource("/ro/mta/library_project/UILogin.fxml"));
        Stage stage = new Stage(StageStyle.DECORATED);
        stage.setTitle("Login Window");
        stage.setScene(new Scene(parent));
        stage.show();
    }

}
