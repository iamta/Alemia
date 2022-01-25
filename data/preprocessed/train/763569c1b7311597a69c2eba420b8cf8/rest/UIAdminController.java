package ro.mta.library_project.Controllers.AdminControllers;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.TextField;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import ro.mta.library_project.Controllers.AdminControllers.UICreateAccountController;
import ro.mta.library_project.Controllers.AdminControllers.UIModifyAccountController;
import ro.mta.library_project.People.DaoPeopleLogs;

/**
 * Clasa controller pentru interfata Admin
 *
 * @author Cioaca Andrei
 */
public class UIAdminController {
    @FXML
    protected TextField labelPentruID;

    private Parent root;

    private int ID;
    private String Username;

    /**
     * Metoda seteaza variabila ID
     *
     * @param ID ID-ul adminului care s-a logat
     */
    public void setID(int ID) {
        this.ID = ID;
        labelPentruID.setText(Integer.toString(ID));

    }

    /**
     * Metoda seteaza variabila Username
     *
     * @param Username username-ul adminului care s-a logat
     */
    public void setUsername(String Username) {
        this.Username = Username;
    }

    /**
     * Metoda inchide fereastra
     */
    private void closeStage() {
        ((Stage) labelPentruID.getScene().getWindow()).close();
    }

    /**
     * Metoda se ocupa de logout, jurnalizeaza actiunea si deschide interfata Login
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
     * Metoda se ocupa de afisarea interfetei VisualizeLoginLogoutLogs si jurnalizeaza aceasta actiune
     */
    public void handleVizualizareLoguriLoginLogoutButtonAction(ActionEvent event) throws Exception {
        String str = "Adminul " + Username + " a cerut sa vizualizeze tabela LoginHistory";
        DaoPeopleLogs.logSeeLoginLogout(ID, str);

        Stage stage = new Stage(StageStyle.DECORATED);
        Parent root = FXMLLoader.load(getClass().
                getResource("/ro/mta/library_project/AdminViews/UIVisualizeLoginLogoutLogs.fxml"));
        stage.setTitle("Login/Logout Logs Window");
        Scene scene = new Scene(root);
        stage.setScene(scene);
        stage.show();
    }

    /**
     * Metoda se ocupa de afisarea interfetei VisualizeActionLogs si jurnalizeaza aceasta actiune
     */
    public void handleVizualizareLoguriActiuniButtonAction(ActionEvent event) throws Exception {
        String str = "Adminul " + Username + " a cerut sa vizualizeze tabela LoguriActiuni";
        DaoPeopleLogs.logSeeActions(ID, str);

        Stage stage = new Stage(StageStyle.DECORATED);
        Parent root = FXMLLoader.load(getClass().
                getResource("/ro/mta/library_project/AdminViews/UIVisualizeActionLogs.fxml"));
        stage.setTitle("Action Logs Window");
        Scene scene = new Scene(root);
        stage.setScene(scene);
        stage.show();
    }

    /**
     * Metoda se ocupa de afisarea interfetei VisualizeAccounts si jurnalizeaza aceasta actiune
     */
    public void handleVizualizareConturiButtonAction(ActionEvent event) throws Exception {
        String str = "Adminul " + Username + " a cerut sa vizualizeze tabela Persoane";
        DaoPeopleLogs.setlogSeeTablePersoane(ID, str);

        Stage stage = new Stage(StageStyle.DECORATED);
        Parent root = FXMLLoader.load(getClass().
                getResource("/ro/mta/library_project/AdminViews/UIVisualizeAccounts.fxml"));
        stage.setTitle("Accounts Window");
        Scene scene = new Scene(root);
        stage.setScene(scene);
        stage.show();

    }

    /**
     * Metoda se ocupa de afisarea interfetei ModifyAccount si ii trimite ID-ul si Username-ul adminului
     */
    public void handleModificareContButtonAction(ActionEvent event) throws Exception {
        Stage stage = new Stage(StageStyle.DECORATED);
        FXMLLoader loader = new FXMLLoader(getClass().
                getResource("/ro/mta/library_project/AdminViews/UIModifyAccount.fxml"));
        root = loader.load();
        stage.setTitle("Modify Account Window");

        UIModifyAccountController uiModifyAccountController = loader.getController();
        uiModifyAccountController.setID(this.ID);
        uiModifyAccountController.setUsername(this.Username);

        Scene scene = new Scene(root);
        stage.setScene(scene);
        stage.show();
    }

    /**
     * Metoda se ocupa de afisarea interfetei CreateAccount si ii trimite ID-ul si Username-ul adminului
     */
    public void handleCreareContButtonAction(ActionEvent event) throws Exception {
        Stage stage = new Stage(StageStyle.DECORATED);
        FXMLLoader loader = new FXMLLoader(getClass().
                getResource("/ro/mta/library_project/AdminViews/UICreateAccount.fxml"));
        root = loader.load();
        stage.setTitle("Create/Delete Account Window");

        UICreateAccountController uiCreateAccountController = loader.getController();
        uiCreateAccountController.setID(this.ID);
        uiCreateAccountController.setUsername(this.Username);

        Scene scene = new Scene(root);
        stage.setScene(scene);
        stage.show();
    }
}
