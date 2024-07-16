echo 'KERNEL=="video*", ATTRS{devpath}=="2.2.4", MODE:="0777", SYMLINK+="YahboomCamera"' >/etc/udev/rules.d/YahboomCamera.rules

service udev reload
sleep 2
service udev restart