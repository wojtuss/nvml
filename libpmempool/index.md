---
title: libpmempool
layout: nvml
---

#### The libpmempool library

**libpmempool** provides a set of utilities for management, diagnostics and
repair of persistent memory pools.
By pool in this context we mean pmemobj pool, pmemblk pool, pmemlog pool or
BTT layout, independent of the underlying storage.
The **libpmempool** is for applications that need high reliability or built-in
troubleshooting. It may be useful for testing and debugging purposes also.

Man pages that contains a list of the interfaces provided:

* Man page for [libpmempool current master](../manpages/master/libpmempool.3.html)
* Latest releases:
   * [libpmempool version 1.1](../manpages/v1.1/libpmempool.3.html)

#### libpmempool Examples

**More Detail Coming Soon**

<code data-gist-id='krzycz/53f5b5f33cc6bfbbd80c04a3209202d0' data-gist-file='manpage.c' data-gist-line='37-96' data-gist-highlight-line='41' data-gist-hide-footer='true'></code>

##### libpmempool transform #####

**Example 1.**

Let files `/path/poolset_file_src` and `/path/poolset_file_dst` have the
following contents:

<script src="https://gist.github.com/wojtuss/06c22e3a8340e85574cc89d767ae2534.js"></script>

<script src="https://gist.github.com/wojtuss/b9693dd0f1f8962bf01eb0791a68128a.js"></script>

Then

`pmempool_transform("/path/poolset_file_src", "/path/poolset_file_dst", 0);`

adds a replica to the poolset. All other replicas remain unchanged and
the size of the pool remains 60M.


**Example 2.**

Let files `/path/poolset_file_src` and `/path/poolset_file_dst` have the
following contents:

<script src="https://gist.github.com/wojtuss/06c22e3a8340e85574cc89d767ae2534.js"></script>

<script src="https://gist.github.com/wojtuss/f535a8ced7a34522f8b6189c9ddd7e89.js"></script>

Then

`pmempool_transform("/path/poolset_file_src", "/path/poolset_file_dst", 0);`

deletes the second replica from the poolset. The first replica remains unchanged and
the size of the pool is still 60M.


<script src="https://gist.github.com/wojtuss/5dc79d006f220353c14361a2ac57aac9.js"></script>

<code data-gist-id='wojtuss/06c22e3a8340e85574cc89d767ae2534' data-gist-file='poolset_file_src' data-gist-hide-footer='true'></code>

