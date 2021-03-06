# -*- mode:python; -*-
DESCRIPTION = "Tools for managing memory technology devices."
HOMEPAGE = "http://www.linux-mtd.infradead.org/"

RECIPE_TYPES = "machine native sdk"

COMPATIBLE_HOST_ARCHS = ".*linux"

inherit c make auto-package-utils

SRC_URI = "git://git.infradead.org/mtd-utils.git;protocol=git;tag=v${PV}"
S = "${SRCDIR}/mtd-utils"

DEPENDS = "libz liblzo2 libuuid libm"

do_configure () {
	sed -i \
		-e "s%\(PREFIX\)=.*%\1=${prefix}%g" \
		-e "s%\(EXEC_PREFIX\)=.*%\1=${exec_prefix}%g" \
		-e "s%\(SBINDIR\)=.*%\1=${sbindir}%g" \
		-e "s%\(MANDIR\)=.*%\1=${mandir}%g" \
		-e "s%\(INCLUDEDIR\)=.*%\1=${includedir}%g" \
		common.mk
}

EXTRA_OEMAKE = "'LDFLAGS=${LDFLAGS}' \
	'CFLAGS=${CFLAGS} -I${S}/include -DWITHOUT_XATTR'"

do_install () {
	oe_runmake install DESTDIR=${D}
	install -d ${D}${includedir}/mtd/
	for f in ${S}/include/mtd/*.h; do
		install -m 0644 $f ${D}${includedir}/mtd/
	done
}

AUTO_PACKAGE_UTILS = "\
	bin2nand docfdisk doc_loadbios flashcp flash_erase flash_eraseall \
	flash_info flash_lock flash_otp_dump flash_otp_info flash_unlock \
	ftl_check ftl_format jffs2dump mkbootenv mkfs.jffs2 mkfs.ubifs mkpfi \
	mtd_debug mtdinfo nand2bin nanddump nandtest nandwrite nftldump \
	nftl_format pddcustomize pfi2bin pfiflash recv_image rfddump \
	rfdformat serve_image sumtool ubiattach ubicrc32 \
	ubidetach ubiformat ubigen ubimirror ubimkvol ubinfo ubinize \
	ubirename ubirmvol ubirsvol ubiupdatevol unubi \
"

AUTO_PACKAGE_UTILS_DEPENDS = "libc libgcc"
AUTO_PACKAGE_UTILS_RDEPENDS = "libc libgcc"

FILES_mtd-utils-ubicrc32 = "${sbindir}/ubicrc32.pl"

DEPENDS_${PN}-jffs2reader = "libz liblzo2"
RDEPENDS_${PN}-jffs2reader = "libz liblzo2"
DEPENDS_${PN}-mkfs-jffs2 = "libz liblzo2"
RDEPENDS_${PN}-mkfs-jffs2 = "libz liblzo2"
DEPENDS_${PN}-mkfs-ubifs = "libz liblzo2 libuuid libm"
RDEPENDS_${PN}-mkfs-ubifs = "libz liblzo2 libuuid libm"

# The mtd-utils package is used to pull in all provided util features
RDEPENDS_${PN} = "${AUTO_PACKAGE_UTILS_PROVIDES}"
