#ifndef MESHCORE_CUSTOM_MESH_PORT_H
#define MESHCORE_CUSTOM_MESH_PORT_H

/*
 * Sketch of the custom Wio Tracker UI port bound to MeshCore 1.15's
 * companion_radio architecture.
 *
 * This is not a drop-in build target yet. It is the intended class shape for
 * forwarding MeshCore callbacks into the custom UI overlay.
 */

#include <helpers/BaseChatMesh.h>
#include "meshcore/services/overlay_context.h"

class CustomMeshPort {
public:
  static void onDirectMessage(const mc_overlay_contact_ref_t& contact, uint32_t timestamp, const char* text);
  static void onChannelMessage(const mc_overlay_channel_ref_t& channel, uint32_t timestamp, const char* text);
  static bool tryImportInvite(const char* text, mc_channel_invite_t* out);
};

#endif
