SUMMARY = "startup service to handle daemon apps "
DESCRIPTION = "${SUMMARY}"
LICENSE = "CLOSED"

SRC_URI = "file://configstartup-sv"

S = "${WORKDIR}"

inherit update-rc.d

INITSCRIPT_NAME = "configstartup-sv"
INITSCRIPT_PARAMS = "start 12 1 2 3 4 5 . stop 12 1 6 ."

do_install(){
    install -d ${D}${sysconfdir}/init.d 
    install -m 0755 ${WORKDIR}/configstartup-sv ${D}${sysconfdir}/init.d/
}
