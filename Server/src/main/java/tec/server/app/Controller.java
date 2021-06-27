package tec.server.app;

import javafx.event.ActionEvent;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.TextField;
import tec.server.app.Entities.enemigos.Enemigo;
import tec.server.app.Entities.enemigos.FactoryEnemigo;
import tec.server.app.server.ClientHandler;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class Controller {
    public TextField insertarEnemigoPosicion;
    public Button botonInsertarEnemigo;
    public Button botonEliminar;
    public CheckBox checkBoxFilaUno;
    public CheckBox checkBoxFilaDos;
    public CheckBox checkBoxFilaTres;
    public TextField posicionEnemigoEliminar;
    public CheckBox todosEliminar;
    public TextField puntajeEnemigoAleatorio;
    public Button insertarEnemigoAleatorio;
    public CheckBox checkBoxJuegoUno;
    public CheckBox checkBoxJuegoDos;
    public CheckBox tipoEnemigoPulpo;
    public CheckBox tipoEnemigoCalamar;
    public CheckBox tipoEnemigoCangrejo;
    public String tipoEnemigo;

    public Boolean isEnemySelected(){
        return tipoEnemigoCalamar.isSelected() || tipoEnemigoPulpo.isSelected() || tipoEnemigoCangrejo.isSelected();
    }

    public Boolean isRowSelected(){
        return checkBoxFilaUno.isSelected() || checkBoxFilaDos.isSelected() || checkBoxFilaTres.isSelected();
    }

    public List<Enemigo> getEnemyList(){
        List<Enemigo> list = new ArrayList<>();
        if (checkBoxFilaUno.isSelected()){
            for (int i=1; i <= 10; i++){
                list.add(FactoryEnemigo.getEnemigo(tipoEnemigo,i));
            }
        }
        if (checkBoxFilaDos.isSelected()){
            for (int i=11; i <= 20; i++){
                list.add(FactoryEnemigo.getEnemigo(tipoEnemigo,i));
            }
        }
        if (checkBoxFilaUno.isSelected()){
            for (int i=21; i <= 30; i++){
                list.add(FactoryEnemigo.getEnemigo(tipoEnemigo,i));
            }
        }
        return list;
    }


    public void insertarEnemigo() throws IOException {
        if (checkBoxJuegoUno.isSelected() && isEnemySelected()){
            if (isRowSelected()){
                ClientHandler.getGameById(1).sendClientes(Serializer.colocarEnemigos(getEnemyList()));
            }
            else {
                try {
                    Integer posicionEnemigo = Integer.parseInt(insertarEnemigoPosicion.getText());
                    if (0 < posicionEnemigo && posicionEnemigo < 31){
                        List<Enemigo> enemigos = new ArrayList<>();
                        enemigos.add(FactoryEnemigo.getEnemigo(tipoEnemigo,posicionEnemigo));
                        ClientHandler.getGameById(1).sendClientes(Serializer.colocarEnemigos(enemigos));
                    } else {
                        System.out.println("Posicion ingresada no se encuentra en el mapa");
                    }
                } catch (NumberFormatException | IOException e) {
                    e.printStackTrace();
                }
            }
        }
        else if (checkBoxJuegoDos.isSelected()){
            if (isRowSelected()){
                ClientHandler.getGameById(2).sendClientes(Serializer.colocarEnemigos(getEnemyList()));
            }
            else {
                try {
                    Integer posicionEnemigo = Integer.parseInt(insertarEnemigoPosicion.getText());
                    if (0 < posicionEnemigo && posicionEnemigo < 31){
                        List<Enemigo> enemigos = new ArrayList<>();
                        enemigos.add(FactoryEnemigo.getEnemigo(tipoEnemigo,posicionEnemigo));
                        ClientHandler.getGameById(2).sendClientes(Serializer.colocarEnemigos(enemigos));
                    } else {
                        System.out.println("Posicion ingresada no se encuentra en el mapa");
                    }
                } catch (NumberFormatException | IOException e) {
                    e.printStackTrace();
                }
            }
        } else {
            System.out.println("No se selecciona el juego que quiere manejar");
        }
    }

    public void iniciarJuego(ActionEvent actionEvent) throws IOException {
        if (checkBoxJuegoUno.isSelected()){
            Objects.requireNonNull(ClientHandler.getGameById(1)).iniciarJuego();
        }
        else if (checkBoxJuegoDos.isSelected()){
            Objects.requireNonNull(ClientHandler.getGameById(2)).iniciarJuego();
        } else {
            System.out.println("No se selecciona el juego que quiere manejar");
        }
    }

    public void isCheckedJuegoUno(ActionEvent actionEvent) {
        checkBoxJuegoDos.setSelected(false);
    }

    public void isCheckedJuegoDos(ActionEvent actionEvent) {
        checkBoxJuegoUno.setSelected(false);
    }

    public void isCheckedEliminarTodos(ActionEvent actionEvent) {
        posicionEnemigoEliminar.clear();
        checkBoxFilaUno.setSelected(false);
        checkBoxFilaDos.setSelected(false);
        checkBoxFilaTres.setSelected(false);
    }

    public void isCheckedPulpo(ActionEvent actionEvent) {
        tipoEnemigoCalamar.setSelected(false);
        tipoEnemigoCangrejo.setSelected(false);
        tipoEnemigo = "pulpo";
    }

    public void isCheckedCalamar(ActionEvent actionEvent) {
        tipoEnemigoCangrejo.setSelected(false);
        tipoEnemigoPulpo.setSelected(false);
        tipoEnemigo = "calamar";
    }

    public void isCheckedCangrejo(ActionEvent actionEvent) {
        tipoEnemigoPulpo.setSelected(false);
        tipoEnemigoCalamar.setSelected(false);
        tipoEnemigo = "cangrejo";
    }


    public void eliminarEnemigo(ActionEvent actionEvent) throws IOException {
        if (checkBoxJuegoUno.isSelected()){
            if (todosEliminar.isSelected()){
                if (Objects.requireNonNull(ClientHandler.getGameById(1)).getEnemigos().size() >0){

                }
            }
        }
    }


    public void isCheckedFilaUno(ActionEvent actionEvent) {
        insertarEnemigoPosicion.clear();
        todosEliminar.setSelected(false);
        posicionEnemigoEliminar.clear();
    }

    public void isCheckedFilaDos(ActionEvent actionEvent) {
        insertarEnemigoPosicion.clear();
        todosEliminar.setSelected(false);
        posicionEnemigoEliminar.clear();
    }

    public void isCheckedFilaTres(ActionEvent actionEvent) {
        insertarEnemigoPosicion.clear();
        todosEliminar.setSelected(false);
        posicionEnemigoEliminar.clear();
    }
}
