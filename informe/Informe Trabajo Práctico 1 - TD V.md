## Federico Giorgi, Gastón Loza Montaña y Tomás Curzio.

### Contexto - El problema y la decisión a tomar:

El trabajo nos pone en el rol de consultores para una empresa que se dedica a dar servicios de movilidad, conectando a pasajeros con conductores, como puede ser Uber, Cabify, etc. 

La empresa, dado un instante o intervalo pequeño de tiempo, en cierta área geográfica, tiene una cierta cantidad de pasajeros pidiendo un viaje, y otra cantidad de conductores disponibles, nuestro objetivo es decidir, de manera inteligente, que vehículo debe buscar a que pasajero.

Para especificar mejor el problema, debemos tener en cuenta los datos que asumimos que la empresa posee, y las simplificaciones que le realizamos al mismo.

Datos:
- Para cada pasajero podemos asumir que tenemos:
	- El instante en el que realizo el pedido.
	- Origen del viaje (donde se realiza el *pick-up*).
	- Destino del viaje o la distancia estimada del recorrido.
	- Estimación de la tarifa a cobrar por el viaje.
- Para cada conductor disponible para realizar un viaje podemos asumir que tenemos su localizacion en tiempo real.
- Combinando ambas podemos asumir entonces que tenemos la distancia que llevaria a cada vehículo llegar a un potencial pasajero para comenzar el viaje.

Simplificaciones al problema:
- Asumimos que la oferta y la demanda esta balanceada es decir, hay misma cantidad de pasajeros que de vehículos.
- Asumimos que los pasajeros se encuentran ordenados de manera creciente segun el instante en el que realizan el pedido.
- Asumimos que ningun pasajero tiene prioridad sobre otro.
- Asumimos que no es necesario lograr una distribucion razonable de viajes a lo largo del día entre los distintos conductores.

### Estrategia FCFS

El problema puede ser resuelto desde distintos enfoques. El que actualmente utiliza la empresa que nos contrata es una idea muy natural que se basa en atender a los pasajeros por orden de llegada y para cada uno de ellos tomar la mejor decisión posible en el momento.

En otras palabras, utiliza el criterio de “First Come, First Served” y toma una decisión greedy para asignar el vehículo más cercano al pasajero que está siendo atendido en el momento (la mejor decisión local, que puede ser distinta a la mejor decisión global). 

Podemos dividir esta estrategia en los siguientes pasos:
1. Considerar a los pasajeros por orden de llegada.
2. Asignar al pasajero que llegó primero el vehículo más cercano.
3. Remover este vehículo de los posibles a asignar (para que no haya un vehículo asignado a dos pasajeros) y remover al pasajero de la lista.
4. Repetir hasta que no haya más pasajeros.

### Implementación para estrategia FCFS

Como parte del trabajo como consultores para la plataforma de intermediación de movilidad nos proponemos en primer lugar analizar la estrategia actual de la empresa para poder contar con resultados de rendimiento con los cuáles comparar las nuevas propuestas a la resolución del problema.

Para ello, siguiendo la idea de la estrategia explicada, realizamos una implementación de la misma en C++ que toma los datos de la distancia entre vehículos y pasajeros (en orden de llegada) en forma de una matriz y la recorre para asignarle a cada pasajero el vehículo disponible más cercano a su posición (*ver GreedySolver.cpp*).

Esta estrategia e implementación es totalmente válida. Sin embargo, si hay una cantidad de demanda significativa, es posible tomar otro enfoque, en el que en lugar de ir atendiendo por orden de llegada en tiempo real, se espera cierta cantidad de tiempo (algunos segundos) y se agrupa a los pasajeros que hayan pedido un viaje en ese lapso de tiempo, para luego tomar una decisión de asignación de vehículos sabiendo las localizaciones de todos. A esto se lo llama estrategia de "batching."

### Estrategia de Batching

Llamamos a ese grupo de clientes que pide el viaje en el lapso de tiempo en el que estamos esperando "batch", de ahí el nombre batching.

Nuestro objetivo es de alguna manera realizar una asignación de vehículos a pasajeros de forma tal que la suma de las distancias recorridas de los vehículos para recoger a los pasajeros sea mínima.

Notar que es posible que en algun momento elijamos un vehículo que no es el mas cercano a un pasajero, porque al final termina siendo mejor para minimizar la suma de distancias, por lo que esta estrategia es totalmente distinta a la estrategia *greedy* vista anteriormente.

Para realizar esta asignación vamos a modelar el problema con grafos.

### Modelo para estrategia de Batching

Nuestro modelo utiliza la idea de resolver matching máximo en grafos bipartitos como un problema de flujo máximo.

Para construirlo, partimos de un grafo que contiene n nodos, representando a los taxis que forman nuestra particion $V_1$ y otros n nodos representando a los pasajeros que forman nuestra particion $V_2$, sabemos además que $n = \#V_1 = \#V_2$ por como se define el problema en las consignas del trabajo. 

![[paso1.png | center]]

Posteriormente, conectamos cada nodo que representa a un taxi con los n nodos que representan a los pasajeros, representando que en principio podemos asignar cualquier taxi a cualquier pasajero. No conectamos taxis entre sí o pasajeros entre sí, por lo que nos queda un grafo bipartito. 
Una vez obtenido el grafo es importante ver que no solo queremos realizar el matching máximo, si no que también queremos minimizar la distancia que recorren los taxis hasta recoger al pasajero. 

![[paso2.png | center]]

Para resolver esto, transformamos el problema de matching máximo en el grafo bipartito en un problema de flujo máximo y costo mínimo, siendo el costo que buscamos minimizar, la distancia mencionada. Para ello, debemos agregar al grafo que teniamos un nodo Source ($S$) y un nodo Sink ($T$) y asignar tanto capacidades como costos adecuados para representar nuestro problema. 

![[paso3.png | center]]

Una vez agregados, conectamos $S$ con todos los taxis, dándole a cada arista capacidad 1, pues queremos que cada taxi se asigne a solo un pasajero, y costo 0, pues aún no se esta asignando ningún pasajero y no hay ninguna distancia que tomar. Luego, en las aristas que conectan a los taxis con los pasajeros, les asignamos capacidad 1, por el mismo motivo que antes y es que no queremos asignarle mas de un pasajero a los taxis (aunque es verdad que al haber elegido capacidad 1 en la conexión de $S$ con los taxis, esto ya estaba limitado y podríamos elegir cualquier capacidad $\geq 1$ ), y el costo será dado por la distancia desde el taxi al pasajero, es decir, la arista que conecta al i-ésimo taxi con el j-ésimo pasajero tendra capacidad 1 y costo $dist_{ij}$. Finalmente, conectamos los pasajeros a $T$, con capacidad 1 por el mismo motivo anterior (aunque otra vez, ya estaba limitado) y costo 0, pues interpretativamente esta conexión representa que el viaje terminó y ya no hay ninguna distancia (costo) a tener en cuenta.

![[paso4.png| center]]

*No se ve representado en las lineas punteadas pues saturaría la visualización pero cada linea punteada se conecta con capacidad 1 y costo $dist_{ij}$, al igual que en las que se ven marcadas.*

El flujo máximo del grafo será $n$, enviando una unidad de flujo por cada arista desde $S$ a los taxis, por lo tanto, cualquier combinación de taxis y pasajeros que "sacie" a todos los pasajeros, es decir, que haya un taxi asignado a cada pasajero nos dará el flujo máximo. Luego, si de estos flujos máximos buscamos el que tenga costo minimo obtendremos la combinación de taxis y pasajeros que sacia a todos los pasajeros y además minimiza la distancia recorrida por los taxis para recoger a los mismos. 

Así, terminamos de construir nuestro modelo que queda de la siguiente manera:

![[modelo.png | center]]

De esta manera, resolvemos el problema planteado en la estrategia de batching utilizando grafos de manera inteligente.

### Implementación para estrategia de Batching

Utilizando el modelo explicado, realizamos una implementación de esta estrategia utilizando la librería "or-tools", que nos provee una manera de resolver el problema de flujo máximo con costo mínimo dadas las siguientes cosas:
- Un vector "start_nodes" y otro "end_nodes" donde el i-ésimo valor de start_nodes está conectado con el i-ésimo valor de end_nodes (con estos dos vectores se representan los arcos del grafo).
- Un vector "capacities" con la capacidad de cada arco.
- Un vector "cost_units" con el costo de cada arco.
- Un vector "supplies" con los desbalances de cada nodo.

Con esto, el problema de implementar nuestro modelo y calcular el flujo maximo con costo minimo se reduce a simplemente representar nuestro grafo con esos 5 vectores.

¿Cómo hacemos esto para una instancia cualquiera?

### Experimentación
### Discusión y análisis de resultados
### Limitaciones y posibles extensiones
### Modelo Alternativo