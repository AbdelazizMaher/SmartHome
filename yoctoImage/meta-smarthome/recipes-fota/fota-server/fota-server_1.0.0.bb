# Recipe created by recipetool
# This is the basis of a recipe and may need further editing in order to be fully functional.
# (Feel free to remove these comments when editing.)

SUMMARY = ""
# Unable to find any files that looked like license statements. Check the accompanying
# documentation and source headers and set LICENSE and LIC_FILES_CHKSUM accordingly.
#
# NOTE: LICENSE is being set to "CLOSED" to allow you to at least start building - if
# this is not accurate with respect to the licensing of the software being built (it
# will not be in most cases) you must specify the correct value before using this
# recipe for anything other than initial testing/development!
LICENSE = "CLOSED"
LIC_FILES_CHKSUM = ""

SRC_URI = " \
    file:///home/abdelaziz/SmartHome/mernAPP/Fota_server.tar \
    "

S = "${WORKDIR}/Fota_server"

inherit npm

# not needed if the package is in the image via IMAGE_INSTALL_append
RDEPENDS_${PN} += "nodejs"

# The do_configure task is not executed for this recipe. 
# This is because the npm class doesn't require a separate configure step.
do_configure[noexec] = "1"

# Install Node.js dependencies and build the project
do_compile() {
    npm install
}

do_install() {
    # Install the server script and dependencies
    install -d ${D}${bindir}/fota-server
    cp -r ${S}/* ${D}${bindir}/fota-server/
    
    # create a symbolic link to the main script for easier execution
    ln -sf ${bindir}/fota-server/server.js ${D}${bindir}/fota-server.js
}

LICENSE:${PN} = "Unknown"
