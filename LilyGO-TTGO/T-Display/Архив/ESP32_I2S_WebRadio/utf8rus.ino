#include <Arduino.h>

#define MaxStringLenght 127
char target[MaxStringLenght + 1] = "";

char *utf8rus(const char *source) {
  int i,j,k;
  unsigned char n;
  char m[2] = { '0', '\0' };
  strcpy(target, "");
  k = strlen(source);
  i = j = 0;
  while (i < k) {
    n = source[i++];
    if (n >= 127) {
      switch (n) {
        case 208:{
          n = source[i++];
          if (n == 129) { n = 149; break; } // перекодируем букву Ё->Е
          break;
        }
        case 209: {
          n = source[i++];
          if (n == 145) { n = 181; break; } // перекодируем букву ё->е
          break;
        }
        case 239: {
          n = source[i++];
          n = source[i++];
          continue;
        }
      }
    }

    m[0] = n; strcat(target, m);
    if (++j >= MaxStringLenght) break;
  }
  return target;
}
