import socket

# Dirección del socket Unix del servidor
socket_file = "/tmp/lineSensor.s"

try:
    client = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
    
    # Conectar al servidor
    client.connect(socket_file)
    
    # Enviar datos al servidor (si es necesario)
    # client.send(b"Hello, server!")

    # Recibir datos del servidor
    data = client.recv(1024)
    print("Datos recibidos del servidor:", data.decode("utf-8"))

except ConnectionError as e:
    print("Error de conexión:", e)

finally:
    # Cerrar la conexión
    client.close()
