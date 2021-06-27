package tec.server.app.Entities.enemigos;

public class Pulpo extends Enemigo{


    public Pulpo(Integer id) {
        super(id);
        this.setTipo(1);
        this.setPuntaje(40);
    }
}
