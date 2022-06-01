# rpi-media-streaming
Enables the Raspberry Pi to stream audio over the local network.

UPnP is used for devices discovery, netJack2 for low latency streaming.

Disabling IPv6 did the trick for me that the systemd target network online reaches only after IPv4 address is obtained.
