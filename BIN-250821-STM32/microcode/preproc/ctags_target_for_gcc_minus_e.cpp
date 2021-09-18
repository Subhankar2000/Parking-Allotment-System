# 1 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\microcode\\microcode.ino"
# 1 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\microcode\\microcode.ino"
# 29 "D:\\Arduino-STM32-ARM-M4\\portable\\sketchbook\\microcode\\microcode.ino"
uint16_t UCODE_TEMPLATE[16][8] = {
  { 0b0100000000000000 /* Memory address register in*/|0b0000000000000100 /* Program counter out*/, 0b0001000000000000 /* RAM data out*/|0b0000010000000000 /* Instruction register in*/|0b0000000000001000 /* Program counter enable*/, 0, 0, 0, 0, 0, 0 }, // 0000 - NOP
  { 0b0100000000000000 /* Memory address register in*/|0b0000000000000100 /* Program counter out*/, 0b0001000000000000 /* RAM data out*/|0b0000010000000000 /* Instruction register in*/|0b0000000000001000 /* Program counter enable*/, 0b0000100000000000 /* Instruction register out*/|0b0100000000000000 /* Memory address register in*/, 0b0001000000000000 /* RAM data out*/|0b0000001000000000 /* A register in*/, 0, 0, 0, 0 }, // 0001 - LDA
  { 0b0100000000000000 /* Memory address register in*/|0b0000000000000100 /* Program counter out*/, 0b0001000000000000 /* RAM data out*/|0b0000010000000000 /* Instruction register in*/|0b0000000000001000 /* Program counter enable*/, 0b0000100000000000 /* Instruction register out*/|0b0100000000000000 /* Memory address register in*/, 0b0001000000000000 /* RAM data out*/|0b0000000000100000 /* B register in*/, 0b0000000010000000 /* ALU out*/|0b0000001000000000 /* A register in*/|0b0000000000000001 /* Flags in*/, 0, 0, 0 }, // 0010 - ADD
  { 0b0100000000000000 /* Memory address register in*/|0b0000000000000100 /* Program counter out*/, 0b0001000000000000 /* RAM data out*/|0b0000010000000000 /* Instruction register in*/|0b0000000000001000 /* Program counter enable*/, 0b0000100000000000 /* Instruction register out*/|0b0100000000000000 /* Memory address register in*/, 0b0001000000000000 /* RAM data out*/|0b0000000000100000 /* B register in*/, 0b0000000010000000 /* ALU out*/|0b0000001000000000 /* A register in*/|0b0000000001000000 /* ALU subtract*/|0b0000000000000001 /* Flags in*/, 0, 0, 0 }, // 0011 - SUB
  { 0b0100000000000000 /* Memory address register in*/|0b0000000000000100 /* Program counter out*/, 0b0001000000000000 /* RAM data out*/|0b0000010000000000 /* Instruction register in*/|0b0000000000001000 /* Program counter enable*/, 0b0000100000000000 /* Instruction register out*/|0b0100000000000000 /* Memory address register in*/, 0b0000000100000000 /* A register out*/|0b0010000000000000 /* RAM data in*/, 0, 0, 0, 0 }, // 0100 - STA
  { 0b0100000000000000 /* Memory address register in*/|0b0000000000000100 /* Program counter out*/, 0b0001000000000000 /* RAM data out*/|0b0000010000000000 /* Instruction register in*/|0b0000000000001000 /* Program counter enable*/, 0b0000100000000000 /* Instruction register out*/|0b0000001000000000 /* A register in*/, 0, 0, 0, 0, 0 }, // 0101 - LDI
  { 0b0100000000000000 /* Memory address register in*/|0b0000000000000100 /* Program counter out*/, 0b0001000000000000 /* RAM data out*/|0b0000010000000000 /* Instruction register in*/|0b0000000000001000 /* Program counter enable*/, 0b0000100000000000 /* Instruction register out*/|0b0000000000000010 /* Jump (program counter in)*/, 0, 0, 0, 0, 0 }, // 0110 - JMP
  { 0b0100000000000000 /* Memory address register in*/|0b0000000000000100 /* Program counter out*/, 0b0001000000000000 /* RAM data out*/|0b0000010000000000 /* Instruction register in*/|0b0000000000001000 /* Program counter enable*/, 0, 0, 0, 0, 0, 0 }, // 0111 - JC
  { 0b0100000000000000 /* Memory address register in*/|0b0000000000000100 /* Program counter out*/, 0b0001000000000000 /* RAM data out*/|0b0000010000000000 /* Instruction register in*/|0b0000000000001000 /* Program counter enable*/, 0, 0, 0, 0, 0, 0 }, // 1000 - JZ
  { 0b0100000000000000 /* Memory address register in*/|0b0000000000000100 /* Program counter out*/, 0b0001000000000000 /* RAM data out*/|0b0000010000000000 /* Instruction register in*/|0b0000000000001000 /* Program counter enable*/, 0, 0, 0, 0, 0, 0 }, // 1001
  { 0b0100000000000000 /* Memory address register in*/|0b0000000000000100 /* Program counter out*/, 0b0001000000000000 /* RAM data out*/|0b0000010000000000 /* Instruction register in*/|0b0000000000001000 /* Program counter enable*/, 0, 0, 0, 0, 0, 0 }, // 1010
  { 0b0100000000000000 /* Memory address register in*/|0b0000000000000100 /* Program counter out*/, 0b0001000000000000 /* RAM data out*/|0b0000010000000000 /* Instruction register in*/|0b0000000000001000 /* Program counter enable*/, 0, 0, 0, 0, 0, 0 }, // 1011
  { 0b0100000000000000 /* Memory address register in*/|0b0000000000000100 /* Program counter out*/, 0b0001000000000000 /* RAM data out*/|0b0000010000000000 /* Instruction register in*/|0b0000000000001000 /* Program counter enable*/, 0, 0, 0, 0, 0, 0 }, // 1100
  { 0b0100000000000000 /* Memory address register in*/|0b0000000000000100 /* Program counter out*/, 0b0001000000000000 /* RAM data out*/|0b0000010000000000 /* Instruction register in*/|0b0000000000001000 /* Program counter enable*/, 0, 0, 0, 0, 0, 0 }, // 1101
  { 0b0100000000000000 /* Memory address register in*/|0b0000000000000100 /* Program counter out*/, 0b0001000000000000 /* RAM data out*/|0b0000010000000000 /* Instruction register in*/|0b0000000000001000 /* Program counter enable*/, 0b0000000100000000 /* A register out*/|0b0000000000010000 /* Output register in*/, 0, 0, 0, 0, 0 }, // 1110 - OUT
  { 0b0100000000000000 /* Memory address register in*/|0b0000000000000100 /* Program counter out*/, 0b0001000000000000 /* RAM data out*/|0b0000010000000000 /* Instruction register in*/|0b0000000000001000 /* Program counter enable*/, 0b1000000000000000 /* Halt clock*/, 0, 0, 0, 0, 0 }, // 1111 - HLT
};

uint16_t ucode[4][16][8];

void initUCode() {
  // ZF = 0, CF = 0
  memcpy(ucode[0], UCODE_TEMPLATE, sizeof(UCODE_TEMPLATE));

  // ZF = 0, CF = 1
  memcpy(ucode[1], UCODE_TEMPLATE, sizeof(UCODE_TEMPLATE));
  ucode[1][0b0111][2] = 0b0000100000000000 /* Instruction register out*/ | 0b0000000000000010 /* Jump (program counter in)*/;

  // ZF = 1, CF = 0
  memcpy(ucode[2], UCODE_TEMPLATE, sizeof(UCODE_TEMPLATE));
  ucode[2][0b1000][2] = 0b0000100000000000 /* Instruction register out*/ | 0b0000000000000010 /* Jump (program counter in)*/;

  // ZF = 1, CF = 1
  memcpy(ucode[3], UCODE_TEMPLATE, sizeof(UCODE_TEMPLATE));
  ucode[3][0b0111][2] = 0b0000100000000000 /* Instruction register out*/ | 0b0000000000000010 /* Jump (program counter in)*/;
  ucode[3][0b1000][2] = 0b0000100000000000 /* Instruction register out*/ | 0b0000000000000010 /* Jump (program counter in)*/;
}

char bufd[2];
char bufa[8];
int line_count = 0;
int oneTime = -1;
int addr = 0;
void writeEEPROM(int address, byte data) {
  for (int pin = 5; pin <= 12; pin += 1) {
    if (oneTime == -1) {
      sprintf(bufd, "%02x ", data);
      Serial2.print(bufd);
    }
    oneTime++;
    data = data >> 1;
  }
  oneTime = -1;

  line_count++;
  if (line_count % 8 == 0)
    Serial2.print("  ");
  if (line_count % 16 == 0) {
    Serial2.println("");
    addr = addr + 16;
    //    Serial.print(addr,HEX);
    //    Serial.print(":  ");
    sprintf(bufa, "%03x: ", addr);
    Serial2.print(bufa);
  }
}

void setup() {
  initUCode();
  Serial2.begin(9600);

  Serial2.print("Programming EEPROM");

  for (int address = 0; address < 1024; address += 1) {
    delayMicroseconds(1);
    delay(10);

    if (address % 64 == 0) {
      Serial2.print(".");
    }
  }

  Serial2.println(" done");

  Serial2.println("Reading EEPROM");

  int zero = 0;
  char buff[3];
  sprintf(buff, "000: ", zero);
  Serial2.print(buff);

  for (int address = 0; address < 1024; address += 1) {
    int flags = (address & 0b1100000000) >> 8;
    int byte_sel = (address & 0b0010000000) >> 7;
    int instruction = (address & 0b0001111000) >> 3;
    int step = (address & 0b0000000111);

    if (byte_sel) {
      writeEEPROM(address, ucode[flags][instruction][step]);
    } else {
      writeEEPROM(address, ucode[flags][instruction][step] >> 8);
    }
  }
}


void loop() {

}
