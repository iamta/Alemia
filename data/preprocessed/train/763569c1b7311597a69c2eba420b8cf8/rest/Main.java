package ro.mta.library_project.DBController;

import ro.mta.library_project.Models.ActionsModel;
import ro.mta.library_project.Models.ExtendedBook;
import ro.mta.library_project.Models.UserModel;
import ro.mta.library_project.People.IPerson;
import ro.mta.library_project.People.Librarian;
import ro.mta.library_project.Book.Book;

import ro.mta.library_project.People.Librarian;

import java.sql.ResultSet;
import java.util.ArrayList;


public class Main {
    public static void main(String[] args) {

        try{

//            DBController dbc=DBController.getInstance();
//            ArrayList<ExtendedBook> books=dbc.SelectExtendedBook("Titlu","Ion");
//            for(ExtendedBook book:books){
//                System.out.println(book.getBookId()+" "+book.getAuthor()+" "+book.getName());
//            }



        }catch(Exception e){
            System.out.println("Something went wrong in main DBController.");
        }

    }
}

