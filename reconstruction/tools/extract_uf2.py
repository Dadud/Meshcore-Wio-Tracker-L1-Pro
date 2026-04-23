#!/usr/bin/env python3
"""Extract raw payload from a UF2 firmware image.

Usage:
  python3 extract_uf2.py input.uf2 output.bin
"""
from __future__ import annotations
import struct
import sys
from pathlib import Path

UF2_MAGIC_START0 = 0x0A324655
UF2_MAGIC_START1 = 0x9E5D5157
UF2_MAGIC_END = 0x0AB16F30


def main() -> int:
    if len(sys.argv) != 3:
        print("usage: extract_uf2.py input.uf2 output.bin", file=sys.stderr)
        return 2

    src = Path(sys.argv[1])
    dst = Path(sys.argv[2])
    blocks = []

    with src.open('rb') as f:
        while True:
            block = f.read(512)
            if not block:
                break
            if len(block) != 512:
                raise ValueError("partial UF2 block")
            h = struct.unpack('<IIIIIIII', block[:32])
            if h[0] != UF2_MAGIC_START0 or h[1] != UF2_MAGIC_START1:
                continue
            if struct.unpack('<I', block[508:512])[0] != UF2_MAGIC_END:
                continue
            target_addr = h[3]
            payload_size = h[4]
            payload = block[32:32 + payload_size]
            blocks.append((target_addr, payload))

    blocks.sort(key=lambda item: item[0])
    with dst.open('wb') as out:
        for _addr, payload in blocks:
            out.write(payload)

    print(f"wrote {len(blocks)} blocks to {dst}")
    return 0


if __name__ == '__main__':
    raise SystemExit(main())
