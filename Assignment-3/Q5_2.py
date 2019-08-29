# Kaustav Vats
# Only valid for ipv4 for ipv6 add {IPv6:%IPv6.src%} with ipv4.

from scapy.all import PcapReader, TCP

for packet in PcapReader("fb.pcap"):
    # print("hey")
    if (TCP in packet) and (packet[TCP].flags & 2):
        sourceIP = packet.sprintf('{IP:%IP.src%}')
        print(sourceIP)