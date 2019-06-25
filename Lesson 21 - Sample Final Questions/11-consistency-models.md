# Problem 11: Consistency Models

Consider the following sequence of operations by processors _P1_, _P2_, and _P3_ which occurred in a distributed shared memory system:

![consistency-model-diagram](https://s3.amazonaws.com/content.udacity-data.com/courses/ud923/notes/ud923-final-consistency-models.png)

Notation

- `R_m1(X) => X` was read from memory location m1 (**does not indicate where it was stored**)
- `W_m1(Y) => Y` was written to memory location m1
- Initially all memory is set to 0

Answer the following questions:

1. Name all processors (_P1_, _P2_, or _P3_) that observe causally consistent reads.
2. Is this execution causally consistent?
