#! /bin/bash

# $1 = rep folder $2= revision

JAVA_HOME="/usr/java/jre1.6.0_13"
PATH="$JAVA_HOME/bin:$PATH"
APPPATH="/svn/svnstats/"
GENERATEDFOLDER="${APPPATH}generated/"
CACHEFOLDER="${APPPATH}cache/"
WORKFOLDER="${APPPATH}work/"
REPOSFOLDER="/svn/repos/"
SVUSER="statsreader"
SVPW="***"

[ ! -d "$CACHEFOLDER" ] && mkdir "$CACHEFOLDER"
[ ! -d "$WORKFOLDER" ] && mkdir "$WORKFOLDER"
[ ! -d "$GENERATEDFOLDER" ] && mkdir "$GENERATEDFOLDER"

pushd "$WORKFOLDER" > /tmp/ll 2>&1

REPNAME=`basename $1`
CACHENAME="${CACHEFOLDER}${REPNAME}"

echo "$n latest: $2" >> /tmp/ll 2>&1

echo "Going to generate report for... $REPNAME" >> /tmp/ll 2>&1
svn co --non-interactive "https://svnserver/repos/${REPNAME}" $REPNAME --no-auth-cache --username "$SVUSER" --password "$SVPW" >> /tmp/ll 2>&1
svn log --xml -v $REPNAME > ${REPNAME}.log
java -jar "${APPPATH}bin/statsvn.jar" -output-dir "${GENERATEDFOLDER}${REPNAME}" ${REPNAME}.log "${REPNAME}" >> /tmp/ll 2>&1
echo "$2" > "$CACHENAME"
rm -rf "${REPNAME}"
rm -f  "${REPNAME}.log"

popd >> /tmp/ll 2>&1


