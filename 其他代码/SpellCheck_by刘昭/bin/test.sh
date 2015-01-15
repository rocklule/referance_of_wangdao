#!/bin/bash
cd ../
echo $PWD
cd shellScripts
echo $PWD


function start 
{
	#./sleep.sh &
	cd /home/anboqing/spellCorrect/bin/
	./spellCorrect
}

function stop
{
	cd /home/anboqing/spellCorrect/bin/
	killall -9 spellCorrect
}

function stat
{
	ps -ef | grep spellCorrect
}

# like switch
case $1 in
	start) start ;;
	stop) stop ;;
	restart restart ;;
	stat) stat ;;

	*) echo "Igorn.." ;;
esac



echo `ps -ef | grep 'sleep.sh'`
#pid=`ps -ef | grep 'sleep.sh' | awk -F' ' '{print $2}'`
pid=$(pidof -x sleep.sh)
echo $pid

kill -9 $pid
echo $?


#tar -czvf shell.tar.gz shellScripts/
