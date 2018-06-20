#include <stdlib.h>
#include <endian.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <hidapi.h>

#define USBRH_VENDOR  0x1774
#define USBRH_PRODUCT 0x1001

/* Parameters by http://www.farnell.com/datasheets/317085.pdf */
#define d1 (-40.00)
#define d2 (0.01)
#define c1 (-4)
#define c2 (0.0405)
#define c3 (-2.8e-6)
#define t1 (0.01)
#define t2 (0.00008)

static inline double calc_temp(const uint16_t t_raw) {
  return d1 + d2 * t_raw;
}

static inline double calc_hum(const uint16_t so_rh, const double t_c) {
  const double rh_linear = c1 + c2 * so_rh + c3 * (so_rh * so_rh);
  return (t_c - 25) * (t1 + t2 * so_rh) + rh_linear;
}

void usbrh_print_data(hid_device* const handle) {
  union {
    unsigned char byte[8];
    uint16_t be16[4];
  } buf;
  static_assert(sizeof(buf.byte) == sizeof(buf.be16), "mismatch union size");
  
  memset(buf.byte, 0, sizeof(buf.byte));

  int res = hid_write(handle, buf.byte, 7);
  if (res < 0) {
    fprintf(stderr, "hid_write: failed\n");
    abort();
  }

  res = hid_read_timeout(handle, buf.byte, 7, 5000 /*ms*/);
  if (res == 0) { /* means timeout */
    fprintf(stderr, "hid_read: timeout\n");
    abort();
  }
  else if (res < 0) {
    fprintf(stderr, "hid_read: failed\n");
    abort();
  }

  // big endian to host endian
  const uint16_t hum_raw = be16toh(buf.be16[0]);
  const uint16_t temp_raw = be16toh(buf.be16[1]);

  const double temp = calc_temp(temp_raw);
  const double hum = calc_hum(hum_raw, temp);

  printf("%lf %lf\n", temp, hum);
}


int main(void) {
  int res = hid_init();
  if (res < 0) {
    fprintf(stderr, "hid_init: failed\n");
    abort();
  }

  hid_device* const handle = hid_open(USBRH_VENDOR, USBRH_PRODUCT, NULL);
  if (handle == NULL) {
    fprintf(stderr, "hid_open: failed\n");
    abort();
  }

  usbrh_print_data(handle);

  hid_close(handle);
  
  res = hid_exit();
  if (res < 0) {
    fprintf(stderr, "hid_exit: failed\n");
    abort();
  }

  return 0;
}
