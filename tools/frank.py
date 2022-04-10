#! /usr/bin/env python3

# Written by Ethan Roseman (ethteck)
# MIT License
# Copyright 2021

# Modified by EpochFlame

import argparse
import sys

# Byte sequence that marks code size
CODESIZE_MAGIC = b"\x00\x00\x00\x06\x00\x00\x00\x00\x00\x00\x00\x34"
ADDI_BYTE_SEQ = b"\x38\x21"
MTLR_BYTE_SEQ = b"\x7C\x08\x03\xA6"
BLR_BYTE_SEQ = b"\x4E\x80\x00\x20"
PROFILE_EXTRA_BYTES = b"\x48\x00\x00\x01\x60\x00\x00\x00"

# Byte sequence array for branches to link register
BLR_BYTE_SEQ_ARRAY = [BLR_BYTE_SEQ,
b"\x4D\x80\x00\x20", b"\x4D\x80\x00\x21", b"\x4C\x81\x00\x20", b"\x4C\x81\x00\x21",
b"\x4D\x82\x00\x20", b"\x4D\x82\x00\x21", b"\x4C\x80\x00\x20", b"\x4C\x80\x00\x21",
b"\x4D\x81\x00\x20", b"\x4D\x81\x00\x21", b"\x4C\x80\x00\x20", b"\x4C\x80\x00\x21",
b"\x4C\x82\x00\x20", b"\x4C\x82\x00\x21", b"\x4C\x81\x00\x20", b"\x4C\x81\x00\x21",
b"\x4D\x83\x00\x20", b"\x4D\x83\x00\x21", b"\x4C\x83\x00\x20", b"\x4C\x83\x00\x21",
b"\x4D\x83\x00\x20", b"\x4D\x83\x00\x21", b"\x4C\x83\x00\x20", b"\x4C\x83\x00\x21"]

# Example invocation: ./frank.py vanilla.o profile.o output.o
parser = argparse.ArgumentParser()
parser.add_argument("vanilla", help="Path to the vanilla object", type=argparse.FileType('rb'))
parser.add_argument("profile", help="Path to the profile object", type=argparse.FileType('rb'))
parser.add_argument("target", help="Path to the target object (to write)")

args = parser.parse_args()

# Read contents into bytearrays and close files
vanilla_bytes = args.vanilla.read()
args.vanilla.close()

# If the file contains no code, the codesize magic will not be found.
# The vanilla object requires no modification.
code_size_magic_idx = vanilla_bytes.find(CODESIZE_MAGIC)
if code_size_magic_idx == -1:
    with open(args.target, "wb") as f:
        f.write(vanilla_bytes)
    sys.exit(0)

saved_len_vanilla = len(vanilla_bytes)

# Find end of code sections in vanilla and stripped bytes
code_size_offset = code_size_magic_idx + len(CODESIZE_MAGIC)
code_size_bytes = vanilla_bytes[code_size_offset:code_size_offset+4]
code_size = int.from_bytes(code_size_bytes, byteorder='big')

eoc_offset = 0x34 + code_size

# Epilogue unscheduling
#
# If the epilogue contains addi/mtlr/blr,
# sift them all to the bottom of the epilogue.
#
idx = 0x34
shift = 0 # difference between vanilla and profile code, due to bl/nops
while idx < eoc_offset:
    # Find next epilogue
    addi_pos = vanilla_bytes.find(ADDI_BYTE_SEQ, idx)
    if addi_pos == -1:
        break # break while loop when no targets remain
    if addi_pos % 4 != 0: # check 4-byte alignment
        idx += 4
        continue
    addi = vanilla_bytes[addi_pos:addi_pos+4]

    # find paired blr
    blr_pos = vanilla_bytes.find(BLR_BYTE_SEQ, addi_pos)
    assert blr_pos != -1
    assert blr_pos % 4 == 0

    mtlr_pos = vanilla_bytes.find(MTLR_BYTE_SEQ, idx, blr_pos)
    if mtlr_pos != -1:
        assert mtlr_pos % 4 == 0
        mtlr = vanilla_bytes[mtlr_pos:mtlr_pos+4]

        i = min(addi_pos, mtlr_pos)
        before = vanilla_bytes[:i]
        epilogue = vanilla_bytes[i+4:blr_pos]
        i = max(addi_pos, mtlr_pos) - (i + 4)
        epilogue = epilogue[:i] + epilogue[i+4:]
    else:
        before = vanilla_bytes[:addi_pos]
        mtlr = b""
        epilogue = vanilla_bytes[addi_pos+4:blr_pos]


    epilogue = epilogue + addi + mtlr
    vanilla_bytes = before + epilogue \
                  + vanilla_bytes[blr_pos:]

    assert len(vanilla_bytes) == saved_len_vanilla

    idx = blr_pos + 4

with open(args.target, "wb") as f:
    f.write(vanilla_bytes)
