SUMMARY = "startup service to handle daemon apps "
DESCRIPTION = "${SUMMARY}"
LICENSE = "CLOSED"

SRC_URI = "file://wpastartup-sv"

S = "${WORKDIR}"

inherit update-rc.d

INITSCRIPT_NAME = "wpastartup-sv"
INITSCRIPT_PARAMS = "start 11 1 2 3 4 5 . stop 11 1 6 ."

do_install(){
    install -d ${D}${sysconfdir}/init.d 
    install -m 0755 ${WORKDIR}/wpastartup-sv ${D}${sysconfdir}/init.d/
}
