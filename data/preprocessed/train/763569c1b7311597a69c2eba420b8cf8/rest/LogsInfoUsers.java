package ro.mta.library_project.DBController;

public class LogsInfoUsers {
    String details;
    String dateh;
    public LogsInfoUsers(String detail, String dateh)
    {
        this.details=detail;
        this.dateh=dateh;
    }

    public String getDateh() {
        return dateh;
    }

    public void setDateh(String dateh) {
        this.dateh = dateh;
    }

    public String getDetails() {
        return details;
    }

    public void setDetails(String details) {
        this.details = details;
    }
}
