package ro.mta.library_project.People;

import ro.mta.library_project.HelperClasses.ActionLogsHelperClass;
import ro.mta.library_project.HelperClasses.LoginLogoutHelperClass;
import ro.mta.library_project.HelperClasses.VisualizeAccountsHelperClass;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.LinkedList;
import java.util.List;
import java.util.Properties;
import java.util.logging.Logger;

/**
 * Clasa de conexiune cu baza de date pe tabelele Persoane, LoginHistory, LoguriActiuni
 * Este folosita doar de Interfata Login si de tot ce tine de Interfata Admin
 *
 * @author Cioaca Andrei
 */
public class DaoPeopleLogs {

    private static final Logger log;
    private static Properties properties;
    private static Connection connection;
    private static Statement statement;

    static {
        System.setProperty("java.util.logging.SimpleFormatter.format", "[%4$-7s] %5$s %n");
        log = Logger.getLogger(ro.mta.library_project.People.DaoPeopleLogs.class.getName());
    }

    /**
     * Metoda initializeaza conexiunea cu baza de date
     */
    public static void init() throws Exception {
        log.info("Loading application properties");
        properties = new Properties();

        properties.load(ro.mta.library_project.People.DaoPeopleLogs.class.getClassLoader().
                getResourceAsStream("application.properties"));

        log.info("Connecting to the database");
        connection = DriverManager.getConnection(properties.getProperty("url"), properties);
        log.info("Database connection test: " + connection.getCatalog());
        statement = connection.createStatement();
    }

    /**
     * Metoda face un select in tabela Persoane si converteste fiecare linie din resultSet intr-un obiect pe care il
     * adauga intr-o lista
     *
     * @return returneaza lista cu obiectele
     * @throws Exception
     */
    public static List getTabelaPersoane() throws Exception {
        //1. Nume
        //2. Prenume
        //3. Data Nasterii
        //4. CNP
        //5. Rol - index 8
        //6. CreatedBy - index 9
        //7. Username

        String str = "SELECT P1.ID, P1.Nume, P1.Prenume, P1.DataNasterii, P1.CNP, P1.Username, " +
                "Roluri.NumeRol AS Rol, P2.Username AS CreatedBy FROM Persoane AS P1 " +
                "INNER JOIN Persoane AS P2 ON P1.CreatedBy = P2.ID INNER JOIN Roluri ON Roluri.ID = P1.Rol";

        init();
        ResultSet resultSet = statement.executeQuery(str);

        List ll = new LinkedList();

        while (resultSet.next()) {
            int i = resultSet.getInt("ID");
            String nume = resultSet.getString("Nume");
            String prenume = resultSet.getString("Prenume");
            String dataNasterii = resultSet.getString("DataNasterii");
            String CNP = resultSet.getString("CNP");
            String username = resultSet.getString("Username");
            String rol = resultSet.getString("Rol");
            String createdBy = resultSet.getString("CreatedBy");

            VisualizeAccountsHelperClass t = new VisualizeAccountsHelperClass(i, nume, prenume, dataNasterii, CNP,
                    username, rol, createdBy);

            ll.add(t);
        }

        end();

        return ll;
    }

    /**
     * Metoda verifica daca credentialele introduse exista in baza de date si daca sunt corecte, iar in caz afirmativ
     * returneaza variabila out in care se trimit id-ul si rol-ul contului catre client
     *
     * @param Username username-ul contului
     * @param Parola   parola contului
     * @return returneaza variabila out daca contul e introdus in baza de date, altfel returneaza 4
     */
    // returneaza ID Rol sau 4 daca contul nu exista
    public static int verifyAccount(String Username, String Parola) throws Exception {
        ResultSet resultSet = null;
        String selectSql = "SELECT ID, Rol, Parola, Salt FROM Persoane where Username='" + Username + "'";
        init();
        resultSet = statement.executeQuery(selectSql);

        if (resultSet.next()) {
            int ID = resultSet.getInt(1);
            int Rol = resultSet.getInt(2);
            String HashParola = resultSet.getString(3);
            String Salt = resultSet.getString(4);

            Parola = CreateSaltAndPassword.getSecurePassword(Parola, Salt);

            if (HashParola.equals(Parola)) {
                int out = ID * 10 + Rol;

                end();
                return out;
            } else {
                end();
                return 4;
            }
        } else {
            end();
            return 4;
        }
    }

    /**
     * Metoda verifica daca Username-ul introdus exista in baza de date sau nu
     *
     * @param Username username-ul care trebuie verificat
     * @return returneaza true daca username-ul apare si false daca nu
     * @throws Exception
     */
    public static boolean verifyUsername(String Username) throws Exception {
        ResultSet resultSet = null;
        String selectSql = "SELECT * FROM Persoane WHERE Username='" + Username + "'";
        init();
        resultSet = statement.executeQuery(selectSql);

        if (resultSet.next()) {
            end();
            return true; // daca e 1 inseamna ca apare
        }

        end();
        return false; // daca e 0 inseamna ca nu apare
    }

    /**
     * Metoda sterge contul cu username-ul introdus de utilizator
     *
     * @param Username username-ul contului care trebuie sters
     * @return returneaza 1
     */
    public static int deleteAccount(String Username) throws Exception {
        ResultSet resultSet = null;
        String selectSql = "DELETE FROM Persoane WHERE Username='" + Username + "'";
        init();
        int result = statement.executeUpdate(selectSql);
        end();

        return 1;
    }

    /**
     * Metoda modifica anumite informatii ale contului care are username-ul identic cu cel introdus de utilizator
     *
     * @param Username username-ul contului care va fi modificat
     * @param pick     daca este 1 atunci se modifica rol-ul, daca e 2 username-ul air daca e 3 parola
     * @param str      string-ul cu care se va inlocui informatia actuala
     * @return returneaza 1 daca modificarea a avut loc, sau 0 in caz contrar
     */
    public static int modifyAccount(String Username, int pick, String str) throws Exception {
        ResultSet resultSet = null;
        String selectSql;

        int ok;

        switch (pick) {
            case 1: // modificare rol
                selectSql = "UPDATE Persoane SET Rol= " + str + " WHERE Username = '" + Username + "'";
                init();
                ok = statement.executeUpdate(selectSql);
                end();

                return 1;
            case 2: // modificare username
                selectSql = "UPDATE Persoane SET Username= '" + str + "' WHERE Username = '" + Username + "'";
                init();
                ok = statement.executeUpdate(selectSql);
                end();

                return 1;
            case 3: // modificare parola
                String NewSalt = CreateSaltAndPassword.getSalt();
                String hashedPassword = CreateSaltAndPassword.getSecurePassword(str, NewSalt);

                selectSql = "UPDATE Persoane SET Parola= '" + hashedPassword + "', Salt = '" + NewSalt + "' " +
                        "WHERE Username = '" + Username + "'";
                init();
                ok = statement.executeUpdate(selectSql);
                end();

                return 1;
            default:
                return 0;
        }
    }

    /**
     * Metoda creaza un user nou
     *
     * @param Nume      numele user-ului
     * @param Prenume   prenumele user-ului
     * @param Data      data de nastere a user-ului
     * @param CNP       CNP-ul user-ului
     * @param Username  username-ul user-ului
     * @param Parola    parola user-ului
     * @param Rol       rol-ul contului
     * @param CreatedBy ID-ul contului care a creat contul
     */
    public static void createUser(String Nume, String Prenume, String Data, String CNP, String Username, String Parola,
                                  int Rol, int CreatedBy) throws Exception {
        String Salt = CreateSaltAndPassword.getSalt();
        String hashedPassword = CreateSaltAndPassword.getSecurePassword(Parola, Salt);

        ResultSet resultSet = null;
        String selectSql = "INSERT INTO Persoane(Nume, Prenume, DataNasterii, CNP, Username, Parola, Rol, " +
                "CreatedBy, Salt) VALUES ('" + Nume + "', '" + Prenume + "', '" + Data + "', '" + CNP + "', '" +
                Username + "', '" + hashedPassword + "','" + Rol + "', '" + CreatedBy + "', '" + Salt + "')";
        init();
        // https://stackoverflow.com/questions/25745094/getting-resultset-from-insert-statement
        int result = statement.executeUpdate(selectSql);
        end();
    }

    /**
     * Metoda care inchide conexiunea cu baza de date
     */
    public static void end() throws Exception {
        log.info("Closing database connection");
        connection.close();
    }

    /**
     * Metoda creaza un log cu ID-ul unui utilizator si ora la care acesta s-a logat
     *
     * @param ID ID-ul contului care s-a logat
     */
    public static void logLogin(int ID) throws Exception {
        String timeStamp = new SimpleDateFormat("yyyy.MM.dd HH:mm:ss").format(new Date());

        ResultSet resultSet = null;
        String selectSql = "INSERT INTO LoginHistory(Username, DataOraLogin) VALUES " +
                "('" + ID + "', '" + timeStamp + "')";
        init();
        // https://stackoverflow.com/questions/25745094/getting-resultset-from-insert-statement
        int result = statement.executeUpdate(selectSql);
        end();
    }

    /**
     * Metoda care updateaza tabela LoginHistory, introducand ora la care un utilizator s-a delogat
     *
     * @param ID ID-ul contului care s-a delogat
     */
    public static void logLogout(int ID) throws Exception {
        String timeStamp = new SimpleDateFormat("yyyy.MM.dd HH:mm:ss").format(new Date());

        String selectSql = "UPDATE LoginHistory SET DataOraLogout= '" + timeStamp + "' WHERE Username = '" + ID +
                "' AND DataOraLogout IS NULL";
        init();
        int ok = statement.executeUpdate(selectSql);
        end();
    }

    /**
     * Metoda introduce in tabela LoguriActiuni un log care spune ca s-a creat un cont
     *
     * @param ID      ID-ul user-ului care a creat contul
     * @param rol     rolul contului creat
     * @param detalii detalii referitoare la crearea contului
     */
    public static void logCreateAccount(int ID, int rol, String detalii) throws Exception {
        String timeStamp = new SimpleDateFormat("yyyy.MM.dd HH:mm:ss").format(new Date());

        int IDactiune = 1;

        switch (rol) {
            case 1: // Admin
                IDactiune = 11;
                break;

            case 2: // Bibliotecar
                IDactiune = 2;
                break;

            case 3: // User
                IDactiune = 1;
                break;
        }

        ResultSet resultSet = null;
        String selectSql = "INSERT INTO LoguriActiuni(IDuser, IDactiune, DataOra, Detalii) VALUES ('" + ID + "', '" +
                IDactiune + "', '" + timeStamp + "', '" + detalii + "')";
        init();
        int result = statement.executeUpdate(selectSql);
        end();
    }

    /**
     * Metoda introduce in tabela LoguriActiuni un log care spune ca s-a sters un cont
     *
     * @param ID      ID-ul contului care a sters contul
     * @param detalii detalii referitoare la stergerea contului
     */
    public static void logEraseAccount(int ID, String detalii) throws Exception {
        String timeStamp = new SimpleDateFormat("yyyy.MM.dd HH:mm:ss").format(new Date());

        int IDactiune = 12;

        ResultSet resultSet = null;
        String selectSql = "INSERT INTO LoguriActiuni(IDuser, IDactiune, DataOra, Detalii) VALUES ('" + ID + "', '" +
                IDactiune + "', '" + timeStamp + "', '" + detalii + "')";
        init();
        int result = statement.executeUpdate(selectSql);
        end();
    }

    /**
     * Metoda introduce in tabela LoguriActiuni un log care spune ca s-a modificat un cont
     *
     * @param ID      ID-ul contului care a sters contul
     * @param detalii detalii referitoare la modificarea contului
     */
    public static void logModifySection(int ID, String detalii) throws Exception {
        String timeStamp = new SimpleDateFormat("yyyy.MM.dd HH:mm:ss").format(new Date());

        int IDactiune = 13;

        ResultSet resultSet = null;
        String selectSql = "INSERT INTO LoguriActiuni(IDuser, IDactiune, DataOra, Detalii) VALUES ('" + ID + "', '" +
                IDactiune + "', '" + timeStamp + "', '" + detalii + "')";
        init();
        int result = statement.executeUpdate(selectSql);
        end();
    }

    /**
     * Metoda ia toate informatiile din tabela Persoane
     *
     * @return returneaza resultSet-ul obtinut in urma interogarii
     */
    public static ResultSet getlogSeeTablePersoane() throws Exception {
        ResultSet resultSet = null;
        String selectSql = "SELECT P1.ID, P1.Nume, P1.Prenume,P1. DataNasterii, P1.CNP, P1.Username, " +
                "Roluri.NumeRol AS Rol, P2.Username AS CreatedBy FROM Persoane AS P1 " +
                "INNER JOIN Roluri ON Roluri.ID = P1.Rol INNER JOIN Persoane AS P2 ON P1.CreatedBy = P2.ID";
        init();
        resultSet = statement.executeQuery(selectSql);
        end();

        return resultSet;
    }

    /**
     * Metoda introduce in tabela LoguriActiuni un log care spune ca un utilizator a cerut sa vizualizeze
     * tabela Persoane
     *
     * @param ID      ID-ul contului care a facut cererea
     * @param detalii detalii referitoare la cine a cerut sa vada tabela
     */
    public static void setlogSeeTablePersoane(int ID, String detalii) throws Exception {
        String timeStamp = new SimpleDateFormat("yyyy.MM.dd HH:mm:ss").format(new Date());

        int IDactiune = 22;

        String selectSql = "INSERT INTO LoguriActiuni(IDuser, IDactiune, DataOra, Detalii) VALUES ('" + ID + "', '" +
                IDactiune + "', '" + timeStamp + "', '" + detalii + "')";
        init();
        int result = statement.executeUpdate(selectSql);
        end();
    }

    /**
     * Metoda ia toate informatiile, sau doar informatiile legate de Creare cont, Stergere cont si tot asa din tabela
     * LoguriActiuni si converteste resultSet-ul intr-o lista de obiecte
     *
     * @param pick ce tipuri de loguri a ales utilizatorul sa vizualizeze din tabela LoguriActiuni
     * @return returneaza lista cu obiectele
     */
    public static List getlogSeeActionLogs(String pick) throws Exception {
        ResultSet resultSet = null;

        String selectSql = "SELECT LoguriActiuni.ID, Persoane.Username, Actiuni.Actiune, LoguriActiuni.DataOra, " +
                "LoguriActiuni.Detalii FROM LoguriActiuni INNER JOIN Persoane ON Persoane.ID = LoguriActiuni.IDuser " +
                "INNER JOIN Actiuni ON Actiuni.ID = LoguriActiuni.IDactiune";

        if (pick == "Creare cont") {
            selectSql = "SELECT LoguriActiuni.ID, Persoane.Username, Actiuni.Actiune, LoguriActiuni.DataOra, " +
                    "LoguriActiuni.Detalii FROM LoguriActiuni INNER JOIN Persoane " +
                    "ON Persoane.ID = LoguriActiuni.IDuser INNER JOIN Actiuni " +
                    "ON Actiuni.ID = LoguriActiuni.IDactiune WHERE IDactiune = 1 OR IDactiune = 2 OR IDactiune = 11";
        } else if (pick == "Stergere cont") {
            selectSql = "SELECT LoguriActiuni.ID, Persoane.Username, Actiuni.Actiune, LoguriActiuni.DataOra, " +
                    "LoguriActiuni.Detalii FROM LoguriActiuni INNER JOIN Persoane " +
                    "ON Persoane.ID = LoguriActiuni.IDuser INNER JOIN Actiuni " +
                    "ON Actiuni.ID = LoguriActiuni.IDactiune WHERE IDactiune = 12";
        } else if (pick == "Modificare cont") {
            selectSql = "SELECT LoguriActiuni.ID, Persoane.Username, Actiuni.Actiune, LoguriActiuni.DataOra, " +
                    "LoguriActiuni.Detalii FROM LoguriActiuni INNER JOIN Persoane " +
                    "ON Persoane.ID = LoguriActiuni.IDuser INNER JOIN Actiuni " +
                    "ON Actiuni.ID = LoguriActiuni.IDactiune WHERE IDactiune = 13";
        } else if (pick == "Vizualizare tabela Persoane") {
            selectSql = "SELECT LoguriActiuni.ID, Persoane.Username, Actiuni.Actiune, LoguriActiuni.DataOra, " +
                    "LoguriActiuni.Detalii FROM LoguriActiuni INNER JOIN Persoane " +
                    "ON Persoane.ID = LoguriActiuni.IDuser INNER JOIN Actiuni " +
                    "ON Actiuni.ID = LoguriActiuni.IDactiune WHERE IDactiune = 22";
        } else if (pick == "Vizualizare Log-uri Actiuni") {
            selectSql = "SELECT LoguriActiuni.ID, Persoane.Username, Actiuni.Actiune, LoguriActiuni.DataOra, " +
                    "LoguriActiuni.Detalii FROM LoguriActiuni INNER JOIN Persoane " +
                    "ON Persoane.ID = LoguriActiuni.IDuser INNER JOIN Actiuni " +
                    "ON Actiuni.ID = LoguriActiuni.IDactiune WHERE IDactiune = 23";
        } else if (pick == "Vizualizare Log-uri Login/Logout") {
            selectSql = "SELECT LoguriActiuni.ID, Persoane.Username, Actiuni.Actiune, LoguriActiuni.DataOra, " +
                    "LoguriActiuni.Detalii FROM LoguriActiuni INNER JOIN Persoane " +
                    "ON Persoane.ID = LoguriActiuni.IDuser INNER JOIN Actiuni " +
                    "ON Actiuni.ID = LoguriActiuni.IDactiune WHERE IDactiune = 24";
        }

        init();
        resultSet = statement.executeQuery(selectSql);

        List ll = new LinkedList();

        while (resultSet.next()) {
            int i = resultSet.getInt("ID");
            String username = resultSet.getString("Username");
            String actiune = resultSet.getString("Actiune");
            String dataOra = resultSet.getString("DataOra");
            String detalii = resultSet.getString("Detalii");

            ActionLogsHelperClass t = new ActionLogsHelperClass(i, username, actiune, dataOra, detalii);

            ll.add(t);
        }

        end();

        return ll;
    }

    /**
     * Metoda ia toate logurile, logurile ce tin de admini, de bilbiotecari sau de useri din LoginHistory si converteste
     * resultSet-ul intr-o lista de obiecte
     *
     * @param pick ce tipuri de loguri a ales utilizatorul sa vizualizeze din tabela LoginHistory
     * @return returneaza lista de obiecte
     */
    public static List getlogLoginLogoutLogs(String pick) throws Exception {
        ResultSet resultSet = null;

        String selectSql = "SELECT LoginHistory.ID, Persoane.Username, DataOraLogin, DataOraLogout FROM LoginHistory " +
                "INNER JOIN Persoane ON LoginHistory.Username = Persoane.ID where DataOraLogout is not null";

        if (pick == "Log-urile adminilor") {
            selectSql = "SELECT LoginHistory.ID, Persoane.Username, DataOraLogin, DataOraLogout FROM LoginHistory " +
                    "INNER JOIN Persoane ON LoginHistory.Username = Persoane.ID WHERE Persoane.Rol = 1 and " +
                    "DataOraLogout is not null";
        } else if (pick == "Log-urile bibliotecarilor") {
            selectSql = "SELECT LoginHistory.ID, Persoane.Username, DataOraLogin, DataOraLogout FROM LoginHistory " +
                    "INNER JOIN Persoane ON LoginHistory.Username = Persoane.ID WHERE Persoane.Rol = 2 and " +
                    "DataOraLogout is not null";
        } else if (pick == "Log-urile user-silor") {
            selectSql = "SELECT LoginHistory.ID, Persoane.Username, DataOraLogin, DataOraLogout FROM LoginHistory " +
                    "INNER JOIN Persoane ON LoginHistory.Username = Persoane.ID WHERE Persoane.Rol = 3 and " +
                    "DataOraLogout is not null";
        }

        init();

        resultSet = statement.executeQuery(selectSql);

        List ll = new LinkedList();

        while (resultSet.next()) {
            int i = resultSet.getInt("ID");
            String username = resultSet.getString("Username");
            String dataOraLogin = resultSet.getString("DataOraLogin");
            String dataOraLogout = resultSet.getString("DataOraLogout");

            LoginLogoutHelperClass t = new LoginLogoutHelperClass(i, username, dataOraLogin, dataOraLogout);

            ll.add(t);
        }

        end();

        return ll;
    }

    /**
     * Metoda introduce in tabela LoguriActiuni un log care spune ca un utilizator a cerut sa vizualizeze tabela
     * LoginHistory
     *
     * @param ID      ID-ul utilizatorului care a facut cererea
     * @param detalii detalii referitoare la cine a cerut sa vada tabela
     * @throws Exception
     */
    public static void logSeeLoginLogout(int ID, String detalii) throws Exception {
        String timeStamp = new SimpleDateFormat("yyyy.MM.dd HH:mm:ss").format(new Date());

        int IDactiune = 23;

        ResultSet resultSet = null;
        String selectSql = "INSERT INTO LoguriActiuni(IDuser, IDactiune, DataOra, Detalii) VALUES ('" + ID + "', '" +
                IDactiune + "', '" + timeStamp + "', '" + detalii + "')";
        init();
        // https://stackoverflow.com/questions/25745094/getting-resultset-from-insert-statement
        int result = statement.executeUpdate(selectSql);
        end();
    }

    /**
     * Metoda introduce in tabela LoguriActiuni un log care spune ca un utilizator a cerut sa vizualizeze tabela
     * LoguriActiuni
     *
     * @param ID      ID-ul utilizatorului care a facut cererea
     * @param detalii detalii referitoare la cine a cerut sa vada tabela
     * @throws Exception
     */
    public static void logSeeActions(int ID, String detalii) throws Exception {
        String timeStamp = new SimpleDateFormat("yyyy.MM.dd HH:mm:ss").format(new Date());

        int IDactiune = 24;

        ResultSet resultSet = null;
        String selectSql = "INSERT INTO LoguriActiuni(IDuser, IDactiune, DataOra, Detalii) VALUES ('" + ID + "', '" +
                IDactiune + "', '" + timeStamp + "', '" + detalii + "')";
        init();
        // https://stackoverflow.com/questions/25745094/getting-resultset-from-insert-statement
        int result = statement.executeUpdate(selectSql);
        end();
    }
}