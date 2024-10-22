.global __ARMV7_ACTLR
__ARMV7_ACTLR = 0xE000E008

.global __ARMV7_SYST_CSR
__ARMV7_SYST_CSR = 0xE000E010
.global __ARMV7_SYST_RVR
__ARMV7_SYST_RVR = 0xE000E014
.global __ARMV7_SYST_CVR
__ARMV7_SYST_CVR = 0xE000E018
.global __ARMV7_SYST_CALIB
__ARMV7_SYST_CALIB = 0xE000E01C

.global __ARMV7_CPUID
__ARMV7_CPUID = 0xE000ED00

.global __ARMV7_ICSR
__ARMV7_ICSR = 0xE000ED04
.global __ARMV7_VTOR
__ARMV7_VTOR = 0xE000ED08

.global __ARMV7_AIRCR
__ARMV7_AIRCR = 0xE000ED0C

.global __ARMV7_SCR
__ARMV7_SCR = 0xE000ED10

.global __ARMV7_CCR
__ARMV7_CCR = 0xE000ED14

.global __ARMV7_SHPR1
__ARMV7_SHPR1 = 0xE000ED18
.global __ARMV7_SHPR2
__ARMV7_SHPR2 = 0xE000ED1C
.global __ARMV7_SHPR3
__ARMV7_SHPR3 = 0xE000ED20
.global __ARMV7_SHCSR
__ARMV7_SHCSR = 0xE000ED24

.global __ARMV7_CFSR
__ARMV7_CFSR = 0xE000ED28
.global __ARMV7_HFSR
__ARMV7_HFSR = 0xE000ED2C
.global __ARMV7_DFSR
__ARMV7_DFSR = 0xE000ED30
.global __ARMV7_MMFAR
__ARMV7_MMFAR = 0xE000ED34
.global __ARMV7_BFAR
__ARMV7_BFAR = 0xE000ED38

.global __ARMV7_ID_PFR0
__ARMV7_ID_PFR0 = 0xE000ED40
.global __ARMV7_ID_PFR1
__ARMV7_ID_PFR1 = 0xE000ED44

.global __ARMV7_ID_DFR0
__ARMV7_ID_DFR0 = 0xE000ED48

.global __ARMV7_ID_AFR0
__ARMV7_ID_AFR0 = 0xE000ED4C

.global __ARMV7_ID_MMFR0
__ARMV7_ID_MMFR0 = 0xE000ED50
.global __ARMV7_ID_MMFR1
__ARMV7_ID_MMFR1 = 0xE000ED54
.global __ARMV7_ID_MMFR2
__ARMV7_ID_MMFR2 = 0xE000ED58
.global __ARMV7_ID_MMFR3
__ARMV7_ID_MMFR3 = 0xE000ED5C

.global __ARMV7_ID_ISAR0
__ARMV7_ID_ISAR0 = 0xE000ED60
.global __ARMV7_ID_ISAR1
__ARMV7_ID_ISAR1 = 0xE000ED64
.global __ARMV7_ID_ISAR2
__ARMV7_ID_ISAR2 = 0xE000ED68
.global __ARMV7_ID_ISAR3
__ARMV7_ID_ISAR3 = 0xE000ED6C
.global __ARMV7_ID_ISAR4
__ARMV7_ID_ISAR4 = 0xE000ED70

.global __ARMV7_CLIDR
__ARMV7_CLIDR = 0xE000ED78
.global __ARMV7_CTR
__ARMV7_CTR = 0xE000ED7C
.global __ARMV7_CCSIDR
__ARMV7_CCSIDR = 0xE000ED80
.global __ARMV7_CSSELR
__ARMV7_CSSELR = 0xE000ED84

.global __ARMV7_DHCSR
__ARMV7_DHCSR = 0xE000EDF0
.global __ARMV7_DCRSR
__ARMV7_DCRSR = 0xE000EDF4
.global __ARMV7_DCRDR
__ARMV7_DCRDR = 0xE000EDF8
.global __ARMV7_DEMCR
__ARMV7_DEMCR = 0xE000EDFC

.global __ARMV7_CPACR
__ARMV7_CPACR = 0xE000ED88

.global __ARMV7_STIR
__ARMV7_STIR = 0xE000EF00

.global __ARMV7_ICIALLU
__ARMV7_ICIALLU = 0xE000EF50
.global __ARMV7_ICIMVAU
__ARMV7_ICIMVAU = 0xE000EF58

.global __ARMV7_DCIMVAC
__ARMV7_DCIMVAC = 0xE000EF5C
.global __ARMV7_DCISW
__ARMV7_DCISW = 0xE000EF60
.global __ARMV7_DCCMVAU
__ARMV7_DCCMVAU = 0xE000EF64
.global __ARMV7_DCCMVAC
__ARMV7_DCCMVAC = 0xE000EF68
.global __ARMV7_DCCSW
__ARMV7_DCCSW = 0xE000EF6C
.global __ARMV7_DCCIMVAC
__ARMV7_DCCIMVAC = 0xE000EF70
.global __ARMV7_DCCISW
__ARMV7_DCCISW = 0xE000EF74

.global __ARMV7_BPIALL
__ARMV7_BPIALL = 0xE000EF78

.global __ARMV7_ITCMCR
__ARMV7_ITCMCR = 0xE000EF90
.global __ARMV7_DTCMCR
__ARMV7_DTCMCR = 0xE000EF94
.global __ARMV7_AHBPCR
__ARMV7_AHBPCR = 0xE000EF98
.global __ARMV7_CACR
__ARMV7_CACR = 0xE000EF9C
.global __ARMV7_AHBSCR
__ARMV7_AHBSCR = 0xE000EFA0
.global __ARMV7_ABFSR
__ARMV7_ABFSR = 0xE000EFA8

.global __ARMV7_IEBR0
__ARMV7_IEBR0 = 0xE000EFB0
.global __ARMV7_IEBR1
__ARMV7_IEBR1 = 0xE000EFB4

.global __ARMV7_DEBR0
__ARMV7_DEBR0 = 0xE000EFB8
.global __ARMV7_DEBR1
__ARMV7_DEBR1 = 0xE000EFBC

.global __ARMV7_PID4
__ARMV7_PID4 = 0xE000EFD0
.global __ARMV7_PID5
__ARMV7_PID5 = 0xE000EFD4
.global __ARMV7_PID6
__ARMV7_PID6 = 0xE000EFD8
.global __ARMV7_PID7
__ARMV7_PID7 = 0xE000EFDC
.global __ARMV7_PID0
__ARMV7_PID0 = 0xE000EFE0
.global __ARMV7_PID1
__ARMV7_PID1 = 0xE000EFE4
.global __ARMV7_PID2
__ARMV7_PID2 = 0xE000EFE8
.global __ARMV7_PID3
__ARMV7_PID3 = 0xE000EFEC

.global __ARMV7_CID0
__ARMV7_CID0 = 0xE000EFF0
.global __ARMV7_CID1
__ARMV7_CID1 = 0xE000EFF4
.global __ARMV7_CID2
__ARMV7_CID2 = 0xE000EFF8
.global __ARMV7_CID3
__ARMV7_CID3 = 0xE000EFFC
