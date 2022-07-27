/*
assembler: Program for compiling an assembly programs.
           This header file contains includes, defines,
           prototypes, typedefs and structs.
author: uri hetzrony
*/

/* includes */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "first_scan.h"
#include "second_scan.h"
#include "output.h"
#include "preprocessor.h"
#include "symbol_table.h"

/* defines */
#define MIN_ARG 2
#define MAX_LINE_LENGTH 81
#define MAX_INSTRUCTION 256
#define MAX_DATA 256
#define FIRST_ADDRESS 100
#define MAX_LABEL_LENGTH 30
#define DATA -1
#define WHITESPACE_TOK " \t\n"
#define COMMA_TOK ","
#define NUM_OF_REGISTERS 8
#define MAX_IMMEDIATE_NUM 8192
#define DEFAULT_BASE 10
/* offsets */
#define DST 2
#define SRC 4
#define OPCODE 6
#define REGULAR_EXTRA_BYTE 2
#define SRC_REG_EXTRA_BYTE 8
/* extensions */
#define OB_EXTENSION ".ob"
#define ENTRY_EXTENSION ".ent"
#define EXTERN_EXTENSION ".ext"

/* enums */
enum{SUCCESS, FAILURE};
enum{FALSE, TRUE};
enum{ABSOLUTE, EXTERNAL, RELOCATABLE};
enum{NO_ARGS, ONE_ARG, TWO_ARGS};
enum{IMMEDIATE, DIRECT, RANDOM, REGISTER};

/* typedefs */
typedef struct symbol_element symbol;
typedef struct queue_element element;
typedef struct comp_info compilation_info;
typedef struct action_func action;
typedef struct reg_info reg;
typedef struct command_func command;

/* structs */

/* Element in the symbol list. */
struct symbol_element {
    char name[MAX_LABEL_LENGTH + 1];
    int value;
    int type;
    symbol *next;
};

/* Element in a queue, for entry and extern list. */
struct queue_element {
    char name[MAX_LABEL_LENGTH + 1];
    int value;
    element *next;
};

/* For actions list. */
struct action_func {
    char *command;
    int code;
    int (*count_func)(compilation_info*);
    int (*parse_func)(compilation_info*,int);
};

/* For registers list. */
struct reg_info {
    char *name;
    int num;
};

/* For command list. */
struct command_func {
    char *name;
    int (*func)(compilation_info*);
};

/* For storing info about the compiling. */
struct comp_info {
    int instruction_count;
    int data_count;
    int not_external_symbol_count;
    int line_count;
    int has_label;
    int fail;
    int has_entry;
    int has_external;

    short int instruction[MAX_INSTRUCTION];
    short int data[MAX_DATA];
    char line[MAX_LINE_LENGTH + 1];
    char label[MAX_LABEL_LENGTH + 1];
    element *entry_head;
    element *entry_tail;
    element *extern_head;
    element *extern_tail;
    symbol *symbol_head;
    action *action_list;
    reg *reg_list;
    command *cmd_list;
};

/* prototypes */

/* assembler.c */
int compile(FILE*, char*, char*);
