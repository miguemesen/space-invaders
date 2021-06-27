package tec.server.app.Entities.enemigos;

public class FactoryEnemigo {

    public static Enemigo getEnemigo(String tipo, Integer id){
        switch (tipo) {
            case "octo":
                return new Pulpo(id);
            case "squid":
                return new Calamar(id);
            case "crab":
                return new Cangrejo(id);
            default:
                return new Platillo(id);
        }
    }
}
