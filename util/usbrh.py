#!/usr/bin/python

import hid

USBRH_VENDOR = 0x1774
USBRH_PRODUCT = 0x1001

d1 = -40.0
d2 = 0.01
c1 = -4
c2 = 0.0405
c3 = -2.8e-6
t1 = 0.01
t2 = 0.00008

def calc_temp(so_t):
    return d1 + d2 * so_t

def calc_hum(so_rh, t_c):
    rh_linear = c1 + c2 * so_rh + c3 * so_rh * so_rh
    return (t_c - 25) * (t1 + t2 * so_rh) + rh_linear

def usbrh_get_rawdata():
    h = hid.device()
    h.open(USBRH_VENDOR, USBRH_PRODUCT)
    try:
        data = [0]*7
        h.write(data)
        out = h.read(7, timeout_ms=50000)
    except:
        raise
    finally:
        h.close()

    return out

def usbrh_trans_rawdata(out):
    so_rh = ((out[0] & 0xff) << 8) + (out[1] & 0xff)
    so_t = ((out[2] & 0xff) << 8) + (out[3] & 0xff)

    tc = calc_temp(so_t)
    rh = calc_hum(so_rh, tc)

    return (tc, rh)

if __name__ == '__main__':
    raw_data = usbrh_get_rawdata()
    actual_data = usbrh_trans_rawdata(raw_data)
    print('%.2f %.2f' % actual_data)
