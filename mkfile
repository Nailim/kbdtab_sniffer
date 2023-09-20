</$objtype/mkfile

RC=$home/bin/rc
BIN=$home/bin/$objtype

ALL=kbdtab_sniffer

all:V:	$ALL

kbdtab_sniffer:		kbdtab_sniffer.$O
	$LD $LDFLAGS -o kbdtab_sniffer kbdtab_sniffer.$O

kbdtab_sniffer.$O:	kbdtab_sniffer.c
	$CC $CFLAGS kbdtab_sniffer.c

clean:V:
	rm -f *.$O kbdtab_sniffer

install:V:
	mv kbdtab_sniffer $BIN/

uninstall:V:
	rm -f $BIN/kbdtab_sniffer
