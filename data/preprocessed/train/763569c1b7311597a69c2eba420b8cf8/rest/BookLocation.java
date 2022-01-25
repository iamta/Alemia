package ro.mta.library_project.DBController;

import javafx.beans.property.IntegerProperty;
import javafx.beans.property.SimpleIntegerProperty;
import javafx.beans.property.SimpleStringProperty;
import javafx.beans.property.StringProperty;

public class BookLocation { //pentru printLocationOfBook din clasa Biancai
    SimpleIntegerProperty ID;
    SimpleIntegerProperty raft;
    SimpleIntegerProperty freeLocations;
    SimpleIntegerProperty totalLocations;
    SimpleStringProperty sections;
    public BookLocation(int ID, int raft, int freeLocations, int totalLocations,String sections)
    {
        this.ID=new SimpleIntegerProperty(ID);
        this.raft=new SimpleIntegerProperty(raft);
        this.freeLocations=new SimpleIntegerProperty(freeLocations);
        this.totalLocations=new SimpleIntegerProperty(totalLocations);
        this.sections=new SimpleStringProperty(sections);
    }

    public BookLocation(){}

    public int getID() {
        return ID.get();
    }

    public void setID(int ID) {
        this.ID.set(ID);
    }

    public int getFreeLocations() {
        return freeLocations.get();
    }

    public int getRaft() {
        return raft.get();
    }

    public int getTotalLocations() {
        return totalLocations.get();
    }

    public void setFreeLocations(int freeLocations) {
        this.freeLocations.set(freeLocations) ;
    }

    public void setRaft(int raft) {
        this.raft.set(raft);
    }

    public void setTotalLocations(int totalLocations) {
        this.totalLocations.set(totalLocations);
    }

    public void setSections(String sections) {
        this.sections.set(sections);
    }
    public String getSection()
    {
        return this.sections.get();
    }
}
