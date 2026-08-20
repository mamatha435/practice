//i2c_defines.h

//pin defines
#define SCL 2
#define SDA 3

#define SCL_PIN_FUNC 0x00000010
#define SDA_PIN_FUNC 0x00000040

//clock defines 
#define FOSC 12000000
#define CCLK (FOSC*5)
#define PCLK (CCLK/4)
#define I2C_SPEED 100000
#define LOADVAL ((PCLK/I2C_SPEED)/2)

//SFRs
//defines for I2CONSET sfr
#define STA_BIT  5
#define STO_BIT  4
#define AA_BIT   2
#define I2EN_BIT 6
#define SI_BIT   3

//defines for I2CONCLR sfr
#define STAC_BIT  5
#define AAC_BIT   2
#define SIC_BIT   3
#define I2ENC_BIT 6
