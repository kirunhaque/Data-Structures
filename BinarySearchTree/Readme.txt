


Name: Kirun Haque

-----------------------------------------------

Please confirm that you compiled your solution with test cases exercising ALL
functions using g++ -std=c++11.  Confirm this statement by typing YES below.
(If you did not do this, compilation errors may result in an overall grade of
zero!)


Yes, I did that but it had warnings and I think it was from the test cases.



Describe what augmentations to the bst data structures you made to complete the 
project -- i.e., what types / data members did you change and why?



I just added numLeft and numRight in the node struct to keep track of each subtree size.


-----------------------------------------------
Which functions did you need to modify as a result of the augmentations from the previous
question?  



I needed to modify insert and remove node to update the book-keeping and the .




-----------------------------------------------
For each function from the previous question, how did you ensure that the (assymptotic) runtime 
remained the same?



I just incremented and decremented the book-keeping accordingly so it really didn't effect the runtime I wanted to have. 




-----------------------------------------------
For each of the assigned functions, tell us how far you got using the choices 0-5 and
answer the given questions.  


0:  didn't get started
1:  started, but far from working
2:  have implementation but only works for simple cases
3:  finished and I think it works most of the time but not sure the runtime req is met. 
4:  finished and I think it works most of the time and I'm sure my design leads to 
       the correct runtime (even if I still have a few bugs).
5:  finished and confident on correctness and runtime requirements


to_vector level of completion:  _____5______  


-----------------------------------------------
get_ith level of completion:  ______5_____  

    How did you ensure O(h) runtime?

    ANSWER: I used recursion and a lot of drawing out corner cases. And book-keeping was the key to meeting the runtime requirements.

-----------------------------------------------
num_geq level of completion:  _______5____  

    How did you ensure O(h) runtime?

    ANSWER:	I used recursion and a lot of drawing out corner cases. And book-keeping was the key to meeting the runtime requirements.

-----------------------------------------------
num_leq level of completion:  ______5______

    How did you ensure O(h) runtime?

    ANSWER: I used recursion and a lot of drawing out corner cases. And book-keeping was the key to meeting the runtime requirements.

-----------------------------------------------
num_range level of completion:  _____5_______

    How did you ensure O(h) runtime? 

    ANSWER: I used recursion and a lot of drawing out corner cases. And book-keeping was the key to meeting the runtime requirements. And I called geq function and made another helper function.

-----------------------------------------------
Implementation of size-balanced criteria according to 
the given guidelines (including bst_sb_work):

    Level of completion: _____5 for insert and 4 for delete______


Write a few sentences describing how you tested your solutions.  Are there
any tests that in retrospect you wish you'd done?

I wrote a cout statements to test my functions and to see if the output was what I wanted it to be.
In retrospect, I wished I test my program with more unbalanced binary trees to be 100% confident that my functions are working.









