# Ejercicio 3.3 - Control de 3 Hilos Concurrentes con Semáforos

En esta sección de la práctica se expandió el entorno concurrente agregando un tercer flujo de ejecución simultáneo, controlando el acceso a la variable compartida mediante el mismo semáforo binario e inspeccionando su estado interno con `sem_getvalue`.

## Explicación de los Cambios y Comentarios Añadidos

A diferencia de los laboratorios anteriores que solo usaban dos flujos, en este programa implementamos modificaciones tanto en la estructura principal como en las tareas secundarias. En el código se añadieron comentarios simples en minúsculas para detallar cada cambio:

### 1. Modificaciones en la Función Principal (main)
En la primera parte del código declaramos la lógica de control, la variable para la lectura del semáforo y la inicialización del recurso.
* **Comentarios documentados:** Se especificaron las líneas donde se aumenta la variable para identificar al `hilo3`, la creación del mismo para que empiece a correr en paralelo, y la espera obligatoria con `pthread_join` para que no se cierre el programa antes de tiempo.
* **Estructura inicial en el editor:**
![Inicio del código fuente en nano](codigo1.jpeg)

### 2. Monitoreo del Estado del Semáforo
Justo después de lanzar los tres hilos, utilizamos la función `sem_getvalue(&s, &valor_semaforo)` para leer qué valor tiene el semáforo en ese microsegundo y lo imprimimos con un `printf`. Esto sirve para ver si el recurso está libre (`1`) o si algún hilo ya lo bloqueó (`0`).

### 3. Implementación del Tercer Hilo
Aumentamos una función completa llamada `funcion_hilo3`. La lógica mantiene las mismas directivas de seguridad usando `sem_wait(&s)` al entrar para pedir permiso y bloquear el acceso, y `sem_post(&s)` al salir para avisar que la variable queda libre. La diferencia es que este flujo realiza una operación de suma doble (`a += 2`) en cada vuelta del bucle.
* **Lógica del tercer hilo en el editor:**
![Final del código fuente en nano](codigo2.jpeg)

---

## Análisis de Resultados de la Ejecución

Al compilar el archivo con soporte para hilos (`-lpthread`) y ejecutarlo en el servidor Ubuntu, la terminal arrojó los siguientes datos exactos:

* **El valor del semáforo durante la ejecución:** `1`
* **El valor final de a es:** `200000`

* **Evidencia de compilación y ejecución:**
![Resultado de la ejecución en la terminal](resultado.jpeg)

### ¿Por qué obtuvimos este resultado matemático?
El comportamiento es completamente correcto y demuestra la efectividad de la exclusión mutua:
1. El `hilo1` suma `1` un total de 100,000 veces ($+100000$).
2. El `hilo2` resta `1` un total de 100,000 veces ($-100000$).
3. Al estar protegidos por el semáforo, ambos hilos operan sin pisarse y sus efectos se anulan de forma exacta, dejando el balance parcial en `0`.
4. El valor final de `200000` es el resultado neto del nuevo `hilo3`, que sumó `+2` un total de 100,000 veces de forma segura ($2 \times 100000 = 200000$).

---

## Instrucciones de Compilación y Ejecución

Para correr este ejercicio localmente en la máquina virtual:

```bash
gcc tres_hilos.c -o tres_hilos -lpthread
./tres_hilos
