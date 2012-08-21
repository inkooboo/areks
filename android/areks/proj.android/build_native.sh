#!/bin/bash

THIS_DIR=$PWD

# set params
#NDK_ROOT=$THIS_DIR/../../../../android/android-ndk-r8b
NDK_ROOT=~/android-ndk-r8b
#NDK_ROOT=~/android-ndk-r7-crystax-5.beta2
COCOS2DX_ROOT=$THIS_DIR/../../../cocos2dx
GAME_ROOT=$THIS_DIR/../../..
GAME_ANDROID_ROOT=$GAME_ROOT/android/areks/proj.android
RESOURCE_ROOT=$GAME_ROOT/resources

buildexternalsfromsource=

usage(){
cat << EOF
usage: $0 [options]

Build C/C++ native code using Android NDK

OPTIONS:
   -s	Build externals from source
   -h	this help
EOF
}

while getopts "s" OPTION; do
	case "$OPTION" in
		s)
			buildexternalsfromsource=1
			;;
		h)
			usage
			exit 0
			;;
	esac
done

# make sure assets is exist
if [ -d $GAME_ANDROID_ROOT/assets ]; then
    rm -rf $GAME_ANDROID_ROOT/assets
fi

mkdir $GAME_ANDROID_ROOT/assets

# copy resources
for file in $RESOURCE_ROOT/*
do
    if [ -d "$file" ]; then
        cp -rf "$file" $GAME_ANDROID_ROOT/assets
    fi

    if [ -f "$file" ]; then
        cp "$file" $GAME_ANDROID_ROOT/assets
    fi
done

rm -f $GAME_ANDROID_ROOT/assets/sound_fx/*.wav
rm -f $GAME_ANDROID_ROOT/assets/bg_sound/*.wav

# copy icons (if they exist)
file=$GAME_ANDROID_ROOT/assets/Icon-72.png
if [ -f "$file" ]; then
	cp $file $GAME_ANDROID_ROOT/res/drawable-hdpi/icon.png
fi
file=$GAME_ANDROID_ROOT/assets/Icon-48.png
if [ -f "$file" ]; then
	cp $file $GAME_ANDROID_ROOT/res/drawable-mdpi/icon.png
fi
file=$GAME_ANDROID_ROOT/assets/Icon-32.png
if [ -f "$file" ]; then
	cp $file $GAME_ANDROID_ROOT/res/drawable-ldpi/icon.png
fi


if [[ $buildexternalsfromsource ]]; then
    echo "Building external dependencies from source"
    $NDK_ROOT/ndk-build -C $GAME_ANDROID_ROOT \
        NDK_MODULE_PATH=${COCOS2DX_ROOT}:${COCOS2DX_ROOT}/cocos2dx/platform/third_party/android/source
else
    echo "Using prebuilt externals"
    $NDK_ROOT/ndk-build -C $GAME_ANDROID_ROOT \
        NDK_MODULE_PATH=${COCOS2DX_ROOT}:${COCOS2DX_ROOT}/cocos2dx/platform/third_party/android/prebuilt
fi



