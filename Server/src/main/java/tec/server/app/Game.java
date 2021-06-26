package tec.server.app;

import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;
import tec.server.app.enemigos.Enemigo;
import tec.server.app.server.ClientHandler;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Game {
    private Integer gameId;
    private List<Enemigo> enemigos;
    private Canon canon;
    private List<ClientHandler> observers;
    private JSONParser jsonParser;
    private ClientHandler player;

    public Game(Integer gameId, ClientHandler player){
        this.gameId = gameId;
        this.enemigos = Collections.synchronizedList(new ArrayList<>());
        this.canon = new Canon();
        this.observers = Collections.synchronizedList(new ArrayList<>());
        this.jsonParser = new JSONParser();
        this.player = player;
    }

    public Integer getGameId() {
        return gameId;
    }

    public void iniciarJuego() throws IOException {
        player.send(Serializer.startGame(gameId));
    }



    public void filterCommand(String command) throws ParseException, IOException {
        JSONObject commandJSON = (JSONObject) jsonParser.parse(command);


    }

}
