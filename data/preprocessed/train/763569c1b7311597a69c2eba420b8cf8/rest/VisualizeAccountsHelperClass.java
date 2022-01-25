package ro.mta.library_project.HelperClasses;

/**
 * Clasa este folosita pentru a convertii resultSet-urile legate de tabela Persoane in liste
 *
 * @author Cioaca Andrei
 */
public class VisualizeAccountsHelperClass {
    private final String id;
    private final String nume;
    private final String prenume;
    private final String dataNasterii;
    private final String CNP;
    private final String username;
    private final String rol;
    private final String createdBy;

    public VisualizeAccountsHelperClass(int id, String nume, String prenume, String dataNasterii, String CNP,
                                        String username, String rol, String createdBy) {
        this.id = Integer.toString(id);
        this.nume = nume;
        this.prenume = prenume;
        this.dataNasterii = dataNasterii;
        this.CNP = CNP;
        this.username = username;
        this.rol = rol;
        this.createdBy = createdBy;
    }

    public String getId() {
        return this.id;
    }

    public String getNume() {
        return this.nume;
    }

    public String getPrenume() {
        return this.prenume;
    }

    public String getDataNasterii() {
        return this.dataNasterii;
    }

    public String getCNP() {
        return this.CNP;
    }

    public String getUsername() {
        return this.username;
    }

    public String getRol() {
        return this.rol;
    }

    public String getCreatedBy() {
        return this.createdBy;
    }
}
