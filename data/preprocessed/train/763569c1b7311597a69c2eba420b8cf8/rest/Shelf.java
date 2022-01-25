package ro.mta.library_project.Shelf_sections;

import ro.mta.library_project.Book.Book;
import ro.mta.library_project.DBController.DBController;

import java.sql.ResultSet;
import java.sql.SQLException;

public class Shelf {
    int idShelf;
    String section;
    int allSpace;
    int availableSpace;

    public Shelf(String section, int numberOfVolumes) throws SQLException {
        this.section = section;
        ResultSet resultSet;
        resultSet = DBController.getInstance().SelectShelf(section, numberOfVolumes);
        if (resultSet.next()) {
            this.idShelf = resultSet.getInt("IDraft");
            this.allSpace = resultSet.getInt("NumarLocuri");
            this.availableSpace = resultSet.getInt("LocuriLibere");
        }

    }

    public Shelf(int toBeErasedID) throws SQLException {
        ResultSet resultSet;
        resultSet = DBController.getInstance().SelectShelf(toBeErasedID);
        if (resultSet.next()) {
            this.section = resultSet.getString("DenumireSectiune");
            this.idShelf = resultSet.getInt("Raft");
            this.allSpace = resultSet.getInt("NumarLocuri");
            this.availableSpace = resultSet.getInt("LocuriLibere");
        }
    }

    public Shelf() {

    }


    public void addBook(Book toBeInserted) throws SQLException {
        String dateNow = String.valueOf(java.time.LocalDate.now());
        int idAuthor = 0;
        int idSection = 0;
        int idType = 0;
        ResultSet resultSet = DBController.getInstance().Select("Autori", "Nume", toBeInserted.getAuthor());
        if (resultSet.next()) {
            idAuthor = resultSet.getInt("ID");
        }
        resultSet = DBController.getInstance().Select("Sectiuni", "DenumireSectiune", toBeInserted.getGenre());
        if (resultSet.next()) {
            idSection = resultSet.getInt("ID");
        }
        resultSet = DBController.getInstance().Select("Tipuri", "NumeTip", toBeInserted.getType());
        if (resultSet.next()) {
            idType = resultSet.getInt("ID");
        }
        DBController.getInstance().BookInsert(toBeInserted.getTitle(), String.valueOf(idAuthor), String.valueOf(toBeInserted.getNumberPages()),
                toBeInserted.getPublishingDate().toString(), dateNow, String.valueOf(idType), String.valueOf(toBeInserted.getNumberVolumes()), String.valueOf(this.idShelf), String.valueOf(idSection), "");
    }

    public void eraseBook(int toBeErasedID) {
        DBController.getInstance().DeleteBook(toBeErasedID);
    }

    public void showAvailableBooksOnShelf() throws SQLException {
        ResultSet resultSet = DBController.getInstance().BooksListing("Carti.Raft", String.valueOf(this.idShelf));
        while (resultSet.next()) {
            System.out.println(resultSet.getString("ID") + " " + resultSet.getString("Titlu") + " " + resultSet.getString("Prenume") +
                    " " + resultSet.getString("Nume") + " " + resultSet.getString("NumarPagini") + " " + resultSet.getString("Tip") + " " + resultSet.getString("Sectiune"));
        }
    }
}