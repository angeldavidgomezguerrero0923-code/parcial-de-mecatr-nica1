# Contador Binario de 4 bits con Arduino

Parcial práctico — construcción, programación y documentación de un contador binario de 4 bits usando Arduino UNO, LEDs y una protoboard.

---

## 1. Descripción del proyecto

Este proyecto consiste en un **contador binario de 4 bits** construido con Arduino. Cuatro LEDs representan, mediante sus estados de encendido y apagado, los números decimales del 0 al 15 en su forma binaria. El contador recorre automáticamente esta secuencia, y sobre esa base se desarrollaron cinco variaciones (retos) que modifican su comportamiento: velocidad de conteo, conteo descendente, avance por botón, solo números pares, y un LED indicador adicional.

## 2. Materiales utilizados

- 1 Arduino UNO (o compatible)
- 1 Protoboard
- 5 LEDs (4 para el contador binario + 1 LED indicador del Reto 5)
- 5 resistencias de aproximadamente 220-330 Ω
- 1 pulsador (push button)
- Cables jumper macho-macho
- Cable USB para alimentar y programar el Arduino

## 3. Explicación del circuito

**LEDs y resistencias:** cada uno de los 4 LEDs del contador tiene su ánodo conectado, mediante un cable independiente, a un pin digital del Arduino. El cátodo de cada LED se conecta en serie con una resistencia de 220-330 Ω, y el otro extremo de esa resistencia llega al riel negativo (GND) de la protoboard.

**Pines digitales:** se usaron los pines digitales **2, 3, 4 y 5**, asignados así:

| Pin Arduino | Bit representado | Peso binario |
|---|---|---|
| 2 | Bit 0 (LSB) | 1 |
| 3 | Bit 1 | 2 |
| 4 | Bit 2 | 4 |
| 5 | Bit 3 (MSB) | 8 |

**GND:** todas las resistencias comparten el mismo riel negativo de la protoboard, y ese riel se conecta con un único cable al pin **GND** del Arduino. Esto cierra el circuito eléctrico para los 5 LEDs a la vez.

**Pulsador (Reto 3):** una pata del pulsador se conecta al pin digital 6, y la otra a GND. Se usó `INPUT_PULLUP` en el código, por lo que no fue necesaria una resistencia externa para el botón.

**LED indicador (Reto 5):** un quinto LED, independiente del contador, se conectó con su ánodo al pin digital 7 (a través de una resistencia de 220-330 Ω) y su cátodo al mismo riel de GND que los demás.

## 4. Funcionamiento del contador binario

Cada LED representa un dígito (bit) de un número binario de 4 bits. Al combinar los 4 LEDs (encendido = 1, apagado = 0) se pueden representar los 16 valores posibles, del 0 al 15:

| Decimal | Binario | LEDs (MSB→LSB) |
|---|---|---|
| 0 | 0000 | Todos apagados |
| 1 | 0001 | Solo bit 0 encendido |
| 2 | 0010 | Solo bit 1 encendido |
| 3 | 0011 | Bits 0 y 1 encendidos |
| ... | ... | ... |
| 15 | 1111 | Todos encendidos |

El programa recorre esta tabla completa y actualiza los 4 LEDs en cada paso según el valor binario correspondiente.

## 5. Explicación del código

- **`setup()`**: función que se ejecuta una sola vez al encender o reiniciar el Arduino. Aquí se configuran los pines de los LEDs como salidas (`OUTPUT`).
- **`loop()`**: función que se repite continuamente mientras el Arduino esté encendido. Aquí vive la lógica del conteo (el ciclo que recorre los números).
- **`pinMode(pin, modo)`**: le indica al Arduino si un pin se va a usar para enviar señal (`OUTPUT`, como los LEDs) o para leer una señal externa (`INPUT`/`INPUT_PULLUP`, como el botón).
- **`digitalWrite(pin, valor)`**: envía una señal `HIGH` (5V, enciende el LED) o `LOW` (0V, apaga el LED) a un pin configurado como salida.
- **`digitalRead(pin)`**: lee el estado actual de un pin configurado como entrada; se usó para saber si el botón está presionado (`LOW`) o no (`HIGH`).
- **`delay(ms)`**: pausa la ejecución del programa por la cantidad de milisegundos indicada. Se usó para controlar cuánto tiempo se muestra cada número antes de pasar al siguiente.
- **Arreglos (arrays)**: se usó un arreglo (`pinesLED[4] = {2, 3, 4, 5}`) para guardar los 4 pines de los LEDs en una sola variable, y así poder recorrerlos con un ciclo en vez de repetir código 4 veces.
- **Ciclos `for`**: se usan en dos niveles — uno para recorrer los números del 0 al 15 (o de 15 a 0, o de 2 en 2), y otro anidado para recorrer los 4 bits de cada número y decidir qué LED encender.
- **Operador `%`**: usado conceptualmente en el Reto 4 para verificar números pares (`numero % 2 == 0`), aunque en la implementación final se optó por incrementar de 2 en 2 (`numero += 2`), que logra el mismo resultado de forma más directa.
- **Operadores bitwise (`&` y `<<`)**: `1 << bit` desplaza el número 1 hacia la izquierda "bit" posiciones, generando una máscara binaria (por ejemplo, `1 << 2` = `0100`). Al combinarlo con `&` (`numero & (1 << bit)`), se compara únicamente esa posición del número: si el resultado es distinto de cero, ese bit específico está en 1; si es cero, el bit está en 0. Así se decide, bit por bit, qué LED debe encenderse.

## 6. Desarrollo de los cinco retos

### Reto 1 — Velocidad del contador
- **Qué se solicitaba:** que el tiempo entre cada número fuera de 500 ms, usando una variable en vez de escribir `delay(500)` repetido en el código.
- **Modificación realizada:** se declaró la variable `int waitDelay = 500;` al inicio del programa, y se reemplazó cualquier `delay(...)` fijo por `delay(waitDelay);`.
- **Parte del código modificada:** declaración de la variable global y la línea de `delay()` dentro del `loop()`.
- **Resultado obtenido:** el contador avanza un número cada 500 ms de forma consistente, y el tiempo se puede ajustar cambiando un solo valor.

### Reto 2 — Contador descendente
- **Qué se solicitaba:** que el contador fuera de 15 a 0 y reiniciara desde 15.
- **Modificación realizada:** se cambió el ciclo `for` de `loop()` para que empiece en 15 y decremente (`numero--`) hasta 0.
- **Parte del código modificada:** la condición e incremento del ciclo `for` principal (`for (int numero = 15; numero >= 0; numero--)`).
- **Resultado obtenido:** los LEDs muestran la secuencia binaria en orden descendente y reinician automáticamente al llegar a 0, gracias a que el `for` se vuelve a ejecutar en cada vuelta del `loop()`.

### Reto 3 — Control mediante botón
- **Qué se solicitaba:** que el contador avance una posición solo cuando se presiona un botón, en vez de avanzar automáticamente.
- **Modificación realizada:** se eliminó el `delay()` automático entre números y se agregó lectura del botón con `digitalRead()`. Se detecta el flanco de bajada (cuando el botón pasa de no presionado a presionado) para incrementar el contador una sola vez por pulsación.
- **Parte del código modificada:** se agregó la variable `numero` como global (para recordar su valor entre lecturas), la configuración del pin del botón (`INPUT_PULLUP`), y la lógica de detección de flanco dentro de `loop()`.
- **Resultado obtenido:** cada pulsación del botón avanza el contador exactamente una posición, y al superar 15 reinicia a 0.

### Reto 4 — Mostrar solamente números pares
- **Qué se solicitaba:** que el contador solo muestre 0, 2, 4, 6, 8, 10, 12 y 14.
- **Modificación realizada:** se cambió el incremento del ciclo `for` de `numero++` a `numero += 2`, comenzando en 0 y terminando en 14.
- **Parte del código modificada:** la línea del ciclo `for` en `loop()`.
- **Resultado obtenido:** los LEDs solo muestran los 8 valores pares en su representación binaria correcta, saltándose los impares.

### Reto 5 — LED indicador
- **Qué se solicitaba:** agregar un quinto LED que se mantenga apagado durante el conteo normal y se encienda únicamente al llegar a 15.
- **Modificación realizada:** se agregó un nuevo pin (`pinIndicador = 7`), configurado como salida en `setup()`. Dentro del `loop()`, se agregó una condición: si `numero == 15`, se enciende ese LED; en cualquier otro caso, permanece apagado.
- **Parte del código modificada:** declaración del nuevo pin, su `pinMode()`, y el bloque `if/else` dentro del ciclo principal.
- **Resultado obtenido:** el quinto LED permanece apagado durante todo el conteo y se enciende brevemente solo cuando los 4 LEDs principales muestran 1111 (15), apagándose de nuevo al reiniciar el conteo.

## 7. Evidencias

> Coloca aquí las fotos y capturas correspondientes dentro de las carpetas `evidencias/montaje_fisico/` y `evidencias/simulacion/`, y enlázalas abajo.

- Montaje físico: `evidencias/montaje_fisico/...`
- Arduino conectado: `evidencias/montaje_fisico/...`
- Funcionamiento de los LEDs: `evidencias/montaje_fisico/...`
- Simulación en Tinkercad: `evidencias/simulacion/...`
- Implementación del botón: `evidencias/simulacion/...`
- Implementación del quinto LED: `evidencias/simulacion/...`

Ejemplo de cómo insertar una imagen en este README una vez subida:
```markdown
![Montaje físico](evidencias/montaje_fisico/foto1.jpg)
```




## Integrantes del grupo

- Angel terryl
- Andres bravo
