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

        if (commandJSON.get("command").equals("killSpacecraft"))
            this.killSpacecraft(commandJSON);

        if (commandJSON.get("command").equals("killEnemy"))
            this.killEnemy(commandJSON);

        if (commandJSON.get("command").equals("enemyImpact"))
            this.enemyImpact();

        if (commandJSON.get("command").equals("win"))
            this.win(commandJSON);

        if (commandJSON.get("command").equals("gameOver"))
            this.gameOver();

//        if (commandJSON.get("command").equals("moveSpacecraft"))
//            this.moveSpacecraft(commandJSON);
    }

    /**
     * Avisa al cliente que el juego ha terminado porque los alienigenas
     * impactaron el canon.
     * @throws IOException
     */
    private void enemyImpact() throws IOException {
        this.gameOver();
    }

    /**
     * Avisa al cliente la eliminacion de la nave aleatoria y actualiza los puntajes
     * @param commandJSON informacion enviada desde el cliente
     * @throws IOException
     */
    private void killSpacecraft(JSONObject commandJSON) throws IOException {
        this.canon.aumentarPuntaje(Controller.getSpacecraftPoints());
        sendClientes(Serializer.updateScore(this.gameId,this.canon.getPuntaje()));
    }

    /**
     * Aumenta la vida del jugador cuando gana y actualiza los datos en los clientes
     * @param commandJSON Comando recibidos del cliente
     * @throws IOException
     */
    private void win(JSONObject commandJSON) throws IOException {
        this.canon.aumentarVida();
        try {
            Thread.sleep(20);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        this.sendClientes(Serializer.updateLives(this.gameId,this.canon.getVidas()));
    }

    /**
     * Toma la informacion recibida del jugador y Actualiza el estado del
     * juego a lado del observador.
     * @param commandJSON Comando recibidos del cliente indicandole al server que esta pasando
     * @throws IOException
     */
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

    /**
     * Elimina al enemigo derribado en el juego y actualiza el estado del juego
     * y los puntos que se muestran en pantalla.
     * @param commandJSON
     * @throws IOException
     */
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

    /**
     * Reduce la vida del canon y verifica si este aun tiene vidas suficientes
     * para continuar la partida, si no es asi, le indica a los clientes
     * que la partida acabo
     * @param commandJSON Comando con la informacion del cliente jugador
     * @throws IOException
     */
    private void attacked(JSONObject commandJSON) throws IOException {
        this.canon.reducirVida();
        if (this.canon.getVidas() == 0){
            this.gameOver();
        } else {
            this.sendClientes(Serializer.updateLives(this.gameId,this.canon.getVidas()));
        }
    }

    /**
     * Envia un comando a los clientes, tanto jugador como observador
     * @param command Comando que se le quiere enviar a los clientes
     * @throws IOException
     */
    public void sendClientes(String command) throws IOException {
        if (player != null){
            player.send(command);
            sendObservers(command);
        }
    }

    /**
     * Envia al cliente el estado actual de los escudos
     * @param commandJSON
     * @throws IOException
     */
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

    /**
     * Lleva registro de los movimientos del cliente jugador y luego los envia
     * al cliente observador para que este los display en pantalla
     * @param commandJSON un comando que incluye las posiciones del canon en el cliente jugador
     * @throws IOException
     */
    private void moverCanon(JSONObject commandJSON) throws IOException {
        Integer posX = Integer.parseInt(commandJSON.get("posX").toString());
        Integer posY = Integer.parseInt(commandJSON.get("posY").toString());
        this.canon.setPosX(posX);
        this.canon.setPosY(posY);
        this.sendObservers(commandJSON.toJSONString());
    }

    /**
     * Envia comandos a solo los observadores
     * @param command comando que desea enviarle al observador
     * @throws IOException
     */
    public void sendObservers(String command) throws IOException {
        if (player != null){
            for (ClientHandler observer : observers){
                observer.send(command);
            }
        }
    }

    /**
     * Agrega a un cliente observador a una partida
     * @param observer El cliente observador que quiere unirse a la partida
     * @throws IOException
     */
    public void addObserver(ClientHandler observer) throws IOException {
        try {
            Thread.sleep(3000);

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
        this.canon.setPuntaje(0);
        this.canon.setVidas(3);
        this.sendClientes(Serializer.gameOver(this.gameId,0,3));
    }
}
