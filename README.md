# EVA y RAMSES Sensórica-Robocol
Este paquete ofrece los códigos de Arduino y Python para mover el Eva y Ramses utilizando una raspberry y 2 arduinos mediante ROS. 

**Tabla de Contenidos**

- [EVA y RAMSES Sensórica-Robocol](https://github.com/Sensorica-Robocol/Codigos-Arduino-EVA "EVA y RAMSES Sensórica-Robocol")
- [Instalación ROS en Raspberry](#instalacion-ros-en-raspberry)
- [Instrucciones Conexión](#instrucciones-conexión)
- [Usage](#usage)
- [Instrucciones para correr nodo de Sensores de Arduino](https://github.com/Sensorica-Robocol/Codigos-Arduino-EVA "#Instrucciones para correr nodo de Sensores de Arduino")
  
# Instalación ROS en Raspberry

Instrucciones para instalación de ROS MELODIC en una Raspberry Pi Zero /W:

// Este archivo explica el proceso para la instalación de ROS Melodic en una Raspberry Pi Zero /W
El método usado realiza una compilación directa de ROS desde la fuente en la raspberry, por lo que es un proceso bastante demorado
NOTA1: no desconectar ni apagar la raspberry durante el proceso de instalación 
NOTA1: para apagar la rapsberry SIEMPRE usar el comando: 
```bash
  sudo shutdown -h now//
  ```


Paso 0. Instalación del sistema operativo en la raspberry:
- Primero se debe instalar el sistema operativo en la raspberry: Para esto descargue el generador ISO de la página oficial de raspberry (xxxxx)
- Una vez descargado el programa, ejecutarlo, introducir la microSD, y en el programa seleccionar la memoria y el sistema operativo recomendado (RaspberrypiOS)
- Después de generada la imagen ISO con el programa, expulse la memoria y vuelva a conectarla, agregue los archivos de configuración para conectarse a la red de internet que corresponda y la comunicarse por ssh (https://youtu.be/I1CgRUPZ-9s - tutorial Franz)


Paso 1. Acceder reomotamente a la raspbery mediante Putty por ssh:
- Descargue Putty de la página oficial (xxxx) y abra el programa
- Inserte la microSD en la raspberry, conectela a la energía y espere unos segundos hasta que esté lista para funcionar
- Revise que la raspberry esté conectada a la red y tenga en cuenta su dirección IP (se va a necesitar después)
- En Putty, introduzca la IP de la raspberry, seleccione ssh y presione "Open"
- Una vez conectado por ssh a la consola de la raspberry, le pedirá usuario y contraseña, por defecto, el usuario es 'pi' y la constraseña es '326435'
- Con esto ya tiene acceso a la raspberry y puede manejarla desde consola


Paso 2. Acceder remotamente a la raspberry mediante el VNC viewer:
Trabajar con una interfaz gráfica es mucho más sencillo en ocasiones, por eso manejamos el VNC
- Instalar VNC Viewer (de www.realvnc.com)
- En la consola de la raspberry por Putty corres el comando: 

```bash
   raspi config
   ```
 
  y habilitar todos los periféricos necesarios junto con el servidor VNC y cámara, luego reiniciar si no se solicita al terminar la habilitación (preguntar a Jhoan para esta configuración $ sudo reboot) 
- Una vez instalado VNC Viewer se procede a conectarse con la raspberry ingresando la IP correspondiente
- Si todo está correcto, se le pedirá de nuevo usuario y contraseña y ya podrá ingresar al entorno gráfico de la raspberry


Paso 3. Instalación de ROS Melodic:
Utilizando la terminal de la raspberry, introducir los siguientes comandos uno a uno:  
```bash
sudo apt update
   ```
   ```bash
sudo apt install -y python-rosdep python-rosinstall-generator python-wstool python-rosinstall build-essential git curl
   ```
   ```bash
sudo rosdep init
   ```
 ```bash
rosdep update
   ```
   ```bash
sudo mkdir -p /usr/src/ros/melodic
   ```
```bash
sudo chown -R $USER:$USER /usr/src/ros
   ```
 ```bash
cd /usr/src/ros/melodic
   ```
 ```bash
rosinstall_generator robot --rosdistro melodic --deps --tar > melodic-robot.rosinstall
   ```
 ```bash
wstool init -j1 src melodic-robot.rosinstall
   ```
 ```bash
rosdep install --from-paths src --ignore-src --rosdistro melodic -y
   ```
   ```bash
sudo mkdir -p /opt/ros/melodic
   ```
  ```bash
echo 'sudo ./src/catkin/bin/catkin_make_isolated --install -DCMAKE_BUILD_TYPE=Release  --install-space /opt/ros/melodic -j1' > install.sh
   ```
 ```bash
bash ./install.sh
   ```
 ```bash
echo "source /opt/ros/melodic/setup.bash" >> ~/.bashrc
   ```


Paso 4. Reiniciar la Raspberry con 
   ```bash
sudo reboot 
   ```
   y volver a acceder a la raspberry con el VNC


Paso 5. Solución de posibles problemas:

* Si al ejecutar el comando $ bash ./install.sh se obtiene un problema por el módulo python-empy, se debe instalar lo siguiente:
   ```bash
sudo apt-get install -y python-empy
   ```
y luego volver a correr el comando
 ```bash
bash ./install.sh   
```

* Si hay problemas para correr el roscore por los modulos defusedxml y netifaces, se debe instalar lo siguiente:
 ```bash
sudo apt-get install python-defusedxml
```
 ```bash
pip install netifaces
```
y luego volver a correr el roscore

* Si hay problemas para correr los comandos de ros (i.e rostopic, rosservice, rosnode, etc), se deben instalar los siguientes modulos:
 ```bash
sudo pip install pycryptodomex
```
 ```bash
pip install gnupg
```

# Instrucciones Conexión 
Instrucciones para conectarse a la Raspberry

- Crear el hotspot: 
SSID: RobocolURC
PSWD: Robocol8102

- Conectar los elementos a la caja guiandose de los esquemáticos

- Conectar la alimentación UNICAMENTE cuando ya esté todo lo demás bien conectado

- Conectarse a la raspberry en la misma red mirando la IP, el usuario es "pi" y la contraseña es "326435"

- Correr los nodos correspondientes y publicar los tópicos para hacer que se muevan los actuadores y ver el echo de los sensores 


# Usage
primero correr el código de la cámara: (ver streaming en http://192.168.1.102:8000/) (MAC raspberry B8-27-EB-75-E5-70)
 ```bash
cd Desktop/
```
 ```bash
python3 rpi_streaming_camera.py
```

seguidamente iniciar el roscore de la red sino está iniciado:
- en una terminal de la rpi correr 
 ```bash
roscore
```
- si ya hay un roscore en la red revisar la ip donde está corriendo ese master

luego, correr los nodos, siempre empezando así en cada terminal:
 ```bash
cd sensorica_ws/
export ROS_IP=192.168.1.102
export ROS_MASTER_URI=http://192.168.1.106:11311
catkin_make
source devel/setup.bash
```
Se puede sustituir los pasos anteriores editando las últimas líneas del bashrc. 

###Comunicación Serial Arduino-Raspberry:
 ```bash
rosrun rosserial_arduino EVA_Serial_Arduino.py
```

###Sensores:
 ```bash
sudo chmod 777 /dev/ttyUSB0
```
 ```bash
rosrun rosserial_arduino serial_node.py _port:=/dev/ttyUSB0

```

###Comando para mirar los puertos desde Ubuntu:
 ```bash
dmesg | grep tty
```

###Comando para darle permiso a los puertos:
 ```bash
sudo chmod a+rw /dev/...
```


#Instrucciones para correr nodo de Sensores de Arduino

- Primero debe instalar la librería serial de ros desde la fuente:
 ```bash
cd <ws>/src
git clone https://github.com/ros-drivers/rosserial.git
cd <ws>
catkin_make
catkin_make install
source devel/setup.bash 
sudo apt-get install ros-melodic-rosserial-arduino
```
 ( El último comando no funciona en la raspberry)



- Después debe correr el roscore:
  ```bash
roscore
```
- Luego correr el nodo en el workspace donde tiene el paquete de rosserial:

```bash
rosrun rosserial_arduino serial_node.py _port:=/dev/tty(Aquí va el nombre del puerto) 
```

- Nota: 

Para poder programar el arduino desde el computador en Windows, se debe instalar el driver desde https://ftdichip.com/drivers/vcp-drivers/
En Ubuntu solo se debe seleccionar la opción en el "Processor" -> ATmega328 (Old Bootloader)

Si no se tienen los permisos del puerto USB:

```bash
ls -l /dev | grep ACM
sudo chmod 777 /dev/tty(Aquí va el nombre del puerto)
```

En mi caso me surgió un error porque la librería "queue" no estaba instalada, para instalarla:

lo que hice fue cambiar en el código del rosserial_python SerialClient.py la línea "import queue" por "import Queue as queue"

Para cambiar nombre de nodo se debe editar "rospy.init_node()" en el archivo "serial_node.py" de la carpeta de rosserial_arduino

- Finalmente, ya puede correr el nodo serial de arduino

[Instrucciones para correr nodo de Sensores de Arduino]: https://github.com/Sensorica-Robocol/Codigos-Arduino-EVA "#Instrucciones para correr nodo de Sensores de Arduino"
