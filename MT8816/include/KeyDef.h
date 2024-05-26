#include <Arduino.h>

constexpr const uint8_t reverse_row(uint8_t row) {
    return 7 - row;
};

#define KEY_Home    {reverse_row(7), 0}         // ↖
#define KEY_CTP     {reverse_row(7), 1}         // СТР
#define KEY_AP2     {reverse_row(7), 2}         // АР2
#define KEY_F1      {reverse_row(7), 3}         // F1
#define KEY_F2      {reverse_row(7), 4}         // F2
#define KEY_F3      {reverse_row(7), 5}         // F3
#define KEY_F4      {reverse_row(7), 6}         // F4
#define KEY_F5      {reverse_row(7), 7}         // F5

#define KEY_Tab     {reverse_row(6), 0}         // ТАБ
#define KEY_LF      {reverse_row(6), 1}         // ПС
#define KEY_ENTER   {reverse_row(6), 2}         // ВК
#define KEY_Back    {reverse_row(6), 3}         // ЗБ
#define KEY_Left    {reverse_row(6), 4}         // ←
#define KEY_Up      {reverse_row(6), 5}         // ↑
#define KEY_Right   {reverse_row(6), 6}         // →
#define KEY_Down    {reverse_row(6), 7}         // ↓

#define KEY_0       {reverse_row(5), 0}         // 0 _
#define KEY_1       {reverse_row(5), 1}         // 1 !
#define KEY_2       {reverse_row(5), 2}         // 2 "
#define KEY_3       {reverse_row(5), 3}         // 3 #
#define KEY_4       {reverse_row(5), 4}         // 4 $
#define KEY_5       {reverse_row(5), 5}         // 5 %
#define KEY_6       {reverse_row(5), 6}         // 6 &
#define KEY_7       {reverse_row(5), 7}         // 7 ,

#define KEY_UnLin   {reverse_row(5), 0, 1}  // _ 0
#define KEY_Excla   {reverse_row(5), 1, 1}  // ! 1
#define KEY_Quote   {reverse_row(5), 2, 1}  // " 2
#define KEY_Octot   {reverse_row(5), 3, 1}  // # 3
#define KEY_Dolla   {reverse_row(5), 4, 1}  // $ 4
#define KEY_Perce   {reverse_row(5), 5, 1}  // % 5
#define KEY_Amper   {reverse_row(5), 6, 1}  // & 6
//#define KEY_Comma   {0x80 | reverse_row(5), 7}  // , 7

#define KEY_8       {reverse_row(4), 0}         // 8 (
#define KEY_9       {reverse_row(4), 1}         // 9 )
#define KEY_Colon   {reverse_row(4), 2}         // : *
#define KEY_SeCol   {reverse_row(4), 3}         // ; +
#define KEY_Dot     {reverse_row(4), 4}         // . >
#define KEY_Minus   {reverse_row(4), 5}         // - =
#define KEY_Comma   {reverse_row(4), 6}         // , <
#define KEY_Slash   {reverse_row(4), 7}         // / ?

#define KEY_OpenL   {reverse_row(4), 0, 1}  // ( 8
#define KEY_ClosR   {reverse_row(4), 1, 1}  // ) 9
#define KEY_Aster   {reverse_row(4), 2, 1}  // * :
#define KEY_Plus    {reverse_row(4), 3, 1}  // + ;
#define KEY_Great   {reverse_row(4), 4, 1}  // > .
#define KEY_Equal   {reverse_row(4), 5, 1}  // = -
#define KEY_Less    {reverse_row(4), 6, 1}  // < ,
#define KEY_Quest   {reverse_row(4), 7, 1}  // ? /

#define KEY_At      {reverse_row(3), 0}         // @
#define KEY_A       {reverse_row(3), 1}         // A
#define KEY_B       {reverse_row(3), 2}         // B
#define KEY_C       {reverse_row(3), 3}         // C
#define KEY_D       {reverse_row(3), 4}         // D
#define KEY_E       {reverse_row(3), 5}         // E
#define KEY_F       {reverse_row(3), 6}         // F
#define KEY_G       {reverse_row(3), 7}         // G

#define KEY_H       {reverse_row(2), 0}         // H
#define KEY_I       {reverse_row(2), 1}         // I
#define KEY_J       {reverse_row(2), 2}         // J
#define KEY_K       {reverse_row(2), 3}         // K
#define KEY_L       {reverse_row(2), 4}         // L
#define KEY_M       {reverse_row(2), 5}         // M
#define KEY_N       {reverse_row(2), 6}         // N
#define KEY_O       {reverse_row(2), 7}         // O

#define KEY_P       {reverse_row(1), 0}         // P
#define KEY_Q       {reverse_row(1), 1}         // Q
#define KEY_R       {reverse_row(1), 2}         // R
#define KEY_S       {reverse_row(1), 3}         // S
#define KEY_T       {reverse_row(1), 4}         // T
#define KEY_U       {reverse_row(1), 5}         // U
#define KEY_V       {reverse_row(1), 6}         // V
#define KEY_W       {reverse_row(1), 7}         // W

#define KEY_X       {reverse_row(0), 0}         // X
#define KEY_Y       {reverse_row(0), 1}         // Y
#define KEY_Z       {reverse_row(0), 2}         // Z
#define KEY_SqBrL   {reverse_row(0), 3}         // [
#define KEY_BaSl    {reverse_row(0), 4}         // "\\"
#define KEY_SqBrR   {reverse_row(0), 5}         // ]
#define KEY_Circ    {reverse_row(0), 6}         // ^
#define KEY_Space   {reverse_row(0), 7}         // SPACE
