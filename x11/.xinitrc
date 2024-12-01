#!/bin/sh

userresources=$HOME/.Xresources
usermodmap=$HOME/.Xmodmap
sysresources=/etc/X11/xinit/.Xresources
sysmodmap=/etc/X11/xinit/.Xmodmap

# merge in defaults and keymaps

if [ -f $sysresources ]; then







    xrdb -merge $sysresources

fi

if [ -f $sysmodmap ]; then
    xmodmap $sysmodmap
fi

if [ -f "$userresources" ]; then







    xrdb -merge "$userresources"

fi

if [ -f "$usermodmap" ]; then
    xmodmap "$usermodmap"
fi

# start some nice programs

if [ -d /etc/X11/xinit/xinitrc.d ] ; then
 for f in /etc/X11/xinit/xinitrc.d/?*.sh ; do
  [ -x "$f" ] && . "$f"
 done
 unset f
fi

xrdb ~/.Xresources &
setxkbmap latam &
numlockx on &
dunst &
xset m 1 0; xset s off; xset s noexpose; xset s noblank; xset s 0 0; xset -dpms; xsetroot -solid "#000" &
#xsetroot -name "$(uname -r)" &

case "$1" in
    dwm)
        /home/lean/.dotfiles/scripts/status.sh &> /dev/null &
        exec /usr/local/bin/dwm ;;

    budgie)  
        export XDG_CURRENT_DESKTOP=Budgie:GNOME
        exec /usr/bin/budgie-desktop ;;
        #exec budgie-desktop ;;
    *)
        xsetroot -name "ERROR .XINITRC" &
        setxkbmap latam &
        exec /usr/local/bin/dwm ;;
esac 
# Statusbar loop
#while true; do
   ####xsetroot -name "$( date +"%T ||| %d-%m-%Y")"
   #xsetroot -name " $( date +"%T") ||| $(upower -i /org/freedesktop/UPower/devices/headset_dev_74_45_CE_F9_19_7E | grep 'model' | awk '{print $2}'): $(upower -i /org/freedesktop/UPower/devices/headset_dev_74_45_CE_F9_19_7E | grep 'percentage' | awk '{print $2}')  ||| : $(~/scripts/Volume.sh --get)% ||| $( date +"%d-%m-%Y") "
   #sleep 1m    # Update time every minute
#done &

#exec /home/lean/dwmDEV.sh
