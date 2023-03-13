#!/bin/bash

echo -e "1. Environment value config\c"
type arm-none-eabi-gcc > /dev/null 2>&1 
if [ $? != 0 ]
then
    echo -e ": arm-none-eabi-gcc not found!!!"
    exit -1
else
    echo -e ""
fi

echo -e "2. Build compile-commands.json\c"
make clean > /dev/null 2>&1
bear -- make > /dev/null 2>&1
if [ $? != 0 ]
then
    echo -e ": Build error!!!, please install bear or make"
    exit -1
else
    echo -e ""
fi

echo -e "3. Fix Cross Compile Inc Problem\c"
compiler=`head -n 10 ./compile_commands.json | grep -Pzo "\"arguments\".*\n\s*\".*\n" | grep -av "arguments" | head -1 | awk -F\" '{print $2}'`
if [ "$compiler" = "" ];
then
    echo ": compile_commands.json invalid"
    exit -1;
else
    echo -e ""
fi

if [ "`echo $compiler | grep ++`" = "" ]; then
    out="--driver-mode=gcc, "`$compiler -xc /dev/null -E -Wp,-v 2>&1 | sed -n 's,^ ,,p'|awk '{print "-isystem, "$0","}'`
else
    out="--driver-mode=g++, "`$compiler -xc++ /dev/null -E -Wp,-v 2>&1 | sed -n 's,^ ,,p'|awk '{print "-isystem, "$0","}'`
fi
$compiler -xc /dev/null -E -Wp,-v > /dev/null 2>&1

echo -e "CompileFlags:\n\tAdd: ["${out/%,}"]" > .clangd

echo -e "4. All done"

