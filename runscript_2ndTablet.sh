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

#create the full refresh binary so it doesn't get mad at it for not existing
sudo touch /dev/shm/full_refresh2.bin

sudo rm /dev/shm/display_data2.bin
sudo ./user_interface_test/v19/build/v19 -platform offscreen -plugin EvdevTouch:/dev/input/event3 --tablet-two &
sudo python secondary_eink.py && fg
wait

