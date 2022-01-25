package ro.mta.library_project.People;

import ro.mta.library_project.DBController.DBController;

import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.Objects;
import java.util.Scanner;

public class Unregistered extends User {
    @Override
    public void showMenu() throws SQLException {
        int response=1;
        String input;
        ResultSet searchResult;
        int choice;
        int gasit=0;
        System.out.println("Bine ai venit!\n Fara cont creat, poti doar sa vezi ce iti putem oferi!\n");
        System.out.println("Vreau sa caut o carte dupa:\n 1) Titlu \n 2) Autor \n 3) Categorie \n 4) Tip \n");
        Scanner keyboard = new Scanner(System.in);
        while(response!=0) {
            System.out.println("Introdu optiunea pe care ti-o doresti\n");
            choice=keyboard.nextInt();
            keyboard.nextLine();
            if (choice==1) {

                System.out.println("Introdu numele cartii\n");
                input = keyboard.nextLine();
                searchResult= DBController.getInstance().BooksListing("Titlu",input);
                while(searchResult.next()) {
                    gasit=1;
                    System.out.println(searchResult.getString("ID")+" "+ searchResult.getString("Titlu")+" "+searchResult.getString("Prenume")+
                            " "+searchResult.getString("Nume")+" "+searchResult.getString("NumarPagini")+" "+searchResult.getString("Tip")+" "+searchResult.getString("Sectiune"));
                }
                if(gasit==0) System.out.println("Nu avem nimic in biblioteca");
            }
            else if(choice==2) {
                System.out.println("Introdu numele autorului cartii\n");
                input = keyboard.nextLine();
                searchResult= DBController.getInstance().BooksListing("Nume",input);
                while(searchResult.next()) {
                    gasit=1;
                    System.out.println(searchResult.getString("ID")+" "+ searchResult.getString("Titlu")+" "+searchResult.getString("Prenume")+
                            " "+searchResult.getString("Nume")+" "+searchResult.getString("NumarPagini")+" "+searchResult.getString("Tip")+" "+searchResult.getString("Sectiune"));
                }
                if(gasit==0) System.out.println("Nu avem nimic in biblioteca");
                gasit=0;
            }
            else if(choice==3) {
                System.out.println("Introdu categoria cartii din cele disponibile\n");
                searchResult= DBController.getInstance().Select("Sectiuni");
                while(searchResult.next()) {
                    System.out.println(searchResult.getString("ID")+" "+ searchResult.getString("DenumireSectiune"));
                }
                input = keyboard.nextLine();
                searchResult= DBController.getInstance().BooksListing("Sectiuni.DenumireSectiune",input);
                while(searchResult.next()) {
                    gasit=1;
                    System.out.println(searchResult.getString("ID")+" "+ searchResult.getString("Titlu")+" "+searchResult.getString("Prenume")+
                            " "+searchResult.getString("Nume")+" "+searchResult.getString("NumarPagini")+" "+searchResult.getString("Tip")+" "+searchResult.getString("Sectiune"));
                }
                if(gasit==0) System.out.println("Nu avem nimic in biblioteca");
                gasit=0;
            }
            else if(choice==4) {
                System.out.println("Introdu tipul cartii din cele disponibile\n");
                searchResult= DBController.getInstance().Select("Tipuri");
                while(searchResult.next()) {
                    System.out.println(searchResult.getString("ID")+" "+ searchResult.getString("NumeTip"));
                }
                input = keyboard.nextLine();
                searchResult= DBController.getInstance().BooksListing("Tipuri.NumeTip",input);
                while(searchResult.next()) {
                    gasit=1;
                    System.out.println(searchResult.getString("ID")+" "+ searchResult.getString("Titlu")+" "+searchResult.getString("Prenume")+
                            " "+searchResult.getString("Nume")+" "+searchResult.getString("NumarPagini")+" "+searchResult.getString("Tip")+" "+searchResult.getString("Sectiune"));
                }
                if(gasit==0) System.out.println("Nu avem nimic in biblioteca");
                gasit=0;
            }

            System.out.println("Te mai putem ajuta cu ceva? 1-Da/0-Nu\n");
            response= keyboard.nextInt();
            keyboard.nextLine();
            if(response==0)
            {
                System.out.println("La revedere!\n");
            }
        }

    }



    @Override
    public void AddUserByLibrarian(String secondName,String firstName,String birthDate,String CNP,String username,String password){};

    @Override
    public void PrintLocationOfBook(String id_book){};

    @Override
    public void BorrowBook(String code){};

    @Override
    public void PrintInformationBook(String title){};

    @Override
    public void DestroyBook(String id){};

    @Override
    public void SearchBook(String input,int choic){};

    @Override
    public void createAccount(){};

    @Override
    public void eraseAccount(){};

    @Override
    public void modifySection(){};
    public int getID(){return 0;};
}
