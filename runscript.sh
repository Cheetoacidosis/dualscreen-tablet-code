trap killgroup SIGINT

killgroup(){
  echo killing...
  kill 0
}

loop(){
  echo $1
  sleep $1
  loop $1
}

FILE=/dev/input/event2
# Do nothing until the touchpanel is connected
while [ ! -e "$FILE" ]
do
    echo "Waiting for touchscreen device to connect..."
    sleep 0.25
done

#create the full refresh binary so it doesn't get mad at it for not existing
sudo touch /dev/shm/full_refresh.bin

sudo rm /dev/shm/display_data.bin
sudo ./user_interface_test/v19/build/v19 -platform offscreen -plugin EvdevTouch:/dev/input/event2 &
sudo python primary_eink.py && fg
wait
