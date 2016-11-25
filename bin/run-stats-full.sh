#! /bin/bash

JAVA_HOME="/usr/java/jdk1.6.0_11"
PATH="$JAVA_HOME/bin:$PATH"
APPPATH="/data/applications/statsvn/"
GENERATEDFOLDER="${APPPATH}generated/"
CACHEFOLDER="${APPPATH}cache/"
WORKFOLDER="${APPPATH}work/"
REPOSFOLDER="/data/svn/repos/svn/"
SVUSER="statsreader"
SVPW="***"

export LANG="en_US.UTF-8"

[ ! -d "$CACHEFOLDER" ] && mkdir "$CACHEFOLDER"
[ ! -d "$WORKFOLDER" ] && mkdir "$WORKFOLDER"
[ ! -d "$GENERATEDFOLDER" ] && mkdir "$GENERATEDFOLDER"

pushd "$WORKFOLDER" > /tmp/ll 2>&1

for n in ${REPOSFOLDER}*; do
	REPNAME=`basename $n`
	LATESTVER=`svnlook youngest $n`
	#CACHENAME="${CACHEFOLDER}${REPNAME}"
	CACHENAME="${GENERATEDFOLDER}${REPNAME}/index.html"
	if [ -f "${CACHENAME}" ]; then
		CACHEVER=`grep -A 1 "Head revision" ${CACHENAME} | tail -n 1 | cut -f 2 -d '>' | cut -f 1 -d '<'`
	else
		CACHEVER="-1"
	fi

	echo "$n latest: $LATESTVER cached: $CACHEVER" >> /tmp/ll 2>&1

	if [ $LATESTVER -gt 0 -a $LATESTVER -ne $CACHEVER ]; then
		echo "Going to generate report for... $REPNAME" >> /tmp/ll 2>&1
		svn co --non-interactive "https://svnserver/svn/${REPNAME}" $REPNAME --no-auth-cache --username "$SVUSER" --password "$SVPW" --config-dir /var/www/.subversion >> /tmp/ll 2>&1
		svn log --xml -v $REPNAME --no-auth-cache --username "$SVUSER" --password "$SVPW" --config-dir /var/www/.subversion > ${REPNAME}.log
		java -Xmx128m -jar "${APPPATH}bin/statsvn.jar" -output-dir "${GENERATEDFOLDER}${REPNAME}" ${REPNAME}.log "${REPNAME}" >> /tmp/ll 2>&1
		rm -rf "$REPNAME"
	fi
done

popd
