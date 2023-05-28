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
- Combinando ambas podemos asumir entonces que tenemos la distancia que llevaria a cada vehiculo llegar a un potencial pasajero para comenzar el viaje.

Simplificaciones al problema:
- Asumimos que la oferta y la demanda esta balanceada es decir, hay misma cantidad de pasajeros que de vehiculos.
- Asumimos que los pasajeros se encuentran ordenados de manera creciente segun el instante en el que realizan el pedido.
- Asumimos que ningun pasajero tiene prioridad sobre otro.
- Asumimos que no es necesario lograr una distribucion razonable de viajes a lo largo del día entre los distintos conductores.

### Estrategia FCFS
### Modelo para estrategia de Batching

Realizamos el siguiente modelo:

![[modelo.png | center]]

Nuestro modelo utiliza la idea de resolver matching máximo en grafos bipartitos como un problema de flujo máximo.

Para ello, partimos de un grafo que contiene n nodos, representando a los taxis que forman nuestra particion $V_1$ y otros n nodos representando a los pasajeros que forman nuestra particion $V_2$, sabemos además que $n = \#V_1 = \#V_2$ por como se define el problema en las consignas del trabajo. 

![[paso1.png | center]]

Conectamos cada nodo que representa a un taxi con los n nodos que representan a los pasajeros, representando que en principio podemos asignar cualquier taxi a cualquier pasajero. No conectamos taxis entre sí o pasajeros entre sí, por lo que nos queda un grafo bipartito. 
Una vez obtenido el grafo es importante ver que no solo queremos realizar el matching máximo, si no que también queremos minimizar la distancia que recorren los taxis hasta recoger al pasajero. 

![[paso2.png | center]]

Para resolver esto, transformamos el problema de matching máximo en el grafo bipartito en un problema de flujo máximo y costo mínimo, siendo el costo que buscamos minimizar, la distancia mencionada. Para ello, debemos agregar al grafo que teniamos un nodo Source ($S$) y un nodo Sink ($T$) y asignar tanto capacidades como costos adecuados para representar nuestro problema. 

![[paso3.png | center]]

Conectamos $S$ con todos los taxis, dándole a cada arista capacidad 1, pues queremos que cada taxi se asigne a solo un pasajero, y costo 0, pues aún no se esta asignando ningún pasajero y no hay ninguna distancia que tomar. Luego, en las aristas que conectan a los taxis con los pasajeros, les asignamos capacidad 1, por el mismo motivo que antes y es que no queremos asignarle mas de un pasajero a los taxis (aunque es verdad que al haber elegido capacidad 1 en la conexión de $S$ con los taxis, esto ya estaba limitado y podríamos elegir cualquier capacidad $\geq 1$ ), y el costo será dado por la distancia desde el taxi al pasajero, es decir, la arista que conecta al i-ésimo taxi con el j-ésimo pasajero tendra capacidad 1 y costo $dist_{ij}$. Finalmente, conectamos los pasajeros a $T$, con capacidad 1 por el mismo motivo anterior (aunque otra vez, ya estaba limitado) y costo 0, pues interpretativamente esta conexión representa que el viaje terminó y ya no hay ninguna distancia (costo) a tener en cuenta.

![[paso4.png| center]]

*No se ve representado en las lineas punteadas pues saturaría la visualización pero cada linea punteada se conecta con capacidad 1 y costo $dist_{ij}$, al igual que en las que se ven marcadas.*

El flujo máximo del grafo será $n$, enviando una unidad de flujo por cada arista desde $S$ a los taxis, por lo tanto, cualquier combinación de taxis y pasajeros que "sacie" a todos los pasajeros, es decir, que haya un taxi asignado a cada pasajero nos dará el flujo máximo. Luego, si de estos flujos máximos buscamos el que tenga costo minimo obtendremos la combinación de taxis y pasajeros que sacia a todos los pasajeros y además minimiza la distancia recorrida por los taxis para recoger a los mismos.

De esta manera, resolvemos el problema planteado utilizando grafos de manera inteligente.

### Implementación para estrategia de Batching
### Experimentación
### Discusión y análisis de resultados
### Limitaciones y posibles extensiones
### Modelo Alternativo


