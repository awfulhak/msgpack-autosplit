
#include <config.h>

#include <assert.h>
#include <err.h>
#include <getopt.h>
#include <stdlib.h>

#include "gettext.h"
#include "log.h"
#include "options.h"

static struct option getopt_long_options[] = {
    { "dir", 1, NULL, 'd' },
    { "max-files", 1, NULL, 'F' },
    { "help", 0, NULL, 'h' },
    { "max-space", 1, NULL, 'S' },
    { "soft-limit", 1, NULL, 's' },
    { "rotate-after", 1, NULL, 't' },
    { "version", 0, NULL, 'V' },
    { "compress", 1, NULL, 'z' },
    { NULL, 0, NULL, 0 }
};

static const char *getopt_options = "d:F:hS:s:t:Vz:";

static void
options_version(void)
{
    puts(PACKAGE_STRING);
}

static void
options_usage(void)
{
    const struct option *options = getopt_long_options;

    options_version();
    printf("\n%s\n", _("Options:"));
    do {
        printf("  -%c\t--%s%s\n", options->val, options->name,
               options->has_arg ? "=..." : "");
        options++;
    } while (options->name != NULL);
}

static int
options_init_with_default(AppContext * const context)
{
    assert(context->log_compression == LOG_COMPRESSION_NONE);
    context->log_dir = NULL;
    context->logfile_soft_limit = (size_t) LOGFILE_SOFT_LIMIT_DEFAULT;
    context->logfile_rotate_after = (time_t) -1;
    context->logfile_seq = 0U;
    context->logfile_max_files = 0U;
    context->logfile_max_space = 0;

    return 0;
}

static int
options_apply(AppContext * const context)
{
    if (context->log_dir == NULL) {
        errx(1, _("Directory not specified"));
    }
    return 0;
}

int
options_parse(AppContext * const context, int argc, char *argv[])
{
    int opt_flag;
    int option_index = 0;

    options_init_with_default(context);
    if (argc <= 1) {
        options_usage();
        exit(1);
    }
    while ((opt_flag = getopt_long(argc, argv,
                                   getopt_options, getopt_long_options,
                                   &option_index)) != -1) {
        switch (opt_flag) {
        case 'd':
            context->log_dir = optarg;
            break;
        case 'F':
            context->logfile_max_files = (size_t) strtoul(optarg, NULL, 10);
            break;
        case 'h':
            options_usage();
            exit(0);
        case 'S':
            context->logfile_max_space = (off_t) strtoul(optarg, NULL, 10);
            break;
        case 's':
            context->logfile_soft_limit = (size_t) strtoul(optarg, NULL, 10);
            break;
        case 't':
            context->logfile_rotate_after = (time_t) strtoul(optarg, NULL, 10);
            break;
        case 'V':
            options_version();
            exit(0);
        case 'z':
            if (log_set_compression(context, optarg) != 0) {
                errx(1, _("Unsupported compression method: [%s]"), optarg);
            }
            break;
        default:
            options_usage();
            exit(0);
        }
    }
    options_apply(context);

    return 0;
}
