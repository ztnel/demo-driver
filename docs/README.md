# Device Driver Development Primer

![img](/docs/img/dd.jpg)

## Device Driver

The main features of a device driver are:
1. Peripheral I/O management.
2. Transparent device management, avoiding low-level programming (ports).
3. Improve I/O speed to a device (since it provides code optimized for that device)
4. Software and hardware error management.
5. Provides concurrent access to the hardware by several processes.

## Implementation
Reasons for Writing a Device Driver:
1. To solve concurrency problems when two or more processes try to access a device at the same time.
2. To use hardware interrupts: as the kernel runs in protected mode, the user cannot manage interrupts directly from a program.
To handle other unusual applications, such as managing a virtual device (a RAM disk or a device simulator).
3. To learn about the internal parts of the system.

Reasons against Writing a Device Driver:
1. It requires a good deal of mental preparation.
2. It requires low-level programming, i.e., direct management of ports and interrupt handlers.
3. In the debug process, the kernel hangs easily, and it is not possible to use debuggers or C library functions such as printf.

There are two ways of implementing a Linux device driver:
1. Compile the driver along with the kernel (static kernel extension)
2. Implement the driver as a kernel module (dynamic kernel module service) which does not require a recompilation of the kernel.

### Dynamic Kernel Module
I will focus on developing a kernel module. Kernel modules are particularily constructed object files written in C or assembly. Linux links kernel modules to the kernel by loading them into the kernels address space on initialization. One big advantage is the fault tolerance the kernel has for kernel modules. If a kernel module encounters a non-critical error, the kernel can simply unload the module and will not generally cause kernel panic.

> Note that the kernel and all loaded modules are a single program and thus share a global namespace. When we write a kernel module we must be cognisant about our exported names. All exported names must be unique and kept brief. To avoid collisions it is common to prefix the name of the module that is exporting the name as the prefix for a global name.

## Types of Device Drivers

### Character Drivers
Character drivers pass data byte by byte as they are received. These are super low latency drivers. The best example of a chracter driver is the computer memory device (`/dev/mem`)
![character](/docs/img/character.jpg)

### Block Drivers
Block drivers transmit information in chunks of data rather than byte by byte. This increases latency but improves CPU utilization efficiency. Incoming data is stored in a buffer until it is full and then is sent out. Examples of this type of driver are disks such as SCSI hard disks (/dev/sd1).
![block](/docs/img/block.jpg)

### Terminal Drivers
Terminal drivers a a subset of character drivers which specialize on user communication. These drivers provide special functions that handle command tools in a terminal instance. Examples of block drivers are `/dev/tty0` or `/dev/ttya` (a serial port).
![terminal](/docs/img/terminal.jpg)

### Stream Drivers
Design pattern for high throughput, low latency data transfer. Examples are networking devices.
![stream](/docs/img/stream.jpg)


## References
https://www.linuxjournal.com/article/2476 \
https://www.apriorit.com/dev-blog/195-simple-driver-for-linux-os