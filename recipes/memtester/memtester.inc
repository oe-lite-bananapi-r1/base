DESCRIPTION = "Utility to test for faulty memory subsystem"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit c make

SRC_URI = "http://pyropus.ca/software/memtester/old-versions/memtester-${PV}.tar.gz"

do_compile () {
	echo '${CC} ${CFLAGS} -DPOSIX -c' > conf-cc
	echo '${CC} ${LDFLAGS}' > conf-ld
	oe_runmake
}

do_install () {
	install -d ${D}${bindir}
	install -d ${D}${mandir}/man8
	install -m 0755 memtester ${D}${bindir}/
	install -m 0755 memtester.8 ${D}${mandir}/man8/
}
