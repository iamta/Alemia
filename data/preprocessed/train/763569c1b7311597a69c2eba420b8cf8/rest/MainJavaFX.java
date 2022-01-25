package ro.mta.library_project;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

public class MainJavaFX extends Application {
    public static void main(String[] args) {
        launch();
    }

    @Override
    public void start(Stage stage) throws IOException {
        //FXMLLoader fxmlLoader = new FXMLLoader(MainJavaFX.class.getResource("UILibrarian.fxml"));

        FXMLLoader fxmlLoader = new FXMLLoader(MainJavaFX.class.
                getResource("/ro/mta/library_project/UILogin.fxml"));
        Scene scene = new Scene(fxmlLoader.load());
        stage.setTitle("Login Window");
        stage.setScene(scene);
        stage.show();
    }
}
