#define datatotal 768

int digitalIn = 13;
bool before = false;
bool countstart = false;
bool countdata = false;

void setup() {
  Serial.begin(500000,SERIAL_8E2);
}

int loopcount = 0;
int comb = 0;
int measuring_time = 1000;
int misodata = 0;

int data[datatotal];
//TODO: Explain each command

void loop() {
  if(Serial.available()>0){
    int readValue = Serial.read();
    if(readValue!=-1) {
      if(readValue=='8'){
        loopcount=0;
      }else if(readValue=='7'){
        Serial.println(loopcount);
      }else if(readValue=='1'){
        if(comb<loopcount){
          Serial.println(data[comb]);
          comb++;
        }
      }else if(readValue=='2'){
        if(comb>0) {
          Serial.println(data[comb]);
          comb--;
        }
      }else if(readValue=='4'){
        comb = 0;
      }else if(readValue=='a'){
        for (int i = 0; i < loopcount; i++)
          Serial.println(data[i]);
      }else if(readValue=='b'){
        if(loopcount>0) {
            if(Serial.available()>0){
              measuring_time = Serial.parseInt();
            }
        }
        
      }
    }
  }
  //digitalValue : DMD Change Signal(DCS)
  //when DCS is positive, it means that DMD is flipping the mirror.
  //when DCS is positive edge, 
  //Pattern Cycle: period of time between DMD is flipping the mirror
  //Flipping Time: period of time that DMD is flipping the mirror(58us)
  //Ignore Time: ignore first fall time after flipping the mirror(not used in this code)

  int digitalValue = digitalRead(digitalIn);
    if(digitalValue) {//digitalValue is true
      before = true;
      if(countdata) {//stop measuring and record the data
            //TODO: receive data from FPGA
            

            data[loopcount-1]=misodata;
            countdata = false;
        }
    }else{
      if(before) {// negedge digitalValue, start measuring
        if (loopcount<datatotal) {
          before = false;
          loopcount++;
          countstart=true;
        }
      }else{
        if(countstart) {
          eachdata[looploopcount]=analogRead(analogIn);
          looploopcount++;
          if (looploopcount == datatotaleach) {
            countstart=false;
            countdata = true;
          }
        }
      }
    }
  } 
