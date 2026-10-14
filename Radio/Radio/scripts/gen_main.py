#!/usr/bin/env python3
import os
import sys
from pathlib import Path

# ------------------------------------------------------------------
# Таблица КОИ‑7 для кириллицы (упрощённая эмуляция с SI/SO)
# ------------------------------------------------------------------
koi7_map = {
    'А': 0x41, 'Б': 0xA0, 'В': 0x42, 'Г': 0xA1, 'Д': 0xE0, 'Е': 0x45, 'Е': 0xA2,
    'Ж': 0xA3, 'З': 0xA4, 'И': 0xA5, 'Й': 0xA6, 'К': 0x4B, 'Л': 0xA7, 'М': 0x4D,
    'Н': 0x48, 'О': 0x4F, 'П': 0xA8, 'Р': 0x50, 'С': 0x43, 'Т': 0x54, 'У': 0xA9,
    'Ф': 0xAA, 'Х': 0x58, 'Ц': 0xE1, 'Ч': 0xAB, 'Ш': 0xAC, 'Щ': 0xE2, 'Ъ': 0xAD,
    'Ы': 0xAE, 'Ь': 0xC4, 'Э': 0xAF, 'Ю': 0xB0, 'Я': 0xB1,

    'а': 0x61, 'б': 0xB2, 'в': 0xB3, 'г': 0xB4, 'д': 0xE3, 'е': 0x65, 'ё': 0xB5,
    'ж': 0xB6, 'з': 0xB7, 'и': 0xB8, 'й': 0xB9, 'к': 0xBA, 'л': 0xBB, 'м': 0xBC,
    'н': 0xBD, 'о': 0x6F, 'п': 0xBE, 'р': 0x70, 'с': 0x63, 'т': 0xBF, 'у': 0x79,
    'ф': 0xE4, 'х': 0x78, 'ц': 0xE5, 'ч': 0xC0, 'ш': 0xC1, 'щ': 0xE6, 'ъ': 0xC2,
    'ы': 0xC3, 'ь': 0xC4, 'э': 0xC5, 'ю': 0xC6, 'я': 0xC7,
}

def utf8_to_koi7_bytes(text: str) -> bytes:
    result = bytearray()
    in_russian_mode = False  # по умолчанию ASCII

    for ch in text:
        if ch in koi7_map:
            result.append(koi7_map[ch])
        else:
            result.append(ord(ch))

    return bytes(result)


def parse_ini(ini_path: Path):
    """Простой парсер strings.ini: ключ = значение"""
    data = {}
    with open(ini_path, "r", encoding="utf-8") as f:
        for line_no, line in enumerate(f, 1):
            line = line.strip()
            if not line or line.startswith("#") or "=" not in line:
                continue
            key, _, value = line.partition("=")
            key = key.strip().replace(" ", "_")
            value = value.strip()
            if key in data:
                print(f"Warning: duplicate key '{key}' at line {line_no}, overwriting.")
            data[key] = value
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

    with open(out_file, "w", encoding="utf-8") as f:
        f.write("// Автосгенерировано gen_strings.py\n")
        f.write("#pragma once\n\n")
        f.write("#include <Arduino.h>\n\n")
        f.write("// Строковые константы в эмуляции КОИ‑7 (SI/SO)\n\n")

        for key, text in strings.items():
            koi7_data = utf8_to_koi7_bytes(text)

            # Формируем C-массив
            hex_parts = [f"\\0x{b:02X}" for b in koi7_data]
            # Разбиваем по 10 элементов на строку для читаемости
            f.write(f"const char {key}[] = \"")
            for i, h in enumerate(hex_parts):
                f.write(h)
            f.write("\";\n")
            # f.write(f"const size_t {key}_LEN = {len(koi7_data)};\n\n")

    print(f"Generated: {out_file}")


if __name__ == "__main__":
    main()
