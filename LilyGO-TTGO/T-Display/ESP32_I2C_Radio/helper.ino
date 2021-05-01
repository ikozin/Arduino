void printlnUint16Hex(uint16_t data) {
  debug_printf("0x%04X\r\n", data);
}

void printlnUInt32Hex(uint32_t data) {
  debug_printf("0x%08X\r\n", data);
}

void printlnStrHex(char* pdata) {
  if (pdata == NULL) {
    debug_printf("NULL\r\n");
    return;
  }
  size_t size = strlen(pdata);
  debug_printf("Address: %d, Size: %d\r\n", (uint32_t)pdata, size);
  for (int i = 0; i < size; i++) {
    debug_printf("0x%02X ", pdata[i]);
  }
  debug_printf("\r\n");
}

void printlnArrayHex(byte* pdata, size_t size) {
  if (pdata == NULL) {
    debug_printf("NULL\r\n");
    return;
  }
  debug_printf("Address: %d, Size: %d\r\n", (uint32_t)pdata, size);
  for (int i = 0; i < size; i++) {
    debug_printf("0x%02X ", pdata[i]);
  }
  debug_printf("\r\n");
}
