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

#include "playlist.h"
#include "compare.h"
#include "print.h"

Playlist::Playlist()
{
    length_ = 0;
    list_size_ = 0;
    playlist_ = (tag_and_file *)NULL;
}

bool Playlist::AddSong(const tag_and_file *song)
{
    if (!song || length_ >= MAX_PLAYLIST_LENGTH)
        return false;

    if (!playlist_)
    {
        list_size_ = 16;
        playlist_ = new tag_and_file[list_size_];
    }
    if (length_ == list_size_)
    {
        list_size_ *= 2;
        tag_and_file *doubled_list = new tag_and_file[list_size_];
        memcpy(doubled_list, playlist_, sizeof(tag_and_file) * length_);
        delete[] playlist_;
        playlist_ = doubled_list;
    }
    playlist_[length_++] = *song;
    return true;
}

bool Playlist::RemoveSong(const unsigned int song_id, tag_and_file *removed_song)
{
    bool found_song = false;
    unsigned int i;
    for (i = 0; i < length_; i++)
    {
        if (playlist_[i].tag.id == song_id)
        {
            if (removed_song)
                *removed_song = playlist_[i];
            found_song = true;
            break;
        }
    }

    if (found_song)
    {
        if (i < length_ - 1)
            memmove(&playlist_[i], &playlist_[i+1], sizeof(tag_and_file) * (length_ - (i+1)));
        --length_;
    }
    return found_song;
}

tag_and_file *Playlist::GetSong(const unsigned int song_id)
{
    tag_and_file *found_song = (tag_and_file *)NULL;
    for (unsigned int i = 0; i < length_; i++)
    {
        if (playlist_[i].tag.id == song_id)
        {
            found_song = &playlist_[i];
            break;
        }
    }
    return found_song;
}

void Playlist::SortById()
{
    Sort(playlist_, length_, &CompareIds);
}

void Playlist::SortByTitle()
{
    Sort(playlist_, length_, &CompareTitles);
}

void Playlist::SortByArtistAndAlbum()
{
    Sort(playlist_, length_, &CompareArtists);
    unsigned int start_idx = 0;
    char *prev_item = (char *)NULL;
    char *cur_item = (char *)NULL;
    if (length_)
        prev_item = playlist_[0].tag.artist;

    for (unsigned int i = 0; i < length_; i++)
    {
        cur_item = playlist_[i].tag.artist;
        if (memcmp(prev_item, cur_item, sizeof(playlist_[i].tag.artist) != 0))
        {
            Sort(&playlist_[start_idx], i - start_idx, &CompareAlbums);
            start_idx = i;
            prev_item = cur_item;
        }
    }
    if (length_)
        Sort(&playlist_[start_idx], length_ - start_idx, &CompareAlbums);
}

void Playlist::SortByArtistAndTitle()
{
    Sort(playlist_, length_, &CompareArtists);
    unsigned int start_idx = 0;
    char *prev_item = (char *)NULL;
    char *cur_item = (char *)NULL;
    if (length_)
        prev_item = playlist_[0].tag.artist;

    for (unsigned int i = 0; i < length_; i++)
    {
        cur_item = playlist_[i].tag.artist;
        if (memcmp(prev_item, cur_item, sizeof(playlist_[i].tag.artist) != 0))
        {
            Sort(&playlist_[start_idx], i - start_idx, &CompareTitles);
            start_idx = i;
            prev_item = cur_item;
        }
    }
    if (length_)
        Sort(&playlist_[start_idx], length_ - start_idx, &CompareTitles);
}

void Playlist::SortByAlbum()
{
    Sort(playlist_, length_, &CompareAlbums);
}

void Playlist::SortByAlbumAndTitle()
{
    Sort(playlist_, length_, &CompareAlbums);
    unsigned int start_idx = 0;
    char *prev_item = (char *)NULL;
    char *cur_item = (char *)NULL;
    if (length_)
        prev_item = playlist_[0].tag.album;

    for (unsigned int i = 0; i < length_; i++)
    {
        cur_item = playlist_[i].tag.album;
        if (memcmp(prev_item, cur_item, sizeof(playlist_[i].tag.album) != 0))
        {
            Sort(&playlist_[start_idx], i - start_idx, &CompareTitles);
            start_idx = i;
            prev_item = cur_item;
        }
    }
    if (length_)
        Sort(&playlist_[start_idx], length_ - start_idx, &CompareTitles);
}


void Playlist::ListAllSongs()
{
    for (unsigned int i = 0; i < length_; i++)
    {
        printf("Song ID: " ESC "d" NL, playlist_[i].tag.id);
        printf("Title: ");
        PRINT_ARR_CHARS(playlist_[i].tag.title, sizeof(playlist_[i].tag.title));
        printf(NL "Artist: ");
        PRINT_ARR_CHARS(playlist_[i].tag.artist, sizeof(playlist_[i].tag.artist));
        printf(NL "Album: ");
        PRINT_ARR_CHARS(playlist_[i].tag.album, sizeof(playlist_[i].tag.album));
        printf(NL "Year: " ESC "d" NL, playlist_[i].tag.year);
        printf("Track #: " ESC "d" NL, playlist_[i].tag.track_number);
        printf("----------" NL);
    }
}

void Playlist::ClearPlaylist(bool delete_playlist)
{
    if (delete_playlist && playlist_)
        delete[] playlist_;

    playlist_ = (tag_and_file *)NULL;
    length_ = 0;
    list_size_ = 0;
}

unsigned int Playlist::length()
{
    return length_;
}

//Private Functions
void Playlist::Sort(tag_and_file *playlist, unsigned int length, int (*compare_fn)(tag_and_file *playlist1, tag_and_file *playlist2))
{
    tag_and_file *duped_list = new tag_and_file[length];
    SortHelper(playlist, duped_list, 0, length, compare_fn);
    delete[] duped_list;
}

void Playlist::SortHelper(tag_and_file *playlist, tag_and_file *duped_list, unsigned int start_idx, unsigned int end_idx,
                    int (*compare_fn)(tag_and_file *playlist1, tag_and_file *playlist2))
{
    if (end_idx - start_idx < 2)
        return;

    int mid_idx = (end_idx + start_idx) / 2;
    SortHelper(playlist, duped_list, start_idx, mid_idx, compare_fn);
    SortHelper(playlist, duped_list, mid_idx, end_idx, compare_fn);

    int left_idx = start_idx;
    int right_idx = mid_idx;

    for (unsigned int i = start_idx; i < end_idx; i++)
    {
        if (left_idx < mid_idx)
        {
            if (right_idx  >= end_idx || compare_fn(&playlist[left_idx], &playlist[right_idx]) <= 0)
                duped_list[i] = playlist[left_idx++];
            else
                duped_list[i] = playlist[right_idx++];
        }
        else
        {
            duped_list[i] = playlist[right_idx++];
        }
    }
    memcpy(&playlist[start_idx], &duped_list[start_idx], (end_idx - start_idx) * sizeof(playlist[0]));
}

