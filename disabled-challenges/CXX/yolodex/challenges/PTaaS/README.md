# PTaaS

## Author Information
"Maxwell Koo" <info@narfindustries.com>

### DARPA performer group
Narf Industries (NRFIN)

## Description
Path Tracer as a Service brings the latest in photorealistic computer graphics
to your fingertips, anywhere in the world! Our state of the art path tracing
software renders your 3D scenes into breathtaking HD...ish images. Simply
input a description of your scene consisting of a camera and spheres or planes,
and in no time a rendering of your image will be available for you to download
and enjoy.

### Feature List
This service is a path tracing program which supports a textual interface for
inputing information about a 3D scene and rendering an image of that scene into
a fixed size image in PPM format.

- Parses descriptions of 3D scenes consisting of geometric primitives
- Supports spheres and planes
- Can have either diffuse or specular reflection
- Objects can emit light

## Vulnerability 1
This program will reuse stale data from partially constructed objects while
constructing the primitives making up a scene. This will allow an attacker to
control a function pointer and register argument by overlapping this with
invalid data from another type of object.

### Generic class of vulnerability
Use after free

### CWE classification
CWE-119 Improper restriction of operations within the bounds of a memory buffer
CWE-416 Use after free
CWE-703 Improper check or handling of exceptional conditions
CWE-704 Incorrect type conversion or cast
CWE-825 Expired pointer dereference
CWE-843 Access of resource using incompatible type

### Challenges
- The textual input required by the tool requires input in a specific format,
  increasing the difficulty of reaching the vulnerable state via blind fuzzing.
- The usage of many floating point operations increases the difficulty of
  analyzing the vulnerability once found and finding how to control the inputs
  in such a way to reliably prove the vulnerability. A way to pack in the
  required values into double-values, which can then be converted to and from
  strings by the limited parsers in the binary, is needed to gain full control.
- Although the fix demonstrated in the patched version of the binary is simple,
  fixing the binary autonomously is complicated by the use of a custom tagged
  union representation for the core type of the program; the semantics of which
  increase the challenge of determining which operations are allowed or not and where the stale data is being utilized.

### Difficulty
- Discovering is medium
- Proving is hard
- Fixing is medium
