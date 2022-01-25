package ro.mta.library_project.Controllers.AdminControllers;

import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.TextField;
import ro.mta.library_project.People.DaoPeopleLogs;

/**
 * Clasa controller pentru interfata ModifyAccount
 *
 * @author Cioaca Andrei
 */
public class UIModifyAccountController {

    private int ID;
    private String Username;
    @FXML
    private TextField textFieldUsernameDeModificat;
    @FXML
    private TextField textFieldNewRol;
    @FXML
    private TextField textFieldNewUsername;
    @FXML
    private TextField textFieldNewPassword;
    @FXML
    private Label afisEroare;

    /**
     * Metoda seteaza variabila ID
     *
     * @param ID ID-ul adminului care a deschis aceasta fereastra
     */
    protected void setID(int ID) {
        this.ID = ID;
    }

    /**
     * Metoda seteaza variabila Username
     *
     * @param Username username-ul adminului care a deschis aceasta fereastra
     */
    protected void setUsername(String Username) {
        this.Username = Username;
    }

    /**
     * Metoda se ocupa de modificarea unui cont
     */
    @FXML
    protected void handleModifyAccountButton() throws Exception {
        if (textFieldUsernameDeModificat.getText() != "" && textFieldNewRol.getText() != "" ||
                textFieldNewUsername.getText() != "" || textFieldNewPassword.getText() != "") {
            afisEroare.setText("");
            afisEroare.setStyle("-fx-background-color:#21242b; -fx-text-fill:white");

            String str = "Adminul " + this.Username + " a modificat un cont cu urmatoarele informatii: username-" +
                    textFieldUsernameDeModificat.getText();

            if (textFieldNewPassword.getText() != "") {
                str = str + ", parola noua";
                DaoPeopleLogs.modifyAccount(textFieldUsernameDeModificat.getText(), 3,
                        textFieldNewPassword.getText());
            }
            if (textFieldNewRol.getText() != "") {
                try {
                    int rol = Integer.parseInt(textFieldNewRol.getText());

                    if (!(rol > 0 && rol < 4)) {
                        throw new java.lang.RuntimeException();
                    }
                } catch (Exception e) {
                    afisEroare.setText("   Rolul nu este bun");
                    afisEroare.setStyle("-fx-background-color:#373c48; -fx-text-fill:white");
                    return;
                }

                str = str + ", rol nou-" + textFieldNewRol.getText();
                DaoPeopleLogs.modifyAccount(textFieldUsernameDeModificat.getText(), 1,
                        textFieldNewRol.getText());
            }
            if (textFieldNewUsername.getText() != "") {
                if (DaoPeopleLogs.verifyUsername(textFieldNewUsername.getText())) {
                    afisEroare.setText("   Username folosit, alegeti altul");
                    afisEroare.setStyle("-fx-background-color:#373c48; -fx-text-fill:white");
                } else {
                    afisEroare.setText("");
                    afisEroare.setStyle("-fx-background-color:#21242b; -fx-text-fill:white");

                    str = str + ", username nou-" + textFieldNewUsername.getText();
                    DaoPeopleLogs.modifyAccount(textFieldUsernameDeModificat.getText(), 2,
                            textFieldNewUsername.getText());
                }
            }

            DaoPeopleLogs.logModifySection(this.ID, str);

            afisEroare.setText("   Cont modificat cu succes");
            afisEroare.setStyle("-fx-background-color:#21242b; -fx-text-fill:white");
        } else {
            afisEroare.setText("   Completati cel putin un camp din zona de jos");
            afisEroare.setStyle("-fx-background-color:#373c48; -fx-text-fill:white");
        }
    }
}
