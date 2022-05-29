#!/opt/bin/python3

import subprocess
import socket
import time
import logging
import sys

# Edit
interval_time = 10          # Seconds
pihole_ip = "192.168.0.2"   # Local IP of pihole/adguard
pihole_port = 53            # DNS port, 53 by default

# Don't edit
FORMAT = '%(asctime)s - [%(message)s]'
logging.basicConfig(stream=sys.stderr, format=FORMAT)
logger = logging.getLogger()
#logger.setLevel("DEBUG")
last_state = -1


def errormsg(msg):
    print(msg)


def ping_pihole():
    logger.debug('Pinging server')
    time.sleep(interval_time)
    sockfd = socket.socket()
    sockfd.settimeout(5)
    sockfd.connect((pihole_ip, pihole_port))
    sockfd.close()


def dns_filter_on(last_state):
    if (last_state != 1):
        logger.debug('DNSFilter ON')
        subprocess.run(['nvram', 'set', 'dnsfilter_enable_x=1'])
    last_state = 1


def dns_filter_off(last_state):
    if (last_state != 0):
        logger.debug('DNSFilter OFF')
        subprocess.run(['nvram', 'set', 'dnsfilter_enable_x=0'])
    last_state = 0


if __name__ == '__main__':
    while (1):
        try:
            ping_pihole()
            dns_filter_on(last_state)

        except (ConnectionRefusedError, socket.timeout):
            dns_filter_off(last_state)

        except socket.gaierror:
            errormsg("Error. Bad IP")

        except KeyboardInterrupt:
            errormsg("Canceled by user")

        except subprocess.CalledProcessError:
            errormsg("Error. Can't ssh to router")

        except:
            pass
