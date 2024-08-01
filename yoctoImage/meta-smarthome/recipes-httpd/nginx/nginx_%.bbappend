FILESEXTRAPATHS:prepend := "${THISDIR}/files:"

SRC_URI += "file://default_server"

do_install:append() {
	install -m 0644 ${WORKDIR}/default_server ${D}${sysconfdir}/nginx/sites-available/
}
