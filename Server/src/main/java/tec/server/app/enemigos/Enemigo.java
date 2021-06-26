package tec.server.app.enemigos;

public abstract class Enemigo {
    private Integer id;
    private Integer tipo; // 1: Pulpo | 2: Calamar | 3: Cangrejo | 4: Platillo
    private Integer puntaje;

    public Enemigo(Integer id) {
        this.id = id;
    }


    public Integer getTipo() {
        return tipo;
    }

    public void setTipo(Integer tipo) {
        this.tipo = tipo;
    }

    public Integer getPuntaje() {
        return puntaje;
    }

    public void setPuntaje(Integer puntaje) {
        this.puntaje = puntaje;
    }
}
