# Printer (KPRCA\_00060)

### DARPA performer group
Kaprica Security (KPRCA)

## Description

Simple Printer Protocol. The service acts like a printer service, but obviously doesn't really print things. All of data are parsed, but most of them are left unused -- except for few fields used in queue state report.

### Feature List


```
- Print jobs
- Receive print jobs
- Manage print jobs (via control files)
- See queue state
- Remove jobs
```


## Vulnerability

### Vuln 1
- One of the control subcommands is not securely handled.
- Specifically, a user-provided argument to the **'T'** (title for the document banner) control subcommand is used without the validity check on its length, causing a heap buffer overflow.
- The overflow happens inside of _job_t_ structure, which is located inside of a _printer_t_ structure as part of an array. Right next to the array of jobs is a function pointer for _'tick'_ function.
- By carefully choosing the _job_id_ and title data, it is possible to achieve an arbitrary code execution.

#### Generic class of vulnerability

Buffer Overflow

#### CWE classification

CWE-122: Heap-based Buffer Overflow

#### Challenges

- There are many possible subcommands available for control file. There is one case that isn't properly guarded.

#### Difficulty

 - **Discovery**: easy
 - **Proving**: medium
 - **Patching**: medium
