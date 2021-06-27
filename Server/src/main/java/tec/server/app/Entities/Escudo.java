package tec.server.app.Entities;

public class Escudo {

    private Integer id;
    private Integer health;

    public Escudo(Integer id) {
        this.id = id;
        this.health = 100;
    }

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public Integer getHealth() {
        return health;
    }

    public void setHealth(Integer health) {
        this.health = health;
    }
}
