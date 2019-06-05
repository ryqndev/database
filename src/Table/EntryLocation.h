#ifndef ENTRY_LOCATION_H
#define ENTRY_LOCATION_H

struct EntryLocation{
    EntryLocation():start(0), end(0){};
    EntryLocation(unsigned start):start(start){};
    EntryLocation(unsigned start, unsigned end):start(start), end(end){};
    unsigned start;
    unsigned end;
};

#endif /* ENTRY_LOCATION_H */