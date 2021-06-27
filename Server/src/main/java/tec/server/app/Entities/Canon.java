package tec.server.app.Entities;

public class Canon {
    private Integer vidas;
    private Integer puntaje;
    private Integer posX;
    private Integer posY;

    public Canon(){
        this.vidas = 3;
        this.puntaje = 0;
    }

    public void aumentarPuntaje(Integer puntos){
        puntaje+=puntos;
    }

    public void reducirVida(){
        vidas--;
    }

    public void aumentarVida(){
        vidas++;
    }

    public Integer getPosX() {
        return posX;
    }

    public void setPosX(Integer posX) {
        this.posX = posX;
    }

    public Integer getPosY() {
        return posY;
    }

    public void setPosY(Integer posY) {
        this.posY = posY;
    }

    public Integer getVidas() {
        return vidas;
    }

    public void setVidas(Integer vidas) {
        this.vidas = vidas;
    }

    public Integer getPuntaje() {
        return puntaje;
    }

    public void setPuntaje(Integer puntaje) {
        this.puntaje = puntaje;
    }
}
