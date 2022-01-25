package ro.mta.library_project;

import ro.mta.library_project.People.AdminLog;
import ro.mta.library_project.People.IPerson;
import ro.mta.library_project.People.Login;

public class Application {


    public static void start() throws Exception {
        AdminLog.init();

        while (true) {
            IPerson p = Login.init();
            p.showMenu();
        }
    }
}
