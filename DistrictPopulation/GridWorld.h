
#ifndef _GRID_WORLD_H
#define _GRID_WORLD_H

#include <vector>
#include <iostream>
using std::vector;

class GridWorld {
private:
    // private stuff goes here!
    //   typedefs
    //   data members
    //   private helper functions
    //   etc.
    
    //change to doubley linked list later
    struct Node{
        int _id;
        Node *next;
        Node *previous;
        
        Node(int idConstrutor = 0, Node *n = nullptr, Node *p = nullptr){
            _id = idConstrutor;
            next = n;
            previous = p;
        }
    };
    
    //struct for each individual person
    struct person{
        int _id;        //indentity,
        int row,col;      //which district person resides
        bool alive;       //person alive?
        Node *pointerNode;    //pointer to for move and death functions without traversing list
    };
    
    //make a district struct the 2d array type is district
    //doubley linked list for each district
    struct district {
        int _id;
        Node *front;
        Node *back;
        int districtPop;

        district(){
            front = nullptr;
            back = nullptr;
            districtPop = 0;
        }
       
        //When moving node to another district push the node to another list
        void push_back(Node* moveNode)
        {
            moveNode->next = nullptr;
            moveNode->previous = back;
            if (front == nullptr){
                front = back = moveNode;
            }
            else{
                back->next = moveNode;
                back = moveNode;

            }
        }
        
        //push back node that only holds id number. This list will come district
        Node* push_back(int _id)
        {
            Node *newNode = new Node(_id);
            push_back(newNode);
            return newNode;
            
        }
        
        //pop the node from the dead pool function
        Node* pop_front()
        {
            Node *tmp;
            tmp = front;
            if (front == nullptr){
                return nullptr;
            }
            front = front->next;
            if (front == nullptr){
                back = nullptr;
            }
            return tmp;
        }
        
        //pointer that is pointing at the node from the people vector
        void deleteNode(Node* pointerNode){
          
            //check if the first node is to be deleted and update the front/previous pointers
            if(pointerNode->previous == nullptr){
                front = pointerNode->next;
            }
            else if (pointerNode->previous != nullptr){
                pointerNode->previous->next = pointerNode->next;
            }
            //check if the last node is to be deleted and update the back/next pointers
            if (pointerNode->next == nullptr){
                back = pointerNode->previous;
            }
            else if (pointerNode->next != nullptr){
                pointerNode->next->previous = pointerNode->previous;
            }
            
            //free(pointNode->next);
            //free(point->previous);
    
            pointerNode->next = nullptr;
            pointerNode->previous = nullptr;
        }
        
    };
    
    //Set private members that will be used a lot for this program
    int nrows;              //object row size
    int ncols;              //object col size
    int worldPop;           //object population size (world population size)
    district **initGrid;    //initialize 2d array for the world
    vector<person> people;  //make a vector with the struct person type
    district deadpool;       //make a list of people who died

public:
    /**
     * constructor:  initializes a "world" with nrows and
     *    ncols (nrows*ncols districtcs) in which all
     *    districtricts are empty (a wasteland!).
     */
    GridWorld(unsigned nrows, unsigned ncols)   {
        // your constructor code here!
        this->nrows = nrows;
        this->ncols = ncols;
        worldPop = 0;
        
        initGrid = new district * [nrows];
        for(int i = 0; i < nrows; i++){
            initGrid[i] = new district[ncols];
        }
    }
    
    ~GridWorld(){
        // your destructor code here.
        for (int i = 0; i < nrows; i++){
            free(initGrid[i]);
        }
        free(initGrid);
        //find some code in program 1 or from 211
    }
    
    /*
     * function: birth
     * description:  if row/col is valid, a new person is created
     *   with an ID according to rules in handout.  New person is
     *   placed in district (row, col)
     *
     * return:  indicates success/failure
     */
    
    bool birth(int row, int col, int &id){
        //return false if district is not valid
        if (row < 0 || row >nrows ||  col < 0 || col >ncols){
            return false;
        }
        //if the deadpool is empty then make a new node
        if (deadpool.front == nullptr){
            //Create a new person with their information with person node
            id = worldPop;
            //push back node that only holds the id into the district
            Node* addNodeToDistrict = initGrid[row][col].push_back(id);
            person addPerson;
            addPerson.alive = true;
            addPerson._id = id;
            addPerson.row = row;
            addPerson.col = col;
            
            //pointer to the node thats in the district
            addPerson.pointerNode = addNodeToDistrict;
            //add the person node to the people vector
            people.push_back(addPerson);
            
            initGrid[row][col].districtPop++;
            worldPop++;
            return true;
        }
        //THIS MIGHT HAVE A HUGE BUG
        else{
            Node *getFristNode = deadpool.pop_front();
            id = getFristNode->_id;
            if (people[id].alive == true){
                return false;
            }
            //people[id-1].alive??
            people[id].alive = true;
            people[id].row = row;
            people[id].col = col;
            
            //push id into the district linked list
            Node* addNodeToDistrict = initGrid[row][col].push_back(id);
            people[id].pointerNode = addNodeToDistrict;
            
            initGrid[row][col].districtPop++;
            worldPop++;
            return true;
        }
      //  return false;
    }
    
    /*
     * function: death
     * description:  if given person is alive, person is killed and
     *   data structures updated to reflect this change.
     *
     * return:  indicates success/failure
     */
    bool death(int personID){
        
        if (people[personID].alive == true){
            //push id into the deadpool que
            deadpool.push_back(personID);
            //change the person's id status
            people[personID].alive = false;
            //get the node that pointing at in the district list
            Node* getNode = people[personID].pointerNode;
            //find which district the person lives so I can delete the node
            int personRow = people[personID].row;
            int personCol = people[personID].col;
            initGrid[personRow][personCol].deleteNode(getNode);
            
            initGrid[personRow][personCol].districtPop--;
            worldPop--;
            return true;
        }
        else{
            //there's a bug or it was the user's fault because the person is still alive
            return false;
        }
      //  return false;
    }
    
    /*
     * function: whereis
     * description:  if given person is alive, his/her current residence
     *   is reported via reference parameters row and col.
     *
     * return:  indicates success/failure
     */
    bool whereis(int id, int &row, int &col)const{
        if (people[id].alive == false){
            return false;
        }
        else{
            row = people[id].row;
            col = people[id].col;
            return true;
        }
        //return false;
    }
    
    /*
     * function: move
     * description:  if given person is alive, and specified target-row
     *   and column are valid, person is moved to specified district and
     *   data structures updated accordingly.
     *
     * return:  indicates success/failure
     *
     * comment/note:  the specified person becomes the 'newest' member
     *   of target district (least seniority) --  see requirements of members().
     */
    bool move(int id, int targetRow, int targetCol){
        
        if (targetRow < 0 || targetRow > nrows || targetCol < 0 || targetCol > ncols){
            return false;
        }
        else{
            if (people[id].alive == true){
                int oldRow = people[id].row;
                int oldCol = people[id].col;
                
                people[id].row = targetRow;
                people[id].col = targetCol;
                
                //push back id in new district location
                Node* updateDistrict = initGrid[targetRow][targetRow].push_back(id);
                
                Node * getNode = people[id].pointerNode;
                initGrid[oldRow][oldCol].deleteNode(getNode);
                
                
                initGrid[oldRow][oldCol].districtPop--;
                people[id].pointerNode = updateDistrict;
                initGrid[targetRow][targetCol].districtPop++;
            }
        }
        return true;
        
            
           /* Node * updateDistrict = initGrid[targetRow][targetCol].push_back(id);
            int oldRow = people[id].row;
            int oldCol = people[id].col;
            initGrid[oldRow][oldCol].districtPop--;

            people[id].row = targetRow;
            people[id].row = targetCol;
            
            Node* getNode = people[id].pointerNode;
            initGrid[oldRow][oldCol].deleteNode(getNode);
            
            people[id].pointerNode = updateDistrict;
            initGrid[targetRow][targetRow].districtPop++;
            return true;
            */
    }
    
    std::vector<int> * members(int row, int col)const{
        
        vector<int> *peopleDistrict = new vector<int>;
        Node* tmp = initGrid[row][col].front;
        
        while(tmp != nullptr){
            peopleDistrict->push_back(tmp->_id);
            tmp = tmp->next;
        }
        return peopleDistrict;
        //return nullptr;
    }
    
    /*
     * function: population
     * description:  returns the current (living) population of the world.
     */
    int population()const{
        return worldPop;
       // return 0;
    }
    
    /*
     * function: population(int,int)
     * description:  returns the current (living) population of specified
     *   district.  If district does not exist, zero is returned
     */
    int population(int row, int col)const{
        if (row < 0 || row > nrows || col < 0 || col > ncols){
            return 0;
        }
        return initGrid[row][col].districtPop;
    }
    
    /*
     * function: num_rows
     * description:  returns number of rows in world
     */
    int num_rows()const {
        return nrows;
        //return 0;
    }
    
    /*
     * function: num_cols
     * description:  returns number of columns in world
     */
    int num_cols()const {
        return ncols;
        //return 0;
    }
};

#endif
