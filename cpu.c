//MULTIPLES 
//0, 8, E, F
uint16_t current_opcode;
void uopc(uint16_t opc) {
  if (opc > current_opcode) current_opcode = opc;
}

typedef struct vm {
  uint8_t V[0x10];
  uint8_t I;
  uint8_t SP;
  uint8_t PC;
  uint8_t DELAY;
  uint8_t SOUND;
  uint8_t *RAM;
  uint8_t *SCREEN;
  opcode *OP_TABLE;
} vm;

void init(vm * v) {
  v -> SP = 0xfa0;
  v -> PC = 0x200;
  v -> RAM = malloc(0x1000)
  v -> SCREEN  = &v->RAM[0xf00]
}

uint16_t decode(vm * v) {
  uint16_t instr = v->RAM[v->PC]

  uint8_t op  = ((instr & 0xF000) >> 0x10);
  uint8_t reg = ((instr & 0x0F00) >> 0x8);
  uint8_t mod = (instr & 0x00FF);

  if (op == 0x0 && mod == 0xE0)
  if (op == 0x0 && mod == 0xEE)
  if (op == 0x8) {

  }
  if (op == 0xE && mod == 0x9E)
  if (op == 0xE && mod == 0xA1)
  if (op == 0xF && mod == 0x07)
  if (op == 0xF && mod == 0x0A)
  if (op == 0xF && mod == 0x15)
  if (op == 0xF && mod == 0x18)
  if (op == 0xF && mod == 0x1E)
  if (op == 0xF && mod == 0x29)
  if (op == 0xF && mod == 0x33)
  if (op == 0xF && mod == 0x55)
  if (op == 0xF && mod == 0x65)
}

void loop(vm * v) {
  while (1) {
    uint8_t STORED_PC = v -> PC;
    uint16_t = decode(v);
    if (debug) {
      printf("-----------------\n")
      printf("OPC: %4x PC: %4x\n", instr, v->PC);
      printf("SPC: %4x SP: %4x\n", STORED_PC, v -> SP);
    }
  }
}
