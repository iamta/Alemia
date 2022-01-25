package ro.mta.library_project.Controllers;

import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.TextField;
import org.json.simple.parser.ParseException;
import ro.mta.library_project.DBController.NewsHelper;
import ro.mta.library_project.News.News;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import javafx.scene.control.*;
import ro.mta.library_project.People.UserLog;

/**
 * Clasa controller pentru interfata NewsView
 *
 * @author Lupu Marcela
 */
public class NewsController {
    private int ID;
    private String Username;

    @FXML
    private ListView<String> listOfNews;

    @FXML
    private TextField getNews;

    /**
     * Metoda seteaza variabila ID
     *
     * @param id ID-ul utilizatorului care s-a logat
     */
    public void setID(int id)
    {
        this.ID = id;
    }

    /**
     * Metoda seteaza variabila Username
     *
     * @param name username-ul utilizatorului care s-a logat
     */
    public void setUsername(String name)
    {
        this.Username = name;
    }

    /**
     * Metoda printArticles(final ActionEvent event) afiseaza intr-o lista link-uri catre stiri returnate in urma cautarii pe baza unui sir de caractere(de exemplu vreme).
     * Este preluat textul introdus si in urma cautarii, stirile sunt puse intr-o lista care va fi afisata ulterior intr-un ListView.
     * */
    @FXML
    private void printArticles(final ActionEvent event) throws IOException, ParseException, InterruptedException {
        String newsString = getNews.getText();
        News news = new News();
        String jsonString = news.GetRequest(newsString);
        int numberOfNews = news.getNumberOfArticles(jsonString);

        ArrayList<NewsHelper> newsList = news.listOfArticles(numberOfNews, jsonString);

        ObservableList newsToPrint = FXCollections.observableArrayList();

        List<String> stringList = new ArrayList<>();

        for (int i = 0; i < newsList.size(); i++)
        {
               stringList.add(newsList.get(i).getUrl());
        }

        newsToPrint.setAll(stringList);

        listOfNews.getItems().addAll(newsToPrint);
        UserLog.getInstance().searchNews(Username, ID, newsString);
    }

}
