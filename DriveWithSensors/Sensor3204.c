/**
* Sensor Reader
* MCP3204 12-bit 4-channel ADC
*/
// MCP3204.8
#define CS 15
// MCP3204.9
#define DIN 14
// MCP3204.10
#define DOUT 13
// MCP3204.11
#define CLK 12

// list of channels
//const char chans[] = {0xC, 0xD, 0xE, 0xF};


//------------- ADC READ FUNCTION----------------
int Read_3204(int channel){
  int adcvalue = 0;
  byte commandbits = B11000000; //command bits - start, mode, chn (3), dont care (3)

  //allow channel selection
  commandbits|((channel-1)<<3);
   //digitalWrite(CS,HIGH);
  digitalWrite(CS,LOW); //Select adc
  // setup bits to be written
  for (int i=7; i>=3; i--){
    digitalWrite(DOUT,commandbits&1<<i);
    //cycle clock
    digitalWrite(CLK,HIGH);
    digitalWrite(CLK,LOW);    
  }

  digitalWrite(CLK,HIGH);    //ignores 2 null bits
  digitalWrite(CLK,LOW);
  digitalWrite(CLK,HIGH);  
  digitalWrite(CLK,LOW);

  //read bits from adc
  for (int i=11; i>=0; i--){
    adcvalue+=digitalRead(DIN)<<i;
    //cycle clock
    digitalWrite(CLK,HIGH);
    digitalWrite(CLK,LOW);
  }
  digitalWrite(CS, HIGH); //turn off device
  //digitalWrite(CS,LOW);
  return adcvalue;
}

void sense_init()
{
    digitalWrite(CS, HIGH);
}