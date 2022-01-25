package ro.mta.library_project.Models;
import javafx.beans.property.IntegerProperty;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

import javafx.beans.property.IntegerProperty;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

/**
 * Clasa Model pentru actiunile unui utilizator inregistrat
 *
 * @author Lupu Marcela
 */
public class ActionsModel {
    IntegerProperty idActionsModel;
    IntegerProperty idUser;
    IntegerProperty idAction;
    StringProperty dateString;
    StringProperty details;

    public ActionsModel(int userId, int idAction, int idActionModel, String dateStr, String details) {
        this.idUser = new SimpleIntegerProperty(userId);
        this.idAction = new SimpleIntegerProperty(idAction);
        this.idActionsModel = new SimpleIntegerProperty(idActionModel);
        this.dateString = new SimpleStringProperty((dateStr));
        this.details = new SimpleStringProperty(details);
    }

    public ActionsModel(String dateStr, String details) {
        this.dateString = new SimpleStringProperty((dateStr));
        this.details = new SimpleStringProperty(details);
    }

    public int getIdActionsModel() {
        return idActionsModel.get();
    }

    public IntegerProperty idActionsModelProperty() {
        return idActionsModel;
    }

    public void setIdActionsModel(int id) {
        this.idActionsModel.set(id);
    }

    public int getIdUser() {
        return idUser.get();
    }

    public IntegerProperty idUserModelProperty() {
        return idUser;
    }

    public void setIdUser(int id) {
        this.idUser.set(id);
    }

    public int getIdAction() {
        return idAction.get();
    }

    public IntegerProperty idActionModelProperty() {
        return idAction;
    }

    public void setIdAction(int id) {
        this.idAction.set(id);
    }

    public String getDateString() {
        return dateString.get();
    }

    public StringProperty dateStringProperty() {
        return dateString;
    }

    public void setDateString(String name) {
        this.dateString.set(name);
    }

    public String getDetails() {
        return details.get();
    }

    public StringProperty detailsProperty() {
        return details;
    }

    public void setDetails(String name) {
        this.details.set(name);
    }
}