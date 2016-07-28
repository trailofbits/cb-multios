# REDPILL Challenge Binary

## Author Information

"Narf Industries" <info@narfindustries.com>

### DARPA performer group

Narf Industries (NRFIN)

## Description

As part of their most recent harebrained scheme for world domination, the megalomaniacal mice duo are making an effort to corner the hamster wheel market by DRM-ing hamster wheels, limiting their use to approved hamster wheel stands.  Their DRM scheme is implemented in software.

Most lab rats have become complacent with hamster wheel DRM schemes, falling prey to the convenience offered in exchange for relinquishing control over hardware they've purchased.

There are pockets of resistance.  Having already paid for your hamster wheel, you feel you are entitled to use whatever stand you desire and to overclock and enable hidden hamster wheel features.  In order to do so, you must root your hamster wheel to regain control of your hardware.

### Feature List

This CB emulates the recent Linux kernel privilege escalation vulnerability reported by comex / Pinkie Pie (Nicholas Allegra) and "proved vulnerable" by geohot / tomcr00se (George Hotz) in Towelroot, providing initial root access on many Android devices.

The vulnerability (CVE-2014-3153) lies in the Linux futex ("Fast Userspace Mutex") syscall interface.  Futexes are used by glibc (and others) to implement locking primitives across threads and processes.  The vulnerability was considered particularly severe due to its accessibility within sandboxed environments.  The interface cannot be easily restricted via e.g. seccomp_bpf() because its availability is expected and relied upon in widespread code.

Specifically, certain futex calls trigger a "requeue" of a futex from one queue to another.  When the same futex is provided twice during such requeueing calls (once as "source", once as "destination"), the syscall interface fails to properly distinguish between its internal tracking of the two futexes, resulting in a situation wherein one of the references may remain on the PI queue while the other is properly disposed of.  The futex that remains on the queue becomes a dangling pointer to stack memory.  The contents of this stack memory can be controlled via recursion into blocking syscalls.

This CB seeks to emulate the futex() bug.  REDPILL is designed as a single "kernel" CB with 5 CBs acting as "userspace threads".  Interactions between the kernel and userspace threads put the kernel's priority inversion queue (simplified as a doubly-linked list) into a vulnerable state.

Proof of vulnerability requires the CRS to cause stack recursion such that a pointer resides at a memory address previously populated with a futex struct.  A crash occurs during a dereference of this vulnerability, triggered through accesses to the dangling futex pointer.

cb_1: "kernel": 
* Provides syscall interface to CRS, tells userspace threads to do things.
* Tracks overall system state.
* Vulnerability contained here.

cb_2 - cb_6: "userspace threads": 
* ACKs instructions from the kernel (necessary to move kernel state forward).
* All CBs are identical in all ways but their names, implemented in a single file (lib_threads/threads.c).

### Relation to CVE-2014-3153 and Real-World Exploitation

This CB attempts to remain true to the _vulnerability_ details of CVE-2014-3153 but does not attempt to recreate all the constraints necessary for real-world "vulnerability proving" of the flaw, as demonstrated in tools such as Towelroot.

Below are specific comparisons between REDPILL and real-world conditions:
* The CRS issues "syscalls" to REDPILL's "kernel" (the only CB that listens for CRS input).  The CRS never speaks directly to the "userspace threads" (the other CBs).  This emulates real-world mechanisms that pass data between threads by way of the kernel, e.g. sendmsg().
* By presenting a "syscall" interface to CRSs, a local attacker's position is emulated, mirroring real-world scenarios.
* The DECREE framework does not support preemptive threading due in part to a lack of signal() capability.  Even if such functionality were offered, proper threading is likely difficult to reason about autonomously - and in a manner that detracts from vulnerability discovery.  Instead, threads are emulated as separate processes, utilizing DECREE's IPC mechanisms.
* When necessary, the kernel sends instructions to the userspace threads (the other CBs) and waits for receipt ACKnoowledgements, only advancing internal kernel state upon receipt.  REDPILL is therefore a cooperative emulation of multiple threads - and is somewhat trusting of userspace data, rather than a preemptive one that treats userspace with a healthy dose of skepticism.  In other words, the "kernel" thread is not privileged in any way relative to the "userspace" threads, unlike real-world scenarios - but this difference doesn't detract from the fidelity of the vulnerability.
* By only advancing internal kernel state in response to userspace ACKs, REDPILL requires CRSs to reason (to some extent) about IPC interactions.  In the specific case of telling a thread to sleep (FUTEX_WAIT) and then getting a verification it had done so, REDPILL is roughly analogous to Towelroot's method of checking whether a thread has been put into a waiting state by reading "voluntary_ctxt_switches" from /proc/self/tasks/<pid>/status.
* Tools like Towelroot use setpriority() to influence linked list positioning in kernelspace for subsequent "vulnerabilty providing".  Given that CVE-2014-3153 can be triggered without this functionality, such functionality has not been offered to the CRSs in REDPILL.  Instead, REDPILL's doubly-linked list is only pushed to or removed from, simplifying the reasoning problem that is orthogonal to vulnerability discovery.
* Real-world "vulnerability proving" of the futex() bug requires the ability to consume a chosen amount of stack space to cause an overwrite of the target members of a dangling PI queue entry.  Towelroot accomplishes this by consuming process kernel stack via blocking sendmsg(), sendmmsg(), recvmsg() and recvmmsg() calls.  In an effort to emulate this interface without introducing undue CB complexity, REDPILL provides a simpler interface for consuming stack data beneath the dangling list entry.  REDPILL provides the CRS with an interface to cause a controllable amount of recursion into a single sendmsg() call.  Within this sendmsg() call, a CRS-chosen byte is memset() to a stack buffer - which will overlap with the dangling list entry.  Proper emulation would necessitate a multi-threaded kernel, which in the DECREE framework would be exceedingly complex (think CB "thread groups") and likely unsolvable for CRSs.  More importantly, it would be arguably more difficult to autonomously solve than real-world conditions.  This interface is further simplified by not requiring blocking threads to ACKnowledge receipt of the sendmsg() syscall, facilitating arbitrary kernel stack consumption without IPC.
* CVE-2014-3153 was caused by an improper return from the futex() syscall without first unlinking what was supposed to be a temporary priority queue entry.  The vulnerable interaction in the Linux kernel is triggered via combination of FUTEX_CMP_REQUEUE_PI and FUTEX_WAIT_REQUEUE_PI futex() calls.  REDPILL simplifies this complex interaction by allowing the CRS to put the CB into an inconsistent state with a single syscall (referred to as FUTEX_CMP_REQUEUE_PI) and allowing the CRS to trigger a crash with this bad state via a subsequent syscall that is stateless relative to the FUTEX_CMP_REQUEUE_PI syscall.  Furthermore, it was deemed that autonomous reasoning about one doubly-linked list is not marked different from reasoning about two.  If competitors can accomplish the former, they can probably accomplish the latter.  Therefore, only one linked list is presented to CRSs and the conditions necessary to trigger the improper return from the futex() call do not demand multi-list reasoning.
* REDPILL provides an interface designed to mimic the /proc interface on Linux or a multitude of syscalls on OS X.  The kernel's internal record keeping regarding thread states and the PI queue are dumped across a transmit() to the CRS.  Like many OS X (and iOS) vulnerabilities, REDPILL fails to obscure the pointers it's dumping to the CRS (which takes the role of userspace), thereby providing a KASLR defeat.  It's possible, though relatively unlikely (due to stack layout), to cause a crash during this dumping - so the provided PoV does not test via this route.  However, it does provide a relatively realistic emulation of a real-world memory leak vulnerability, which is interesting by itself.
* On a related note to the above item, because pollers cannot compute over leaked values (the XML poller spec does not allow this), the leaked values cannot actually be used as they might be in a real-world PoV that incorporates leaks into subsequent syscalls.  Furthermore, it is not safe to assume that allocations will occur in the same location each time as either Linux or libcgc can change this behavior from under us.  The pollers therefore simply consume the leaked values and ignore them.
* Like the real Linux kernel, REDPILL offers functionality that is not relevant to the vulnerable syscalls, e.g. a pause() interface that was primarily used for testing and a FUTEX_FD interface that is a no-op, just like the real world FUTEX_FD.

### Generic class of vulnerability

Use After "Free" (on the Stack)
Information Exposure

### CWE classification

416: Use After Free
200: Information Exposure

## Challenges

* Reasoning about IPC among binaries.
* Reasoning about stack usage after "free" / stale stack area.
* Reasoning about dangling pointers.
* Controlling stack consumption via function recursion.
