package ro.mta.library_project.People;

import java.io.File;
import java.io.IOException;

public class AdminLog extends Log {

    static String filename = "logAdmin.txt";

    public static void init() throws IOException {
        File myObj = new File(filename);
        if (myObj.createNewFile()) {
            System.out.println("File created: " + myObj.getName());
        } else {
            System.out.println("File already exists.");
        }
    }


    public static void logCreateAccount(int ID, String AdminUsername, String Nume, String Prenume, String Data,
                                        String CNP, String Username, int Rol) throws Exception {
        String str = "Adminul " + AdminUsername + " a creat un cont cu urmatoarele informatii: nume-" + Nume +
                ", prenume-" + Prenume + ", data nasterii-" + Data + ", CNP-" + CNP + ", username-" + Username +
                ", rol-" + Rol;

        DaoPeopleLogs.logCreateAccount(ID, Rol, str);
    }

    public static void logEraseAccount(int ID, String AdminUsername, String Username) throws Exception {
        String str = "Adminul " + AdminUsername + " a sters un cont cu urmatoarele informatii: username-" + Username;

        DaoPeopleLogs.logEraseAccount(ID, str);
    }

    public static void logModifySection(int ID, String AdminUsername, String UsernameModifiedAccount, int pick,
                                        String strPick) throws Exception {
        String str = "Adminul " + AdminUsername + " a modificat un cont cu urmatoarele informatii: username-" +
                UsernameModifiedAccount;

        switch (pick) {
            case 1: // modificare rol
                str = str + " rol nou-" + strPick;

                break;

            case 2: // modificare username
                str = str + " username nou-" + strPick;

                break;

            case 3: // modificare parola
                str = str + " parola noua-" + strPick;

                break;
        }

        DaoPeopleLogs.logModifySection(ID, str);
    }

    public static void logSeeTablePersoane(int ID, String AdminUsername, int picks) throws Exception {
        String str = "Adminul " + AdminUsername + " a cerut sa vizualizeze tabela Persoane";

        DaoPeopleLogs.getlogSeeTablePersoane();
        DaoPeopleLogs.setlogSeeTablePersoane(ID, str);
    }
}
