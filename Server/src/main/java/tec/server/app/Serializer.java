package tec.server.app;

import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;

public class Serializer {



    public static String gameRefused(Integer gameId){
        JSONObject jsonObject = new JSONObject();
        jsonObject.put("command", "connectionRefused");
        jsonObject.put("gameId",gameId);
        return jsonObject.toJSONString();
    }

    public static String iniciarJuego(Integer gameId){
        JSONObject jsonObject = new JSONObject();
        jsonObject.put("command","startGame");
        jsonObject.put("gameId",gameId);
        return jsonObject.toJSONString();
    }

}
