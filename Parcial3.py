import datetime
import time

class Parqueadero:
    TARIFAS = {
        "MOTO": 50,
        "VEHICULO": 100,
        "DISCAPACITADO": 45,
        "ELECTRICO": 110
    }
    SIMBOLOS = {
        "MOTO": "M",
        "VEHICULO": "C",
        "DISCAPACITADO": "D",
        "ELECTRICO": "E"
    }

    def __init__(self, filas=8, columnas=8):
        self.filas = filas
        self.columnas = columnas
        self.mapa = [[0 for _ in range(columnas)] for _ in range(filas)]
        self.vehiculos = {}
        self.inicializar_mapa()
        
    def inicializar_mapa(self):
        for i in range(self.filas):
            for j in range(self.columnas):
                if j == 0 or j == self.columnas-1 or i == 0 or i == self.filas-1:
                    self.mapa[i][j] = 2 
                elif j % 2 == 0 and i > 1 and i < self.filas-2:
                    self.mapa[i][j] = 2 
                elif i % 2 == 1 and j > 0 and j < self.columnas-1 and self.mapa[i][j] != 2:
                    self.mapa[i][j] = 1  
        self.entrada = (self.filas//2, 0)
        self.salida = (self.filas//2, self.columnas-1)
        self.mapa[self.entrada[0]][self.entrada[1]] = 4
        self.mapa[self.salida[0]][self.salida[1]] = 5

    def mostrar_mapa(self):
        print("\nMapa del Parqueadero:")
        print("Leyenda:")
        print("E = Entrada | S = Salida | V = Vía | _ = Libre | M = Moto | C = Carro | D = Discapacitado | E = Eléctrico")
        print("-" * (self.columnas * 3 + 1))
        for i, fila in enumerate(self.mapa):
            print("|", end="")
            for j, celda in enumerate(fila):
                if celda == 0:
                    print("   ", end="|")
                elif celda == 1:
                    print(" _ ", end="|")  
                elif celda == 2:
                    print(" V ", end="|")  
                elif celda == 4:
                    print(" E ", end="|")  
                elif celda == 5:
                    print(" S ", end="|") 
                elif isinstance(celda, dict):
                    tipo = celda.get("tipo", "VEHICULO")
                    print(f" {self.SIMBOLOS.get(tipo, 'C')} ", end="|")
                else:
                    print(" ? ", end="|")
            print("\n" + "-" * (self.columnas * 3 + 1))

    def encontrar_espacio_libre(self):
        for i in range(self.filas):
            for j in range(self.columnas):
                if self.mapa[i][j] == 1:  
                    return (i, j)
        return None

    def registrar_entrada(self, placa, tipo):
        tipo = tipo.upper()
        if tipo not in self.TARIFAS:
            print("\nTipo de vehículo no válido.")
            return False
        espacio = self.encontrar_espacio_libre()
        if espacio:
            self.mapa[espacio[0]][espacio[1]] = {"tipo": tipo, "placa": placa}
            hora_entrada = datetime.datetime.now()
            self.vehiculos[placa] = {
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

    def registrar_salida(self, placa):
        if placa in self.vehiculos:
            vehiculo = self.vehiculos[placa]
            hora_salida = datetime.datetime.now()
            tiempo_estacionado = hora_salida - vehiculo['hora_entrada']
            horas = tiempo_estacionado.total_seconds() / 3600
            tipo = vehiculo['tipo']
            tarifa = self.TARIFAS.get(tipo, 100)
            valor_a_pagar = round(horas * tarifa)
            espacio = vehiculo['espacio']
            self.mapa[espacio[0]][espacio[1]] = 1 
            vehiculo['hora_salida'] = hora_salida
            vehiculo['valor_pagado'] = valor_a_pagar
            print(f"\nVehículo {placa} ({tipo}) salió del espacio {espacio}")
            print(f"Tiempo estacionado: {str(tiempo_estacionado).split('.')[0]}")
            print(f"Valor a pagar: ${valor_a_pagar} (Tarifa: {tarifa}/h)")
            return valor_a_pagar
        else:
            print(f"\nVehículo {placa} no encontrado en el parqueadero")
            return None

    def mostrar_disponibilidad(self):
        libres = 0
        ocupados = 0
        for fila in self.mapa:
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
            print(f"Porcentaje de ocupación: {(ocupados/total)*100:.1f}%")
        else:
            print("No hay espacios configurados.")

def mostrar_menu():
    print("\n--- Sistema de Gestión de Parqueadero ---")
    print("1. Mostrar mapa del parqueadero")
    print("2. Registrar entrada de vehículo")
    print("3. Registrar salida de vehículo")
    print("4. Mostrar disponibilidad")
    print("5. Salir")
    print("Tarifas: Moto $50/h | Vehículo $100/h | Discapacitado $45/h | Eléctrico $110/h")
    try:
        return int(input("Selecciona una opción: "))
    except:
        return 0

if __name__ == "__main__":
    usuario = input("¡Bienvenido a michicaar! por favor ingresa tu nombre: ")
    print(f"\nHola {usuario}, bienvenido al sistema de gestión de parqueadero.")
    parqueadero = Parqueadero(9, 9) 
    while True:
        opcion = mostrar_menu()
        if opcion == 1:
            parqueadero.mostrar_mapa()
        elif opcion == 2:
            placa = input("Ingresa la placa del vehículo: ")
            print("Tipos: Moto, Vehiculo, Discapacitado, Electrico")
            tipo = input("Ingresa el tipo de vehículo: ")
            parqueadero.registrar_entrada(placa, tipo)
        elif opcion == 3:
            placa = input("Ingresa la placa del vehículo: ")
            parqueadero.registrar_salida(placa)
        elif opcion == 4:
            parqueadero.mostrar_disponibilidad()
        elif opcion == 5:
            print(f"\nGracias por usar el sistema de michicaar, {usuario}!!! ¡Hasta luego!")
            break
        else:
            print("\nOpción no válida. Intenta nuevamente.")
        input("\nPresiona Enter para continuar...")