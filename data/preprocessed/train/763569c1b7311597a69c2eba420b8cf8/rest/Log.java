package ro.mta.library_project.People;

import java.io.IOException;

public abstract class Log {
    static void init() throws IOException {
    }

    static void logCreateAccount(int ID, String AdminUsername, String Nume, String Prenume, String Data,
                                 String CNP, String Username, int Rol) throws Exception {
    }

    static void logEraseAccount(int ID, String AdminUsername, String Username) throws Exception {
    }

    static void logModifySection(int ID, String AdminUsername, String UsernameModifiedAccount, int pick,
                                 String strPick) throws Exception {
    }

    static void logSeeTablePersoane(int ID, String AdminUsername, int picks) throws Exception {
    }

    static void logGetLogs(String AdminUsername, int pick) throws IOException {
    }
}
