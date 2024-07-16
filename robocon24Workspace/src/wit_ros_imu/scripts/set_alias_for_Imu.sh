echo 'KERNEL=="ttyUSB*", ATTRS{devpath}=="2.2.3", MODE:="0777", SYMLINK+="ImuAlias"' >/etc/udev/rules.d/ImuAlias.rules

service udev reload
sleep 2
service udev restart