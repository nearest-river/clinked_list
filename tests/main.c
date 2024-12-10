#include <stdio.h>
#include <string.h>
#include "../src/lib.h"

#define INP_SIZE 64

typedef enum SubCommand {
  HELP,
  PUSH_FRONT,
  PUSH_BACK,
  INSERT,
  INSERT_AFTER,
  INSERT_BEFORE,
  POP_FRONT,
  POP_BACK,
  REMOVE,
  REMOVE_ELEMENT,
  REMOVE_AFTER,
  REMOVE_BEFORE,
  REV,
  PRINT,
  QUIT,
  INVALID
} SubCommand;

void print_help();
SubCommand parse_subcommand(char* buf);


int main(int argc,const char** argv) {
  LinkedList list=ll_new(sizeof(int),LL_VTABLE_I32);
  print_help();

  while(true) {
    puts("(list) ");
    char line[INP_SIZE];
    scanf("%63[^\n]",line);
    SubCommand subcommand=parse_subcommand(line);

    switch(subcommand) {
      case HELP:
        // ll_help()
      break;
      case PUSH_FRONT:
        // ll_push_front()
      break;
      case PUSH_BACK:
        // ll_push_back()
      break;
      case INSERT:
        // ll_insert()
      break;
      case INSERT_AFTER:
        // ll_insert_after()
      break;
      case INSERT_BEFORE:
        // ll_insert_before()
      break;
      case POP_FRONT:
        // ll_pop_front()
      break;
      case POP_BACK:
        // ll_pop_back()
      break;
      case REMOVE:
        // ll_remove()
      break;
      case REMOVE_ELEMENT:
        // ll_remove_element()
      break;
      case REMOVE_AFTER:
        // ll_remove_after()
      break;
      case REMOVE_BEFORE:
        // ll_remove_before()
      break;
      case REV:
        // ll_rev()
      break;
      case PRINT:
        // ll_print()
      break;
      case QUIT:
        // ll_quit()
      break;
      case INVALID:
      break;
    }
  }




  return 0;
}

static bool eq(char* self,char* rhs) {
  while(*self) {
    char c=*self;
    if(c==' ' || c=='\t' || c=='\r' || c=='\n') {
      self++;
      continue;
    }

    if(c!=*rhs++) {
      return false;
    }

    self++;
  }

  return true;
}

SubCommand parse_subcommand(char* buf) {
  if(eq(buf,"h")) {
    return HELP;
  } else if(eq(buf,"push_front")) {
    return PUSH_FRONT;
  } else if(eq(buf,"push_back")) {
    return PUSH_BACK;
  } else if(eq(buf,"insert")) {
    return INSERT;
  } else if(eq(buf,"insert_after")) {
    return INSERT_AFTER;
  } else if(eq(buf,"insert_before")) {
    return INSERT_BEFORE;
  } else if(eq(buf,"pop_front")) {
    return POP_FRONT;
  } else if(eq(buf,"pop_back")) {
    return POP_BACK;
  } else if(eq(buf,"remove")) {
    return REMOVE;
  } else if(eq(buf,"remove_element")) {
    return REMOVE_ELEMENT;
  } else if(eq(buf,"remove_after")) {
    return REMOVE_AFTER;
  } else if(eq(buf,"remove_before")) {
    return REMOVE_BEFORE;
  } else if(eq(buf,"rev")) {
    return REV;
  } else if(eq(buf,"print")) {
    return PRINT;
  } else if(eq(buf,"q")) {
    return QUIT;
  } else {
    return INVALID;
  }
}

void print_help() {
  puts("  h: prints the list of commands\n");
  puts("  push_front <element>: pushes <element> to the front of the list\n");
  puts("  push_back <element>: pushes <element> to the back of the list\n");
  puts("  insert <n> <element>: inserts <element> at the <n>th position\n");
  puts("  insert_after <element> <target>: inserts <element> after <target>\n");
  puts("  insert_before <element> <target>: inserts <element> before <target>\n");
  puts("  pop_front: pops the first element of the list and prints it\n");
  puts("  pop_back: pops the last element of the list and prints it\n");
  puts("  remove <n>: removes the <n>th element of the list and prints it\n");
  puts("  remove_element <element>: removes <element> from the list\n");
  puts("  remove_after <target>: removes the node after <target> and prints it\n");
  puts("  remove_before <target>: removes the node before <target> and prints it\n");
  puts("  rev: reverses the list\n");
  puts("  print: prints the list to the screen\n");
  puts("  q: exit program\n");
}



