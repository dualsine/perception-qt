#!/usr/bin/env bash
source configs/variables
source bash_helpers.sh

apply_patch_template() {
	# AVAILABLE VARIABLES in .template files:
	# PERCEPTION_SRC_PATH translates to $PERCEPTION_SRC_PATH
	dir=$(dirname "/tmp/tmp_patches_perception$1")
	mkdir -p $dir; check
	rm -rf /tmp/tmp_patches_perception$1
	cp -p $1 /tmp/tmp_patches_perception$1; check
	path_escaped=$(echo $PERCEPTION_SRC_PATH | sed 's_/_\\/_g');check
	sed -i s/PERCEPTION_SRC_PATH/$path_escaped/g "/tmp/tmp_patches_perception$1";check
	git am --signoff < /tmp/tmp_patches_perception$1; check
}

trap exit_trap EXIT
set -e

cd $CHROME_SRC_PATH; check
# pre install chromium patches
git checkout 72.0.3599.0; check
git am --signoff < $PERCEPTION_SRC_PATH/patches/chrome/pre-cef-changes.patch; check

# cef patches
cd $CHROME_SRC_PATH/cef; check
git checkout 91a1286d52dd78f8a327803e7ab628077b50d406; check
git am --signoff < $PERCEPTION_SRC_PATH/patches/cef/remove-tracking-unnecessary-files-by-git.patch; check
git am --signoff < $PERCEPTION_SRC_PATH/patches/cef/added-inspector-class.patch; check
#git am --signoff < $PERCEPTION_SRC_PATH/patches/cef/added-signals-dependency-to-BUILD.gn.patch; check

# translate cef api
cd $CHROME_SRC_PATH/cef/tools/; check
./translator.sh; check

cd $CHROME_SRC_PATH/cef; check
GN_DEFINES=use_jumbo_build=false\ cc_wrapper="ccache"\ enable_nacl=true ./cef_create_projects.sh; check

# chromium patches
cd $CHROME_SRC_PATH; check
git add .; check
git commit -m 'cef patches applied'; check
git am --signoff < $PERCEPTION_SRC_PATH/patches/chrome/fix-libdrm-build-warnings.patch; check
git am --signoff < $PERCEPTION_SRC_PATH/patches/chrome/fix-CUPS-build-warnings.patch; check
apply_patch_template $PERCEPTION_SRC_PATH/patches/chrome/added-signals-lib.template
# git am --signoff < $PERCEPTION_SRC_PATH/patches/chrome/added-signals-lib.patch; check
