package tec.server.app.server;

import java.io.*;
import java.net.*;

import org.json.simple.JSONObject;
import org.json.simple.parser.*;
import tec.server.app.Game;

public class ClientHandler implements Runnable{

    private final Socket clientSocket;
    private JSONParser jsonParser;
    private PrintWriter out;
    private BufferedReader in;
    private Game game;


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

    public void newGameHandler(JSONObject responseJson){
        this.out.println("Se crea un nuevo juego");
    }


    @Override
    public void run() {

        try {

            String response;
            while ((response = in.readLine()) != null) {


                JSONObject responseJson = (JSONObject) (this.jsonParser.parse(response));
                String command = responseJson.get("command").toString();

                if (command.equals("newGame")){
                    this.newGameHandler(responseJson);
                } else {
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
