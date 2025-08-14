import crc
import codec

hdlc_spec = crc.make_spec \
    (32, 0x04C11DB7, 0xFFFFFFFF, True, True, 0xFFFFFFFF)
xmodem_spec = crc.make_spec(16, 0x1021, 0, False, False, 0)

hdlc_session = crc.start(hdlc_spec)
xmodem_session = crc.start(xmodem_spec)

zero_c = codec.decode_u8('0')
for i in 1..10:
    c = codec.encode_u8(zero_c + i)
    print('Adding %r' % (c,))
    crc.add(hdlc_spec, hdlc_session, c)
    crc.add(xmodem_spec, xmodem_session, c)

print('CRC-32/ISO-HDLC: %8X' % (crc.finish(hdlc_spec, hdlc_session),))
print('XMODEM: %4X' % (crc.finish(xmodem_spec, xmodem_session),))
