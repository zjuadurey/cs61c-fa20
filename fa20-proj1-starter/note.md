attention:

when you use malloc to allocate a 2-d array, you should know:

1. free every row of the 2-d array, and finally free the pointer to the head of the 2-d array

2. 正确地申请内存（2-d array的每一行都要单独用一次malloc）