package tec.server.app.server;



import java.io.*;
import java.net.*;


public class Server extends Thread{

    private static ServerSocket server;
    private static boolean running = true;
    public static Server serverInstance;

    public Server(Integer port) {
        try {
            server = new ServerSocket(port);
            System.out.println("Init Server");
            this.start();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static Server getInstance(Integer port){
        if (serverInstance == null){
            serverInstance = new Server(port);
        }
        return serverInstance;
    }

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
