#!/bin/sh
xprop |awk '
    /^WM_CLASS/{sub(/.* =/, "instance:"); sub(/,/, "\nclass:"); print}
    /^WM_NAME/{sub(/.* =/, "title:"); print}
    /^WM_WINDOW_ROLE/{sub(/.* =/, "role:"); print}'
