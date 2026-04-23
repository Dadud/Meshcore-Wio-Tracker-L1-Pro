#include "meshcore/port/custom_mesh_port.h"

void CustomMeshPort::onDirectMessage(const mc_overlay_contact_ref_t& contact, uint32_t timestamp, const char* text) {
  mc_overlay_receive_direct_message(&contact, timestamp, text, false);
}

void CustomMeshPort::onChannelMessage(const mc_overlay_channel_ref_t& channel, uint32_t timestamp, const char* text) {
  mc_overlay_receive_channel_message(&channel, timestamp, text);
}

bool CustomMeshPort::tryImportInvite(const char* text, mc_channel_invite_t* out) {
  return mc_overlay_try_import_channel_invite(text, out);
}
