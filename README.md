## TDV: Diseño de Algoritmos | TP1: taxi batching
### Federico Giorgi, Gaston Loza Montaña & Tomás Curzio.

### Contexto

En los últimos tiempos, el surgimiento masivo de plataformas colaborativas que conectan demanda con oferta ha transformado la manera en que interactuamos con diversos servicios, incluyendo el transporte. En este contexto, las aplicaciones colaborativas de movilidad privada, como Uber, Cabify, Didi, entre otras, han logrado un gran éxito al actuar como intermediarias entre pasajeros y conductores, brindando una experiencia más cómoda y eficiente.

El objetivo de este trabajo es analizar un aspecto fundamental del funcionamiento de estas plataformas: la asignación en tiempo real entre pasajeros y conductores. Con el crecimiento sostenido de usuarios de estas empresas, se ha ido complejizando el desafío de lograr emparejamientos efectivos ante requerimientos de experiencia del usuario cada vez más exigentes. A través de este análisis, buscamos ofrecer recomendaciones que permitan optimizar el sistema de emparejamiento y brindar una experiencia aún más satisfactoria tanto para los pasajeros como para los conductores de la plataforma.

### El problema (y la decisión a tomar)

El trabajo nos pone en el rol de consultores para una empresa que se dedica a dar servicios de movilidad, conectando a pasajeros con conductores. La empresa, dado un instante o intervalo pequeño de tiempo, en cierta área geográfica, tiene una cierta cantidad de pasajeros pidiendo un viaje, y otra cantidad de conductores disponibles. Nuestro objetivo es decidir, de manera inteligente, qué vehículo debe buscar a cada pasajero.

Para especificar mejor el problema, debemos tener en cuenta los datos que la empresa posee a su disposición previamente, y las simplificaciones que le realizamos al mismo.

Datos:

-   Para cada pasajero podemos asumir que tenemos:

    -   El instante en el que realizó el pedido.

    -   El origen del viaje (donde se realiza el *pick-up*).

    -   El destino del viaje o la distancia estimada del recorrido.

    -   La estimación de la tarifa a cobrar por el viaje.

-   Por cada conductor disponible para realizar un viaje podemos asumir que tenemos su localización en tiempo real.

Luego, combinando ambas podemos asumir entonces que tenemos la distancia que llevaría a cada vehículo llegar a un potencial pasajero para comenzar el viaje.

Simplificaciones al problema:

-   Asumimos que la oferta y la demanda esta balanceada, es decir que hay misma cantidad de pasajeros que de conductores.

-   Asumimos que los pasajeros se encuentran ordenados de manera creciente según el instante en el que realizan el pedido.

-   Asumimos que ningun pasajero tiene prioridad sobre otro.

-   Asumimos que no es necesario lograr una distribución razonable de viajes a lo largo del día entre los distintos conductores.