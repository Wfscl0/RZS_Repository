#ifndef _TSMaster_MP_H
#define _TSMaster_MP_H

/*
  Note: 
  [1] Definitions of TCAN, TCANFD and TLIN can be found in this header
  [2] use "log", "test_log", "test_log_ok", "test_log_nok" instead of "printf"
  [3] channel index is always starting from 0
  [4] for error codes of API, please see {TSMaster installation}\bin\Help\TSMaster Error Codes.xlsx
*/

#include <math.h>
#include <stdio.h>

#define CH1 0
#define CH2 1
#define CH3 2
#define CH4 3
#define CH5 4
#define CH6 5
#define CH7 6
#define CH8 7
#define CH9 8
#define CH10 9
#define CH11 10
#define CH12 11
#define CH13 12
#define CH14 13
#define CH15 14
#define CH16 15
#define CH17 16
#define CH18 17
#define CH19 18
#define CH20 19
#define CH21 20
#define CH22 21
#define CH23 22
#define CH24 23
#define CH25 24
#define CH26 25
#define CH27 26
#define CH28 27
#define CH29 28
#define CH30 29
#define CH31 30
#define CH32 31

typedef enum {lvlError = 1, lvlWarning = 2, lvlOK = 3, lvlHint = 4, lvlInfo = 5, lvlVerbose = 6} TLogLevel;

// basic var type definition
typedef unsigned __int8 u8;
typedef signed __int8 s8;
typedef unsigned __int16 u16;
typedef signed __int16 s16;
typedef unsigned __int32 u32;
typedef signed __int32 s32;
typedef unsigned __int64 u64;
typedef signed __int64 s64;
// pointer definition
typedef unsigned __int8* pu8;
typedef signed __int8* ps8;
typedef unsigned __int16* pu16;
typedef signed __int16* ps16;
typedef unsigned __int32* pu32;
typedef signed __int32* ps32;
typedef signed __int32** pps32;
typedef unsigned __int64* pu64;
typedef signed __int64* ps64;
typedef float* pfloat;
typedef double* pdouble;
typedef char* pchar;

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define DLLEXPORT extern "C" _declspec(dllexport)

#pragma pack(push)
#pragma pack(1)

// CAN definitions
#define MASK_CANProp_DIR_TX 0x01
#define MASK_CANProp_REMOTE 0x02
#define MASK_CANProp_EXTEND 0x04
#define MASK_CANProp_ERROR  0x80
#define MASK_CANProp_LOGGED 0x60

// CAN FD message properties
#define MASK_CANFDProp_IS_FD 0x01
#define MASK_CANFDProp_IS_EDL MASK_CANFDProp_IS_FD
#define MASK_CANFDProp_IS_BRS 0x02
#define MASK_CANFDProp_IS_ESI 0x04

// LIN message properties
#define MASK_LINProp_DIR_TX         0x01
#define MASK_LINProp_SEND_BREAK     0x02
#define MASK_LINProp_RECEIVED_BREAK 0x04
#define MASK_LINProp_SEND_SYNC      0x80
#define MASK_LINProp_RECEIVED_SYNC  0x10

// C++ property definition
#define PROPERTY(t,n)  __declspec( property ( put = property__set_##n, get = property__get_##n ) ) t n;\
    typedef t property__tmp_type_##n
#define READONLY_PROPERTY(t,n) __declspec( property (get = property__get_##n) ) t n;\
    typedef t property__tmp_type_##n
#define WRITEONLY_PROPERTY(t,n) __declspec( property (put = property__set_##n) ) t n;\
    typedef t property__tmp_type_##n
#define GET(n) property__tmp_type_##n property__get_##n() 
#define SET(n) void property__set_##n(const property__tmp_type_##n& value)   

const u8 DLC_DATA_BYTE_CNT[16] = {
    0, 1, 2, 3, 4, 5, 6, 7,
    8, 12, 16, 20, 24, 32, 48, 64
};
        
// CAN frame type ================================================
typedef struct _TCAN{
    u8 FIdxChn;
    u8 FProperties;
    u8 FDLC;
    u8 FReserved;
    s32 FIdentifier;
    s64 FTimeUs;
    u8  FData[8];
    // is_tx -----------------------------------------------------
    PROPERTY(bool, is_tx);
    GET(is_tx)  
    { 
        return (FProperties & MASK_CANProp_DIR_TX) != 0;
    }
    SET(is_tx)
    {
        if (value) {
            FProperties = FProperties | MASK_CANProp_DIR_TX;
        } else {
            FProperties = FProperties & (~MASK_CANProp_DIR_TX);
        }
    }
    // is_data ----------------------------------------------------
    PROPERTY(bool, is_data);
    GET(is_data) 
    { 
        return (FProperties & MASK_CANProp_REMOTE) == 0;
    }
    SET(is_data)
    {
        if (value) {
            FProperties = FProperties & (~MASK_CANProp_REMOTE);
        } else {
            FProperties = FProperties | MASK_CANProp_REMOTE;
        }
    }
    // is_std -----------------------------------------------------
    PROPERTY(bool, is_std);
    GET(is_std) 
    { 
        return (FProperties & MASK_CANProp_EXTEND) == 0;
    }
    SET(is_std)
    {
        if (value) {
            FProperties = FProperties & (~MASK_CANProp_EXTEND);
        } else {
            FProperties = FProperties | MASK_CANProp_EXTEND;
        }
    }
    // is_err ----------------------------------------------------
    PROPERTY(bool, is_err);
    GET(is_err) 
    { 
        return (FProperties & MASK_CANProp_ERROR) != 0;
    }
    SET(is_err)
    {
        if (value) {
            FProperties = FProperties & (~MASK_CANProp_ERROR);
        } else {
            FProperties = FProperties | MASK_CANProp_ERROR;
        }
    }
    // load data bytes -------------------------------------------
    void load_data(u8* a) {
        for (u32 i = 0; i < 8; i++) {
            FData[i] = *a++;
        }
    }
    void set_data(const u8 d0, const u8 d1, const u8 d2, const u8 d3, const u8 d4, const u8 d5, const u8 d6, const u8 d7){
        FData[0] = d0;
        FData[1] = d1;
        FData[2] = d2;
        FData[3] = d3;
        FData[4] = d4;
        FData[5] = d5;
        FData[6] = d6;
        FData[7] = d7;
    }
    // initialize with standard identifier -----------------------
    void init_w_std_id(s32 AId, s32 ADLC) {
        FIdxChn = 0;
        FIdentifier = AId;
        FDLC = ADLC;
        FReserved = 0;
        FProperties = 0;
        is_tx = false;
        is_std = true;
        is_data = true;
        *(u64*)(&FData[0]) = 0;
        FTimeUs = 0;
    }
    // initialize with extended identifier -----------------------
    void init_w_ext_id(s32 AId, s32 ADLC) {
        FIdxChn = 0;
        FIdentifier = AId;
        FDLC = ADLC;
        FReserved = 0;
        FProperties = 0;
        is_tx = false;
        is_std = false;
        is_data = true;
        *(u64*)(&FData[0]) = 0;
        FTimeUs = 0;
    }
} TCAN, *PCAN;

// CAN FD frame type =============================================
typedef struct _TCANFD{
    u8 FIdxChn;
    u8 FProperties;
    u8 FDLC;
    u8 FFDProperties;
    s32 FIdentifier;
    s64 FTimeUs;
    u8  FData[64];
    // is_tx -----------------------------------------------------
    PROPERTY(bool, is_tx);
    GET(is_tx)  
    { 
        return (FProperties & MASK_CANProp_DIR_TX) != 0;
    }
    SET(is_tx)
    {
        if (value) {
            FProperties = FProperties | MASK_CANProp_DIR_TX;
        } else {
            FProperties = FProperties & (~MASK_CANProp_DIR_TX);
        }
    }
    // is_data ---------------------------------------------------
    PROPERTY(bool, is_data);
    GET(is_data) 
    { 
        return (FProperties & MASK_CANProp_REMOTE) == 0;
    }
    SET(is_data)
    {
        if (value) {
            FProperties = FProperties & (~MASK_CANProp_REMOTE);
        } else {
            FProperties = FProperties | MASK_CANProp_REMOTE;
        }
    }
    // is_std ----------------------------------------------------
    PROPERTY(bool, is_std);
    GET(is_std) 
    { 
        return (FProperties & MASK_CANProp_EXTEND) == 0;
    }
    SET(is_std)
    {
        if (value) {
            FProperties = FProperties & (~MASK_CANProp_EXTEND);
        } else {
            FProperties = FProperties | MASK_CANProp_EXTEND;
        }
    }
    // is_err ----------------------------------------------------
    PROPERTY(bool, is_err);
    GET(is_err) 
    { 
        return (FProperties & MASK_CANProp_ERROR) != 0;
    }
    SET(is_err)
    {
        if (value) {
            FProperties = FProperties & (~MASK_CANProp_ERROR);
        } else {
            FProperties = FProperties | MASK_CANProp_ERROR;
        }
    }
    // is_edl ----------------------------------------------------
    PROPERTY(bool, is_edl);
    GET(is_edl) 
    { 
        return (FFDProperties & MASK_CANFDProp_IS_FD) != 0;
    }
    SET(is_edl)
    {
        if (value) {
            FFDProperties = FFDProperties | MASK_CANFDProp_IS_FD;
        } else {
            FFDProperties = FFDProperties & (~MASK_CANFDProp_IS_FD);
        }
    }
    // is_brs ----------------------------------------------------
    PROPERTY(bool, is_brs);
    GET(is_brs) 
    { 
        return (FFDProperties & MASK_CANFDProp_IS_BRS) != 0;
    }
    SET(is_brs)
    {
        if (value) {
            FFDProperties = FFDProperties | MASK_CANFDProp_IS_BRS;
        } else {
            FFDProperties = FFDProperties & (~MASK_CANFDProp_IS_BRS);
        }
    }
    // is_esi ----------------------------------------------------
    PROPERTY(bool, is_esi);
    GET(is_esi) 
    { 
        return (FFDProperties & MASK_CANFDProp_IS_ESI) != 0;
    }
    SET(is_esi)
    {
        if (value) {
            FFDProperties = FFDProperties | MASK_CANFDProp_IS_ESI;
        } else {
            FFDProperties = FFDProperties & (~MASK_CANFDProp_IS_ESI);
        }
    }    
    // load data bytes -------------------------------------------
    void load_data(u8* a) {
        for (u32 i = 0; i < 64; i++) {
            FData[i] = *a++;
        }
    }
    // initialize with standard identifier -----------------------
    void init_w_std_id(s32 AId, s32 ADLC) {
        s32 i;
        FIdxChn = 0;
        FIdentifier = AId;
        FDLC = ADLC;
        FProperties = 0;
        FFDProperties = MASK_CANFDProp_IS_FD;
        is_tx = false;
        is_std = true;
        is_data = true;
        for (i = 0; i < 64; i++) FData[i] = 0;
        FTimeUs = 0;
    }
    // initialize with extended identifier -----------------------
    void init_w_ext_id(s32 AId, s32 ADLC) {
        s32 i;
        FIdxChn = 0;
        FIdentifier = AId;
        FDLC = ADLC;
        FFDProperties = MASK_CANFDProp_IS_FD;
        FProperties = 0;
        is_tx = false;
        is_std = false;
        is_data = true;
        for (i = 0; i < 64; i++) FData[i] = 0;
        FTimeUs = 0;
    }
    // get fd data length ----------------------------------------
    s32 get_data_length() {
        s32 l = MIN(FDLC, 15);
        l = MAX(l, 0);
        return DLC_DATA_BYTE_CNT[l];
    }
    // to CAN struct ---------------------------------------------
    TCAN to_tcan(void){
        return *(TCAN*)(&FIdxChn);
    }
} TCANFD, *PCANFD;

// LIN frame type ================================================
typedef struct _LIN {
    u8  FIdxChn;
    u8  FErrStatus;
    u8  FProperties;
    u8  FDLC;
    u8  FIdentifier;
    u8  FChecksum;
    u8  FStatus;
    s64 FTimeUs;
    u8  FData[8];
    // is_tx -----------------------------------------------------
    PROPERTY(bool, is_tx);
    GET(is_tx)
    {
        return (FProperties & MASK_LINProp_DIR_TX) != 0;
    }
    SET(is_tx)
    {
        if (value) {
            FProperties = FProperties | MASK_LINProp_DIR_TX;
        }
        else {
            FProperties = FProperties & (~MASK_LINProp_DIR_TX);
        }
    }
    // load data bytes -------------------------------------------
    void load_data(u8* a) {
        for (u32 i = 0; i < 8; i++) {
            FData[i] = *a++;
        }
    }
    // initialize with identifier --------------------------------
    void init_w_id(const s32 AId, const s32 ADLC) {
        FIdxChn = 0;
        FErrStatus = 0;
        FProperties = 0;
        FDLC = ADLC;
        FIdentifier = AId;
        *(__int64*)(&FData[0]) = 0;
        FChecksum = 0;
        FStatus = 0;
        FTimeUs = 0;
    }
}TLIN, *PLIN;

// Generic definitions ===========================================
typedef void (__stdcall *TProcedure)(const void* AObj);
typedef void (__stdcall *TProcedureSetInt)(const void* AObj, const s32 AValue);
typedef s32 (__stdcall *TIntFunction)(const void* AObj);
typedef void (__stdcall *TProcedureSetDouble)(const void* AObj, const double AValue);
typedef double (__stdcall *TDoubleFunction)(const void* AObj);
typedef void (__stdcall *TProcedureSetString)(const void* AObj, const char* AValue);
typedef char* (__stdcall *TStringFunction)(const void* AObj);
typedef void (__stdcall *TProcedureSetCAN)(const void* AObj, const PCAN AValue);
typedef TCAN (__stdcall *TTCANFunction)(const void* AObj);
typedef void (__stdcall *TProcedureSetCANFD)(const void* AObj, const PCANFD AValue);
typedef TCANFD (__stdcall *TTCANFDFunction)(const void* AObj);
typedef void (__stdcall *TProcedureSetLIN)(const void* AObj, const PLIN AValue);
typedef TLIN (__stdcall *TTLINFunction)(const void* AObj);
typedef void(__stdcall* TWriteAPIDocumentFunc)(const void* AOpaque, const char* AName, const char* AGroup, const char* ADesc, const char* AExample, const s32 AParaCount);
typedef void(__stdcall* TWriteAPIParaFunc)(const void* AOpaque, const s32 AIdx, const char* AAPIName, const char* AParaName, const bool AIsConst, const char* AParaType, const char* ADesc);                            

// TSMaster variable =============================================
typedef struct _TMPVarInt {
    void* FObj;
    TIntFunction internal_get;
    TProcedureSetInt internal_set;
    s32 get(void) {
        return internal_get(FObj);
    }
    void set(const s32 AValue) {
        internal_set(FObj, AValue);
    }
}TMPVarInt;

typedef struct _TMPVarDouble {
    void* FObj;
    TDoubleFunction internal_get;
    TProcedureSetDouble internal_set;
    double get(void) {
        return internal_get(FObj);
    }
    void set(const double AValue) {
        internal_set(FObj, AValue);
    }
}TMPVarDouble;

typedef struct _TMPVarString {
    void* FObj;
    TStringFunction internal_get;
    TProcedureSetString internal_set;
    char* get(void) {
        return internal_get(FObj);
    }
    void set(const char* AValue) {
        internal_set(FObj, AValue);
    }
}TMPVarString;

typedef struct _TMPVarCAN {
    void* FObj;
    TTCANFunction internal_get;
    TProcedureSetCAN internal_set;
    TCAN get(void) {
        return internal_get(FObj);
    }
    void set(TCAN AValue) {
        internal_set(FObj, &AValue);
    }
}TMPVarCAN;

typedef struct _TMPVarCANFD {
    void* FObj;
    TTCANFDFunction internal_get;
    TProcedureSetCANFD internal_set;
    TCANFD get(void) {
        return internal_get(FObj);
    }
    void set(TCANFD AValue) {
        internal_set(FObj, &AValue);
    }
}TMPVarCANFD;

typedef struct _TMPVarLIN {
    void* FObj;
    TTLINFunction internal_get;
    TProcedureSetLIN internal_set;
    TLIN get(void) {
        return internal_get(FObj);
    }
    void set(TLIN AValue) {
        internal_set(FObj, &AValue);
    }
}TMPVarLIN;

// TSMaster timer ================================================
typedef struct _TMPTimerMS {
    void* FObj;
    TProcedure internal_start;
    TProcedure internal_stop;
    TProcedureSetInt internal_set_interval;
    TIntFunction internal_get_interval;
    void start(void) {
        internal_start(FObj);
    }
    void stop(void) {
        internal_stop(FObj);
    }
    void set_interval(const s32 AInterval) {
        internal_set_interval(FObj, AInterval);
    }
    s32 get_interval(void) {
        return internal_get_interval(FObj);
    }
}TMPTimerMS;

// TSMaster application definition ===============================
#define APP_DEVICE_NAME_LENGTH 32
typedef enum {
    BUS_UNKNOWN_TYPE           = 0, 
    TS_TCP_DEVICE              = 1, 
    XL_USB_DEVICE              = 2, 
    TS_USB_DEVICE              = 3, 
    PEAK_USB_DEVICE            = 4,
    KVASER_USB_DEVICE          = 5,
    ZLG_USB_DEVICE             = 6,
    ICS_USB_DEVICE             = 7,
    TS_TC1005_DEVICE           = 8
} TLIBBusToolDeviceType;
typedef enum {APP_CAN = 0, APP_LIN = 1} TLIBApplicationChannelType;
typedef enum {
    cbsBusLoad = 0, cbsPeakLoad, cbsFpsStdData, cbsAllStdData,
    cbsFpsExtData, cbsAllExtData, cbsFpsStdRemote, cbsAllStdRemote,
    cbsFpsExtRemote, cbsAllExtRemote, cbsFpsErrorFrame, cbsAllErrorFrame    
} TLIBCANBusStatistics;
struct _TLIBTSMapping {
    char                       FAppName[APP_DEVICE_NAME_LENGTH];
    s32                        FAppChannelIndex;
    TLIBApplicationChannelType FAppChannelType;
    TLIBBusToolDeviceType      FHWDeviceType;
    s32                        FHWIndex;
    s32                        FHWChannelIndex;
    s32                        FHWDeviceSubType;
    char                       FHWDeviceName[APP_DEVICE_NAME_LENGTH];
    bool                       FMappingDisabled;
    void init(void) {
        s32 i;
        for (i = 0; i < APP_DEVICE_NAME_LENGTH; i++) {
            FAppName[i] = 0;
            FHWDeviceName[i] = 0;
        }
        FAppChannelIndex = 0;
        FAppChannelType = APP_CAN;
        FHWDeviceType = TS_USB_DEVICE;
        FHWIndex = 0;
        FHWChannelIndex = 0;
        FHWDeviceSubType = 0;
        FMappingDisabled = false;
    }
};
typedef struct _TLIBTSMapping TLIBTSMapping, * PLIBTSMapping;
// system var def
typedef enum {svtInt32 = 0, svtUInt32, svtInt64, svtUInt64, svtUInt8Array,
    svtInt32Array, svtInt64Array, svtDouble, svtDoubleArray, svtString} TLIBSystemVarType;
typedef struct {
    char              FName[APP_DEVICE_NAME_LENGTH];
    char              FCategory[APP_DEVICE_NAME_LENGTH];
    char              FComment[APP_DEVICE_NAME_LENGTH];
    TLIBSystemVarType FDataType;
    bool              FIsReadOnly;
    double            FValueMin;
    double            FValueMax;
} TLIBSystemVarDef, *PLIBSystemVarDef;
typedef enum {fdtCAN = 0, fdtISOCANFD = 1, fdtNonISOCANFD = 2} TCANFDControllerType;
typedef enum {fdmNormal = 0, fdmACKOff = 1, fdmRestricted = 2} TCANFDControllerMode;
// log def
typedef enum {ortImmediately = 0, ortAsLog = 1, ortDelayed = 2} TLIBOnlineReplayTimingMode;
typedef enum {orsNotStarted = 0, orsRunning = 1, orsPaused = 2, orsCompleted = 3, orsTerminated = 4} TLIBOnlineReplayStatus;
typedef enum _TSupportedBLFObjType {sotCAN = 0, sotLIN = 1, sotCANFD = 2, sotRealtimeComment = 3} TSupportedBLFObjType;
// database utilities
typedef struct {
    u8     FCANSgnType; // 0 - Unsigned, 1 - Signed, 2 - Single 32, 3 - Double 64
    bool   FIsIntel;
    s32    FStartBit;
    s32    FLength;    
    double FFactor;
    double FOffset;    
} TCANSignal, *PCANSignal;
#define CANMsgDecl(typ, name, chn, prop, dlc, id) const typ name = {{chn, prop, dlc, 0, id, 0, {0}}};
#define CANFDMsgDecl(typ, name, chn, prop, dlc, id) const typ name = {{chn, prop, dlc, 1, id, 0, {0}}};
#define LINMsgDecl(typ, name, chn, prop, dlc, id) const typ name = {{chn, 0, prop, dlc, id, 0, 0, 0, {0}}};
#define CANSgnDecl(name, typ, isIntel, startBit, len, factor, offset) const TCANSignal name = {typ, isIntel, startBit, len, factor, offset};
typedef enum {rivUseDB = 0, rivUseLast, rivUse0} TLIBRBSInitValueOptions;
typedef void(__stdcall* TProgressCallback)(const double AProgress100);
typedef bool(__stdcall* TCheckResultCallback)(void);
// Realtime comment
typedef struct _realtime_comment_t {
	s64 FTimeUs;
	s32 FEventType;
	u32 FCapacity;
	char* FComment;
} Trealtime_comment_t, *Prealtime_comment_t;
// IP
typedef void(__stdcall* TOnIoIPData)(const pu8 APointer, const s32 ASize);

// =========================== APP ===========================
typedef s32 (__stdcall *TTSAppSetCurrentApplication)(const char* AAppName);
typedef s32 (__stdcall *TTSAppGetCurrentApplication)(char** AAppName);
typedef s32 (__stdcall *TTSAppDelApplication)(const char* AAppName);
typedef s32 (__stdcall *TTSAppAddApplication)(const char* AAppName);
typedef s32 (__stdcall *TTSAppGetApplicationList)(char** AAppNameList);
typedef s32 (__stdcall *TTSAppSetCANChannelCount)(const s32 ACount);
typedef s32 (__stdcall *TTSAppSetLINChannelCount)(const s32 ACount);
typedef s32 (__stdcall *TTSAppGetCANChannelCount)(const ps32 ACount);
typedef s32 (__stdcall *TTSAppGetLINChannelCount)(const ps32 ACount);
typedef s32 (__stdcall *TTSAppSetMapping)(const PLIBTSMapping AMapping);
typedef s32 (__stdcall *TTSAppGetMapping)(const PLIBTSMapping AMapping);
typedef s32 (__stdcall *TTSAppDeleteMapping)(const PLIBTSMapping AMapping);
typedef s32 (__stdcall *TTSAppConnectApplication)(void);
typedef s32 (__stdcall *TTSAppDisconnectApplication)(void);
typedef s32 (__stdcall* TTSAppLogger)(const char* AStr, const TLogLevel ALevel);
typedef s32 (__stdcall *TTSAppSetTurboMode)(const bool AEnable);
typedef s32 (__stdcall *TTSAppGetTurboMode)(const bool* AEnable);
typedef s32 (__stdcall *TTSAppGetErrorDescription)(const s32 ACode, char** ADesc);
typedef s32 (__stdcall *TTSAppConfigureBaudrateCAN)(const s32 AIdxChn, const float ABaudrateKbps, const bool AListenOnly, const bool AInstallTermResistor120Ohm);
typedef s32 (__stdcall *TTSAppConfigureBaudrateCANFD)(const s32 AIdxChn, const float ABaudrateArbKbps, const float ABaudrateDataKbps, const TCANFDControllerType AControllerType, const TCANFDControllerMode AControllerMode, const bool AInstallTermResistor120Ohm);
typedef s32 (__stdcall *TTSAppTerminate)(const void* AObj);
typedef s32 (__stdcall* TTSWaitTime)(const void* AObj, const s32 ATimeMs, const char* AMsg);
typedef s32 (__stdcall* TTSCheckError)(const void* AObj, const s32 AErrorCode);
typedef s32 (__stdcall* TTSStartLog)(const void* AObj);
typedef s32 (__stdcall* TTSEndLog)(const void* AObj);
typedef s32 (__stdcall* TTSCheckTerminate)(const void* AObj);
typedef s32 (__stdcall* TTSGetTimestampUs)(s64* ATimestamp);
typedef s32 (__stdcall* TTSShowConfirmDialog)(const char* ATitle, const char* APrompt, const char* AImage, const s32 ATimeoutMs, const bool ADefaultOK);
typedef s32 (__stdcall* TTSPause)(void);
typedef s32 (__stdcall* TTSSetCheckFailedTerminate)(const void* AObj, const s32 AToTerminate);
typedef s32 (__stdcall* TTSAppSplitString)(const char* ASplitter, const char* AStr, char** AArray, const s32 ASingleStrSize, const s32 AArraySize, s32* AActualCount);
typedef s32 (__stdcall* TTSAppGetConfigurationFileName)(char** AFileName);
typedef s32 (__stdcall* TTSAppGetConfigurationFilePath)(char** AFilePath);
typedef s32 (__stdcall* TTSAppSetDefaultOutputDir)(const char* APath);
typedef s32 (__stdcall* TTSAppSaveScreenshot)(const char* AFormCaption, const char* AFilePath);
typedef s32 (__stdcall* TTSAppRunForm)(const char* AFormCaption);
typedef s32 (__stdcall* TTSAppStopForm)(const char* AFormCaption);
// system var def
typedef s32 (__stdcall* TTSAppGetSystemVarCount)(s32* AInternalCount, s32* AUserCount);
typedef s32 (__stdcall* TTSAppGetSystemVarDefByIndex)(const bool AIsUser, const s32 AIndex, const PLIBSystemVarDef AVarDef);
typedef s32 (__stdcall* TTSAppFindSystemVarDefByName)(const bool AIsUser, const char* ACompleteName, const PLIBSystemVarDef AVarDef);
typedef s32 (__stdcall* TTSAppCreateSystemVar)(const char* ACompleteName, const TLIBSystemVarType AType, const char* ADefaultValue, const char* AComment);
typedef s32 (__stdcall* TTSAppDeleteSystemVar)(const char* ACompleteName);
// system var get
typedef s32 (__stdcall* TTSAppGetSystemVarDouble)(const char* ACompleteName, double* AValue);
typedef s32 (__stdcall* TTSAppGetSystemVarInt32)(const char* ACompleteName, s32* AValue);
typedef s32 (__stdcall* TTSAppGetSystemVarUInt32)(const char* ACompleteName, u32* AValue);
typedef s32 (__stdcall* TTSAppGetSystemVarInt64)(const char* ACompleteName, s64* AValue);
typedef s32 (__stdcall* TTSAppGetSystemVarUInt64)(const char* ACompleteName, u64* AValue);
typedef s32 (__stdcall* TTSAppGetSystemVarUInt8Array)(const char* ACompleteName, const s32 ACapacity, s32* AVarCount, u8* AValue);
typedef s32 (__stdcall* TTSAppGetSystemVarInt32Array)(const char* ACompleteName, const s32 ACapacity, s32* AVarCount, s32* AValue);
typedef s32 (__stdcall* TTSAppGetSystemVarInt64Array)(const char* ACompleteName, const s32 ACapacity, s32* AVarCount, s64* AValue);
typedef s32 (__stdcall* TTSAppGetSystemVarDoubleArray)(const char* ACompleteName, const s32 ACapacity, s32* AVarCount, double* AValue);
typedef s32 (__stdcall* TTSAppGetSystemVarString)(const char* ACompleteName, const s32 ACapacity, char* AString);
typedef s32 (__stdcall* TTSAppGetSystemVarGerneric)(const char* ACompleteName, const s32 ACapacity, char* AValue);
typedef s32 (__stdcall* TTSWaitSystemVariable)(const char* ACompleteName, const char* AValue, const s32 ATimeoutMs);
// system var set
typedef s32 (__stdcall* TTSAppSetSystemVarDouble)(const char* ACompleteName, double AValue);
typedef s32 (__stdcall* TTSAppSetSystemVarInt32)(const char* ACompleteName, s32 AValue);
typedef s32 (__stdcall* TTSAppSetSystemVarUInt32)(const char* ACompleteName, u32 AValue);
typedef s32 (__stdcall* TTSAppSetSystemVarInt64)(const char* ACompleteName, s64 AValue);
typedef s32 (__stdcall* TTSAppSetSystemVarUInt64)(const char* ACompleteName, u64 AValue);
typedef s32 (__stdcall* TTSAppSetSystemVarUInt8Array)(const char* ACompleteName, const s32 ACapacity, u8* AValue);
typedef s32 (__stdcall* TTSAppSetSystemVarInt32Array)(const char* ACompleteName, const s32 ACapacity, s32* AValue);
typedef s32 (__stdcall* TTSAppSetSystemVarInt64Array)(const char* ACompleteName, const s32 ACapacity, s64* AValue);
typedef s32 (__stdcall* TTSAppSetSystemVarDoubleArray)(const char* ACompleteName, const s32 ACapacity, double* AValue);
typedef s32 (__stdcall* TTSAppSetSystemVarString)(const char* ACompleteName, char* AString);
typedef s32 (__stdcall* TTSAppSetSystemVarGeneric)(const char* ACompleteName, char* AValue);
typedef s32 (__stdcall* TTSAppLogSystemVar)(const char* ACompleteName);
typedef s32 (__stdcall* TTSAppWaitSystemVarExistance)(const char* ACompleteName, const s32 ATimeOutMs);
typedef s32 (__stdcall* TTSAppWaitSystemVarDisappear)(const char* ACompleteName, const s32 ATimeOutMs);
// excel
typedef s32 (__stdcall* Texcel_load)(const char* AFileName, void** AObj);
typedef s32 (__stdcall* Texcel_get_sheet_count)(const void* AObj, s32* ACount);
typedef s32 (__stdcall* Texcel_set_sheet_count)(const void* AObj, const s32 ACount);
typedef s32 (__stdcall* Texcel_get_sheet_name)(const void* AObj, const s32 AIdxSheet, char** AName);
typedef s32 (__stdcall* Texcel_set_sheet_name)(const void* AObj, const s32 AIdxSheet, const char* AName);
typedef s32 (__stdcall* Texcel_get_cell_count)(const void* AObj, const s32 AIdxSheet, s32* ARowCount, s32* AColCount);
typedef s32 (__stdcall* Texcel_get_cell_value)(const void* AObj, const s32 AIdxSheet, const s32 AIdxRow, const s32 AIdxCol, char** AValue);
typedef s32 (__stdcall* Texcel_set_cell_count)(const void* AObj, const s32 AIdxSheet, const s32 ARowCount, const s32 AColCount);
typedef s32 (__stdcall* Texcel_set_cell_value)(const void* AObj, const s32 AIdxSheet, const s32 AIdxRow, const s32 AIdxCol, char* AValue);
typedef s32 (__stdcall* Texcel_unload)(const void* AObj);
typedef s32 (__stdcall* Texcel_unload_all)(void);
// text file write
typedef s32 (__stdcall* TWriteTextFileStart)(const char* AFileName, s32* AHandle);
typedef s32 (__stdcall* TWriteTextFileLine)(const s32 AHandle, const char* ALine);
typedef s32 (__stdcall* TWriteTextFileLineWithDoubleArray)(const s32 AHandle, const double* AArray, const s32 ACount);
typedef s32 (__stdcall* TWriteTextFileLineWithStringArray)(const s32 AHandle, const char** AArray, const s32 ACount);
typedef s32 (__stdcall* TWriteTextFileEnd)(const s32 AHandle);
// text file read
typedef s32 (__stdcall* TReadTextFileStart)(const char* AFileName, s32* AHandle);
typedef s32 (__stdcall* TReadTextFileLine)(const s32 AHandle, const s32 ACapacity, ps32 AReadCharCount, char* ALine);
typedef s32 (__stdcall* TReadTextFileEnd)(const s32 AHandle);
// mat file
typedef s32 (__stdcall* TWriteMatFileStart)(const char* AFileName, s32* AHandle);
typedef s32 (__stdcall* TWriteMatFileVariableDouble)(const s32 AHandle, const char* AVarName, const double AValue);
typedef s32 (__stdcall* TWriteMatFileVariableString)(const s32 AHandle, const char* AVarName, const char* AValue);
typedef s32 (__stdcall* TWriteMatFileVariableDoubleArray)(const s32 AHandle, const char* AVarName, const double* AArray, const s32 ACount);
typedef s32 (__stdcall* TWriteMatFileEnd)(const s32 AHandle);
typedef s32 (__stdcall* TReadMatFileStart)(const char* AFileName, s32* AHandle);
typedef s32 (__stdcall* TReadMatFileVariableCount)(const s32 AHandle, const char* AVarName, ps32 ACount);
typedef s32 (__stdcall* TReadMatFileVariableString)(const s32 AHandle, const char* AVarName, char* AValue, const s32 ACapacity);
typedef s32 (__stdcall* TReadMatFileVariableDouble)(const s32 AHandle, const char* AVarName, const double* AValue, const s32 AStartIdx, const s32 ACount);
typedef s32 (__stdcall* TReadMatFileEnd)(const s32 AHandle);
// ini file
typedef s32 (__stdcall* TIniCreate)(const char* AFileName, s32* AHandle);
typedef s32 (__stdcall* TIniWriteInt32)(const s32 AHandle, const char* ASection, const char* AKey, const s32 AValue);
typedef s32 (__stdcall* TIniWriteInt64)(const s32 AHandle, const char* ASection, const char* AKey, const s64 AValue);
typedef s32 (__stdcall* TIniWriteBool)(const s32 AHandle, const char* ASection, const char* AKey, const bool AValue);
typedef s32 (__stdcall* TIniWriteFloat)(const s32 AHandle, const char* ASection, const char* AKey, const double AValue);
typedef s32 (__stdcall* TIniWriteString)(const s32 AHandle, const char* ASection, const char* AKey, const char* AValue);
typedef s32 (__stdcall* TIniReadInt32)(const s32 AHandle, const char* ASection, const char* AKey, const s32* AValue, const s32 ADefault);
typedef s32 (__stdcall* TIniReadInt64)(const s32 AHandle, const char* ASection, const char* AKey, const s64* AValue, const s64 ADefault);
typedef s32 (__stdcall* TIniReadBool)(const s32 AHandle, const char* ASection, const char* AKey, const bool* AValue, const bool ADefault);
typedef s32 (__stdcall* TIniReadFloat)(const s32 AHandle, const char* ASection, const char* AKey, const double* AValue, const double ADefault);
typedef s32 (__stdcall* TIniReadString)(const s32 AHandle, const char* ASection, const char* AKey, const char* AValue, s32* ACapacity, const char* ADefault);
typedef s32 (__stdcall* TIniSectionExists)(const s32 AHandle, const char* ASection);
typedef s32 (__stdcall* TIniKeyExists)(const s32 AHandle, const char* ASection, const char* AKey);
typedef s32 (__stdcall* TIniDeleteKey)(const s32 AHandle, const char* ASection, const char* AKey);
typedef s32 (__stdcall* TIniDeleteSection)(const s32 AHandle, const char* ASection);
typedef s32 (__stdcall* TIniClose)(const s32 AHandle);
// misc
typedef s32 (__stdcall* TTSAppMakeToast)(const char* AString, const TLogLevel ALevel);
typedef s32 (__stdcall* TTSAppMakeToastUntil)(const char* AString, const TLogLevel ALevel, const bool* ACloseCriteria, const bool AUserCanBreak);
typedef s32 (__stdcall* TTSAppMakeToastWithCallback)(const char* AString, const TLogLevel ALevel, const TCheckResultCallback ACallback, const bool AUserCanBreak);
typedef s32 (__stdcall* TTSAppExecutePythonString)(const char* AString, const char* AArguments, const bool AIsSync, const bool AIsX64, char** AResultLog);
typedef s32 (__stdcall* TTSAppExecutePythonScript)(const char* AFilePath, const char* AArguments, const bool AIsSync, const bool AIsX64, char** AResultLog);
typedef s32 (__stdcall* TTSAppExecuteApp)(const char* AAppPath,  const char* AWorkingDir, const char* AParameter, const s32 AWaitTimeMS);
typedef s32 (__stdcall* TTSAppTerminateAppByName)(const char* AImageName);
typedef s32 (__stdcall* TTSAppCallMPAPI)(const char* ALibName, const char* AFuncName, const char* AInParameters, char** AOutParameters);
typedef s32 (__stdcall* TTSAppSetAnalysisTimeRange)(const s64 ATimeStartUs, const s64 ATimeEndUs);
typedef s32 (__stdcall* TTSAppEnableAllGraphics)(const bool AEnable, const char* AExceptCaptions);
typedef s32 (__stdcall* TTSAppGetTSMasterVersion)(ps32 AYear, ps32 AMonth, ps32 ADay, ps32 ABuildNumber);
typedef s32 (__stdcall* TUIShowPageByIndex)(const s32 AIndex);
typedef s32 (__stdcall* TUIShowPageByName)(const char* AName);
typedef s32 (__stdcall* TWriteRealtimeComment)(const void* AObj, const char* AName);
typedef s32 (__stdcall* TTSAppSetThreadPriority)(const void* AObj, const s32 APriority);
typedef s32 (__stdcall* TTSAppForceDirectory)(const char* ADir);
typedef s32 (__stdcall* TTSAppDirectoryExists)(const char* ADir);
typedef s32 (__stdcall* TTSAppOpenDirectoryAndSelectFile)(const char* AFileName);
typedef s32 (__stdcall* TTSMiniDelayCPU)(void);
typedef s32 (__stdcall* TPromptUserInputValue)(const char* APrompt, double* AValue);
typedef s32 (__stdcall* TPromptUserInputString)(const char* APrompt, char* AValue, const s32 ACapacity);
typedef s32 (__stdcall* TTSAppGetDocPath)(char** AFilePath);
typedef s32 (__stdcall* TTSAppGetHWIDString)(char** AIDString);
typedef s32 (__stdcall* TTSAppGetHWIDArray)(pu8 AArray8B);
typedef s32 (__stdcall* TPlaySound)(const bool AIsSync, const char* AWaveFileName);

typedef struct _TTSApp {
    void*                              FObj;
    // >>> mp app start <<<
    TTSAppSetCurrentApplication        set_current_application;
    TTSAppGetCurrentApplication        get_current_application;
    TTSAppDelApplication               del_application;
    TTSAppAddApplication               add_application;
    TTSAppGetApplicationList           get_application_list;
    TTSAppSetCANChannelCount           set_can_channel_count;
    TTSAppSetLINChannelCount           set_lin_channel_count;
    TTSAppGetCANChannelCount           get_can_channel_count;
    TTSAppGetLINChannelCount           get_lin_channel_count;
    TTSAppSetMapping                   set_mapping;
    TTSAppGetMapping                   get_mapping;
    TTSAppDeleteMapping                del_mapping;
    TTSAppConnectApplication           connect;
    TTSAppDisconnectApplication        disconnect;
    TTSAppLogger                       log;
    TTSAppConfigureBaudrateCAN         configure_can_baudrate;
    TTSAppConfigureBaudrateCANFD       configure_canfd_baudrate;
    TTSAppSetTurboMode                 set_turbo_mode;
    TTSAppGetTurboMode                 get_turbo_mode;
    TTSAppGetErrorDescription          get_error_description;
    TTSAppTerminate                    internal_terminate_application;
    TTSWaitTime                        internal_wait;                 
    TTSCheckError                      internal_check;                
    TTSStartLog                        internal_start_log;            
    TTSEndLog                          internal_end_log;              
    TTSCheckTerminate                  internal_check_terminate;      
    TTSGetTimestampUs                  get_timestamp;
    TTSShowConfirmDialog               show_confirm_dialog;
    TTSPause                           pause;
    TTSSetCheckFailedTerminate         internal_set_check_failed_terminate;
    TTSAppGetSystemVarCount            get_system_var_count;
    TTSAppGetSystemVarDefByIndex       get_system_var_def_by_index;
    TTSAppFindSystemVarDefByName       get_system_var_def_by_name;
    TTSAppGetSystemVarDouble           get_system_var_double;
    TTSAppGetSystemVarInt32            get_system_var_int32;
    TTSAppGetSystemVarUInt32           get_system_var_uint32;
    TTSAppGetSystemVarInt64            get_system_var_int64;
    TTSAppGetSystemVarUInt64           get_system_var_uint64;
    TTSAppGetSystemVarUInt8Array       get_system_var_uint8_array;
    TTSAppGetSystemVarInt32Array       get_system_var_int32_array;
    TTSAppGetSystemVarInt64Array       get_system_var_int64_array;
    TTSAppGetSystemVarDoubleArray      get_system_var_double_array;
    TTSAppGetSystemVarString           get_system_var_string;
    TTSAppSetSystemVarDouble           set_system_var_double;
    TTSAppSetSystemVarInt32            set_system_var_int32;
    TTSAppSetSystemVarUInt32           set_system_var_uint32;
    TTSAppSetSystemVarInt64            set_system_var_int64;
    TTSAppSetSystemVarUInt64           set_system_var_uint64;
    TTSAppSetSystemVarUInt8Array       set_system_var_uint8_array;
    TTSAppSetSystemVarInt32Array       set_system_var_int32_array;
    TTSAppSetSystemVarInt64Array       set_system_var_int64_array;
    TTSAppSetSystemVarDoubleArray      set_system_var_double_array;
    TTSAppSetSystemVarString           set_system_var_string;
    TTSAppMakeToast                    make_toast;
    TTSAppExecutePythonString          execute_python_string;
    TTSAppExecutePythonScript          execute_python_script;
    TTSAppExecuteApp                   execute_app;
    TTSAppTerminateAppByName           terminate_app_by_name;
    Texcel_load                        excel_load           ;
    Texcel_get_sheet_count             excel_get_sheet_count;
    Texcel_set_sheet_count             excel_set_sheet_count;
    Texcel_get_sheet_name              excel_get_sheet_name ;
    Texcel_get_cell_count              excel_get_cell_count ;
    Texcel_get_cell_value              excel_get_cell_value ;
    Texcel_set_cell_count              excel_set_cell_count ;
    Texcel_set_cell_value              excel_set_cell_value ;
    Texcel_unload                      excel_unload         ;
    Texcel_unload_all                  excel_unload_all     ;
    TTSAppLogSystemVar                 log_system_var       ;
    Texcel_set_sheet_name              excel_set_sheet_name ;
    TTSAppCallMPAPI                    call_mini_program_api;
    TTSAppSplitString                  split_string         ;
    TTSAppWaitSystemVarExistance       wait_system_var_existance;
    TTSAppWaitSystemVarDisappear       wait_system_var_disappear;
    TTSAppSetAnalysisTimeRange         set_analysis_time_range;
    TTSAppGetConfigurationFileName     get_configuration_file_name;
    TTSAppGetConfigurationFilePath     get_configuration_file_path;
    TTSAppSetDefaultOutputDir          set_default_output_dir;
    TTSAppSaveScreenshot               save_screenshot;
    TTSAppEnableAllGraphics            enable_all_graphics;
    TTSAppGetTSMasterVersion           get_tsmaster_version;
    TUIShowPageByIndex                 ui_show_page_by_index;
    TUIShowPageByName                  ui_show_page_by_name;
    TWriteRealtimeComment              internal_write_realtime_comment;
    TTSAppSetThreadPriority            internal_set_thread_priority;
    TTSAppGetSystemVarGerneric         get_system_var_generic;
    TTSAppSetSystemVarGeneric          set_system_var_generic;
    TWriteTextFileStart                write_text_file_start;
    TWriteTextFileLine                 write_text_file_line;
    TWriteTextFileLineWithDoubleArray  write_text_file_line_double_array;
    TWriteTextFileLineWithStringArray  write_text_file_line_string_array;
    TWriteTextFileEnd                  write_text_file_end;
    TTSAppForceDirectory               force_directory;
    TTSAppDirectoryExists              directory_exists;
    TTSAppOpenDirectoryAndSelectFile   open_directory_and_select_file;
    TTSMiniDelayCPU                    mini_delay_cpu;
    TTSWaitSystemVariable              wait_system_var;
    TWriteMatFileStart                 write_mat_file_start;
    TWriteMatFileVariableDouble        write_mat_file_variable_double;
    TWriteMatFileVariableString        write_mat_file_variable_string;
    TWriteMatFileVariableDoubleArray   write_mat_file_variable_double_array;
    TWriteMatFileEnd                   write_mat_file_end;
    TReadMatFileStart                  read_mat_file_start;
    TReadMatFileVariableCount          read_mat_file_variable_count;
    TReadMatFileVariableString         read_mat_file_variable_string;
    TReadMatFileVariableDouble         read_mat_file_variable_double;
    TReadMatFileEnd                    read_mat_file_end;
    TPromptUserInputValue              prompt_user_input_value;
    TPromptUserInputString             prompt_user_input_string;
    TIniCreate                         ini_create;
    TIniWriteInt32                     ini_write_int32;
    TIniWriteInt64                     ini_write_int64;
    TIniWriteBool                      ini_write_bool;
    TIniWriteFloat                     ini_write_float;
    TIniWriteString                    ini_write_string;
    TIniReadInt32                      ini_read_int32;
    TIniReadInt64                      ini_read_int64;
    TIniReadBool                       ini_read_bool;
    TIniReadFloat                      ini_read_float;
    TIniReadString                     ini_read_string;
    TIniSectionExists                  ini_section_exists;
    TIniKeyExists                      ini_key_exists;
    TIniDeleteKey                      ini_delete_key;
    TIniDeleteSection                  ini_delete_section;
    TIniClose                          ini_close;
    TTSAppMakeToastUntil               make_toast_until;
    TTSAppMakeToastWithCallback        make_toast_with_callback;
    TTSAppGetDocPath                   get_doc_path;
    TTSAppGetHWIDString                get_hardware_id_string;
    TTSAppGetHWIDArray                 get_hardware_id_array;
    TTSAppCreateSystemVar              create_system_var;
    TTSAppDeleteSystemVar              delete_system_var;
    TTSAppRunForm                      run_form;
    TTSAppStopForm                     stop_form;
    TReadTextFileStart                 read_text_file_start;
    TReadTextFileLine                  read_text_file_line;
    TReadTextFileEnd                   read_text_file_end;
    TPlaySound                         play_sound;
    // >>> mp app end <<<
    // place holder
    s32                                FDummy[915];
    void terminate_application(void){
        internal_terminate_application(FObj);
    }
    s32 wait(const s32 ATimeMs, const char* AMsg){
        return internal_wait(FObj, ATimeMs, AMsg);
    }
    s32 check(const s32 AErrorCode){
        return internal_check(FObj, AErrorCode);
    }
    s32 start_log(void){
        return internal_start_log(FObj);
    }
    s32 end_log(void){
        return internal_end_log(FObj);
    }
    s32 write_realtime_comment(const char* AName){
        return internal_write_realtime_comment(FObj, AName);
    }
    s32 check_terminate(void){
        return internal_check_terminate(FObj);
    }
    s32 set_check_failed_terminate(const s32 AToTerminate){
        return internal_set_check_failed_terminate(FObj, AToTerminate);
    }
    s32 set_thread_priority(const s32 APriority){
        return internal_set_thread_priority(FObj, APriority);
    }
}TTSApp, * PTSApp;

// =========================== COM ===========================
typedef s32 (__stdcall* TTransmitCANAsync)(const PCAN ACAN);
typedef s32 (__stdcall* TTransmitCANFDAsync)(const PCANFD ACANFD);
typedef s32 (__stdcall* TTransmitLINAsync)(const PLIN ALIN);
typedef s32 (__stdcall* TTransmitCANSync)(const PCAN ACAN, const s32 ATimeoutMS);
typedef s32 (__stdcall* TTransmitCANFDSync)(const PCANFD ACANFD, const s32 ATimeoutMS);
typedef s32 (__stdcall* TTransmitLINSync)(const PLIN ALIN, const s32 ATimeoutMS);
typedef double (__stdcall* TGetCANSignalValue)(const PCANSignal ACANSignal, const pu8 AData);
typedef void (__stdcall* TSetCANSignalValue)(const PCANSignal ACANSignal, const pu8 AData, const double AValue);
typedef void (__stdcall* TCANEvent)(const ps32 AObj, const PCAN ACAN);
typedef void (__stdcall* TCANFDEvent)(const ps32 AObj, const PCANFD ACANFD);
typedef void (__stdcall* TLINEvent)(const ps32 AObj, const PLIN ALIN);
typedef s32 (__stdcall* TRegisterCANEvent)(const ps32 AObj, const TCANEvent AEvent);
typedef s32 (__stdcall* TUnregisterCANEvent)(const ps32 AObj, const TCANEvent AEvent);
typedef s32 (__stdcall* TRegisterCANFDEvent)(const ps32 AObj, const TCANFDEvent AEvent);
typedef s32 (__stdcall* TUnregisterCANFDEvent)(const ps32 AObj, const TCANFDEvent AEvent);
typedef s32 (__stdcall* TRegisterLINEvent)(const ps32 AObj, const TLINEvent AEvent);
typedef s32 (__stdcall* TUnregisterLINEvent)(const ps32 AObj, const TLINEvent AEvent);
typedef s32 (__stdcall* TUnregisterCANEvents)(const ps32 AObj);
typedef s32 (__stdcall* TUnregisterLINEvents)(const ps32 AObj);
typedef s32 (__stdcall* TUnregisterCANFDEvents)(const ps32 AObj);
typedef s32 (__stdcall* TUnregisterALLEvents)(const ps32 AObj);
typedef s32 (__stdcall* TRegisterPreTxCANEvent)(const ps32 AObj, const TCANEvent AEvent);
typedef s32 (__stdcall* TUnregisterPreTxCANEvent)(const ps32 AObj, const TCANEvent AEvent);
typedef s32 (__stdcall* TRegisterPreTxCANFDEvent)(const ps32 AObj, const TCANFDEvent AEvent);
typedef s32 (__stdcall* TUnregisterPreTxCANFDEvent)(const ps32 AObj, const TCANFDEvent AEvent);
typedef s32 (__stdcall* TRegisterPreTxLINEvent)(const ps32 AObj, const TLINEvent AEvent);
typedef s32 (__stdcall* TUnregisterPreTxLINEvent)(const ps32 AObj, const TLINEvent AEvent);
typedef s32 (__stdcall* TUnregisterPreTxCANEvents)(const ps32 AObj);
typedef s32 (__stdcall* TUnregisterPreTxLINEvents)(const ps32 AObj);
typedef s32 (__stdcall* TUnregisterPreTxCANFDEvents)(const ps32 AObj);
typedef s32 (__stdcall* TUnregisterPreTxALLEvents)(const ps32 AObj);
typedef s32 (__stdcall* TEnableBusStatistics)(const bool AEnable);
typedef s32 (__stdcall* TClearBusStatistics)(void);
typedef s32 (__stdcall* TGetBusStatistics)(const TLIBApplicationChannelType ABusType, const s32 AIdxChn, const TLIBCANBusStatistics AIdxStat, pdouble AStat);
typedef s32 (__stdcall* TGetFPSCAN)(const s32 AIdxChn, const s32 AIdentifier, ps32 AFPS);
typedef s32 (__stdcall* TGetFPSCANFD)(const s32 AIdxChn, const s32 AIdentifier, ps32 AFPS);
typedef s32 (__stdcall* TGetFPSLIN)(const s32 AIdxChn, const s32 AIdentifier, ps32 AFPS);
typedef s32 (__stdcall* TWaitCANMessage)(const void* AObj, const PCAN ATxCAN, const PCAN ARxCAN, const s32 ATimeoutMS);
typedef s32 (__stdcall* TWaitCANFDMessage)(const void* AObj, const PCANFD ATxCANFD, const PCANFD ARxCANFD, const s32 ATimeoutMS);
typedef s32 (__stdcall* TAddCyclicMsgCAN)(const PCAN ACAN, const float APeriodMS);
typedef s32 (__stdcall* TAddCyclicMsgCANFD)(const PCANFD ACANFD, const float APeriodMS);
typedef s32 (__stdcall* TDeleteCyclicMsgCAN)(const PCAN ACAN);
typedef s32 (__stdcall* TDeleteCyclicMsgCANFD)(const PCANFD ACANFD);
typedef s32 (__stdcall* TDeleteCyclicMsgs)(void);
// online replay functions
typedef s32 (__stdcall* Ttslog_add_online_replay_config)(const char* AFileName, s32* AIndex);
typedef s32 (__stdcall* Ttslog_set_online_replay_config)(const s32 AIndex, const char* AName, const char* AFileName, const bool AAutoStart, const bool AIsRepetitiveMode, const TLIBOnlineReplayTimingMode AStartTimingMode, const s32 AStartDelayTimeMs, const bool ASendTx, const bool ASendRx, const char* AMappings);
typedef s32 (__stdcall* Ttslog_get_online_replay_count)(s32* ACount);
typedef s32 (__stdcall* Ttslog_get_online_replay_config)(const s32 AIndex, char** AName, char** AFileName, bool* AAutoStart, bool* AIsRepetitiveMode, TLIBOnlineReplayTimingMode* AStartTimingMode, s32* AStartDelayTimeMs, bool* ASendTx, bool* ASendRx, char** AMappings);
typedef s32 (__stdcall* Ttslog_del_online_replay_config)(const s32 AIndex);
typedef s32 (__stdcall* Ttslog_del_online_replay_configs)(void);
typedef s32 (__stdcall* Ttslog_start_online_replay)(const s32 AIndex);
typedef s32 (__stdcall* Ttslog_start_online_replays)(void);
typedef s32 (__stdcall* Ttslog_pause_online_replay)(const s32 AIndex);
typedef s32 (__stdcall* Ttslog_pause_online_replays)(void);
typedef s32 (__stdcall* Ttslog_stop_online_replay)(const s32 AIndex);
typedef s32 (__stdcall* Ttslog_stop_online_replays)(void);
typedef s32 (__stdcall* Ttslog_get_online_replay_status)(const s32 AIndex, TLIBOnlineReplayStatus* AStatus, float* AProgressPercent100);
// CAN rbs functions
typedef s32 (__stdcall* TCANRBSStart)(void);
typedef s32 (__stdcall* TCANRBSStop)(void);
typedef s32 (__stdcall* TCANRBSIsRunning)(bool* AIsRunning);
typedef s32 (__stdcall* TCANRBSConfigure)(const bool AAutoStart, const bool AAutoSendOnModification, const bool AActivateNodeSimulation, const TLIBRBSInitValueOptions AInitValueOptions);
typedef s32 (__stdcall* TCANRBSActivateAllNetworks)(const bool AEnable, const bool AIncludingChildren);
typedef s32 (__stdcall* TCANRBSActivateNetworkByName)(const bool AEnable, const char* ANetworkName, const bool AIncludingChildren);
typedef s32 (__stdcall* TCANRBSActivateNodeByName)(const bool AEnable, const char* ANetworkName, const char* ANodeName, const bool AIncludingChildren);
typedef s32 (__stdcall* TCANRBSActivateMessageByName)(const bool AEnable, const char* ANetworkName, const char* ANodeName, const char* AMsgName);
typedef s32 (__stdcall* TCANRBSSetMessageCycleByName)(const s32 AIntervalMs, const char* ANetworkName, const char* ANodeName, const char* AMsgName);
typedef s32 (__stdcall* TCANRBSGetSignalValueByElement)(const s32 AIdxChn, const char* ANetworkName, const char* ANodeName, const char* AMsgName, const char* ASignalName, double* AValue);
typedef s32 (__stdcall* TCANRBSGetSignalValueByAddress)(const char* ASymbolAddress, double* AValue);
typedef s32 (__stdcall* TCANRBSSetSignalValueByElement)(const s32 AIdxChn, const char* ANetworkName, const char* ANodeName, const char* AMsgName, const char* ASignalName, const double AValue);
typedef s32 (__stdcall* TCANRBSSetSignalValueByAddress)(const char* ASymbolAddress, const double AValue);
// log file functions
typedef s32 (__stdcall* Ttslog_blf_write_start)(const char* AFileName, s32* AHandle);
typedef s32 (__stdcall* Ttslog_blf_write_start_w_timestamp)(const char* AFileName, s32* AHandle, u16* AYear, u16* AMonth, u16* ADay, u16* AHour, u16* AMinute, u16* ASecond, u16* AMilliseconds);
typedef s32 (__stdcall* Ttslog_blf_write_set_max_count)(const s32 AHandle, const u32 ACount);
typedef s32 (__stdcall* Ttslog_blf_write_can)(const s32 AHandle, const PCAN ACAN);
typedef s32 (__stdcall* Ttslog_blf_write_can_fd)(const s32 AHandle, const PCANFD ACANFD);
typedef s32 (__stdcall* Ttslog_blf_write_lin)(const s32 AHandle, const PLIN ALIN);
typedef s32 (__stdcall* Ttslog_blf_write_realtime_comment)(const s32 AHandle, const s64 ATimeUs, const char* AComment);
typedef s32 (__stdcall* Ttslog_blf_write_end)(const s32 AHandle);
typedef s32 (__stdcall* Ttslog_blf_read_start)(const char* AFileName, s32* AHandle, s32* AObjCount);
typedef s32 (__stdcall* Ttslog_blf_read_status)(const s32 AHandle, s32* AObjReadCount);
typedef s32 (__stdcall* Ttslog_blf_read_object)(const s32 AHandle, s32* AProgressedCnt, TSupportedBLFObjType* AType, PCAN ACAN, PLIN ALIN, PCANFD ACANFD);
typedef s32 (__stdcall* Ttslog_blf_read_object_w_comment)(const s32 AHandle, s32* AProgressedCnt, TSupportedBLFObjType* AType, PCAN ACAN, PLIN ALIN, PCANFD ACANFD, Prealtime_comment_t AComment);
typedef s32 (__stdcall* Ttslog_blf_read_end)(const s32 AHandle);
typedef s32 (__stdcall* Ttslog_blf_seek_object_time)(const s32 AHandle, const double AProg100, s64* ATime, s32* AProgressedCnt);
typedef s32 (__stdcall* Ttslog_blf_to_asc)(const char* ABLFFileName, const char* AASCFileName, const TProgressCallback AProgressCallback);
typedef s32 (__stdcall* Ttslog_asc_to_blf)(const char* AASCFileName, const char* ABLFFileName, const TProgressCallback AProgressCallback);
// IP functions
typedef s32 (__stdcall* TIoIPCreate)(const void* AObj, const u16 APortTCP, const u16 APortUDP, const TOnIoIPData AOnTCPDataEvent, const TOnIoIPData AOnUDPDataEvent, s32* AHandle);
typedef s32 (__stdcall* TIoIPDelete)(const void* AObj, const s32 AHandle);
typedef s32 (__stdcall* TIoIPEnableTCPServer)(const void* AObj, const s32 AHandle, const bool AEnable);
typedef s32 (__stdcall* TIoIPEnableUDPServer)(const void* AObj, const s32 AHandle, const bool AEnable);
typedef s32 (__stdcall* TIoIPConnectTCPServer)(const void* AObj, const s32 AHandle, const char* AIpAddress, const u16 APort);
typedef s32 (__stdcall* TIoIPConnectUDPServer)(const void* AObj, const s32 AHandle, const char* AIpAddress, const u16 APort);
typedef s32 (__stdcall* TIoIPDisconnectTCPServer)(const void* AObj, const s32 AHandle);
typedef s32 (__stdcall* TIoIPSendBufferTCP)(const void* AObj, const s32 AHandle, const pu8 APointer, const s32 ASize);
typedef s32 (__stdcall* TIoIPSendBufferUDP)(const void* AObj, const s32 AHandle, const pu8 APointer, const s32 ASize);
typedef s32 (__stdcall* TIoIPRecvTCPClientResponse)(const void* AObj, const s32 AHandle, const s32 ATimeoutMs, const pu8 ABufferToReadTo, ps32 AActualSize);
typedef s32 (__stdcall* TIoIPSendTCPServerResponse)(const void* AObj, const s32 AHandle, const pu8 ABufferToWriteFrom, const s32 ASize);
typedef s32 (__stdcall* TIoIPSendUDPBroadcast)(const void* AObj, const s32 AHandle, const u16 APort, const pu8 ABufferToWriteFrom, const s32 ASize);
typedef s32 (__stdcall* TIoIPSetUDPServerBufferSize)(const void* AObj, const s32 AHandle, const s32 ASize);
typedef s32 (__stdcall* TIoIPRecvUDPClientResponse)(const void* AObj, const s32 AHandle, const s32 ATimeoutMs, const pu8 ABufferToReadTo, ps32 AActualSize);
typedef s32 (__stdcall* TIoIPSendUDPServerResponse)(const void* AObj, const s32 AHandle, const pu8 ABufferToWriteFrom, const s32 ASize);
// signal server
typedef s32 (__stdcall* TSgnSrvRegisterCANSignalByMsgId)(const s32 AIdxChn, const s32 AMsgId, const char* ASgnName, ps32 AClientId);
typedef s32 (__stdcall* TSgnSrvRegisterLINSignalByMsgId)(const s32 AIdxChn, const s32 AMsgId, const char* ASgnName, ps32 AClientId);
typedef s32 (__stdcall* TSgnSrvRegisterCANSignalByMsgName)(const s32 AIdxChn, const char* ANetworkName, const char* AMsgName, const char* ASgnName, ps32 AClientId);
typedef s32 (__stdcall* TSgnSrvRegisterLINSignalByMsgName)(const s32 AIdxChn, const char* ANetworkName, const char* AMsgName, const char* ASgnName, ps32 AClientId);
typedef s32 (__stdcall* TSgnSrvGetCANSignalPhyValueLatest)(const s32 AIdxChn, const s32 AClientId, pdouble AValue, ps64 ATimeUs);
typedef s32 (__stdcall* TSgnSrvGetLINSignalPhyValueLatest)(const s32 AIdxChn, const s32 AClientId, pdouble AValue, ps64 ATimeUs);
typedef s32 (__stdcall* TSgnSrvGetCANSignalPhyValueInMsg)(const s32 AIdxChn, const s32 AClientId, const PCANFD AMsg, pdouble AValue, ps64 ATimeUs);
typedef s32 (__stdcall* TSgnSrvGetLINSignalPhyValueInMsg)(const s32 AIdxChn, const s32 AClientId, const PLIN AMsg, pdouble AValue, ps64 ATimeUs);
// TSMaster variable =============================================

// definitions
typedef struct _TTSCOM {
    void*                              FObj;
    // >>> mp com start <<<
    TTransmitCANAsync                  transmit_can_async;
    TTransmitCANSync                   transmit_can_sync;
    TTransmitCANFDAsync                transmit_canfd_async;
    TTransmitCANFDSync                 transmit_canfd_sync;
    TTransmitLINAsync                  transmit_lin_async;
    TTransmitLINSync                   transmit_lin_sync;
    TGetCANSignalValue                 get_can_signal_value;
    TSetCANSignalValue                 set_can_signal_value;
    TEnableBusStatistics               enable_bus_statistics;
    TClearBusStatistics                clear_bus_statistics;
    TGetBusStatistics                  get_bus_statistics;
    TGetFPSCAN                         get_fps_can;
    TGetFPSCANFD                       get_fps_canfd;
    TGetFPSLIN                         get_fps_lin;
    TWaitCANMessage                    internal_wait_can_message;
    TWaitCANFDMessage                  internal_wait_canfd_message;
    TAddCyclicMsgCAN                   add_cyclic_message_can;
    TAddCyclicMsgCANFD                 add_cyclic_message_canfd;
    TDeleteCyclicMsgCAN                del_cyclic_message_can;
    TDeleteCyclicMsgCANFD              del_cyclic_message_canfd;
    TDeleteCyclicMsgs                  del_cyclic_messages;
    TRegisterCANEvent                  internal_register_event_can;
    TUnregisterCANEvent                internal_unregister_event_can;
    TRegisterCANFDEvent                internal_register_event_canfd;
    TUnregisterCANFDEvent              internal_unregister_event_canfd;
    TRegisterLINEvent                  internal_register_event_lin;
    TUnregisterLINEvent                internal_unregister_event_lin;    
    TUnregisterCANEvents               internal_unregister_events_can;
    TUnregisterLINEvents               internal_unregister_events_lin;
    TUnregisterCANFDEvents             internal_unregister_events_canfd;
    TUnregisterALLEvents               internal_unregister_events_all;
    Ttslog_add_online_replay_config    tslog_add_online_replay_config ;
    Ttslog_set_online_replay_config    tslog_set_online_replay_config ;
    Ttslog_get_online_replay_count     tslog_get_online_replay_count  ;
    Ttslog_get_online_replay_config    tslog_get_online_replay_config ;
    Ttslog_del_online_replay_config    tslog_del_online_replay_config ;
    Ttslog_del_online_replay_configs   tslog_del_online_replay_configs;
    Ttslog_start_online_replay         tslog_start_online_replay      ;
    Ttslog_start_online_replays        tslog_start_online_replays     ;
    Ttslog_pause_online_replay         tslog_pause_online_replay      ;
    Ttslog_pause_online_replays        tslog_pause_online_replays     ;
    Ttslog_stop_online_replay          tslog_stop_online_replay       ;
    Ttslog_stop_online_replays         tslog_stop_online_replays      ;
    Ttslog_get_online_replay_status    tslog_get_online_replay_status ;
    TCANRBSStart                       can_rbs_start;
    TCANRBSStop                        can_rbs_stop;
    TCANRBSIsRunning                   can_rbs_is_running;
    TCANRBSConfigure                   can_rbs_configure;
    TCANRBSActivateAllNetworks         can_rbs_activate_all_networks;
    TCANRBSActivateNetworkByName       can_rbs_activate_network_by_name;
    TCANRBSActivateNodeByName          can_rbs_activate_node_by_name;
    TCANRBSActivateMessageByName       can_rbs_activate_message_by_name;
    TCANRBSGetSignalValueByElement     can_rbs_get_signal_value_by_element;
    TCANRBSGetSignalValueByAddress     can_rbs_get_signal_value_by_address;
    TCANRBSSetSignalValueByElement     can_rbs_set_signal_value_by_element;
    TCANRBSSetSignalValueByAddress     can_rbs_set_signal_value_by_address;
    TRegisterPreTxCANEvent             internal_register_pretx_event_can;
    TUnregisterPreTxCANEvent           internal_unregister_pretx_event_can;    
    TRegisterPreTxCANFDEvent           internal_register_pretx_event_canfd;
    TUnregisterPreTxCANFDEvent         internal_unregister_pretx_event_canfd;
    TRegisterPreTxLINEvent             internal_register_pretx_event_lin;
    TUnregisterPreTxLINEvent           internal_unregister_pretx_event_lin;    
    TUnregisterPreTxCANEvents          internal_unregister_pretx_events_can;
    TUnregisterPreTxLINEvents          internal_unregister_pretx_events_lin;
    TUnregisterPreTxCANFDEvents        internal_unregister_pretx_events_canfd;
    TUnregisterPreTxALLEvents          internal_unregister_pretx_events_all;
    Ttslog_blf_write_start             tslog_blf_write_start     ;
    Ttslog_blf_write_can               tslog_blf_write_can       ;
    Ttslog_blf_write_can_fd            tslog_blf_write_can_fd    ;
    Ttslog_blf_write_lin               tslog_blf_write_lin       ;
    Ttslog_blf_write_end               tslog_blf_write_end       ;
    Ttslog_blf_read_start              tslog_blf_read_start      ;
    Ttslog_blf_read_status             tslog_blf_read_status     ;
    Ttslog_blf_read_object             tslog_blf_read_object     ;
    Ttslog_blf_read_end                tslog_blf_read_end        ;
    Ttslog_blf_seek_object_time        tslog_blf_seek_object_time;
    Ttslog_blf_to_asc                  tslog_blf_to_asc          ;
    Ttslog_asc_to_blf                  tslog_asc_to_blf          ;
    TIoIPCreate                        internal_ioip_create               ;
    TIoIPDelete                        internal_ioip_delete               ;
    TIoIPEnableTCPServer               internal_ioip_enable_tcp_server    ;
    TIoIPEnableUDPServer               internal_ioip_enable_udp_server    ;
    TIoIPConnectTCPServer              internal_ioip_connect_tcp_server   ;
    TIoIPConnectUDPServer              internal_ioip_connect_udp_server   ;
    TIoIPDisconnectTCPServer           internal_ioip_disconnect_tcp_server;
    TIoIPSendBufferTCP                 internal_ioip_send_buffer_tcp      ;
    TIoIPSendBufferUDP                 internal_ioip_send_buffer_udp      ;
    Ttslog_blf_write_realtime_comment  tslog_blf_write_realtime_comment   ;
    Ttslog_blf_read_object_w_comment   tslog_blf_read_object_w_comment    ;
    TIoIPRecvTCPClientResponse         internal_ioip_receive_tcp_client_response;
    TIoIPSendTCPServerResponse         internal_ioip_send_tcp_server_response;
    TIoIPSendUDPBroadcast              internal_ioip_send_udp_broadcast;
    TIoIPSetUDPServerBufferSize        internal_ioip_set_udp_server_buffer_size;
    TIoIPRecvUDPClientResponse         internal_ioip_receive_udp_client_response;
    TIoIPSendUDPServerResponse         internal_ioip_send_udp_server_response;
    Ttslog_blf_write_start_w_timestamp tslog_blf_write_start_w_timestamp;
    Ttslog_blf_write_set_max_count     tslog_blf_write_set_max_count;
    TCANRBSSetMessageCycleByName       can_rbs_set_message_cycle_by_name;
    TSgnSrvRegisterCANSignalByMsgId    sgnsrv_register_can_signal_by_msg_identifier;
    TSgnSrvRegisterLINSignalByMsgId    sgnsrv_register_lin_signal_by_msg_identifier;
    TSgnSrvRegisterCANSignalByMsgName  sgnsrv_register_can_signal_by_msg_name;
    TSgnSrvRegisterLINSignalByMsgName  sgnsrv_register_lin_signal_by_msg_name;
    TSgnSrvGetCANSignalPhyValueLatest  sgnsrv_get_can_signal_phy_value_latest;
    TSgnSrvGetLINSignalPhyValueLatest  sgnsrv_get_lin_signal_phy_value_latest;
    TSgnSrvGetCANSignalPhyValueInMsg   sgnsrv_get_can_signal_phy_value_in_msg;
    TSgnSrvGetLINSignalPhyValueInMsg   sgnsrv_get_lin_signal_phy_value_in_msg;
    // >>> mp com end <<<
    // place holder
    s32                                FDummy[925];
    // internal functions
    s32 wait_can_message(const PCAN ATxCAN, const PCAN ARxCAN, const s32 ATimeoutMS) {
        return internal_wait_can_message(FObj, ATxCAN, ARxCAN, ATimeoutMS);
    }
    s32 wait_canfd_message(const PCANFD ATxCANFD, const PCANFD ARxCANFD, const s32 ATimeoutMS) {
        return internal_wait_canfd_message(FObj, ATxCANFD, ARxCANFD, ATimeoutMS);
    }
    s32 register_event_can(const ps32 AObj, const TCANEvent AEvent){
        return internal_register_event_can(AObj, AEvent);
    }
    s32 unregister_event_can(const ps32 AObj, const TCANEvent AEvent){
        return internal_unregister_event_can(AObj, AEvent);
    }
    s32 register_event_canfd(const ps32 AObj, const TCANFDEvent AEvent){
        return internal_register_event_canfd(AObj, AEvent);
    }
    s32 unregister_event_canfd(const ps32 AObj, const TCANFDEvent AEvent){
        return internal_unregister_event_canfd(AObj, AEvent);
    }
    s32 register_event_lin(const ps32 AObj, const TLINEvent AEvent){
        return internal_register_event_lin(AObj, AEvent);
    }
    s32 unregister_event_lin(const ps32 AObj, const TLINEvent AEvent){
        return internal_unregister_event_lin(AObj, AEvent);
    }
    s32 unregister_events_can(const ps32 AObj){
        return internal_unregister_events_can(AObj);
    }
    s32 unregister_events_lin(const ps32 AObj){
        return internal_unregister_events_lin(AObj);
    }
    s32 unregister_events_canfd(const ps32 AObj){
        return internal_unregister_events_canfd(AObj);
    }
    s32 unregister_events_all(const ps32 AObj){
        return internal_unregister_events_all(AObj);
    }
    s32 register_pretx_event_can(const ps32 AObj, const TCANEvent AEvent){
        return internal_register_pretx_event_can(AObj, AEvent);
    }
    s32 unregister_pretx_event_can(const ps32 AObj, const TCANEvent AEvent){
        return internal_unregister_pretx_event_can(AObj, AEvent);
    }
    s32 register_pretx_event_canfd(const ps32 AObj, const TCANFDEvent AEvent){
        return internal_register_pretx_event_canfd(AObj, AEvent);
    }
    s32 unregister_pretx_event_canfd(const ps32 AObj, const TCANFDEvent AEvent){
        return internal_unregister_pretx_event_canfd(AObj, AEvent);
    }
    s32 register_pretx_event_lin(const ps32 AObj, const TLINEvent AEvent){
        return internal_register_pretx_event_lin(AObj, AEvent);
    }
    s32 unregister_pretx_event_lin(const ps32 AObj, const TLINEvent AEvent){
        return internal_unregister_pretx_event_lin(AObj, AEvent);
    }
    s32 unregister_pretx_events_can(const ps32 AObj){
        return internal_unregister_pretx_events_can(AObj);
    }
    s32 unregister_pretx_events_lin(const ps32 AObj){
        return internal_unregister_pretx_events_lin(AObj);
    }
    s32 unregister_pretx_events_canfd(const ps32 AObj){
        return internal_unregister_pretx_events_canfd(AObj);
    }
    s32 unregister_pretx_events_all(const ps32 AObj){
        return internal_unregister_pretx_events_all(AObj);
    }
    // IP functions
    s32 ioip_create(const u16 APortTCP, const u16 APortUDP, const TOnIoIPData AOnTCPDataEvent, const TOnIoIPData AOnUDPEvent, s32* AHandle){
        return internal_ioip_create(FObj, APortTCP, APortUDP, AOnTCPDataEvent, AOnUDPEvent, AHandle);
    }
    s32 ioip_delete(const s32 AHandle){
        return internal_ioip_delete(FObj, AHandle);
    }
    s32 ioip_enable_tcp_server(const s32 AHandle, const bool AEnable){
        return internal_ioip_enable_tcp_server(FObj, AHandle, AEnable);
    }
    s32 ioip_enable_udp_server(const s32 AHandle, const bool AEnable){
        return internal_ioip_enable_udp_server(FObj, AHandle, AEnable);
    }
    s32 ioip_connect_tcp_server(const s32 AHandle, const char* AIpAddress, const u16 APort){
        return internal_ioip_connect_tcp_server(FObj, AHandle, AIpAddress, APort);
    }
    s32 ioip_connect_udp_server(const s32 AHandle, const char* AIpAddress, const u16 APort){
        return internal_ioip_connect_udp_server(FObj, AHandle, AIpAddress, APort);
    }
    s32 ioip_disconnect_tcp_server(const s32 AHandle){
        return internal_ioip_disconnect_tcp_server(FObj, AHandle);
    }
    s32 ioip_send_buffer_tcp(const s32 AHandle, const pu8 APointer, const s32 ASize){
        return internal_ioip_send_buffer_tcp(FObj, AHandle, APointer, ASize);
    }
    s32 ioip_send_buffer_udp(const s32 AHandle, const pu8 APointer, const s32 ASize){
        return internal_ioip_send_buffer_udp(FObj, AHandle, APointer, ASize);
    }
    s32 ioip_receive_tcp_client_response(const s32 AHandle, const s32 ATimeoutMs, const pu8 ABufferToReadTo, ps32 AActualSize){
        return internal_ioip_receive_tcp_client_response(FObj, AHandle, ATimeoutMs, ABufferToReadTo, AActualSize);
    }
    s32 ioip_send_tcp_server_response(const s32 AHandle, const pu8 ABufferToWriteFrom, const s32 ASize){
        return internal_ioip_send_tcp_server_response(FObj, AHandle, ABufferToWriteFrom, ASize);
    }
    s32 ioip_send_udp_broadcast(const s32 AHandle, const u16 APort, const pu8 ABufferToWriteFrom, const s32 ASize){
        return internal_ioip_send_udp_broadcast(FObj, AHandle, APort, ABufferToWriteFrom, ASize);
    }
    s32 ioip_set_udp_server_buffer_size(const s32 AHandle, const s32 ASize){
        return internal_ioip_set_udp_server_buffer_size(FObj, AHandle, ASize);
    }
    s32 ioip_receive_udp_client_response(const s32 AHandle, const s32 ATimeoutMs, const pu8 ABufferToReadTo, ps32 AActualSize){
        return internal_ioip_receive_udp_client_response(FObj, AHandle, ATimeoutMs, ABufferToReadTo, AActualSize);
    }
    s32 ioip_send_udp_server_response(const s32 AHandle, const pu8 ABufferToWriteFrom, const s32 ASize){
        return internal_ioip_send_udp_server_response(FObj, AHandle, ABufferToWriteFrom, ASize);
    }
}TTSCOM, * PTSCOM;

// =========================== Test ===========================
typedef s32 (__stdcall* TTestSetVerdictOK)(const void* AObj, const char* AStr);
typedef s32 (__stdcall* TTestSetVerdictNOK)(const void* AObj, const char* AStr);
typedef s32 (__stdcall* TTestSetVerdictCOK)(const void* AObj, const char* AStr);
typedef s32 (__stdcall* TTestLog)(const void* AObj, const char* AStr, const TLogLevel ALevel);
typedef s32 (__stdcall* TTestWriteResultString)(const void* AObj, const char* AName, const char* AValue, const TLogLevel ALevel);
typedef s32 (__stdcall* TTestWriteResultValue)(const void* AObj, const char* AName, const double AValue, const TLogLevel ALevel);
typedef s32 (__stdcall* TTestCheckErrorBegin)(void);
typedef s32 (__stdcall* TTestCheckErrorEnd)(const ps32 AErrorCount);
typedef s32 (__stdcall* TTestWriteResultImage)(const void* AObj, const char* AName, const char* AImageFileFullPath);
typedef s32 (__stdcall* TTestRetrieveCurrentResultFolder)(const void* AObj, char** AFolder);
typedef s32 (__stdcall* TTestCheckTerminate)(void);

typedef struct _TTSTest {
    void* FObj;
    // >>> mp test start <<<
    TTestSetVerdictOK                internal_set_verdict_ok;
    TTestSetVerdictNOK               internal_set_verdict_nok;
    TTestSetVerdictCOK               internal_set_verdict_cok;
    TTestLog                         internal_log_info;
    TTestWriteResultString           internal_write_result_string;
    TTestWriteResultValue            internal_write_result_value;
    TTestCheckErrorBegin             check_error_begin;
    TTestCheckErrorEnd               check_error_end;
    TTestWriteResultImage            internal_write_result_image;
    TTestRetrieveCurrentResultFolder internal_retrieve_current_result_folder;
    TTestCheckTerminate              check_test_terminate;
    // >>> mp test end <<<
    // place holder
    s32                    FDummy[995];
    void set_verdict_ok(const char* AStr) {
        internal_set_verdict_ok(FObj, AStr);
    }
    void set_verdict_nok(const char* AStr) {
        internal_set_verdict_nok(FObj, AStr);
    }
    void set_verdict_cok(const char* AStr) {
        internal_set_verdict_cok(FObj, AStr);
    }
    void log_info(const char* AStr, const TLogLevel ALevel) {
        internal_log_info(FObj, AStr, ALevel);
    }
    void write_result_string(const char* AName, const char* AValue, const TLogLevel ALevel) {
        internal_write_result_string(FObj, AName, AValue, ALevel);
    }
    void write_result_value(const char* AName, const double AValue, const TLogLevel ALevel) {
        internal_write_result_value(FObj, AName, AValue, ALevel);
    }
    s32 write_result_image(const char* AName, const char* AImageFileFullPath) {
        return internal_write_result_image(FObj, AName, AImageFileFullPath);
    }
    s32 retrieve_current_result_folder(char** AFolder) {
        return internal_retrieve_current_result_folder(FObj, AFolder);
    }
}TTSTest, * PTSTest;

// TSMaster Configuration ========================================
typedef struct {
    TTSApp  FTSApp;
    TTSCOM  FTSCOM;
    TTSTest FTSTest;
    s32 FDummy[3000];
} TTSMasterConfiguration, *PTSMasterConfiguration;

// Variables definition
extern TTSApp app;
extern TTSCOM com;
extern TTSTest test;

// Utility functions definition
extern void log(const char* format, ...);
extern void test_log(const char* format, ...);
extern void test_log_ok(const char* format, ...);
extern void test_log_nok(const char* format, ...);
extern void test_logCAN(const char* ADesc, PCAN ACAN, const TLogLevel ALevel);

#pragma pack(pop)

#endif
