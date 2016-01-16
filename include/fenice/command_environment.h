#ifndef _COMMAND_ENVIRONMENTH
#define _COMMAND_ENVIRONMENTH

#ifdef HAVE_GETOPT_H
#include <getopt.h>
#endif
#include <fenice/prefs.h>
#include <fenice/log.h>
#include <fenice/types.h>

uint32 command_environment(int, char **);
#endif
