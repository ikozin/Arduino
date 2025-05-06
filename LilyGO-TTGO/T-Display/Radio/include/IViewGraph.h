#pragma once
#include <Arduino.h>
#include <TFT_eSPI.h>

template<typename DataType,
    uint32_t PosX, uint32_t PosY, uint32_t Height, uint32_t ColWidth, uint32_t Multiplier, uint32_t MaxValue,
    uint32_t ColorBorder, uint32_t ColorNormal, uint32_t ColorMax>
class IViewGraph {
    protected:
        virtual float ExtractValue(DataType value) = 0; 

        void DrawGraph(TFT_eSprite* sprite, DataType* data, size_t size) {
            for (size_t i = 0; i < size; i++) {
                uint32_t value = ExtractValue(data[i]) * Multiplier;
                // LOG("%d (%.1f) ", value, ExtractValue(data[i]));
                if (value > 0) {
                    if (value > Height) value = Height;
                    uint32_t color = (value >= MaxValue * Multiplier) ? ColorMax : ColorNormal;
                    sprite->fillRect(PosX + (i * (ColWidth + 1)), PosY - value, ColWidth, value, color);
                }
            }
            // LOGN("");
            sprite->drawFastHLine(PosX, PosY - (MaxValue * Multiplier), (ColWidth + 1) * size, ColorMax);
            sprite->drawRect(PosX - 1, PosY - Height - 1, (ColWidth + 1) * size + 2, Height + 2, ColorBorder);
        }
};