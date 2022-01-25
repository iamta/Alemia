package ro.mta.library_project.People;

import ro.mta.library_project.DBController.DBController;

import java.sql.ResultSet;
import java.sql.SQLException;

abstract public class User implements IPerson {
    protected String username;
    protected int id;

    User(int id, String username) {
        this.id = id;
        this.username = username;
    }



    User()
    {

    }


    public void showMenu() throws Exception {
    }

    public void AddUserByLibrarian(String secondName, String firstName, String birthDate, String CNP, String username, String password) {
    }

    public void PrintLocationOfBook(String id_book) {
    }

    public void BorrowBook(String code) {
    }


    public void PrintInformationBook(String title) {
    }

    public void DestroyBook(String id) {
    }

    public void SearchBook(String input, int choic) {
    }

    public void createAccount() throws Exception {
    }

    public void eraseAccount() throws Exception {
    }

    public void modifySection() throws Exception {
    }

    public int getID() {
        return 0;
    }

    public void seeTablePersoane() throws Exception {
    }

    public String getUsername() {
        return "";
    }

    public void seeTopElectronicBooks() throws SQLException {
        ResultSet resultSet= DBController.getInstance().SelectTopTen("CartiCitite", "NumarCitiri");
        while(resultSet.next())
            System.out.println(resultSet.getString("Titlu")+" "+ resultSet.getString("Prenume")+" "+resultSet.getString("Nume")+
                    " "+resultSet.getInt("NumarCitiri"));
    }


    public void seeTopBorrowedBooks() throws SQLException {
        ResultSet resultSet= DBController.getInstance().SelectTopTen("CartiImprumutate","NumarImprumuturi");
        while(resultSet.next())
            System.out.println(resultSet.getString("Titlu")+" "+ resultSet.getString("Prenume")+" "+resultSet.getString("Nume")+
                    " "+resultSet.getInt("NumarImprumuturi"));
    }

}


