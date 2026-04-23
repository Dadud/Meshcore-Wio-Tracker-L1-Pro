#ifndef MESHCORE_REPEATER_VIEW_MODELS_H
#define MESHCORE_REPEATER_VIEW_MODELS_H

#include <stdint.h>
#include <stdbool.h>

#define MC_MAX_OWNER_NAME 64
#define MC_MAX_OWNER_INFO 160
#define MC_MAX_ACL_ROWS 32
#define MC_MAX_NEIGHBOURS 32
#define MC_MAX_NODE_LABEL 48

typedef struct {
  bool valid;
  uint8_t pub_key[6];   // identifying prefix of the repeater that reported this status
  uint8_t channel_idx;   // channel index used for this repeater session (0xff = none)
  uint32_t uptime_seconds;
  uint32_t rx_packets;
  uint32_t tx_packets;
  int16_t last_rssi;
  int16_t last_snr_tenths;
  uint16_t queue_used;
  uint16_t queue_free;
  uint16_t battery_mv;
} mc_repeater_status_view_t;

typedef struct {
  bool valid;
  uint8_t pub_key[6];
  uint8_t channel_idx;
  char owner_name[MC_MAX_OWNER_NAME];
  char owner_info[MC_MAX_OWNER_INFO];
} mc_repeater_owner_view_t;

typedef struct {
  char label[MC_MAX_NODE_LABEL];
  uint8_t permissions;
} mc_acl_entry_t;

typedef struct {
  bool valid;
  uint8_t pub_key[6];
  uint8_t channel_idx;
  uint8_t count;
  mc_acl_entry_t entries[MC_MAX_ACL_ROWS];
} mc_repeater_acl_view_t;

typedef struct {
  char label[MC_MAX_NODE_LABEL];
  int16_t rssi;
  int16_t snr_tenths;
  uint8_t hops;
} mc_neighbour_entry_t;

typedef struct {
  bool valid;
  uint8_t pub_key[6];
  uint8_t channel_idx;
  uint8_t count;
  mc_neighbour_entry_t entries[MC_MAX_NEIGHBOURS];
} mc_repeater_neighbours_view_t;

#endif
