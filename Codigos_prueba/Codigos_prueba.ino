#include <OneWire.h>
#include <DallasTemperature.h>
#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Float32.h>
#include <HX711.h>


//Código para leer los valores random de los sensores. 

HX711 scale;
ros::NodeHandle nh;

// Mensajes que se van a enviar por los tópicos
std_msgs::Float32 testtemp;
std_msgs::Float32 testmq4met;
std_msgs::Float32 testmq7mono;
std_msgs::Float32 testmq8hidro;
std_msgs::Float32 testhumedad;
std_msgs::Float32 testcelda;

// Tópicos para publicar los sensores que lee el Arduino
ros::Publisher p_temp("/stemp", &testtemp);
ros::Publisher p_metano("/smeta", &testmq4met);
ros::Publisher p_monox("/smonox", &testmq7mono);
ros::Publisher p_hidro("/shidro", &testmq8hidro);
ros::Publisher p_humed("/shumed", &testhumedad);
ros::Publisher p_celda("/scelda", &testcelda);

//Temperatura-Variables-lectura-pin(2)
OneWire oneWireObjeto(2);
DallasTemperature sensorDS18B20(&oneWireObjeto);
double temperatura;
double lecturahumedad;
//CeldaCarga-Variables
float calibration_factor = -947.43; // value obtained from preliminary calibration of load cell in EVA
float units;


void setup() 
{
  //sensorDS18B20.begin();
  //scale.begin(3,4); // dout = D3, clk = D4
  //scale.set_scale();
  //scale.tare();  //Reset the scale to 0
  nh.initNode();
  nh.advertise(p_temp);
  nh.advertise(p_metano);
  nh.advertise(p_monox);
  nh.advertise(p_hidro);
  nh.advertise(p_humed);
  nh.advertise(p_celda);

}

void updateUnits(){
  scale.set_scale(calibration_factor); //Adjust to this calibration factor
  units = scale.get_units(5); // 5 measures of weight
  if (units < 0)
  {
    units = 0.00;
  }
}

void loop() 
{

  //TEMPERATURA
  //Se lee realmente el valor del sensor
  //sensorDS18B20.requestTemperatures();
  //temperatura = sensorDS18B20.getTempCByIndex(0);
  int temperatura=random(0,100);
  //METANO
  //Para medir las concentraciones de Metano se obtuvo la siguiente Ecuación basandonos en las curvas de caraceterización. 
  // 300-10000ppm
  //int met = analogRead(A0); //Este me da la lectura en ppm
  int met=random(0,100);
  
  //MONOXIDO DE CARBONO
  //C0-Rango: 20 a 2000ppm 
  //int adc_MQ7 = analogRead(A1); //Leemos la salida analógica del MQ7
  int adc_MQ7=random(0,100);

  //HIDROGENO 
  //Hidrogeno = 986,79x-0,679
  //int adc_MQ8 = analogRead(A2); //Este la da en ppm
  int adc_MQ8=random(0,100);
  //HUMEDAD
  //El sensor de humedad trabaja en un rango de voltaje de 0V-4,2V
  //lecturahumedad = analogRead(A3);
  int lecturahumedad=random(0,100);
  
  // CELDA DE CARGA 
  //updateUnits();
  int units=random(0,100);
  
  // PUBLICAR TÓPICOS
  testtemp.data = temperatura;
  p_temp.publish( &testtemp );
  
  testmq4met.data = met;
  p_metano.publish( &testmq4met);
  
  testmq7mono.data = adc_MQ7;
  p_monox.publish( &testmq7mono );
  
  testmq8hidro.data = adc_MQ8;
  p_hidro.publish( &testmq8hidro );
  
  testhumedad.data = lecturahumedad;
  p_humed.publish( &testhumedad );

  testcelda.data = units;
  p_celda.publish( &testcelda );
  
  nh.spinOnce();
  
  delay(1000); // publish messages every 1 second
}
