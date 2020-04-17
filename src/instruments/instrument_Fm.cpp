#include <iostream>
#include <math.h>
#include "keyvalue.h"
#include "instrument_Fm.h"

#include <stdlib.h>

using namespace upc;
using namespace std;

Instrument_Fm::Instrument_Fm(const std::string &param) 
  : adsr(SamplingRate, param) {
  bActive = false;
  x.resize(BSIZE);

  /*
    You can use the class keyvalue to parse "param" and configure your instrument.
    Take a Look at keyvalue.h    
  */
  KeyValue kv(param);

  if (!kv.to_float("n1",n1))
    n1 = 1; 
  
  if (!kv.to_float("i",I))
    I = 4; 

  if (!kv.to_float("n2",n2))
    n2 = 1; 
}


void Instrument_Fm::command(long cmd, long note, long vel) {
  if (cmd == 9) {		//'Key' pressed: attack begins
    bActive = true;
    adsr.start();
  }
  else if (cmd == 8) {	//'Key' released: sustain ends, release begins
    adsr.stop();
  }
  else if (cmd == 0) {	//Sound extinguished without waiting for release to end
    adsr.end();
  }

  f0 = 440.0 * pow(2, (((float)note - 69.0) / 12.0));  // Calculo de la frecuencia de la nota
  c = n1 * f0;
  m = n2 * f0; 
	A = 0.3 * vel / 127.;                                         // Amplitud normalizada

  //cout << "c:" << c << "\t" << "m:" << m << "\t" << "f0:" << f0 << endl;
  
  fase_c = 0;
  fase_m = 0;

  step_c = 2 * M_PI * c / SamplingRate;
  step_m = 2 * M_PI * m  / SamplingRate;   

}


const vector<float> & Instrument_Fm::synthesize() {
  if (not adsr.active()) {
    x.assign(x.size(), 0);
    bActive = false;
    return x;
  }
  else if (not bActive)
    return x;
  
  for (unsigned int i=0; i<x.size(); ++i) {
    x[i] = A * sin(fase_c + I * sin(fase_m));
    fase_c += step_c;
    fase_m += step_m;
    while(fase_c > M_PI)  fase_c -= 2*M_PI;
    while(fase_m > M_PI)  fase_m -= 2*M_PI;
  }
  adsr(x); //apply envelope to x and update internal status of ADSR

  return x;
}
