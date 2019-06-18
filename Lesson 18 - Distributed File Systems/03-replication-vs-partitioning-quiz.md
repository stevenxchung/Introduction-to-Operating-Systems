# Quiz 3: Replication vs Partitioning

Consider **server machines** that hold **100 files each**. Using **three** such machines, a **DFS** can be configured using **replication** or **partitioning**. Answer the following:

1. How many **total files can be stored** int he **replicated** vs the **partitioned DFS**?

2. What **percentage of the total files will be lost if one machine fails** in the **replicated** versus **partitioned DFS** (round to the nearest %)?

A: The answers are as follows,

1. There will be **100** files in replicated DFS and **300** files in partitioned DFS.
2. There will be **0** % lost in replicated DFS and **33** % lost in partitioned DFS.
