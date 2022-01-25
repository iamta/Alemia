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

public class Archive extends Book {
    private int NumberVolumes;

    Archive()
    {

    }


    Archive(int id, String title, String author, int nr_pag, String genre, LocalDate Pub_year)
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

    //afiseaza titlul si autorul unei arhive
    public void seeArchiveDetails()
    {
        System.out.print("Title :"+this.getTitle()+" \nAuthor: "+this.getAuthor()+"\n");
    }

}
