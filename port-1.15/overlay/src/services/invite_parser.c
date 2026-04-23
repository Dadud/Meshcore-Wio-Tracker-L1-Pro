#include "meshcore/services/invite_parser.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

static int hex_value(char c) {
  if (c >= '0' && c <= '9') return c - '0';
  if (c >= 'a' && c <= 'f') return 10 + (c - 'a');
  if (c >= 'A' && c <= 'F') return 10 + (c - 'A');
  return -1;
}

static bool decode_hex_16(const char* hex, uint8_t out[MC_INVITE_SECRET_LEN]) {
  for (int i = 0; i < MC_INVITE_SECRET_LEN; ++i) {
    int hi = hex_value(hex[i * 2]);
    int lo = hex_value(hex[i * 2 + 1]);
    if (hi < 0 || lo < 0) return false;
    out[i] = (uint8_t)((hi << 4) | lo);
  }
  return true;
}

static void encode_hex_16(const uint8_t in[MC_INVITE_SECRET_LEN], char out[MC_INVITE_SECRET_LEN * 2 + 1]) {
  static const char* hex = "0123456789abcdef";
  for (int i = 0; i < MC_INVITE_SECRET_LEN; ++i) {
    out[i * 2] = hex[(in[i] >> 4) & 0xF];
    out[i * 2 + 1] = hex[in[i] & 0xF];
  }
  out[MC_INVITE_SECRET_LEN * 2] = '\0';
}

bool mc_invite_parse_channel_url(const char* text, mc_channel_invite_t* out) {
  const char* prefix = "meshcore://channel/add?";
  const char* name_key = "name=";
  const char* secret_key = "secret=";
  const char* name_pos;
  const char* secret_pos;
  const char* name_end;
  size_t name_len;

  if (!text || !out) return false;
  memset(out, 0, sizeof(*out));

  if (strncmp(text, prefix, strlen(prefix)) != 0) return false;
  name_pos = strstr(text, name_key);
  secret_pos = strstr(text, secret_key);
  if (!name_pos || !secret_pos) return false;

  name_pos += strlen(name_key);
  name_end = strchr(name_pos, '&');
  if (!name_end) name_end = secret_pos - 1;
  if (name_end < name_pos) return false;

  name_len = (size_t)(name_end - name_pos);
  if (name_len == 0 || name_len >= sizeof(out->name)) return false;
  memcpy(out->name, name_pos, name_len);
  out->name[name_len] = '\0';

  secret_pos += strlen(secret_key);
  if (strlen(secret_pos) < MC_INVITE_SECRET_LEN * 2) return false;
  if (!decode_hex_16(secret_pos, out->secret)) return false;

  out->valid = true;
  return true;
}

bool mc_invite_format_channel_url(const mc_channel_invite_t* invite, char* out, int out_len) {
  char secret_hex[MC_INVITE_SECRET_LEN * 2 + 1];
  int written;
  if (!invite || !out || out_len <= 0 || !invite->valid) return false;
  encode_hex_16(invite->secret, secret_hex);
  written = snprintf(out, (size_t)out_len, "meshcore://channel/add?name=%s&secret=%s", invite->name, secret_hex);
  return written > 0 && written < out_len;
}
