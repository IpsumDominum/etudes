Etude Number 6 Counting It Up
------------------------------
Pair Members: Chenrong Lu and Suhaib Aljehani
==============================
Report:
        So this etude was very fun, it is very
        straight forward but we ran into some
        issues. Most notably was the problem
        with a random segmentation fault occuring
        at above a seemingly random number- 181635.
        We first suspected that It was due to the
        memory allocation implementations of C++.
        However, after debugging, the problem was
        narrowed to be at the line of which
        the recursive GCD algorithm was being
        called, to factorise the secondary remainders.
        We re-implemented the recursive GCD to an
        iterative GCD, which solved the problem,
        suggesting that the problem was with
        recursion beyond the system stack.
==============================
To Run:
        First build a testfile named "test.txt"
        and put it into the directory,
        then run:
            python test_multiple.py


        
        
       
        
     