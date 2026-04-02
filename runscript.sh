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



sudo rm /dev/shm/display_data.bin
sudo ./user_interface_test/v19/build/v19 -platform offscreen -plugin EvdevTouch:/dev/input/event2 &
sudo python user_interface_test/v4.py && fg
wait