#!/bin/sh
# Usage:
#	cat <<EOF >> .xinitrc
#	> exec dwm_loop.sh 2>~/.dwm.log
#	> EOF

while true; do
	[ -x /usr/bin/dbus-launch ] && LAUNCH="$LAUNCH /usr/bin/dbus-launch"
	$LAUNCH dwm
done

# End of file
