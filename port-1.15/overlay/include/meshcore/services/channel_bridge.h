#ifndef MESHCORE_CHANNEL_BRIDGE_H
#define MESHCORE_CHANNEL_BRIDGE_H

#include <stdbool.h>
#include <stdint.h>
#include "meshcore/services/invite_parser.h"

bool mc_channel_bridge_secret_is_private(const uint8_t* secret16, int len);
bool mc_channel_bridge_invite_to_secret(const mc_channel_invite_t* invite, uint8_t out_secret16[16]);

#endif
