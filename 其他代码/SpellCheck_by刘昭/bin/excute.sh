#########################################################################
# File Name: excute.sh
# Author: Comst
# mail: 750145240@qq.com
# Created Time: Sun 04 May 2014 03:48:34 PM CST
#########################################################################
#!/bin/bash
function start
{
	./main 
}
function stop
{
	killall -9 main
}
function restart
{
	killall -9 main
	./main &
}
function stat
{
	ps -ef | grep main
}
case $1 in
start) start ;;
stop ) stop ;;
restart) restart ;;
stat) stat ;;
*) echo "Ignore.." ;;
esac

