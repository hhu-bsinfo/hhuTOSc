#*****************************************************************************
#* ACHTUNG:         Ein falsch angegebenes Laufwerk kann dazu fuehren, dass  *
#*                  Daten auf dem spezifizierten Laufwerk verloren gehen!    *
#*                  Nicht mit root-Rechten ausfuehren!                       *
#*                                                                           *
#* Autor:           Michael Schoettner, HHU, 11.01.2023                      *
#*****************************************************************************/

BOOTDRIVE = /dev/sdb

# -----------------------------------------------------------------------------
# Liste der Quelltexte:
BOOT_SOURCES = $(shell find ./boot -name "*.asm")
CC_SOURCES = $(shell find . -name "*.cc")
C_SOURCES = $(shell find . -name "*.c")
ASM_SOURCES = $(shell find ./kernel -name "*.asm")

# -------------------------------------------------------------------------
# Einstellungen fuer die Tools
VERBOSE = @
ASMOBJFORMAT = elf64
ASMFLAGS := -w+error=label-redef-late
OBJDIR = ./build
DEPDIR = ./dep
DELETE = rm
ASM = nasm
CC ?= gcc
CXX ?= g++
CFLAGS := $(CFLAGS) -m64 -Wall -fno-stack-protector -fno-omit-frame-pointer  -nostdlib -I. -g -ffreestanding -fno-pie -fno-pic -mpreferred-stack-boundary=4 -Wno-write-strings -mno-sse -mno-sse2 -mmanual-endbr
CXXFLAGS := $(CFLAGS) -Wno-non-virtual-dtor -nodefaultlibs -nostdinc -nostdlib -fno-threadsafe-statics -fno-use-cxa-atexit -fno-rtti -fno-exceptions
GRUB_CFG := boot/grub.cfg

# -------------------------------------------------------------------------
# Namen der Unterverzeichnisse mit den Quelltexten
VPATH = $(sort $(dir $(BOOT_SOURCES) $(CC_SOURCES) $(C_SOURCES) $(ASM_SOURCES)))


# -------------------------------------------------------------------------
# Listen mit den Objektdateien, die beim Kompilieren entstehen:
C_OBJECTS = $(notdir $(C_SOURCES:.c=.o))
CC_OBJECTS = $(notdir $(CC_SOURCES:.cc=.o))

DEP_FILES = $(patsubst %.o,$(DEPDIR)/%.d,$(C_OBJECTS))
DEP_FILES += $(patsubst %.o,$(DEPDIR)/%.d,$(CC_OBJECTS))

ASM_OBJECTS = $(patsubst %.asm,_%.o, $(notdir $(ASM_SOURCES)))

BOOT_OBJECTS = $(addprefix $(OBJDIR)/,$(patsubst %.asm,_%.o, $(notdir $(BOOT_SOURCES))))
OBJPRE = $(addprefix $(OBJDIR)/,$(ASM_OBJECTS) $(C_OBJECTS) $(CC_OBJECTS))

# --------------------------------------------------------------------------
# Default targets (einfaches Image, Image fuer USB Sticks, Image fuer VMWare
# und Boot CDs)
all: $(OBJDIR)/system.iso

dump:
	echo $(BOOT_OBJECTS)
	echo $(FIRST_OBJECT)


# --------------------------------------------------------------------------
# Regeln zur Erzeugung der Abhaengigkeitsdateien
$(DEPDIR)/%.d : %.c
	@echo "DEP		$@"
	@if test \( ! \( -d $(@D) \) \) ;then mkdir -p $(@D);fi
	$(VERBOSE) $(CC) $(CFLAGS) -MM -MT $(OBJDIR)/$*.o -MF $@ $<

$(DEPDIR)/%.d : %.cc
	@echo "DEP		$@"
	@if test \( ! \( -d $(@D) \) \) ;then mkdir -p $(@D);fi
	$(VERBOSE) $(CXX) $(CXXFLAGS) -MM -MT $(OBJDIR)/$*.o -MF $@ $<


# --------------------------------------------------------------------------
# Regeln zur Erzeugung der Objektdateien
$(OBJDIR)/%.o : %.c
	@echo "CC		$@" 
	@if test \( ! \( -d $(@D) \) \) ;then mkdir -p $(@D);fi
	$(VERBOSE) $(CC) -c $(CFLAGS) -o $@ $<

$(OBJDIR)/%.o : %.cc
	@echo "CXX		$@" 
	@if test \( ! \( -d $(@D) \) \) ;then mkdir -p $(@D);fi
	$(VERBOSE) $(CXX) -c $(CXXFLAGS) -o $@ $<
	
$(OBJDIR)/_%.o : %.asm
	@echo "ASM		$@"
	@if test \( ! \( -d $(@D) \) \) ;then mkdir -p $(@D);fi
	$(VERBOSE) $(ASM) -f $(ASMOBJFORMAT) $(ASMFLAGS) -o $@ $<


# --------------------------------------------------------------------------
# System binden
$(OBJDIR)/system: $(BOOT_OBJECTS) $(OBJPRE)  
	@echo "LD		$@"
	@if test \( ! \( -d $(@D) \) \) ;then mkdir -p $(@D);fi
	$(VERBOSE) $(CXX) $(CXXFLAGS) -static -e startup -T sections -o $(OBJDIR)/system $(BOOT_OBJECTS) $(OBJPRE) 


# --------------------------------------------------------------------------
# ISO erstellen
$(OBJDIR)/system.iso: $(OBJDIR)/system
	@mkdir -p build/isofiles/boot/grub
	@cp $(OBJDIR)/system build/isofiles/boot/system.bin
	@cp $(GRUB_CFG) build/isofiles/boot/grub
	@grub-mkrescue -o $(OBJDIR)/system.iso build/isofiles
#	@rm -r build/isofiles

# --------------------------------------------------------------------------
# 'clean' loescht das generierte System, die Objektdateien und die
# Abhaengigkeitsdateien

clean:
	@echo "RM		$(OBJDIR)"
	$(VERBOSE) rm -rf $(OBJDIR)
	@echo "RM		$(DEPDIR)"
	$(VERBOSE) rm -rf $(DEPDIR)

# --------------------------------------------------------------------------
# 'bootdisk' erzeugt zunaechst das System, falls das noch nicht geschehen ist.
# Danach wird das Image auf das Block-Device 'DRIVE' geschrieben

bootdisk:  $(OBJDIR)/system.iso
	dd if=$(OBJDIR)/system.iso of=$(BOOTDRIVE) conv=fdatasync status=progress
	sync
    
# --------------------------------------------------------------------------
# 'qemu' ruft den qemu-Emulator mit dem System auf.

qemu: $(OBJDIR)/system.iso
	qemu-system-x86_64 -cdrom $(OBJDIR)/system.iso -k en-us -soundhw pcspk -vga std

# --------------------------------------------------------------------------
# 'qemu-gdb' ruft den qemu-Emulator mit aktiviertem GDB-Stub mit dem System
# auf, sodass es per GDB inspiziert werden kann.

qemu-gdb: $(OBJDIR)/system.iso
	$(VERBOSE) echo "break startup" > /tmp/gdbcommands.$(shell id -u)
	$(VERBOSE) echo "target remote 127.0.0.1:1234" >> /tmp/gdbcommands.$(shell id -u)
	$(VERBOSE) echo "continue" >> /tmp/gdbcommands.$(shell id -u)
	qemu-system-x86_64 -cdrom $(OBJDIR)/system.iso -k en-us -s -S -soundhw pcspk -vga std 

# --------------------------------------------------------------------------
# 'gdb' startet den GDB-Debugger und verbindet sich mit dem GDB-Stub des vorher
# gestarteten Qemu.

gdb:
	gdb -x /tmp/gdbcommands.$(shell id -u) $(OBJDIR)/system


# --------------------------------------------------------------------------
# Einbindung der Abhaengigkeitsdateien

ifneq ($(MAKECMDGOALS),clean)
-include $(DEP_FILES)
endif

.PHONY: clean bootdisk gdb 

help:
	@/bin/clear
	@/bin/echo -e "\n" \
		"\e[1mMAKEFILE fuer hhuTOSc\e[0m\n" \
		"---------------------\n\n" \
		"Durch Aufruf von '\e[4mmake\e[0m' wird das Betriebssystem compiliert und gebunden.\n" \
		"Danach wird die Datei 'system.iso' im Verzeichnis 'build' erzeugt.\n"
	@/bin/echo -e " Emulation\n" \
		"	\e[3mqemu\e[0m        Startet das Betriebssystem in QEMU\n" \
		"	            Achtung: Manchmal ist das Verhalten des Beitriebssystems\n" \
		"	            in Qemu nicht exakt wie auf echter Hardware!\n\n" \
		"	\e[3mqemu-gdb\e[0m    Startet Qemu mit GDB-Unterstuetzung und wartet, dass GDB\n" \
		"	            sich verbindet. Dies geht mit dem Aufruf 'make qemu-gdb'.\n"
	@/bin/echo -e " Bootfaehiges Medium\n" \
		"	\e[3mbootdisk\e[0m    Schreibt die zuvor erzeugte 'system.iso' Datei auf den\n" \
		"                   konfigurierten USB-Stick. Hierzu muss im Makefile die\n" \
        "                   Variable \e[4mBOOTDRIVE\e[0m auf die richtige Geraetedatei zeigen.\n" \
        "                   Fuer den Zugriff auf die Geraetedatei sind root-Rechte \n" \
        "                   notwendig.\n" \
        "                   \e[1mAchtung:\e[0m Alle Daten auf dem Stick werden geloescht.\n" \
        "                   Sollte die Gerätedatei falsch sein, werden u.U. Daten \n" \
        "                   auf der Festplatte geloescht!\n\n"
