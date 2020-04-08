#ifndef INSTRUMENT_FM
#define INSTRUMENT_FM

#include <vector>
#include <string>
#include "instrument.h"
#include "envelope_adsr.h"

namespace upc {
  class Instrument_Fm: public upc::Instrument {
    EnvelopeADSR adsr;
    float c;
    float fase_c;
    float fase_m;
    float step_c;
    float step_m;
    float I; 
    float m;
	  float A;
    float f0;
    float n1;
    float n2;
  public:
    Instrument_Fm(const std::string &param = "");
    void command(long cmd, long note, long velocity=1); 
    const std::vector<float> & synthesize();
    bool is_active() const {return bActive;} 
  };
}

#endif
