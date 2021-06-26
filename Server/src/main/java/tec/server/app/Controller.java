package tec.server.app;

import javafx.event.ActionEvent;
import javafx.scene.control.Button;
import javafx.scene.control.CheckBox;
import javafx.scene.control.TextField;
import tec.server.app.server.ClientHandler;

import java.io.IOException;
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


    public void insertarEnemigo(){

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

    public void isCheckedPulpo(ActionEvent actionEvent) {
        tipoEnemigoCalamar.setSelected(false);
        tipoEnemigoCangrejo.setSelected(false);
    }

    public void isCheckedCalamar(ActionEvent actionEvent) {
        tipoEnemigoCangrejo.setSelected(false);
        tipoEnemigoPulpo.setSelected(false);
    }

    public void isCheckedCangrejo(ActionEvent actionEvent) {
        tipoEnemigoPulpo.setSelected(false);
        tipoEnemigoCalamar.setSelected(false);
    }
}
