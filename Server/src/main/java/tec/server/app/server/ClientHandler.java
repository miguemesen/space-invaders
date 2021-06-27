package tec.server.app.server;

import java.io.*;
import java.net.*;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import org.json.simple.JSONObject;
import org.json.simple.parser.*;
import tec.server.app.Game;
import tec.server.app.Serializer;

public class ClientHandler implements Runnable{

    private final Integer MAX_NUM_OF_OBSERVERS = 2;
    private final Integer MAX_GAMES = 2;
    private final Socket clientSocket;
    private JSONParser jsonParser;
    private PrintWriter out;
    private BufferedReader in;
    private Game game;
    public static List<Game> games;
    public static boolean game1_disponible = false;
    public static boolean game2_disponible = false;
    private boolean isActive = true;


    // Constructor
    public ClientHandler(Socket client) throws IOException {
        games = Collections.synchronizedList(new ArrayList<>());
        this.clientSocket = client;
        this.out = new PrintWriter(client.getOutputStream(),true);
        this.in = new BufferedReader(new InputStreamReader(client.getInputStream()));
        this.jsonParser = new JSONParser();
    }

    public synchronized void send(String message) throws IOException {
        this.out.println(message);
        this.out = new PrintWriter(clientSocket.getOutputStream(),true);

    }

    public static Game getGameById(Integer gameId){
        for (Game game : games){
            if (gameId == game.getGameId())
                return game;

        }
        return null;
    }

    public void newGameHandler(JSONObject responseJson) throws IOException {

        Integer game_id = Integer.parseInt(responseJson.get("gameId").toString());

        if (totalGames() < MAX_GAMES){

            if (game_id == 1){
                if (!game1_disponible){ // verifica si alguien lo esta jugando, si no lo estan jugando crea un juego nuevo
                    send(Serializer.gameAccepted(game_id));
                    createNewGame(game_id);
                    game1_disponible = true;
                } else { // si ya estan jugando el juego le manda un rechazo al cliente
                    send(Serializer.gameRejected(game_id));
                }
            }
            if (game_id == 2){
                if (!game2_disponible){
                    send(Serializer.gameAccepted(game_id));
                    createNewGame(game_id);
                    game2_disponible = true;
                } else {
                    send(Serializer.gameRejected(game_id));
                }
            }

        } else {
            send(Serializer.gameRejected(game_id));
        }
    }


    /**
     * Crea un nuevo juego con el cliente actual y el id ingresado por el mismo
     * @param game_id id del juego que desea iniciar
     */
    private void createNewGame(Integer game_id) {
        Game game = new Game(game_id,this);
        ClientHandler.games.add(game);
        this.game = game;
    }

    /**
     * Devuelve el total de juegos existentes
     * @return
     */
    private Integer totalGames(){
        return ClientHandler.games.size();
    }


    @Override
    public void run() {

        try {

            while (isActive){
                String response = in.readLine();

                if (response == null){
                    if (game.getPlayer() == this){
                        this.endExecution();
                        break;
                    } else {
                        this.game.removeObserver(this);
                        this.clientSocket.close();
                        break;
                    }
                }

                JSONObject responseJson = (JSONObject) (this.jsonParser.parse(response));
                String command = responseJson.get("command").toString();

                if (command.equals("newGame")){ // El cliente pide crear un nuevo juego
                    this.newGameHandler(responseJson);

                } 
                if (command.equals("observer")){
                    this.observerHandler(responseJson);
                }
                else { // No se entiende el comando enviado, por lo que es un comando para el juego
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

    private void observerHandler(JSONObject responseJson) throws IOException {
        Integer gameId = Integer.parseInt(responseJson.get("gameId").toString());

        for (Game game : games){
            if (game.getGameId() == gameId){
                if (game.getNumberObservers() < MAX_NUM_OF_OBSERVERS){
                    this.game = game;
                    game.addObserver(this);
                } else {
                    send(Serializer.gameRejected(gameId));
                }
            }
        }
    }

    private void endExecution() {
        if (game.getPlayer() == this){
            game.gameOver();
            freeGame(game.getGameId());
            games.remove(this.game);
            this.isActive = false;
        }
        try {
            this.clientSocket.close();
            this.in.close();
            this.out.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private void freeGame(Integer gameId) {
        if (gameId == 1){
            game1_disponible = false;
            games.remove(game);
        }
        else if (gameId == 2){
            game2_disponible = false;
            games.remove(game);
        } else {
            System.out.println("Id invlaido");
        }
    }
}
