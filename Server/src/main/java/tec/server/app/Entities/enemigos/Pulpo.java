package tec.server.app.Entities.enemigos;

public class Pulpo extends Enemigo{


    public Pulpo(Integer id) {
        super(id);
        this.setTipo("octo");
        this.setPuntaje(40);
    }
}
