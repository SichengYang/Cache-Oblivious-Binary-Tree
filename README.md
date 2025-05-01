# Cache-Oblivious-Binary-Tree

/// This is self-balancing binary tree structure that supports efficient insertion, deletion, search, and scan (via the iterator)
/// operations. Our group review the papers about the B-Tree and implement this data structure. Unlike the common tree on the internet,
/// we use a custom pack memory array to store the data in a contiguous block of memory. This is done to improve cache performance and
/// reduce memory transfers.