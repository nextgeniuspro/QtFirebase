
# Firebase cpp
export FIREBASE_VER=5.4.3
# Firebase iOS 
export FIREBASE_IOS_MAJOR=5
export FIREBASE_IOS_MINOR=15
export FIREBASE_IOS_PATCH=0

if command -v wget >/dev/null 2>&1; then
    echo "Downloading firebase_cpp_sdk_$FIREBASE_VER..."
    wget -c https://dl.google.com/firebase/sdk/cpp/firebase_cpp_sdk_$FIREBASE_VER.zip || exit 1
    echo "Downloading firebase iOS ${FIREBASE_IOS_MAJOR}.${FIREBASE_IOS_MINOR}.${FIREBASE_IOS_PATCH}..."
    wget -c https://dl.google.com/firebase/sdk/ios/${FIREBASE_IOS_MAJOR}_${FIREBASE_IOS_MINOR}_${FIREBASE_IOS_PATCH}/Firebase-${FIREBASE_IOS_MAJOR}.${FIREBASE_IOS_MINOR}.${FIREBASE_IOS_PATCH}.zip || exit 1
elif command -v curl >/dev/null 2>&1; then
    echo "Downloading firebase_cpp_sdk_$FIREBASE_VER..."
    curl -C - -O https://dl.google.com/firebase/sdk/cpp/firebase_cpp_sdk_$FIREBASE_VER.zip || exit 1
    echo "Downloading firebase iOS ${FIREBASE_IOS_MAJOR}.${FIREBASE_IOS_MINOR}.${FIREBASE_IOS_PATCH}..."
    curl -C - -O https://dl.google.com/firebase/sdk/ios/${FIREBASE_IOS_MAJOR}_${FIREBASE_IOS_MINOR}_${FIREBASE_IOS_PATCH}/Firebase-${FIREBASE_IOS_MAJOR}.${FIREBASE_IOS_MINOR}.${FIREBASE_IOS_PATCH}.zip || exit 1
else
    echo >&2 "You must have either wget or cURL installed to use this script!"
    exit 1
fi

echo "Unpacking firebase_cpp_sdk_$FIREBASE_VER..."
unzip -q firebase_cpp_sdk_$FIREBASE_VER.zip
echo "Unpacking firebase iOS ${FIREBASE_IOS_MAJOR}.${FIREBASE_IOS_MINOR}.${FIREBASE_IOS_PATCH}..."
unzip -q Firebase-${FIREBASE_IOS_MAJOR}.${FIREBASE_IOS_MINOR}.${FIREBASE_IOS_PATCH}

echo "Deleting archives..."
rm ./*.zip