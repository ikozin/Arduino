#pragma once

#include "esphome/core/component.h"
#include "esphome/core/automation.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/i2c/i2c.h"


namespace esphome {
namespace rda5807m {

#if !defined(RADIO_BAND_WIDTH_0) &&  !defined(RADIO_BAND_WIDTH_1) &&  !defined(RADIO_BAND_WIDTH_2)
  #define RADIO_BAND_WIDTH_2
#endif

#if defined(RADIO_BAND_WIDTH_0)
  #define RADIO_BAND_WIDTH  0x00
  #define RADIO_BAND_MIN    870
  #define RADIO_BAND_MAX    1080
#endif
#if defined(RADIO_BAND_WIDTH_1)
  #define RADIO_BAND_WIDTH  0x01
  #define RADIO_BAND_MIN    760
  #define RADIO_BAND_MAX    910
#endif
#if defined(RADIO_BAND_WIDTH_2)
  #define RADIO_BAND_WIDTH  0x02
  #define RADIO_BAND_MIN    760
  #define RADIO_BAND_MAX    1080
#endif


#define RDA5807M_RANDOM_ACCESS_ADDRESS 0x11
// регистры
#define RDA5807M_REG2 0x02
#define RDA5807M_REG3 0x03
#define RDA5807M_REG4 0x04
#define RDA5807M_REG5 0x05
#define RDA5807M_REG7 0x07
#define RDA5807M_REGA 0x0A
#define RDA5807M_REGB 0x0B

// https://tsibrov.blogspot.com/2019/11/rda5807m-part1.html
typedef union rda_reg2 {
  struct {
    uint8_t ENABLE : 1;       //Power Up Enable - разрешение работы. Установка в 1 переводит приемник в рабочий режим; 0 - спящий режим - отключает питание внутренних узлов, состояние регистров при этом сохраняется, после возвращения в рабочий режим необходимо выполнить TUNE для настройки на радиостанцию.
    uint8_t SOFT_RESET : 1;   //Программный сброс RDA5807M. Установка бита в 1 приведет к сбросу всех внутренних регистров к значениям по умолчанию. Сброс выполняется автоматически при включении питания микросхемы, нет необходимости сбрасывать устройство дополнительно.
    uint8_t NEW_METHOD : 1;   //New Demodulation Method Enable - установка этого бита задействует новый метод демодуляции, способный улучшить чувствительность приемника
    uint8_t RDS_EN : 1;       //RDS/RBDS Enable. Запись 1 в этот бит включает прием RDS/RBDS сообщений.
    uint8_t CLK_MODE : 3;     //Позволяет выбрать частоту внешнего тактового сигнала. Возможны следующие значения: 000 = 32.768кГц, 001 = 12МГц, 101 = 24МГц, 010 = 13МГц, 110 = 26МГц, 011 = 19.2МГц, 111 = 38.4МГц. При указании неверного значения ничего страшного не произойдет, просто FM приемник не сможет настраиваться на частоту и выполнять поиск радиостанций.
    uint8_t SKMODE : 1;       //Seek Mode. Определяет поведение при достижении границы диапазона во время поиска радиостанций: 0 - продолжить поиск с другой границы; 1 - прекратить поиск
    uint8_t SEEK : 1;         //Запись 1 в этот бит запускает процесс поиска радиостанции. Поиск ведется в направлении, заданном битом SEEKUP, до нахождения радиостанции или до прохождения всего диапазона частот, после чего данный бит сбрасывается и устанавливается бит STC.
    uint8_t SEEKUP : 1;       //Seek Up - направление поиска радиостанций: 0 - к нижней границе диапазона; 1 - вверх.
    uint8_t RCLK_DIRECT_INPUT_MODE : 1;   //Бит RCLK Direct Input Mode следует установить в 1, если используется внешний тактовый сигнал
    uint8_t RCLK_NON_CALIBRATE_MODE : 1;  //Если я правильно понял, этот бит отключает температурную компенсацию тактового генератора, в результате чего RDA5807M не сможет работать в заявленном температурном диапазоне (-20..70C) и сможет поддерживать колебания температуры только на +/- 20C от точки настройки.
    uint8_t BASS : 1;         //Bass Boost - усиление басов. Для включения данной опции необходимо записать 1
    uint8_t MONO : 1;         //Принудительное моно, включается записью в данный бит значения 1 
    uint8_t DMUTE : 1;        //Mute Disable - отключение режима mute, который по умолчанию включен (значение 0). Для отключения mute в этот бит следует записать 1.
    uint8_t DHIZ : 1;         //Audio Output High-Z Disable. Управляет состоянием аудио выводов: 0 - выводы находятся в высокоимпедансном состоянии; 1 - переводит выводы в рабочий режим.
  };
  uint16_t value;
} rda_reg2_t;

typedef union rda_reg3 {
  struct {
    uint16_t SPACE: 2;        //Задает шаг изменения частоты. Возможны следующие значения: 00 - 100кГц, 01 - 200кГц, 10 - 50кГц, 11 - 25кГц. В большинстве стран частоты радиостанций разнесены на 200кГц или 100кГц. Поэтому, скорее всего, вам не придется менять значение по умолчанию. Установив шаг 50кГц или 25кГц, вы лишь замедлите процесс поиска радиостанций.
    uint16_t BAND: 2;         //Выбор полосы. Возможно одно из четырех значений: 00 - 87..108МГц, 01 - 76..91МГц, 10 - 76..108МГц, 11 - 65..76МГц или 50..65МГц (определяется битом 65M_50M MODE регистра 07h)
    uint16_t TUNE : 1;        //Запись в этот бит значения 1 запускает процесс настройки. По окончании настройки устанавливается бит STC, бит TUNE при этом сбрасывается.
    uint16_t DIRECT_MODE : 1; //Режим прямого управления, который используется только при тестировании - это описание из даташита, не уверен, что данный бит имеет отношение к RDA5807M.
    uint16_t CHAN : 10;       //Channel Select - выбор канала. Частота радиостанции устанавливается не явно, а путем изменения значения CHAN, которое при умножении на SPACE и прибавления нижней границы диапазона дает итоговую частоту. Для записи CHAN необходимо также установить бит TUNE, в противном случае CHAN не изменится.
  };
  uint16_t value;
} rda_reg3_t;

typedef union rda_reg4 {
  struct {
    uint8_t RSVD1 : 8;        //Биты зарезервированы
    uint8_t AFCD : 1;         //Automatic Frequency Control Disable - отключение автоматической подстройки частоты. 0 - AFC работает. 1 - AFC выключено. 
    uint8_t SOFTMUTE_EN  : 1; //Soft Mute Enable - приглушение звука, может быть использовано для минимизации шумов в условиях слабого приема. Функция включается установкой бита в 1.
    uint8_t RSVD2 : 1;        //Зарезервирован
    uint8_t DE : 1;           //De-emphases. Определяет значение постоянной времени для  частотных предыскажений: 0 - 75мкс, 1 - 50мкс. Предыскажения подразумевают усиление высоких частот сигнала при передаче (pre-emphasis) с целью уменьшения воздействия на них помех и последующее восстановление исходного сигнала в приемнике (ослабление высоких частот - de-emphases). В большинстве стран (в т.ч. в Европе и РФ) используется значение 50. В Северной и Южной Америке, в Южной Корее - 75.
    uint8_t RSVD3 : 4;        //Биты зарезервированы 
  };
  uint16_t value;
} rda_reg4_t;

typedef union rda_reg5 {
  struct {
    uint8_t VOLUME : 4;       //Регулировка громкости
    uint8_t RSVD1 : 2;        //Биты зарезервированы
    uint8_t LNA_PORT_SEL : 2; //Low Noise Amplifier Port Selection - эти биты пропущены в даташите RDA5807M. При этом они весьма важны, поскольку определяют источник сигнала для приемника (смотрите блок LNA на функциональной схеме приемника в даташите): 00 - нет входа, 01 - LNAN (земля), 10 - LNAP (вход FMIN), 11 - оба источника
    uint8_t SEEKTH : 4;       //Seek Threshold. Данные биты задают порог отношения сигнал/шум при выполнении поиска радиостанций. 
    uint8_t RSVD2  : 3;       //Биты зарезервированы
    uint8_t INT_MODE : 1;     //Режим генерации прерывания при завершении поиска/настройки. Данный бит определен в даташите, но не имеет отношения к RDA5807M. Актуален для микросхем с дополнительными выводами GPIO, например, RDA5807P.
  };
  uint16_t value;
} rda_reg5_t;

typedef union rda_reg6 {
  struct {
    uint8_t RSVD1 : 8;        //Биты зарезервированы
    uint8_t RSVD2 : 5;        //Биты зарезервированы
    uint8_t OPEN_MODE : 2;    //Данные биты указаны в даташите, но они неактуальны для RDA5807M. В других микросхемах серии установка этих битов в 11 разрешает изменение остальных битов регистра, отвечающих за настройку I2S (Audio Data Interface).
    uint8_t RSVD3 : 1;        //Зарезервирован
  };
  uint16_t value;
} rda_reg6_t;

typedef union rda_reg7 {
  struct {
    uint8_t FREQ_MODE : 1;    //Режим задания частоты. Когда данный бит сброшен в 0, результирующая частота определяется как BAND + CHAN * STEP. При FREQ_MODE = 1 частота определяется как BAND + содержимое регистра 08h.
    uint8_t SOFTBLEND_EN : 1; //Soft Blend Enable. Данный бит разрешает шумоподавление, уровень которого задан битами TH_SOFTBLEND. Помогает здорово очистить сигнал от помех.
    uint8_t SEEK_TH_OLD : 6;  //Seek Threshold Old - по аналогии с SEEKTH данные биты определяют порог при поиске радиостанций, но актуальны только при SEEK_MODE (биты 14:12 регистра 0x20h) = 001 - "старый" метод поиска.
    uint8_t RSVD1 : 1;        //Зарезервирован
    uint8_t MODE_65M_50M : 1; //Данный бит определяет используемый диапазон частот, когда биты BAND содержат значение 11: 0 - 50..76МГц, 1 - 65..76МГц
    uint8_t TH_SOFRBLEND : 5; //Soft Blend Thershold - настройка уровня шумоподавления.
    uint8_t RSVD2 : 1;        //Зарезервирован
  };
  uint16_t value;
} rda_reg7_t;

typedef union rda_reg8 {
  struct {
    uint8_t lo;
    uint8_t hi;   
  };
  uint16_t value;
} rda_reg8_t;

typedef union rda_rega {
  struct {
    uint16_t READCHAN : 10;   //Read Channel. Эти биты содержат значение CHAN, доступны только для чтения. В режиме последовательного доступа к регистрам RDA5807M стартовый адрес для чтения - 0Ah, таким образом нет возможности прочитать значение CHAN регистра 03h. Этим и обусловлено наличие битов READCHAN.
    uint16_t ST : 1;          //Stereo Indicator. 0 - моно; 1 - стерео.
    uint16_t BLK_E : 1;       //Данный флаг сообщает о получении E блока.
    uint16_t RDSS : 1;        //RDS Synchronization - индикатор синхронизации RDS. 0 - RDS декодер не синхронизирован; 1 - RDS декодер синхронизирован. В даташите указано, что данный флаг обновляется только в verbose (подробном) режиме работы RDS (в противопоставление стандартному, менее информативному режиму), однако не уточняется, какой бит отвечает за выбор режима. Судя по тому, что данный флаг обновляется, как и биты BLERA .. BLERD, RDA5807M по умолчанию работает в подробном режиме RDS.
    uint16_t SF : 1;          //Seek Fail - флаг, сигнализирующий о неуспешном выполнении поиска, когда не удалось найти сигнал с RSSI большим порога SEEKTH
    uint16_t STC : 1;         //Seek/Tune Complete - флаг завершения поиска/настройки на заданную частоту (1 - операция завершена). 
    uint16_t RDSR : 1;        //RDS Ready - флаг готовности данных RDS/RBDS (1 - данные готовы)
  };
  uint16_t value;
} rda_rega_t;

typedef union rda_regb {
  struct {
    uint8_t BLERB : 2;        //Block Errors Level Of B - уровень ошибок в блоке B (RDS) или E (RBDS, когда ABCD_E флаг установлен в 1). Значения битов аналогичны BLERA.
    uint8_t BLERA : 2;        //Block Errors Level Of A - уровень ошибок в блоке A (RDS) или E (RBDS, когда ABCD_E флаг установлен в 1): 00 - нет ошибок; 01 - 1..2 ошибки требуют коррекции; 10 - 3..5 ошибок  требуют коррекции; 11 - более 6 ошибок - блок некорректный и не должен использоваться.
    uint8_t ABCD_E : 1;       //Действующий в США стандарт RBDS помимо блоков A, B, C и D, предусмотренных стандартом RDS,  предполагает использование еще одного блока - E. Бит ABCD_E помогает идентифицировать содержимое регистров 0Ch..0Fh как  ABCD или E: 0 - A, B, C, D; 1 - E
    uint8_t RSVD1  : 2;       //Биты зарезервированы
    uint8_t FM_READY : 1;     //Насколько я могу судить, данный флаг идентичен флагу STC
    uint8_t FM_TRUE : 1;      //Данный флаг сигнализирует о наличии передачи на текущей частоте. То есть приемник настроен на радиостанцию.
    uint8_t RSSI : 7;         //Received Signal Strength Indicator - показатель уровня принимаемого сигнала.
  };
  uint16_t value;
} rda_regb_t;

class RDA5807M : public Component, public i2c::I2CDevice {
    public:
        void volume_up();
        void volume_down();
        void set_volume(uint8_t volume);
        void toggle_mute();
        void set_band(uint16_t band);
    protected:
        uint16_t    _band;
        uint8_t     _volume;
        bool        _mute;
    public:
        // ========== INTERNAL METHODS ==========
        // (In most use cases you won't need these)
        void setup() override;
        void dump_config() override;
        float get_setup_priority() const override;
        void loop() override;
    protected:
        void Init();
        void SetChannel(uint16_t value);
        void SetVolume(uint16_t value);
        void SetMute(bool value);
        void SetHardMute(bool value);
        void Seek(uint16_t seekth, uint16_t softblend, bool seekUp);

        uint16_t GetChannel();
        uint8_t GetVolume();
        bool GetMute();
        bool GetHardMute();
        uint8_t GetRssi();
        uint16_t GetSeekTh();
        uint16_t GetSoftBlend();
    private:
        const int WaitTime = 5;
    private:
        SemaphoreHandle_t _mutex;
    private:
        void waitTune();
        uint16_t getRegister(uint8_t reg);
        void setRegister(uint8_t reg, const uint16_t value);
};

template<typename... Ts> class VolumeUpAction : public Action<Ts...>, public Parented<RDA5807M> {
    void play(Ts... x) override { this->parent_->volume_up(); }
};

template<typename... Ts> class VolumeDownAction : public Action<Ts...>, public Parented<RDA5807M> {
    void play(Ts... x) override { this->parent_->volume_down(); }
};

template<typename... Ts> class SetVolumeAction : public Action<Ts...>, public Parented<RDA5807M> {
 public:
  TEMPLATABLE_VALUE(uint8_t, volume)

  void play(Ts... x) override {
    auto volume = this->volume_.value(x...);
    this->parent_->set_volume(volume);
  }
};

template<typename... Ts> class ToggleMuteAction : public Action<Ts...>, public Parented<RDA5807M> {
    void play(Ts... x) override { this->parent_->toggle_mute(); }
};

template<typename... Ts> class SetBandAction : public Action<Ts...>, public Parented<RDA5807M> {
 public:
  TEMPLATABLE_VALUE(uint16_t, volume)

  void play(Ts... x) override {
    auto band = this->volume_.value(x...);
    this->parent_->set_band(band);
  }
};



}  // namespace rda5807m
}  // namespace esphome