package tec.server.app.Entities.enemigos;

public class FactoryEnemigo {

    public static Enemigo getEnemigo(String tipo, Integer id){
        switch (tipo) {
            case "pulpo":
                return new Pulpo(id);
            case "calamar":
                return new Calamar(id);
            case "cangrejo":
                return new Cangrejo(id);
            default:
                return new Platillo(id);
        }
    }
}
