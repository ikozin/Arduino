#!/usr/bin/env python3
import os
import sys
from datetime import datetime, timezone
from pathlib import Path
import configparser

from koi7 import koi7_map


def utf8_to_koi7_bytes(text: str) -> bytes:
    result = bytearray()
    for ch in text:
        if ch in koi7_map:
            result.append(koi7_map[ch])
        else:
            result.append(ord(ch))
    return bytes(result)


def parse_ini(ini_path: Path):
    """Парсер strings.ini через configparser (поддержка ;, #, секций)"""
    config = configparser.ConfigParser(
        interpolation=None,
        inline_comment_prefixes=(';',)
    )
    config.read(ini_path, encoding="utf-8-sig")

    data = {}
    for section in config.sections():
        for key, value in config.items(section):
            data[key] = value.strip('"')
    return data


def main():
    project_root = Path(__file__).resolve().parent.parent
    ini_path = project_root / "strings.ini"
    out_dir = project_root / "include"
    out_file = out_dir / "strings.h"

    if not ini_path.exists():
        print(f"Error: strings.ini not found at {ini_path}")
        sys.exit(1)

    os.makedirs(out_dir, exist_ok=True)

    strings = parse_ini(ini_path)
    if not strings:
        print("Warning: no strings found in strings.ini")

    timestamp = datetime.now(timezone.utc).strftime("%Y-%m-%d %H:%M UTC")

    with open(out_file, "w", encoding="utf-8") as f:
        f.write(f"// Автосгенерировано gen_strings.py ({timestamp})\n")
        f.write("#pragma once\n\n")
        f.write("#include <Arduino.h>\n\n")
        f.write("// Строковые константы в эмуляции КОИ-7 (SI/SO)\n\n")

        for key, text in strings.items():
            koi7_data = utf8_to_koi7_bytes(text)

            hex_parts = [f"\\0x{b:02X}" for b in koi7_data]
            f.write(f"#define\t{key} \"")
            for h in hex_parts:
                f.write(h)
            f.write("\"\n")

    print(f"Generated: {out_file}")


if __name__ == "__main__":
    main()
