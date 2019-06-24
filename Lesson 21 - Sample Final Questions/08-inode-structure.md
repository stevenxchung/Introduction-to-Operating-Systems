# Problem 8: Inode Structure

Assume an inode has the following structure:

![Inode Structure](https://s3.amazonaws.com/content.udacity-data.com/courses/ud923/notes/ud923-final-inodes.png)

Also assume that each **block pointer element is 4 bytes**.

If a block on the disk is 4 kB, then what is the **maximum file size** that can be supported by this inode structure?

A: About 4 TB when we take into account addresses of first 12 disk blocks and single, double, and triple indirect.
