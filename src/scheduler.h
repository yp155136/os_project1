#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#define _GNU_SOURCE

#include "util.h"

#include "FIFO.h"
#include "SJF.h"
#include "RR.h"
#include "PSJF.h"

int get_policy();

#endif // _SCHEDULER_H_
