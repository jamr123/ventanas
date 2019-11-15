#include "Arduino.h"
#include"Ventanas.h"


Ventana V1(R1, R2, LED_VN, SS1, SS2) ; // Ventana (PIN_RELE_OPEN,PIN_RELE_CLOSE,PIN_LED_CERRADO,S1,S2)
Puerta P1(PUERTA1) ; // Puerta (PIN_PUERTA)
Puerta P2(PUERTA2) ; // Puerta (PIN_PUERTA)
Boton  BA(BTA) ; // Boton(PIN_BOTON_ABRIR)
Boton  BC(BTC) ; // Boton(PIN_BOTON_CERRAR)
Boton  E1(BTN) ; // Boton(ENTRADA NUEVA)
Boton  Jump(JMP) ;//Jumper


Corriente corriente(10);//Corriente con filtrado de muestras

bool flagEstadoVentana = true;
int picoCorriente = 100;
int tiempoStopDelay = 780;  // Tiempo paro de motor (STOP) 

int conteo1 = 0;
int conteo2 = 0;
int conteo3 = 0;
int conteo4 = 0;

int t1 = 30;     //tiempo delay salida 2
int t2 = 15000; //tiempo salida 1 en milisegundos
int t3 = 15;   //tiempo Apertura ventana entrada nueva
int t4 = 30;  //tiempo de led entrada nueva

int periodo = 1000;
unsigned long TiempoAhora = 0;


void setup() {

  //flagEstadoVentana = true;

  cerrarVentana();
}





void loop() {
  
  if (millis() > TiempoAhora + periodo) {
    
    btns();
    puertas();
    TiempoAhora = millis();
  }


  
}








void puertas() {

  if (P1.getPuertaStatus() == true)
  {
    conteo1 ++;

    if (P1.getPuertaStatus() == true && P2.getPuertaStatus() == false)
    {
      conteo2 ++;
      if (conteo2 == 10) {
        conteo1 = 0;
        conteo2 = 0;
        cerrarVentana();
        
      }
    }


    if (conteo1 == 60) {
      conteo1 = 0;
      conteo2 = 0;
      cerrarVentana();
    
    }
  }


  if (P1.getPuertaStatus() == false && P2.getPuertaStatus() == true)
  {
    conteo1 = 0;
    conteo2 = 0;
  }

}

void btns() {



  if (BA.getBotonStatus() == false)
  {
    abrirVentana();
    conteo3 ++;
    if (conteo3 == t1) {
      conteo3 = 0;
      V1.setS2(true);
    }
  }

  if (BC.getBotonStatus() == false)
  {
    cerrarVentana();
    conteo3 ++;
    if (conteo3 == t1) {
      conteo3 = 0;
      V1.setS2(true);
    }
  }





  if (E1.getBotonStatus() == false)
  {
    conteo4 ++;
    if (conteo4 == t3) {
      abrirVentana();
    }

    if (conteo4 == t4) {
      V1.setS1(true);
      delay(t2);
      V1.setS1(false);
    }


  } else {
    conteo4 = 0;
  }

  if (BC.getBotonStatus() == false && BA.getBotonStatus() == false)
  {
    conteo3 ++;
    if (conteo3 == t1) {
      conteo3 = 0;
      V1.setS2(true);
    }

  } 
  
  
  if (BC.getBotonStatus() == true && BA.getBotonStatus() == true)
  {
    conteo3 = 0;
    V1.setS2(false);
  }

}


void jumpStop() {
  if (Jump.getBotonStatus() == true) {
    corrienteStop();
  }
  else {
    tiempoStop();
  }
}


void cerrarVentana() {
  if (flagEstadoVentana == true) {     //lectura de estado de ventanas
    flagEstadoVentana = false;
    V1.cerrarV();
    jumpStop();
  }
}


void abrirVentana() {
  if (flagEstadoVentana == false ) { //lectura de estado de ventanas
    flagEstadoVentana = true;
    V1.abrirV();
    jumpStop();
  }
}


void stopVentana() {
  V1.stopMotion();

  if (flagEstadoVentana == false ) {
    V1.setWindowsStatus(1);
  } else {
    V1.setWindowsStatus(0);
  }
}



void corrienteStop() {
  bool flagcorriente = true;
  delay(picoCorriente);
  while (corriente.get_corriente() == false) {
    delay(10);
  }
  stopVentana();
}

void tiempoStop() {
  delay(tiempoStopDelay);
  stopVentana();
}
