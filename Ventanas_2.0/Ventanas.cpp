#include "Ventanas.h"

Boton::Boton(short pin)
{
  pinMode(pin, INPUT_PULLUP) ;
  pinBoton = pin ;
  botonStatus = digitalRead(pinBoton) ;
  botonStatusBup = botonStatus ;
}
bool Boton::getBotonStatus(void)
{
  botonStatus = digitalRead(pinBoton) ;
  delay(50) ;
  botonStatusBup = botonStatus ;
  //return(botonStatusBup ^ botonStatus) ;
  return (digitalRead(pinBoton)) ;
}


Puerta::Puerta(short Pin)
{
  pinMode(Pin, INPUT_PULLUP) ;
  pinPuerta = Pin ;
  puertaStatus = digitalRead(pinPuerta) ;
  puertaStatusBup = puertaStatus ;
}
bool Puerta::getPuertaStatus(void)
{
  puertaStatus = digitalRead(pinPuerta) ;
  delay(10) ;
  puertaStatusBup = puertaStatus ;
  //return(puertaStatusBup ^ puertaStatus) ;
  return (digitalRead(pinPuerta)) ;
}

Ventana::Ventana(short openRele, short closeRele, short ledClosed, short S1, short S2)
{
  pinMode(openRele, OUTPUT) ;
  pinMode(closeRele, OUTPUT) ;
  pinMode(ledClosed, OUTPUT) ;
  pinMode(S1, OUTPUT) ;
  pinMode(S2, OUTPUT) ;
  
  releCerrar = closeRele ;
  releAbrir = openRele ;
  ledCerrado = ledClosed ;
  s1=S1;
  s2=S2;
}
void Ventana::abrirV(void)
{
  digitalWrite(releAbrir, HIGH) ;
  digitalWrite(releCerrar, LOW) ;
}
void Ventana::cerrarV(void)
{
  digitalWrite(releAbrir, LOW) ;
  digitalWrite(releCerrar, HIGH) ;
}
void Ventana::stopMotion(void)
{
  digitalWrite(releAbrir, LOW) ;
  digitalWrite(releCerrar, LOW) ;
}

void Ventana::setS1(bool s)
{
  if (s == true)
    digitalWrite(s1, HIGH);
  else
    digitalWrite(s1, LOW);
}

void Ventana::setS2(bool s)
{
  if (s == true)
    digitalWrite(s2, HIGH);
  else
    digitalWrite(s2, LOW);
}


void Ventana::setWindowsStatus(bool s)
{
  bf_estadoVentana = s ;

  if (bf_estadoVentana == true)
    digitalWrite(ledCerrado, HIGH);
  else
    digitalWrite(ledCerrado, LOW);
}




Corriente::Corriente(int muestras){
  
  }


bool Corriente::get_corriente()
{
  bool bfReturnCurrent ;
  static unsigned int adcSensorMedia ;
  
  i++ ;
  bfReturnCurrent = false ;
  adcSensorMedia = adcSensorMedia + analogRead(SENSORCHANNEL) ;
  if (i >= NoSAMPLES)
  {
    adcSensorMedia = adcSensorMedia / (i) ;
    //currentSensor = abs(((float)(adcSensorMedia - 5)) / 0.085) ;
    currentSensor = abs((float)(((5 * (float)adcSensorMedia) - 2557) / 85)) ;      // 85 formula de JUAN
    i = 0 ;
    adcSensorMedia = 0 ;
    Serial.println(currentSensor);
    if (currentSensor >= 3.50)                          //ajuste corriente motor
    {
      bfReturnCurrent = true ;
    }
    else
    {
      bfReturnCurrent = false ;
    }
  }
  return (bfReturnCurrent) ;
}
