#!/bin/bash

/usr/local/bin/jackd -d netone &
sleep 1
/usr/local/bin/alsa_in -c2 &

/usr/bin/volume &

/usr/local/bin/upnpserver &

/root/jackc &

