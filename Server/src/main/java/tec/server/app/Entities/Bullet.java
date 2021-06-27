package tec.server.app.Entities;

public class Bullet {

    private Integer posX;
    private Integer posY;
    private Boolean isActive;

    public Bullet(Boolean isActive) {
        this.isActive = false;
    }

    public Boolean isActive() {
        return isActive;
    }

    public void setIsActive(Boolean active) {
        isActive = active;
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
}
