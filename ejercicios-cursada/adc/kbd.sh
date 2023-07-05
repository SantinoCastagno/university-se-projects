stty -F /dev/ttyACM0 speed 9600
cat /dev/ttyACM0 |
while read tecla; do
    echo $tecla
    echo '\n'
done
