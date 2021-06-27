package tec.server.app.server;



import java.io.*;
import java.net.*;


public class Server extends Thread{

    private static ServerSocket server;
    private static boolean running = true;
    public static Server serverInstance;

    /**
     * Metodo constructor del server
     * @param port Puerto donde el server iniciado estara escuchando
     */
    public Server(Integer port) {
        try {
            server = new ServerSocket(port);
            System.out.println("Init Server");
            this.start();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * Singleton para tomar una instancia del server
     * @param port Puerto donde el server iniciado estara escuchando
     * @return
     */
    public static Server getInstance(Integer port){
        if (serverInstance == null){
            serverInstance = new Server(port);
        }
        return serverInstance;
    }

    /**
     * Metodo overridden de la clase thread para que el server siempre este corriendo
     */
    @Override
    public void run(){
        while (running){
            try {
                Socket client = server.accept();

                System.out.printf("Client conneted %s \n", client.getInetAddress());

                ClientHandler newClient = new ClientHandler(client);

                new Thread(newClient).start();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
