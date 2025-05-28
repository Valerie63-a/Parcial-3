# Desarrollo innovador Parqueadero - Detallado

## Sistema de Tarifas Diferenciadas

### ¿Para qué se implementó?
Para ofrecer tarifas distintas según el tipo de vehículo (motos, vehículos estándar, discapacitados, eléctricos), lo que refleja una gestión más realista y justa.

### ¿Por qué se consideró necesario?
En un parqueadero real, los vehículos tienen necesidades y costos operativos diferentes. Esto agrega valor al sistema y mejora su utilidad práctica.

### ¿Cómo se llevó a cabo su implementación?
Se definió un diccionario TARIFAS que asocia cada tipo de vehículo con un valor por hora. Durante el cálculo del cobro (registrar_salida), se aplica la tarifa correspondiente al tipo de vehículo registrado.

## Visualización con Emojis

### ¿Para qué se implementó?
Para hacer el mapa del parqueadero más intuitivo y visualmente atractivo, facilitando la identificación de espacios libres, ocupados, vías y tipos de vehículos.

### ¿Por qué se consideró necesario?
Mejora la experiencia de usuario al proporcionar una representación gráfica clara y amigable, especialmente útil en sistemas basados en consola.

### ¿Cómo se llevó a cabo su implementación?
Se utilizó un diccionario EMOJIS que mapea cada elemento del parqueadero (ej. "MOTO": "🛵") a un emoji. En mostrar_mapa(), estos emojis se imprimen según el estado de cada celda.

## Cálculo Automatizado del Tiempo y Cobro

### ¿Para qué se implementó?
Para calcular automáticamente el tiempo de estacionamiento y el valor a pagar al salir, basado en la hora de entrada y salida.

### ¿Por qué se consideró necesario?
Elimina errores manuales y agiliza el proceso de cobro, replicando funcionalidades clave de sistemas reales.

### ¿Cómo se llevó a cabo su implementación?
Se usó el módulo datetime para registrar la hora de entrada (hora_entrada) y compararla con la hora de salida (hora_salida). El valor se calcula multiplicando las horas por la tarifa correspondiente.

## Estadísticas de Ocupación en Tiempo Real

### ¿Para qué se implementó?
Para mostrar métricas clave como espacios libres, ocupados y porcentaje de ocupación, ayudando en la toma de decisiones.

### ¿Por qué se consideró necesario?
Proporciona información valiosa para la gestión eficiente del parqueadero, similar a sistemas profesionales.

### ¿Cómo se llevó a cabo su implementación?
En mostrar_disponibilidad(), se recorren las celdas del mapa para contar espacios libres (celda == 1) y ocupados (isinstance(celda, dict)), calculando luego el porcentaje.

## Personalización con Nombre de Usuario

### ¿Para qué se implementó?
Para crear una experiencia más personalizada al saludar al usuario por su nombre al iniciar el sistema.

### ¿Por qué se consideró necesario?
Mejora la interacción humano-computadora, haciendo el sistema más amigable.

### ¿Cómo se llevó a cabo su implementación?
Se solicitó el nombre del usuario al inicio (input("¡Bienvenido...")) y se usó en mensajes posteriores (ej. print(f"Hola {usuario}...")).
