# Practica 4 - Informatica II

Simulador de red de enrutadores en C++17 usando clases `Red` y `Enrutador`, contenedores STL y el algoritmo de Dijkstra.

## Compilacion

Abrir `Practica_4.pro` en Qt Creator, o ejecutar:

```sh
g++ -std=c++17 -Wall -Wextra -pedantic main.cpp Red.cpp Enrutador.cpp -o practica4
./practica4
```

## Operaciones

Agregar y eliminar enrutadores; conectar, desconectar o actualizar costos de enlaces; consultar vecinos, costos, rutas minimas y tablas de enrutamiento completas. La opcion 12 carga una topologia desde archivo y la opcion 13 genera una red aleatoria conectada de 1 a 50 enrutadores, con costos entre 1 y 20. Estas dos operaciones reemplazan la red existente.

## Archivo de topologia

```text
ROUTER A
ROUTER B
ROUTER C
ROUTER D
ENLACE A B 4
ENLACE A C 10
ENLACE B D 1
ENLACE C D 2
```

Se aceptan lineas vacias y comentarios que empiezan por `#`. Los nombres son cadenas sin espacios, los enlaces no son dirigidos y los costos son enteros no negativos menores que INT_MAX. Ante errores de formato no se cambia la red anterior.

## Pruebas recomendadas

- Consultar A-C en el ejemplo de clase (costo 7).
- Cambiar costos y comprobar que las tablas se recalculan.
- Eliminar enlaces y comprobar destinos inaccesibles.
- Generar redes aleatorias de 1, 2, 10 y 50 nodos.
- Probar archivos invalidos y comprobar que la red anterior se mantiene.
