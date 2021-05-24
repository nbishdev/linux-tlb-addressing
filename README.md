# On-demand paging
On-demand paging using translation lookaside buffer.

## Description
This repository contains a very simple simulation of an on-demand paging system, insipred by [Virtual Memory management](https://en.wikipedia.org/wiki/Virtual_memory) system for Linux.

This simulation aims at performing virtual to physical memory address translation, utilizing a [translation lookaside buffer (TLB)](https://en.wikipedia.org/wiki/Translation_lookaside_buffer).

We create a virtual memory space of <img src="https://render.githubusercontent.com/render/math?math=2^16"> addresses, a TLB of 16 entries, and a single-layer page table (we assume that the page table is of unlimited space).

Then, we read a series of logical addresses from the [addresses file](/files/addresses.txt) in which all addresses are stored as unsigned integer numbers and we convert then into physical addresses.

Every logical address consists of:
* an 8-bit page number
* an 8-bit offset (within the page)

After an address is read from the file, we search for it in the TLB. We consider the 2 following cases:
* <b>Page fault</b>. In this case, if the address does not exist in the page table, we open the binary [content file](/files/BACKING_STORE.bin), we read the corresponding page, we store it both in the TLB and the page table and we extract the signed byte which is stored in this physical address.
* <b>Page hit</b>. In this case, we just extract the signed byte which is stored in the corresponding physical address.

The TLB is updated using the [Least Recently Used (LRU)](https://en.wikipedia.org/wiki/Cache_replacement_policies#Least_recently_used_(LRU)) policy.

For every logical address we read from the file, we print:
* The logical address read
* The physical address to which the logical address is translated
* The signed byte which is stored in the corresponding physical address

In the end, we print the following statistics:
* The page fault ratio
* The TLB hit ratio

## Execution
In order to execute the software, use a Terminal Emulator and navigate to the src directory.

Then, to compile and build the software type the following command:
```bash
make
```

After you have successfully built the software, execute it using the following command:
```bash
./vmm DIRECTORY PAGE_TABLE_SIZE
```

where:
* DIRECTORY is the path to the directory which contains both the address file and the page file
* PAGE_TABLE_SIZE is the size of the page table and must be a positive power of 2 and at least equal to 256

For example, to execute the software using a the relative path to the default files directory and a page table of 512 frames, use the following command:
```bash
./vmm ../files 512
```
