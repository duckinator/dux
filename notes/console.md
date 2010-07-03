# dux-based game console #

The goal is to have an operating system suitable for gaming, as well as normal applications, and programming games.

## Design ##

Metodo (dux's kernel) with a monolithic design using cooperative multitasking, with nearly all communication would be done using interrupts and/or syscalls.
Upon booting, it would initialize everything in the HAL, scheduler being last.

### Scheduler design ###

Metodo's scheduler for the game console will use cooperative multitasking, threads in each task will be ran using a time-share design.

Quick example because I don't feel like typing up a formal explanation:

So assuming there are 1 task with one thread - task 1 is the main screen.
The main screen has 1 thread - A:

    Task:     main
               |
    Thread:    A

The user opens program, lets call it "foo." Foo has 3 threads:

    Task:     main       foo
               |        / | \
    Thread:    A       A  B C

#### Inside the thread scheduler ####
    The thread scheduler is a time-share design.
    Each thread gets a designated time slot, then the next one moves in,
    and is almost entirely isolated from the task scheduler.
    
    It will be in the design that you can trigger a particular interrupt,
    to switch to a timeshare scheduler, and vice-versa.
    
    The timeshare scheduler would be good for desktop style software.

You minimize foo, and open "bar." Task 1 (main screen) sends a signal to open "bar" and surrenders control.
Bar has 1 thread:

    Task:     main       foo      bar
               |        / | \      |
    Thread:    A       A  B C      A

Once bar (task 3) gives up control, we go back to main (task 1) until it gives up control, then go to foo (task 2) until it gives up control, then back to bar (task 3).
