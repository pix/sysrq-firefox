/*
 * -*- mode: c; c-file-style: "openbsd" -*-
 * Copyright (c) 2019 Camille MONCELIER <camille@moncelier.fr>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <linux/init.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/sched/mm.h>
#include <linux/module.h>
#include <linux/sysrq.h>
#include <linux/kernel.h>
#include <linux/dcache.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/mm.h>
#include <linux/mm_types.h>
#include <linux/mman.h>

#ifdef DEBUG
#define TRACE_ENTRY printk(KERN_CRIT "Entering %s\n", __func__)
#define TRACE_EXIT  printk(KERN_CRIT "Exiting %s\n", __func__)
#else
#define TRACE_ENTRY do {} while (0)
#define TRACE_EXIT  do {} while (0)
#endif

#if HAVE_CONFIG_H
#  include <config.h>
#endif

#define PATH_MAX 4096

extern const char *__progname;
extern struct task_struct init_task;

void kill_task(struct task_struct *task)
{
    int signum = SIGKILL;
    struct kernel_siginfo info;
    memset(&info, 0, sizeof(struct kernel_siginfo));
    info.si_signo = signum;
    int ret = send_sig_info(signum, &info, task);
    if (ret < 0) {
        printk(KERN_INFO "error sending signal\n");
    }
}

void handle_task(struct task_struct *task)
{
    if (strstr("MainThread", task->comm)) {
        printk("Will kill this thread: name: %s, pid: [%d], state: %li, path: \n", task->comm, task->pid, task->state);
        kill_task(task);
    } else {
        printk("Nope: %s : %d", task->comm, task->pid);
    }
}

/**
 * Performs a DFS on a given task's children.
 *
 * @void
 */
void DFS(struct task_struct *task)
{
    struct task_struct *child;
    struct list_head *list;

    handle_task(task);

    list_for_each(list, &task->children) {
        child = list_entry(list, struct task_struct, sibling);
        DFS(child);
    }
}

static void
firekill(int key)
{
    DFS(&init_task);
}

static struct sysrq_key_op firekill_op = {
    handler:    &firekill,
    help_msg:    "fireKill",
    action_msg:    "Kill Firefox",
    enable_mask: SYSRQ_ENABLE_BOOT
};


static int __init
_sysrqff_init (void) {
    int exitcode = 1;

    TRACE_ENTRY;

    printk("Hello, world!");

    register_sysrq_key('x', &firekill_op);

    exitcode = 0;

    goto exit;

exit:
  TRACE_EXIT;
    return exitcode;
}

module_init(_sysrqff_init);

static void __exit
_sysrqff_exit (void) {
  TRACE_ENTRY;

    printk("Goodbye, world!");

    unregister_sysrq_key('x', &firekill_op);

  TRACE_EXIT;
}

module_exit(_sysrqff_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Camille MONCELIER");
MODULE_DESCRIPTION("Kill firefox via a Sysrq");
MODULE_VERSION("printk");
