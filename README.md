# Parcial-3

## Natali Miranda Acosta
## Valerie Gutiérrez Zambrano

# DESARROLLO innovador parqueadero 

## ¿Qué se implementó?

 Se añadieron categorías de vehículos como: Moto, Vehiculo, Discapacitado y Eléctrico, también se le implementaron tarifas y saludo al usuario junto con símbolos visuales
## ¿Para qué se implementó?

 Se implementaron para gestionar de manera más eficiente el parqueadero, los organizamos registrando entradas y salidas de vehiculos, calcular las tarifas según el tipo de vehiculo, podemos visualizar la disponibilidad de espacios en tiempo real y podemos diferenciar entre categorias de vehiculos. A parte de esto podemos digitalizar el control manual, optimizar el uso de espacios y generar datos de facturación.
## ¿Por qué se consideró necesario?

 Se consideró necesario porque evita desorden en la asignación manual de espacios, las tarifas diferenciadas son equitativas, se mejora la experiencia del usuario  haciendo el interfaz intuitivo con emojis y menús, es óptimo en cálculos manuales de tarifas, etc...
 
## ¿Cómo se llevó a cabo su implementación?

Componentes clave:
TARIFAS = {"MOTO": 50, ...}   Diccionario de precios
EMOJIS = {"MOTO": "🛵", ...}  Visualización amigable
mapa = []   Matriz que representa espacios
vehiculos = {}  Diccionario para registro de vehículos

Implementamos un módulo para calcular el tiempo y los precios (import datetime) y el uso de emojis para mejor identificación de áreas.

1. Configura el parqueadero al inicio.
2. Registra entradas y salidas de vehículos.
3. Visualiza el estado actual del parqueadero.


# DESARROLLO innovador Pokemon

## ¿Qué se implementó?

 1. Sistema de protección
 2. Efectos de estado en los Pokemon
 3. Sistema de tipos
 4. Interfaz visual más animada
 5. Seleccion de Pokemon y sobrenombre

## ¿Para qué se implementó?

 Los cambios agregados al codigo se implementaron para hacer el juego mas entretenido para el usuario, agregando la necesidad de tener una estrategia para la batalla donde se deba tener en cuenta la diferencia de ventaja de los tipos de pokemon y los efectos de estado que puedan aplicar durante la batalla, asi mismo una interfaz más entretenida y amigable con el usuario brinda una mejor experiencia mientras replica algunas funciones del juego original.

 ## ¿Por qué se consideró necesario?

  Se considero necesario debido a que el codigo responde a una necesidad de entretenimiento, y debido a esto decidimos priorizar la inmersion del usuario en el juego, añadiendo profundidad a la batalla, una interfaz mas atractiva y una necesidad de estrategia al usar el programa.

## ¿Cómo se llevó a cabo su implementación?

 Utlizando clases, mapas, metodos y funciones conocidas como

 1. Mecánicas de combate:
    - Protección: Método *protect()* en la clase *Pokemon* y ajuste de daño en *calculateDamage()*.
    - Efectos de estado: Enumerador *Status*, métodos *applyStatus()* y *applyStatusEffects()*.
    - Tipos y efectividad: Mapa *typeMatchup* y consulta durante el cálculo de daño.
 2. Interfaz y personalización:
    - Emojis: Strings con símbolos.
    - Barra de vida: Cálculo proporcional en *displayStatus()* usando ♥/♡.
    - Sobrenombre: Función *selectPlayerPokemon()* que permite asignarle un nombre al Pokemon.
 3. Movimientos especiales:
    - Clase *Move* con propiedades *effect* y *effectChance*, aplicadas al atacar.
