/*
  Reto 5 - LED indicador
  ----------------------
  Se agrega un quinto LED (pin 7) que permanece apagado durante
  el conteo normal, y se enciende únicamente cuando el contador
  llega a 15 (1111). Al reiniciar el conteo (volver a 0), el
  LED indicador se apaga.
*/

const int pinesLED[4] = {2, 3, 4, 5};
const int NUM_BITS = 4;
const int pinIndicador = 7; // quinto LED, indicador

int waitDelay = 500;

void setup() {
  for (int i = 0; i < NUM_BITS; i++) {
    pinMode(pinesLED[i], OUTPUT);
  }
  pinMode(pinIndicador, OUTPUT);
}

void loop() {
  for (int numero = 0; numero <= 15; numero++) {
    mostrarBinario(numero);

    // Si el número actual es 15, encendemos el LED indicador
    if (numero == 15) {
      digitalWrite(pinIndicador, HIGH);
    } else {
      digitalWrite(pinIndicador, LOW);
    }

    delay(waitDelay);
  }
  // Al reiniciar el for desde 0, el LED indicador se apaga
  // automáticamente en la primera iteración (numero == 0).
}

void mostrarBinario(int numero) {
  for (int bit = 0; bit < NUM_BITS; bit++) {
    int estadoBit = numero & (1 << bit);

    if (estadoBit != 0) {
      digitalWrite(pinesLED[bit], HIGH);
    } else {
      digitalWrite(pinesLED[bit], LOW);
    }
  }
}
