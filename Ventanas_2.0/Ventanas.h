#ifndef VENTANAS_H
#define VENTANAS_H

#include <stdint.h>
#include "Arduino.h"


#define SECS_10         10       // --> 5 secs
#define SECS_60         30       // --> 15 secs 


////////////////////ENTRADAS Y SALIDAS/////////////////////////////////////////////
#define R1               1        // RELE_OPEN
#define R2               0        // RELE_CLOSE
#define LED_VN           2        // PIN_LED
#define SS1              3       // SALIDA1 AGREGADA 
#define SS2              4       // SALIDA2 AGREGADA
#define PUERTA1          6       // PIN_PUERTA1
#define PUERTA2          5       // PIN_PUERTA2
#define BTC              9       // BOTON CERRAR
#define BTA              8       // BOTON ABRIR
#define BTN              7       // BOTON AGREGADO
#define JMP             18       // JUMPER
/////////////////////////////////////////////////////////////////////////////////////


#define SENSIBILITY     0.065    // Constante para el ACS
#define CONVERSION      (5/1023)
#define SENSORCHANNEL   A5       // CAnal ADC para Sensor ACS
#define POTCHANNEL      A1       // Canal ADC para Potenciometro
#define NoSAMPLES       5        // Numero de muestras para la lectura de los canales ADC
#define INIT_STATE      0        // ESTADO INICIAL, CIERRA LA VENTANA PARA ESTABLECER EL VALOR DE LAS BANDERAS
#define CIERRA_VENTANA  1        // ESTADO PARA HACER LA LECTURA DE BOTONES y PUERTAS
#define ABRE_VENTANA    2        // ESTADO PARA ABRIR VENTANA
#define CLOSE_WINDOW    3        // ESTADO PARA CERRAR VENTANA
#define ABRE_VENTANA_CURRENT 4
#define CIERRA_VENTANA_CURRENT 5
#define WINDOWS_CLOSED  1        // CONSTANTE SIMBOLICA INDICA CUANDO LA VENTANA ESTA CERRADA 
#define WINDOWS_OPENED  0        // CONSTANTE SIMBOLICA INDICA CUANDO LA VENTANA ESTA ABIERTA
#define DOOR_CLOSED     1        // CONSTANTE SIMBOLICA --> 1 CUANDO LA PUERTA ESTA CERRADA
#define DOOR_OPENED     0        // CONSTANTE SIMBOLICA --> 0 CUANDO LA PUERTA ESTA ABIERTA
#define APERTURA_CORRIENTE  10
#define CIERRA_VENTANA      11
#define CIERRE_CORRIENTE    12

const float inMin = 0.0 ;
const float inMax = 5.0 ;
const float outMin = 0.0 ;
const float outMax = 10.0 ;

class Boton
{
  private :
    short pinBoton ;
    bool botonStatus ;
    bool botonStatusBup ;
  public :
    Boton(short pin);
    bool getBotonStatus(void);
} ;
class Puerta                      // DEclaración de la clase Puerta
{
  private :
    short pinPuerta ;
    bool puertaStatus ;
    bool puertaStatusBup ;
  public :
    Puerta(short Pin);
    bool getPuertaStatus(void);
} ;

class Ventana                      // DEclaración de la clase Ventana
{
  private :
    short releCerrar ;
    short releAbrir ;
    short ledCerrado ;
    short s1;
    short s2;
    bool bf_estadoVentana ;
  public :

    Ventana(short openRele, short closeRele, short ledClosed, short S1, short S2);

    void abrirV(void);
    void cerrarV(void);
    void stopMotion(void);
    void setS1(bool s);
    void setS2(bool s);
    void setWindowsStatus(bool s);
} ;



class Corriente
{
  private:
  int i;
  float currentSensor;
  public:
  Corriente(int muestras);
  bool get_corriente(void);

  };
#endif
