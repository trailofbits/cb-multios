# One_Amp

### DARPA performer group
Kaprica Security (KPRCA)

## Description

A music manager for all your music files

### Feature List


The service supports addings songs to a master library.
That library can organize subsets of songs into 'playlists'
Operations:
    -Add Songs 
    -Delete Songs
    -Select a Playlist
    -Add Songs To Playlist(s)
    -Delete SongFrom Playlist(s)
    -List Song
    -Sort Library or Playlist(s)
    -Remix Music Track
     -Create Playlist
     -Delete Playlist
     -List Playlists
    
Songs need to conform to a specific Music File Format and are verified when being read in. Each file is proceeded by a
tag that contains information about the music track (who made it, what it's called, etc etc).

## Vulnerability
### Vuln 1
When reading a music file into the music manager there is an error when processing the bits that determine what the sampling 
frequency of the audio file is `(mgc_header_info.cc:74)`. If the frequency doens't match one of the options, it will return
the third byte of the header as the frequency. This allows the user to write a frame that's larger than the assumed largest frame
and will overwrite the frame buffer in `mgc_file.cc:ReadMgcFile`. 

#### Generic class of vulnerability

Stack Overflow

#### CWE classification

CWE-121: Stack-based Buffer Overflow

#### Challenges

- The CB requires understanding of the Music File structure in order to exploit the CB. The structure that is vulnerable is a small
    5 byte structure that requires fairly strict bit checking in order to continue processing the file.
- Once discovered the vulnerability is not very difficult to trigger, however exploiting it requires a little more finesse. Because
    of how the sampling formula is calculated the file inputted needs to choose very specfic values or the buffer created by the file
    will crash the CB.

#### Difficulty

 - **Discovery**: medium
 - **Proving**: medium
 - **Patching**: medium
