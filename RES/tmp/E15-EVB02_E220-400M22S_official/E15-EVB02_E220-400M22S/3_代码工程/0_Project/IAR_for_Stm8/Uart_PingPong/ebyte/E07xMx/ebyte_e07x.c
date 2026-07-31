#include "ebyte_e07x.h"

#define EBYTE_E07X_XOSC     26000000  //26MHz晶振
#define EBYTE_E07X_POW_2_18     268435456 //2的28次方
#define EBYTE_E07X_CAL_BASE     ((double)EBYTE_E07X_POW_2_18) / ((double)EBYTE_E07X_XOSC)


// CC1100 STROBE, CONTROL AND STATUS REGSITER
#define CC1101_IOCFG2       0x00    // GDO2 output pin configuration
#define CC1101_IOCFG1       0x01    // GDO1 output pin configuration
#define CC1101_IOCFG0       0x02    // GDO0 output pin configuration
#define CC1101_FIFOTHR      0x03    // RX FIFO and TX FIFO thresholds
#define CC1101_SYNC1        0x04    // Sync word, high int8e_t
#define CC1101_SYNC0        0x05    // Sync word, low int8e_t
#define CC1101_PKTLEN       0x06    // Packet length
#define CC1101_PKTCTRL1     0x07    // Packet automation control
#define CC1101_PKTCTRL0     0x08    // Packet automation control
#define CC1101_ADDR         0x09    // Device address
#define CC1101_CHANNR       0x0A    // Channel number
#define CC1101_FSCTRL1      0x0B    // Frequency synthesizer control
#define CC1101_FSCTRL0      0x0C    // Frequency synthesizer control
#define CC1101_FREQ2        0x0D    // Frequency control word, high int8e_t
#define CC1101_FREQ1        0x0E    // Frequency control word, middle int8e_t
#define CC1101_FREQ0        0x0F    // Frequency control word, low int8e_t
#define CC1101_MDMCFG4      0x10    // Modem configuration
#define CC1101_MDMCFG3      0x11    // Modem configuration
#define CC1101_MDMCFG2      0x12    // Modem configuration
#define CC1101_MDMCFG1      0x13    // Modem configuration
#define CC1101_MDMCFG0      0x14    // Modem configuration
#define CC1101_DEVIATN      0x15    // Modem deviation setting
#define CC1101_MCSM2        0x16    // Main Radio Control State Machine configuration
#define CC1101_MCSM1        0x17    // Main Radio Control State Machine configuration
#define CC1101_MCSM0        0x18    // Main Radio Control State Machine configuration
#define CC1101_FOCCFG       0x19    // Frequency Offset Compensation configuration
#define CC1101_BSCFG        0x1A    // Bit Synchronization configuration
#define CC1101_AGCCTRL2     0x1B    // AGC control
#define CC1101_AGCCTRL1     0x1C    // AGC control
#define CC1101_AGCCTRL0     0x1D    // AGC control
#define CC1101_WOREVT1      0x1E    // High int8e_t Event 0 timeout
#define CC1101_WOREVT0      0x1F    // Low int8e_t Event 0 timeout
#define CC1101_WORCTRL      0x20    // Wake On Radio control
#define CC1101_FREND1       0x21    // Front end RX configuration
#define CC1101_FREND0       0x22    // Front end TX configuration
#define CC1101_FSCAL3       0x23    // Frequency synthesizer calibration
#define CC1101_FSCAL2       0x24    // Frequency synthesizer calibration
#define CC1101_FSCAL1       0x25    // Frequency synthesizer calibration
#define CC1101_FSCAL0       0x26    // Frequency synthesizer calibration
#define CC1101_RCCTRL1      0x27    // RC oscillator configuration
#define CC1101_RCCTRL0      0x28    // RC oscillator configuration
#define CC1101_FSTEST       0x29    // Frequency synthesizer calibration control
#define CC1101_PTEST        0x2A    // Production test
#define CC1101_AGCTEST      0x2B    // AGC test
#define CC1101_TEST2        0x2C    // Various test settings
#define CC1101_TEST1        0x2D    // Various test settings
#define CC1101_TEST0        0x2E    // Various test settings

// Strobe commands
#define CC1101_SRES         0x30    // Reset chip.
#define CC1101_SFSTXON      0x31    // Enable and calibrate frequency synthesizer (if MCSM0.FS_AUTOCAL=1).
                                    // If in RX/TX: Go to a wait state where only the synthesizer is
                                    // running (for quick RX / TX turnaround).
#define CC1101_SXOFF        0x32    // Turn off crystal oscillator.
#define CC1101_SCAL         0x33    // Calibrate frequency synthesizer and turn it off
                                    // (enables quick start).
#define CC1101_SRX          0x34    // Enable RX. Perform calibration first if coming from IDLE and
                                    // MCSM0.FS_AUTOCAL=1.
#define CC1101_STX          0x35    // In IDLE state: Enable TX. Perform calibration first if
                                    // MCSM0.FS_AUTOCAL=1. If in RX state and CCA is enabled:
                                    // Only go to TX if channel is clear.
#define CC1101_SIDLE        0x36    // Exit RX / TX, turn off frequency synthesizer and exit
                                    // Wake-On-Radio mode if applicable.
#define CC1101_SAFC         0x37    // Perform AFC adjustment of the frequency synthesizer
#define CC1101_SWOR         0x38    // Start automatic RX polling sequence (Wake-on-Radio)
#define CC1101_SPWD         0x39    // Enter power down mode when CSn goes high.
#define CC1101_SFRX         0x3A    // Flush the RX FIFO buffer.
#define CC1101_SFTX         0x3B    // Flush the TX FIFO buffer.
#define CC1101_SWORRST      0x3C    // Reset real time clock.
#define CC1101_SNOP         0x3D    // No operation. May be used to pad strobe commands to two
                                    // int8e_ts for simpler software.
                                    
#define CC1101_PARTNUM      0x30
#define CC1101_VERSION      0x31
#define CC1101_FREQEST      0x32
#define CC1101_LQI          0x33
#define CC1101_RSSI         0x34
#define CC1101_MARCSTATE    0x35
#define CC1101_WORTIME1     0x36
#define CC1101_WORTIME0     0x37
#define CC1101_PKTSTATUS    0x38
#define CC1101_VCO_VC_DAC   0x39
#define CC1101_TXBYTES      0x3A
#define CC1101_RXBYTES      0x3B

#define CC1101_PATABLE      0x3E
#define CC1101_TXFIFO       0x3F
#define CC1101_RXFIFO       0x3F

#define WRITE_BURST     	0x40    // 连续写入
#define READ_SINGLE     	0x80    // 读
#define READ_BURST      	0xC0    // 连续读
#define BYTES_IN_RXFIFO     0x7F    // 接收缓冲区的有效字节数
#define CRC_OK              0x80    // CRC校验通过位标志




/*===========================================================================
----------------------------------macro definitions--------------------------
============================================================================*/
typedef enum { TX_MODE, RX_MODE } TRMODE;
typedef enum { BROAD_ALL, BROAD_NO, BROAD_0, BROAD_0AND255 } ADDR_MODE;
typedef enum { BROADCAST, ADDRESS_CHECK} TX_DATA_MODE;


//10, 7, 5, 0, -5, -10, -15, -20, dbm output power, 0x12 == -30dbm
int8e_t PaTabel[] = { 0xc0, 0xC8, 0x84, 0x60, 0x68, 0x34, 0x1D, 0x0E};

// Sync word qualifier mode = 30/32 sync word bits detected 
// CRC autoflush = false 
// Channel spacing = 199.951172 
// Data format = Normal mode 
// Data rate = 2.00224 
// RX filter BW = 58.035714 
// PA ramping = false 
// Preamble count = 4 
// Whitening = false 
// Address config = No address check 
// Carrier frequency = 400.199890 
// Device address = 0 
// TX power = 10 
// Manchester enable = false 
// CRC enable = true 
// Deviation = 5.157471 
// Packet length mode = Variable packet length mode. Packet length configured by the first byte after sync word 
// Packet length = 255 
// Modulation format = GFSK 
// Base frequency = 399.999939 
// Modulated = true 
// Channel number = 1 
// PA table 
#define PA_TABLE {0xc2,0x00,0x00,0x00,0x00,0x00,0x00,0x00,}


static int8e_t CC1101InitData[22][2]= 
{
  {CC1101_IOCFG0,      0x06},
  {CC1101_FIFOTHR,     0x47},
  {CC1101_PKTCTRL0,    0x01},
  {CC1101_CHANNR,      0x00},
  {CC1101_FSCTRL1,     0x06},
//  {CC1101_FREQ2,       0x10},
//  {CC1101_FREQ1,       0xA7},
//  {CC1101_FREQ0,       0x62},//433Mhz
  {CC1101_FREQ2,       0x23},
  {CC1101_FREQ1,       0x31},
  {CC1101_FREQ0,       0x3B},//915Mhz
  {CC1101_MDMCFG4,     0xF5},
  {CC1101_MDMCFG3,     0x83},
  {CC1101_MDMCFG2,     0x13},//1.2K air rate   RW 58K
  {CC1101_DEVIATN,     0x31},//DEV 14.3K
  {CC1101_MCSM0,       0x18},
  {CC1101_FOCCFG,      0x16},
  {CC1101_WORCTRL,     0xFB},
  {CC1101_FSCAL3,      0xE9},
  {CC1101_FSCAL2,      0x2A},
  {CC1101_FSCAL1,      0x00},
  {CC1101_FSCAL0,      0x1F},
  {CC1101_TEST2,       0x81},
  {CC1101_TEST1,       0x35},
  {CC1101_MCSM1,       0x3B},
};


/*read a byte from the specified register*/
int8e_t CC1101ReadReg( int8e_t addr );

/*Read some bytes from the rigisters continously*/
void CC1101ReadMultiReg( int8e_t addr, int8e_t *buff, int8e_t size );

/*Write a byte to the specified register*/
void CC1101WriteReg( int8e_t addr, int8e_t value );

/*Flush the TX buffer of CC1101*/
void CC1101ClrTXBuff( void );

/*Flush the RX buffer of CC1101*/
void CC1101ClrRXBuff( void );

/*Get received count of CC1101*/
int8e_t CC1101GetRXCnt( void );

/*Reset the CC1101 device*/
void CC1101Reset( void );

/*Write some bytes to the specified register*/
void CC1101WriteMultiReg( int8e_t addr, int8e_t *buff, int8e_t size );


/* !
 * @brief 调制方式
 *
 * @param mod 期望的调制方式 
 *        @arg 0:2-FSK
 *        @arg 1:GFSK
 *        @arg 3:ASK/OOK
 *        @arg 4:4-FSK
 *        @arg 7:MSK
 */
void Ebyte_E07x_SetPackageModulation(uint8e_t mod)
{
    /* 转换位 */
    uint8e_t tmp = (mod<<4) & 0x70;
  
    /* 清除位[6:4] */
    CC1101InitData[10][1] &= 0x8F;
    
    /* 填充 */
    CC1101InitData[10][1] |= tmp;
}

/* !
 * @brief 自由载波频率基准值计算
 *
 * @param frequency 期望的载波频率 Hz
 * @note 必须在以下频段之间( Hz ):
 *        300000000 - 348000000
 *        387000000 - 464000000
 *        779000000 - 928000000
 *       ！！！注意:不同架构处理器计算结果小数部分可能不一致，产生频率偏差
 */
void Ebyte_E07x_SetFrequency( uint32e_t frequency )
{ 
   uint32e_t freq ;
   uint8e_t  freq2,freq1,freq0;
   
   /* 频率控制器字(FREQ)=载波频率 *（2^16)/ 晶振频率   */
   freq = (uint32e_t)(((double)frequency * 65535 )/ ( (double)EBYTE_E07X_XOSC ));
   freq2 = ( uint8e_t )( ( freq >> 16 ) & 0xFF );
   freq1 = ( uint8e_t )( ( freq >> 8 ) & 0xFF );
   freq0 = ( uint8e_t )(  freq  & 0xFF );
   
   /* 填充初始化参数数组中的频率部分 等待后续统一写入  */
   CC1101InitData[5][1] = freq2;
   CC1101InitData[6][1] = freq1;
   CC1101InitData[7][1] = freq0;
}

/* !
 * @brief 自由数据速率基准值计算
 *
 * @param datarate 期望的数据速率
 * @note 建议在以下速率之间:
 *        300 (0.3K) - 250000000 (250K)
 *        实测和官方计算器结果一致
 */
void Ebyte_E07x_SetDataRate( uint32e_t datarate )
{
    uint8e_t  date_m ;
    uint16e_t date_e ;
    uint32e_t date_e_sum = 1,temp;
    
    /* 中间公式换算 (256+DRATE_M)*2^DRATE_E=datarate*2^28/晶振频率  */
    uint32e_t calculation = (uint32e_t)( datarate * EBYTE_E07X_CAL_BASE);
    
    /* 逐次逼近匹配 DRATE_E */
    for( date_e=0 ; date_e<=0xFF;date_e++ )
    {
       if(date_e==0)
       {
          date_e_sum =1;//2^0
       }
       else
       {
          date_e_sum *= 2;//2^DRATE_E 
       }
       
       temp = calculation/date_e_sum; // 结果必须在 [256 ,256+DRATE_M]之间
       if(  temp>=256 && temp<=511 )
       {
          date_m = temp - 256;//得到DRATE_M
          break;
       }
    }
    
    /* 填充初始化参数数组中的数据速率部分 等待后续统一写入  */
    if ( date_e<256 )
    {
       CC1101InitData[8][1] &= 0xF0;
       CC1101InitData[8][1] |= date_e;
       CC1101InitData[9][1] = date_m;    
    }
    
}

/* !
 * @brief 自由频宽基准值计算
 *
 * @param bandwidth 期望的接收频宽 (Hz)
 * @note 实测和官方计算器结果一致 默认最低58.035714
 *       注意：芯片实际只能配置为固定几个频宽，输入的数值会被向上转化接近到如下固定频宽：
 *        58.035714 KHz 
 *        67.708333 KHz 
 *        81.250000 KHz
 *       101.562500 KHz 
 *       116.071429 KHz
 *       135.416667 KHz
 *       162.500000 KHz
 *       203.125000 KHz
 *       232.142857 KHz
 *       270.833333 KHz
 *       325.000000 KHz
 *       406.250000 KHz
 *       464.285714 KHz
 *       541.666667 KHz
 *       650.000000 KHz
 *       812.500000 KHz
 */
void Ebyte_E07x_SetChannelBandwidth( uint32e_t bandwidth )
{
    uint8e_t  chanbw_m ,chanbw_e,mask;

    uint32e_t chanbw_e_sum = 1,temp;
    
    /* 中间公式换算 (4+CHANBW_M)*2^CHANBW_E=晶振频率/(8*bandwidth)  */
    uint32e_t calculation = (uint32e_t)( EBYTE_E07X_XOSC/(8 * bandwidth));    
    
    /* 逐次逼近匹配 CHANBW_E */
    for( chanbw_e=0 ; chanbw_e<=3;chanbw_e++ )
    {
       if(chanbw_e==0)
       {
          chanbw_e_sum = 1;//2^0
       }
       else
       {
          chanbw_e_sum *= 2;//2^CHANBW_E
       }
        
       temp = calculation/chanbw_e_sum; 
       if(  temp>=4 && temp<=7 )
       {
          chanbw_m = temp - 4;//得到CHANBW_M
          break;
       }
    }    
    
    /* 填充初始化参数数组中的频宽部分 等待后续统一写入  */
    if( chanbw_e<=3 )
    {
        mask = ((uint8e_t)((chanbw_e<<6)|(chanbw_m<<4))) & 0xF0;
        CC1101InitData[8][1] &= 0x0F;
        CC1101InitData[8][1] |= mask;
    }
    
}


/*
================================================================================
Function : CC1101WriteCmd( )
    Write a command byte to the device
INPUT    : command, the byte you want to write
OUTPUT   : None
================================================================================
*/
void CC1101WriteCmd( int8e_t command )
{
    Ebyte_Port_SpiCsIoControl(0);
    Ebyte_Port_SpiTransmitAndReceivce( command );
    Ebyte_Port_SpiCsIoControl(1);
}

/*
================================================================================
Function : CC1101WORInit( )
    Initialize the WOR function of CC1101
INPUT    : None
OUTPUT   : None
================================================================================
*/
void  CC1101WORInit( void )
{

    CC1101WriteReg(CC1101_MCSM0,0x18);
    CC1101WriteReg(CC1101_WORCTRL,0x78); //Wake On Radio Control
    CC1101WriteReg(CC1101_MCSM2,0x00);
    CC1101WriteReg(CC1101_WOREVT1,0x8C);
    CC1101WriteReg(CC1101_WOREVT0,0xA0);
	
    CC1101WriteCmd( CC1101_SWORRST );
}
/*
================================================================================
Function : CC1101ReadReg( )
    read a byte from the specified register
INPUT    : addr, The address of the register
OUTPUT   : the byte read from the rigister
================================================================================
*/
int8e_t CC1101ReadReg( int8e_t addr )
{
    int8e_t i;
    Ebyte_Port_SpiCsIoControl(0);
    Ebyte_Port_SpiTransmitAndReceivce( addr | READ_SINGLE);
    i = Ebyte_Port_SpiTransmitAndReceivce( 0xFF );
    Ebyte_Port_SpiCsIoControl(1);
    return i;
}
/*
================================================================================
Function : CC1101ReadMultiReg( )
    Read some bytes from the rigisters continously
INPUT    : addr, The address of the register
           buff, The buffer stores the data
           size, How many bytes should be read
OUTPUT   : None
================================================================================
*/
void CC1101ReadMultiReg( int8e_t addr, int8e_t *buff, int8e_t size )
{
    int8e_t i, j;
    Ebyte_Port_SpiCsIoControl(0);
    Ebyte_Port_SpiTransmitAndReceivce( addr | READ_BURST);
    for( i = 0; i < size; i ++ )
    {
        for( j = 0; j < 20; j ++ );
        *( buff + i ) = Ebyte_Port_SpiTransmitAndReceivce( 0xFF );
    }
    Ebyte_Port_SpiCsIoControl(1);
}
/*
================================================================================
Function : CC1101ReadStatus( )
    Read a status register
INPUT    : addr, The address of the register
OUTPUT   : the value read from the status register
================================================================================
*/
int8e_t CC1101ReadStatus( int8e_t addr )
{
    int8e_t i;
    Ebyte_Port_SpiCsIoControl(0);
    Ebyte_Port_SpiTransmitAndReceivce( addr | READ_BURST);
    i = Ebyte_Port_SpiTransmitAndReceivce( 0xFF );
    Ebyte_Port_SpiCsIoControl(1);
    return i;
}



/*
================================================================================
Function : CC1101SetTRMode( )
    Set the device as TX mode or RX mode
INPUT    : mode selection
OUTPUT   : None
================================================================================
*/
void CC1101SetTRMode( TRMODE mode )
{
    if( mode == TX_MODE )
    {
        CC1101WriteReg(CC1101_IOCFG0,0x46);
        CC1101WriteCmd( CC1101_STX );
    }
    else if( mode == RX_MODE )
    {
        CC1101WriteReg(CC1101_IOCFG0,0x46);
        CC1101WriteCmd( CC1101_SRX );
    }
}
/*
================================================================================
Function : CC1101WriteReg( )
    Write a byte to the specified register
INPUT    : addr, The address of the register
           value, the byte you want to write
OUTPUT   : None
================================================================================
*/
void CC1101WriteReg( int8e_t addr, int8e_t value )
{
    Ebyte_Port_SpiCsIoControl(0);
    Ebyte_Port_SpiTransmitAndReceivce( addr );
    Ebyte_Port_SpiTransmitAndReceivce( value );
    Ebyte_Port_SpiCsIoControl(1);
}
/*
================================================================================
Function : CC1101WriteMultiReg( )
    Write some bytes to the specified register
INPUT    : addr, The address of the register
           buff, a buffer stores the values
           size, How many byte should be written
OUTPUT   : None
================================================================================
*/
void CC1101WriteMultiReg( int8e_t addr, int8e_t *buff, int8e_t size )
{
    int8e_t i;
    Ebyte_Port_SpiCsIoControl(0);
    Ebyte_Port_SpiTransmitAndReceivce( addr | WRITE_BURST );
    for( i = 0; i < size; i ++ )
    {
        Ebyte_Port_SpiTransmitAndReceivce( *( buff + i ) );
    }
    Ebyte_Port_SpiCsIoControl(1);
}

/*
================================================================================
Function : CC1101Reset( )
    Reset the CC1101 device
INPUT    : None
OUTPUT   : None
================================================================================
*/
void CC1101Reset( void )
{
    Ebyte_Port_SpiCsIoControl(1);
    Ebyte_Port_SpiCsIoControl(0);
    Ebyte_Port_DelayMs(1);
    Ebyte_Port_SpiCsIoControl(1);
    Ebyte_Port_DelayMs(1);
    CC1101WriteCmd( CC1101_SRES );
}
/*
================================================================================
Function : CC1101SetIdle( )
    Set the CC1101 into IDLE mode
INPUT    : None
OUTPUT   : None
================================================================================
*/
void CC1101SetIdle( void )
{
    CC1101WriteCmd(CC1101_SIDLE);
}
/*
================================================================================
Function : CC1101ClrTXBuff( )
    Flush the TX buffer of CC1101
INPUT    : None
OUTPUT   : None
================================================================================
*/
void CC1101ClrTXBuff( void )
{
    CC1101SetIdle();//MUST BE IDLE MODE
    CC1101WriteCmd( CC1101_SFTX );
}
/*
================================================================================
Function : CC1101ClrRXBuff( )
    Flush the RX buffer of CC1101
INPUT    : None
OUTPUT   : None
================================================================================
*/
void CC1101ClrRXBuff( void )
{
    CC1101SetIdle();//MUST BE IDLE MODE
    CC1101WriteCmd( CC1101_SFRX );
}
/*
================================================================================
Function : CC1101SendPacket( )
    Send a packet
INPUT    : txbuffer, The buffer stores data to be sent
           size, How many bytes should be sent
           mode, Broadcast or address check packet
OUTPUT   : None
================================================================================
*/
void CC1101SendPacket( int8e_t *txbuffer, int8e_t size, TX_DATA_MODE mode )
{
    int8e_t address;
    if( mode == BROADCAST )             { address = 0; }
    else if( mode == ADDRESS_CHECK )    { address = CC1101ReadReg( CC1101_ADDR ); }

    CC1101ClrTXBuff( );
    
    if( ( CC1101ReadReg( CC1101_PKTCTRL1 ) & ~0x03 ) != 0 )
    {
        CC1101WriteReg( CC1101_TXFIFO, size + 1 );
        CC1101WriteReg( CC1101_TXFIFO, address );
    }
    else
    {
        CC1101WriteReg( CC1101_TXFIFO, size );
    }

    CC1101WriteMultiReg( CC1101_TXFIFO, txbuffer, size );
    CC1101SetTRMode( TX_MODE );
    
    while( Ebyte_Port_Gdo0IoRead() != 0 );
    while( Ebyte_Port_Gdo0IoRead() == 0 );

    CC1101ClrTXBuff( );
}
/*
================================================================================
Function : CC1101GetRXCnt( )
    Get received count of CC1101
INPUT    : None
OUTPUT   : How many bytes hae been received
================================================================================
*/
int8e_t CC1101GetRXCnt( void )
{
    return ( CC1101ReadStatus( CC1101_RXBYTES )  & BYTES_IN_RXFIFO );
}
/*
================================================================================
Function : CC1101SetAddress( )
    Set the address and address mode of the CC1101
INPUT    : address, The address byte
           AddressMode, the address check mode
OUTPUT   : None
================================================================================
*/
void CC1101SetAddress( int8e_t address, ADDR_MODE AddressMode)
{
    int8e_t btmp = CC1101ReadReg( CC1101_PKTCTRL1 ) & ~0x03;
    CC1101WriteReg(CC1101_ADDR, address);
    if     ( AddressMode == BROAD_ALL )     {}
    else if( AddressMode == BROAD_NO  )     { btmp |= 0x01; }
    else if( AddressMode == BROAD_0   )     { btmp |= 0x02; }
    else if( AddressMode == BROAD_0AND255 ) { btmp |= 0x03; }   
}
/*
================================================================================
Function : CC1101SetSYNC( )
    Set the SYNC bytes of the CC1101
INPUT    : sync, 16bit sync 
OUTPUT   : None
================================================================================
*/
void CC1101SetSYNC( int16e_t sync )
{
    CC1101WriteReg(CC1101_SYNC1, 0xFF & ( sync>>8 ) );
    CC1101WriteReg(CC1101_SYNC0, 0xFF & sync ); 
}
/*
================================================================================
Function : CC1101RecPacket( )
    Receive a packet
INPUT    : rxBuffer, A buffer store the received data
OUTPUT   : 1:received count, 0:no data
================================================================================
*/
int8e_t CC1101RecPacket( int8e_t *rxBuffer )
{
    int8e_t status[2];
    int8e_t pktLen;

    if ( CC1101GetRXCnt( ) != 0 )
    {
        pktLen = CC1101ReadReg(CC1101_RXFIFO);           // Read length byte
        if( ( CC1101ReadReg( CC1101_PKTCTRL1 ) & ~0x03 ) != 0 )
        {
            CC1101ReadReg(CC1101_RXFIFO);
        }
        if( pktLen == 0 )           { return 0; }
        else                        { pktLen --; }
        CC1101ReadMultiReg(CC1101_RXFIFO, rxBuffer, pktLen); // Pull data
        CC1101ReadMultiReg(CC1101_RXFIFO, status, 2);   // Read  status bytes

        CC1101ClrRXBuff( );

        if( status[1] & CRC_OK ) {   return pktLen; }
        else                     {   return 0; }
    }
    else   {  return 0; }                               // Error
}
/*
================================================================================
Function : CC1101Init( )
    Initialize the CC1101, User can modify it
INPUT    : None
OUTPUT   : None
================================================================================
*/
void Ebyte_E07x_Init( void )
{
    int8e_t i;

    CC1101Reset( );    
    
    /* 设置载波频率 */
    Ebyte_E07x_SetFrequency( RF_FREQUENCY_START );
    
    Ebyte_E07x_SetDataRate( 10000 );
    
    Ebyte_E07x_SetChannelBandwidth(100000);
    
    for( i = 0; i < 22; i++ )
    {
        CC1101WriteReg( CC1101InitData[i][0], CC1101InitData[i][1] );
    }
    CC1101SetAddress( 0x05, BROAD_0AND255 );
    CC1101SetSYNC( 0x8799 );
    CC1101WriteReg(CC1101_MDMCFG1,   0x72); //Modem Configuration

    CC1101WriteMultiReg(CC1101_PATABLE, PaTabel, 8 );

    CC1101ReadStatus( CC1101_PARTNUM );//for test, must be 0x80
    CC1101ReadStatus( CC1101_VERSION );//for test, refer to the datasheet
}


void Ebyte_E07x_IntOrPollTask(void)
{
    int8e_t length=0, recv_buffer[64]={0};
    uint16e_t irqStatus = 0x0002;
    
    CC1101SetTRMode(RX_MODE);           // 进入接收模式
    
    if (0 == Ebyte_Port_Gdo0IoRead())             // 检测无线模块是否产生接收中断 
    {
        while (Ebyte_Port_Gdo0IoRead() == 0);

        // 读取接收到的数据长度和数据内容
        length = CC1101RecPacket(recv_buffer);
       
        Ebyte_Port_ReceiveCallback( irqStatus , (uint8e_t*)recv_buffer, (uint8e_t)length );
    }
}

void Ebyte_E07x_SendPayload( uint8e_t *payload, uint8e_t size, uint32e_t timeout )
{
    CC1101SendPacket( (int8e_t*)payload, size ,ADDRESS_CHECK);

}

void Ebyte_E07x_SetRx( uint32e_t timeout )
{
    CC1101SetTRMode(RX_MODE);                           // 进入接收模式
}
