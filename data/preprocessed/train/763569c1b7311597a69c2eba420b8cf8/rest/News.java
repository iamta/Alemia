package ro.mta.library_project.News;


import java.io.*;
import java.net.URI;
import java.net.URLEncoder;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;


import com.google.common.net.UrlEscapers;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.*;
import ro.mta.library_project.DBController.NewsHelper;

public class News {

    public News()  {

    }
    public String GetRequest(String SearchFor) throws IOException, InterruptedException, ParseException {

        String UrlString=  UrlEscapers.urlFragmentEscaper().escape(SearchFor);

        String link="https://newsapi.org/v2/everything?q="+UrlString+"&sortBy=popularity&language=ro&apiKey=44b715fdc3ae4f13acc9aa9b5ec500a7";
        HttpClient client = HttpClient.newHttpClient();
        HttpRequest request = HttpRequest.newBuilder()
                .uri(URI.create(link))
                .build();

        HttpResponse<String> response = client.send(request,
                HttpResponse.BodyHandlers.ofString());
        File file = new File("ArticlesLog.txt");
        FileWriter fr = new FileWriter(file, true);


        SimpleDateFormat formatter= new SimpleDateFormat("yyyy-MM-dd 'at' HH:mm:ss z");
        Date date = new Date(System.currentTimeMillis());
        fr.write(date.toString()+" Searched: "+SearchFor+"\n");
        fr.close();


        return  response.body().toString();
    }

    public int  getNumberOfArticles(String json) throws ParseException {

        Object obj = new JSONParser().parse(json);

        JSONObject jo = (JSONObject) obj;

        JSONArray articles=(JSONArray) jo.get("articles");
        int totalResults=articles.size();

        return totalResults;
    }
    public String getStatus(String json) throws ParseException {
        Object obj = new JSONParser().parse(json);

        JSONObject jo = (JSONObject) obj;
        String status=(String) jo.get("status");

        return status;

    }
    public void printArticles(int n,String json) throws ParseException {
        Object obj = new JSONParser().parse(json);

        JSONObject jo = (JSONObject) obj;
        JSONArray articles=(JSONArray) jo.get("articles");

        JSONObject article;
        String url;
        String description;
        for(int i=0;i<n;i++)
        {
            article= (JSONObject) articles.get(i);
            url=(String) article.get("url");
            description=(String) article.get("description");
            System.out.println(url);
            System.out.println(description);
        }
    }
    public ArrayList<NewsHelper> listOfArticles(int n, String json) throws ParseException {
        ArrayList<NewsHelper> helperArrayList=new ArrayList<NewsHelper>();
        Object obj = new JSONParser().parse(json);

        JSONObject jo = (JSONObject) obj;
        JSONArray articles=(JSONArray) jo.get("articles");

        JSONObject article;
        String url;
        String description;
        for(int i=0;i<n;i++)
        {
            article= (JSONObject) articles.get(i);
            url=(String) article.get("url");
            description=(String) article.get("description");
            helperArrayList.add(new NewsHelper(url,description));
        }
        return helperArrayList;
    }

}
