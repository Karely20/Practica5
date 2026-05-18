# Ejercicio 3.1 - Concurrencia de Hilos sin Sincronización

Este módulo contiene la implementación del primer escenario de la práctica, diseñado para analizar el comportamiento de dos hilos concurrentes que acceden y modifican una variable global compartida (`int a`) en ausencia de mecanismos de exclusión mutua.

## Metodología de Pruebas (Modificación de MAX)

Con el fin de observar cómo afecta el volumen de iteraciones a la ejecución, la variable `MAX` fue modificada y evaluada en 5 escalas distintas durante las pruebas de laboratorio:

1. `MAX = 1000`
2. `MAX = 10000`
3. `MAX = 100000`
4. `MAX = 1000000` 

Tras compilar y ejecutar el programa de forma repetida para cada uno de estos cinco valores, el resultado impreso de la variable compartida fue siempre:
`El valor de a es 0`

---

## Análisis de Resultados: ¿Por qué el resultado siempre es cero?

El hecho de que el valor final retorne a `0` de forma constante en todas las escalas de prueba se debe a la velocidad del hardware y a la planificación del sistema operativo:

* **Simplicidad de las instrucciones:** Las operaciones de incremento (`a += 1`) y decremento (`a -= 1`) consumen recursos mínimos del procesador, resolviéndose en microsegundos.
* **Ejecución secuencial por ráfagas:** Debido a la alta velocidad del procesador de la máquina anfitriona, el tiempo de CPU asignado a cada hilo es suficiente para que el primer hilo inicie y complete todas sus iteraciones de golpe. 
* **Ausencia de intercalación:** Al no existir una mezcla de instrucciones a mitad del ciclo, los hilos terminan ejecutándose uno detrás del otro de manera limpia. El primer hilo termina de sumar el valor total de `MAX` y, posteriormente, el segundo hilo resta exactamente la misma cantidad. Al operar de forma consecutiva, los efectos aritméticos se anulan de manera exacta ($+MAX - MAX = 0$), manteniendo el balance final en cero.

---

## Instrucciones de Compilación y Ejecución

Para correr este ejercicio en Ubuntu Server:

```bash
gcc sin_semaforos.c -o sin_semaforos -lpthread
./sin_semaforos

