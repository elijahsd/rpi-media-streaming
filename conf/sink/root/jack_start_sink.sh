#!/bin/bash

/usr/local/bin/jackd -d alsa &
sleep 1
/usr/bin/upnpclient Bedroom &

