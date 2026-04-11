idf_component_register(
    SRCS
        "main.c"
        "config.c"
        "core_dump.c"
        "log.c"
        "status_led.c"
        "uart.c"
        "util.c"
        "web_server.c"
        "wifi.c"
        "retry.c"
        "stream_stats.c"

        "interface/ntrip_util.c"
        "interface/ntrip_caster.c"
        "interface/ntrip_client.c"
        "interface/ntrip_server.c"
        "interface/socket_client.c"
        "interface/socket_server.c"

        "protocol/nmea.c"

    INCLUDE_DIRS "include"

    REQUIRES
        # Core
        freertos
        esp_ringbuf
        esp_system
        esp_event

        # Storage
        nvs_flash
        esp_partition
        spi_flash

        # Drivers (v6 split)
        esp_driver_uart
        esp_driver_gpio
        esp_driver_ledc

        # Networking
        esp_wifi
        lwip

        # HTTP
        esp_http_server
        esp_http_client
        esp-tls
        cjson

        # OTA
        app_update

        # Transport
        tcp_transport

        # Core dump
        espcoredump
)

# SPIFFS
spiffs_create_partition_image(www ${PROJECT_DIR}/www FLASH_IN_PROJECT)
