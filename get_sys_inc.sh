#!/bin/bash

compiler=`head -n 10 ./compile_commands.json | grep -Pzo "\"arguments\".*\n\s*\".*\n"|grep -av "arguments"|head -1|awk -F\" '{print $2}'`
echo ${compiler}

if [ "$compiler" = "" ];then
	echo "compile_commands.json文件中没有找到有效的编译器参数"
	return
fi

if [ "`echo $compiler|grep ++`" = "" ]; then
	out="--driver-mode=gcc, "`$compiler -xc /dev/null -E -Wp,-v 2>&1 | sed -n 's,^ ,,p'|awk '{print "-isystem, "$0","}'`
else
	out="--driver-mode=g++, "`$compiler -xc++ /dev/null -E -Wp,-v 2>&1 | sed -n 's,^ ,,p'|awk '{print "-isystem, "$0","}'`
fi
echo ${out}
$compiler -xc /dev/null -E -Wp,-v 

echo -e "CompileFlags:\n\tAdd: ["${out/%,}"]" > .clangd
