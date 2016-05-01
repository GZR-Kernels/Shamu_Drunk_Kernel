#ifndef _SCHED_RT_H
#define _SCHED_RT_H

#ifdef CONFIG_SCHED_BFS
#define MAX_USER_RT_PRIO	100
#define MAX_RT_PRIO		(MAX_USER_RT_PRIO + 1)
#define DEFAULT_PRIO		(MAX_RT_PRIO + 20)

#define PRIO_RANGE		(40)
#define MAX_PRIO		(MAX_RT_PRIO + PRIO_RANGE)
#define ISO_PRIO		(MAX_RT_PRIO)
#define NORMAL_PRIO		(MAX_RT_PRIO + 1)
#define IDLE_PRIO		(MAX_RT_PRIO + 2)
#define PRIO_LIMIT		((IDLE_PRIO) + 1)
#endif /* CONFIG_SCHED_BFS */

#include <linux/sched/prio.h>
static inline int rt_prio(int prio)
{
	if (unlikely(prio < MAX_RT_PRIO))
		return 1;
	return 0;
}

static inline int rt_task(struct task_struct *p)
{
	return rt_prio(p->prio);
}

#ifdef CONFIG_RT_MUTEXES
extern int rt_mutex_getprio(struct task_struct *p);
extern void rt_mutex_setprio(struct task_struct *p, int prio);
extern void rt_mutex_adjust_pi(struct task_struct *p);
extern int rt_mutex_check_prio(struct task_struct *task, int newprio);
static inline bool tsk_is_pi_blocked(struct task_struct *tsk)
{
	return tsk->pi_blocked_on != NULL;
}
#else
static inline int rt_mutex_getprio(struct task_struct *p)
{
	return p->normal_prio;
}
# define rt_mutex_adjust_pi(p)		do { } while (0)
static inline bool tsk_is_pi_blocked(struct task_struct *tsk)
{
	return false;
}
static inline int rt_mutex_check_prio(struct task_struct *task, int newprio)
{
	return 0;
}
#endif

extern void normalize_rt_tasks(void);


/*
 * default timeslice is 100 msecs (used only for SCHED_RR tasks).
 * Timeslices get refilled after they expire.
 */
#define RR_TIMESLICE		(100 * HZ / 1000)

#endif /* _SCHED_RT_H */
