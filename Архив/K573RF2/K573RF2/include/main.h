#pragma once

typedef struct _MenuAction_
{
    const char * text;
    void (*handler)();
} MenuAction;

typedef struct _FileEntry_
{
    char    name[16];
} FileEntry;
 