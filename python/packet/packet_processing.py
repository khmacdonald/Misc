#!/usr/local/bin/python3.7

import array
import datetime
import os
import struct
import sys
import time


def ip_checksum ( arr ) :
    ''' Computes IP checksum on bytes in arr '''
    if len(arr) & 1 : 
        res = sum(array.array("H",arr[:-1]))
        res += struct.unpack("B",arr[-1:])
    else :
        res = sum(array.array("H",arr))
    while res > 0xffff :
        res = (res>>16) + (res & 0xffff)
    
    res = (~res) & 0xffff
    if res==0 : 
        return True
    return False


class Protocol ( object ) :
    def __init__ ( self, start, length, id_str, proc=None ) :
        self.start  = start
        self.length = length 
        self.id_str = id_str
        self.proc   = proc
        

class Packet ( object ) :
    '''
    This class defines a packet container and the methods to process
    a packet.
    '''
    def __init__ ( self, number, sec, usec, plen, wlen, packet, network ) :
        ''' Set values of packet '''
        self.number     = number        # Packet number in processing
        self.sec        = sec           # Time in seconds
        self.usec       = usec          # Time in microseconds
        self.plen       = plen          # Captured packet length 
        self.wlen       = wlen          # Actual length
        self.trunc      = plen!=wlen    # Is the packet truncated
        self.packet     = packet        # Bytes of the packet
        self.network    = network       # The first protocol

        self.cloc       = 0             # The current byte in the pacekt
        self.stack      = []            # Empty protocol stack
        self.err_msg    = 'success'

    def __process_ip4 ( self ) :
        ''' Processes the IPv4 protocol header '''
        prot_len    = 20
        ipv4 = self.packet[self.cloc:self.cloc+prot_len]
        vihl = struct.unpack("!B",ipv4[:1])[0]
        ver     = (vihl>>4) & 0x0f
        hLen    = (vihl & 0x0f) * 4
        if hLen!=prot_len : 
            print(f"Expected a header length of {prot_len}, but have {hLen}")
            self.err_msg = f"Expected header length {prot_len} != {hLen}"
            return False
        if not ip_checksum(ipv4) :
            self.err_msg = "IPv4 header checksum failure"
            return False

        prot_id     = Protocol(self.cloc,prot_len,'ipv4')
        self.stack.append(prot_id)

    def __process_ethernet ( self ) :
        ''' Processes the ethernet header '''
        prot_len    = 14
        prot_id     = Protocol(self.cloc,prot_len,'eth')
        self.stack.append(prot_id)

        # Discover next protocol
        eth = self.packet[self.cloc:prot_len]
        nprot = struct.unpack(">H",eth[12:])[0] # Always big endian
        
        # Adjust current processing location 
        self.cloc += prot_len
        if 0x0800==nprot : 
            return self.__process_ip4()

    # -----------------------------------------------------------------------

    def print_packet_header ( self, hdate = False, fmt="%Y-%m-%d_%H:%M:%S" ) :
        ''' Print the meta data of the packet '''
        print(f"    Packet {self.number} Header :")
        if hdate : 
            hstr = time.strftime(fmt,time.localtime(self.sec))
            usec = float(self.usec)/1000000.0
            ustr = f"{usec:.6f}"
            print(f"Date       : {hstr}.{ustr[2:]}")
        else :
            print(f"Seconds     : {self.sec}")
            print(f"uSeconds    : {self.usec}")
        print(f"Length      : {self.plen}")
        print(f"Truncated   : {self.trunc}")
        if self.trunc :
            printf(f"    Actual length : {self.wlen}")

    def print_protocol_stack ( self ) :
        ''' Creates a string detailing the protocol stack '''
        stk = ''.join(['%s:' % p.id_str for p in self.stack])
        stack = stk[:-1]
        return stack

    def process ( self ) :
        ''' Process the protocol stack of a packet. '''
        if 1==self.network : 
            return self.__process_ethernet()

    # End Packet class


class PacketFile ( object ) :
    '''
    This class defines a packet file and the methods associated with
    processing packets inside the packet file.
    '''
    def __process_packet_file_header ( self ) :
        ''' 
        Wrapper function in case more than type of packet file.
        '''
        self.__process_packet_file_header_pcap()

    def __process_packet_file_header_pcap ( self ) :
        '''
        Reads and processes file header:
            uint32 magic number
            uint16 major version number
            uint16 minor version number
             int32 GMT to local correction
            uint32 accuracy of time stamps
            uint32 maximum length of captured packet
            uint32 data link type
        '''
        self.file_type = "pcap"
        file_header = self.fd.read(24)

        # The magic number determines the endiannes of the file 
        magic = struct.unpack("I",file_header[:4])[0]
        little  = 0xa1b2c3d4
        big     = 0xd4c3b2a1
        if little==magic:
            self.little_endian = True
            unpacked = struct.unpack("<HHiIII",file_header[4:])
        elif big==magic:
            self.little_endian = False
            unpacked = struct.unpack(">HHiIII",file_header[4:])
        else:
            print("Unknown endianness: 0x%x" % (magic))
            print("    Expected 0x%x or 0x%x" % (little,big))
            print("    Exiting....")
            sys.exit(1)

        # Save off the file header information  
        self.major,   self.minor,   self.thiszone = unpacked[:3]
        self.sigfigs, self.snaplen, self.network = unpacked[3:]

    def __init__ ( self, fname ) :
        ''' Initializes the packet file object '''
        try : 
            fd = open(fname,"rb")
        except Exception as e:
            print(e)

        self.file_name = fname
        self.fd = fd
        self.__process_packet_file_header()
        self.pkt_num = 0
        self.eof = False

    def __get_next_packet_pcap ( self ) :
        '''
        Gets the next packet from a PCAP file
        uint32      seconds
        uint32      microseconds
        uint32      captured length 
        uint32      actual length  on wire
        '''
        hdr = self.fd.read(16)
        if 0==len(hdr) :
            self.eof = True
            return None
        elif len(hdr)!=16 :
            print(f"Error: Packet header is 16 bytes, but read {len(hdr)}")
            self.eof = True
            return None
        if self.little_endian : 
            sec, usec, plen, wlen = struct.unpack("<IIII",hdr)
        else :
            sec, usec, plen, wlen = struct.unpack(">IIII",hdr)

        pkt = self.fd.read(plen)
        if len(pkt)!=plen :
            self.eof = True
            print(f"Error: Packet length is {plen} bytes, but read {len(pkt)}")
            return None
        self.pkt_num += 1
        packet = Packet(self.pkt_num,sec,usec,plen,wlen,pkt,self.network)
        return packet

    def __print_file_header_pcap ( self ) :
        ''' Prints packet file meta data '''
        print(f"    File header for {self.file_name}")
        print(f"major   = {self.major}")
        print(f"minor   = {self.minor}")
        print(f"zone    = {self.thiszone}")
        print(f"sfigs   = {self.sigfigs}")
        print(f"slen    = {self.snaplen}")
        print(f"network = {self.network}")

    # ---------------------------------------------------------

    def print_file_header ( self ) :
        ''' Prints file header information '''
        if 'pcap' == self.file_type : 
            self.__print_file_header_pcap()
        else :
            print(f"Invalid file type: {self.file_type}")

    def get_next_packet ( self ) :
        ''' 
        Reads the next packet in the packet file.
        This is a wrapper for the various types of packet files.
        '''
        packet = None
        if 'pcap' == self.file_type : 
            packet = self.__get_next_packet_pcap()

        return packet

    # End PacketFile class
        

def test_main ( ) :
    ''' Uses test data to test the class functions '''
    if 2!=len(sys.argv):
        print(f"Usage: {sys.argv[0]} <PCAP file>") 
        return False
    fname = sys.argv[1]

    print(" ")
    pfile = PacketFile(fname)   # Open packet file
    pfile.print_file_header()   # Print meta data
    print(" ")

    while not pfile.eof:
        packet = pfile.get_next_packet()    # Read next packet
        if packet :
            packet.process()                    # Process the protocol stack
            stack = packet.print_protocol_stack() 
            print(f"Packet {packet.number} protocol stack is '{stack}'")
        break
    print(f"There are {pfile.pkt_num} packets in file.")


if __name__=="__main__" :
    test_main()
