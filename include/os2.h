/* os2.h (emx/gcc) */

#if !defined (_OS2_H)

#define _OS2_H

#pragma pack(1)

/* ------------------------ CONSTANTS AND TYPES --------------------------- */

#if !defined (FALSE)
#define FALSE 0
#endif

#if !defined (TRUE)
#define TRUE 1
#endif

#define VOID void

typedef unsigned short BOOL;
typedef BOOL *PBOOL;

typedef unsigned long BOOL32;
typedef BOOL *PBOOL32;

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

typedef VOID *PVOID;
typedef PVOID *PPVOID;
typedef unsigned char *PCH;
typedef unsigned char *PSZ;

typedef const VOID *CONSTPVOID;
typedef const unsigned char *CONSTPSZ;

typedef unsigned long SHANDLE;
typedef VOID *LHANDLE;

typedef SHANDLE HFILE;
typedef HFILE *PHFILE;

typedef SHANDLE HPIPE;
typedef HPIPE *PHPIPE;

typedef SHANDLE HQUEUE;
typedef HQUEUE *PHQUEUE;

typedef SHANDLE HMODULE;
typedef HMODULE *PHMODULE;

typedef ULONG PID;
typedef PID *PPID;

typedef ULONG TID;
typedef TID *PTID;

typedef int (*PFN)();
typedef PFN *PPFN;

/* ---------------------------- ERROR CODES ------------------------------- */

#define NO_ERROR                                0
#define ERROR_INVALID_FUNCTION                  1
#define ERROR_FILE_NOT_FOUND                    2
#define ERROR_PATH_NOT_FOUND                    3
#define ERROR_TOO_MANY_OPEN_FILES               4
#define ERROR_ACCESS_DENIED                     5
#define ERROR_INVALID_HANDLE                    6
#define ERROR_ARENA_TRASHED                     7
#define ERROR_NOT_ENOUGH_MEMORY                 8
#define ERROR_INVALID_BLOCK                     9
#define ERROR_BAD_ENVIRONMENT                  10
#define ERROR_BAD_FORMAT                       11
#define ERROR_INVALID_ACCESS                   12
#define ERROR_INVALID_DATA                     13
#define ERROR_INVALID_DRIVE                    15
#define ERROR_CURRENT_DIRECTORY                16
#define ERROR_NOT_SAME_DEVICE                  17
#define ERROR_NO_MORE_FILES                    18
#define ERROR_WRITE_PROTECT                    19
#define ERROR_BAD_UNIT                         20
#define ERROR_NOT_READY                        21
#define ERROR_BAD_COMMAND                      22
#define ERROR_CRC                              23
#define ERROR_BAD_LENGTH                       24
#define ERROR_SEEK                             25
#define ERROR_NOT_DOS_DISK                     26
#define ERROR_SECTOR_NOT_FOUND                 27
#define ERROR_OUT_OF_PAPER                     28
#define ERROR_WRITE_FAULT                      29
#define ERROR_READ_FAULT                       30
#define ERROR_GEN_FAILURE                      31
#define ERROR_SHARING_VIOLATION                32
#define ERROR_LOCK_VIOLATION                   33
#define ERROR_WRONG_DISK                       34
#define ERROR_SHARING_BUFFER_EXCEEDED          36
#define ERROR_CODE_PAGE_MISMATCHED             37
#define ERROR_HANDLE_EOF                       38
#define ERROR_HANDLE_DISK_FULL                 39
#define ERROR_CANNOT_MAKE                      82
#define ERROR_INVALID_PARAMETER                87
#define ERROR_NO_PROC_SLOTS                    89
#define ERROR_INTERRUPT                        95
#define ERROR_DEVICE_IN_USE                    99
#define ERROR_TOO_MANY_SEMAPHORES             100
#define ERROR_TOO_MANY_SEM_REQUESTS           103
#define ERROR_SEM_OWNER_DIED                  105
#define ERROR_DRIVE_LOCKED                    108
#define ERROR_BROKEN_PIPE                     109
#define ERROR_OPEN_FAILED                     110
#define ERROR_BUFFER_OVERFLOW                 111
#define ERROR_DISK_FULL                       112
#define ERROR_NO_MORE_SEARCH_HANDLES          113
#define ERROR_PROTECTION_VIOLATION            115
#define ERROR_INVALID_NAME                    123
#define ERROR_INVALID_LEVEL                   124
#define ERROR_PROC_NOT_FOUND                  127
#define ERROR_CHILD_NOT_COMPLETE              129
#define ERROR_DIRECT_ACCESS_HANDLE            130
#define ERROR_INVALID_SEGMENT_NUMBER          180
#define ERROR_INVALID_ORDINAL                 182
#define ERROR_ALREADY_EXISTS                  183
#define ERROR_SEM_NOT_FOUND                   187
#define ERROR_INVALID_MODULETYPE              190
#define ERROR_INVALID_EXE_SIGNATURE           191
#define ERROR_EXE_MARKED_INVALID              192
#define ERROR_ITERATED_DATA_EXCEEDS_64K       194
#define ERROR_INVALID_MINALLOCSIZE            195
#define ERROR_DYNLINK_FROM_INVALID_RING       196
#define ERROR_INVALID_SEGDPL                  198
#define ERROR_AUTODATASEG_EXCEEDS_64K         199
#define ERROR_RELOCSRC_CHAIN_EXCEEDS_SEGLIMIT 201
#define ERROR_FILENAME_EXCED_RANGE            206
#define ERROR_LOCKED                          212
#define ERROR_NO_CHILDREN                     228
#define ERROR_INVALID_SCREEN_GROUP            229
#define ERROR_BAD_PIPE                        230
#define ERROR_PIPE_BUSY                       231
#define ERROR_NO_DATA                         232
#define ERROR_PIPE_NOT_CONNECTED              233
#define ERROR_MORE_DATA                       234
#define ERROR_CIRCULARITY_REQUESTED           250
#define ERROR_DIRECTORY_IN_CDS                251
#define ERROR_INVALID_EA_NAME                 254
#define ERROR_EA_LIST_INCONSISTENT            255
#define ERROR_DIRECTORY                       267
#define ERROR_EAS_DIDNT_FIT                   275
#define ERROR_EAS_NOT_SUPPORTED               282
#define ERROR_NEED_EAS_FOUND                  283
#define ERROR_DUPLICATE_HANDLE                284
#define ERROR_DUPLICATE_NAME                  285
#define ERROR_EMPTY_MUXWAIT                   286
#define ERROR_MUTEX_OWNED                     287
#define ERROR_NOT_OWNER                       288
#define ERROR_PARAM_TOO_SMALL                 289
#define ERROR_TOO_MANY_HANDLES                290
#define ERROR_TOO_MANY_OPENS                  291
#define ERROR_WRONG_TYPE                      292
#define ERROR_INIT_ROUTINE_FAILED             295
#define ERROR_TOO_MANY_POSTS                  298
#define ERROR_ALREADY_POSTED                  299
#define ERROR_ALREADY_RESET                   300
#define ERROR_SEM_BUSY                        301
#define ERROR_INVALID_PROCID                  303
#define ERROR_INVALID_PDELTA                  304
#define ERROR_INVALID_PCLASS                  307
#define ERROR_INVALID_SCOPE                   308
#define ERROR_INVALID_THREADID                309
#define ERROR_DOSSUB_SHRINK                   310
#define ERROR_DOSSUB_NOMEM                    311
#define ERROR_DOSSUB_OVERLAP                  312
#define ERROR_NLS_OPEN_FAILED                 397
#define ERROR_NLS_NO_CTRY_CODE                398
#define ERROR_NLS_TABLE_TRUNCATED             399
#define ERROR_NLS_TYPE_NOT_FOUND              401
#define ERROR_CPLIST_TOO_SMALL                473
#define ERROR_CP_NOT_MOVED                    474
#define ERROR_CODE_PAGE_NOT_FOUND             476
#define ERROR_INVALID_ADDRESS                 487
#define ERROR_DOSSUB_CORRUPTED                532
#define ERROR_TIMEOUT                         640
#define ERROR_MODULE_CORRUPTED                731
#define ERROR_CROSSES_OBJECT_BOUNDARY       32798
#define ERROR_ENTRY_IS_CALLGATE             65079

/* ----------------------------- ERRORS ----------------------------------- */

#define ERRACT_RETRY            1
#define ERRACT_DLYRET           2
#define ERRACT_USER             3
#define ERRACT_ABORT            4
#define ERRACT_PANIC            5
#define ERRACT_IGNORE           6
#define ERRACT_INTRET           7

#define ERRCLASS_OUTRES         1
#define ERRCLASS_TEMPSIT        2
#define ERRCLASS_AUTH           3
#define ERRCLASS_INTRN          4
#define ERRCLASS_HRDFAIL        5
#define ERRCLASS_SYSFAIL        6
#define ERRCLASS_APPERR         7
#define ERRCLASS_NOTFND         8
#define ERRCLASS_BADFMT         9
#define ERRCLASS_LOCKED         10
#define ERRCLASS_MEDIA          11
#define ERRCLASS_ALREADY        12
#define ERRCLASS_UNK            13
#define ERRCLASS_CANT           14
#define ERRCLASS_TIME           15

#define ERRLOC_UNK              1
#define ERRLOC_DISK             2
#define ERRLOC_NET              3
#define ERRLOC_SERDEV           4
#define ERRLOC_MEM              5

#define FERR_DISABLEHARDERR     0x0000L
#define FERR_ENABLEHARDERR      0x0001L
#define FERR_ENABLEEXCEPTION    0x0000L
#define FERR_DISABLEEXCEPTION   0x0002L

ULONG DosErrClass (ULONG ulCode, PULONG pulClass, PULONG pulAction,
    PULONG pulLocus);
ULONG DosError (ULONG ulError);

/* ------------------------- MEMORY MANAGEMENT ---------------------------- */

#define PAG_READ                0x0001
#define PAG_WRITE               0x0002
#define PAG_EXECUTE             0x0004
#define PAG_GUARD               0x0008
#define PAG_COMMIT              0x0010
#define OBJ_TILE                0x0040
#define OBJ_PROTECTED           0x0080
#define OBJ_GETTABLE            0x0100
#define OBJ_GIVEABLE            0x0200
#define PAG_DEFAULT             0x0400
#define PAG_SHARED              0x2000
#define PAG_FREE                0x4000

#define DOSSUB_INIT             0x0001
#define DOSSUB_GROW             0x0002
#define DOSSUB_SPARSE_OBJ       0x0004
#define DOSSUB_SERIALIZE        0x0008

ULONG DosAllocMem (PPVOID pBaseAddress, ULONG ulObjectSize,
    ULONG ulAllocationFlags);
ULONG DosAllocSharedMem (PPVOID pBaseAddress, CONSTPSZ pszName,
    ULONG ulObjectSize, ULONG ulAllocationFlags);
ULONG DosFreeMem (PVOID pBaseAddress);
ULONG DosGetNamedSharedMem (PPVOID pBaseAddress, CONSTPSZ pszSharedMemName,
    ULONG ulAttributeFlags);
ULONG DosGetSharedMem (CONSTPVOID pBaseAddress, PULONG pulAttributeFlags);
ULONG DosGiveSharedMem (CONSTPVOID pBaseAddress, PID idProcessId,
    ULONG ulAttributeFlags);
ULONG DosQueryMem (CONSTPVOID pBaseAddress, PULONG pulRegionSize,
    PULONG pulAllocationFlags);
ULONG DosSetMem (CONSTPVOID pBaseAddress, ULONG ulRegionSize,
    ULONG ulAttributeFlags);
ULONG DosSubAllocMem (PVOID pOffset, PPVOID pBlockOffset, ULONG ulSize);
ULONG DosSubFreeMem (PVOID pOffset, PVOID pBlockOffset, ULONG ulSize);
ULONG DosSubSetMem (PVOID pOffset, ULONG ulFlags, ULONG ulSize);
ULONG DosSubUnsetMem (PVOID pOffset);

/* --------------------------- FILE SYSTEM -------------------------------- */

#define CCHMAXPATH              260
#define CCHMAXPATHCOMP          256

#define FILE_NORMAL             0x0000
#define FILE_READONLY           0x0001
#define FILE_HIDDEN             0x0002
#define FILE_SYSTEM             0x0004
#define FILE_DIRECTORY          0x0010
#define FILE_ARCHIVED           0x0020

#define FILE_EXISTED            0x0001
#define FILE_CREATED            0x0002
#define FILE_TRUNCATED          0x0003

#define FILE_OPEN               0x0001
#define FILE_TRUNCATE           0x0002
#define FILE_CREATE             0x0010

#define FILE_BEGIN              0
#define FILE_CURRENT            1
#define FILE_END                2

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

#define FIL_STANDARD            1
#define FIL_QUERYEASIZE         2
#define FIL_QUERYEASFROMLIST    3
#define FIL_QUERYFULLNAME       5    /* DosQueryPathInfo */

#define FSAIL_QUERYNAME         1
#define FSAIL_DEVNUMBER         2
#define FSAIL_DRVNUMBER         3

#define FSAT_CHARDEV            1
#define FSAT_PSEUDODEV          2
#define FSAT_LOCALDRV           3
#define FSAT_REMOTEDRV          4

#define DCPY_EXISTING           0x0001
#define DCPY_APPEND             0x0002
#define DCPY_FAILEAS            0x0004

#define HDIR_SYSTEM             1
#define HDIR_CREATE             (-1)

#define FILE_IGNORE             0x10000

#define MUST_HAVE_READONLY      (FILE_READONLY  | (FILE_READONLY  << 8))
#define MUST_HAVE_HIDDEN        (FILE_HIDDEN    | (FILE_HIDDEN    << 8))
#define MUST_HAVE_SYSTEM        (FILE_SYSTEM    | (FILE_SYSTEM    << 8))
#define MUST_HAVE_DIRECTORY     (FILE_DIRECTORY | (FILE_DIRECTORY << 8))
#define MUST_HAVE_ARCHIVED      (FILE_ARCHIVED  | (FILE_ARCHIVED  << 8))

#define EAT_BINARY              0xfffe
#define EAT_ASCII               0xfffd
#define EAT_BITMAP              0xfffb
#define EAT_METAFILE            0xfffa
#define EAT_ICON                0xfff9
#define EAT_EA                  0xffee
#define EAT_MVMT                0xffdf
#define EAT_MVST                0xffde
#define EAT_ASN1                0xffdd

typedef SHANDLE HDIR;
typedef HDIR *PHDIR;

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
    ULONG idFileSystem;
    ULONG cSectorUnit;
    ULONG cUnit;
    ULONG cUnitAvail;
    USHORT cbSector;
    } FSALLOCATE;
typedef FSALLOCATE *PFSALLOCATE;

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

typedef struct
    {
    ULONG oNextEntryOffset;
    BYTE fEA;
    BYTE cbName;
    USHORT cbValue;
    CHAR szName[1];
    } FEA2;
typedef FEA2 *PFEA2;

typedef struct
    {
    ULONG cbList;
    FEA2 list[1];
    } FEA2LIST;
typedef FEA2LIST *PFEA2LIST;

typedef struct
    {
    ULONG oNextEntryOffset;
    BYTE cbName;
    CHAR szName[1];
    } GEA2;
typedef GEA2 *PGEA2;

typedef struct
    {
    ULONG cbList;
    GEA2 list[1];
    } GEA2LIST;
typedef GEA2LIST *PGEA2LIST;

typedef struct
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
    USHORT attrFile;
    ULONG cbList;
    } FILESTATUS2;
typedef FILESTATUS2 *PFILESTATUS2;

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

typedef struct
    {
    USHORT iType;
    USHORT cbName;
    USHORT cbFSDName;
    USHORT cbFSAData;
    UCHAR szName[1];
    UCHAR szFSDName[1];
    UCHAR rgFSAData[1];
    } FSQBUFFER2;
typedef FSQBUFFER2 *PFSQBUFFER2;

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
    USHORT attrFile;
    UCHAR cchName;
    CHAR achName[CCHMAXPATHCOMP];
    } FILEFINDBUF;
typedef FILEFINDBUF *PFILEFINDBUF;

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
    USHORT attrFile;
    ULONG cbList;
    UCHAR cchName;
    CHAR achName[CCHMAXPATHCOMP];
    } FILEFINDBUF2;
typedef FILEFINDBUF2 *PFILEFINDBUF2;

typedef struct
    {
    ULONG oNextEntryOffset;
    FDATE fdateCreation;
    FTIME ftimeCreation;
    FDATE fdateLastAccess;
    FTIME ftimeLastAccess;
    FDATE fdateLastWrite;
    FTIME ftimeLastWrite;
    ULONG cbFile;
    ULONG cbFileAlloc;
    ULONG attrFile;
    UCHAR cchName;
    CHAR achName[CCHMAXPATHCOMP];
    } FILEFINDBUF3;
typedef FILEFINDBUF3 *PFILEFINDBUF3;

typedef struct
    {
    ULONG oNextEntryOffset;
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
    UCHAR cchName;
    CHAR achName[CCHMAXPATHCOMP];
    } FILEFINDBUF4;
typedef FILEFINDBUF4 *PFILEFINDBUF4;

ULONG DosClose (HFILE hfFile);
ULONG DosCopy (CONSTPSZ pszSource, CONSTPSZ pszTarget, ULONG ulOption);
ULONG DosCreateDir (CONSTPSZ pszDirName, PEAOP2 pEABuf);
ULONG DosCreatePipe (PHFILE phfReadHandle, PHFILE phfWriteHandle,
    ULONG ulPipeSize);
ULONG DosDelete (CONSTPSZ pszFileName);
ULONG DosDeleteDir (CONSTPSZ pszDirName);
ULONG DosDupHandle (HFILE hFile, PHFILE phFile);
ULONG DosEditName (ULONG ulLevel, CONSTPSZ pszSource, CONSTPSZ pszEdit,
    PBYTE pszTargetBuf, ULONG ulTargetBufLength);
ULONG DosFindClose (HDIR hDir);
ULONG DosFindFirst (CONSTPSZ pszFileSpec, PHDIR phDir, ULONG flAttribute,
    PVOID pFindBuf, ULONG ulFindBufLength, PULONG pulFileNames,
    ULONG ulInfoLevel);
ULONG DosFindNext (HDIR hDir, PVOID pFindBuf, ULONG ulFindBufLength,
    PULONG pulFileNames);
ULONG DosMove (CONSTPSZ pszOldName, CONSTPSZ pszNewName);
ULONG DosOpen (CONSTPSZ pszFileName, PHFILE phfFile, PULONG pulAction,
    ULONG ulFileSize, ULONG ulAttribute, ULONG ulOpenFlags, ULONG ulOpenMode,
    PEAOP2 pEABuf);
ULONG DosQueryCurrentDisk (PULONG pulDiskNum, PULONG pulLogical);
ULONG DosQueryFHState (HFILE hFile, PULONG pulMode);
ULONG DosQueryFileInfo (HFILE hfFile, ULONG ulInfoLevel, PVOID pInfoBuffer,
    ULONG ulInfoLength);
ULONG DosQueryFSAttach (CONSTPSZ pszDeviceName, ULONG ulOrdinal,
    ULONG ulFSAInfoLevel, PFSQBUFFER2 pfsqb, PULONG pulBufLength);
ULONG DosQueryHType (HFILE hFile, PULONG pulType, PULONG pulAttr);
ULONG DosQueryPathInfo (CONSTPSZ pszPathName, ULONG ulInfoLevel,
    PVOID pInfoBuffer, ULONG ulInfoLength);
ULONG DosRead (HFILE hfFile, PVOID pBuffer, ULONG ulLength,
    PULONG pulBytesRead);
ULONG DosResetBuffer (HFILE hf);
ULONG DosSetCurrentDir (CONSTPSZ pszDir);
ULONG DosSetDefaultDisk (ULONG ulDiskNum);
ULONG DosSetFHState (HFILE hFile, ULONG ulMode);
ULONG DosSetFileInfo (HFILE hf, ULONG ulInfoLevel, PVOID pInfoBuffer,
    ULONG ulInfoLength);
ULONG DosSetFilePtr (HFILE hf, LONG ulOffset, ULONG ulOrigin, PULONG ulPos);
ULONG DosSetFileSize (HFILE hf, ULONG ulSize);
ULONG DosSetMaxFH (ULONG ulCount);
ULONG DosSetPathInfo (CONSTPSZ pszPathName, ULONG ulInfoLevel,
    PVOID pInfoBuffer, ULONG ulInfoLength, ULONG ulOptions);
ULONG DosSetRelMaxFH (PLONG pulReqCount, PULONG pulCurMaxFH);
ULONG DosShutdown (ULONG ulReserved);
ULONG DosWrite (HFILE hfFile, CONSTPVOID pBuffer, ULONG ulLength,
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

ULONG DosMapCase (ULONG ulLength, const COUNTRYCODE *pCountryCode,
    PCHAR pchString);
ULONG DosQueryCollate (ULONG ulLength, const COUNTRYCODE *pCountryCode,
    PCHAR pchBuffer, PULONG pulDataLength);
ULONG DosQueryCp (ULONG ulLength, PULONG pCodePageList, PULONG pDataLength);
ULONG DosQueryCtryInfo (ULONG ulLength, PCOUNTRYCODE pCountryCode,
    PCOUNTRYINFO pCountryInfo, PULONG pulDataLength);
ULONG DosQueryDBCSEnv (ULONG ulLength, PCOUNTRYCODE pCountryCode, PCHAR pBuf);
ULONG DosSetProcessCp (ULONG ulCodePage);

/* -------------------------- DYNAMIC LINKING ----------------------------- */

#define PT_16BIT                0
#define PT_32BIT                1

ULONG DosFreeModule (HMODULE hmod);
ULONG DosLoadModule (PSZ pszObject, ULONG uObjectLen, CONSTPSZ pszModule,
    PHMODULE phmod);
ULONG DosQueryModuleHandle (CONSTPSZ pszModname, PHMODULE phmod);
ULONG DosQueryModuleName (HMODULE hmod, ULONG ulNameLength, PCHAR pNameBuf);
ULONG DosQueryProcAddr (HMODULE hmod, ULONG ulOrdinal, CONSTPSZ pszProcName,
    PPFN pProcAddr);
ULONG DosQueryProcType (HMODULE hmod, ULONG ulOrdinal, CONSTPSZ pszProcName,
     PULONG pulProcType);

/* -------------------------------- TASKS --------------------------------- */

#define DCWA_PROCESS            0
#define DCWA_PROCESSTREE        1

#define DCWW_WAIT               0
#define DCWW_NOWAIT             1

#define DKP_PROCESSTREE         0
#define DKP_PROCESS             1

#define EXEC_SYNC               0
#define EXEC_ASYNC              1
#define EXEC_ASYNCRESULT        2
#define EXEC_TRACE              3
#define EXEC_BACKGROUND         4
#define EXEC_LOAD               5
#define EXEC_ASYNCRESULTDB      6

#define EXIT_THREAD             0
#define EXIT_PROCESS            1

#define EXLST_ADD               1
#define EXLST_REMOVE            2
#define EXLST_EXIT              3

#define PRTYC_NOCHANGE          0
#define PRTYC_IDLETIME          1
#define PRTYC_REGULAR           2
#define PRTYC_TIMECRITICAL      3
#define PRTYC_FOREGROUNDSERVER  4

#define PRTYD_MINIMUM           (-31)
#define PRTYD_MAXIMUM           31

#define PRTYS_PROCESS           0
#define PRTYS_PROCESSTREE       1
#define PRTYS_THREAD            2

#define TC_EXIT                 0
#define TC_HARDERROR            1
#define TC_TRAP                 2
#define TC_KILLPROCESS          3
#define TC_EXCEPTION            4

typedef struct
    {
    ULONG codeTerminate;
    ULONG codeResult;
    } RESULTCODES;
typedef RESULTCODES *PRESULTCODES;

typedef struct
    {
    ULONG tib2_ultid;
    ULONG tib2_ulpri;
    ULONG tib2_version;
    USHORT tib2_usMCCount;
    USHORT tib2_fMCForceFlag;
    } TIB2;
typedef TIB2 *PTIB2;

typedef struct
    {
    PVOID tib_pexchain;
    PVOID tib_pstack;
    PVOID tib_pstacklimit;
    PTIB2 tib_ptib2;
    ULONG tib_version;
    PVOID tib_arbpointer;
    } TIB;
typedef TIB *PTIB;

typedef struct
    {
    ULONG pib_ulpid;
    ULONG pib_ulppid;
    ULONG pib_hmte;
    PCHAR pib_pchcmd;
    PCHAR pib_pchenv;
    ULONG pib_flstatus;
    ULONG pib_ultype;
    } PIB;
typedef PIB *PPIB;

typedef VOID (*PFNTHREAD)(ULONG ulThreadArg);
typedef VOID (*PFNEXITLIST)(ULONG ulArg);

ULONG DosBeep (ULONG ulFrequency, ULONG ulDuration);
ULONG DosCreateThread (PTID ptidThreadID, PFNTHREAD pfnThreadAddr,
    ULONG ulThreadArg, ULONG ulFlags, ULONG ulStackSize);
ULONG DosEnterCritSec (VOID);
ULONG DosExecPgm (PCHAR pObjname, LONG lObjnameLength, ULONG ulFlagS,
    CONSTPSZ pszArg, CONSTPSZ pszEnv, PRESULTCODES pReturnCodes,
    CONSTPSZ pszName);
VOID volatile DosExit (ULONG ulAction, ULONG ulResult);
ULONG DosExitCritSec (VOID);
ULONG DosExitList (ULONG ulOrder, PFNEXITLIST pfn);
ULONG DosGetInfoBlocks (PTIB *ptib, PPIB *ppib);
ULONG DosKillProcess (ULONG ulAction, PID pid);
ULONG DosKillThread (TID tid);
ULONG DosResumeThread (TID tid);
ULONG DosSetPriority (ULONG ulScope, ULONG ulClass, LONG lDelta, ULONG ulID);
ULONG DosSleep (ULONG ulInterval);
ULONG DosSuspendThread (TID tid);
ULONG DosWaitChild (ULONG ulAction, ULONG ulWait, PRESULTCODES pReturnCodes,
    PPID ppidOut, PID pidIn);
ULONG DosWaitThread (PTID ptid, ULONG ulWait);

/* ------------------------------ SESSIONS -------------------------------- */

#define SSF_RELATED_INDEPENDENT 0
#define SSF_RELATED_CHILD       1

#define SSF_FGBG_FORE           0
#define SSF_FGBG_BACK           1

#define SSF_TRACEOPT_NONE       0
#define SSF_TRACEOPT_TRACE      1
#define SSF_TRACEOPT_TRACEALL   2

#define SSF_INHERTOPT_SHELL     0
#define SSF_INHERTOPT_PARENT    1

#define SSF_TYPE_DEFAULT        0
#define SSF_TYPE_FULLSCREEN     1
#define SSF_TYPE_WINDOWABLEVIO  2
#define SSF_TYPE_PM             3
#define SSF_TYPE_VDM            4
#define SSF_TYPE_GROUP          5
#define SSF_TYPE_DLL            6
#define SSF_TYPE_WINDOWEDVDM    7
#define SSF_TYPE_PDD            8
#define SSF_TYPE_VDD            9

#define SSF_CONTROL_VISIBLE     0x0000
#define SSF_CONTROL_INVISIBLE   0x0001
#define SSF_CONTROL_MAXIMIZE    0x0002
#define SSF_CONTROL_MINIMIZE    0x0004
#define SSF_CONTROL_NOAUTOCLOSE 0x0008
#define SSF_CONTROL_SETPOS      0x8000

#define SET_SESSION_UNCHANGED          0
#define SET_SESSION_SELECTABLE         1
#define SET_SESSION_NON_SELECTABLE     2
#define SET_SESSION_BOND               1
#define SET_SESSION_NO_BOND            2

#define STOP_SESSION_SPECIFIED         0
#define STOP_SESSION_ALL               1

#define FAPPTYP_NOTSPEC         0x0000
#define FAPPTYP_NOTWINDOWCOMPAT 0x0001
#define FAPPTYP_WINDOWCOMPAT    0x0002
#define FAPPTYP_WINDOWAPI       0x0003
#define FAPPTYP_BOUND           0x0008
#define FAPPTYP_DLL             0x0010
#define FAPPTYP_DOS             0x0020
#define FAPPTYP_PHYSDRV         0x0040
#define FAPPTYP_VIRTDRV         0x0080
#define FAPPTYP_PROTDLL         0x0100
#define FAPPTYP_WINDOWSREAL     0x0200
#define FAPPTYP_WINDOWSPROT     0x0400
#define FAPPTYP_32BIT           0x4000
#define FAPPTYP_EXETYPE         0x0003
#define FAPPTYP_RESERVED        ~(FAPPTYP_WINDOWAPI | FAPPTYP_BOUND | \
                                  FAPPTYP_DLL | FAPPTYP_DOS | \
                                  FAPPTYP_PHYSDRV | FAPPTYP_VIRTDRV | \
                                  FAPPTYP_PROTDLL | FAPPTYP_32BIT)

typedef struct
    {
    USHORT Length;
    USHORT Related;
    USHORT FgBg;
    USHORT TraceOpt;
    PSZ PgmTitle;
    PSZ PgmName;
    PBYTE PgmInputs;
    PBYTE TermQ;
    PBYTE Environment;
    USHORT InheritOpt;
    USHORT SessionType;
    PSZ IconFile;
    ULONG PgmHandle;
    USHORT PgmControl;
    USHORT InitXPos;
    USHORT InitYPos;
    USHORT InitXSize;
    USHORT InitYSize;
    USHORT Reserved;
    PSZ ObjectBuffer;
    ULONG ObjectBuffLen;
    } STARTDATA;
typedef STARTDATA *PSTARTDATA;

typedef struct
    {
    USHORT Length;
    USHORT SelectInd;
    USHORT BondInd;
    } STATUSDATA;
typedef STATUSDATA *PSTATUSDATA;

ULONG DosQueryAppType (PSZ pszName, PULONG pulFlags);
ULONG DosSelectSession (ULONG ulIDSession);
ULONG DosSetSession (ULONG ulIDSession, PSTATUSDATA psd);
ULONG DosStartSession (PSTARTDATA psd, PULONG pulIDSession, PPID ppid);
ULONG DosStopSession (ULONG ulScope, ULONG ulIDSession);

/* ----------------------------- SEMAPHORES ------------------------------- */

#define SEM_INDEFINITE_WAIT     (-1L)
#define SEM_IMMEDIATE_RETURN    0L

#define DC_SEM_SHARED           0x01
#define DCMW_WAIT_ANY           0x02
#define DCMW_WAIT_ALL           0x04

typedef ULONG HEV;
typedef HEV *PHEV;

ULONG DosCloseEventSem (HEV hev);
ULONG DosCreateEventSem (CONSTPSZ pszName, PHEV phev, ULONG ulAttr,
    BOOL32 fState);
ULONG DosOpenEventSem (CONSTPSZ pszName, PHEV phev);
ULONG DosPostEventSem (HEV hev);
ULONG DosQueryEventSem (HEV hev, PULONG pulCount);
ULONG DosResetEventSem (HEV hev, PULONG pulCount);
ULONG DosWaitEventSem (HEV hev, ULONG ulTimeout);

typedef ULONG HMTX;
typedef HMTX *PHMTX;

ULONG DosCloseMutexSem (HMTX hmtx);
ULONG DosCreateMutexSem (CONSTPSZ pszName, PHMTX phmtx, ULONG ulAttr,
    BOOL32 fState);
ULONG DosOpenMutexSem (CONSTPSZ pszName, PHMTX phmtx);
ULONG DosQueryMutexSem (HMTX hmtx, PPID ppid, PTID ptid, PULONG pulCount);
ULONG DosReleaseMutexSem (HMTX hmtx);
ULONG DosRequestMutexSem (HMTX hmtx, ULONG ulTimeout);

typedef ULONG HMUX;
typedef HMUX *PHMUX;

typedef VOID *HSEM;
typedef HSEM *PHSEM;

typedef struct
    {
    HSEM hsemCur;
    ULONG ulUser;
    } SEMRECORD;
typedef SEMRECORD *PSEMRECORD;

ULONG DosAddMuxWaitSem (HMUX hmux, PSEMRECORD pSemRec);
ULONG DosCloseMuxWaitSem (HMUX hmux);
ULONG DosCreateMuxWaitSem (CONSTPSZ pszName, PHMUX phmux, ULONG ulcSemRec,
    PSEMRECORD pSemRec, ULONG ulAttr);
ULONG DosDeleteMuxWaitSem (HMUX hmux, HSEM hSem);
ULONG DosOpenMuxWaitSem (CONSTPSZ pszName, PHMUX phmux);
ULONG DosQueryMuxWaitSem (HMUX hmux, PULONG pulcSemRec, PSEMRECORD pSemRec,
    PULONG pulAttr);
ULONG DosWaitMuxWaitSem (HMUX hmux, ULONG ulTimeout, PULONG pulUser);

/* ---------------------------- NAMED PIPES ------------------------------- */

#define NP_INDEFINITE_WAIT      (-1)
#define NP_DEFAULT_WAIT         0

#define NP_STATE_DISCONNECTED   1
#define NP_STATE_LISTENING      2
#define NP_STATE_CONNECTED      3
#define NP_STATE_CLOSING        4

#define NP_ACCESS_INBOUND       0x0000
#define NP_ACCESS_OUTBOUND      0x0001
#define NP_ACCESS_DUPLEX        0x0002
#define NP_INHERIT              0x0000
#define NP_NOINHERIT            0x0080
#define NP_WRITEBEHIND          0x0000
#define NP_NOWRITEBEHIND        0x4000

#define NP_READMODE_BYTE        0x0000
#define NP_READMODE_MESSAGE     0x0100
#define NP_TYPE_BYTE            0x0000
#define NP_TYPE_MESSAGE         0x0400
#define NP_END_CLIENT           0x0000
#define NP_END_SERVER           0x4000
#define NP_WAIT                 0x0000
#define NP_NOWAIT               0x8000
#define NP_UNLIMITED_INSTANCES  0x00ff

#define NPSS_EOI                0
#define NPSS_RDATA              1
#define NPSS_WSPACE             2
#define NPSS_CLOSE              3

#define NPSS_WAIT               0x0001

typedef struct
    {
    USHORT cbpipe;
    USHORT cbmessage;
    } AVAILDATA;
typedef AVAILDATA *PAVAILDATA;

typedef struct
    {
    USHORT cbOut;
    USHORT cbIn;
    BYTE cbMaxInst;
    BYTE cbCurInst;
    BYTE cbName;
    CHAR szName[1];
    } PIPEINFO;
typedef PIPEINFO *PPIPEINFO;

typedef struct
    {
    BYTE fStatus;
    BYTE fFlag;
    USHORT usKey;
    USHORT usAvail;
    } PIPESEMSTATE;
typedef PIPESEMSTATE *PPIPESEMSTATE;

ULONG DosCallNPipe (CONSTPSZ pszName, PVOID pInbuf, ULONG ulInbufLength,
    PVOID pOutbuf, ULONG ulOutbufSize, PULONG pulActualLength,
    ULONG ulTimeout);
ULONG DosConnectNPipe (HPIPE hpipe);
ULONG DosCreateNPipe (CONSTPSZ pszName, PHPIPE phpipe, ULONG ulOpenMode,
    ULONG ulPipeMode, ULONG ulInbufLength, ULONG ulOutbufLength,
    ULONG ulTimeout);
ULONG DosDisConnectNPipe (HPIPE hpipe);
ULONG DosPeekNPipe (HPIPE hpipe, PVOID pBuf, ULONG ulBufLength,
    PULONG pulActualLength, PAVAILDATA pAvail, PULONG pulState);
ULONG DosQueryNPHState (HPIPE hpipe, PULONG pulState);
ULONG DosQueryNPipeInfo (HPIPE hpipe, ULONG ulInfoLevel, PVOID pBuf,
    ULONG ulBufLength);
ULONG DosQueryNPipeSemState (HSEM hsem, PPIPESEMSTATE pState,
    ULONG ulBufLength);
ULONG DosSetNPHState (HPIPE hpipe, ULONG ulState);
ULONG DosSetNPipeSem (HPIPE hpipe, HSEM hsem, ULONG ulKey);
ULONG DosTransactNPipe (HPIPE hpipe, PVOID pOutbuf, ULONG ulOutbufLength,
    PVOID pInbuf, ULONG ulInbufLength, PULONG pulBytesRead);
ULONG DosWaitNPipe (CONSTPSZ pszName, ULONG ulTimeout);

/* ------------------------------- QUEUES --------------------------------- */

#define QUE_FIFO                0x0000L
#define QUE_LIFO                0x0001L
#define QUE_PRIORITY            0x0002L
#define QUE_NOCONVERT_ADDRESS   0x0000L
#define QUE_CONVERT_ADDRESS     0x0004L

typedef struct
    {
    PID pid;
    ULONG ulData;
    } REQUESTDATA;
typedef REQUESTDATA *PREQUESTDATA;

ULONG DosCloseQueue (HQUEUE hq);
ULONG DosCreateQueue (PHQUEUE phq, ULONG ulPriority, CONSTPSZ pszName);
ULONG DosOpenQueue (PPID ppid, PHQUEUE phq, CONSTPSZ pszName);
ULONG DosPeekQueue (HQUEUE hq, PREQUESTDATA pRequest, PULONG pulDataLength,
    PPVOID pDataAddress, PULONG pulElement, BOOL32 fNowait, PBYTE pPriority,
    HEV hsem);
ULONG DosPurgeQueue (HQUEUE hq);
ULONG DosQueryQueue (HQUEUE hq, PULONG pulCount);
ULONG DosReadQueue (HQUEUE hq, PREQUESTDATA pRequest, PULONG pulDataLength,
    PPVOID pDataAddress, ULONG pulElement, BOOL32 fNowait, PBYTE pPriority,
    HEV hsem);
ULONG DosWriteQueue (HQUEUE hq, ULONG ulRequest, ULONG ulDataLength,
    PVOID pData, ULONG ulPriority);

/* --------------------------- EXCEPTIONS --------------------------------- */

#define CONTEXT_CONTROL         0x0001L
#define CONTEXT_INTEGER         0x0002L
#define CONTEXT_SEGMENTS        0x0004L
#define CONTEXT_FLOATING_POINT  0x0008L
#define CONTEXT_FULL            (CONTEXT_CONTROL | CONTEXT_INTEGER \
                                 | CONTEXT_SEGMENTS | CONTEXT_FLOATING_POINT)

#define EH_NONCONTINUABLE       0x0001
#define EH_UNWINDING            0x0002
#define EH_EXIT_UNWIND          0x0004
#define EH_STACK_INVALID        0x0008
#define EH_NESTED_CALL          0x0010

#define SIG_UNSETFOCUS          0
#define SIG_SETFOCUS            1

#define UNWIND_ALL              0

#define XCPT_CONTINUE_SEARCH    0x00000000
#define XCPT_CONTINUE_EXECUTION 0xffffffff
#define XCPT_CONTINUE_STOP      0x00716668

#define XCPT_SIGNAL_INTR        1
#define XCPT_SIGNAL_KILLPROC    3
#define XCPT_SIGNAL_BREAK       4

#define XCPT_FATAL_EXCEPTION    0xc0000000
#define XCPT_SEVERITY_CODE      0xc0000000
#define XCPT_CUSTOMER_CODE      0x20000000
#define XCPT_FACILITY_CODE      0x1fff0000
#define XCPT_EXCEPTION_CODE     0x0000ffff

#define XCPT_UNKNOWN_ACCESS     0x00000000
#define XCPT_READ_ACCESS        0x00000001
#define XCPT_WRITE_ACCESS       0x00000002
#define XCPT_EXECUTE_ACCESS     0x00000004
#define XCPT_SPACE_ACCESS       0x00000008
#define XCPT_LIMIT_ACCESS       0x00000010
#define XCPT_DATA_UNKNOWN       0xffffffff

#define XCPT_GUARD_PAGE_VIOLATION       0x80000001
#define XCPT_UNABLE_TO_GROW_STACK       0x80010001
#define XCPT_ACCESS_VIOLATION           0xc0000005
#define XCPT_IN_PAGE_ERROR              0xc0000006
#define XCPT_ILLEGAL_INSTRUCTION        0xc000001c
#define XCPT_INVALID_LOCK_SEQUENCE      0xc000001d
#define XCPT_NONCONTINUABLE_EXCEPTION   0xc0000024
#define XCPT_INVALID_DISPOSITION        0xc0000025
#define XCPT_UNWIND                     0xc0000026
#define XCPT_BAD_STACK                  0xc0000027
#define XCPT_INVALID_UNWIND_TARGET      0xc0000028
#define XCPT_ARRAY_BOUNDS_EXCEEDED      0xc0000093
#define XCPT_FLOAT_DENORMAL_OPERAND     0xc0000094
#define XCPT_FLOAT_DIVIDE_BY_ZERO       0xc0000095
#define XCPT_FLOAT_INEXACT_RESULT       0xc0000096
#define XCPT_FLOAT_INVALID_OPERATION    0xc0000097
#define XCPT_FLOAT_OVERFLOW             0xc0000098
#define XCPT_FLOAT_STACK_CHECK          0xc0000099
#define XCPT_FLOAT_UNDERFLOW            0xc000009a
#define XCPT_INTEGER_DIVIDE_BY_ZERO     0xc000009b
#define XCPT_INTEGER_OVERFLOW           0xc000009c
#define XCPT_PRIVILEGED_INSTRUCTION     0xc000009d
#define XCPT_DATATYPE_MISALIGNMENT      0xc000009e
#define XCPT_BREAKPOINT                 0xc000009f
#define XCPT_SINGLE_STEP                0xc00000a0
#define XCPT_PROCESS_TERMINATE          0xc0010001
#define XCPT_ASYNC_PROCESS_TERMINATE    0xc0010002
#define XCPT_SIGNAL                     0xc0010003

typedef struct
    {
    ULONG losig;
    ULONG hisig;
    USHORT signexp;
    } FPREG;
typedef FPREG *PFPREG;

typedef struct
    {
    ULONG ContextFlags;
    ULONG ctx_env[7];
    FPREG ctx_stack[8];
    ULONG ctx_SegGs;
    ULONG ctx_SegFs;
    ULONG ctx_SegEs;
    ULONG ctx_SegDs;
    ULONG ctx_RegEdi;
    ULONG ctx_RegEsi;
    ULONG ctx_RegEax;
    ULONG ctx_RegEbx;
    ULONG ctx_RegEcx;
    ULONG ctx_RegEdx;
    ULONG ctx_RegEbp;
    ULONG ctx_RegEip;
    ULONG ctx_SegCs;
    ULONG ctx_EFlags;
    ULONG ctx_RegEsp;
    ULONG ctx_SegSs;
    } CONTEXTRECORD;
typedef CONTEXTRECORD *PCONTEXTRECORD;

#define EXCEPTION_MAXIMUM_PARAMETERS 4

typedef struct _EXCEPTIONREPORTRECORD
    {
    ULONG ExceptionNum;
    ULONG fHandlerFlags;
    struct _EXCEPTIONREPORTRECORD *NestedExceptionReportRecord;
    PVOID ExceptionAddress;
    ULONG cParameters;
    ULONG ExceptionInfo[EXCEPTION_MAXIMUM_PARAMETERS];
    } EXCEPTIONREPORTRECORD;
typedef EXCEPTIONREPORTRECORD *PEXCEPTIONREPORTRECORD;

struct _EXCEPTIONREGISTRATIONRECORD;

typedef ULONG (*ERR)(PEXCEPTIONREPORTRECORD pReport,
    struct _EXCEPTIONREGISTRATIONRECORD *pRegistration,
    PCONTEXTRECORD pContext, PVOID pWhatever);

typedef struct _EXCEPTIONREGISTRATIONRECORD
    {
    struct _EXCEPTIONREGISTRATIONRECORD * volatile prev_structure;
    ERR volatile ExceptionHandler;
    } EXCEPTIONREGISTRATIONRECORD;
typedef EXCEPTIONREGISTRATIONRECORD *PEXCEPTIONREGISTRATIONRECORD;

#define END_OF_CHAIN            ((PEXCEPTIONREGISTRATIONRECORD)(-1))

ULONG DosAcknowledgeSignalException (ULONG ulSignal);
ULONG DosEnterMustComplete (PULONG pulNesting);
ULONG DosExitMustComplete (PULONG pulNesting);
ULONG DosRaiseException (PEXCEPTIONREPORTRECORD pXRepRec);
ULONG DosSendSignalException (PID pid, ULONG ulSignal);
ULONG DosSetExceptionHandler (PEXCEPTIONREGISTRATIONRECORD pXRegRec);
ULONG DosSetSignalExceptionFocus (BOOL32 flag, PULONG pulTimes);
ULONG DosUnsetExceptionHandler (PEXCEPTIONREGISTRATIONRECORD pXRegRec);
ULONG DosUnwindException (PEXCEPTIONREGISTRATIONRECORD pXRegRec,
    PVOID pJumpThere, PEXCEPTIONREPORTRECORD pXRepRec);

/* --------------------------- INFORMATION -------------------------------- */

#define QSV_MAX_PATH_LENGTH     1
#define QSV_MAX_TEXT_SESSIONS   2
#define QSV_MAX_PM_SESSIONS     3
#define QSV_MAX_VDM_SESSIONS    4
#define QSV_BOOT_DRIVE          5
#define QSV_DYN_PRI_VARIATION   6
#define QSV_MAX_WAIT            7
#define QSV_MIN_SLICE           8
#define QSV_MAX_SLICE           9
#define QSV_PAGE_SIZE           10
#define QSV_VERSION_MAJOR       11
#define QSV_VERSION_MINOR       12
#define QSV_VERSION_REVISION    13
#define QSV_MS_COUNT            14
#define QSV_TIME_LOW            15
#define QSV_TIME_HIGH           16
#define QSV_TOTPHYSMEM          17
#define QSV_TOTRESMEM           18
#define QSV_TOTAVAILMEM         19
#define QSV_MAXPRMEM            20
#define QSV_MAXSHMEM            21
#define QSV_TIMER_INTERVAL      22
#define QSV_MAX_COMP_LENGTH     23
#define QSV_MAX                 QSV_MAX_COMP_LENGTH

ULONG DosQuerySysInfo (ULONG ulStart, ULONG ulLast, PVOID pBuf,
    ULONG ulBufLength);

/* --------------------------- DEBUGGING ---------------------------------- */

#define DBG_C_Null              0
#define DBG_C_ReadMem           1
#define DBG_C_ReadMem_I         1
#define DBG_C_ReadMem_D         2
#define DBG_C_ReadReg           3
#define DBG_C_WriteMem          4
#define DBG_C_WriteMem_I        4
#define DBG_C_WriteMem_D        5
#define DBG_C_WriteReg          6
#define DBG_C_Go                7
#define DBG_C_Term              8
#define DBG_C_SStep             9
#define DBG_C_Stop              10
#define DBG_C_Freeze            11
#define DBG_C_Resume            12
#define DBG_C_NumToAddr         13
#define DBG_C_ReadCoRegs        14
#define DBG_C_WriteCoRegs       15
#define DBG_C_ThrdStat          17
#define DBG_C_MapROAlias        18
#define DBG_C_MapRWAlias        19
#define DBG_C_UnMapAlias        20
#define DBG_C_Connect           21
#define DBG_C_ReadMemBuf        22
#define DBG_C_WriteMemBuf       23
#define DBG_C_SetWatch          24
#define DBG_C_ClearWatch        25
#define DBG_C_RangeStep         26
#define DBG_C_Continue          27
#define DBG_C_AddrToObject      28
#define DBG_C_XchngOpcode       29
#define DBG_C_LinToSel          30
#define DBG_C_SelToLin          31

#define DBG_N_SUCCESS           0
#define DBG_N_ERROR             (-1)
#define DBG_N_ProcTerm          (-6)
#define DBG_N_Exception         (-7)
#define DBG_N_ModuleLoad        (-8)
#define DBG_N_CoError           (-9)
#define DBG_N_ThreadTerm        (-10)
#define DBG_N_AsyncStop         (-11)
#define DBG_N_NewProc           (-12)
#define DBG_N_AliasFree         (-13)
#define DBG_N_Watchpoint        (-14)
#define DBG_N_ThreadCreate      (-15)
#define DBG_N_ModuleFree        (-16)
#define DBG_N_RangeStep         (-17)

#define DBG_D_Thawed            0
#define DBG_D_Frozen            1

#define DBG_T_Runnable          0
#define DBG_T_Suspended         1
#define DBG_T_Blocked           2
#define DBG_T_CritSec           3

#define DBG_L_386               1

#define DBG_CO_387              1

#define DBG_O_OBJMTE            0x10000000

#define DBG_W_Global            0x00000001
#define DBG_W_Local             0x00000002
#define DBG_W_Execute           0x00010000
#define DBG_W_Write             0x00020000
#define DBG_W_ReadWrite         0x00040000

typedef struct
    {
    ULONG ulPid;
    ULONG ulTid;
    LONG lCmd;
    LONG lValue;
    ULONG ulAddr;
    ULONG ulBuffer;
    ULONG ulLen;
    ULONG ulIndex;
    ULONG ulMTE;
    ULONG ulEAX;
    ULONG ulECX;
    ULONG ulEDX;
    ULONG ulEBX;
    ULONG ulESP;
    ULONG ulEBP;
    ULONG ulESI;
    ULONG ulEDI;
    ULONG ulEFlags;
    ULONG ulEIP;
    ULONG ulCSLim;
    ULONG ulCSBase;
    UCHAR ucCSAcc;
    UCHAR ucCSAtr;
    USHORT usCS;
    ULONG ulDSLim;
    ULONG ulDSBase;
    UCHAR ucDSAcc;
    UCHAR ucDSAtr;
    USHORT usDS;
    ULONG ulESLim;
    ULONG ulESBase;
    UCHAR ucESAcc;
    UCHAR ucESAtr;
    USHORT usES;
    ULONG ulFSLim;
    ULONG ulFSBase;
    UCHAR ucFSAcc;
    UCHAR ucFSAtr;
    USHORT usFS;
    ULONG ulGSLim;
    ULONG ulGSBase;
    UCHAR ucGSAcc;
    UCHAR ucGSAtr;
    USHORT usGS;
    ULONG ulSSLim;
    ULONG ulSSBase;
    UCHAR ucSSAcc;
    UCHAR ucSSAtr;
    USHORT usSS;
    } DEBUGBUFFER;
typedef DEBUGBUFFER *PDEBUGBUFFER;

ULONG DosDebug (PDEBUGBUFFER pDebugBuffer);

/* ----------------------- PRESENTATION MANAGER --------------------------- */

#define WM_NULL                 0x0000
#define WM_CREATE               0x0001
#define WM_DESTROY              0x0002
#define WM_ENABLE               0x0004
#define WM_SHOW                 0x0005
#define WM_MOVE                 0x0006
#define WM_SIZE                 0x0007
#define WM_ADJUSTWINDOWPOS      0x0008
#define WM_CALCVALIDRECTS       0x0009
#define WM_SETWINDOWPARAMS      0x000a
#define WM_QUERYWINDOWPARAMS    0x000b
#define WM_HITTEST              0x000c
#define WM_ACTIVATE             0x000d
#define WM_SETFOCUS             0x000f
#define WM_SETSELECTION         0x0010
#define WM_PPAINT               0x0011
#define WM_PSETFOCUS            0x0012
#define WM_PSYSCOLORCHANGE      0x0013
#define WM_PSIZE                0x0014
#define WM_PACTIVATE            0x0015
#define WM_PCONTROL             0x0016
#define WM_COMMAND              0x0020
#define WM_SYSCOMMAND           0x0021
#define WM_HELP                 0x0022
#define WM_PAINT                0x0023
#define WM_TIMER                0x0024
#define WM_SEM1                 0x0025
#define WM_SEM2                 0x0026
#define WM_SEM3                 0x0027
#define WM_SEM4                 0x0028
#define WM_CLOSE                0x0029
#define WM_QUIT                 0x002a
#define WM_SYSCOLORCHANGE       0x002b
#define WM_SYSVALUECHANGED      0x002d
#define WM_APPTERMINATENOTIFY   0x002e
#define WM_PRESPARAMCHANGED     0x002f
#define WM_CONTROL              0x0030
#define WM_VSCROLL              0x0031
#define WM_HSCROLL              0x0032
#define WM_INITMENU             0x0033
#define WM_MENUSELECT           0x0034
#define WM_MENUEND              0x0035
#define WM_DRAWITEM             0x0036
#define WM_MEASUREITEM          0x0037
#define WM_CONTROLPOINTER       0x0038
#define WM_QUERYDLGCODE         0x003a
#define WM_INITDLG              0x003b
#define WM_SUBSTITUTESTRING     0x003c
#define WM_MATCHMNEMONIC        0x003d
#define WM_SAVEAPPLICATION      0x003e

#define WM_MOUSEFIRST           0x0070
#define WM_MOUSEMOVE            0x0070
#define WM_BUTTONCLICKFIRST     0x0071
#define WM_BUTTON1DOWN          0x0071
#define WM_BUTTON1UP            0x0072
#define WM_BUTTON1DBLCLK        0x0073
#define WM_BUTTON2DOWN          0x0074
#define WM_BUTTON2UP            0x0075
#define WM_BUTTON2DBLCLK        0x0076
#define WM_BUTTON3DOWN          0x0077
#define WM_BUTTON3UP            0x0078
#define WM_BUTTON3DBLCLK        0x0079
#define WM_BUTTONCLICKLAST      0x0079
#define WM_MOUSELAST            0x0079

#define WM_CHAR                 0x007a
#define WM_VIOCHAR              0x007b

#define WM_USER                 0x1000

#define CS_SIZEREDRAW           0x00000004L

#define WS_VISIBLE              0x80000000L

#define FCF_TITLEBAR            0x00000001L
#define FCF_SYSMENU             0x00000002L
#define FCF_MENU                0x00000004L
#define FCF_SIZEBORDER          0x00000008L
#define FCF_MINBUTTON           0x00000010L
#define FCF_MAXBUTTON           0x00000020L
#define FCF_MINMAX              (FCF_MINBUTTON|FCF_MAXBUTTON)
#define FCF_VERTSCROLL          0x00000040L
#define FCF_HORZSCROLL          0x00000080L
#define FCF_DLGBORDER           0x00000100L
#define FCF_BORDER              0x00000200L
#define FCF_SHELLPOSITION       0x00000400L
#define FCF_TASKLIST            0x00000800L
#define FCF_NOBYTEALIGN         0x00001000L
#define FCF_NOMOVEWITHOWNER     0x00002000L
#define FCF_ICON                0x00004000L
#define FCF_ACCELTABLE          0x00008000L
#define FCF_SYSMODAL            0x00010000L
#define FCF_SCREENALIGN         0x00020000L
#define FCF_MOUSEALIGN          0x00040000L
#define FCF_PALETTE_NORMAL      0x00080000L
#define FCF_PALETTE_HELP        0x00100000L
#define FCF_PALETTE_POPUPODD    0x00200000L
#define FCF_PALETTE_POPUPEVEN   0x00400000L

#define FCF_STANDARD (FCF_TITLEBAR | FCF_SYSMENU | FCF_MENU | FCF_SIZEBORDER \
  | FCF_MINMAX | FCF_SHELLPOSITION | FCF_TASKLIST | FCF_ICON \
  | FCF_ACCELTABLE | FCF_PALETTE_NORMAL)

#define FID_SYSMENU             0x8002
#define FID_TITLEBAR            0x8003
#define FID_MINMAX              0x8004
#define FID_MENU                0x8005
#define FID_VERTSCROLL          0x8006
#define FID_HORZSCROLL          0x8007
#define FID_CLIENT              0x8008

#define DT_LEFT                 0x0000
#define DT_QUERYEXTENT          0x0002
#define DT_UNDERSCORE           0x0010
#define DT_STRIKEOUT            0x0020
#define DT_TEXTATTRS            0x0040
#define DT_EXTERNALLEADING      0x0080
#define DT_CENTER               0x0100
#define DT_RIGHT                0x0200
#define DT_TOP                  0x0000
#define DT_VCENTER              0x0400
#define DT_BOTTOM               0x0800
#define DT_HALFTONE             0x1000
#define DT_MNEMONIC             0x2000
#define DT_WORDBREAK            0x4000
#define DT_ERASERECT            0x8000

#define QW_NEXT                 0
#define QW_PREV                 1
#define QW_TOP                  2
#define QW_BOTTOM               3
#define QW_OWNER                4
#define QW_PARENT               5
#define QW_NEXTTOP              6
#define QW_PREVTOP              7
#define QW_FRAMEOWNER           8

#define SWP_SIZE                0x0001
#define SWP_MOVE                0x0002
#define SWP_ZORDER              0x0004
#define SWP_SHOW                0x0008
#define SWP_HIDE                0x0010
#define SWP_NOREDRAW            0x0020
#define SWP_NOADJUST            0x0040
#define SWP_ACTIVATE            0x0080
#define SWP_DEACTIVATE          0x0100
#define SWP_EXTSTATECHANGE      0x0200
#define SWP_MINIMIZE            0x0400
#define SWP_MAXIMIZE            0x0800
#define SWP_RESTORE             0x1000
#define SWP_FOCUSACTIVATE       0x2000
#define SWP_FOCUSDEACTIVATE     0x4000

#define CMDSRC_PUSHBUTTON       1
#define CMDSRC_MENU             2
#define CMDSRC_ACCELERATOR      3
#define CMDSRC_FONTDLG          4
#define CMDSRC_FILEDLG          5
#define CMDSRC_PRINTDLG         6
#define CMDSRC_COLORDLG         7
#define CMDSRC_OTHER            0

#define KC_NONE                 0x0000
#define KC_CHAR                 0x0001
#define KC_VIRTUALKEY           0x0002
#define KC_SCANCODE             0x0004
#define KC_SHIFT                0x0008
#define KC_CTRL                 0x0010
#define KC_ALT                  0x0020
#define KC_KEYUP                0x0040
#define KC_PREVDOWN             0x0080
#define KC_LONEKEY              0x0100
#define KC_DEADKEY              0x0200
#define KC_COMPOSITE            0x0400
#define KC_INVALIDCOMP          0x0800
#define KC_TOGGLE               0x1000
#define KC_INVALIDCHAR          0x2000

#define VK_BUTTON1              0x0001
#define VK_BUTTON2              0x0002
#define VK_BUTTON3              0x0003
#define VK_BREAK                0x0004
#define VK_BACKSPACE            0x0005
#define VK_TAB                  0x0006
#define VK_BACKTAB              0x0007
#define VK_NEWLINE              0x0008
#define VK_SHIFT                0x0009
#define VK_CTRL                 0x000a
#define VK_ALT                  0x000b
#define VK_ALTGRAF              0x000c
#define VK_PAUSE                0x000d
#define VK_CAPSLOCK             0x000e
#define VK_ESC                  0x000f
#define VK_SPACE                0x0010
#define VK_PAGEUP               0x0011
#define VK_PAGEDOWN             0x0012
#define VK_END                  0x0013
#define VK_HOME                 0x0014
#define VK_LEFT                 0x0015
#define VK_UP                   0x0016
#define VK_RIGHT                0x0017
#define VK_DOWN                 0x0018
#define VK_PRINTSCRN            0x0019
#define VK_INSERT               0x001a
#define VK_DELETE               0x001b
#define VK_SCRLLOCK             0x001c
#define VK_NUMLOCK              0x001d
#define VK_ENTER                0x001e
#define VK_SYSRQ                0x001f
#define VK_F1                   0x0020
#define VK_F2                   0x0021
#define VK_F3                   0x0022
#define VK_F4                   0x0023
#define VK_F5                   0x0024
#define VK_F6                   0x0025
#define VK_F7                   0x0026
#define VK_F8                   0x0027
#define VK_F9                   0x0028
#define VK_F10                  0x0029
#define VK_F11                  0x002a
#define VK_F12                  0x002b
#define VK_F13                  0x002c
#define VK_F14                  0x002d
#define VK_F15                  0x002e
#define VK_F16                  0x002f
#define VK_F17                  0x0030
#define VK_F18                  0x0031
#define VK_F19                  0x0032
#define VK_F20                  0x0033
#define VK_F21                  0x0034
#define VK_F22                  0x0035
#define VK_F23                  0x0036
#define VK_F24                  0x0037

#define VK_MENU                 VK_F10

#define VK_USERFIRST            0x0100
#define VK_USERLAST             0x01ff

#define HWND_DESKTOP            ((HWND)1)
#define HWND_OBJECT             ((HWND)2)
#define HWND_TOP                ((HWND)3)
#define HWND_BOTTOM             ((HWND)4)
#define HWND_THREADCAPTURE      ((HWND)5)

#define GPI_ERROR               0L
#define GPI_OK                  1L

#define HDC_ERROR               ((HDC)(-1L))

#define CLR_ERROR               (-255L)
#define CLR_NOINDEX             (-254L)
#define CLR_FALSE               (-5L)
#define CLR_TRUE                (-4L)
#define CLR_DEFAULT             (-3L)
#define CLR_WHITE               (-2L)
#define CLR_BLACK               (-1L)
#define CLR_BACKGROUND          0L
#define CLR_BLUE                1L
#define CLR_RED                 2L
#define CLR_PINK                3L
#define CLR_GREEN               4L
#define CLR_CYAN                5L
#define CLR_YELLOW              6L
#define CLR_NEUTRAL             7L
#define CLR_DARKGRAY            8L
#define CLR_DARKBLUE            9L
#define CLR_DARKRED             10L
#define CLR_DARKPINK            11L
#define CLR_DARKGREEN           12L
#define CLR_DARKCYAN            13L
#define CLR_BROWN               14L
#define CLR_PALEGRAY            15L

#define RGB_ERROR               (-255L)
#define RGB_BLACK               0x00000000L
#define RGB_BLUE                0x000000ffL
#define RGB_GREEN               0x0000ff00L
#define RGB_CYAN                0x0000ffffL
#define RGB_RED                 0x00ff0000L
#define RGB_PINK                0x00ff00ffL
#define RGB_YELLOW              0x00ffff00L
#define RGB_WHITE               0x00ffffffL

#define GPIA_NOASSOC            0x0000L
#define GPIA_ASSOC              0x4000L

#define GPIF_DEFAULT            0x0000L
#define GPIF_SHORT              0x0100L
#define GPIF_LONG               0x0200L

#define GPIT_NORMAL             0x0000L
#define GPIT_MICRO              0x1000L

#define GRES_ATTRS              0x0001L
#define GRES_SEGMENTS           0x0002L
#define GRES_ALL                0x0004L

#define PS_UNITS                0x00fcL
#define PS_FORMAT               0x0f00L
#define PS_TYPE                 0x1000L
#define PS_MODE                 0x2000L
#define PS_ASSOCIATE            0x4000L
#define PS_NORESET              0x8000L

#define PU_ARBITRARY            0x0004L
#define PU_PELS                 0x0008L
#define PU_LOMETRIC             0x000cL
#define PU_HIMETRIC             0x0010L
#define PU_LOENGLISH            0x0014L
#define PU_HIENGLISH            0x0018L
#define PU_TWIPS                0x001cL

typedef LHANDLE HAB;
typedef HAB *PHAB;

typedef LHANDLE HPS;
typedef HPS *PHPS;

typedef LHANDLE HDC;
typedef HDC *PHDC;

typedef LHANDLE HWND;
typedef HWND *PHWND;

typedef LHANDLE HMQ;

typedef VOID *MRESULT;
typedef VOID *MPARAM;

typedef MRESULT FNWP (HWND hwnd, ULONG msg, MPARAM mp1, MPARAM mp2);
typedef FNWP *PFNWP;

typedef struct
    {
    LONG x;
    LONG y;
    } POINTL;
typedef POINTL *PPOINTL;

typedef struct
    {
    LONG cx;
    LONG cy;
    } SIZEL;
typedef SIZEL *PSIZEL;

typedef struct
    {
    LONG xLeft;
    LONG yBottom;
    LONG xRight;
    LONG yTop;
    } RECTL;
typedef RECTL *PRECTL;

typedef struct
    {
    HWND hwnd;
    USHORT msg;
    MPARAM mp1;
    MPARAM mp2;
    ULONG time;
    POINTL ptl;
    } QMSG;
typedef QMSG *PQMSG;

typedef struct
    {
    ULONG fl;
    SHORT cy;
    SHORT cx;
    SHORT y;
    SHORT x;
    HWND hwndInsertBehind;
    HWND hwnd;
    ULONG ulReserved1;
    ULONG ulReserved2;
    } SWP;
typedef SWP *PSWP;

#define PVOIDFROMMP(mp)         ((PVOID)(mp))
#define HWNDFROMMP(mp)          ((HWND)(mp))
#define CHAR1FROMMP(mp)         ((UCHAR)(mp))
#define CHAR2FROMMP(mp)         ((UCHAR)((ULONG)mp >> 8))
#define CHAR3FROMMP(mp)         ((UCHAR)((ULONG)mp >> 16))
#define CHAR4FROMMP(mp)         ((UCHAR)((ULONG)mp >> 24))
#define SHORT1FROMMP(mp)        ((USHORT)(ULONG)(mp))
#define SHORT2FROMMP(mp)        ((USHORT)((ULONG)mp >> 16))
#define LONGFROMMP(mp)          ((ULONG)(mp))

HPS WinBeginPaint (HWND hwnd, HPS hps, PRECTL prclPaint);
HMQ WinCreateMsgQueue (HAB hab, SHORT cmsg);
HWND WinCreateStdWindow (HWND hwndParent, ULONG flStyle,
    PULONG pflCreateFlags, CONSTPSZ pszClientClass, CONSTPSZ pszTitle,
    ULONG styleClient, HMODULE hmod, USHORT idResources, PHWND phwndClient);
HWND WinCreateWindow (HWND hwndParent, CONSTPSZ pszClass, CONSTPSZ pszName,
    ULONG flStyle, SHORT x, SHORT y, SHORT cx, SHORT cy, HWND hwndOwner,
    HWND hwndInsertBehind, USHORT id, PVOID pCtlData, PVOID pPresParams);
MRESULT WinDefWindowProc (HWND hwnd, USHORT msg, MPARAM mp1, MPARAM mp2);
BOOL WinDestroyMsgQueue (HMQ hmq);
BOOL WinDestroyWindow (HWND hwnd);
MRESULT WinDispatchMsg (HAB hab, PQMSG pqmsg);
SHORT WinDrawText (HPS hps, SHORT cchText, PCH lpchText, PRECTL prcl,
    LONG clrFore, LONG clrBack, ULONG flCmd);
BOOL WinEnableWindow (HWND hwnd, BOOL fEnable);
BOOL WinEndPaint (HPS hps);
BOOL WinFillRect (HPS hps, PRECTL prcl, LONG lColor);
BOOL WinGetMsg (HAB hab, PQMSG pqmsg, HWND hwndFilter, USHORT msgFilterFirst,
    USHORT msgFilterLast);
HPS WinGetPS (HWND hwnd);
HPS WinGetScreenPS (HWND hwndDesktop);
HAB WinInitialize (USHORT fsOptions);
BOOL WinInvalidateRect (HWND hwnd, PRECTL pwrc, USHORT vrf);
BOOL WinIsWindowEnabled (HWND hwnd);
BOOL WinIsWindowVisible (HWND hwnd);
SHORT WinLoadMessage (HAB hab, HMODULE hmod, USHORT id, SHORT cchMax,
    PSZ pchBuffer);
SHORT WinLoadString (HAB hab, HMODULE hmod, USHORT id, SHORT cchMax,
    PSZ pchBuffer);
HDC WinOpenWindowDC (HWND hwnd);
BOOL WinPostMsg (HWND hwnd, USHORT msg, MPARAM mp1, MPARAM mp2);
BOOL WinRegisterClass (HAB hab, CONSTPSZ pszClassName, PFNWP pfnWndProc,
    ULONG flStyle, USHORT cbWindowData);
BOOL WinReleasePS (HPS hps);
HWND WinQueryActiveWindow (HWND hwndDesktop);
HWND WinQueryDesktopWindow (HAB hab, HDC hdc);
HWND WinQueryWindow (HWND hwnd, SHORT cmd);
HDC WinQueryWindowDC (HWND hwnd);
BOOL WinQueryWindowPos (HWND hwnd, PSWP pswp);
BOOL WinQueryWindowRect (HWND hwnd, PRECTL prclDest);
MRESULT WinSendMsg (HWND hwnd, USHORT msg, MPARAM mp1, MPARAM mp2);
BOOL WinSetActiveWindow (HWND hwndDesktop, HWND hwnd);
BOOL WinSetWindowPos (HWND hwnd, HWND hwndInsertBehind, SHORT x, SHORT y,
    SHORT cx, SHORT cy, ULONG fl);
BOOL WinSetWindowText (HWND hwnd, CONSTPSZ pszText);
BOOL WinShowWindow (HWND hwnd, BOOL fShow);
PFNWP WinSubclassWindow (HWND hwnd, PFNWP pfnwp);
BOOL WinTerminate (HAB hab);
HWND WinWindowFromDC (HDC hdc);
HWND WinWindowFromID (HWND hwndParent, USHORT id);

BOOL GpiAssociate (HPS hps, HDC hdc);
LONG GpiBox (HPS hps, LONG lControl, PPOINTL pptlPoint, LONG lHRound,
    LONG lVRound);
HPS GpiCreatePS (HAB hab, HDC hdc, PSIZEL psizlSize, ULONG flOptions);
BOOL GpiDestroyPS (HPS hps);
BOOL GpiErase (HPS hps);
LONG GpiLine (HPS hps, PPOINTL pptlEndPoint);
BOOL GpiMove (HPS hps, PPOINTL pptlPoint);
LONG GpiPolyLine (HPS hps, LONG lCount, PPOINTL aptlPoints);
LONG GpiQueryColor (HPS hps);
ULONG GpiQueryPS (HPS hps, PSIZEL psizlSize);
BOOL GpiResetPS (HPS hps, ULONG flOptions);
BOOL GpiRestorePS (HPS hps, LONG lPSid);
LONG GpiSavePS (HPS hps);
BOOL GpiSetColor (HPS hps, LONG lColor);
BOOL GpiSetPS (HPS hps, PSIZEL psizlsize, ULONG flOptions);

#pragma pack(4)

#endif /* !defined (_OS2_H) */
