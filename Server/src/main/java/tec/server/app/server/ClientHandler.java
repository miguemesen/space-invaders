package tec.server.app.server;

import java.io.*;
import java.net.*;
import java.util.List;

import org.json.simple.JSONObject;
import org.json.simple.parser.*;
import tec.server.app.Game;
import tec.server.app.Serializer;

public class ClientHandler implements Runnable{

    private final Socket clientSocket;
    private JSONParser jsonParser;
    private PrintWriter out;
    private BufferedReader in;
    private Game game;
    public static List<Game> games;
    public static boolean game1_disponible = false;
    public static boolean game2_disponible = false;


    // Constructor
    public ClientHandler(Socket client) throws IOException {
        this.clientSocket = client;
        this.out = new PrintWriter(client.getOutputStream(),true);
        this.in = new BufferedReader(new InputStreamReader(client.getInputStream()));
        this.jsonParser = new JSONParser();
    }

    public synchronized void send(String message) throws IOException {
        this.out.println(message);
        this.out = new PrintWriter(clientSocket.getOutputStream(),true);

    }

    public void newGameHandler(JSONObject responseJson) throws IOException {
        this.out.println("Se crea un nuevo juego");

        if (ClientHandler.games.size() < 2){

            Integer game_id = Integer.parseInt(responseJson.get("gameId").toString());

            if (game_id == 1){
                if (!game1_disponible){ // verifica si alguien lo esta jugando, si no lo estan jugando crea un juego nuevo
                    createNewGame(game_id);
                    game1_disponible = true;
                } else { // si ya estan jugando el juego le manda un rechazo al cliente
                    send(Serializer.gameRefused(game_id));
                }
            }
        }
    }

    private void createNewGame(Integer game_id) {
        Game game = new Game(game_id,this);
        ClientHandler.games.add(game);
        this.game = game;
    }


    @Override
    public void run() {

        try {

            String response;
            while ((response = in.readLine()) != null) {


                JSONObject responseJson = (JSONObject) (this.jsonParser.parse(response));
                String command = responseJson.get("command").toString();

                if (command.equals("newGame")){ // El cliente pide crear un nuevo juego
                    this.newGameHandler(responseJson);

                } else { // No se entiende el comando enviado, por lo que es un comando para el juego
                    game.filterCommand(response);
                }
            }
        }
        catch (IOException | ParseException e) {
            e.printStackTrace();
        }
        finally {
            try {
                if (out != null) {
                    out.close();
                }
                if (in != null) {
                    in.close();
                    clientSocket.close();
                }
            }
            catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
