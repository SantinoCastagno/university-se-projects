stty -F /dev/ttyACM0 speed 9600 # o 2400 la que necesiten
cat /dev/ttyACM0 | while read -n 1 tecla; do
    xdotool key $tecla
done
