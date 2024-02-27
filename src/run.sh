#!/bin/bash

# Detect OS and Architecture
OS="$(uname)"
ARCH="$(uname -m)"

# Set tool paths based on OS and Architecture
if [ "$OS" = "Linux" ] && [ "$ARCH" = "aarch64" ]; then
    TOOL_PATH="../tools/linux_arm64"
elif [ "$OS" = "Darwin" ]; then
    TOOL_PATH="../tools/mac"
else
    echo "Unsupported OS/Architecture: $OS/$ARCH"
    exit 1
fi

# regn
$TOOL_PATH/gn gen out
gn_result=$?
if [ $gn_result -ne 0 ]; then
    echo "gn build failed with error $gn_result"
    exit 1
fi

# reninja
$TOOL_PATH/ninja -C out
ninja_result=$?
echo "ninja result: $ninja_result"

# continue or not
if [ $ninja_result -ne 0 ]; then
    echo "ninja build failed with error $ninja_result"
    exit 1
fi

# get test name
test_pattern=$1

# raw exec
command="out/cc_learning_test --gtest_filter=CCLearningTest.TestFactoryPattern"

# replace with new command
exec_command=$(echo $command | sed "s/TestFactoryPattern/$test_pattern/")

echo "exec: $exec_command"
$exec_command
