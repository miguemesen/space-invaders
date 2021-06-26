package tec.server.app;

import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;

public class Serializer {



    public static String gameRejected(Integer gameId){
        JSONObject jsonObject = new JSONObject();
        jsonObject.put("command", "connectionRejected");
        jsonObject.put("gameId",gameId);
        return jsonObject.toJSONString();
    }

    /**
     * Cuando se presiona el boton iniciar juego desde el administrador se llama iniciar juego para que el cliente empiece
     * @param gameId id del juego que se quiere iniciar
     * @return
     */
    public static String startGame(Integer gameId){
        JSONObject jsonObject = new JSONObject();
        jsonObject.put("command","startGame");
        jsonObject.put("gameId",gameId);
        return jsonObject.toJSONString();
    }

    public static String gameAccepted(Integer gameId) {
        JSONObject jsonObject = new JSONObject();
        jsonObject.put("command", "connectionAccepted");
        jsonObject.put("gameId", gameId);
        return jsonObject.toJSONString();
    }
}
