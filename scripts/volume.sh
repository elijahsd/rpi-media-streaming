evtest /dev/input/event2 | while read line; do
if [ -n "$(echo $line | grep VOLUMEUP)" ]; then
/root/volume_up.sh
fi
if [ -n "$(echo $line | grep VOLUMEDOWN)" ]; then
/root/volume_down.sh
fi
done
