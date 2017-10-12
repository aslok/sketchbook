// Информация об измеренной температуре хранится в оперативной памяти датчика,
// которая состоит из 9 байт.
// 1 и 2 байты хранят информацию о температуре.
// 3 и 4 байты хранят соответственно верхний и нижний пределы температуры.
// 5 и 6 байты зарезервированы.
// 7 и 8 байты используются для сверхточного измерения температуры.
// 9 байт хранит помехоустойчивый CRC код предыдущих 8 байт.

// Команды:
// 0x44 – провести измерение температуры и записать данные в оперативную память
// 0x4E – записать 3 байта в 3й, 4й и 5й байты оперативной памяти
// 0xBE – считать последовательно 9 байт оперативной памяти
// 0x48 – скопировать 3й и 4й байты оперативной памяти в EEPROM
// 0xB8 – скопировать данные из EEPROM В 3й и 4й байты оперативной памяти
// 0xB4 – вернет тип питания (0 – паразитное, 1 – внешнее)

#include "LiquidCrystal.h"
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
#include "OneWire.h"
// Шина OneWire подключена к 12-му пину
OneWire ds(12);

// Количество подключенных датчиков ds_cnt
const byte ds_cnt = 2;

// Массив из ds_cnt групп по 8 байт
byte addr[ds_cnt][8];
// Массив для id найденных устройств
int addr_id[ds_cnt];
// Температура в градусах Цельсия
float celsius[ds_cnt];

// Поиск 1-Wire устройств
// Если устройство найдено, то в 8 байтный массив addr[ds_num]
// записывается его ROM код
void ds_search(){
    // Предпологаем, что все устройства уже найдены
    boolean search_done = true;
    for (byte ds_num = 0; ds_num < ds_cnt; ds_num++){
        // Если устройство найдено переходим к следующему
        if (addr_id[ds_cnt]){
            continue;
        }
        // Устройство номер ds_num не было найдено
        search_done = false;
        break;
    }
    search:
    // Повторяем поиск до тех пор, пока не найдем все устройства
    while (!search_done){
        // Выполняет новый поиск с первого устройства.
        ds.reset_search();
        delay(250);
        for (byte ds_num = 0; ds_num < ds_cnt; ds_num++){
            // Если устройство не найдено или CRC код не верный
            if (!ds.search(addr[ds_num]) ||
                    OneWire::crc8(addr[ds_num], 7) != addr[ds_num][7]){
                // Начинаем поиск с начала
                goto search;
            }
            // Присваиваем id новому устройству
            addr_id[ds_num] = ds_id_get(addr[ds_num]);
        }
        // Все устройства успешно найдены
        search_done = true;
    }
    return;
}

// Присваиваем id новому устройству
int ds_id_get(byte* addr){
    int ds_id = 0;
    for (byte byte_num = 0; byte_num < 8; byte_num++){
        ds_id += addr[byte_num];
    }
    return ds_id;
}

// Провести измерение температуры и записать данные в оперативную память
void ds_raw_create(byte* addr){
    // Выполняет сброс шины, необходимо перед связью с датчиком.
    ds.reset();
    // Выполняет выбор устройства после сброса, передается ROM Код устройства.
    ds.select(addr);
    // Передает информационный байт на устройство, работающее в паразитном режиме питания
    ds.write(0x44, 1);
}

// Считать последовательно 9 байт оперативной памяти
void ds_raw_read(byte* addr, byte* data){
    // Выполняет сброс шины, необходимо перед связью с датчиком.
    ds.reset();
    // Выполняет выбор устройства после сброса, передается ROM Код устройства.
    ds.select(addr);
    // Передает информационный байт на устройство
    ds.write(0xBE);
    // Смотрим 9 байтов
    for (byte i = 0; i < 9; i++){
        // Считывает информационный байт с устройства
        data[i] = ds.read();
    }
}

// Преобразуем получненный данные в температуру
float ds_raw_to_celsius(byte* addr, byte* data){
    int16_t raw = (data[1] << 8) | data[0];
    switch (addr[0]){
        // Old DS18S20
        case 0x10:
            raw = raw << 3;
            if (data[7] == 0x10){
                raw = (raw & 0xFFF0) + 12 - data[6];
            }
            break;
        // DS18B20
        case 0x28:
        // DS1822
        case 0x22:
            switch (data[4] & 0x60){
                case 0x00:
                    raw = raw & ~7;
                    break;
                case 0x20:
                    raw = raw & ~3;
                    break;
                case 0x40:
                    raw = raw & ~1;
            }
    }
    return (float) raw / 16.0;
}

void setup(){
    // Обнуляем id устройств
    for (byte ds_num = 0; ds_num < ds_cnt; ds_num++){
        addr_id[ds_num] = 0;
    }

    lcd.begin(16, 2);
}

void loop(){
    // Ищем все устройства
    ds_search();

    // Массив для температур
    float celsius[ds_cnt];
    // Получаем температуру с каждого устройства
    for (byte ds_num = 0; ds_num < ds_cnt; ds_num++){
        ds_raw_create(addr[ds_num]);

        delay(250);

        byte data[9];
        ds_raw_read(addr[ds_num], data);
        celsius[ds_num] = ds_raw_to_celsius(addr[ds_num], data);

        delay(250);
    }

    // Выводим температуру с каждого устройства на экран
    for (byte ds_num = 0; ds_num < ds_cnt; ds_num++){
        // Выводим id устройства
        lcd.setCursor(0, ds_num);
        lcd.print(addr_id[ds_num]);
        // Выводим температуру с устройства
        lcd.setCursor(11, ds_num);
        lcd.print(celsius[ds_num]);
    }
}
