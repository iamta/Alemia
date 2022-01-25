package ro.mta.library_project.RequestsModule;

import java.util.ArrayList;

/**
 * Clasa helper pentru cererea de imprumut
 *
 * @author Lupu Marcela
 */
public class BorrowRequest {
    public int userId;
    public ArrayList<Integer> bookId;
    public int borrowCode;

    /**
     * Clasa BorrowRequest suprascrie metoda toString() pentru a afisa datele unui request: ID user, ID-uri carti, cod de imprumut.
     * */
    @Override
    public String toString() {
        StringBuilder builder = new StringBuilder();

        builder.append("Id: ");
        builder.append(userId);
        builder.append("\n");
        builder.append("bookId: ");
        for (int i = 0; i < this.bookId.size(); i++) {
            builder.append(bookId.get(i));
            builder.append("\t");
        }

        builder.append("BorrowCode: ");
        builder.append(borrowCode);

        String result = builder.toString();
        return result;
    }
}
