echo 'KERNEL=="ttyUSB*",ATTRS{devpath}=="2.3", MODE:="0777", SYMLINK+="USBTTL"' >/etc/udev/rules.d/USBTTL.rules

service udev reload
sleep 2
service udev restart