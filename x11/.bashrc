#
# ~/.bashrc
#

# If not running interactively, don't do anything
[[ $- != *i* ]] && return


# git branch info if present
parse_git_branch() {
     git branch 2> /dev/null | sed -e '/^[^*]/d' -e 's/* \(.*\)/ (\1)/'
}

alias athlon='xfce4-terminal --hide-menubar --hide-scrollbar -e "ssh athlon"'
alias hypr='cd ~/.config/hypr/'
alias ls='ls -Ah --color=auto'
alias ll='ls -l'
alias grep='grep --color=auto'
alias spice='looking-glass-client -F -f /dev/kvmfr0'

#PS1='[\u@\h \W]\$ '
#PS1='\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]$ '

export PS1="\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]$\[\033[33m\]\$(parse_git_branch)\[\033[00m\] "
#PS1='\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\] $ \$(parse_git_branch)'
#export PS1="\[\033[36m\]\u@\h\[\033[00m\] \[\033[32m\]\w\[\033[33m\]\$(parse_git_branch)\[\033[00m\] \n\[\033[1;31m\]>>\[\033[00m\] "

export HISTFILESIZE=10000
export HISTSIZE=10000
