package ro.mta.library_project.People;

import java.util.Scanner;

public class Login {
    public static IPerson init() throws Exception {
        while (true) {
            System.out.println("Press 1 for User\nPress 2 for Guest\nPress 3 to Exit");
            Scanner scanner = new Scanner(System.in);
            String pick = scanner.nextLine();

            IPerson p;

            if (pick.equals("2")) {
                p = new Unregistered();
                return p;
            }

            if (pick.equals("1")) {
                boolean loop = true;
                while (loop) {
                    // preluare credentiale
                    System.out.print("Username: ");
                    scanner = new Scanner(System.in);
                    String Username = scanner.nextLine();

                    System.out.print("Parola: ");
                    String Parola = scanner.nextLine();

                    // functie care se uita in baza de date
                    int out = DaoPeopleLogs.verifyAccount(Username, Parola);

                    int ID = out / 10;
                    int rol = out % 10;

                    // returnare obiect

                    switch (rol) {
                        case 1:
                            p = new Admin(ID, Username);
                            DaoPeopleLogs.logLogin(ID);
                            return p;
                        case 2:
                            p = new Librarian(ID, Username);
                            DaoPeopleLogs.logLogin(ID);
                            return p;
                        case 3:
                            p = new RegisteredUser(ID, Username);
                            DaoPeopleLogs.logLogin(ID);
                            return p;
                        default:
                            System.out.println("Contul nu este bun\n");
                            loop = false;
                    }
                }
            }

            if (pick.equals("3")) {
                System.exit(0);
            }
        }
    }
}
