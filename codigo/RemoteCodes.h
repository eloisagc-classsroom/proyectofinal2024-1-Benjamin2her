#ifndef REMOTECODES_H
#define REMOTECODES_H

// Define los códigos hexadecimales del control Remoto de Elegoo
enum RemoteCode : uint32_t {
    POWER = 0xBA45FF00,
    FUNC_STOP = 0xB847FF00,
    VOL_PLUS = 0xB946FF00,
    FAST_BACK = 0xBB44FF00,
    PAUSE = 0xBF40FF00,
    FAST_FORWARD = 0xBC43FF00,
    DOWN = 0xF807FF00,
    VOL_MINUS = 0xEA15FF00,
    UP = 0xF609FF00,
    EQ = 0xE619FF00,
    ST_REPT = 0xF20DFF00,
    NUM_0 = 0xE916FF00,
    NUM_1 = 0xF30CFF00,
    NUM_2 = 0xE718FF00,
    NUM_3 = 0xA15EFF00,
    NUM_4 = 0xF708FF00,
    NUM_5 = 0xE31CFF00,
    NUM_6 = 0xA55AFF00,
    NUM_7 = 0xBD42FF00,
    NUM_8 = 0xAD52FF00,
    NUM_9 = 0xB54AFF00
};

#endif // REMOTECODES_H
