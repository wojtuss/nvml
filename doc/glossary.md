---
title: "(lib)pmempool Glossary"
description: "Glossary of terms used in (lib)pmempool"
keywords: "libpmempool, pmempool, terms, definitions, glossary"
---

## part file

a regular file or a device DAX being a media for a [part](#part)

## part

a building block of a [replica](#replica); consists of data and metadata which
are stored in a single [part file](#part file)

## replica

a set of connected [parts](#part); provides a [pool](#pool)

## poolset

a set of connected [replicas](#replica); all the replicas but the first one
serve as a backup for the [master replica](#master replica)

## pool
a continuous area of memory exposed by a single [replica](#replica); it is
comprised of memory areas from mapped data of the [replica](#replica)'s
[parts](#part)

## part's size

amount of data that can fit in the [part](#part); equals the size of the
[part file](#part file) minus the size of the metadata, rounded down to the
pagesize

## replica's size

maximum capacity of a [replica](#replica); equals the sum of all the
[replica](#replica)'s [parts's sizes](#part size)

## poolset's size

maximum capacity of a [poolset](#poolset); equals the minimum of sizes of all
[replicas' sizes](#replica's size) comprising the [poolset](#poolset)

## replica's poolsize

current size of a [pool](#pool) exposed by the [replica](#replica)

## poolset's poolsize

current size of the [master pool](#master pool)

## master pool

a [pool](#pool) exposed by the [master replica](#master replica)

## master replica

the first [replica](#replica) in a [poolset](#poolset)

## poolset file

a text file describing the structure of a [poolset](#poolset)

