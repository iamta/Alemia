package ro.mta.library_project.HelperClasses;

/**
 * Clasa este folosita pentru a convertii resultSet-urile legate de tabela LoguriActiuni in liste
 *
 * @author Cioaca Andrei
 */
public class ActionLogsHelperClass {
    private final String id;
    private final String username;
    private final String actiune;
    private final String dataOra;
    private final String detalii;

    public ActionLogsHelperClass(int id, String username, String actiune, String dataOra, String detalii) {
        this.id = Integer.toString(id);
        this.username = username;
        this.actiune = actiune;
        this.dataOra = dataOra;
        this.detalii = detalii;
    }

    public String getId() {
        return this.id;
    }

    public String getUsername() {
        return this.username;
    }

    public String getActiune() {
        return this.actiune;
    }

    public String getDataOra() {
        return this.dataOra;
    }

    public String getDetalii() {
        return this.detalii;
    }
}
