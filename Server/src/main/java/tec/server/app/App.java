package tec.server.app;

import javafx.application.Application;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.fxml.FXMLLoader;
import javafx.stage.Stage;
import tec.server.app.server.Server;

/**
 * JavaFX App
 */
public class App extends Application {

    /**
     * Metodo principal que abre la venta de administrado e inicia el server
     * @param stage
     */
    @Override
    public void start(Stage stage) {
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource("/administrador.fxml"));
            Parent root = loader.load();
            Controller controller = loader.getController();

            Stage gameStage = new Stage();
            gameStage.setTitle("Administrador");
            gameStage.setResizable(false);
            Scene scene = new Scene(root, 905, 504);
            gameStage.setScene(scene);
            gameStage.show();

            Server server = Server.getInstance(1234);

        } catch (Exception e) {
            e.printStackTrace();
        }

    }

    public static void main(String[] args) {
        launch();
    }

}