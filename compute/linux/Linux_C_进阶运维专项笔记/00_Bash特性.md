# 00_Bash特性

echo命令行

```shell
sky92@sky92:~$ echo ABC
ABC

sky92@sky92:~$ echo {good,bad}
good bad

sky92@sky92:~$ echo good{1..8}
good1 good2 good3 good4 good5 good6 good7 good8

sky92@sky92:~$ echo good{1..8..2}
good1 good3 good5 good7

sky92@sky92:~$ echo good{01..18..2}
good01 good03 good05 good07 good09 good11 good13 good15 good17
 
```

命令别名

```shell
sky92@sky92:~$ alias
alias alert='notify-send --urgency=low -i "$([ $? = 0 ] && echo terminal || echo error)" "$(history|tail -n1|sed -e '\''s/^\s*[0-9]\+\s*//;s/[;&|]\s*alert$//'\'')"'
alias egrep='egrep --color=auto'
alias fgrep='fgrep --color=auto'
alias grep='grep --color=auto'
alias l='ls -CF'
alias la='ls -A'
alias ll='ls -alF'
alias ls='ls --color=auto'

sky92@sky92:~$ alias rm='rm -i'

sky92@sky92:~$ alias
alias alert='notify-send --urgency=low -i "$([ $? = 0 ] && echo terminal || echo error)" "$(history|tail -n1|sed -e '\''s/^\s*[0-9]\+\s*//;s/[;&|]\s*alert$//'\'')"'
alias egrep='egrep --color=auto'
alias fgrep='fgrep --color=auto'
alias grep='grep --color=auto'
alias l='ls -CF'
alias la='ls -A'
alias ll='ls -alF'
alias ls='ls --color=auto'
alias rm='rm -i'


sky92@sky92:~$ unalias rm
sky92@sky92:~$ alias rm='echo 该服务禁用rm'
sky92@sky92:~$ alias reboot='echo 该服务禁止重启'
sky92@sky92:~$ alias halt='echo 该服务静止关机'
sky92@sky92:~$ alias shutdown='echo 该服务静止关机'
```

历史

```shell
sky92@sky92:~$ history
sky92@sky92:~$ !  #上一次的命令
sky92@sky92:~$ !! #再上一次的命令
```

快捷键

```
CTRL+A	到行首
CTRL+E	到行尾
CTRL+K	光标后删除
CTRL+U	光标前删除
CTRL+L	清屏
```

命令补全 

```shell
#tab补全查找的是PATH路径下的内容

sky92@sky92:~$ echo $PATH
/home/sky92/bin:/home/sky92/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin

sky92@sky92:~$ py
py3clean            pygettext2.7        python3
py3compile          pygettext3          python3.5
py3versions         pygettext3.5        python3.5-config
pybuild             pygmentize          python3.5m
pyclean             pylupdate5          python3.5m-config
pycompile           pyrcc5              python3-config
pydoc               python              python3m
pydoc2.7            python2             python3m-config
pydoc3              python2.7           pyuic5
pydoc3.5            python2-jsonschema  pyversions
pygettext           python2-pbr

sky92@sky92:~$ which python3
/usr/bin/python3
 

```





















