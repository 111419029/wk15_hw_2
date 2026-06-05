const byte rowFormat[8] = {2, 7, 19, 5, 13, 18, 12, 16};
const byte columnFormat[8] = {6, 11, 10, 3, 17, 4, 8, 9};

const byte outputPattern[8][8] = {
  {0x00, 0x3c, 0x66, 0x66, 0x66, 0x66, 0x3c, 0x00}, //0
  {0x00, 0x18, 0x38, 0x18, 0x18, 0x18, 0x3c, 0x00}, //1
  {0x00, 0x3c, 0x4e, 0x0e, 0x3c, 0x70, 0x7e, 0x00}, //2
  {0x00, 0x7c, 0x0e, 0x3c, 0x0e, 0x0e, 0x7c, 0x00}, //3
  {0x00, 0x3c, 0x6c, 0x4c, 0x4c, 0x7e, 0x0c, 0x00}, //4
  {0x00, 0x7c, 0x60, 0x7c, 0x0e, 0x4e, 0x3c, 0x00}, //5
  {0x00, 0x3c, 0x60, 0x7e, 0x66, 0x66, 0x3c, 0x00}, //6
  {0x00, 0x7e, 0x06, 0x0c, 0x18, 0x38, 0x38, 0x00}, //7
};

void setup() {
  for (int thisPin = 0; thisPin < 8; thisPin++) {
    pinMode(columnFormat[thisPin], OUTPUT);
    pinMode(rowFormat[thisPin], OUTPUT);
    digitalWrite(columnFormat[thisPin], HIGH);
  }
}


void loop() {
  refreshScreen(readSensor8Level());
}


char readSensor8Level(){
  char ans = map(analogRead(A1), 0, 1024, -1, 8);
  if(ans == -1)
    return 0;
  if(ans == 8)
    return 7;
  return ans;
}


void refreshScreen(char outputChar) {
  for (int row = 0; row < 8; row++) {
    for (int column = 0; column < 8; column++)
      digitalWrite(columnFormat[column], HIGH);
    digitalWrite(rowFormat[row], HIGH);
    for (int column = 0; column < 8; column++){
      digitalWrite(columnFormat[column], (outputPattern[outputChar][row] & (128>>column)) ? LOW : HIGH);
    }
    digitalWrite(rowFormat[row], LOW);
  }
}
