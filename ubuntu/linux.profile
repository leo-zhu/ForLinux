#### Allow unlimited size for coredump
ulimit -c unlimited

## chop file from byte to byte (starting with byte 0)
chop()
{
    if [ $# -eq 3 ]; then
        { head -c$2 > /dev/null ; head -c$3 2>&1; } < $1
    else
        echo "Usage: $FUNCNAME <inputFile> <startByte> <size>"
    fi  
}

## use beyond-compare
use_bcompare()
{
    if [ $# -eq 2 ]; then
        if [ -e $1 -a -e $2 ]; then
            bcompare $1 $2 &
        fi
    elif [ $# -eq 3 ]; then
        if [ -e $1/$3 -a -e $2/$3 ]; then
            bcompare $1/$3 $2/$3 &
        fi
    else
        echo "Usage: $FUNCNAME <file1> <file2>"
        echo "       $FUNCNAME <path1> <path2> <file>"
    fi
}
alias b='use_bcompare $@'


## Display file content from ~/myHowTo/howTo...
howto()
{
    if [ $# -eq 0 ]; then
        find ~/myHowTo -iname "howTo*" -printf "%f\n" | sed "s/howTo/howTo\ /g"
    fi

    if [ $# -eq 1 ]; then
##        find ~/myHowTo -iname "howTo*${1}*" -type f -exec sh -c "echo ; echo {} ; cat {}" \;
        fileNames=`find ~/myHowTo -iname "howTo*${1}*" -type f`
        for fileName in $fileNames; do
            echo "$fileName"
            fileType=`file -b $fileName`
            if [[ $fileType =~ "ASCII text" ]]; then echo; cat $fileName; fi
            if [[ $fileType =~ "PDF" ]]; then firefox $fileName; fi
        done
    fi
}
alias ht='howto'


## start vim then run :find within vim, works when vim has the following setting
## set path=.,,**
vimfind()
{
    if [ $# -eq 1 ]; then
        vim -c "find $1"
    else
        vim -p
    fi
}


## upper case convertion
upper()
{
    echo ${1} | tr '[:lower:]' '[:upper:]'
}

## lower case convertion
lower()
{
    echo ${1} | tr '[:upper:]' '[:lower:]'
}

## find latest n files
find_last() 
{ 
    if [ $# -ne 2 ]; then
        echo "Usage:  ${0} <path> <number of latest files>"
    else
        find "${1:-.}" -type f -printf '%TY-%Tm-%Td %TH:%TM:%.2TS %P\n' 2>/dev/null | sort | tail -n "${2:-10}";                                                                                                                                             
    fi  
}

## sudo with assword inserted
mysudo()
{
    cmd=`echo expect -c \'spawn sudo $@ \; expect assword: \; send \"Mon_day123!@#\\\n\" \; interact\'`
#    echo $cmd
    eval $cmd
#    sleep 2
}


#### Alias
## system commands
alias src='source ~/.bashrc >& /dev/null'
alias hg='history | grep'
alias lt='ls --time-style="+%Y-%m-%d %H:%M:%S"'
alias treet='tree -D --timefmt "%Y-%m-%d %T"'

alias ff='find -type f -regex ".*/.*\.\(c\|cc\|cpp\|h\|hh\|hpp\|py\|json\)$" | xargs grep -H -n -i'
alias fcc='find -type f -regex ".*/.*\.\(c\|cc\|cpp\\)$" | xargs grep -H -n -i'
alias fhh='find -type f -regex ".*/.*\.\(h\|hh\|hpp\)$" | xargs grep -H -n -i'
alias cache1='echo 1 > abc123abc; sudo sync; sudo cp abc123abc /proc/sys/vm/drop_caches; rm -f abc123abc'
alias cache2='echo 2 > abc123abc; sudo sync; sudo cp abc123abc /proc/sys/vm/drop_caches; rm -f abc123abc'
alias cache3='echo 3 > abc123abc; sudo sync; sudo cp abc123abc /proc/sys/vm/drop_caches; rm -f abc123abc'

## handy scripts
alias vf="vimfind"
alias datefile="datefile.sh"
alias dg="dstatgraph.sh"
alias del="mydel.sh"
alias sys="myDstat --my -C0,1,2,3"
alias convertUrl="echo \"$@\" | sed -e's/%\([0-9A-F][0-9A-F]\)/\\\\\x\1/g' | xargs echo -e"
alias datetime="date +%Y%m%d_%H%M%S"

alias ..="cd .."
alias 2..="cd ../.."
alias 3..="cd ../../.."
alias 4..="cd ../../../.."
alias 5..="cd ../../../../.."

## installed tools
#alias tree='/usr/bin/tree -C'
alias kg='kcachegrind $1 > /dev/null 2>&1 &'
alias nb='~/Tools/netbeans/bin/netbeans --fontsize 14 -J-Xverify:none -J-Xmx2048m -J-XX:NewSize=512m -J-XX:MaxNewSize=512m'
alias pycharm='~/Tools/pycharm-community-2016.2.3/bin/pycharm.sh'
#alias qt='~/Tools/qtcreator-4.2.1/bin/qtcreator.sh'
alias youtube-download='youtube-dl'
alias youtube-audio='youtube-dl -x --audio-format mp3 --audio-quality 5'

## path and prompt
NOCOLOR="\[\033[0m\]"
BLUE="\[\033[0;34m\]"
LIGHTYELLOW="\[\033[;33m\]"
YELLOW="\[\033[1;33m\]"
PSCOLOR=${LIGHTYELLOW}
PS1='[$(pwd | sed "s@^/home/szhu/\?@~\/@")]\$ '
#PS1='[$(pwd)]\$ '
PS1=${PSCOLOR}${PS1}${NOCOLOR}
LS_COLORS=$LS_COLORS:'di=1;34:'; export LS_COLORS

## Terminal window resize
#WMW=1271  # max window width
#WMH=1278  # max window height
#alias wl='wmctrl -r :ACTIVE: -b remove,maximized_horz && wmctrl -r :ACTIVE: -e 0,0,70,1271,1278    && wmctrl -r :ACTIVE: -b add,maximized_vert'
#alias wr='wmctrl -r :ACTIVE: -b remove,maximized_horz && wmctrl -r :ACTIVE: -e 0,1280,70,1271,1278 && wmctrl -r :ACTIVE: -b add,maximized_vert'
#alias wm='wmctrl -r :ACTIVE: -b remove,maximized_horz && wmctrl -r :ACTIVE: -e 0,640,70,1271,1278  && wmctrl -r :ACTIVE: -b add,maximized_vert'
#alias wf='wmctrl -r :ACTIVE: -b add,maximized_vert,maximized_horz'

## gdb customized
#
#alias gdb=/usr/local/bin/gdb
#alias gdb=/tools/bin/arm/gcc-arm-none-eabi-10.3-2021.10/bin/arm-none-eabi-gdb
#for i in {1..12}; do alias gdb$i="GLOG_logtostderr=true GLOG_v=$i gdb"; done

## glog customized
for i in {1..12}; do alias glog$i="GLOG_logtostderr=true GLOG_v=$i"; done

#alias p4o="p4 opened | sed 's/#.*//' | p4 -x - where | cut -d' ' -f3"
alias dockerclean='docker stop $(docker ps -aq) && docker rm $(docker ps -aq) && docker rmi $(docker images -q)'

## docker settings
FORMAT="\nID\t{{.ID}}\nIMAGE\t{{.Image}}\nCOMMAND\t{{.Command}}\nCREATED\t{{.RunningFor}}\nSTATUS\t{{.Status}}\nPORTS\t{{.Ports}}\nNAMES\t{{.Names}}\n"

