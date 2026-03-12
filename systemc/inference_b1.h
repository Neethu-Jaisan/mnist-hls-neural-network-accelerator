// ==============================================================
// Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2020.1 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __inference_b1_H__
#define __inference_b1_H__


#include <systemc>
using namespace sc_core;
using namespace sc_dt;




#include <iostream>
#include <fstream>

struct inference_b1_ram : public sc_core::sc_module {

  static const unsigned DataWidth = 32;
  static const unsigned AddressRange = 16;
  static const unsigned AddressWidth = 4;

//latency = 1
//input_reg = 1
//output_reg = 0
sc_core::sc_in <sc_lv<AddressWidth> > address0;
sc_core::sc_in <sc_logic> ce0;
sc_core::sc_out <sc_lv<DataWidth> > q0;
sc_core::sc_in<sc_logic> reset;
sc_core::sc_in<bool> clk;


sc_lv<DataWidth> ram[AddressRange];


   SC_CTOR(inference_b1_ram) {
        ram[0] = "0b00111110110011110011001110001000";
        ram[1] = "0b00111110000111101111001110001111";
        ram[2] = "0b00111101101101000001110011001111";
        ram[3] = "0b00111110011101100100111000100001";
        ram[4] = "0b10111101001001110001110100101000";
        ram[5] = "0b10111011101100010110000111110111";
        ram[6] = "0b10111110001101110110000000101110";
        ram[7] = "0b00111110010001011100110100101110";
        ram[8] = "0b10111101111011100000110100010100";
        ram[9] = "0b10111101110111100010010111011010";
        ram[10] = "0b00111101101010100010001000000000";
        ram[11] = "0b00111101000100101000011111111100";
        ram[12] = "0b00111110110000011101000001101011";
        ram[13] = "0b00111101101000110100000110110100";
        ram[14] = "0b00111101110011001011011100001110";
        ram[15] = "0b00111011001011001001100001111011";


SC_METHOD(prc_write_0);
  sensitive<<clk.pos();
   }


void prc_write_0()
{
    if (ce0.read() == sc_dt::Log_1) 
    {
            if(address0.read().is_01() && address0.read().to_uint()<AddressRange)
              q0 = ram[address0.read().to_uint()];
            else
              q0 = sc_lv<DataWidth>();
    }
}


}; //endmodule


SC_MODULE(inference_b1) {


static const unsigned DataWidth = 32;
static const unsigned AddressRange = 16;
static const unsigned AddressWidth = 4;

sc_core::sc_in <sc_lv<AddressWidth> > address0;
sc_core::sc_in<sc_logic> ce0;
sc_core::sc_out <sc_lv<DataWidth> > q0;
sc_core::sc_in<sc_logic> reset;
sc_core::sc_in<bool> clk;


inference_b1_ram* meminst;


SC_CTOR(inference_b1) {
meminst = new inference_b1_ram("inference_b1_ram");
meminst->address0(address0);
meminst->ce0(ce0);
meminst->q0(q0);

meminst->reset(reset);
meminst->clk(clk);
}
~inference_b1() {
    delete meminst;
}


};//endmodule
#endif
