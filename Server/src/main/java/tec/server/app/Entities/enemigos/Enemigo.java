package tec.server.app.Entities.enemigos;

public abstract class Enemigo {
    private Integer id;
    private String tipo; // 1: Pulpo | 2: Calamar | 3: Cangrejo | 4: Platillo
    private Integer puntaje;

    public Enemigo(Integer id) {
        this.id = id;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getTipo() {
        return tipo;
    }

    public void setTipo(String tipo) {
        this.tipo = tipo;
    }

    public Integer getPuntaje() {
        return puntaje;
    }

    public void setPuntaje(Integer puntaje) {
        this.puntaje = puntaje;
    }
}
