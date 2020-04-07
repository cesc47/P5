#include <iostream>
#include <math.h>
#include "keyvalue.h"
#include "seno.h"

#include <stdlib.h>

using namespace upc;
using namespace std;

Seno::Seno(const std::string &param) 
  : adsr(SamplingRate, param) {
  bActive = false;
  x.resize(BSIZE);

  /*
    You can use the class keyvalue to parse "param" and configure your instrument.
    Take a Look at keyvalue.h    
  */
  KeyValue kv(param);
  int N;

  if (!kv.to_int("N",N))
    N = 40; //default value 40
  
  //Create a tbl with one period of a sinusoidal wave
  tbl.resize(N);
  float phase = 0, step = 2 * M_PI /(float) N;
  index = 0;
  for (int i=0; i < N ; ++i) {
    tbl[i] = sin(phase);
    phase += step;
  }
}


void Seno::command(long cmd, long note, long vel) {
  if (cmd == 9) {		//'Key' pressed: attack begins
    bActive = true;
    adsr.start();
    index = 0;
    float fo = 440.0 * pow(2,(((float)note - 69.0)/12.0));      //calculo de la frecuencia de la nota
    Fo = fo/SamplingRate;                            //cálculo de la frecuencia discreta de la nota
    step = 2 * M_PI * Fo;                                   //crearemos el seno a partir de nuestra frecuencia Fo
    cout << fo << endl;

	A = vel / 127.;                                           //amplitud normalizada
  }
  else if (cmd == 8) {	//'Key' released: sustain ends, release begins
    adsr.stop();
    acumulat = 0;
  }
  else if (cmd == 0) {	//Sound extinguished without waiting for release to end
    adsr.end();
  }
}


const vector<float> & Seno::synthesize() {
  if (not adsr.active()) {
    x.assign(x.size(), 0);
    bActive = false;
    return x;
  }
  else if (not bActive)
    return x;

  float increment = Fo*tbl.size();
  
  for (unsigned int i=0; i<x.size(); ++i) {
    cout << index << endl;
    x[i] = A * tbl[index];
    acumulat += increment;

    index = roundf(acumulat);
    if (index >= tbl.size()){
      //cout << "hola" << endl;
      index = 0;
      acumulat = 0;
    }
      
  }
  adsr(x); //apply envelope to x and update internal status of ADSR

  return x;
}
