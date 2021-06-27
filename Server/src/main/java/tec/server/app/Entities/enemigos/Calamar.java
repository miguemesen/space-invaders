package tec.server.app.Entities.enemigos;

public class Calamar extends Enemigo{

    public Calamar(Integer id) {
        super(id);
        this.setTipo("squid");
        this.setPuntaje(10);
    }
}
