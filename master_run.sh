
sudo systemctl start touchpanel1.service
sudo systemctl start touchpanel2.service

sudo ./runscript.sh &
sleep 4
sudo ./runscript_2ndTablet.sh &
wait
