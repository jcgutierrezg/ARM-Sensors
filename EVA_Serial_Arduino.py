#!/usr/bin/env python3 

import rospy
import time
import serial
from std_msgs.msg import String

# Este codigo sirve para la comunicacion serial entre un Arduino y una Raspberry. Es un nodo de ros que se subscribe 
# al tópico sensorica_actuadores_hablar y lee el mensaje para pasarlo luego al Arduino. Publica el mensaje entregado 
# por el Arduino en el tópico sensorica_actuadores_escuchar. Los mensajes son tipo String. 

def callback(data):
    ser.write(data.data.encode('utf-8'))
    
def EVA_Serial_Arduino():
    respuesta = rospy.Publisher('sensorica_actuadores_escuchar', String, queue_size=10)
    rospy.Subscriber("sensorica_actuadores_hablar", String, callback)
    rospy.init_node('sensorica_actuadores', anonymous=True)
    rate = rospy.Rate(10) # 10hz
    while not rospy.is_shutdown():
        if ser.in_waiting > 0:
            line = ser.readline().decode('utf-8').rstrip()
            print(line)
            time.sleep(1)  
            rospy.loginfo(line)
            respuesta.publish(line)
            
            

if __name__ == '__main__':
    try:
        ser = serial.Serial('/dev/ttyUSB0', 57600, timeout=1)
        ser.reset_input_buffer()
        EVA_Serial_Arduino()
        
    except rospy.ROSInterruptException:
        pass

