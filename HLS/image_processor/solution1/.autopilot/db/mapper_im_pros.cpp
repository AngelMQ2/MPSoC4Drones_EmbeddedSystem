#include <systemc>
#include <vector>
#include <iostream>
#include "hls_stream.h"
#include "ap_int.h"
#include "ap_fixed.h"
using namespace std;
using namespace sc_dt;
class AESL_RUNTIME_BC {
  public:
    AESL_RUNTIME_BC(const char* name) {
      file_token.open( name);
      if (!file_token.good()) {
        cout << "Failed to open tv file " << name << endl;
        exit (1);
      }
      file_token >> mName;//[[[runtime]]]
    }
    ~AESL_RUNTIME_BC() {
      file_token.close();
    }
    int read_size () {
      int size = 0;
      file_token >> mName;//[[transaction]]
      file_token >> mName;//transaction number
      file_token >> mName;//pop_size
      size = atoi(mName.c_str());
      file_token >> mName;//[[/transaction]]
      return size;
    }
  public:
    fstream file_token;
    string mName;
};
extern "C" void im_pros(char*, char*);
extern "C" void apatb_im_pros_hw(volatile void * __xlx_apatb_param_imageIn, volatile void * __xlx_apatb_param_imageOut) {
  // Collect __xlx_imageIn__tmp_vec
  vector<sc_bv<8> >__xlx_imageIn__tmp_vec;
  for (int j = 0, e = 12288; j != e; ++j) {
    __xlx_imageIn__tmp_vec.push_back(((char*)__xlx_apatb_param_imageIn)[j]);
  }
  int __xlx_size_param_imageIn = 12288;
  int __xlx_offset_param_imageIn = 0;
  int __xlx_offset_byte_param_imageIn = 0*1;
  char* __xlx_imageIn__input_buffer= new char[__xlx_imageIn__tmp_vec.size()];
  for (int i = 0; i < __xlx_imageIn__tmp_vec.size(); ++i) {
    __xlx_imageIn__input_buffer[i] = __xlx_imageIn__tmp_vec[i].range(7, 0).to_uint64();
  }
  // Collect __xlx_imageOut__tmp_vec
  vector<sc_bv<8> >__xlx_imageOut__tmp_vec;
  for (int j = 0, e = 12288; j != e; ++j) {
    __xlx_imageOut__tmp_vec.push_back(((char*)__xlx_apatb_param_imageOut)[j]);
  }
  int __xlx_size_param_imageOut = 12288;
  int __xlx_offset_param_imageOut = 0;
  int __xlx_offset_byte_param_imageOut = 0*1;
  char* __xlx_imageOut__input_buffer= new char[__xlx_imageOut__tmp_vec.size()];
  for (int i = 0; i < __xlx_imageOut__tmp_vec.size(); ++i) {
    __xlx_imageOut__input_buffer[i] = __xlx_imageOut__tmp_vec[i].range(7, 0).to_uint64();
  }
  // DUT call
  im_pros(__xlx_imageIn__input_buffer, __xlx_imageOut__input_buffer);
// print __xlx_apatb_param_imageIn
  sc_bv<8>*__xlx_imageIn_output_buffer = new sc_bv<8>[__xlx_size_param_imageIn];
  for (int i = 0; i < __xlx_size_param_imageIn; ++i) {
    __xlx_imageIn_output_buffer[i] = __xlx_imageIn__input_buffer[i+__xlx_offset_param_imageIn];
  }
  for (int i = 0; i < __xlx_size_param_imageIn; ++i) {
    ((char*)__xlx_apatb_param_imageIn)[i] = __xlx_imageIn_output_buffer[i].to_uint64();
  }
// print __xlx_apatb_param_imageOut
  sc_bv<8>*__xlx_imageOut_output_buffer = new sc_bv<8>[__xlx_size_param_imageOut];
  for (int i = 0; i < __xlx_size_param_imageOut; ++i) {
    __xlx_imageOut_output_buffer[i] = __xlx_imageOut__input_buffer[i+__xlx_offset_param_imageOut];
  }
  for (int i = 0; i < __xlx_size_param_imageOut; ++i) {
    ((char*)__xlx_apatb_param_imageOut)[i] = __xlx_imageOut_output_buffer[i].to_uint64();
  }
}
