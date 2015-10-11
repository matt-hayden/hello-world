#! /bin/bash

set -e

function help() {
	cat <<- EOF
This is help
EOF
	caller 0
	exit -1
}

function usage() {
	cat <<- EOF
This is usage
EOF
	caller 0
	exit -1
}

mode=1
while getopts ":hv0123456789 -:" OPT
do
	if [[ $OPT == '-' ]] # Long option
	then
		OPT=$OPTARG
		eval $OPT && continue || usage # you may or may not want the continue
	fi
	case $OPT in
		-) echo Long option: $OPT $OPTARG
		;;
		h|help) help
		;;
		v|verbose) echo Verbose
		;;
		[0-9]) mode=$OPT
		;;
		\?) usage # getopts replaces unknown with ?
		;;
	esac
done >&2
shift $((OPTIND-1))

echo mode: $mode
set
