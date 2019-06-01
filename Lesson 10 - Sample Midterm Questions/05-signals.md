# Problem 5: Signals

If the kernel cannot see user-level signal masks, then how is a signal delivered to a user-level thread (where the signal can be handled)?

A: There must exist a handler (more specifically, a ULT library handler) in between the user-level and the kernel-level such that signal masks created on the user-level can be transmitted from the user-level to the kernel-level.
