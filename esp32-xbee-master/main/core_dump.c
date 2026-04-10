/* 
 * This file is part of the ESP32-XBee distribution (https://github.com/nebkat/esp32-xbee).
 * Copyright (c) 2019 Nebojsa Cvetkovic.
 * 
 * This program is free software: you can redistribute it and/or modify  
 * it under the terms of the GNU General Public License as published by  
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU 
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License 
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <string.h>
#include <esp_partition.h>
#include "core_dump.h"

#if __has_include(<esp_core_dump.h>)
#include <esp_core_dump.h>
#define HAS_ESP_CORE_DUMP 1
#else
#define HAS_ESP_CORE_DUMP 0
#endif

static const esp_partition_t *core_dump_partition;
static size_t core_dump_size = 0;

void core_dump_check() {
#if HAS_ESP_CORE_DUMP
    size_t core_dump_addr = 0;
    if (esp_core_dump_image_get(&core_dump_addr, &core_dump_size) != ESP_OK || core_dump_size == 0) {
        return;
    }

    core_dump_partition = esp_partition_find_first(ESP_PARTITION_TYPE_DATA,
            ESP_PARTITION_SUBTYPE_DATA_COREDUMP, NULL);
#else
    core_dump_size = 0;
    core_dump_partition = NULL;
#endif
}

size_t core_dump_available() {
    return core_dump_size;
}

esp_err_t core_dump_read(size_t offset, void *buffer, size_t len) {
    if (core_dump_partition == NULL) {
        return ESP_ERR_NOT_FOUND;
    }

    return esp_partition_read(core_dump_partition, offset, buffer, len);
}
