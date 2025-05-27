# Parcial-3

## Natali Miranda Acosta
## Valerie Gutiérrez Zambrano

# DESARROLLO innovador parqueadero 

## ¿Qué se implementó?

 Se añadieron categorías de vehículos como: Moto, Vehiculo, Discapacitado y Eléctrico, también se le implementaron tarifas y saludo al usuario junto con símbolos visuales
## ¿Para qué se implementó?

 Se implementaron para gestionar de manera más eficiente el parqueadero, los organizamos registrando entradas y salidas de vehiculos, calcular las tarifas según el tipo de vehiculo, podemos visualizar la disponibilidad de espacios en tiempo real y podemos diferenciar entre categorias de vehiculos. A parte de esto podemos digitalizar el control manual, optimizar el uso de espacios y generar datos de facturación.
## ¿Por qué se consideró necesario?

 Se consideró necesario porque evita desorde en la asignación manual de espacios, las tarifas diferenciadas son equitativas, se mejora la experiencia del usuario  haciendo el interfaz intuitivo con emojis y menús, es óptimo en cálculos manuales de tarifas, etc...
 
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
