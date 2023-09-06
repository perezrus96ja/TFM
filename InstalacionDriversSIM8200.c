sudo apt-get install p7zip-full
wget https://files.waveshare.com/upload/8/89/SIM8200_for_RPI.7z
7z x SIM8200_for_RPI.7z -r -o./SIM8200_for_RPI
sudo chmod 777 -R SIM8200_for_RPI
cd SIM8200_for_RPI/Goonline
make
sudo ./simcom-cm &
sudo apt-get install udhcpc
sudo udhcpc -i wwan0
sudo route add -net 0.0.0.0 wwan0
