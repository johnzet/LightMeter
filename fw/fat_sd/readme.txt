******************************************************************************
  Demo for ChaN's FAT-module on AT91SAM7
  Version Timestamp 20090529
  by Martin Thomas, Kaiserslautern, Germany <mthomas(at)rhrk.uni-kl.de>
******************************************************************************

/* Copyright (c) 2009
   - ChaN (FAT-Code, test-terminal)
   - Atmel (AT91LIB)
   - Martin Thomas (diskio-interface, glue-functions, misc-terminal)
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.
   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */
******************************************************************************

Changelog:
15. Sept. 2009
- updated Chan's FatFS to 0.07c with patches up to 27. July 2009
- moved some files into the Library subdirectory
- updated makefile based on my latests "WinARM template"
- added addtional terminal with a few test-functions, 'x' switches
  between terminals
- tested with Codesourcery G++ lite 2009q1-161
- tested with Amontec JTAGkey2. Thanks to Amontec for donating
  the interface.
- removed special gdb from package, the gdb from CS G++ 2009q1
  seems to work as expected
- added UART1 driver with RX-fifo-buffer and demo in misc-term
- linker-script for "RAM_RUN". Executing from interal RAM for
  debugging is "supported" now.
- Eclipse/External Tools: two OpenOCD launches, one is for flash-
  programming and debugging in flash, the other one for debugging 
  in RAM which should be used with the OpenOCD reset load debug SRAM 
  debug-launch.
- board_cstartup.S: modified exeptions-table to use absolute
  addressing for easier debugging in RAM
- minor modification in board_memories.c/BOARD_GetRemap, marked
  with MOD_MTHOMAS_AT91LIB, made BOARD_GetRemap non-static, test
  in main.c
- SD-SPI interface: modified xmit_datablock_dma, additional "safe"
  routine available and can be selected by a define. Both routines 
  worked in my tests.
- Test for DCC based on code from the OpenOCD SVN. Note the license
  if you'd like to use dcc_stdio.c in own (commercial) developments.



This is a small demo-application to show how Chan's Fat-Module
can be used to interface MMC/SD/SDHC-Cards with a AT91SAM microcontroller
(ARM Ltd. ARM7TDMI). It also demonstrates various basic development
tasks like using the AT91-library, FLASH-programming, JTAG debugging 
in FLASH and RAM and more using Eclipse/CDT-hardware debugging plugin/
arm-*-gdb/OpenOCD/JTAG-interface(i.e. Amontec JTAGkey2)/AT91SAM-board

Code from others used in this project:
- Chan's FAT-Module
- Atmel's at91lib
- some utility-code for time-calculations (see rtc.c)

Tested with:
- Controller: AT91SAM7S256
- Board: Olimex SAM7-Pxxx Rev C
- Cards: extrememory 1GB performace SD-Card, SanDisk 256MB SD-Card,
         SanDisk Ultra II 4GB SDHC-Card

Tools:
- Compiler/Toolchain: GNU cross-toolchain for ARM (binutils, gcc)
  with newlib as libc as in the package Codesourcery G++ lite for 
  ARM EABI (I have used the CS package. Tools from Yagarto, DevkitARM,
  WinARM may work too but have not been tested)
- IDEs/Editors: 
  - Programmers Notepad
  - Eclipse Ganymede SR1 Package Eclipse IDE for C/C++ Developers
    This is not the current version in Arp. 2009 but the CDT 5.0.2
    does not offer a setting for the compiler invocation command in
    Project->Properties->C/C++ Build->Discovery Options which is
    needed to locate the inlude files of the toolchain (i.e. stdlib.h).
    Additional plug-ins: CDT Hardware Debugging, Target Managment Terminal,
    RXTX Enduser Runtime.
- OpenOCD for "batch programming" (make program) and debugging with
  gdb and Eclipse. This package comes with a OpenOCD directory including 
  a Win32 binary for FT2232 and par.-port interfaces ("feature freeze"). 
  If you are using a different version you may need to adapt the settings
  (Makefile, target-library, config-file). Since the OpenOCD package included
  may violate a license you must delete it NOW! (I have built the binary 
  myself but as far as I understand you must also build it on your own
  to use the FTDI driver from the chip-vendor. The full OpenOCD source is
  available from berlios SVN, see OpenOCD/doc/*)

******************************************************************************

Test Session SanDisk Ultra II 4GB SDHC


AT91SAM7S Demo Application by Martin Thomas
V1.1.8 9/2009
-- Compiled: Sep 14 2009 18:35:47
-- for Board SAM7-Pxxx
-- not re-mapped, re-mapping... o.k.

FatFs module test terminal
>di 0
rc=0
>ds
Power is ON
Drive size: 7744512 sectors
Sector size: 512
Erase block size: 8192 sectors
MMC/SDC type: 12
CSD:
00000000  40 0E 00 32 5B 59 00 00 1D 8A 7F 80 0A 40 40 B9 @..2[Y.......@@.
CID:
00000000  03 53 44 53 44 30 34 47 80 70 8C 95 06 00 93 C5 .SDSD04G.p......
OCR:
00000000  C0 FF 80 00 ....
SD Status:
00000000  00 00 00 00 02 00 00 00 02 02 90 00 0D 05 00 00 ................
00000010  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ................
00000020  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ................
00000030  00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 ................
>fi 0
rc=0 FR_OK
>fs
FAT type = 3 (FAT32)
Bytes/Cluster = 32768
Number of FATs = 1
Root DIR entries = 0
Sectors/FAT = 8096
Number of clusters = 120880
FAT start (lba) = 96
DIR start (lba,clustor) = 2
Data start (lba) = 8192

4 files, 12200002 bytes.
0 folders.
3868160 KB total disk space.
3856096 KB available.
>fl
----A 2000/01/01 11:55         1  1  
----A 2000/01/01 11:55         1  2  
----A 2000/01/01 11:55    200000  3  
----A 2000/01/01 11:59  12000000  4  
   4 File(s),   12200002 bytes total
   0 Dir(s),  3948642304 bytes free
>fo 10 Müll
rc=0 FR_OK
>fw 1000000 1
1000000 bytes written with 1375 kB/sec.
>fw 1000000 2
1000000 bytes written with 825 kB/sec.
>fw 1000000 3
1000000 bytes written with 806 kB/sec.
>fw 1000000 4
1000000 bytes written with 823 kB/sec.
>fc
rc=0 FR_OK
>fl
----A 2000/01/01 11:55         1  1  
----A 2000/01/01 11:55         1  2  
----A 2000/01/01 11:55    200000  3  
----A 2000/01/01 11:59  12000000  4  
----A 2000/01/01 11:56   4000000  MÜLL  Müll
   5 File(s),   16200002 bytes total
   0 Dir(s),  3944611840 bytes free
>fo 1 Müll
rc=0 FR_OK
>fr 1000000 1
1000000 bytes read with 1342 kB/sec.
>fr 1000000 2
1000000 bytes read with 1141 kB/sec.
>fd 20 
001E8480  03 03 03 03 03 03 03 03 03 03 03 03 03 03 03 03 ................
001E8490  03 03 03 03 ....
>fc
rc=0 FR_OK
>fl
----A 2000/01/01 11:55         1  1  
----A 2000/01/01 11:55         1  2  
----A 2000/01/01 11:55    200000  3  
----A 2000/01/01 11:59  12000000  4  
----A 2000/01/01 11:56   4000000  MÜLL  Müll
   5 File(s),   16200002 bytes total
   0 Dir(s),  3944611840 bytes free
>t
2000/1/1 11:57:55
>t 2009 9 14 19 0 0
2009/9/14 19:00:00
>t 
2009/9/14 19:00:04
>t
2009/9/14 19:00:06
>fo 10 5
rc=0 FR_OK
>fw 1 1
1 bytes written with 1 kB/sec.
>fc
rc=0 FR_OK
>fl
----A 2000/01/01 11:55         1  1  
----A 2000/01/01 11:55         1  2  
----A 2000/01/01 11:55    200000  3  
----A 2000/01/01 11:59  12000000  4  
----A 2000/01/01 11:56   4000000  MÜLL  Müll
----A 2009/09/14 19:00         1  5  
   6 File(s),   16200003 bytes total
   0 Dir(s),  3944579072 bytes free
>


******************************************************************************

Output from cs-make clean all program


C:\WinARM\examples\at91sam_chanfat_ws\project>cs-make clean all program
COMSPEC detected  C:\WINDOWS\system32\cmd.exe
SHELL is C:/WINDOWS/system32/cmd.exe
--------  begin, mode: FLASH_RUN  --------
Cleaning project:
cs-rm -f FLASH_RUN/at91sam_chanfat.map
cs-rm -f FLASH_RUN/at91sam_chanfat.elf
cs-rm -f FLASH_RUN/at91sam_chanfat.hex
cs-rm -f FLASH_RUN/at91sam_chanfat.bin
cs-rm -f FLASH_RUN/at91sam_chanfat.sym
cs-rm -f FLASH_RUN/at91sam_chanfat.lss
cs-rm -f FLASH_RUN/board_cstartup.o FLASH_RUN/main.o FLASH_RUN/comm.o FLASH_RUN/
term_io.o FLASH_RUN/rtc.o FLASH_RUN/ff_test_term.o FLASH_RUN/misc_test_term.o FL
ASH_RUN/uart1.o FLASH_RUN/ff.o FLASH_RUN/fattime.o FLASH_RUN/sd_spi_at91.o FLASH
_RUN/ccsbcs.o FLASH_RUN/string.o FLASH_RUN/stdio.o FLASH_RUN/led.o FLASH_RUN/dbg
u.o FLASH_RUN/pio.o FLASH_RUN/aic.o FLASH_RUN/pmc.o FLASH_RUN/spi.o FLASH_RUN/pi
t.o FLASH_RUN/usart.o FLASH_RUN/board_memories.o FLASH_RUN/board_lowlevel.o
cs-rm -f FLASH_RUN/board_cstartup.lst FLASH_RUN/main.lst FLASH_RUN/comm.lst FLAS
H_RUN/term_io.lst FLASH_RUN/rtc.lst FLASH_RUN/ff_test_term.lst FLASH_RUN/misc_te
st_term.lst FLASH_RUN/uart1.lst FLASH_RUN/ff.lst FLASH_RUN/fattime.lst FLASH_RUN
/sd_spi_at91.lst FLASH_RUN/ccsbcs.lst FLASH_RUN/string.lst FLASH_RUN/stdio.lst F
LASH_RUN/led.lst FLASH_RUN/dbgu.lst FLASH_RUN/pio.lst FLASH_RUN/aic.lst FLASH_RU
N/pmc.lst FLASH_RUN/spi.lst FLASH_RUN/pit.lst FLASH_RUN/usart.lst FLASH_RUN/boar
d_memories.lst FLASH_RUN/board_lowlevel.lst
cs-rm -f FLASH_RUN/dep/board_cstartup.o.d FLASH_RUN/dep/main.o.d FLASH_RUN/dep/c
omm.o.d FLASH_RUN/dep/term_io.o.d FLASH_RUN/dep/rtc.o.d FLASH_RUN/dep/ff_test_te
rm.o.d FLASH_RUN/dep/misc_test_term.o.d FLASH_RUN/dep/uart1.o.d FLASH_RUN/dep/ff
.o.d FLASH_RUN/dep/fattime.o.d FLASH_RUN/dep/sd_spi_at91.o.d FLASH_RUN/dep/ccsbc
s.o.d FLASH_RUN/dep/string.o.d FLASH_RUN/dep/stdio.o.d FLASH_RUN/dep/led.o.d FLA
SH_RUN/dep/dbgu.o.d FLASH_RUN/dep/pio.o.d FLASH_RUN/dep/aic.o.d FLASH_RUN/dep/pm
c.o.d FLASH_RUN/dep/spi.o.d FLASH_RUN/dep/pit.o.d FLASH_RUN/dep/usart.o.d FLASH_
RUN/dep/board_memories.o.d FLASH_RUN/dep/board_lowlevel.o.d
cs-rm -f main.s comm.s term_io.s rtc.s ff_test_term.s misc_test_term.s uart1.s .
/Libraries/fat_sd/ff.s ./Libraries/fat_sd/fattime.s ./Libraries/fat_sd/sd_spi_at
91.s ./Libraries/fat_sd/option/ccsbcs.s ./Libraries/at91lib/utility/string.s ./L
ibraries/at91lib/utility/stdio.s ./Libraries/at91lib/utility/led.s ./Libraries/a
t91lib/peripherals/dbgu/dbgu.s ./Libraries/at91lib/peripherals/pio/pio.s ./Libra
ries/at91lib/peripherals/aic/aic.s ./Libraries/at91lib/peripherals/pmc/pmc.s ./L
ibraries/at91lib/peripherals/spi/spi.s ./Libraries/at91lib/peripherals/pit/pit.s
 ./Libraries/at91lib/peripherals/usart/usart.s ./Libraries/at91lib/boards/SAM7-P
xxx_RevC/board_memories.s ./Libraries/at91lib/boards/SAM7-Pxxx_RevC/board_lowlev
el.s
cs-rm -f
cs-rm -f
cs-rm -f
--------  end  --------
arm-none-eabi-gcc (Sourcery G++ Lite 2009q1-161) 4.3.3
Copyright (C) 2008 Free Software Foundation, Inc.
This is free software; see the source for copying conditions.  There is NO
warranty; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

---- Assembling ARM-only: Libraries/at91lib/boards/SAM7-Pxxx_RevC/board_cstartup
.S to FLASH_RUN/board_cstartup.o
arm-none-eabi-gcc -c -mcpu=arm7tdmi -mthumb-interwork -I. -x assembler-with-cpp
-D__ASSEMBLY__ -DVECT_TAB_RAM -DFLASH_RUN -Dat91sam7s256 -Wa,-adhlns=FLASH_RUN/b
oard_cstartup.lst -Wa,-gdwarf-2 -I./Libraries/at91lib/boards/SAM7-Pxxx_RevC -I./
Libraries/at91lib -I./Libraries/at91lib/peripherals -I./Libraries/fat_sd Librari
es/at91lib/boards/SAM7-Pxxx_RevC/board_cstartup.S -o FLASH_RUN/board_cstartup.o

---- Compiling C : main.c to FLASH_RUN/main.o
arm-none-eabi-gcc -c -mthumb -gdwarf-2 -Os -mcpu=arm7tdmi -mthumb-interwork  -DM
OD_MTHOMAS_AT91LIB -DSTARTUP_DELAY -DVECT_TAB_RAM -DFLASH_RUN -Dat91sam7s256 -I.
/Libraries/at91lib/boards/SAM7-Pxxx_RevC -I./Libraries/at91lib -I./Libraries/at9
1lib/peripherals -I./Libraries/fat_sd -I. -ffunction-sections -fdata-sections -f
promote-loop-indices -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wred
undant-decls -Wshadow -Wcast-qual -Wcast-align -Wa,-adhlns=FLASH_RUN/main.lst -M
D -MP -MF FLASH_RUN/dep/main.o.d -Wnested-externs  -std=gnu99 main.c -o FLASH_RU
N/main.o
---- Compiling C : comm.c to FLASH_RUN/comm.o
arm-none-eabi-gcc -c -mthumb -gdwarf-2 -Os -mcpu=arm7tdmi -mthumb-interwork  -DM
OD_MTHOMAS_AT91LIB -DSTARTUP_DELAY -DVECT_TAB_RAM -DFLASH_RUN -Dat91sam7s256 -I.
/Libraries/at91lib/boards/SAM7-Pxxx_RevC -I./Libraries/at91lib -I./Libraries/at9
1lib/peripherals -I./Libraries/fat_sd -I. -ffunction-sections -fdata-sections -f
promote-loop-indices -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wred
undant-decls -Wshadow -Wcast-qual -Wcast-align -Wa,-adhlns=FLASH_RUN/comm.lst -M
D -MP -MF FLASH_RUN/dep/comm.o.d -Wnested-externs  -std=gnu99 comm.c -o FLASH_RU
N/comm.o
---- Compiling C : term_io.c to FLASH_RUN/term_io.o
arm-none-eabi-gcc -c -mthumb -gdwarf-2 -Os -mcpu=arm7tdmi -mthumb-interwork  -DM
OD_MTHOMAS_AT91LIB -DSTARTUP_DELAY -DVECT_TAB_RAM -DFLASH_RUN -Dat91sam7s256 -I.
/Libraries/at91lib/boards/SAM7-Pxxx_RevC -I./Libraries/at91lib -I./Libraries/at9
1lib/peripherals -I./Libraries/fat_sd -I. -ffunction-sections -fdata-sections -f
promote-loop-indices -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wred
undant-decls -Wshadow -Wcast-qual -Wcast-align -Wa,-adhlns=FLASH_RUN/term_io.lst
 -MD -MP -MF FLASH_RUN/dep/term_io.o.d -Wnested-externs  -std=gnu99 term_io.c -o
 FLASH_RUN/term_io.o
---- Compiling C : rtc.c to FLASH_RUN/rtc.o
arm-none-eabi-gcc -c -mthumb -gdwarf-2 -Os -mcpu=arm7tdmi -mthumb-interwork  -DM
OD_MTHOMAS_AT91LIB -DSTARTUP_DELAY -DVECT_TAB_RAM -DFLASH_RUN -Dat91sam7s256 -I.
/Libraries/at91lib/boards/SAM7-Pxxx_RevC -I./Libraries/at91lib -I./Libraries/at9
1lib/peripherals -I./Libraries/fat_sd -I. -ffunction-sections -fdata-sections -f
promote-loop-indices -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wred
undant-decls -Wshadow -Wcast-qual -Wcast-align -Wa,-adhlns=FLASH_RUN/rtc.lst -MD
 -MP -MF FLASH_RUN/dep/rtc.o.d -Wnested-externs  -std=gnu99 rtc.c -o FLASH_RUN/r
tc.o
---- Compiling C : ff_test_term.c to FLASH_RUN/ff_test_term.o
arm-none-eabi-gcc -c -mthumb -gdwarf-2 -Os -mcpu=arm7tdmi -mthumb-interwork  -DM
OD_MTHOMAS_AT91LIB -DSTARTUP_DELAY -DVECT_TAB_RAM -DFLASH_RUN -Dat91sam7s256 -I.
/Libraries/at91lib/boards/SAM7-Pxxx_RevC -I./Libraries/at91lib -I./Libraries/at9
1lib/peripherals -I./Libraries/fat_sd -I. -ffunction-sections -fdata-sections -f
promote-loop-indices -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wred
undant-decls -Wshadow -Wcast-qual -Wcast-align -Wa,-adhlns=FLASH_RUN/ff_test_ter
m.lst -MD -MP -MF FLASH_RUN/dep/ff_test_term.o.d -Wnested-externs  -std=gnu99 ff
_test_term.c -o FLASH_RUN/ff_test_term.o
---- Compiling C : misc_test_term.c to FLASH_RUN/misc_test_term.o
arm-none-eabi-gcc -c -mthumb -gdwarf-2 -Os -mcpu=arm7tdmi -mthumb-interwork  -DM
OD_MTHOMAS_AT91LIB -DSTARTUP_DELAY -DVECT_TAB_RAM -DFLASH_RUN -Dat91sam7s256 -I.
/Libraries/at91lib/boards/SAM7-Pxxx_RevC -I./Libraries/at91lib -I./Libraries/at9
1lib/peripherals -I./Libraries/fat_sd -I. -ffunction-sections -fdata-sections -f
promote-loop-indices -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wred
undant-decls -Wshadow -Wcast-qual -Wcast-align -Wa,-adhlns=FLASH_RUN/misc_test_t
erm.lst -MD -MP -MF FLASH_RUN/dep/misc_test_term.o.d -Wnested-externs  -std=gnu9
9 misc_test_term.c -o FLASH_RUN/misc_test_term.o
---- Compiling C : uart1.c to FLASH_RUN/uart1.o
arm-none-eabi-gcc -c -mthumb -gdwarf-2 -Os -mcpu=arm7tdmi -mthumb-interwork  -DM
OD_MTHOMAS_AT91LIB -DSTARTUP_DELAY -DVECT_TAB_RAM -DFLASH_RUN -Dat91sam7s256 -I.
/Libraries/at91lib/boards/SAM7-Pxxx_RevC -I./Libraries/at91lib -I./Libraries/at9
1lib/peripherals -I./Libraries/fat_sd -I. -ffunction-sections -fdata-sections -f
promote-loop-indices -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wred
undant-decls -Wshadow -Wcast-qual -Wcast-align -Wa,-adhlns=FLASH_RUN/uart1.lst -
MD -MP -MF FLASH_RUN/dep/uart1.o.d -Wnested-externs  -std=gnu99 uart1.c -o FLASH
_RUN/uart1.o
---- Compiling C : Libraries/fat_sd/ff.c to FLASH_RUN/ff.o
arm-none-eabi-gcc -c -mthumb -gdwarf-2 -Os -mcpu=arm7tdmi -mthumb-interwork  -DM
OD_MTHOMAS_AT91LIB -DSTARTUP_DELAY -DVECT_TAB_RAM -DFLASH_RUN -Dat91sam7s256 -I.
/Libraries/at91lib/boards/SAM7-Pxxx_RevC -I./Libraries/at91lib -I./Libraries/at9
1lib/peripherals -I./Libraries/fat_sd -I. -ffunction-sections -fdata-sections -f
promote-loop-indices -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wred
undant-decls -Wshadow -Wcast-qual -Wcast-align -Wa,-adhlns=FLASH_RUN/ff.lst -MD
-MP -MF FLASH_RUN/dep/ff.o.d -Wnested-externs  -std=gnu99 Libraries/fat_sd/ff.c
-o FLASH_RUN/ff.o
---- Compiling C : Libraries/fat_sd/fattime.c to FLASH_RUN/fattime.o
arm-none-eabi-gcc -c -mthumb -gdwarf-2 -Os -mcpu=arm7tdmi -mthumb-interwork  -DM
OD_MTHOMAS_AT91LIB -DSTARTUP_DELAY -DVECT_TAB_RAM -DFLASH_RUN -Dat91sam7s256 -I.
/Libraries/at91lib/boards/SAM7-Pxxx_RevC -I./Libraries/at91lib -I./Libraries/at9
1lib/peripherals -I./Libraries/fat_sd -I. -ffunction-sections -fdata-sections -f
promote-loop-indices -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wred
undant-decls -Wshadow -Wcast-qual -Wcast-align -Wa,-adhlns=FLASH_RUN/fattime.lst
 -MD -MP -MF FLASH_RUN/dep/fattime.o.d -Wnested-externs  -std=gnu99 Libraries/fa
t_sd/fattime.c -o FLASH_RUN/fattime.o
---- Compiling C : Libraries/fat_sd/sd_spi_at91.c to FLASH_RUN/sd_spi_at91.o
arm-none-eabi-gcc -c -mthumb -gdwarf-2 -Os -mcpu=arm7tdmi -mthumb-interwork  -DM
OD_MTHOMAS_AT91LIB -DSTARTUP_DELAY -DVECT_TAB_RAM -DFLASH_RUN -Dat91sam7s256 -I.
/Libraries/at91lib/boards/SAM7-Pxxx_RevC -I./Libraries/at91lib -I./Libraries/at9
1lib/peripherals -I./Libraries/fat_sd -I. -ffunction-sections -fdata-sections -f
promote-loop-indices -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wred
undant-decls -Wshadow -Wcast-qual -Wcast-align -Wa,-adhlns=FLASH_RUN/sd_spi_at91
.lst -MD -MP -MF FLASH_RUN/dep/sd_spi_at91.o.d -Wnested-externs  -std=gnu99 Libr
aries/fat_sd/sd_spi_at91.c -o FLASH_RUN/sd_spi_at91.o
---- Compiling C : Libraries/fat_sd/option/ccsbcs.c to FLASH_RUN/ccsbcs.o
arm-none-eabi-gcc -c -mthumb -gdwarf-2 -Os -mcpu=arm7tdmi -mthumb-interwork  -DM
OD_MTHOMAS_AT91LIB -DSTARTUP_DELAY -DVECT_TAB_RAM -DFLASH_RUN -Dat91sam7s256 -I.
/Libraries/at91lib/boards/SAM7-Pxxx_RevC -I./Libraries/at91lib -I./Libraries/at9
1lib/peripherals -I./Libraries/fat_sd -I. -ffunction-sections -fdata-sections -f
promote-loop-indices -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wred
undant-decls -Wshadow -Wcast-qual -Wcast-align -Wa,-adhlns=FLASH_RUN/ccsbcs.lst
-MD -MP -MF FLASH_RUN/dep/ccsbcs.o.d -Wnested-externs  -std=gnu99 Libraries/fat_
sd/option/ccsbcs.c -o FLASH_RUN/ccsbcs.o
---- Compiling C : Libraries/at91lib/utility/string.c to FLASH_RUN/string.o
arm-none-eabi-gcc -c -mthumb -gdwarf-2 -Os -mcpu=arm7tdmi -mthumb-interwork  -DM
OD_MTHOMAS_AT91LIB -DSTARTUP_DELAY -DVECT_TAB_RAM -DFLASH_RUN -Dat91sam7s256 -I.
/Libraries/at91lib/boards/SAM7-Pxxx_RevC -I./Libraries/at91lib -I./Libraries/at9
1lib/peripherals -I./Libraries/fat_sd -I. -ffunction-sections -fdata-sections -f
promote-loop-indices -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wred
undant-decls -Wshadow -Wcast-qual -Wcast-align -Wa,-adhlns=FLASH_RUN/string.lst
-MD -MP -MF FLASH_RUN/dep/string.o.d -Wnested-externs  -std=gnu99 Libraries/at91
lib/utility/string.c -o FLASH_RUN/string.o
---- Compiling C : Libraries/at91lib/utility/stdio.c to FLASH_RUN/stdio.o
arm-none-eabi-gcc -c -mthumb -gdwarf-2 -Os -mcpu=arm7tdmi -mthumb-interwork  -DM
OD_MTHOMAS_AT91LIB -DSTARTUP_DELAY -DVECT_TAB_RAM -DFLASH_RUN -Dat91sam7s256 -I.
/Libraries/at91lib/boards/SAM7-Pxxx_RevC -I./Libraries/at91lib -I./Libraries/at9
1lib/peripherals -I./Libraries/fat_sd -I. -ffunction-sections -fdata-sections -f
promote-loop-indices -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wred
undant-decls -Wshadow -Wcast-qual -Wcast-align -Wa,-adhlns=FLASH_RUN/stdio.lst -
MD -MP -MF FLASH_RUN/dep/stdio.o.d -Wnested-externs  -std=gnu99 Libraries/at91li
b/utility/stdio.c -o FLASH_RUN/stdio.o
---- Compiling C : Libraries/at91lib/utility/led.c to FLASH_RUN/led.o
arm-none-eabi-gcc -c -mthumb -gdwarf-2 -Os -mcpu=arm7tdmi -mthumb-interwork  -DM
OD_MTHOMAS_AT91LIB -DSTARTUP_DELAY -DVECT_TAB_RAM -DFLASH_RUN -Dat91sam7s256 -I.
/Libraries/at91lib/boards/SAM7-Pxxx_RevC -I./Libraries/at91lib -I./Libraries/at9
1lib/peripherals -I./Libraries/fat_sd -I. -ffunction-sections -fdata-sections -f
promote-loop-indices -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wred
undant-decls -Wshadow -Wcast-qual -Wcast-align -Wa,-adhlns=FLASH_RUN/led.lst -MD
 -MP -MF FLASH_RUN/dep/led.o.d -Wnested-externs  -std=gnu99 Libraries/at91lib/ut
ility/led.c -o FLASH_RUN/led.o
---- Compiling C : Libraries/at91lib/peripherals/dbgu/dbgu.c to FLASH_RUN/dbgu.o

arm-none-eabi-gcc -c -mthumb -gdwarf-2 -Os -mcpu=arm7tdmi -mthumb-interwork  -DM
OD_MTHOMAS_AT91LIB -DSTARTUP_DELAY -DVECT_TAB_RAM -DFLASH_RUN -Dat91sam7s256 -I.
/Libraries/at91lib/boards/SAM7-Pxxx_RevC -I./Libraries/at91lib -I./Libraries/at9
1lib/peripherals -I./Libraries/fat_sd -I. -ffunction-sections -fdata-sections -f
promote-loop-indices -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wred
undant-decls -Wshadow -Wcast-qual -Wcast-align -Wa,-adhlns=FLASH_RUN/dbgu.lst -M
D -MP -MF FLASH_RUN/dep/dbgu.o.d -Wnested-externs  -std=gnu99 Libraries/at91lib/
peripherals/dbgu/dbgu.c -o FLASH_RUN/dbgu.o
---- Compiling C : Libraries/at91lib/peripherals/pio/pio.c to FLASH_RUN/pio.o
arm-none-eabi-gcc -c -mthumb -gdwarf-2 -Os -mcpu=arm7tdmi -mthumb-interwork  -DM
OD_MTHOMAS_AT91LIB -DSTARTUP_DELAY -DVECT_TAB_RAM -DFLASH_RUN -Dat91sam7s256 -I.
/Libraries/at91lib/boards/SAM7-Pxxx_RevC -I./Libraries/at91lib -I./Libraries/at9
1lib/peripherals -I./Libraries/fat_sd -I. -ffunction-sections -fdata-sections -f
promote-loop-indices -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wred
undant-decls -Wshadow -Wcast-qual -Wcast-align -Wa,-adhlns=FLASH_RUN/pio.lst -MD
 -MP -MF FLASH_RUN/dep/pio.o.d -Wnested-externs  -std=gnu99 Libraries/at91lib/pe
ripherals/pio/pio.c -o FLASH_RUN/pio.o
---- Compiling C : Libraries/at91lib/peripherals/aic/aic.c to FLASH_RUN/aic.o
arm-none-eabi-gcc -c -mthumb -gdwarf-2 -Os -mcpu=arm7tdmi -mthumb-interwork  -DM
OD_MTHOMAS_AT91LIB -DSTARTUP_DELAY -DVECT_TAB_RAM -DFLASH_RUN -Dat91sam7s256 -I.
/Libraries/at91lib/boards/SAM7-Pxxx_RevC -I./Libraries/at91lib -I./Libraries/at9
1lib/peripherals -I./Libraries/fat_sd -I. -ffunction-sections -fdata-sections -f
promote-loop-indices -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wred
undant-decls -Wshadow -Wcast-qual -Wcast-align -Wa,-adhlns=FLASH_RUN/aic.lst -MD
 -MP -MF FLASH_RUN/dep/aic.o.d -Wnested-externs  -std=gnu99 Libraries/at91lib/pe
ripherals/aic/aic.c -o FLASH_RUN/aic.o
---- Compiling C : Libraries/at91lib/peripherals/pmc/pmc.c to FLASH_RUN/pmc.o
arm-none-eabi-gcc -c -mthumb -gdwarf-2 -Os -mcpu=arm7tdmi -mthumb-interwork  -DM
OD_MTHOMAS_AT91LIB -DSTARTUP_DELAY -DVECT_TAB_RAM -DFLASH_RUN -Dat91sam7s256 -I.
/Libraries/at91lib/boards/SAM7-Pxxx_RevC -I./Libraries/at91lib -I./Libraries/at9
1lib/peripherals -I./Libraries/fat_sd -I. -ffunction-sections -fdata-sections -f
promote-loop-indices -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wred
undant-decls -Wshadow -Wcast-qual -Wcast-align -Wa,-adhlns=FLASH_RUN/pmc.lst -MD
 -MP -MF FLASH_RUN/dep/pmc.o.d -Wnested-externs  -std=gnu99 Libraries/at91lib/pe
ripherals/pmc/pmc.c -o FLASH_RUN/pmc.o
---- Compiling C : Libraries/at91lib/peripherals/spi/spi.c to FLASH_RUN/spi.o
arm-none-eabi-gcc -c -mthumb -gdwarf-2 -Os -mcpu=arm7tdmi -mthumb-interwork  -DM
OD_MTHOMAS_AT91LIB -DSTARTUP_DELAY -DVECT_TAB_RAM -DFLASH_RUN -Dat91sam7s256 -I.
/Libraries/at91lib/boards/SAM7-Pxxx_RevC -I./Libraries/at91lib -I./Libraries/at9
1lib/peripherals -I./Libraries/fat_sd -I. -ffunction-sections -fdata-sections -f
promote-loop-indices -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wred
undant-decls -Wshadow -Wcast-qual -Wcast-align -Wa,-adhlns=FLASH_RUN/spi.lst -MD
 -MP -MF FLASH_RUN/dep/spi.o.d -Wnested-externs  -std=gnu99 Libraries/at91lib/pe
ripherals/spi/spi.c -o FLASH_RUN/spi.o
---- Compiling C : Libraries/at91lib/peripherals/pit/pit.c to FLASH_RUN/pit.o
arm-none-eabi-gcc -c -mthumb -gdwarf-2 -Os -mcpu=arm7tdmi -mthumb-interwork  -DM
OD_MTHOMAS_AT91LIB -DSTARTUP_DELAY -DVECT_TAB_RAM -DFLASH_RUN -Dat91sam7s256 -I.
/Libraries/at91lib/boards/SAM7-Pxxx_RevC -I./Libraries/at91lib -I./Libraries/at9
1lib/peripherals -I./Libraries/fat_sd -I. -ffunction-sections -fdata-sections -f
promote-loop-indices -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wred
undant-decls -Wshadow -Wcast-qual -Wcast-align -Wa,-adhlns=FLASH_RUN/pit.lst -MD
 -MP -MF FLASH_RUN/dep/pit.o.d -Wnested-externs  -std=gnu99 Libraries/at91lib/pe
ripherals/pit/pit.c -o FLASH_RUN/pit.o
---- Compiling C : Libraries/at91lib/peripherals/usart/usart.c to FLASH_RUN/usar
t.o
arm-none-eabi-gcc -c -mthumb -gdwarf-2 -Os -mcpu=arm7tdmi -mthumb-interwork  -DM
OD_MTHOMAS_AT91LIB -DSTARTUP_DELAY -DVECT_TAB_RAM -DFLASH_RUN -Dat91sam7s256 -I.
/Libraries/at91lib/boards/SAM7-Pxxx_RevC -I./Libraries/at91lib -I./Libraries/at9
1lib/peripherals -I./Libraries/fat_sd -I. -ffunction-sections -fdata-sections -f
promote-loop-indices -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wred
undant-decls -Wshadow -Wcast-qual -Wcast-align -Wa,-adhlns=FLASH_RUN/usart.lst -
MD -MP -MF FLASH_RUN/dep/usart.o.d -Wnested-externs  -std=gnu99 Libraries/at91li
b/peripherals/usart/usart.c -o FLASH_RUN/usart.o
---- Compiling C : Libraries/at91lib/boards/SAM7-Pxxx_RevC/board_memories.c to F
LASH_RUN/board_memories.o
arm-none-eabi-gcc -c -mthumb -gdwarf-2 -Os -mcpu=arm7tdmi -mthumb-interwork  -DM
OD_MTHOMAS_AT91LIB -DSTARTUP_DELAY -DVECT_TAB_RAM -DFLASH_RUN -Dat91sam7s256 -I.
/Libraries/at91lib/boards/SAM7-Pxxx_RevC -I./Libraries/at91lib -I./Libraries/at9
1lib/peripherals -I./Libraries/fat_sd -I. -ffunction-sections -fdata-sections -f
promote-loop-indices -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wred
undant-decls -Wshadow -Wcast-qual -Wcast-align -Wa,-adhlns=FLASH_RUN/board_memor
ies.lst -MD -MP -MF FLASH_RUN/dep/board_memories.o.d -Wnested-externs  -std=gnu9
9 Libraries/at91lib/boards/SAM7-Pxxx_RevC/board_memories.c -o FLASH_RUN/board_me
mories.o
---- Compiling C : Libraries/at91lib/boards/SAM7-Pxxx_RevC/board_lowlevel.c to F
LASH_RUN/board_lowlevel.o
arm-none-eabi-gcc -c -mthumb -gdwarf-2 -Os -mcpu=arm7tdmi -mthumb-interwork  -DM
OD_MTHOMAS_AT91LIB -DSTARTUP_DELAY -DVECT_TAB_RAM -DFLASH_RUN -Dat91sam7s256 -I.
/Libraries/at91lib/boards/SAM7-Pxxx_RevC -I./Libraries/at91lib -I./Libraries/at9
1lib/peripherals -I./Libraries/fat_sd -I. -ffunction-sections -fdata-sections -f
promote-loop-indices -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wred
undant-decls -Wshadow -Wcast-qual -Wcast-align -Wa,-adhlns=FLASH_RUN/board_lowle
vel.lst -MD -MP -MF FLASH_RUN/dep/board_lowlevel.o.d -Wnested-externs  -std=gnu9
9 Libraries/at91lib/boards/SAM7-Pxxx_RevC/board_lowlevel.c -o FLASH_RUN/board_lo
wlevel.o
---- Linking : FLASH_RUN/at91sam_chanfat.elf
arm-none-eabi-gcc -mthumb -gdwarf-2 -Os -mcpu=arm7tdmi -mthumb-interwork  -DMOD_
MTHOMAS_AT91LIB -DSTARTUP_DELAY -DVECT_TAB_RAM -DFLASH_RUN -Dat91sam7s256 -I./Li
braries/at91lib/boards/SAM7-Pxxx_RevC -I./Libraries/at91lib -I./Libraries/at91li
b/peripherals -I./Libraries/fat_sd -I. -ffunction-sections -fdata-sections -fpro
mote-loop-indices -Wall -Wextra -Wimplicit -Wcast-align -Wpointer-arith -Wredund
ant-decls -Wshadow -Wcast-qual -Wcast-align -Wa,-adhlns=FLASH_RUN/board_cstartup
.lst -MD -MP -MF FLASH_RUN/dep/at91sam_chanfat.elf.d FLASH_RUN/board_cstartup.o
FLASH_RUN/main.o FLASH_RUN/comm.o FLASH_RUN/term_io.o FLASH_RUN/rtc.o FLASH_RUN/
ff_test_term.o FLASH_RUN/misc_test_term.o FLASH_RUN/uart1.o FLASH_RUN/ff.o FLASH
_RUN/fattime.o FLASH_RUN/sd_spi_at91.o FLASH_RUN/ccsbcs.o FLASH_RUN/string.o FLA
SH_RUN/stdio.o FLASH_RUN/led.o FLASH_RUN/dbgu.o FLASH_RUN/pio.o FLASH_RUN/aic.o
FLASH_RUN/pmc.o FLASH_RUN/spi.o FLASH_RUN/pit.o FLASH_RUN/usart.o FLASH_RUN/boar
d_memories.o FLASH_RUN/board_lowlevel.o --output FLASH_RUN/at91sam_chanfat.elf -
nostartfiles -Wl,-Map=FLASH_RUN/at91sam_chanfat.map,--cref,--gc-sections -L./Lib
raries/at91lib/boards/SAM7-Pxxx_RevC/ -lc  -lm  -lc -lgcc  -T./Libraries/at91lib
/boards/SAM7-Pxxx_RevC/at91sam7s256/flash.lds
Creating load file: FLASH_RUN/at91sam_chanfat.hex
arm-none-eabi-objcopy -O ihex FLASH_RUN/at91sam_chanfat.elf FLASH_RUN/at91sam_ch
anfat.hex
Creating load file: FLASH_RUN/at91sam_chanfat.bin
arm-none-eabi-objcopy -O binary FLASH_RUN/at91sam_chanfat.elf FLASH_RUN/at91sam_
chanfat.bin
Creating Extended Listing/Disassembly: FLASH_RUN/at91sam_chanfat.lss
arm-none-eabi-objdump -h -S -C -r FLASH_RUN/at91sam_chanfat.elf > FLASH_RUN/at91
sam_chanfat.lss
Creating Symbol Table: FLASH_RUN/at91sam_chanfat.sym
arm-none-eabi-nm -n FLASH_RUN/at91sam_chanfat.elf > FLASH_RUN/at91sam_chanfat.sy
m
Size after build:
arm-none-eabi-size -A  FLASH_RUN/at91sam_chanfat.elf
FLASH_RUN/at91sam_chanfat.elf  :
section             size      addr
.fixed             25040   1048576
.relocate           1856   2097152
.bss                7188   2099008
.ARM.attributes       44         0
.comment             989         0
.debug_line        10885         0
.debug_info        37183         0
.debug_abbrev       8126         0
.debug_aranges      2080         0
.debug_ranges       2248         0
.debug_frame        5132         0
.debug_loc         28260         0
.debug_pubnames     2862         0
.debug_str          7484         0
Total             139377


"Programming with OPENOCD"
OpenOCD\bin\openocd -d0 -f interface/jtagkey2.cfg -f OpenOCD_at91sam7s256_FLASH.
cfg -c init -c targets -c "reset init" -c "halt" -c "flash write_image erase FLA
SH_RUN/at91sam_chanfat.elf" -c "verify_image FLASH_RUN/at91sam_chanfat.elf" -c "
reset run" -c shutdown
Open On-Chip Debugger 0.3.0-in-development (2009-09-01-21:04) svn:2660
$URL: http://svn.berlios.de/svnroot/repos/openocd/trunk/src/openocd.c $
For bug reports, read http://svn.berlios.de/svnroot/repos/openocd/trunk/BUGS
debug_level: 0
5 kHz
jtag_nsrst_delay: 100
jtag_ntrst_delay: 100
    TargetName         Type       Endian TapName            State
--  ------------------ ---------- ------ ------------------ ------------
 0* AT91SAM7S256.cpu   arm7tdmi   little AT91SAM7S256.cpu   running
target state: halted
target halted in Thumb state due to debug-request, current mode: Supervisor
cpsr: 0x000000f3 pc: 0x001051ce
6000 kHz
fast memory access is enabled
dcc downloads are enabled
auto erase enabled
wrote 26896 byte from file FLASH_RUN/at91sam_chanfat.elf in 3.734375s (7.033473
kb/s)
verified 26896 bytes in 0.140625s

C:\WinARM\examples\at91sam_chanfat_ws\project>

---

Scratchpad:

C:\WinARM\examples\at91sam_chanfat_ws\project>arm-none-eabi-ld --verbose
GNU ld (Sourcery G++ Lite 2009q1-161) 2.19.51.20090205
  Supported emulations:
   armelf
using internal linker script:
==================================================
/* Script for -z combreloc: combine and sort reloc sections */
OUTPUT_FORMAT("elf32-littlearm", "elf32-bigarm",
              "elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_start)
SEARCH_DIR("=/usr/local/lib"); SEARCH_DIR("=/lib"); SEARCH_DIR("=/usr/lib");
SECTIONS
{
  /* Read-only sections, merged into text segment: */
  PROVIDE (__executable_start = SEGMENT_START("text-segment", 0x8000)); . = SEGM
ENT_START("text-segment", 0x8000);
  .interp         : { *(.interp) }
  .note.gnu.build-id : { *(.note.gnu.build-id) }
  .hash           : { *(.hash) }
  .gnu.hash       : { *(.gnu.hash) }
  .dynsym         : { *(.dynsym) }
  .dynstr         : { *(.dynstr) }
  .gnu.version    : { *(.gnu.version) }
  .gnu.version_d  : { *(.gnu.version_d) }
  .gnu.version_r  : { *(.gnu.version_r) }
  .rel.dyn        :
    {
      *(.rel.init)
      *(.rel.text .rel.text.* .rel.gnu.linkonce.t.*)
      *(.rel.fini)
      *(.rel.rodata .rel.rodata.* .rel.gnu.linkonce.r.*)
      *(.rel.data.rel.ro* .rel.gnu.linkonce.d.rel.ro.*)
      *(.rel.data .rel.data.* .rel.gnu.linkonce.d.*)
      *(.rel.tdata .rel.tdata.* .rel.gnu.linkonce.td.*)
      *(.rel.tbss .rel.tbss.* .rel.gnu.linkonce.tb.*)
      *(.rel.ctors)
      *(.rel.dtors)
      *(.rel.got)
      *(.rel.bss .rel.bss.* .rel.gnu.linkonce.b.*)
    }
  .rel.ifunc.dyn        :
    {
      *(.rel.ifunc.*)
    }
  .rela.dyn       :
    {
      *(.rela.init)
      *(.rela.text .rela.text.* .rela.gnu.linkonce.t.*)
      *(.rela.fini)
      *(.rela.rodata .rela.rodata.* .rela.gnu.linkonce.r.*)
      *(.rela.data .rela.data.* .rela.gnu.linkonce.d.*)
      *(.rela.tdata .rela.tdata.* .rela.gnu.linkonce.td.*)
      *(.rela.tbss .rela.tbss.* .rela.gnu.linkonce.tb.*)
      *(.rela.ctors)
      *(.rela.dtors)
      *(.rela.got)
      *(.rela.bss .rela.bss.* .rela.gnu.linkonce.b.*)
    }
  .rela.ifunc.dyn       :
    {
      *(.rela.ifunc.*)
    }
  .rel.plt        : { *(.rel.plt) }
  .rela.plt       : { *(.rela.plt) }
  .init           :
  {
    KEEP (*(.init))
  } =0
  .plt            : { *(.plt) }
  .text           :
  {
    *(.text .stub .text.* .gnu.linkonce.t.*)
    /* .gnu.warning sections are handled specially by elf32.em.  */
    *(.gnu.warning)
    *(.glue_7t) *(.glue_7) *(.vfp11_veneer) *(.janus_2cc_veneer) *(.v4_bx)
  } =0
  .fini           :
  {
    KEEP (*(.fini))
  } =0
  PROVIDE (__etext = .);
  PROVIDE (_etext = .);
  PROVIDE (etext = .);
  .rodata         : { *(.rodata .rodata.* .gnu.linkonce.r.*) }
  .rodata1        : { *(.rodata1) }
  .ARM.extab   : { *(.ARM.extab* .gnu.linkonce.armextab.*) }
   __exidx_start = .;
  .ARM.exidx   : { *(.ARM.exidx* .gnu.linkonce.armexidx.*) }
   __exidx_end = .;
  .eh_frame_hdr : { *(.eh_frame_hdr) }
  .eh_frame       : ONLY_IF_RO { KEEP (*(.eh_frame)) }
  .gcc_except_table   : ONLY_IF_RO { *(.gcc_except_table .gcc_except_table.*) }
  /* Adjust the address for the data segment.  We want to adjust up to
     the same address within the page on the next page up.  */
  . = ALIGN(CONSTANT (MAXPAGESIZE)) + (. & (CONSTANT (MAXPAGESIZE) - 1));
  /* Exception handling  */
  .eh_frame       : ONLY_IF_RW { KEEP (*(.eh_frame)) }
  .gcc_except_table   : ONLY_IF_RW { *(.gcc_except_table .gcc_except_table.*) }
  /* Thread Local Storage sections  */
  .tdata          : { *(.tdata .tdata.* .gnu.linkonce.td.*) }
  .tbss           : { *(.tbss .tbss.* .gnu.linkonce.tb.*) *(.tcommon) }
  .preinit_array     :
  {
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array))
    PROVIDE_HIDDEN (__preinit_array_end = .);
  }
  .init_array     :
  {
     PROVIDE_HIDDEN (__init_array_start = .);
     KEEP (*(SORT(.init_array.*)))
     KEEP (*(.init_array))
     PROVIDE_HIDDEN (__init_array_end = .);
  }
  .fini_array     :
  {
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(.fini_array))
    KEEP (*(SORT(.fini_array.*)))
    PROVIDE_HIDDEN (__fini_array_end = .);
  }
  .ctors          :
  {
    /* gcc uses crtbegin.o to find the start of
       the constructors, so we make sure it is
       first.  Because this is a wildcard, it
       doesn't matter if the user does not
       actually link against crtbegin.o; the
       linker won't look for a file to match a
       wildcard.  The wildcard also means that it
       doesn't matter which directory crtbegin.o
       is in.  */
    KEEP (*crtbegin.o(.ctors))
    KEEP (*crtbegin?.o(.ctors))
    /* We don't want to include the .ctor section from
       the crtend.o file until after the sorted ctors.
       The .ctor section from the crtend file contains the
       end of ctors marker and it must be last */
    KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .ctors))
    KEEP (*(SORT(.ctors.*)))
    KEEP (*(.ctors))
  }
  .dtors          :
  {
    KEEP (*crtbegin.o(.dtors))
    KEEP (*crtbegin?.o(.dtors))
    KEEP (*(EXCLUDE_FILE (*crtend.o *crtend?.o ) .dtors))
    KEEP (*(SORT(.dtors.*)))
    KEEP (*(.dtors))
  }
  .jcr            : { KEEP (*(.jcr)) }
  .data.rel.ro : { *(.data.rel.ro.local* .gnu.linkonce.d.rel.ro.local.*) *(.data
.rel.ro* .gnu.linkonce.d.rel.ro.*) }
  .dynamic        : { *(.dynamic) }
  .got            : { *(.got.plt) *(.got) }
  .data           :
  {
    __data_start = . ;
    *(.data .data.* .gnu.linkonce.d.*)
    SORT(CONSTRUCTORS)
  }
  .data1          : { *(.data1) }
  _edata = .; PROVIDE (edata = .);
  __bss_start = .;
  __bss_start__ = .;
  .bss            :
  {
   *(.dynbss)
   *(.bss .bss.* .gnu.linkonce.b.*)
   *(COMMON)
   /* Align here to ensure that the .bss section occupies space up to
      _end.  Align after .bss to ensure correct alignment even if the
      .bss section disappears because there are no input sections.
      FIXME: Why do we need it? When there is no .bss section, we don't
      pad the .data section.  */
   . = ALIGN(. != 0 ? 32 / 8 : 1);
  }
  _bss_end__ = . ; __bss_end__ = . ;
  . = ALIGN(32 / 8);
  . = ALIGN(32 / 8);
  __end__ = . ;
  _end = .; PROVIDE (end = .);
  /* Stabs debugging sections.  */
  .stab          0 : { *(.stab) }
  .stabstr       0 : { *(.stabstr) }
  .stab.excl     0 : { *(.stab.excl) }
  .stab.exclstr  0 : { *(.stab.exclstr) }
  .stab.index    0 : { *(.stab.index) }
  .stab.indexstr 0 : { *(.stab.indexstr) }
  .comment       0 : { *(.comment) }
  /* DWARF debug sections.
     Symbols in the DWARF debugging sections are relative to the beginning
     of the section so we begin them at 0.  */
  /* DWARF 1 */
  .debug          0 : { *(.debug) }
  .line           0 : { *(.line) }
  /* GNU DWARF 1 extensions */
  .debug_srcinfo  0 : { *(.debug_srcinfo) }
  .debug_sfnames  0 : { *(.debug_sfnames) }
  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges  0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  /* DWARF 2 */
  .debug_info     0 : { *(.debug_info .gnu.linkonce.wi.*) }
  .debug_abbrev   0 : { *(.debug_abbrev) }
  .debug_line     0 : { *(.debug_line) }
  .debug_frame    0 : { *(.debug_frame) }
  .debug_str      0 : { *(.debug_str) }
  .debug_loc      0 : { *(.debug_loc) }
  .debug_macinfo  0 : { *(.debug_macinfo) }
  /* SGI/MIPS DWARF 2 extensions */
  .debug_weaknames 0 : { *(.debug_weaknames) }
  .debug_funcnames 0 : { *(.debug_funcnames) }
  .debug_typenames 0 : { *(.debug_typenames) }
  .debug_varnames  0 : { *(.debug_varnames) }
  /* DWARF 3 */
  .debug_pubtypes 0 : { *(.debug_pubtypes) }
  .debug_ranges   0 : { *(.debug_ranges) }
    .stack         0x80000 :
  {
    _stack = .;
    *(.stack)
  }
  .ARM.attributes 0 : { KEEP (*(.ARM.attributes)) KEEP (*(.gnu.attributes)) }
  .note.gnu.arm.ident 0 : { KEEP (*(.note.gnu.arm.ident)) }
  /DISCARD/ : { *(.note.GNU-stack) *(.gnu_debuglink) }
}


==================================================

C:\WinARM\examples\at91sam_chanfat_ws\project>
