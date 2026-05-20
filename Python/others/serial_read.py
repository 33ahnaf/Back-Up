import serial.tools.list_ports
ports = serial.tools.list_ports.comports()
serialInst = serial.Serial()
portsList = []
for one in ports:
    portsList.append(str(one))
    print(str(one))
com = input("Select a COM port for Arduino: ")
for i in range(len(portsList)):
    if portsList[i].startswith("COM" + str(com)):
        selected_port = "COM" + str(com)
serialInst.baudrate = 9600; # Set baudrate here.
serialInst.port = selected_port
serialInst.open()
while True:
    output = serialInst.read("utf-8")
    real_output = str(output)
    print(real_output)