import datetime

TARIFAS = {
    "MOTO": 50,
    "VEHICULO": 100,
    "DISCAPACITADO": 45,
    "ELECTRICO": 110
}

EMOJIS = {
    "MOTO": "🛵",
    "VEHICULO": "🚗",
    "DISCAPACITADO": "♿",
    "ELECTRICO": "🔌",
    "VIA": "⬛",
    "LIBRE": "⬜",
    "ENTRADA": "🚪",
    "SALIDA": "🚪"
}

filas = 9
columnas = 9
mapa = []
vehiculos = {}
entrada = (filas // 2, 0)
salida = (filas // 2, columnas - 1)

def inicializar_mapa():
    global mapa, entrada, salida
    mapa = [[0 for _ in range(columnas)] for _ in range(filas)]
    for i in range(filas):
        for j in range(columnas):
            if j == 0 or j == columnas - 1 or i == 0 or i == filas - 1:
                mapa[i][j] = 2
            elif j % 2 == 0 and 1 < i < filas - 2:
                mapa[i][j] = 2
            elif i % 2 == 1 and 0 < j < columnas - 1 and mapa[i][j] != 2:
                mapa[i][j] = 1
    mapa[entrada[0]][entrada[1]] = 4
    mapa[salida[0]][salida[1]] = 5

def mostrar_mapa():
    print("\nMapa del Parqueadero:")
    print("Leyenda:")
    print(f"{EMOJIS['ENTRADA']} = Entrada  {EMOJIS['SALIDA']} = Salida  {EMOJIS['VIA']} = Vía")
    print(f"{EMOJIS['LIBRE']} = Libre  {EMOJIS['MOTO']} = Moto  {EMOJIS['VEHICULO']} = Carro")
    print(f"{EMOJIS['DISCAPACITADO']} = Discapacitado  {EMOJIS['ELECTRICO']} = Eléctrico")
    print("-" * (columnas * 3 + 1))
    for fila in mapa:
        print("", end="")
        for celda in fila:
            if celda == 0:
                print("   ", end=" ")
            elif celda == 1:
                print(f" {EMOJIS['LIBRE']} ", end=" ")
            elif celda == 2:
                print(f" {EMOJIS['VIA']} ", end=" ")
            elif celda == 4:
                print(f" {EMOJIS['ENTRADA']} ", end=" ")
            elif celda == 5:
                print(f" {EMOJIS['SALIDA']} ", end=" ")
            elif isinstance(celda, dict):
                tipo = celda.get("tipo", "VEHICULO")
                print(f" {EMOJIS.get(tipo, EMOJIS['VEHICULO'])} ", end=" ")
            else:
                print(" ? ", end=" ")
        print("\n" + "-" * (columnas * 3 + 1))

def encontrar_espacio_libre():
    for i in range(filas):
        for j in range(columnas):
            if mapa[i][j] == 1:
                return (i, j)
    return None

def registrar_entrada(placa, tipo):
    global mapa, vehiculos
    tipo = tipo.upper()
    if tipo not in TARIFAS:
        print("\nTipo de vehículo no válido.")
        return False
    espacio = encontrar_espacio_libre()
    if espacio:
        mapa[espacio[0]][espacio[1]] = {"tipo": tipo, "placa": placa}
        hora_entrada = datetime.datetime.now()
        vehiculos[placa] = {
            'espacio': espacio,
            'hora_entrada': hora_entrada,
            'hora_salida': None,
            'valor_pagado': None,
            'tipo': tipo
        }
        print(f"\nVehículo {placa} ({tipo}) registrado en espacio {espacio} a las {hora_entrada}")
        return True
    else:
        print("\nNo hay espacios disponibles")
        return False

def registrar_salida(placa):
    global mapa, vehiculos
    if placa in vehiculos:
        vehiculo = vehiculos[placa]
        hora_salida = datetime.datetime.now()
        tiempo_estacionado = hora_salida - vehiculo['hora_entrada']
        horas = tiempo_estacionado.total_seconds() / 3600
        tarifa = TARIFAS.get(vehiculo['tipo'], 100)
        valor_a_pagar = round(horas * tarifa)
        espacio = vehiculo['espacio']
        mapa[espacio[0]][espacio[1]] = 1
        vehiculo['hora_salida'] = hora_salida
        vehiculo['valor_pagado'] = valor_a_pagar
        print(f"\nVehículo {placa} ({vehiculo['tipo']}) salió del espacio {espacio}")
        print(f"Tiempo estacionado: {str(tiempo_estacionado).split('.')[0]}")
        print(f"Valor a pagar: ${valor_a_pagar} (Tarifa: {tarifa}/h)")
        return valor_a_pagar
    else:
        print(f"\nVehículo {placa} no encontrado en el parqueadero")
        return None

def mostrar_disponibilidad():
    libres = 0
    ocupados = 0
    for fila in mapa:
        for celda in fila:
            if celda == 1:
                libres += 1
            elif isinstance(celda, dict):
                ocupados += 1
    total = libres + ocupados
    print(f"\nEspacios libres: {libres}")
    print(f"Espacios ocupados: {ocupados}")
    print(f"Total espacios: {total}")
    if total > 0:
        print(f"Porcentaje de ocupación: {(ocupados / total) * 100:.1f}%")
    else:
        print("No hay espacios configurados.")

def mostrar_menu():
    print("\n Sistema de Gestión de Parqueadero - michicaar")
    print("Selecciona una opción, por favor:")
    print("1. Mostrar mapa del parqueadero")
    print("2. Registrar entrada de vehículo")
    print("3. Registrar salida de vehículo")
    print("4. Mostrar disponibilidad")
    print("5. Salir")
    print(f"Tarifas: Moto ${TARIFAS['MOTO']}/h | Vehículo ${TARIFAS['VEHICULO']}/h | Discapacitado ${TARIFAS['DISCAPACITADO']}/h | Eléctrico ${TARIFAS['ELECTRICO']}/h")
    try:
        return int(input("Selecciona una opción: "))
    except ValueError:
        return 0
    
if __name__ == "__main__":
    usuario = input("¡Bienvenido a michicaar! Por favor ingresa tu nombre: ")
    print(f"\nHola {usuario}, bienvenido al sistema de gestión de parqueadero.")
    inicializar_mapa()
    while True:
        opcion = mostrar_menu()
        if opcion == 1:
            mostrar_mapa()
        elif opcion == 2:
            placa = input("Ingresa la placa del vehículo: ")
            print("Tipos: Moto, Vehiculo, Discapacitado, Electrico")
            tipo = input("Ingresa el tipo de vehículo: ")
            registrar_entrada(placa, tipo)
        elif opcion == 3:
            placa = input("Ingresa la placa del vehículo: ")
            registrar_salida(placa)
        elif opcion == 4:
            mostrar_disponibilidad()
        elif opcion == 5:
            print(f"\nGracias por usar el sistema de michicaar, {usuario}. ¡Hasta luego!")
            break
        else:
            print("\nOpción no válida. Intenta nuevamente.")
        input("\nPresiona Enter para continuar...")
