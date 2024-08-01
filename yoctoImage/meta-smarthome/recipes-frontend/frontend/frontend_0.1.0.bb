# Recipe created by recipetool
# This is the basis of a recipe and may need further editing in order to be fully functional.
# (Feel free to remove these comments when editing.)

# Unable to find any files that looked like license statements. Check the accompanying
# documentation and source headers and set LICENSE and LIC_FILES_CHKSUM accordingly.
#
# NOTE: LICENSE is being set to "CLOSED" to allow you to at least start building - if
# this is not accurate with respect to the licensing of the software being built (it
# will not be in most cases) you must specify the correct value before using this
# recipe for anything other than initial testing/development!
LICENSE = "CLOSED"
LIC_FILES_CHKSUM = ""

SRC_URI = "file:///home/abdelaziz/SmartHome/mernAPP/webpage.tar"

# The tarball will be extracted here.
S = "${WORKDIR}/webpage"


# Inherit the npm class to handle Node.js and npm-related tasks.
# This sets up environment variables and other npm-specific configurations.
inherit npm

# License field specific to the package. Since the license is unknown, we use "Unknown."
LICENSE:${PN} = "Unknown"

# The do_configure task is not executed for this recipe. 
# This is because the npm class doesn't require a separate configure step.
do_configure[noexec] = "1"

do_compile(){
	# Install Node.js dependencies listed in package.json
    npm install
    # Build the project based on the build script defined in package.json
    npm run build
}

do_install(){
    install -d ${D}/var/www/react-app
    cp -r ${S}/build/* ${D}/var/www/react-app/
}
