package tec.server.app;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import tec.server.app.Entities.Bullet;
import tec.server.app.Entities.Canon;
import tec.server.app.Entities.Escudo;
import tec.server.app.Entities.enemigos.Enemigo;

import java.util.List;

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

    public static String updateScore(Integer gameId, Integer score){
        JSONObject jsonObject = new JSONObject();
        jsonObject.put("command","updateScore");
        jsonObject.put("gameId",gameId);
        jsonObject.put("score",score);
        return jsonObject.toJSONString();
    }

    public static String updateLives(Integer gameId, Integer lives){
        JSONObject jsonObject = new JSONObject();
        jsonObject.put("command","lives");
        jsonObject.put("lives", lives);
        jsonObject.put("gameId",gameId);
        return jsonObject.toJSONString();
    }

    public static String gameAccepted(Integer gameId) {
        JSONObject jsonObject = new JSONObject();
        jsonObject.put("command", "connectionAccepted");
        jsonObject.put("gameId", gameId);
        return jsonObject.toJSONString();
    }

    public static String moveCanon(Integer gameId, Integer posX, Integer posY) {
        JSONObject jsonObject = new JSONObject();
        jsonObject.put("command", "moveCanon");
        jsonObject.put("gameId",gameId);
        jsonObject.put("posX",posX);
        jsonObject.put("posY",posY);
        return jsonObject.toJSONString();
    }

    public static String eliminarEnemigos(List<Enemigo> enemigos){
        JSONArray jsonArray = new JSONArray();
        for (Enemigo enemigo : enemigos){
            JSONObject jsonObject = new JSONObject();
            jsonObject.put("enemyId",enemigo.getId());
            jsonObject.put("enemyType",enemigo.getTipo());
            jsonArray.add(jsonObject);
        }
        JSONObject jsonObject = new JSONObject();
        jsonObject.put("enemies",jsonArray);
        jsonObject.put("command","removeEnemies");
        return jsonObject.toJSONString();
    }

    public static String colocarEnemigos(List<Enemigo> enemigos){
        JSONArray jsonArray = new JSONArray();
        for (Enemigo enemigo : enemigos){
            JSONObject jsonObject = new JSONObject();
            jsonObject.put("enemyId",enemigo.getId());
            jsonObject.put("enemyType",enemigo.getTipo());
            jsonArray.add(jsonObject);
        }
        JSONObject jsonObject = new JSONObject();
        jsonObject.put("enemies",jsonArray);
        jsonObject.put("command","putEnemmies");
        return jsonObject.toJSONString();
    }

    public static String sendAllGame(Integer gameId, Canon canon, List<Enemigo> enemigos, Bullet enemyBullet, Bullet playerBullet, List<Escudo> escudos) {
        JSONObject jsonObject = new JSONObject();
        jsonObject.put("command","gameObjects");
        jsonObject.put("gameId",gameId);
        jsonObject.put("score",canon.getPuntaje());
        jsonObject.put("lives",canon.getVidas());
        jsonObject.put("posX_canon",canon.getPosX());
        jsonObject.put("posY_canon",canon.getPosY());

        JSONArray jsonArrayEnemigos = new JSONArray();
        for (Enemigo enemigo : enemigos){
            JSONObject jsonObjectEnemigo = new JSONObject();
            jsonObjectEnemigo.put("enemyId",enemigo.getId());
            jsonObjectEnemigo.put("enemyType",enemigo.getTipo());
            jsonArrayEnemigos.add(enemigo);
        }
        jsonObject.put("enemigos",jsonArrayEnemigos);


        JSONArray jsonArrayBullets = new JSONArray();
        JSONObject jsonObjectEnemyBullet = new JSONObject();
        JSONObject jsonObjectPlayerBullet = new JSONObject();

        if (enemyBullet.isActive()){
            jsonObjectEnemyBullet.put("isActive",enemyBullet.isActive());
            jsonObjectEnemyBullet.put("posX_enemyBullet",enemyBullet.getPosX());
            jsonObjectEnemyBullet.put("posY_enemyBullet",enemyBullet.getPosY());
        } else {
            jsonObjectEnemyBullet.put("isActive",enemyBullet.isActive());
        }

        if (playerBullet.isActive()){
            jsonObjectPlayerBullet.put("isActive",playerBullet.isActive());
            jsonObjectPlayerBullet.put("posX_playerBullet",playerBullet.getPosX());
            jsonObjectPlayerBullet.put("posY_playerBullet",playerBullet.getPosY());
        } else {
            jsonObjectPlayerBullet.put("isActive",playerBullet.isActive());
        }

        jsonArrayBullets.add(jsonObjectEnemyBullet);
        jsonArrayBullets.add(jsonObjectPlayerBullet);

        jsonObject.put("bullets",jsonArrayBullets);

        JSONArray jsonArrayEscudos = new JSONArray();
        for (Escudo escudo : escudos){
            JSONObject jsonObjectEscudo = new JSONObject();
            jsonObjectEscudo.put("escudoId",escudo.getId());
            jsonObjectEscudo.put("escudoHealth",escudo.getHealth());
            jsonArrayEscudos.add(jsonObjectEscudo);
        }
        jsonObject.put("escudos",jsonArrayEscudos);
        return jsonObject.toJSONString();
    }
}
