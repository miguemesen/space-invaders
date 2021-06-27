package tec.server.app;

import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;
import tec.server.app.Entities.Bullet;
import tec.server.app.Entities.Canon;
import tec.server.app.Entities.Escudo;
import tec.server.app.Entities.enemigos.Enemigo;
import tec.server.app.Entities.enemigos.FactoryEnemigo;
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
    private Bullet playerBullet;
    private Bullet enemyBullet;
    private List<Escudo> escudos;

    /**
     * Constructor de la clase Game
     * @param gameId Id del juego que será inicializado
     * @param player Jugador que llevara el juego
     */
    public Game(Integer gameId, ClientHandler player){
        this.gameId = gameId;
        this.enemigos = Collections.synchronizedList(new ArrayList<>());
        this.canon = new Canon();
        this.observers = Collections.synchronizedList(new ArrayList<>());
        this.jsonParser = new JSONParser();
        this.player = player;
        this.escudos = new ArrayList<>();
        for (int i = 1; i<4; i++)
            this.escudos.add(new Escudo(i));
    }



    public List<Enemigo> getEnemigos() {
        return enemigos;
    }

    public Integer getNumberObservers(){
        return this.observers.size();
    }

    public ClientHandler getPlayer() {
        return player;
    }

    public Integer getGameId() {
        return gameId;
    }

    /**
     * Le indica a los clientes que pueden ser tanto jugador como observadores
     * que la partida ya inicio
     * @throws IOException
     */
    public void iniciarJuego() throws IOException {
        sendClientes(Serializer.startGame(gameId));
    }


    /**
     * Recibe los comandos enviados desde el cliente e interpreta que tipo
     * de informacion es la que envia
     * @param command Comando que es enviado desde el cliente, una palabra representativa
     *                de la informacion que viene.
     * @throws ParseException
     * @throws IOException
     */
    public void filterCommand(String command) throws ParseException, IOException {
        JSONObject commandJSON = (JSONObject) jsonParser.parse(command);
        
        if (commandJSON.get("command").equals("movePlayer"))
            this.moverCanon(commandJSON);

        if (commandJSON.get("command").equals("updateGameState"))
            this.updateGameState(commandJSON);
        
//        if (commandJSON.get("command").equals("moveEnemies"))
//            this.moverEnemigo(commandJSON);

//        if (commandJSON.get("command").equals("moveBulletEnemy") || commandJSON.get("command").equals("moveBulletPlayer"))
//            this.moverBalas(commandJSON);

        if (commandJSON.get("command").equals("updateBunkers"))
            this.actualizarEscudo(commandJSON);

        if (commandJSON.get("command").equals("attacked"))
            this.attacked(commandJSON);

//        if (commandJSON.get("command").equals("putBulletEnemy") || commandJSON.get("command").equals("putBulletPlayer"))
//            this.putBullet(commandJSON);

        if (commandJSON.get("command").equals("killEnemy"))
            this.killEnemy(commandJSON);

        if (commandJSON.get("command").equals("win"))
            this.win(commandJSON);

        if (commandJSON.get("command").equals("gameOver"))
            this.gameOver();

//        if (commandJSON.get("command").equals("moveSpacecraft"))
//            this.moveSpacecraft(commandJSON);
    }

    private void win(JSONObject commandJSON) throws IOException {
        this.canon.aumentarVida();
        try {
            Thread.sleep(20);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        this.sendClientes(Serializer.updateLives(this.gameId,this.canon.getVidas()));
    }

    private void updateGameState(JSONObject commandJSON) throws IOException {
        try {
            Thread.sleep(20);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        this.sendObservers(commandJSON.toJSONString());
    }


    private void moveSpacecraft(JSONObject commandJSON) throws IOException {
        try {
            Thread.sleep(20);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        this.sendObservers(commandJSON.toJSONString());
    }

    private void killEnemy(JSONObject commandJSON) throws IOException {
        Integer enemyId = Integer.parseInt(commandJSON.get("id").toString());
        String enemyType = commandJSON.get("type").toString();

        Enemigo enemigo = FactoryEnemigo.getEnemigo(enemyType,enemyId);

        if (enemigo.getTipo().equals("spacecraft"))
            enemigo.setPuntaje(Controller.getSpacecraftPoints());

        this.canon.aumentarPuntaje(enemigo.getPuntaje());

        this.enemigos.remove(enemigo);

        sendClientes(Serializer.updateScore(this.gameId,this.canon.getPuntaje()));
    }

    private void putBullet(JSONObject commandJSON) throws IOException {
        try {
            Thread.sleep(20);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        this.sendObservers(commandJSON.toJSONString());
    }

    private void attacked(JSONObject commandJSON) throws IOException {
        this.canon.reducirVida();
        System.out.println("Vida del jugador: " + this.canon.getVidas());
        if (this.canon.getVidas() == 0){
            System.out.println("la vida es 0");
            this.gameOver();
        } else {
            this.sendClientes(Serializer.updateLives(this.gameId,this.canon.getVidas()));
        }
    }

    public void sendClientes(String command) throws IOException {
        if (player != null){
            player.send(command);
            sendObservers(command);
        }
    }

    private void actualizarEscudo(JSONObject commandJSON) throws IOException {
        try {
            Thread.sleep(20);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        this.sendObservers(commandJSON.toJSONString());
    }

    private void moverBalas(JSONObject commandJSON) throws IOException {
        try {
            Thread.sleep(20);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        this.sendObservers(commandJSON.toJSONString());
    }

    private void moverEnemigo(JSONObject commandJSON) throws IOException {
        try {
            Thread.sleep(20);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        this.sendObservers(commandJSON.toJSONString());
    }

    private void moverCanon(JSONObject commandJSON) throws IOException {
        Integer posX = Integer.parseInt(commandJSON.get("posX").toString());
        Integer posY = Integer.parseInt(commandJSON.get("posY").toString());
        this.canon.setPosX(posX);
        this.canon.setPosY(posY);
        this.sendObservers(commandJSON.toJSONString());
    }

    public void sendObservers(String command) throws IOException {
        if (player != null){
            for (ClientHandler observer : observers){
                observer.send(command);
            }
        }
    }

    public void addObserver(ClientHandler observer) throws IOException {
        try {
            Thread.sleep(3500);

        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        this.observers.add(observer);
        //observer.send(Serializer.sendAllGame(gameId,this.canon,this.enemigos,this.enemyBullet,this.playerBullet,this.escudos));
    }

    public void removeObserver(ClientHandler clientHandler) {
        this.observers.remove(clientHandler);
    }

    public void gameOver() throws IOException {
        try {
            Thread.sleep(1000);

        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        this.canon.setPuntaje(0);
        this.canon.setVidas(3);
        this.sendClientes(Serializer.gameOver(this.gameId,0,3));
    }
}
