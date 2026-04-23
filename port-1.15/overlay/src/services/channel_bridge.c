#include "meshcore/services/channel_bridge.h"

#include <string.h>

bool mc_channel_bridge_secret_is_private(const uint8_t* secret16, int len) {
  int i;
  if (!secret16 || len < 16) return false;
  for (i = 0; i < 16; ++i) {
    if (secret16[i] != 0) return true;
  }
  return false;
}

bool mc_channel_bridge_invite_to_secret(const mc_channel_invite_t* invite, uint8_t out_secret16[16]) {
  if (!invite || !invite->valid || !out_secret16) return false;
  memcpy(out_secret16, invite->secret, 16);
  return true;
}
