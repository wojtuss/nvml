---
title: "libpmemlot Glossary"
description: "Glossary of terms used in libpmemlot"
keywords: "libpmemlot, pmemlot, terms, definitions, glossary"
---

## part

a building block of a [replica](#replica); consists of metadata and data which
are stored in a single [part file](#part file)

## part file

a regular file or a device DAX being a media for a [part](#part)

## part's size

amount of data that can fit in the [part](#part); equals the size of the
[part file](#part file) minus the size of the metadata, rounded down to the
pagesize

## replica

a set of connected [parts](#part); provides a [lot](#lot)

## lot
a continuous area of memory exposed by a single [replica](#replica); it is
comprised of memory areas from mapped data of the [replica](#replica)'s
[parts](#part)

## pool
a continuous area of memory developed by libpmemobj/blk/log in a [lot](#lot)

## replica's size

size of a [lot](#lot) exposed by the replica; it determines the maximum capacity
of the [replica](#replica)

## replica's poolsize

current size of a [pool](#pool) stored in the [lot](#lot) exposed by the
[replica](#replica)

## repset

a set of connected [replicas](#replica); all the replicas but the first one
serve as a backup for the [master replica](#master replica)

## repset's size

maximum capacity of a [repset](#repset); equals the minimum of sizes of all
lots exposed by [replicas](#replica) comprising the [repset](#repset)

## repset's poolsize

current size of a [pool](#pool) stored in the [master lot](#master lot)

## master replica

the first [replica](#replica) in a [repset](#repset)

## master lot

a [lot](#lot) exposed by the [master replica](#master replica)

## master pool

a [pool](#pool) stored in the [master lot](#master lot)

## repset file

a text file describing the structure of a [repset](#repset)

