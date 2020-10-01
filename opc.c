#define X(v, addr) (v->V[(addr & 0x0F00) >> 0x8])
#define Y(v, addr) (v->V[(addr & 0x00F0) >> 0x4])

typedef struct opcode {
  uint16_t code;
  char debug[32];
  void (*func)(vm*, uint16_t);
} opcode;

void call_mc(vm* v, uint16_t addr) {v->PC = addr;}
void disp_cl(vm* v, uint16_t addr) {
  for (uint8_t off = 0; off < 0x100; off++)
    v->(SCREEN+off) = 0x0;
}
void ret(vm* v, uint16_t addr) {
  v->PC = v->RAM[v->SP];
  v->PC--;
  v->SP--;
}

void jump(vm* v, uint16_t addr) {
  v->PC = addr;
  v->PC--;
}

void call(vm* v, uint16_t addr) {
  RAM[v->SP++] = (v->PC)+1;
  jump(v, addr);
}

void skip_vx_eq_nn(vm* v, uint16_t addr) {
  if (X(v,addr) == addr && 0xFF) v->PC++;
}

void skip_vx_neq_nn(vm* v, uint16_t addr) {
  if (X(v,addr) != addr && 0xFF) v->PC++;
}

void skip_vx_eq_vy(vm* v, uint16_t addr) {
  if (X(v,addr) == Y(v,addr)) v->PC++;
}

void vx_eq_nn(vm* v, uint16_t addr) {
  X(v,addr) = addr && 0xFF;
}

void vx_add_nn(vm* v, uint16_t addr) {
  X(v,addr) += addr && 0xFF;
}

void vx_eq_vy(vm* v, uint16_t addr) {
  X(v,addr) = Y(v,addr);
}

void vx_oeq_vy(vm* v, uint16_t addr) {
  X(v,addr) |= Y(v,addr);
}

void vx_aeq_vy(vm* v, uint16_t addr) {
  X(v,addr) &= Y(v,addr);
}

void vx_xeq_vy(vm* v, uint16_t addr) {
  X(v,addr) ^= Y(v,addr);
}

void vx_add_vy(vm* v, uint16_t addr) {
  int no = X(v,addr) + Y(v,addr);
  X(v,addr) += Y(v,addr);
  v->V[0xF] = (no != (int)X(v,addr));
}

//IGUAL FALLA, QUE ES UN BORROW?¿
void vx_sub_vy(vm* v, uint16_t addr) {
  int no = X(v,addr) - Y(v,addr);
  X(v,addr) -= Y(v,addr);
  v->V[0xF] = (no != (int)X(v,addr));
}

void vx_shift(vm* v, uint16_t addr) {
  v->V[0xF] = X(v,addr) & 0x1;
  X(v,addr) >>= 1;
}

void 

void init_opc_table(opcode * opc) {
  opc[0x0000 ... 0x0FFF] -> func = opct[0];
  opc[0x00E0] -> func            = opct[1];
  opc[0x00EE] -> func            = opct[2];
  opc[0x1000 ... 0x1FFF] -> func = opct[3];
  opc[0x2000 ... 0x2FFF] -> func = opct[4];
  opc[0x3000 ... 0x3FFF] -> func = opct[5];
  opc[0x4000 ... 0x4FFF] -> func = opct[6];
  opc[0x5000 ... 0x5FFF] -> func = opct[7];
  opc[0x6000 ... 0x6FFF] -> func = opct[8];
  opc[0x7000 ... 0x7FFF] -> func = opct[9];
  opc[0x9000 ... 0x9FFF] -> func = opct[10];
  opc[0xA000 ... 0xAFFF] -> func = opct[11];
  opc[0xB000 ... 0xBFFF] -> func = opct[12];
  opc[0xC000 ... 0xCFFF] -> func = opct[13];
  opc[0xD000 ... 0xDFFF] -> func = opct[14];

  for (int i = 0xF000; i < 0xFFFF); i++) {
    int last = i & 0xFF;
    switch (last) {
      case 0x07: opc[i] -> func = opct[15];
      break;
      case 0x0A: opc[i] -> func = opct[16];
      break;
      case 0x15: opc[i] -> func = opct[17];
      break;
      case 0x18: opc[i] -> func = opct[18];
      break;
      case 0x1E: opc[i] -> func = opct[19];
      break;
      case 0x29: opc[i] -> func = opct[20];
      break;
      case 0x33: opc[i] -> func = opct[21];
      break;
      case 0x55: opc[i] -> func = opct[22];
      break;
      case 0x65: opc[i] -> func = opct[23];
      break;
    }
  }

  for (int i = 0x8000; i < 0x9000; i++) {
    int last = i & 0xF;
    if (last == 0xE) opc[i] -> func = opct[24];
    if (last <  0x8) opc[i] -> func = opct[25+last];
  }
}
