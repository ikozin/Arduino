Import("env")

import subprocess
import sys
from os import path

script = path.join(env.get("PROJECT_DIR"), "scripts", "gen_strings.py")

print("=== Запуск генерации strings.h (KOI‑7) ===")
result = subprocess.run([sys.executable, script], check=False)
if result.returncode != 0:
    print("Ошибка генерации strings.h — сборка прервана.")
    env.Exit(1)
print("=== Генерация завершена ===")
