/*
 * Copyright (c) 2016 Kaprica Security, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <cstdlib.h>
#include <cstring.h>
#include "playlist.h"
#include "tag_and_file.h"
#include "print.h"

#define MAX_USER_PLAYLISTS 10
#define SECRET_PAGE_SIZE 4096

unsigned int g_song_idx = 0;

bool RecvNewSong(tag_and_file *new_song)
{
    new_song->file = new MgcFile();
    if (new_song->file->ReadMgcFile(stdin))
    {
        fflush(stdout);
        if (fread(&new_song->tag, new_song->tag.header_size(), stdin) != new_song->tag.header_size())
        {
            delete new_song;
            return false;
        }
        new_song->tag.id = g_song_idx++;
        return true;
    }

    return false;
}

void PrintPlaylist(Playlist *playlist, unsigned int playlist_id)
{
    if (!playlist)
        return;

    printf("Playlist ID: " ESC "d" NL, playlist_id);
    printf("Number of songs added to playlist: " ESC "d" NL, playlist->length());
    fflush(stdout);
}

extern "C" int __attribute__((fastcall)) main(int secret_page_i, char *unused[])
{
    unsigned char *secret_page = (unsigned char *)secret_page_i;
    /* If you want to obfuscate input/output, uncomment and change */
    fxlat(stdin, "393748225");
    fxlat(stdout, "393748225");

    unsigned int remix_idx;
    remix_idx = secret_page[2];
    fbuffered(stdout, 1);

    printf("--One Amp--" NL);
    printf(NL NL);
    fflush(stdout);

    Playlist *master = new Playlist();
    Playlist *selected_playlist = master;
    Playlist *user_playlists = new Playlist[MAX_USER_PLAYLISTS];
    unsigned int num_playlists = 0;

    char input[1024];
    int exit_program = false;
    int choice = 0;
    while(!exit_program)
    {
        printf("Main Menu:" NL);
        if (selected_playlist == master)
        {
            printf("1. Add Song To Library" NL);
            printf("2. Delete Song From Library" NL);
            printf("3. Select Playlist" NL);
        }
        else
        {
            printf("1. Add Song To Playlist" NL);
            printf("2. Delete Song From Playlist" NL);
            printf("3. Return to Main Library" NL);
        }
        printf("4. List Songs" NL);
        printf("5. Sort By Song ID (Default Sort)" NL);
        printf("6. Sort By Song Title" NL);
        printf("7. Sort By Artist and Album" NL);
        printf("8. Sort By Artist and Song Title" NL);
        printf("9. Sort By Album" NL);
        printf("10. Sort By Album and Song Title" NL);
        printf("11. Remix Track" NL);
        if (selected_playlist == master)
        {
            printf("12. Create Playlist" NL);
            printf("13. Delete Playlist" NL);
            printf("14. List Playlists" NL);
            printf("15. Exit" NL);
        }
        else
        {
            printf("12. List All Songs In Library" NL);
            printf("13. Exit" NL);
        }

        printf("[::]  ");
        fflush(stdout);

        if (freaduntil(input, sizeof(input), *NL, stdin) < 0)
            break;
        if (*input == 0)
            continue;
        choice = strtol(input, NULL, 10);
        if (choice == 1 && selected_playlist == master)
        {
            tag_and_file new_song;
            if (RecvNewSong(&new_song) && master->AddSong(&new_song))
                printf("Added song to library" NL);
            else
                printf("Could not add song to library" NL);
            fflush(stdout);
        }
        else if (choice == 2 && selected_playlist == master)
        {
            tag_and_file song_to_remove;
            printf("Enter Song ID to delete from library" NL);
            printf("[::] ");
            fflush(stdout);

            if (freaduntil(input, sizeof(input), *NL, stdin) <= 0)
                continue;
            unsigned int song_id = strtol(input, NULL, 10);
            if (master->RemoveSong(song_id, &song_to_remove))
            {
                for (unsigned int i = 0; i < num_playlists; i++)
                    user_playlists[i].RemoveSong(song_id, (tag_and_file *)NULL);

                delete song_to_remove.file;
                printf("Successfully removed song from library" NL);
            }
            else
            {
                printf("Could not remove song from library" NL);
            }
            fflush(stdout);

        }
        else if (choice == 3 && selected_playlist == master)
        {
            printf("Select Playlist ID" NL);
            printf("[::] ");
            fflush(stdout);

            if (freaduntil(input, sizeof(input), *NL, stdin) <= 0)
                continue;
            unsigned int playlist_id = strtol(input, NULL, 10);
            if(playlist_id < num_playlists)
                selected_playlist = &user_playlists[playlist_id];
            else
                printf("Bad Playlist ID" NL);
            fflush(stdout);
        }
        else if (choice == 1)
        {
            printf("Enter Song ID to add to playlist" NL);
            printf("[::] ");
            fflush(stdout);

            if (freaduntil(input, sizeof(input), *NL, stdin) <= 0)
                continue;
            unsigned int song_id = strtol(input, NULL, 10);
            tag_and_file *playlist_song = master->GetSong(song_id);
            tag_and_file *song_already_added = selected_playlist->GetSong(song_id);
            if (playlist_song && !song_already_added && selected_playlist->AddSong(playlist_song))
                printf("Added song to playlist" NL);
            else
                printf("Could not add song to playlist" NL);
            fflush(stdout);
        }
        else if (choice == 2)
        {
            printf("Enter Song ID to delete from playlist" NL);
            printf("[::] ");
            fflush(stdout);

            if (freaduntil(input, sizeof(input), *NL, stdin) <= 0)
                continue;
            unsigned int song_id = strtol(input, NULL, 10);
            if (selected_playlist->RemoveSong(song_id, (tag_and_file *)NULL))
                printf("Successfully removed song from playlist" NL);
            else
                printf("Could not remove song from playlist" NL);
            fflush(stdout);

        }
        else if (choice == 3)
        {
            selected_playlist = master;
        }
        else if (choice == 4)
        {
            selected_playlist->ListAllSongs();
        }
        else if (choice == 5)
        {
            selected_playlist->SortById();
            printf("Successfully sorted list by Song ID" NL);
            fflush(stdout);
        }
        else if (choice == 6)
        {
            selected_playlist->SortByTitle();
            printf("Successfully sorted list by Song Title" NL);
            fflush(stdout);
        }
        else if (choice == 7)
        {
            selected_playlist->SortByArtistAndAlbum();
            printf("Successfully sorted list by Artist Name and Album" NL);
            fflush(stdout);
        }
        else if (choice == 8)
        {
            selected_playlist->SortByArtistAndTitle();
            printf("Successfully sorted list by Artist Name and Song Title" NL);
            fflush(stdout);
        }
        else if (choice == 9)
        {
            selected_playlist->SortByAlbum();
            printf("Successfully sorted list by Album" NL);
            fflush(stdout);
        }
        else if (choice == 10)
        {
            selected_playlist->SortByAlbumAndTitle();
            printf("Successfully sorted list by Album and Song Title" NL);
            fflush(stdout);
        }
        else if (choice == 11)
        {
            printf("Enter Song ID to remix" NL);
            printf("[::] ");
            fflush(stdout);

            if (freaduntil(input, sizeof(input), *NL, stdin) <= 0)
                continue;
            unsigned int song_id = strtol(input, NULL, 10);
            tag_and_file *song = selected_playlist->GetSong(song_id);
            if (song)
            {
                printf("Original Track Data:" NL);
                song->file->PrintFrameData();
                unsigned int secret_page_size = SECRET_PAGE_SIZE;
                song->file->Remix(secret_page, &remix_idx, secret_page_size);
                printf("Successfully remixed song" NL);
                printf("Printing New Track Data:" NL);
                song->file->PrintFrameData();
            }
            else
            {
                printf("Could not remix track" NL);
            }
            fflush(stdout);
        }
        else if (choice == 12 && selected_playlist == master)
        {
            if(num_playlists < MAX_USER_PLAYLISTS)
            {
                user_playlists[num_playlists].ClearPlaylist(true);
                printf("Created a new playlist with ID [" ESC "d]" NL, num_playlists++);
            }
            else
            {
                printf("Maximum number of playlists reached" NL);
            }
            fflush(stdout);
        }
        else if (choice == 13 && selected_playlist == master)
        {
            printf("Enter Playlist ID to delete");
            printf("[::] ");
            fflush(stdout);

            if (freaduntil(input, sizeof(input), *NL, stdin) <= 0)
                continue;
            unsigned int playlist_id = strtol(input, NULL, 10);
            if(playlist_id < num_playlists)
            {
                user_playlists[playlist_id].ClearPlaylist(true);
                if (playlist_id < num_playlists - 1)
                {
                    memmove(&user_playlists[playlist_id], &user_playlists[playlist_id+1],
                            sizeof(user_playlists[0]) * (num_playlists - (playlist_id+1)));
                }
                --num_playlists;
                user_playlists[num_playlists].ClearPlaylist(false);
                printf("Deleted Playlist ID: " ESC "d" NL, playlist_id);
            }
            else
            {
                printf("Bad Playlist ID" NL);
            }
            fflush(stdout);
        }
        else if (choice == 14 && selected_playlist == master)
        {
            for (unsigned int i = 0; i < num_playlists; i++)
                PrintPlaylist(&user_playlists[i], i);
        }
        else if (choice == 15 && selected_playlist == master)
        {
            exit_program = true;
        }
        else if (choice == 12)
        {
            master->ListAllSongs();
        }
        else if (choice == 13)
        {
            exit_program = true;
        }
    }

    printf("--Exited One Amp--" NL);
    fflush(stdout);

    return 0;
}
