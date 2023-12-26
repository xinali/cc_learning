#!/bin/bash

# regn
../tools/linux_arm64/gn gen out
gn_result=$?
if [ $gn_result -ne 0 ]; then
    echo "gn build failed with error $gn_result"
    exit 1
fi

# reninja
../tools/linux_arm64/ninja -C out
ninja_result=$?
echo "ninja result: $ninja_result"

# continue or not
if [ $ninja_result -ne 0 ]; then
    echo "ninja build faild with error $ninja_result"
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