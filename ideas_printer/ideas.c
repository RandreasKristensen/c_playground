#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Each entry: { argument string, start line, end line, description }
typedef struct {
    const char *arg;
    int         start;
    int         end;
    const char *desc;
} Section;

Section sections[] = {
    { "0", 201, 223, "Toolchain cheat sheet"              },
    { "1", 7,   26,  "Stage 1 — Syntax and toolchain"     },
    { "2", 29,  45,  "Stage 2 — Pointers and memory"      },
    { "3", 48,  66,  "Stage 3 — Structs and logic"        },
    { "4", 69,  88,  "Stage 4 — Multiple files / headers" },
    { "5", 91,  109, "Stage 5 — A small real project"     },
    { "s", 112, 146, "Stage S — Build your own string"    },
    { "a", 156, 163, "Fat Structs A — Fat entity pool"    },
    { "b", 164, 172, "Fat Structs B — SoA vs AoS"         },
    { "c", 173, 181, "Fat Structs C — Immediate mode UI"  },
    { "d", 182, 190, "Fat Structs D — System vs object"   },
    { "e", 191, 198, "Fat Structs E — Flat serialization" },
};

#define NUM_SECTIONS (int)(sizeof(sections) / sizeof(sections[0]))

void print_help(void) {
    printf("Usage: ideas <arg>\n\n");
    printf("  -h        Show this help\n\n");
    printf("  Stages:\n");
    printf("    0       Toolchain cheat sheet\n");
    printf("    1-5     Stages 1 through 5\n");
    printf("    s       Stage S — Build your own string type\n\n");
    printf("  Fat Structs / Data-Oriented Thinking:\n");
    printf("    a       Fat entity pool\n");
    printf("    b       SoA vs AoS benchmark\n");
    printf("    c       Immediate mode terminal UI\n");
    printf("    d       System vs object refactor\n");
    printf("    e       Flat binary serialization\n\n");
    printf("  All sections:\n");
    for (int i = 0; i < NUM_SECTIONS; i++) {
        printf("    %-4s    %s\n", sections[i].arg, sections[i].desc);
    }
}

void print_section(const char *path, int start, int end) {
    FILE *f = fopen(path, "r");
    if (!f) {
        printf("Error: could not open %s\n", path);
        printf("Make sure Ideas.md is in your home directory.\n");
        return;
    }

    char line[512];
    int  current = 0;

    while (fgets(line, sizeof(line), f)) {
        current++;
        if (current > end) break;
        if (current >= start) {
            printf("%s", line);
        }
    }

    fclose(f);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        print_help();
        return 1;
    }

    if (strcmp(argv[1], "-h") == 0) {
        print_help();
        return 0;
    }

    // Build path: $HOME/Ideas.md
    char *home = getenv("HOME");
    if (!home) {
        printf("Error: could not read HOME environment variable.\n");
        return 1;
    }

    char path[512];
    snprintf(path, sizeof(path), "%s/c_playground/Ideas.md", home);

    // Find matching section
    for (int i = 0; i < NUM_SECTIONS; i++) {
        if (strcmp(argv[1], sections[i].arg) == 0) {
            print_section(path, sections[i].start, sections[i].end);
            return 0;
        }
    }

    printf("Unknown argument: %s\n\n", argv[1]);
    print_help();
    return 1;
}
