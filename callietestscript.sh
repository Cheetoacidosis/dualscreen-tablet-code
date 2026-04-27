# Do nothing until the second tablet is connected
while  ! i2cdetect 1 -y 0x14 0x14 | grep "14" ;
do
    echo "Waiting for touchscreen device to connect..."
    sleep 0.25
done


