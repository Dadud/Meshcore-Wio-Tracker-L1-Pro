#ifndef MESHCORE_INVITE_PARSER_H
#define MESHCORE_INVITE_PARSER_H

#include <stdbool.h>
#include <stdint.h>

#define MC_INVITE_MAX_NAME 48
#define MC_INVITE_SECRET_LEN 16

typedef struct {
  char name[MC_INVITE_MAX_NAME];
  uint8_t secret[MC_INVITE_SECRET_LEN];
  bool valid;
} mc_channel_invite_t;

bool mc_invite_parse_channel_url(const char* text, mc_channel_invite_t* out);
bool mc_invite_format_channel_url(const mc_channel_invite_t* invite, char* out, int out_len);

#endif
