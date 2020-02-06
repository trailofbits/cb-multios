#!/usr/bin/env python

from generator.actions import Actions
import random, string

# Printer State
PS_IDLE = 0
PS_QUEUED = 1
PS_RECEIVING = 2
PS_PRINTING = 3

# Job State
JS_INVALID = 0
JS_WAITING = 1
JS_QUEUED = 2
JS_PRINTING = 3

# Mode
MODE_NORMAL = 0
MODE_RECEIVE = 1

# ACK
ACK_OK = '\x00'
ACK_FAIL = '\xFF'

NUM_MAX_JOBS = 1000
NUM_PRINTERS = 10

def random_string(size=20):
    return ''.join([random.choice(string.ascii_letters) for x in xrange(random.randint(1,size))])

def random_host():
    return '%d.%d.%d.%d' % (random.randint(0,255),random.randint(0,255),random.randint(0,255),random.randint(0,255))

class Printer(object):
    def __init__(self, queue):
        self.state = PS_IDLE
        self.queue = queue
        self.jobs = list()
        self.job_ids = list()

        for i in xrange(NUM_MAX_JOBS):
            self.jobs.append(Job())

class Job(object):
    def __init__(self):
        self.state = JS_INVALID
        self.data = None
        self.ticks = 10

        self.cls = None
        self.host = None
        self.indent = None
        self.name = None
        self.banner_flag = False
        self.banner_user = None
        self.owner = None
        self.mail_flag = False
        self.mail_user = None
        self.source = None
        self.device_num = None
        self.inode_num = None
        self.title = None
        self.width = 132
        self.fmt = None

    def __str__(self):
        if self.state == JS_INVALID:
            return "Invalid"
        elif self.state == JS_WAITING:
            return "Waiting"
        elif self.state == JS_QUEUED:
            return "Queued"
        elif self.state == JS_PRINTING:
            return "Printing"
        else:
            return "Unknown"

class APrinter(Actions):
    def start(self):
        #self.delay(100)
        def get_name(index):
            return ''.join([chr(0x41 + (ord(x) & 0x3F)) for x in self.magic_page[index*32:(index+1)*32]])
        self.mode = MODE_NORMAL
        self.cur_printer = None
        self.cur_job = None
        self.printers = list()
        for i in xrange(NUM_PRINTERS):
            name = "DEFAULT" if i == 0 else get_name(i)
            self.printers.append(Printer(name))

    def commands(self):
        pass

    def cmd_print_jobs(self):
        if self.mode == MODE_RECEIVE:
            return
        pn = random.randint(0, 9)
        printer = self.printers[pn]
        msg = '\x01' + printer.queue + '\n'
        self.write(msg)

        for i in xrange(NUM_MAX_JOBS):
            if printer.jobs[i].state == JS_QUEUED:
                printer.jobs[i].state = JS_PRINTING
                if printer.state != PS_PRINTING:
                    printer.state = PS_PRINTING

        self.read(length=len(ACK_OK), expect=ACK_OK)
        self.printer_tick()

    def cmd_recv_job(self):
        if self.mode == MODE_RECEIVE:
            return
        pn = random.randint(0, 9)
        printer = self.printers[pn]
        msg = '\x02' + printer.queue + '\n'
        self.write(msg)

        if printer.state == PS_PRINTING:
            self.read(length=len(ACK_FAIL), expect=ACK_FAIL)
            self.printer_tick()
            return
        else:
            printer.state = PS_RECEIVING
            self.read(length=len(ACK_OK), expect=ACK_OK)
        self.mode = MODE_RECEIVE
        self.cur_printer = printer
        self.printer_tick()

    def cmd_abort_job(self):
        if self.mode != MODE_RECEIVE or self.cur_printer is None:
            return
        busy = False
        printer = self.cur_printer
        for i in xrange(NUM_MAX_JOBS):
            if printer.jobs[i].state == JS_WAITING or printer.jobs[i].state == JS_QUEUED:
                printer.job_ids.remove(i)
                printer.jobs[i] = Job()
            elif printer.jobs[i].state == JS_PRINTING:
                busy = True
        if not busy:
            printer.state = PS_IDLE
        self.cur_printer = None
        self.cur_job = None
        self.write('\x01\n')
        self.read(length=len(ACK_OK), expect=ACK_OK)
        self.printer_tick()

    def cmd_send_queue_state(self):
        if self.mode == MODE_RECEIVE:
            return
        pn = random.randint(0, 9)
        printer = self.printers[pn]
        if random.randint(0, 1) == 0:
            msg = '\x03'
        else:
            msg = '\x04'
        msg += printer.queue + ' \n'
        self.write(msg)

        out = 'Queue State for %s\n\n' % printer.queue
        out += 'Owner       Status      Jobname             Job-ID      Size  \n'
        out += '==============================================================\n'
        self.read(length=len(out), expect=out)

        final = ''
        for i in xrange(NUM_MAX_JOBS):
            if printer.jobs[i].state != JS_INVALID:
                out = ''
                out += printer.jobs[i].owner[:10]
                out = out.ljust(12, ' ')
                out += str(printer.jobs[i])
                out = out.ljust(24, ' ')
                out += printer.jobs[i].source[:18] if printer.jobs[i].source else ''
                out = out.ljust(44, ' ')
                out += '%03d' % i
                out = out.ljust(56, ' ')
                out += '%d\n' % len(printer.jobs[i].data)
                final += out
        final += '\n\n'
        self.read(length=len(final), expect=final)
        self.read(length=len(ACK_OK), expect=ACK_OK)
        self.printer_tick()

    def cmd_recv_control_file(self):
        if self.mode != MODE_RECEIVE or self.cur_printer is None:
            return
        host = random_host()
        user = random_string()
        printer = self.cur_printer
        while True:
            job_id = random.randint(0, 999)
            if job_id not in printer.job_ids:
                break
        job = printer.jobs[job_id]
        job.host = host
        job.owner = user

        ctrl = 'H%s\nP%s\n' % (host, user)
        if random.randint(1, 100) <= 10:
            job.cls = random_string()
            ctrl += 'C%s\n' % job.cls
        if random.randint(1, 100) <= 10:
            job.indent = random.randint(0, 131)
            ctrl += 'I%d\n' % job.indent
        if random.randint(1, 100) <= 10:
            job.name = random_string()
            ctrl += 'J%s\n' % job.name
        if random.randint(1, 100) <= 10:
            job.banner_flag = True
            job.banner_user = job.owner
            ctrl += 'L%s\n' % job.banner_user
        if random.randint(1, 100) <= 10:
            job.mail_flag = True
            job.mail_user = job.owner
            ctrl += 'M%s\n' % job.mail_user
        if random.randint(1, 100) <= 10:
            job.source = random_string()
            ctrl += 'N%s\n' % job.source
        if random.randint(1, 100) <= 10:
            job.device_num = random.randint(0, 0xFFFFFFFF)
            job.inode_num = random.randint(0, 0xFFFFFFFF)
            ctrl += 'S%d %d\n' % (job.device_num, job.inode_num)
        if random.randint(1, 100) <= 10:
            job.title = random_string()
            ctrl += 'T%s\n' % job.title
        if random.randint(1, 100) <= 10:
            ctrl += 'UdfA%03d%s\n' % (job_id, host)
        if random.randint(1, 100) <= 10:
            job.width = random.randint(1, 132)
            ctrl += 'W%d\n' % job.width
        if random.randint(1, 100) <= 10:
            r = random.randint(1, 100)
            fname = 'dfA%03d%s' % (job_id, host)
            job.fmt = random.choice(['c','d','f','g','l'])
            ctrl += '%s%s\n' % (job.fmt, fname)

        msg = '\x02%d cfA%03d%s\n' % (len(ctrl), job_id, host)
        self.write(msg)
        self.write(ctrl)

        if job.state == JS_INVALID:
            job.state = JS_WAITING
        elif job.state == JS_WAITING:
            job.state = JS_QUEUED
        else:
            self.read(length=len(ACK_FAIL), expect=ACK_FAIL)
            self.printer_tick()
            return

        self.cur_job = job
        printer.job_ids.append(job_id)
        self.read(length=len(ACK_OK), expect=ACK_OK)
        self.printer_tick()

    def cmd_remove_jobs(self):
        if self.mode == MODE_RECEIVE:
            return
        pn = random.randint(0, 9)
        printer = self.printers[pn]
        if len(printer.job_ids) == 0:
            agent = random_string()
            job_id = random.randint(0, 999)
        else:
            agents = [x.owner for x in printer.jobs if x.state != JS_INVALID]
            agents.append('root')
            agent = random.choice(agents)
            job_id = random.choice(printer.job_ids)
            if random.randint(1, 100) <= 20:
                if random.randint(0, 1) == 0:
                    agent = random_string()
                else:
                    while True:
                        job_id = random.randint(0, 999)
                        if job_id not in printer.job_ids:
                            break
        msg = '\x05%s %s %d\n' % (printer.queue, agent, job_id)
        self.write(msg)

        if printer.jobs[job_id].state != JS_INVALID and (printer.jobs[job_id].owner == agent or agent == "root"):
            printer.jobs[job_id] = Job()
            self.read(length=len(ACK_OK), expect=ACK_OK)
        else:
            self.read(length=len(ACK_FAIL), expect=ACK_FAIL)
        self.printer_tick()

    def cmd_recv_data_file(self):
        if self.mode != MODE_RECEIVE or self.cur_printer is None:
            return
        job = self.cur_job
        job_id = self.cur_printer.jobs.index(job)

        data = random_string(500)
        msg = '\x03%d dfA%03d%s\n' % (len(data), job_id, job.host)
        self.write(msg)
        self.write(data + '\x00')

        job.data = data
        if job.state == JS_INVALID:
            job.state = JS_WAITING
        elif job.state == JS_WAITING:
            job.state = JS_QUEUED
        else:
            self.read(length=len(ACK_FAIL), expect=ACK_FAIL)
            self.printer_tick()
            return

        self.cur_printer.jobs[job_id] = job
        self.read(length=len(ACK_OK), expect=ACK_OK)
        self.printer_tick()

    def invalid(self):
        self.write(random_string() + '\n')
        self.read(length=len(ACK_FAIL), expect=ACK_FAIL)
        self.printer_tick()

    def quit(self):
        self.write('\x07\n')

    def done_recv(self):
        if self.mode != MODE_RECEIVE:
            return
        self.write('\x00\n')
        self.read(length=len(ACK_OK), expect=ACK_OK)
        self.mode = MODE_NORMAL
        self.printer_tick()

    def printer_tick(self):
        for i in xrange(NUM_PRINTERS):
            s = 0
            printer = self.printers[i]
            if printer.state == PS_IDLE:
                continue
            for j in xrange(NUM_MAX_JOBS):
                if printer.jobs[j].state != JS_PRINTING:
                    continue
                printer.jobs[j].ticks -= 1
                s += printer.jobs[j].ticks
                if printer.jobs[j].ticks == 0:
                    printer.jobs[j] = Job()
            if s == 0:
                printer.state = PS_IDLE

