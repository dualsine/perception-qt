QMAKE_CXX = ccache $$CHROME_SRC_PATH/third_party/llvm-build/Release+Asserts/bin/clang++
QMAKE_CXXFLAGS =  -std=c++14 \
                -fno-exceptions \
                -fno-rtti \
                -nostdinc++ \
                -isystem$$CHROME_SRC_PATH/buildtools/third_party/libc++/trunk/include \
                -isystem$$CHROME_SRC_PATH/buildtools/third_party/libc++abi/trunk/include
