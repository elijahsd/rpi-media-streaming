# rpi-media-streaming
Enables the Raspberry Pi to stream audio over the local network.
Source:
1. Daemon that listens for the input source and changes volume on the given channel.
2. Deamon that streams captured audio over RTP.
3. Deamon that provides UPnP information.

Sink:
1. SSDP discovery for the source.
2. Deamon that accepts RTP stream from the discovered device and plays it.

