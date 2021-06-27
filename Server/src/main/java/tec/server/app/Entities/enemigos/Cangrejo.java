package tec.server.app.Entities.enemigos;

public class Cangrejo extends Enemigo{
    public Cangrejo(Integer id) {
        super(id);
        this.setTipo(3);
        this.setPuntaje(20);
    }
}
