# Ejercicio 3.2 - Sincronización con Semáforos 

Este módulo implementa el uso de semáforos POSIX (`semaphore.h`) para resolver los problemas de concurrencia analizados anteriormente. El objetivo es garantizar la integridad de la variable compartida mediante ráfagas controladas de acceso.

## Metodología de Pruebas y Resultados de la Tabla 2

Para esta sección, se evaluó la eficacia del semáforo binario incrementando el valor de `MAX` a escalas masivas. A diferencia del ejercicio anterior, aquí la sincronización es forzada por software:

### 1. Prueba con MAX = 1e6 (1,000,000)
El programa se ejecuta de forma casi instantánea, devolviendo un valor exacto debido a la protección de la región crítica.
* **Resultado:** `a = 0`
![Resultado 1e6](1e6.png)

### 2. Prueba con MAX = 1e9 (1,000,000,000)
Al procesar mil millones de iteraciones, se observa un incremento en el tiempo de ejecución (aproximadamente 15-20 segundos). Esto se debe al "overhead" o sobrecarga que genera el sistema operativo al bloquear y desbloquear el semáforo mil millones de veces.
* **Resultado:** `a = 0`
![Resultado 1e9](1e9.png)

### 3. Prueba con MAX = 1e12 (1,000,000,000,000)
En la escala de un billón de iteraciones, el tiempo de espera es considerablemente mayor (varios minutos), sin embargo, la precisión aritmética se mantiene íntegra.
* **Resultado:** `a = 0`
![Resultado 1e12](1e12.png)

---

## Análisis Técnico: El rol del Semáforo en la integridad de datos

En este ejercicio, la obtención del valor `0` no depende de la velocidad del procesador o del azar, sino de la implementación de primitivas de sincronización:

* **Mecanismo de Bloqueo (`sem_wait`):** Antes de que un hilo modifique la variable `a`, ejecuta una instrucción de espera que decrementa el semáforo. Si el valor llega a 0, cualquier otro hilo que intente entrar queda en estado de suspensión (*blocked*).
* **Exclusión Mutua:** El semáforo garantiza que solo un hilo se encuentre dentro de la región crítica a la vez. Esto evita que las operaciones de lectura, incremento y escritura se solapen entre los núcleos del procesador.
* **Sincronización Determinista:** Aunque aumentemos el valor de `MAX` a cifras astronómicas, el resultado siempre será cero porque el semáforo obliga a un ordenamiento lógico de las operaciones, eliminando de raíz la condición de carrera (*race condition*).

---

## Instrucciones de Compilación y Ejecución

Para correr este ejercicio en Ubuntu Server:

```bash
gcc con_semaforos.c -o con_semaforos -lpthread
./con_semaforos
