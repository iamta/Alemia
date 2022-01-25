package ro.mta.library_project.HelperClasses;

/**
 * Clasa este folosita pentru a convertii resultSet-urile legate de tabela LoginHistory in liste
 *
 * @author Cioaca Andrei
 */
public class LoginLogoutHelperClass {
    private final String id;
    private final String username;
    private final String dataOraLogin;
    private final String dataOraLogout;

    public LoginLogoutHelperClass(int id, String username, String dataOraLogin, String dataOraLogout) {
        this.id = Integer.toString(id);
        this.username = username;
        this.dataOraLogin = dataOraLogin;
        this.dataOraLogout = dataOraLogout;
    }

    public String getId() {
        return this.id;
    }

    public String getUsername() {
        return this.username;
    }

    public String getDataOraLogin() {
        return this.dataOraLogin;
    }

    public String getDataOraLogout() {
        return this.dataOraLogout;
    }
}
