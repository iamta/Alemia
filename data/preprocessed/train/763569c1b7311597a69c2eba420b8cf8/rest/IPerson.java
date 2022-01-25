package ro.mta.library_project.People;

public interface IPerson {
    void showMenu() throws Exception;

    void AddUserByLibrarian(String secondName, String firstName, String birthDate, String CNP, String username,
                            String password);

    void PrintLocationOfBook(String id_book);

    void BorrowBook(String code);

    void PrintInformationBook(String title);

    void DestroyBook(String id);

    void SearchBook(String input, int choic);

    void createAccount() throws Exception;

    void eraseAccount() throws Exception;

    void modifySection() throws Exception;

    int getID();

    void seeTablePersoane() throws Exception;

    String getUsername();
}
