# Desarrollo innovador Batalla de Pokemon - Detallado

## Sistema de Protección

### ¿Para qué se implementó?
Para agregar una capa estratégica al combate, permitiendo a los Pokémon protegerse de ataques enemigos y reducir el daño recibido.

### ¿Por qué se consideró necesario?
Para hacer el combate más dinámico y realista, similar a los juegos originales de Pokémon donde movimientos como "Protect" son comunes.

### ¿Cómo se llevó a cabo su implementación?
Se añadió un método protect() en la clase Pokemon que activa un estado de protección (protectedThisTurn). Durante el cálculo de daño, si el defensor está protegido, el daño se reduce a la mitad.

## Efectos de Estado (Burned, Paralyzed, Poisoned)

### ¿Para qué se implementó?
Para simular condiciones de estado que afectan a los Pokémon durante el combate, como quemaduras, parálisis o envenenamiento.

### ¿Por qué se consideró necesario?
Para enriquecer la experiencia de combate y agregar variedad táctica, ya que estos efectos pueden alterar el resultado de la batalla.

### ¿Cómo se llevó a cabo su implementación?
Se definió un enumerador Status y se añadieron métodos como applyStatus() y applyStatusEffects() para gestionar los efectos. Los movimientos tienen una probabilidad de infligir estos estados.

## Sistema de Tipos y Efectividad

### ¿Para qué se implementó?
Para replicar las ventajas y desventajas entre tipos de Pokémon (por ejemplo, agua vs. fuego).

### ¿Por qué se consideró necesario?
Porque es un pilar fundamental de la franquicia Pokémon, donde la estrategia depende de los tipos de los Pokémon y sus movimientos.

### ¿Cómo se llevó a cabo su implementación?
Se usó un mapa (typeMatchup) que almacena las efectividades entre tipos. Durante el cálculo de daño, se consulta este mapa para ajustar el daño según las reglas del juego.

## Interfaz Visual Mejorada con Emojis

### ¿Para qué se implementó?
Para hacer la interfaz más atractiva y fácil de entender, utilizando emojis que representan tipos, estados y acciones.

### ¿Por qué se consideró necesario?
Para mejorar la experiencia de usuario y hacer el juego más visualmente intuitivo.

### ¿Cómo se llevó a cabo su implementación?
Se incluyeron emojis en las cadenas de texto, como 🔥 para fuego o 🛡️ para protección, y se mostraron en los mensajes de la consola.

## Barra de Vida Visual

### ¿Para qué se implementó?
Para mostrar de manera gráfica la salud restante de los Pokémon, facilitando la comprensión del estado del combate.

### ¿Por qué se consideró necesario?
Porque una representación visual es más intuitiva que solo números, especialmente en juegos por turnos.

### ¿Cómo se llevó a cabo su implementación?
En el método displayStatus(), se calcula la proporción de vida restante y se muestra una barra con corazones (♥ para vida llena y ♡ para vacía).

## Movimientos con Efectos Secundarios

### ¿Para qué se implementó?
Para que algunos movimientos tengan efectos adicionales, como quemar o paralizar al oponente.

### ¿Por qué se consideró necesario?
Para agregar profundidad táctica al combate, permitiendo al jugador planificar estrategias basadas en efectos.

### ¿Cómo se llevó a cabo su implementación?
Cada movimiento (Move) tiene propiedades como effect y effectChance. Al usarse, hay una probabilidad de aplicar el efecto al oponente.

## Menú de Selección de Pokémon con Nicknames

### ¿Para qué se implementó?
Para permitir al jugador personalizar su Pokémon con un nombre único y elegir su tipo inicial.

### ¿Por qué se consideró necesario?
Para aumentar la inmersión y la conexión emocional con el Pokémon del jugador.

### ¿Cómo se llevó a cabo su implementación?
En la función selectPlayerPokemon(), el jugador elige un tipo y luego ingresa un sobrenombre, que se asigna al Pokémon creado.
