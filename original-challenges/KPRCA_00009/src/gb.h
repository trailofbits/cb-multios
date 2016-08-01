#include <stdint.h>

#define SLEEP_US (100)
#define TICKS_SLEEP (1)
#define TICKS_DIVIDER 61
#define TICKS_MAX (10 * 1000000) /* about 10 seconds */

#define MEM_SIZE 0x10000 /* 64KB Address Space */
#define ROM_SIZE 0x8000 /* 32KB ROM */

/* Memory Regions */
#define ADDR_ROM0 0x0000
#define SIZE_ROM0 0x4000
#define ADDR_ROM1 0x4000
#define SIZE_ROM1 0x4000
#define ADDR_VRAM 0x8000
#define SIZE_VRAM 0x2000
#define ADDR_CRAM 0xA000 /* External (Cartridge) RAM */
#define SIZE_CRAM 0x2000
#define ADDR_WRAM 0xC000
#define SIZE_WRAM 0x2000
#define ADDR_ECHO 0xE000
#define SIZE_ECHO 0x1E00
#define ADDR_OAM  0xFE00 /* Sprite Attribute Table */
#define SIZE_OAM  0x00A0
#define ADDR_MMIO 0xFF00 /* I/O Ports */
#define SIZE_MMIO 0x0080
#define ADDR_HRAM 0xFF80 /* High RAM */
#define SIZE_HRAM 0x007F
#define ADDR_IE   0xFFFF /* Interrupt Enable Register */
#define SIZE_IE   0x0001

/* I/O Ports */
#define IO_JOYP 0xFF00
#define IO_SB   0xFF01
#define IO_SC   0xFF02
#define IO_DIV  0xFF04
#define IO_TIMA 0xFF05
#define IO_TMA  0xFF06
#define IO_TAC  0xFF07
#define IO_IF   0xFF0F
#define IO_NR10 0xFF10
#define IO_NR11 0xFF11
#define IO_NR12 0xFF12
#define IO_NR13 0xFF13
#define IO_NR14 0xFF14
#define IO_NR21 0xFF16
#define IO_NR22 0xFF17
#define IO_NR23 0xFF18
#define IO_NR24 0xFF19
#define IO_NR30 0xFF1A
#define IO_NR31 0xFF1B
#define IO_NR32 0xFF1C
#define IO_NR33 0xFF1D
#define IO_NR34 0xFF1E
#define IO_NR41 0xFF20
#define IO_NR42 0xFF21
#define IO_NR43 0xFF22
#define IO_NR44 0xFF23
#define IO_NR45 0xFF24
#define IO_NR51 0xFF25
#define IO_NR52 0xFF26
#define IO_WAVE 0xFF30 /* FF30 - FF3F Pattern RAM */
#define IO_LCDC 0xFF40
#define IO_STAT 0xFF41
#define IO_SCY  0xFF42
#define IO_SCX  0xFF43
#define IO_LY   0xFF44
#define IO_LYC  0xFF45
#define IO_DMA  0xFF46
#define IO_BGP  0xFF47
#define IO_OBP0 0xFF48
#define IO_OBP1 0xFF49
#define IO_WY   0xFF4A
#define IO_WX   0xFF4B
#define IO_IE   0xFFFF

typedef uint8_t input_t;
#define INPUT_RIGHT 0x01
#define INPUT_LEFT  0x02
#define INPUT_UP    0x04
#define INPUT_DOWN  0x08
#define INPUT_A     0x10
#define INPUT_B     0x20
#define INPUT_SELECT 0x40
#define INPUT_START 0x80

#define F_C 0x10
#define F_H 0x20
#define F_N 0x40
#define F_Z 0x80

typedef struct {
#define LOGO_SIZE 0x30
#define TITLE_SIZE 0x10
    uint8_t code[0x4];
    uint8_t logo[LOGO_SIZE];
    char title[TITLE_SIZE];
    char new_publisher[0x2];
    uint8_t sgb_flags;
    uint8_t cart_type;
#define ROM_32KB 0x00
#define ROM_64KB 0x01
#define ROM_128KB 0x02
#define ROM_256KB 0x03
#define ROM_512KB 0x04
#define ROM_1024KB 0x05
#define ROM_2048KB 0x06
#define ROM_4096KB 0x07
    uint8_t rom_size;
#define RAM_NONE 0x00
#define RAM_2KB 0x01
#define RAM_8KB 0x02
#define RAM_32KB 0x03
    uint8_t ram_size;
    uint8_t region;
    uint8_t publisher;
    uint8_t version;
    uint8_t hdr_cksum;
    uint16_t cksum;
} hdr_t;

typedef struct {
    union {
        uint16_t r16;
        uint8_t r8[2];
    } AF;
    union {
        uint16_t r16;
        uint8_t r8[2];
    } BC;
    union {
        uint16_t r16;
        uint8_t r8[2];
    } DE;
    union {
        uint16_t r16;
        uint8_t r8[2];
    } HL;
    uint16_t SP;
    uint16_t PC;
    uint8_t IME;
#define IME_WAIT 0x80
#define IME_DI  0x40
#define IME_EI  0x20
#define IME_IE  0x01
} reg_t;

typedef struct {
    uint8_t bytes[16];
} tile_t;

typedef struct {
    uint8_t colors[4];
} pal_t;

typedef struct {
    /* Memory */
    uint8_t *mem;

    /* Cartridge */
    uint8_t *rom;
    char title[TITLE_SIZE];

    /* LCD */
    uint8_t *bg;
    uint8_t *screen;
    pal_t palettes[3];

    /* Joypad */
    input_t input;

    /* CPU state */
    reg_t reg;
#define R_SP reg.SP
#define R_PC reg.PC
#define R_AF reg.AF.r16
#define R_BC reg.BC.r16
#define R_DE reg.DE.r16
#define R_HL reg.HL.r16
#define R_A reg.AF.r8[1]
#define R_F reg.AF.r8[0]
#define R_B reg.BC.r8[1]
#define R_C reg.BC.r8[0]
#define R_D reg.DE.r8[1]
#define R_E reg.DE.r8[0]
#define R_H reg.HL.r8[1]
#define R_L reg.HL.r8[0]
    int halted;
    float speed;
    int vblank;

    /* Timers */
    unsigned int ticks;
    unsigned int ticks_skip;
    unsigned int ticks_ly;
    unsigned int ticks_divider;
    unsigned int ticks_timer;
} gb_t;

// Hardware functions
gb_t *gb_new();
void gb_reset(gb_t *gb);
int gb_load(gb_t *gb, uint8_t *cartridge);
int gb_tick(gb_t *gb);

// CPU functions
int cpu_tick(gb_t *gb);
void cpu_interrupt(gb_t *gb, int n);

// LCD functions
int lcd_tick(gb_t *gb);
