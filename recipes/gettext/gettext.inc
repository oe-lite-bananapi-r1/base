# -*- mode:python; -*-
DESCRIPTION = "The GNU internationalization library."
HOMEPAGE = "http://www.gnu.org/software/gettext/gettext.html"

RECIPE_TYPES = "machine native sdk"

inherit c++ autotools library make-vpath
DEPENDS_AUTORECONF = ""

require conf/fetch/gnu.conf
SRC_URI = "${GNU_MIRROR}/gettext/gettext-${PV}.tar.gz"

DEPENDS = "libiconv libm"

DEPENDS += "${DEPENDS_LIBNCURSES}"
DEPENDS_LIBNCURSES = "libncurses"
DEPENDS_LIBNCURSES:HOST_OS_mingw32 = ""

DEPENDS += "${DEPENDS_LIBDL}"
DEPENDS_LIBDL = "libdl"
DEPENDS_LIBDL:HOST_OS_mingw32 = ""

DEPENDS += "${DEPENDS_LIBPTHREAD}"
DEPENDS_LIBPTHREAD = "libpthread"
DEPENDS_LIBPTHREAD:HOST_OS_mingw32 = ""

DEPENDS += "${DEPENDS_SELF_NATIVE}"
DEPENDS_SELF_NATIVE = "native:gettext"
DEPENDS_SELF_NATIVE:native = ""

acpaths = "-I ${S}/gnulib-local/m4/ \
           -I ${S}/gettext-runtime/m4 \
           -I ${S}/gettext-tools/m4"

EXTRA_OECONF += "\
--disable-rpath --enable-relocatable \
--disable-dependency-tracking \
--disable-java --disable-native-java \
--disable-csharp \
--without-lispdir \
--disable-libasprintf \
--disable-acl \
--disable-openmp \
--disable-largefile \
--with-included-libxml \
--with-included-libunistring \
--with-included-libcroco \
--without-emacs --without-git --without-cvs \
--without-libcurses-prefix --without-libncurses-prefix --without-libtermcap-prexix --without-libxcurses-prefix \
--with-included-glib \
"

CFLAGS += "-O1"

RECIPE_FLAGS += "nls"
EXTRA_OECONF += "${EXTRA_OECONF_NLS}"
EXTRA_OECONF_NLS = " --disable-nls"
EXTRA_OECONF_NLS:USE_nls = " --enable-nls"
EXTRA_OECONF_NLS:native = " --enable-nls"
EXTRA_OECONF_NLS:HOST_OS_mingw32 = " --enable-nls"
EXTRA_OECONF_NLS:HOST_KERNEL_darwin = " --enable-nls"

EXTRA_OECONF += "${EXTRA_OECONF_GETTEXT}"
EXTRA_OECONF_GETTEXT = ""
EXTRA_OECONF_GETTEXT:native = "--disable-curses --with-included-gettext"
EXTRA_OECONF_GETTEXT:HOST_OS_mingw32 = "--disable-curses --with-included-gettext"

FILES_${PN} += "${libdir}/gettext ${datadir}/gettext"
COMMON_DEPENDS = "libintl libgettextpo libgettextlib \
    libiconv ${DEPENDS_LIBNCURSES} ${DEPENDS_LIBDL} libm"
DEPENDS_${PN} = "${COMMON_DEPENDS}"
RDEPENDS_${PN} = "${COMMON_DEPENDS}"

inherit auto-package-utils
AUTO_PACKAGE_UTILS = "autopoint envsubst gettext gettextize gettext.sh \
	msgattrib msgcat msgcmp msgcomm msgconv msgen msgexec msgfilter \
	msgfmt msggrep msginit msgmerge msgunfmt msguniq ngettext \
	recode-sr-latin xgettext"
DEPENDS_${PN}-gettext-sh = "${PN}-gettext ${PN}-ngettext"
RDEPENDS_${PN}-gettext-sh = "${PN}-gettext ${PN}-ngettext"
PACKAGES =+ "${PN}-utils"
DEPENDS_${PN}-utils += "gettext ${AUTO_PACKAGE_UTILS_PACKAGES}"

inherit auto-package-libs
AUTO_PACKAGE_LIBS = "intl gettextpo gettextlib gettextsrc"
AUTO_PACKAGE_LIBS_DEV_DEPENDS = "${PN}-dev_${PV}"
AUTO_PACKAGE_LIBS_LIBDIR += "${sharedlibdir}:lib:-*:${SOLIBSDEV}:"
FILES_${PN}-libintl += "${sharedlibdir}/preloadable_libintl${SOLIBSDEV}"
FILES_${PN}-libintl-dev += "${sharedlibdir}/.debug/preloadable_libintl${SOLIBSDEV}"
DEPENDS_${PN}-libintl += "libiconv"
DEPENDS_${PN}-libgettextpo += "libiconv"
DEPENDS_${PN}-libgettextlib += "libiconv ${DEPENDS_LIBNCURSES}"
DEPENDS_${PN}-libgettextsrc += "libgettextlib libiconv ${DEPENDS_LIBNCURSES} ${DEPENDS_LIBDL} libm"
