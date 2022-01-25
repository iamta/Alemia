package ro.mta.library_project.Controllers.AdminControllers;

import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import ro.mta.library_project.People.DaoPeopleLogs;

/**
 * Clasa controller pentru interfata CreateAccount
 *
 * @author Cioaca Andrei
 */
public class UICreateAccountController {

    @FXML
    private TextField textFieldNume;

    @FXML
    private TextField textFieldPrenume;

    @FXML
    private TextField textFieldDataNasterii;

    @FXML
    private TextField textFieldCNP;

    @FXML
    private TextField textFieldUsername;

    @FXML
    private PasswordField textFieldParola;

    @FXML
    private PasswordField textFieldParola2;

    @FXML
    private TextField textFieldRol;

    @FXML
    private TextField textFieldUsername2;

    @FXML
    private TextField textFieldUsername3;

    @FXML
    private Label afisEroare;

    private int ID;
    private String Username;

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
     * Metoda se ocupa de crearea unui cont
     */
    @FXML
    protected void handleCreateAccountButton() throws Exception {
        afisEroare.setText("");
        afisEroare.setStyle("-fx-background-color:#21242b; -fx-text-fill:white");

        if (textFieldNume.getText() != "" && textFieldPrenume.getText() != "" && textFieldDataNasterii.getText() != ""
                && textFieldCNP.getText() != "" && textFieldUsername.getText() != "" && textFieldParola.getText() != ""
                && textFieldParola2.getText() != "" && textFieldRol.getText() != "") {
            if (textFieldParola.getText().equals(textFieldParola2.getText())) {
                // daca e true inseamna ca Username-ul e folosit deja
                if (DaoPeopleLogs.verifyUsername(textFieldUsername.getText())) {
                    afisEroare.setText("   Username folosit, alegeti altul");
                    afisEroare.setStyle("-fx-background-color:#373c48; -fx-text-fill:white");
                } else {
                    afisEroare.setText("");
                    afisEroare.setStyle("-fx-background-color:#21242b; -fx-text-fill:white");

                    try {
                        int rol = Integer.parseInt(textFieldRol.getText());
                        if (rol < 0 || rol > 3) {
                            throw new java.lang.RuntimeException();
                        }
                    } catch (Exception e) {
                        afisEroare.setText("   Rolul nu este bun");
                        afisEroare.setStyle("-fx-background-color:#373c48; -fx-text-fill:white");
                        return;
                    }

                    try {
                        Integer.parseInt(textFieldCNP.getText());

                        if (textFieldCNP.getText().length() != 13) {
                            throw new java.lang.RuntimeException();
                        }
                    } catch (Exception e) {
                        afisEroare.setText("   CNP-ul nu este bun");
                        afisEroare.setStyle("-fx-background-color:#373c48; -fx-text-fill:white");
                        return;
                    }

                    try {
                        DaoPeopleLogs.createUser(textFieldNume.getText(), textFieldPrenume.getText(),
                                textFieldDataNasterii.getText(), textFieldCNP.getText(), textFieldUsername.getText(),
                                textFieldParola.getText(), Integer.parseInt(textFieldRol.getText()), this.ID);

                        String str = "Adminul " + this.Username + " a creat un cont cu urmatoarele informatii: " +
                                "nume-" + textFieldNume.getText() + ", prenume-" + textFieldPrenume.getText() +
                                ", data nasterii-" + textFieldDataNasterii.getText() +
                                ", CNP-" + textFieldCNP.getText() + ", username-" + textFieldUsername.getText() +
                                ", rol-" + Integer.parseInt(textFieldRol.getText());

                        DaoPeopleLogs.logCreateAccount(ID, 1, str);

                        afisEroare.setText("   Cont creat cu succes");
                        afisEroare.setStyle("-fx-background-color:#21242b; -fx-text-fill:white");
                    } catch (Exception e) {
                        afisEroare.setText("   Data nasterii nu este buna");
                        afisEroare.setStyle("-fx-background-color:#373c48; -fx-text-fill:white");
                    }


                }

            } else {
                afisEroare.setText("   Parolele difera");
                afisEroare.setStyle("-fx-background-color:#373c48; -fx-text-fill:white");
            }
        } else {
            afisEroare.setText("   Completati toate campurile dintr-o zona");
            afisEroare.setStyle("-fx-background-color:#373c48; -fx-text-fill:white");
        }
    }

    /**
     * Metoda se ocupa de stergerea unui cont
     */
    @FXML
    protected void handleDeleteAccountButton() throws Exception {
        afisEroare.setText("");
        afisEroare.setStyle("-fx-background-color:#21242b; -fx-text-fill:white");

        if (textFieldUsername2.getText() != "" && textFieldUsername3.getText() != "") {
            if (textFieldUsername2.getText().equals(textFieldUsername3.getText())) {
                afisEroare.setText("");
                afisEroare.setStyle("-fx-background-color:#21242b; -fx-text-fill:white");

                DaoPeopleLogs.deleteAccount(textFieldUsername2.getText());

                String str = "Adminul " + this.Username + " a sters un cont cu urmatoarele informatii: username-" +
                        textFieldUsername2.getText();
                DaoPeopleLogs.logEraseAccount(this.ID, str);

                afisEroare.setText("   Cont sters cu succes");
                afisEroare.setStyle("-fx-background-color:#21242b; -fx-text-fill:white");
            } else {
                afisEroare.setText("   Username-urile difera");
                afisEroare.setStyle("-fx-background-color:#373c48; -fx-text-fill:white");
            }
        } else {
            afisEroare.setText("   Completati toate campurile dintr-o zona");
            afisEroare.setStyle("-fx-background-color:#373c48; -fx-text-fill:white");
        }
    }
}
