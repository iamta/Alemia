package ro.mta.library_project.DBController;

import ro.mta.library_project.Book.Book;
import ro.mta.library_project.Models.ActionsModel;
import ro.mta.library_project.Models.ExtendedBook;
import ro.mta.library_project.Models.UserModel;

import java.sql.*;
import java.text.SimpleDateFormat;
import java.time.format.DateTimeFormatter;
import java.sql.Timestamp;
import java.util.*;
import java.util.Date;

public class DBController {
    private static DBController instance=null;
    private static Connection connection=null;
    private ResultSet resultSet=null;
    private DBController() {
        try {
            Properties properties = new Properties();

            properties.load(DBController.class.getClassLoader().getResourceAsStream("application.properties"));
            connection = DriverManager.getConnection(properties.getProperty("url"), properties);

        }catch (Exception e){
            System.out.println("Something went wrong in DBController.");
        }
    }

    public static DBController getInstance(){
        if(instance==null){
            instance=new DBController();
        }

        return instance;
    }

    public ResultSet Select(String tableName){
        try {
            Statement statement = connection.createStatement();
            String selectSql = "SELECT * FROM "+tableName;
            resultSet = statement.executeQuery(selectSql);

        }catch(Exception e){
            System.out.println("Something went wrong in select * from table.");
        }
        return resultSet;
    }

    public ResultSet Select(String tableName,String column, String value){
        try {
            Statement statement = connection.createStatement();
            String selectSql = "SELECT * FROM "+tableName+" WHERE "+column+" = '"+value+"'";
            resultSet = statement.executeQuery(selectSql);

        }catch(Exception e){
            System.out.println("Something went wrong in here.");
        }
        return resultSet;
    }

    public ResultSet Select(String tableName,String column, String[] vector){
        try {
            Statement statement = connection.createStatement();

            String selectSql = "SELECT * FROM "+tableName+" WHERE "+column+" in (";
            for(int i=0;i<vector.length;i++){
                selectSql+=vector[i];
                if(i< vector.length-1){
                    selectSql+=",";
                }
                else{
                    selectSql+=")";
                }
            }
            resultSet = statement.executeQuery(selectSql);

        }catch(Exception e){
            System.out.println("Something went wrong.");
        }
        return resultSet;
    }

    public void PersonInsert(String secondName,String firstName,String birthDate,String CNP,String username,
                             String password,String role,String createdBy,String salt){
        try {
            Statement statement = connection.createStatement();
            String insertSql = "INSERT INTO Persoane Values("+"'" + secondName+"'" + "," +"'"+ firstName +"'"+ ","+"'"+ birthDate +"'"+ "," +"'"+ CNP +"'"+ ","
                    +"'"+ username +"'"+ "," +"'"+ password +"'"+ ","+"'"+ role +"'"+ ","+"'" + createdBy+"'" + ","+"'"+salt+"'"+")";

            statement.executeUpdate(insertSql);


        }catch (Exception e){
            System.out.println("Something went wrong inserting a person.");
        }

    }

    public void BookInsert(String title,String author,String numberOfPages,String publicationDate,String acquisitionDate,
                           String type,String numberOfVolumes,String shelf,String section,String bookURL){
        try {
            Statement statement = connection.createStatement();
            String insertSql = "INSERT INTO Carti Values("+"'" + title+"'" + "," +"'"+ author +"'"+ ","+"'"+ numberOfPages +"'"+ "," +"'"+ publicationDate +"'"+ ","
                    +"'"+ acquisitionDate +"'"+ "," +"'"+ type +"'"+ ","+"'"+ numberOfVolumes +"'"+ ","+"'" + shelf+"'" + ","+"'"+section+"'"+ ","+"'"+bookURL+"'"+")";

            //Insert INTO Carti VALUES('Carte','1','220','1999-11-20T00:00:00.0000000','2017-11-20T00:00:00.0000000','2','1','1','1','')
            statement.executeUpdate(insertSql);


        }catch (Exception e){
            System.out.println("Something went wrong in inserting a book.");
        }

    }

    public void BorrowRequestInsert(String username,String dataRequest,String cod,String carteFizica){
        try {
            Statement statement = connection.createStatement();
            String insertSql = "INSERT INTO CereriImprumut Values("+ username+ "," +"'"+ dataRequest +"'"+ ","+"'"+ cod +"'"+ "," +carteFizica+")";

            statement.executeUpdate(insertSql);


        }catch (Exception e){
            System.out.println("Something went wrong in borrow request.");
        }

    }

    public ResultSet BooksListing(String column, String value){
        try {
            Statement statement = connection.createStatement();
            String selectSql = "select Carti.ID as ID, Titlu, Autori.Prenume as Prenume, Autori.Nume as Nume, " +
                    "NumarPagini, Tipuri.NumeTip as Tip, Sectiuni.DenumireSectiune as Sectiune from Carti inner " +
                    "join Autori on Autori.ID=Carti.ID inner join Sectiuni on Sectiuni.ID=Carti.Sectiune inner join " +
                    "Tipuri on Tipuri.ID=Carti.Tip where "+column+" = '"+value+"'";
            resultSet = statement.executeQuery(selectSql);

        }catch(Exception e){
            System.out.println("Something went wrong in book listing");
        }
        return resultSet;
    }

    public void DeleteBook(int ID){
        try {
            Statement statement = connection.createStatement();
            String deleteSql ="DELETE FROM Carti WHERE id = "+String.valueOf(ID)+";";
            statement.executeUpdate(deleteSql);


        }catch (Exception e){
            System.out.println("Something went wrong in deleting book.");
        }
    }

    public int GetNumberOfRows(String tableName){
        int counter=0;
        try {
            Statement statement = connection.createStatement();
            String selectSql = "SELECT * FROM "+tableName;
            resultSet = statement.executeQuery(selectSql);
            while (resultSet.next()) {
                counter++;
            }

        }catch(Exception e){
            System.out.println("Something went wrong in getting number of rows.");
        }
        return counter;
    }

    public int GetNumberOfRows(String tableName,String column, String value){
        int counter=0;
        try {
            Statement statement = connection.createStatement();
            String selectSql = "SELECT * FROM "+tableName+" WHERE "+column+" = '"+value+"'";
            resultSet = statement.executeQuery(selectSql);
            while (resultSet.next()) {
                counter++;
            }
        }catch(Exception e){
            System.out.println("Something went wrong.");
        }
        return counter;
    }

    public void UpdateValue(String tableName,String setColumn,String setValue,String conditionColumn,String conditionValue){
        try {
            Statement statement = connection.createStatement();
            String insertSql = "UPDATE "+tableName+" SET "+setColumn+" = '"+setValue+"' WHERE "+conditionColumn+" = '"+conditionValue+"'";

            statement.executeUpdate(insertSql);

        }catch (Exception e){
            System.out.println("Something went wrong.");
        }

    }

    public void BorrowInsert(String username,String dateBorrow,String dateRetur,String bookFormat,String realReturDate,String aspect,String librarian){
        try {
            Statement statement = connection.createStatement();
            String insertSql = "INSERT INTO Imprumuturi Values("+ username+ "," +"'"+ dateBorrow +"'"+ ","+"'"+ dateRetur +"'"+ "," +bookFormat+ "," +"'"+
                    realReturDate +"'"+ ","+"'"+ aspect +"'"+ ","+"'"+ librarian +"'"+")";

            statement.executeUpdate(insertSql);


        }catch (Exception e){
            System.out.println("Something went wrong in borrow insert.");
        }

    }
    public void BorrowInsertHash(String username,String dateBorrow,String dateRetur,String bookFormat,String realReturDate,String aspect,String librarian,String hash){
        try {
            Statement statement = connection.createStatement();
            String insertSql = "INSERT INTO Imprumuturi Values("+ username+ "," +"'"+ dateBorrow +"'"+ ","+"'"+ dateRetur +"'"+ "," +bookFormat+ "," +"'"+
                    realReturDate +"'"+ ","+"'"+ aspect +"'"+ ","+"'"+ librarian +"'"+ ","+"'"+ hash+"'"+")";

            statement.executeUpdate(insertSql);


        }catch (Exception e){
            System.out.println("Something went wrong in borrow insert hash.");
        }

    }

    public ResultSet SelectWithinRange(String tableName,int start,int end){
        try {

            Statement statement = connection.createStatement();
            String selectSql = "SELECT  * FROM (SELECT *, ROW_NUMBER() OVER (ORDER BY Id) AS 'RowNumber' FROM "+  tableName  + ") AS A WHERE   RowNumber " +
                    "between " + String.valueOf(start) + " and " + String.valueOf(end) + " ";

            resultSet = statement.executeQuery(selectSql);

        }catch(Exception e){
            System.out.println("Something went wrong in select within range.");
        }
        return resultSet;
    }

    public ResultSet InnerSelect(String table1,String table2,String condition1,String condition2){

        try {

            Statement statement = connection.createStatement();
            String selectSql = "SELECT * FROM " + table1 + " inner join " + table2 + " ON " + condition1 + "=" + condition2 + ";";

            resultSet = statement.executeQuery(selectSql);

        }catch(Exception e){
            System.out.println("Something went wrong in inner select.");
        }
        return resultSet;
    }

    public ResultSet InnerSelect_twoConditions(String table1,String table2,String condition1,String condition2,String condition3,String condition4,String interestColumn1,String interestColumn2){

        try {

            Statement statement = connection.createStatement();
            String selectSql = "SELECT * FROM " + table1 + " inner join " + table2 + " ON " + interestColumn1 + " = " + interestColumn2 + " where " +
                    condition1+ " = " +condition2 +" and "+condition3+" < "+condition4 +";";

            resultSet = statement.executeQuery(selectSql);

        }catch(Exception e){
            System.out.println("Something went wrong in inner select 2 conditions.");
        }
        return resultSet;
    }

    public ResultSet SelectShelf(String section,int numberOfVolumes){

        try {

            Statement statement = connection.createStatement();
            String selectSql = "select IDraft, IDsectiune, NumarLocuri, LocuriLibere, DenumireSectiune from TabelJonctiune \n" +
                    "inner join Rafturi on Rafturi.ID=TabelJonctiune.IDraft inner join Sectiuni on Sectiuni.ID=TabelJonctiune.IDsectiune \n" +
                    "where DenumireSectiune = '" + section + "' and LocuriLibere>" + String.valueOf(numberOfVolumes) + ";";

            resultSet = statement.executeQuery(selectSql);

        }catch(Exception e){
            System.out.println("Something went wrong in inner select.");
        }
        return resultSet;
    }

    public ResultSet SelectShelf(int idToBeErased){

        try {

            Statement statement = connection.createStatement();
            String selectSql = "select Carti.Raft, Carti.Sectiune, Rafturi.NumarLocuri, Rafturi.LocuriLibere, Sectiuni.DenumireSectiune \n" +
                    "from Carti inner join Rafturi on Rafturi.ID=Carti.Raft\n" +
                    "inner join Sectiuni on Sectiuni.ID=Carti.Sectiune where Carti.ID= " + String.valueOf(idToBeErased) + ";";

            resultSet = statement.executeQuery(selectSql);

        }catch(Exception e){
            System.out.println("Something went wrong in inner select.");
        }
        return resultSet;
    }

    public void ActionInsert(String action){
        try {
            Statement statement = connection.createStatement();
            String insertSql = "insert into Actiuni values('" + action + "')";

            statement.executeUpdate(insertSql);


        }catch (Exception e){
            System.out.println("Something went wrong in action insert.");
        }

    }

    public void LoguriActiuniInsert(int idUser,int idAction,String details){
        try {
            Statement statement = connection.createStatement();

            String insertSql = "insert into LoguriActiuni values(" + String.valueOf(idUser) + "," + String.valueOf(idAction) + ", CURRENT_TIMESTAMP,'"+details+"')";
            statement.executeUpdate(insertSql);


        }catch (Exception e){
            System.out.println("Something went wrong in loguri actiuni insert.");
        }

    }

    public ResultSet InnerActiuniLoguriActiuniSelect(int id){

        try {

            Statement statement = connection.createStatement();
            String selectSql = "select * from Actiuni inner join LoguriActiuni on Actiuni.ID=LoguriActiuni.IDactiune where IDuser=" + id + "";

            resultSet = statement.executeQuery(selectSql);

        }catch(Exception e){
            System.out.println("Something went wrong in inner select.");
        }
        return resultSet;
    }

    public ResultSet SelectTopTen(String tableName){
        try {
            Statement statement = connection.createStatement();
            String selectSql = "SELECT top 10 * FROM "+tableName;
            resultSet = statement.executeQuery(selectSql);

        }catch(Exception e){
            System.out.println("Something went wrong in select top 10 from table.");
        }
        return resultSet;
    }

    public ResultSet SelectTopTen(String tableName,String orderCondition){
        try {
            Statement statement = connection.createStatement();
            String selectSql = "SELECT top 10 * FROM "+tableName+" order by "+orderCondition+" desc";
            resultSet = statement.executeQuery(selectSql);

        }catch(Exception e){
            System.out.println("Something went wrong in select top ten from table order desc.");
        }
        return resultSet;
    }

    public ArrayList<Book> BookAllInfoListing(String columnName,String value){
        ArrayList<Book> books=new ArrayList<>();
        try {
            Statement statement = connection.createStatement();
            String selectSql = "Select c.ID, c.Titlu, a.Nume,a.Prenume,c.NumarPagini,c.DataPublicarii,c.DataAdaugarii," +
                    "t.NumeTip,c.NumarVolume,c.Raft,s.DenumireSectiune,c.UrlCarte  from Carti c inner join Autori a on " +
                    "a.ID=c.Autor inner join Tipuri t on t.ID=c.Tip inner join Sectiuni s on s.ID=c.Sectiune" +
                    " where c."+columnName+"='"+value+"'";
            resultSet = statement.executeQuery(selectSql);

            while(resultSet.next()){
                Book book=new Book();

                book.setIdBook(resultSet.getInt(1));
                book.setTitle(resultSet.getString(2));
                book.setAuthor(resultSet.getString(3)+" "+resultSet.getString(4));
                book.setNumberPages(resultSet.getInt(5));
                book.setPublishingDate(resultSet.getDate(6).toLocalDate());
                book.setType(resultSet.getString(8));
                book.setNumberVolumes(resultSet.getInt(9));
                book.setShelf(resultSet.getInt(10));
                book.setGenre(resultSet.getString(11));

                books.add(book);

            }

        }catch(Exception e){
            System.out.println("Something went wrong in select all info from books.");
        }

        return books;

    }

    public ArrayList<Book> BookAllInfoListing(){
        ArrayList<Book> books=new ArrayList<>();
        try {
            Statement statement = connection.createStatement();
            String selectSql = "Select c.ID, c.Titlu, a.Nume,a.Prenume,c.NumarPagini,c.DataPublicarii,c.DataAdaugarii," +
                    "t.NumeTip,c.NumarVolume,c.Raft,s.DenumireSectiune,c.UrlCarte  from Carti c inner join Autori a on " +
                    "a.ID=c.Autor inner join Tipuri t on t.ID=c.Tip inner join Sectiuni s on s.ID=c.Sectiune";
            resultSet = statement.executeQuery(selectSql);

            while(resultSet.next()){
                Book book=new Book();

                book.setIdBook(resultSet.getInt(1));
                book.setTitle(resultSet.getString(2));
                book.setAuthor(resultSet.getString(3)+" "+resultSet.getString(4));
                book.setNumberPages(resultSet.getInt(5));
                book.setPublishingDate(resultSet.getDate(6).toLocalDate());
                book.setType(resultSet.getString(8));
                book.setNumberVolumes(resultSet.getInt(9));
                book.setShelf(resultSet.getInt(10));
                book.setGenre(resultSet.getString(11));

                books.add(book);

            }

        }catch(Exception e){
            System.out.println("Something went wrong in select all info from books.");
        }

        return books;

    }

    public LibrarianData SelectLibrarian(int id){
        LibrarianData librarian=null;
        try {
            Statement statement = connection.createStatement();
            String selectSql = "SELECT * FROM Persoane WHERE ID = "+id;
            resultSet = statement.executeQuery(selectSql);
            resultSet.next();
            librarian=new LibrarianData(id,resultSet.getString(2),resultSet.getString(3)
                    ,resultSet.getString(4),resultSet.getString(5),resultSet.getString(6));

            return librarian;

        }catch(Exception e){
            System.out.println("Something went wrong in here.");
        }
        return librarian;
    }

    public ArrayList<BookDataUser1> BookDataUserListing(){
        ArrayList<BookDataUser1> books=new ArrayList<>();
        try {
            Statement statement = connection.createStatement();
            String selectSql = "Select c.ID, c.Titlu,c.Autor, a.Nume,a.Prenume,t.NumeTip,s.DenumireSectiune from Carti c " +
                    "inner join Autori a on a.ID=c.Autor inner join Tipuri t on t.ID=c.Tip inner join Sectiuni s on s.ID=c.Sectiune";
            resultSet = statement.executeQuery(selectSql);

            while(resultSet.next()){
                BookDataUser1 book=new BookDataUser1(resultSet.getInt(1),resultSet.getString(2),resultSet.getInt(3),
                        resultSet.getString(4),resultSet.getString(5),resultSet.getString(7),resultSet.getString(6));

                books.add(book);

            }

        }catch(Exception e){
            System.out.println("Something went wrong in book data user listing.");
        }

        return books;

    }

    public ArrayList<BookData> BookDataListing(){
        ArrayList<BookData> books=new ArrayList<>();
        try {
            Statement statement = connection.createStatement();
            String selectSql = "Select c.ID, c.Titlu,c.Autor, a.Nume,a.Prenume,t.NumeTip,s.DenumireSectiune, c.DataPublicarii, c.NumarPagini from Carti c " +
                    "inner join Autori a on a.ID=c.Autor inner join Tipuri t on t.ID=c.Tip inner join Sectiuni s on s.ID=c.Sectiune";
            resultSet = statement.executeQuery(selectSql);

            while(resultSet.next()){
                BookData book=new BookData(resultSet.getInt(1),resultSet.getString(2),resultSet.getInt(3),
                        resultSet.getString(4),resultSet.getString(5),resultSet.getInt(9),
                        resultSet.getString(7),resultSet.getString(8));
                books.add(book);

            }
        }catch(Exception e){
            System.out.println("Something went wrong in book data listing.");
        }

        return books;

    }


    public ArrayList<BookDataUser1> BookDataUserListing(String searchField,String searchValue){
        ArrayList<BookDataUser1> books=new ArrayList<>();
        try {
            Statement statement = connection.createStatement();
            String selectSql = "Select c.ID as ID, c.Titlu,c.Autor as Autor, a.Nume,a.Prenume,t.NumeTip,s.DenumireSectiune from Carti c " +
                    "inner join Autori a on a.ID=c.Autor inner join Tipuri t on t.ID=c.Tip inner join Sectiuni s on s.ID=c.Sectiune ";
            if((searchField=="ID")||(searchField=="Titlu")) {
                selectSql=selectSql+"where c." + searchField + "='" + searchValue + "'";
            }else if(searchField=="Tip"){
                selectSql=selectSql+"where t.NumeTip='" + searchValue + "'";
            }else if(searchField=="Sectiune"){
                selectSql=selectSql+"where s.DenumireSectiune='" + searchValue + "'";
            }else if(searchField=="Autor"){
                selectSql=selectSql+"where a.Nume='" + searchValue + "'";
            }
            resultSet = statement.executeQuery(selectSql);
            while(resultSet.next()){
                BookDataUser1 book=new BookDataUser1(resultSet.getInt(1),resultSet.getString(2),resultSet.getInt(3),
                        resultSet.getString(4),resultSet.getString(5),resultSet.getString(7),resultSet.getString(6));

                books.add(book);

            }

        }catch(Exception e){
            System.out.println("Something went wrong in book data user listing");
        }

        return books;

    }

    public ArrayList<LogsInfoUsers> SelectUserLogs(int id){
        ArrayList<LogsInfoUsers> logs=new ArrayList<>();
        try {
            Statement statement = connection.createStatement();
            String selectSql = "SELECT * FROM LoguriActiuni where IDuser = "+id;
            resultSet = statement.executeQuery(selectSql);
            while(resultSet.next()){
                LogsInfoUsers log=new LogsInfoUsers(resultSet.getString(5),
                        resultSet.getString(4).substring(0,10)+" "+resultSet.getString(4).substring(11,19) );
                logs.add(log);
            }

        }catch(Exception e){
            System.out.println("Something went wrong in book data user listing");
        }

        return logs;

    }

    public UserModel SelectUser(int id){
        UserModel user=null;
        try {
            Statement statement = connection.createStatement();
            String selectSql = "SELECT * FROM Persoane WHERE ID = "+id;
            resultSet = statement.executeQuery(selectSql);
            resultSet.next();
            user=new UserModel(id,resultSet.getString(3),resultSet.getString(2),
                    resultSet.getString(4),resultSet.getString(5),resultSet.getString(6),
                    resultSet.getString(7),resultSet.getInt(8));

            return user;

        }catch(Exception e){
            System.out.println("Something went wrong in here.");
        }
        return user;
    }

    public ArrayList<ExtendedBook> SelectExtendedBook(){
        ArrayList<ExtendedBook> books=new ArrayList<>();
        try {
            Statement statement = connection.createStatement();
            String selectSql = "Select c.ID, c.Titlu,c.Autor, a.Nume,a.Prenume,t.NumeTip,s.DenumireSectiune from Carti c " +
                    "inner join Autori a on a.ID=c.Autor inner join Tipuri t on t.ID=c.Tip inner join Sectiuni s on s.ID=c.Sectiune";
            resultSet = statement.executeQuery(selectSql);

            while(resultSet.next()){
                ExtendedBook book=new ExtendedBook(resultSet.getInt(1),resultSet.getString(2),resultSet.getString(5)+" "+
                        resultSet.getString(4),resultSet.getString(6),resultSet.getString(7));
                books.add(book);
            }

        }catch(Exception e){
            System.out.println("Something went wrong in book data user listing.");
        }

        return books;

    }

    public ArrayList<ExtendedBook> SelectExtendedBook(String searchField,String searchValue){
        ArrayList<ExtendedBook> books=new ArrayList<>();
        try {
            Statement statement = connection.createStatement();
            String selectSql = "Select c.ID as ID, c.Titlu,c.Autor as Autor, a.Nume,a.Prenume,t.NumeTip,s.DenumireSectiune from Carti c " +
                    "inner join Autori a on a.ID=c.Autor inner join Tipuri t on t.ID=c.Tip inner join Sectiuni s on s.ID=c.Sectiune ";
            if(searchField=="ID") {
                selectSql=selectSql+"where c." + searchField + "='" + searchValue + "'";
            }else if(searchField=="Tip"){
                selectSql=selectSql+"where t.NumeTip LIKE '%" + searchValue + "%'";
            }else if(searchField=="Sectiune"){
                selectSql=selectSql+"where s.DenumireSectiune LIKE '%" + searchValue + "%'";
            }else if(searchField=="Autor"){
                selectSql=selectSql+"where a.Nume LIKE '%" + searchValue + "%'";
            }else if(searchField=="Titlu"){
                selectSql=selectSql+"where c.Titlu LIKE '%"+ searchValue + "%'";
            }
            resultSet = statement.executeQuery(selectSql);
            while(resultSet.next()){
                ExtendedBook book=new ExtendedBook(resultSet.getInt(1),resultSet.getString(2),resultSet.getString(5)+" "+
                        resultSet.getString(4),resultSet.getString(6),resultSet.getString(7));
                books.add(book);
            }

        }catch(Exception e){
            System.out.println("Something went wrong in book data user listing");
        }

        return books;

    }

    public ArrayList<ActionsModel> GetUserActions(int id){
        ArrayList<ActionsModel> logs=new ArrayList<>();
        try {
            Statement statement = connection.createStatement();
            String selectSql = "SELECT * FROM LoguriActiuni where IDuser = "+id;
            resultSet = statement.executeQuery(selectSql);
            while(resultSet.next()){
                ActionsModel log=new ActionsModel(resultSet.getString(4).substring(0,10)+" "
                        +resultSet.getString(4).substring(11,19),resultSet.getString(5) );
                logs.add(log);
            }

        }catch(Exception e){
            System.out.println("Something went wrong in book data user listing");
        }

        return logs;

    }

    public void InsertWriter(String firstName,String lastName){
        try {
            Statement statement = connection.createStatement();
            String insertSql = "insert into Autori values('" + firstName + "','"+lastName+"')";

            statement.executeUpdate(insertSql);

        }catch (Exception e){
            System.out.println("Something went wrong in action insert.");
        }

    }

    public ArrayList<IDTitleBook> SelectIDTitleBook(){
        ArrayList<IDTitleBook> books=new ArrayList<>();
        try {
            Statement statement = connection.createStatement();
            String selectSql = "Select ID,Titlu from Carti";
            resultSet = statement.executeQuery(selectSql);

            while(resultSet.next()){
                IDTitleBook book=new IDTitleBook(resultSet.getInt(1),resultSet.getString(2));
                books.add(book);
            }

        }catch(Exception e){
            System.out.println("Something went wrong in book data user listing.");
        }

        return books;

    }
    public ArrayList<TopTenBooks> SelectTop(String tableName){
        ArrayList<TopTenBooks> topTen=new ArrayList<>();
        try {
            Statement statement = connection.createStatement();
            String selectSql = "SELECT top 10 * FROM "+tableName;
            resultSet = statement.executeQuery(selectSql);
            while(resultSet.next()){
                TopTenBooks book=new TopTenBooks(resultSet.getString(1),resultSet.getString(2),
                        resultSet.getString(3),resultSet.getInt(4));
                topTen.add(book);
            }
        }catch(Exception e){
            System.out.println("Something went wrong in select top 10 from table.");
        }
        return topTen;
    }


    public ArrayList<ExtendedBook> SelectBorrowedBooks(int userID){
        ArrayList<ExtendedBook> books=new ArrayList<>();
        try {
            Statement statement = connection.createStatement();
            String selectSql = "Select c.ID, c.Titlu,c.Autor, a.Nume,a.Prenume,t.NumeTip,s.DenumireSectiune," +
                    "i.DataReturReal,i.HashCarte from Carti c inner join Autori a on a.ID=c.Autor inner join Tipuri t " +
                    "on t.ID=c.Tip inner join Sectiuni s on s.ID=c.Sectiune inner join Imprumuturi i on i.CarteFizica=c.ID " +
                    "where i.Username="+String.valueOf(userID)+"";
            resultSet = statement.executeQuery(selectSql);

            while(resultSet.next()){
                ExtendedBook book=new ExtendedBook(resultSet.getInt(1),resultSet.getString(2),
                        resultSet.getString(5)+" "+ resultSet.getString(4),resultSet.getString(6),
                        resultSet.getString(7),resultSet.getString(8),resultSet.getString(9));
                books.add(book);
            }

        }catch(Exception e){
            System.out.println("Something went wrong in book data user listing.");
        }

        return books;

    }

    public ArrayList<TitlePagesBorrowed> SelectBorrowed(){
        ArrayList<TitlePagesBorrowed> borrowed=new ArrayList<>();
        try {
            Statement statement = connection.createStatement();
            String selectSql = "select Imprumuturi.CarteFizica,Carti.Titlu, [dbo].[Carti].NumarPagini from Imprumuturi inner join Carti on Carti.ID=[dbo].[Imprumuturi].CarteFizica";
            resultSet = statement.executeQuery(selectSql);
            while(resultSet.next()){
                TitlePagesBorrowed book=new TitlePagesBorrowed(resultSet.getInt(1),resultSet.getString(2), resultSet.getInt(3));
                borrowed.add(book);

            }

        }catch(Exception e){
            System.out.println("Something went wrong in select top 10 from table.");
        }
        return borrowed;
    }


}
