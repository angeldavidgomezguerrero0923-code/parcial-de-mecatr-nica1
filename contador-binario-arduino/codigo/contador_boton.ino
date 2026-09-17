/*
  Reto 3 - Control mediante botón
  --------------------------------
  El contador ya NO avanza solo. Cada vez que se presiona el
  pulsador, el número mostrado en los LEDs aumenta en 1.

  Conexión sugerida del botón:
    - Una pata al pin digital 6
    - La misma pata a GND a través de una resistencia (o usando
      INPUT_PULLUP como se hace en este código, que no requiere
      resistencia externa)
    - La otra pata del botón al pin digital 6 también, cerrando
      el circuito al presionar.

  Con INPUT_PULLUP, el pin lee HIGH cuando el botón NO está
  presionado, y LOW cuando SÍ está presionado.
*/

const int pinesLED[4] = {2, 3, 4, 5};
const int NUM_BITS = 4;
const int pinBoton = 6;

int waitDelay = 500; // se usa como tiempo de "antirrebote" (debounce)

int numero = 0;          // valor actual del contador
int estadoBotonAnterior = HIGH; // estado anterior del botón (sin presionar)

void setup() {
  for (int i = 0; i < NUM_BITS; i++) {
    pinMode(pinesLED[i], OUTPUT);
  }

  pinMode(pinBoton, INPUT_PULLUP);

  // Mostramos el estado inicial (0) apenas arranca el programa
  mostrarBinario(numero);
}

void loop() {
  int estadoBotonActual = digitalRead(pinBoton);

  // Detectamos el momento en que el botón pasa de "no presionado" (HIGH)
  // a "presionado" (LOW). Esto evita que el contador avance varias
  // veces con una sola pulsación.
  if (estadoBotonActual == LOW && estadoBotonAnterior == HIGH) {
    numero++;

    // Si supera 15, reiniciamos a 0
    if (numero > 15) {
      numero = 0;
    }

    mostrarBinario(numero);
    delay(waitDelay); // pequeña pausa para evitar rebotes del botón
  }

  estadoBotonAnterior = estadoBotonActual;
}

void mostrarBinario(int num) {
  for (int bit = 0; bit < NUM_BITS; bit++) {
    int estadoBit = num & (1 << bit);

    if (estadoBit != 0) {
      digitalWrite(pinesLED[bit], HIGH);
    } else {
      digitalWrite(pinesLED[bit], LOW);
    }
  }
}
