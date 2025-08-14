import crc

text = '123456789'

crc32_iso_hdlc_spec = crc.make_spec \
    (32, 0x04C11DB7, 0xFFFFFFFF, True, True, 0xFFFFFFFF)
xmodem_spec = crc.make_spec(16, 0x1021, 0, False, False, 0)

print('Computing CRCs for %r' % (text,))
print('CRC-32/ISO-HDLC: %8X' % (crc.calc(crc32_iso_hdlc_spec, text),))
print('XMODEM: %4X' % (crc.calc(xmodem_spec, text),))
