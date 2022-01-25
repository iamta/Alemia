package ro.mta.library_project.People;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Admin extends User {

    int ID;
    String Username;

    public Admin(int ID, String Username) {
        this.ID = ID;
        this.Username = Username;
    }


    public int getID() {
        return ID;
    }

    public String getUsername() {
        return Username;
    }


    public void createAccount() throws Exception {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Inregistrare:\nNume:");
        String Nume = scanner.nextLine();

        System.out.println("Prenume:");
        String Prenume = scanner.nextLine();

        System.out.println("Data (YYYY-MM-DD):");
        String Data = scanner.nextLine();

        System.out.println("CNP:");
        String CNP = scanner.nextLine();

        String Username;
        while (true) {
            System.out.println("Username:");
            Username = scanner.nextLine();

            if (DaoPeopleLogs.verifyUsername(Username)) // daca e true inseamna ca Username-ul e folosit deja
            {
                System.out.print("Username folosit deja. Introduceti alt ");
            } else // daca e false inseamna ca Username-ul nu e folosit de nimeni
            {
                break;
            }
        }

        System.out.println("Password:");
        String Password = scanner.nextLine();

        System.out.println("Rol:");
        int Rol = scanner.nextInt();

        //

        int CreatedBy = ID;

        DaoPeopleLogs.createUser(Nume, Prenume, Data, CNP, Username, Password, Rol, CreatedBy);

        System.out.println("User-ul a fost creat\n");

        AdminLog.logCreateAccount(this.ID, this.Username, Nume, Prenume, Data, CNP, Username, Rol);
    }

    public void eraseAccount() throws Exception {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Stergere cont:\nUsername:");
        String Username = scanner.nextLine();

        int ok = DaoPeopleLogs.deleteAccount(Username);

        if (ok == 1) {
            System.out.println("Contul a fost sters\n");
            AdminLog.logEraseAccount(this.ID, this.Username, Username);
        } else {
            System.out.println("Contul introdus nu este corect\n");
        }
    }

    public void modifySection() throws Exception {
        Scanner scanner = new Scanner(System.in);

        System.out.println("Modificare cont:\nUsername-ul contului pe care doriti sa-l modificati:");
        String Username = scanner.nextLine();

        //

        System.out.println("Ce doriti sa modificati:\n1. Rol\n2. Username\n3. Parola");
        int pick = scanner.nextInt();
        scanner.nextLine();

        int ok = 0;

        boolean loop = true;
        while (loop) {
            switch (pick) {
                case 1:
                    System.out.println("Dati ID-ul noul Rol:");
                    String NewRol = scanner.nextLine();

                    ok = DaoPeopleLogs.modifyAccount(Username, pick, NewRol);
                    AdminLog.logModifySection(this.ID, this.Username, Username, pick, NewRol);

                    loop = false;
                    break;

                case 2:
                    System.out.println("Dati noul Username:");
                    String NewUsername = scanner.nextLine();

                    ok = DaoPeopleLogs.modifyAccount(Username, pick, NewUsername);
                    AdminLog.logModifySection(this.ID, this.Username, Username, pick, NewUsername);

                    loop = false;
                    break;

                case 3:
                    System.out.println("Dati noua Parola:");
                    String NewParola = scanner.nextLine();

                    ok = DaoPeopleLogs.modifyAccount(Username, pick, NewParola);
                    AdminLog.logModifySection(this.ID, this.Username, Username, pick, NewParola);

                    loop = false;
                    break;

                default:
                    System.out.println("Alegere gresita\n");

            }
        }

        //

        if (ok == 1) {
            System.out.println("Contul a fost modificat\n");
        } else {
            System.out.println("Contul introdus nu este corect\n");
        }
    }

    public void seeTablePersoane() throws Exception {
        System.out.println("Scrieti indexii coloanelor pe care doriti sa le vizualizati:");
        System.out.println("1. Nume\n2. Prenume\n3. Data Nasterii\n4. CNP\n5. Rol\n6. CreatedBy\n7. Username");

        Scanner scanner = new Scanner(System.in);
        int picks = scanner.nextInt();
        int copiePicks = picks;

        System.out.println(picks);

        DaoPeopleLogs.getTabelaPersoane();
        AdminLog.logSeeTablePersoane(this.ID, this.Username, picks);
    }

    // metoda de vizualizare log-uri LoginHistory
    public void seeLoginLogoutLogs() throws Exception {
        boolean loop = true;
        while (loop) {
            System.out.println("\nScrieti indexul optiunii pe care doriti sa o vizualizati:");
            System.out.println("1. Toate log-urile\n2. Log-urile adminilor\n3. Log-urile bibliotecarilor\n" +
                    "4. Log-urile user-silor\n5. Iesire");

            Scanner scanner = new Scanner(System.in);
            int pick = scanner.nextInt();

            int ok;

            /*switch (pick) {
                case 1:
                    ok = DaoPeopleLogs.getLogs(1);
                    AdminLog.logGetLogs(this.ID, this.Username, 1);
                    break;

                case 2:
                    ok = DaoPeopleLogs.getLogs(2);
                    AdminLog.logGetLogs(this.ID, this.Username, 2);
                    break;

                case 3:
                    ok = DaoPeopleLogs.getLogs(3);
                    AdminLog.logGetLogs(this.ID, this.Username, 3);
                    break;

                case 4:
                    ok = DaoPeopleLogs.getLogs(4);
                    AdminLog.logGetLogs(this.ID, this.Username, 4);
                    break;

                default:
                    loop = false;
                    break;
            }*/
        }
    }

    // metoda de vizualizare log-ui LoguriActiuni
    public void seeActionsLogs() throws Exception {
        boolean loop = true;
        while (loop) {
            System.out.println("\nScrieti indexul tipului de log-uri pe care doriti sa le vizualizati:");
            System.out.println("1. Detaliate\n2. Restanse\n3. Iesire");

            Scanner scanner = new Scanner(System.in);
            int pick = scanner.nextInt();

            switch (pick) {
                case 1:
                    seeActionsLogsDetaliate();
                    break;

                case 2:
                    //seeActionsLogsRestanse();
                    break;

                default:
                    loop = false;
                    break;
            }
        }
    }

    /*public void seeActionsLogsRestanse() throws Exception
    {
        DaoPeopleLogs.getActionsLogsRestanse();
    }*/

    public void printSomeLogs(String str) throws FileNotFoundException {
        File file = new File("logAdmin.txt");
        Scanner in = null;

        in = new Scanner(file);
        while (in.hasNext()) {
            String line = in.nextLine();
            if (line.contains(str))
                System.out.println(line);
        }
    }

    public void printAllLogs() throws FileNotFoundException {
        File file = new File("logAdmin.txt");
        Scanner in = null;

        in = new Scanner(file);
        while (in.hasNext()) {
            String line = in.nextLine();
            System.out.println(line);
        }
    }

    public void seeActionsLogsDetaliate() throws Exception {
        boolean loop = true;
        while (loop) {
            System.out.println("\nScrieti indexul optiunii pe care doriti sa o vizualizati:");
            System.out.println("1. Toate\n2. Creare cont\n3. Stergere cont\n4. Modificare cont\n" +
                    "5. Vizualizare tabela Persoane\n6. Vizualizare Log-uri\n7. Iesire");

            Scanner scanner = new Scanner(System.in);
            int pick = scanner.nextInt();

            String str;

            switch (pick) {
                case 1:
                    printAllLogs();
                    break;

                case 2:
                    str = "Creare cont";
                    printSomeLogs(str);
                    break;

                case 3:
                    str = "Stergere cont";
                    printSomeLogs(str);
                    break;

                case 4:
                    str = "Modificare cont";
                    printSomeLogs(str);
                    break;

                case 5:
                    str = "Vizualizare tabela Persoane";
                    printSomeLogs(str);
                    break;

                case 6:
                    str = "Vizualizare Log-uri";
                    printSomeLogs(str);
                    break;

                default:
                    loop = false;
                    break;
            }
        }
    }

    public void showMenu() throws Exception {
        System.out.println("Admin");

        boolean loop = true;

        while (loop) {
            System.out.println("\nCe doriti sa faceti?\n1. Afisare ID propriu\n2. Creare cont\n3. Stergere cont\n" +
                    "4. Modificare cont\n5. Vizualizare coloane din tabelul Persoane\n" +
                    "6. Vizualizare log-uri Actiuni\n7. Vizualizare log-uri Login/Logout\n8. Delogare");

            Scanner scanner = new Scanner(System.in);
            int pick = scanner.nextInt();

            switch (pick) {
                case 1:
                    System.out.println(getID());
                    break;

                case 2:
                    createAccount();
                    break;

                case 3:
                    eraseAccount();
                    break;

                case 4:
                    modifySection();
                    break;

                case 5:
                    seeTablePersoane();
                    break;

                case 6:
                    seeActionsLogs();
                    break;

                case 7:
                    seeLoginLogoutLogs();
                    break;

                default:
                    DaoPeopleLogs.logLogout(ID);
                    loop = false;
                    break;
            }
        }
    }
}
