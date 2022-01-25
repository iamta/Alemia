package ro.mta.library_project.books;

import ro.mta.library_project.Book.Book;
import ro.mta.library_project.DBController.DBController;

import java.awt.*;
import java.net.URI;
import javax.security.sasl.AuthorizeCallback;
import java.io.*;
import java.sql.ResultSet;
import java.text.SimpleDateFormat;
import java.time.LocalDate;
import java.util.Date;

public class PhysicalBook extends Book{
    private int NumberVolumes;
    private int Status;

    PhysicalBook()
    {

    }


    PhysicalBook(int id, String title, String author, int nr_pag, String genre, LocalDate Pub_year)
    {
        setIdBook(id);
        setTitle(title);
        setAuthor(author);
        setNumberPages(nr_pag);
        setGenre(genre);
        setPublishingDate(Pub_year);
        try
        {
            DBController dbc = DBController.getInstance();
            ResultSet toGetNumberVolumes = null;
            toGetNumberVolumes = dbc.Select("Carti", "ID", String.valueOf(this.getIdBook()));
            this.NumberVolumes=toGetNumberVolumes.getInt(8);

            ResultSet toGetStatus = null;
            toGetStatus=dbc.Select("Imprumuturi", "CarteFizica", String.valueOf(this.getIdBook()));
            this.Status =toGetStatus.getInt(5);
        }
        catch(Exception e)
        {
            System.out.println("Something went wrong.");
        }
    }

    public void setNumberVolumes(int numberOfVolumes) {
        this.NumberVolumes = numberOfVolumes;
    }
    public int getNumberVolumes() {
        return this.NumberVolumes ;
    }

    public void setStatus(int Status) {
        this.Status = Status;
    }
    public int getStatus() {
        return this.Status ;
    }

    public void print()
    {
        System.out.print(this.getTitle()+" \nAuthor: "+this.getAuthor()+" \nPublishingYear: "+this.getPublishingDate()+
                " \nGenre: "+this.getGenre() + " \nNumber of Pages: "+this.getNumberPages()+" \nNumberVolumes: "+this.NumberVolumes+
                " \nStatus: "+this.Status+" \n");
    }
}
