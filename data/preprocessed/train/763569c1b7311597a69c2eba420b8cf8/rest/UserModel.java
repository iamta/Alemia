package ro.mta.library_project.Models;

import javafx.beans.property.IntegerProperty;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

/**
 * Clasa Model pentru un user inregistrat
 *
 * @author Lupu Marcela
 */
public class UserModel {
    IntegerProperty userId;
    StringProperty firstName;
    StringProperty lastName;
    StringProperty birthDate;
    StringProperty CNP;
    StringProperty username;
    StringProperty password;
    IntegerProperty idRole;

    public UserModel(int userId, String firstName, String lastName, String birthDate, String CNP, String username, String password, int idRole) {
        this.userId = new SimpleIntegerProperty(userId);
        this.firstName = new SimpleStringProperty(firstName);
        this.lastName = new SimpleStringProperty(lastName);
        this.birthDate = new SimpleStringProperty(birthDate);
        this.CNP = new SimpleStringProperty(CNP);
        this.username = new SimpleStringProperty(username);
        this.password = new SimpleStringProperty(password);
        this.idRole = new SimpleIntegerProperty(idRole);
    }

    public UserModel(int userId, String firstName, String lastName, String birthDate, String CNP, String username) {
        this.userId = new SimpleIntegerProperty(userId);
        this.firstName = new SimpleStringProperty(firstName);
        this.lastName = new SimpleStringProperty(lastName);
        this.birthDate = new SimpleStringProperty(birthDate);
        this.CNP = new SimpleStringProperty(CNP);
        this.username = new SimpleStringProperty(username);
    }

    public int getUserId() {
        return userId.get();
    }

    public IntegerProperty userIdProperty() {
        return userId;
    }

    public void setUserId(int id) {
        this.userId.set(id);
    }

    public String getFirstName() {
        return firstName.get();
    }

    public StringProperty firstNameProperty() {
        return firstName;
    }

    public void setFirstName(String name) {
        this.firstName.set(name);
    }

    public String getLastName() {
        return lastName.get();
    }

    public StringProperty lastNameProperty() {
        return lastName;
    }

    public void setLastName(String name) {
        this.lastName.set(name);
    }

    public String getBirthDate() {
        return birthDate.get();
    }

    public StringProperty birthDateProperty() {
        return birthDate;
    }

    public void setBirthDate(String name) {
        this.birthDate.set(name);
    }

    public String getCNP() {
        return CNP.get();
    }

    public StringProperty CNPProperty() {
        return CNP;
    }

    public void setCNP(String name) {
        this.CNP.set(name);
    }

    public String getUsername() {
        return username.get();
    }

    public StringProperty usernameProperty() {
        return username;
    }

    public void setUsername(String name) {
        this.username.set(name);
    }

    public String getPassword() {
        return password.get();
    }

    public StringProperty passwordProperty() {
        return password;
    }

    public void setPassword(String name) {
        this.password.set(name);
    }

    public int getIdRole() {
        return idRole.get();
    }

    public IntegerProperty idRoleProperty() {
        return idRole;
    }

    public void setIdRole(int id) {
        this.idRole.set(id);
    }
}
