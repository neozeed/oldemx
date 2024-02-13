/* os2.h (emx/gcc) */

#if !defined (_OS2_H)

#define _OS2_H

/* ------------------------------ TYPES ----------------------------------- */

#define _PACKED                 /* Not yet implemented */

typedef char CHAR;
typedef CHAR *PCHAR;

typedef unsigned char UCHAR;
typedef UCHAR *PUCHAR;

typedef unsigned char BYTE;
typedef BYTE *PBYTE;

typedef short SHORT;
typedef SHORT *PSHORT;

typedef unsigned short USHORT;
typedef USHORT *PUSHORT;

typedef long LONG;
typedef LONG *PLONG;

typedef unsigned long ULONG;
typedef ULONG *PULONG;

typedef void *PVOID;
typedef PVOID *PPVOID;
typedef unsigned char *PSZ;

typedef unsigned long SHANDLE;

typedef SHANDLE HFILE;
typedef HFILE *PHFILE;

typedef ULONG PID;

/* ---------------------------- ERROR CODES ------------------------------- */

#define NO_ERROR                            0
#define ERROR_FILE_NOT_FOUND                2
#define ERROR_PATH_NOT_FOUND                3
#define ERROR_TOO_MANY_OPEN_FILES           4
#define ERROR_ACCESS_DENIED                 5
#define ERROR_INVALID_HANDLE                6
#define ERROR_NOT_ENOUGH_MEMORY             8
#define ERROR_INVALID_ACCESS               12
#define ERROR_CURRENT_DIRECTORY            16
#define ERROR_NOT_SAME_DEVICE              17
#define ERROR_WRITE_PROTECT                19
#define ERROR_NOT_DOS_DISK                 26
#define ERROR_WRITE_FAULT                  29
#define ERROR_SHARING_VIOLATION            32
#define ERROR_LOCK_VIOLATION               33
#define ERROR_SHARING_BUFFER_EXCEEDED      36
#define ERROR_CANNOT_MAKE                  82
#define ERROR_INVALID_PARAMETER            87
#define ERROR_INTERRUPT                    95
#define ERROR_DEVICE_IN_USE                99
#define ERROR_DRIVE_LOCKED                108
#define ERROR_BROKEN_PIPE                 109
#define ERROR_OPEN_FAILED                 110
#define ERROR_BUFFER_OVERFLOW             111
#define ERROR_DISK_FULL                   112
#define ERROR_INVALID_NAME                123
#define ERROR_INVALID_LEVEL               124
#define ERROR_DIRECT_ACCESS_HANDLE        130
#define ERROR_ALREADY_EXISTS              183
#define ERROR_FILENAME_EXCED_RANGE        206
#define ERROR_LOCKED                      212
#define ERROR_PIPE_BUSY                   231
#define ERROR_MORE_DATA                   234
#define ERROR_CIRCULARITY_REQUESTED       250
#define ERROR_DIRECTORY_IN_CDS            251
#define ERROR_INVALID_EA_NAME             254
#define ERROR_EA_LIST_INCONSISTENT        255
#define ERROR_DIRECTORY                   267
#define ERROR_EAS_NOT_SUPPORTED           282
#define ERROR_NEED_EAS_FOUND              283
#define ERROR_INVALID_PROCID              303
#define ERROR_DOSSUB_SHRINK               310
#define ERROR_DOSSUB_NOMEM                311
#define ERROR_DOSSUB_OVERLAP              312
#define ERROR_NLS_OPEN_FAILED             397
#define ERROR_NLS_NO_CTRY_CODE            398
#define ERROR_NLS_TABLE_TRUNCATED         399
#define ERROR_NLS_TYPE_NOT_FOUND          401
#define ERROR_CPLIST_TOO_SMALL            473
#define ERROR_CP_NOT_MOVED                474
#define ERROR_CODE_PAGE_NOT_FOUND         476
#define ERROR_INVALID_ADDRESS             487
#define ERROR_DOSSUB_CORRUPTED            532
#define ERROR_CROSSES_OBJECT_BOUNDARY   32798

/* ------------------------- MEMORY MANAGEMENT ---------------------------- */

#define PAG_READ            0x0001
#define PAG_WRITE           0x0002
#define PAG_EXECUTE         0x0004
#define PAG_GUARD           0x0008
#define PAG_COMMIT          0x0010
#define OBJ_TILE            0x0040
#define PAG_DEFAULT         0x0400
#define PAG_SHARED          0x2000
#define PAG_FREE            0x4000

#define DOSSUB_INIT         0x0001
#define DOSSUB_GROW         0x0002
#define DOSSUB_SPARSE_OBJ   0x0004
#define DOSSUB_SERIALIZE    0x0008

ULONG DosAllocMem (PPVOID pBaseAddress, ULONG ulObjectSize,
    ULONG ulAllocationFlags);
ULONG DosAllocSharedMem (PPVOID pBaseAddress, const PSZ pszName,
    ULONG ulObjectSize, ULONG ulAllocationFlags);
ULONG DosFreeMem (PVOID pBaseAddress);
ULONG DosGetNamedSharedMem (PPVOID pBaseAddress, const PSZ pszSharedMemName,
    ULONG ulAttributeFlags);
ULONG DosGetSharedMem (const PVOID pBaseAddress, PULONG pulAttributeFlags);
ULONG DosGiveSharedMem (const PVOID pBaseAddress, PID idProcessId,
    ULONG ulAttributeFlags);
ULONG DosQueryMem (const PVOID pBaseAddress, PULONG pulRegionSize,
    PULONG pulAllocationFlags);
ULONG DosSetMem (const PVOID pBaseAddress, ULONG ulRegionSize,
    ULONG ulAttributeFlags);
ULONG DosSubAllocMem (PVOID pOffset, PPVOID pBlockOffset, ULONG ulSize);
ULONG DosSubFreeMem (PVOID pOffset, PVOID pBlockOffset, ULONG ulSize);
ULONG DosSubSetMem (PVOID pOffset, ULONG ulFlags, ULONG ulSize);
ULONG DosSubUnsetMem (PVOID pOffset);

/* --------------------------- FILE SYSTEM -------------------------------- */

#define FILE_NORMAL                    0x0000
#define FILE_READONLY                  0x0001
#define FILE_HIDDEN                    0x0002
#define FILE_SYSTEM                    0x0004
#define FILE_DIRECTORY                 0x0010
#define FILE_ARCHIVED                  0x0020

#define FILE_EXISTED                   0x0001
#define FILE_CREATED                   0x0002
#define FILE_TRUNCATED                 0x0003

#define FILE_OPEN                      0x0001
#define FILE_TRUNCATE                  0x0002
#define FILE_CREATE                    0x0010

#define OPEN_ACTION_FAIL_IF_EXISTS     0x0000
#define OPEN_ACTION_OPEN_IF_EXISTS     0x0001
#define OPEN_ACTION_REPLACE_IF_EXISTS  0x0002
#define OPEN_ACTION_FAIL_IF_NEW        0x0000
#define OPEN_ACTION_CREATE_IF_NEW      0x0010

#define OPEN_ACCESS_READONLY           0x0000
#define OPEN_ACCESS_WRITEONLY          0x0001
#define OPEN_ACCESS_READWRITE          0x0002

#define OPEN_SHARE_DENYREADWRITE       0x0010
#define OPEN_SHARE_DENYWRITE           0x0020
#define OPEN_SHARE_DENYREAD            0x0030
#define OPEN_SHARE_DENYNONE            0x0040

#define OPEN_FLAGS_NOINHERIT           0x0080
#define OPEN_FLAGS_NO_LOCALITY         0x0000
#define OPEN_FLAGS_SEQUENTIAL          0x0100
#define OPEN_FLAGS_RANDOM              0x0200
#define OPEN_FLAGS_RANDOMSEQUENTIAL    0x0300
#define OPEN_FLAGS_NO_CACHE            0x1000
#define OPEN_FLAGS_FAIL_ON_ERROR       0x2000
#define OPEN_FLAGS_WRITE_THROUGH       0x4000
#define OPEN_FLAGS_DASD                0x8000
#define OPEN_FLAGS_NONSPOOLED         0x40000

#define FIL_STANDARD                   1
#define FIL_QUERYEASIZE                2
#define FIL_QUERYEASFROMLIST           3
#define FIL_QUERYFULLNAME              5    /* DosQueryPathInfo */

#define DCPY_EXISTING                  0x0001
#define DCPY_APPEND                    0x0002
#define DCPY_FAILEAS                   0x0004

typedef struct
    {
    USHORT twosecs : 5;
    USHORT minutes : 6;
    USHORT hours   : 5;
    } FTIME;
typedef FTIME *PFTIME;

typedef struct
    {
    USHORT day   : 5;
    USHORT month : 4;
    USHORT year  : 7;
    } FDATE;
typedef FDATE *PFDATE;

typedef struct
    {
    BYTE fEA;
    BYTE cbName;
    USHORT cbValue;
    } FEA;
typedef FEA *PFEA;

typedef struct
    {
    ULONG cbList;
    FEA list[1];
    } FEALIST;
typedef FEALIST *PFEALIST;

typedef struct
    {
    BYTE cbName;
    CHAR szName[1];
    } GEA;
typedef GEA *PGEA;

typedef struct
    {
    ULONG cbList;
    GEA list[1];
    } GEALIST;
typedef GEALIST *PGEALIST;

typedef struct
    {
    PGEALIST fpGEAList;
    PFEALIST fpFEAList;
    ULONG oError;
    } EAOP;
typedef EAOP *PEAOP;

typedef _PACKED struct
    {
    ULONG oNextEntryOffset;
    BYTE fEA;
    BYTE cbName;
    USHORT cbValue;
    CHAR szName[1];
    } FEA2;
typedef FEA2 *PFEA2;

typedef _PACKED struct
    {
    ULONG cbList;
    FEA2 list[1];
    } FEA2LIST;
typedef FEA2LIST *PFEA2LIST;

typedef _PACKED struct
    {
    ULONG oNextEntryOffset;
    BYTE cbName;
    CHAR szName[1];
    } GEA2;
typedef GEA2 *PGEA2;

typedef _PACKED struct
    {
    ULONG cbList;
    GEA2 list[1];
    } GEA2LIST;
typedef GEA2LIST *PGEA2LIST;

typedef _PACKED struct
    {
    PGEA2LIST fpGEA2List;
    PFEA2LIST fpFEA2List;
    ULONG oError;
    } EAOP2;
typedef EAOP2 *PEAOP2;

typedef struct
    {
    FDATE  fdateCreation;
    FTIME  ftimeCreation;
    FDATE  fdateLastAccess;
    FTIME  ftimeLastAccess;
    FDATE  fdateLastWrite;
    FTIME  ftimeLastWrite;
    ULONG  cbFile;
    ULONG  cbFileAlloc;
    USHORT attrFile;
    } FILESTATUS;
typedef FILESTATUS *PFILESTATUS;

typedef struct
    {
    FDATE fdateCreation;
    FTIME ftimeCreation;
    FDATE fdateLastAccess;
    FTIME ftimeLastAccess;
    FDATE fdateLastWrite;
    FTIME ftimeLastWrite;
    ULONG cbFile;
    ULONG cbFileAlloc;
    ULONG attrFile;
    } FILESTATUS3;
typedef FILESTATUS3 *PFILESTATUS3;

typedef struct
    {
    FDATE fdateCreation;
    FTIME ftimeCreation;
    FDATE fdateLastAccess;
    FTIME ftimeLastAccess;
    FDATE fdateLastWrite;
    FTIME ftimeLastWrite;
    ULONG cbFile;
    ULONG cbFileAlloc;
    ULONG attrFile;
    ULONG cbList;
    } FILESTATUS4;
typedef FILESTATUS4 *PFILESTATUS4;

ULONG DosClose (HFILE hfFile);
ULONG DosCopy (const PSZ pszSource, const PSZ pszTarget, ULONG ulOption);
ULONG DosCreateDir (const PSZ pszDirName, PEAOP2 pEABuf);
ULONG DosCreatePipe (PHFILE phfReadHandle, PHFILE phfWriteHandle,
    ULONG ulPipeSize);
ULONG DosDelete (const PSZ pszFileName);
ULONG DosDeleteDir (const PSZ pszDirName);
ULONG DosMove (const PSZ pszOldName, const PSZ pszNewName);
ULONG DosOpen (const PSZ pszFileName, PHFILE phfFile, PULONG pulAction,
    ULONG ulFileSize, ULONG ulAttribute, ULONG ulOpenFlags, ULONG ulOpenMode,
    PEAOP2 pEABuf);
ULONG DosQueryFileInfo (HFILE hfFile, ULONG ulInfoLevel, PVOID pInfoBuffer,
    ULONG ulInfoLength);
ULONG DosRead (HFILE hfFile, PVOID pBuffer, ULONG ulLength,
    PULONG pulBytesRead);
ULONG DosWrite (HFILE hfFile, const PVOID pBuffer, ULONG ulLength,
    PULONG pulBytesWritten);

/* -------------------- NATIONAL LANGUAGE SUPPORT ------------------------- */

typedef struct
    {
    ULONG country;
    ULONG codepage;
    } COUNTRYCODE;
typedef COUNTRYCODE *PCOUNTRYCODE;

typedef struct
    {
    ULONG country;
    ULONG codepage;
    ULONG fsDateFmt;
    CHAR szCurrency[5];
    CHAR szThousandsSeparator[2];
    CHAR szDecimal[2];
    CHAR szDateSeparator[2];
    CHAR szTimeSeparator[2];
    UCHAR fsCurrencyFmt;
    UCHAR cDecimalPlace;
    UCHAR fsTimeFmt;
    USHORT abReserved1[2];
    CHAR szDataSeparator[2];
    USHORT abReserved2[5];
    } COUNTRYINFO;
typedef COUNTRYINFO *PCOUNTRYINFO;

ULONG DosMapCase (ULONG ulLength, const PCOUNTRYCODE pCountryCode,
    PCHAR pchString);
ULONG DosQueryCollate (ULONG ulLength, const PCOUNTRYCODE pCountryCode,
    PCHAR pchBuffer, PULONG pulDataLength);
ULONG DosQueryCp (ULONG ulLength, PULONG pCodePageList, PULONG pDataLength);
ULONG DosQueryCtryInfo (ULONG ulLength, PCOUNTRYCODE pCountryCode,
    PCOUNTRYINFO pCountryInfo, PULONG pulDataLength);

#endif
