#include <glob.h>
#include <gpiod.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

int showLineInfo(unsigned int line_offset, struct gpiod_chip *chip, spdlog::logger &main_logger) {

    const char *name, *consumer, *dir;
    struct gpiod_line_info *info;

    info = gpiod_chip_get_line_info(chip, line_offset);
    if (!info) {
        main_logger.error("failed to read info: {}", strerror(errno));
        return EXIT_FAILURE;
    }

    name = gpiod_line_info_get_name(info);
    if (!name)
        name = "unnamed";

    consumer = gpiod_line_info_get_consumer(info);
    if (!consumer)
        consumer = "unused";

    dir = (gpiod_line_info_get_direction(info) ==
            GPIOD_LINE_DIRECTION_INPUT) ?
                "input" :
                "output";

    main_logger.info("line {:3d}: {:12s} {:12s} {:8s} {:10s}",
            gpiod_line_info_get_offset(info), name, consumer, dir,
            gpiod_line_info_is_active_low(info) ? "active-low" :
                                "active-high");

    gpiod_line_info_free(info);

    return EXIT_SUCCESS;
}

int showGpioInfo(const char *chip_path, spdlog::logger &main_logger) {

    struct gpiod_chip_info *info;
    struct gpiod_chip *chip;

    chip = gpiod_chip_open(chip_path);
    if (!chip) {
        main_logger.error("failed to open chip: {}", strerror(errno));
        return EXIT_FAILURE;
    }

    info = gpiod_chip_get_info(chip);
    if (!info) {
        main_logger.error("failed to read info: {}", strerror(errno));
        return EXIT_FAILURE;
    }

    spdlog::info("Chip name: {}", gpiod_chip_info_get_name(info));
    spdlog::info("Chip label: {}", gpiod_chip_info_get_label(info));
    spdlog::info("Chip lines: {}", gpiod_chip_info_get_num_lines(info));

    for (unsigned int i = 0; i < gpiod_chip_info_get_num_lines(info); i++) {
        showLineInfo(i, chip, main_logger);
    }

    gpiod_chip_info_free(info);
    gpiod_chip_close(chip);

    return EXIT_SUCCESS;
}

int main(void) {

    int ret_val = 0;

    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/my_program_log.txt", true);

    // Multi sink logger:
    spdlog::logger main_logger("main", {console_sink, file_sink});

        // Set up log level:
    main_logger.set_level(spdlog::level::info);
    main_logger.info("Hello, world from the multi-sink logger!");


    glob_t glob_result;
    memset(&glob_result, 0, sizeof(glob_result));

    int return_value = glob("/dev/gpiochip*", GLOB_TILDE, NULL, &glob_result);
    if (return_value != 0) {
        globfree(&glob_result);
        main_logger.error("Error: No files found or error reading files.");
        return 1;
    }

    for (size_t i = 0; i < glob_result.gl_pathc; ++i) {
        // std::cout << "Found path: " << glob_result.gl_pathv[i] << std::endl;
        ret_val = showGpioInfo(glob_result.gl_pathv[i], main_logger);
        if (ret_val != 0) {
            main_logger.error("Error: Unable to read GPIO info.");
            break;
        }
    }

    globfree(&glob_result);

    return ret_val;
}
