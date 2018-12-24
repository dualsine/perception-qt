#!/usr/bin/env bash

source configs/variables
source bash_helpers.sh

trap exit_trap EXIT
set -e

sed -i s/-Werror//g $CHROME_SRC_PATH/out/Release_GN_x64/obj/printing/printing.ninja; check
sed -i s/-Werror//g $CHROME_SRC_PATH/out/Release_GN_x64/obj/third_party/libdrm/libdrm.ninja; check

ninja -C $CHROME_SRC_PATH/out/Release_GN_x64 cef chrome_sandbox; check

#copy cef wrapper
rm -rf $CHROME_SRC_PATH/out/Release_GN_x64/libcef; check
rm -rf $CHROME_SRC_PATH/out/Release_GN_x64/libcef_pack; check
rm -rf $CHROME_SRC_PATH/out/Release_GN_x64/perception; check

mkdir -p $CHROME_SRC_PATH/out/Release_GN_x64/libcef; check
mkdir -p $CHROME_SRC_PATH/out/Release_GN_x64/libcef/include/cef; check
mkdir -p $CHROME_SRC_PATH/out/Release_GN_x64/libcef/libcef_dll_wrapper; check
mkdir -p $CHROME_SRC_PATH/out/Release_GN_x64/libcef/Release; check
mkdir -p $CHROME_SRC_PATH/out/Release_GN_x64/libcef/Resources; check
mkdir -p $CHROME_SRC_PATH/out/Release_GN_x64/libcef/Resources/locales; check

cp -rpf $CHROME_SRC_PATH/cef/include \
		$CHROME_SRC_PATH/out/Release_GN_x64/libcef/include/cef/.; check

cp -rpf $CHROME_SRC_PATH/out/Release_GN_x64/chrome_sandbox \
		$CHROME_SRC_PATH/out/Release_GN_x64/libcef/Release/chrome-sandbox; check
sudo chown root:root $CHROME_SRC_PATH/out/Release_GN_x64/libcef/Release/chrome-sandbox; check
sudo chmod 4755 $CHROME_SRC_PATH/out/Release_GN_x64/libcef/Release/chrome-sandbox; check
cp -rpf $CHROME_SRC_PATH/out/Release_GN_x64/libcef.so $CHROME_SRC_PATH/out/Release_GN_x64/libcef/Release/.; check
cp -rpf $CHROME_SRC_PATH/out/Release_GN_x64/libEGL.so $CHROME_SRC_PATH/out/Release_GN_x64/libcef/Release/.; check
cp -rpf $CHROME_SRC_PATH/out/Release_GN_x64/libGLESv2.so $CHROME_SRC_PATH/out/Release_GN_x64/libcef/Release/.; check
cp -rpf $CHROME_SRC_PATH/out/Release_GN_x64/natives_blob.bin $CHROME_SRC_PATH/out/Release_GN_x64/libcef/Release/.; check
cp -rpf $CHROME_SRC_PATH/out/Release_GN_x64/snapshot_blob.bin $CHROME_SRC_PATH/out/Release_GN_x64/libcef/Release/.; check
cp -rpf $CHROME_SRC_PATH/out/Release_GN_x64/v8_context_snapshot.bin $CHROME_SRC_PATH/out/Release_GN_x64/libcef/Release/.; check
cp -rpf $CHROME_SRC_PATH/out/Release_GN_x64/swiftshader $CHROME_SRC_PATH/out/Release_GN_x64/libcef/Release/.; check

ln -s $CHROME_SRC_PATH/out/Release_GN_x64/libcef/Release $CHROME_SRC_PATH/out/Release_GN_x64/libcef/Debug; check

cp -rpf $CHROME_SRC_PATH/out/Release_GN_x64/cef_100_percent.pak $CHROME_SRC_PATH/out/Release_GN_x64/libcef/Resources/.; check
cp -rpf $CHROME_SRC_PATH/out/Release_GN_x64/cef_200_percent.pak $CHROME_SRC_PATH/out/Release_GN_x64/libcef/Resources/.; check
cp -rpf $CHROME_SRC_PATH/out/Release_GN_x64/cef_extensions.pak $CHROME_SRC_PATH/out/Release_GN_x64/libcef/Resources/.; check
cp -rpf $CHROME_SRC_PATH/out/Release_GN_x64/cef.pak $CHROME_SRC_PATH/out/Release_GN_x64/libcef/Resources/.; check
cp -rpf $CHROME_SRC_PATH/out/Release_GN_x64/devtools_resources.pak $CHROME_SRC_PATH/out/Release_GN_x64/libcef/Resources/.; check
cp -rpf $CHROME_SRC_PATH/out/Release_GN_x64/icudtl.dat $CHROME_SRC_PATH/out/Release_GN_x64/libcef/Resources/.; check
cp -rpf $CHROME_SRC_PATH/out/Release_GN_x64/locales $CHROME_SRC_PATH/out/Release_GN_x64/libcef/Resources/.; check

cd $CHROME_SRC_PATH/cef/tools/; check
./make_distrib.sh --allow-partial --no-docs --x64-build --no-symbols --ninja-build --output-dir=../../out/Release_GN_x64 --no-archive --distrib-subdir=libcef_pack
check
cd $CHROME_SRC_PATH/out/Release_GN_x64/libcef_pack; check
cmake .; check
sed -i s/-Werror//g libcef_dll_wrapper/CMakeFiles/libcef_dll_wrapper.dir/flags.make; check
make libcef_dll_wrapper -j8; check
cp -rpf libcef_dll_wrapper/libcef_dll_wrapper.a ../libcef/libcef_dll_wrapper/.; check  
