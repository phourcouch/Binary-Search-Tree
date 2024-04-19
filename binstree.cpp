// CS311 YOSHII F23 binstree.cpp
// This is the BST implementation file template by Rika Yoshii

// Each node has an Up link to make it easy to go up the tree.  It must be set as nodes are inserted.  Some deletion
// cases require Up link to be updated.  Couts are there to test to make sure
// you set the Up links correctly!!!! (Fall 19)
//
// INSTRUCTIONS:
// Look for ** comments to complete this file for HW4
// DO not delete the ** comments, but add the code next to them
// Make sure all { } match. Doing Tab on each line helps.
// Draw pictures as you complete each **
//  NEVER delete my comments!!!!
// =========================================================
//HW#: HW4 BST
//Your name: Kayla Le
//Complier:  g++
//File type: implementation file binstree.cpp
//================================================================

using namespace std;
#include "binstree.h"
#include <iostream>
//#include "binstreeEC.h"
// constructor  initializes Root
BST::BST()
{
  Root = NULL;   // This is an empty tree
}

// destructor must completely destroy the tree
BST::~BST()
{
  dtraverse(Root); // traverse to delete all vertices in post order
  Root = NULL;    
}
// PURPOSE: Does Post Order traversal of the tree and deletes each vertex
// PARAM:   V is a pointer to the vertex to be deleted
void BST::dtraverse(Vertex *V)  // recursive post order traversal
{   
  if (V != NULL) //loop through tree
    {
      dtraverse(V->Left);         // destroy left sub tree of V
      dtraverse(V->Right);       //  destroy right sub tree of V
      delete V;                  //  delete V
    }
}

// PURPOSE: Show vertices in IN order traversal from the Root
void BST::Display()
{
  cout << "--- Elements in the IN order: ---" << endl;
  cout << "Root is: " << Root->Elem << endl;
  INorderTraversal(Root);  // start in-order traversal from the root
  cout << "---------------------------------" << endl;
}
// PURPOSE: Does IN order traversal from V recursively
// PARAM: V is te pointer to the vertex to visit right now
// For non EC, the height and balance will always be 0 
void BST::INorderTraversal(Vertex *V)
{
  if (V != NULL)
    {
    INorderTraversal(V->Left); //  traverse left sub-tree of V recursively
     cout << "Vertex is: " << V->Elem << "\nVertex Height: " << V->Height << 
     "\nVertex Balance: " << V->Balance << endl;//print out vertex element, height, and balance
     INorderTraversal(V->Right); //  traverse right sub-tree of V recursively
    }
}

// PURPOSE: Searches for an element in PRE-order traversal
// This is the same as Depth First Traversal
// PARAM: K is the number the user wants to search  for in the tree
bool BST::Search(el_t K)
{
  PREorderSearch(Root, K);  // start pre-order traversal from the root
}
// PURPOSE: Does PRE order search from V recursively
// PARAM: V is the pointer to the vertex to be visited now
//        K is what we are looking for
bool BST::PREorderSearch(Vertex *V, el_t K)
{
    if (V != NULL)//loop through tree
      {
        if (K == V->Elem) return true; // found the element in V
        else if (K < V->Elem )//if key is less than vertex's elememt, go left
		 PREorderSearch(V->Left,K); // traverse left sub-tree of V recursively
	  else 
	    PREorderSearch(V->Right,K); // traverse right sub-tree of V recursively
      }
    else return false;//return false if not found in tree
}

// ------ The following are for adding and deleting vertices -----


// PURPOSE: Adds a vertex to the binary search tree for a new element 
// PARAM: the new element E
// ALGORITHM: We will do this iteratively (not recursively)
// to demonstrate the algorithm that is in the notes
//    - smaller than the current -> go to the left
//    - bigger than the current  -> go to the right
//    - cannot go any further    -> add it there
void BST::InsertVertex(el_t E)
{
  // Set up a new vertex first
   Vertex *N;         // N will point to the new vertex to be inserted
   N = new Vertex;    // a new vertex is created
   N->Left  = NULL;   // make sure it does not
   N->Right = NULL;   // point to anything
   N->Elem  = E;      // put element E in it
   N->Height = 0;
   N->Balance = 0;
   N->Up = NULL;      // no parent for now
   cout << "Trying to insert " << E << endl;

   if (Root == NULL)  // Special case: we have a brand new empty tree
     {
       Root = N;      // the new vertex is added as the root
       cout << "...adding " << E << " as the root" << endl; 
     }// end of the special case

   else  // the tree is not empty
     {
        Vertex *V;       // V will point to the current vertex
        Vertex *Parent;  // Parent will always point to V's parent

        V = Root;        // start with the root as V
        Parent = NULL;   // above V so it does not point to anything  

	// go down the tree until you cannot go any further        
	while (V != NULL)
	  {
	    if (N->Elem == V->Elem) // the element already exists
              {	 cout << "...error: the element already exists" << endl;
		return;  }
	    else{
	      if (N->Elem < V->Elem)  // what I have is smaller than V
		{  cout << "...going to the left" << endl; 
		  Parent = V; //  change Parent to be V to go down -----------------
		  V = V->Left; // change V to be V's Left ---------------------
		}
	      else // what I have is bigger than V
		{  cout << "...going to the right" << endl;
		   Parent = V; // change Parent to be V to go dow-n--------------------
		  V = V->Right; // change V to be V's Right -------------------------
		}
	    }
	  }//end of while
        
   // reached NULL -- Must add N as the Parent's child
        
        if (N->Elem < Parent->Elem)  
          {  
	   Parent->Left = N;  // Parent's Left should point to the same place as N ------------
	    cout << "...adding " << E << " as the left child of " 
		 << Parent->Elem << endl;
             N->Up = Parent;  // N must point UP to the Parent -----------------------------
             cout << N->Elem  << " now points UP to " << N->Up->Elem << endl;   
            //** EC call here to adjust height and BF	
            climbUp(N);
            }
        else 
           {
	     Parent->Right = N; // Parent's Right should point to the same place as N -------
             cout << "...adding " << E << " as the right child of " 
                  << Parent->Elem << endl;
             N->Up = Parent;// N must point UP to the Parent --------------------------
             cout << N->Elem << " now points UP to " << N->Up->Elem << endl;   
	     //** EC call here to adjust height and BF
             climbUp(N);
  	}

      }// end of normal case

}// end of InsertVertex

  
// PURPOSE: Deletes a vertex that has E as its element.
// PARAM: element E to be removed
// ALGORITHM: First we must find the vertex then call Remove 
void BST::DeleteVertex(el_t E)
{
  cout << "Trying to delete " << E << endl;
  
 Vertex *V;       // the current vertex
  Vertex *Parent;  // Parent will always point to V's parent

  // case 1: Lonely Root  --------------------
  if ((E == Root->Elem) && (Root->Left == NULL) && (Root->Right == NULL))
    { cout << "...deleting the lonely root" << endl;
      delete Root; 
      Root = NULL;
      return; }  // only the Root was there and deleted it
  
  // case 2:  One Substree Root ----------------
  if(E == Root->Elem) // if what you want to delete is the root
  { cout << "... deleting the root with just one child" << endl; 
    if(Root->Left != NULL && Root->Right == NULL && E == Root->Elem ) // and it has only the left subtree
      {  //** change the root to the left child and return
       //   making sure the old root has been deleted and the new root's UP is NULL 
       Vertex *OldRoot = Root;//temp vertex 
      delete OldRoot;//delete OldRoot
      Root = Root->Left;//change root to its left child
      Root->Up = NULL; 
     return;//returning
    }
    if(Root->Left == NULL && Root->Right != NULL && E == Root->Elem) // and it has only the right subtree
    {  // change the root to the right child and return
      //    making sure the old root has been deleted and the new root's UP is NULL 
     Vertex *OldRoot = Root;//temip vertex
      Root = Root->Right;//change root to its right  child
     delete OldRoot;//delete OldRoot
      Root->Up = NULL;//make root's up null
     return;//returning
 
    }
  }// end of deleting the root with one subtree
  
  // ---- Otherwise deleting something else  --------------
  
  V = Root;  // start with the root to look for E
  Parent = NULL;  // above the V so does not point to anything yet

  // going down the tree looking for E
  while (V != NULL)
    { 
      if ( E == V->Elem)   // found it
	{  cout << "...removing " << V->Elem << endl;
	  remove(V,Parent); // call remove here to remove V
	  return; }
      
      else{
	if (E < V->Elem)//if key is less than pointer's element go left
	  {  cout << "...going to the left" << endl;
	  Parent = V;   // update Parent and V here to go down 
	  V = V->Left;
	  }
	else//going right
	  {  cout << "...going to the right" << endl;
	  Parent = V; // update Parent and V here to go down
          V = V->Right;
	  }
	}
    }// end of while
  
  // reached NULL  -- did not find it
  cout << "Did not find the key in the tree." << endl;
  
}// end of DeleteVertex


// PURPOSE: Removes vertex pointed to by V
// PARAM: V and its parent  pointer P
// Case 1: it is a leaf, delete it
// Case 2: it has just one child, bypass it
// Case 3: it has two children, replace it with the max of the left subtree
void BST::remove(Vertex *V, Vertex *P)
{
  if(V->Left == NULL && V->Right == NULL) // if V is a leaf (case 1)
      {
	cout << "removing a leaf" << endl;
	if(P->Left == V) // if V is a left child of P
	{
	  delete V;// delete V and also make Parent's left NULL 
	P->Left = NULL;
          // ** EC call here from P to adjust height and BF  
 	climbUp(P);
	}
	else // V is a right child of the Parent
	  { 
          delete V; P->Right = NULL; // delete V and also make Parent's right NULL 
          // ** EC call from P to adjust height and BF
          climbUp(P);
	  }
      }//end of leaf case
    
   else if(V->Left != NULL && V->Right == NULL)// if V has just the left child so bypass V (case 2)
     {    Vertex* C = V->Left; // C is the left child
	  cout << "removing a vertex with just the left child" << endl;
          if(C->Elem < P->Elem )//check if left child element is less than parent's element
		P->Left  = C;//making parent's left point to the left child of deleted vertex
	else
	 P->Right = C;//mkaing parent's right point to the left child of deleted vertex
	C->Up = P;
 		
 // You need if then else to determine Parent's left or right
	  //    should point to C; 
	  
	  //
           // Make C point UP to the parent;
          cout << C->Elem << " points up to " << C->Up->Elem << endl;
	  delete V; // Be sure to delete V
          //** EC call from P to adjust height and BF
	climbUp(P);
	}// end of V with left child       
 
   else if(V->Right != NULL && V->Left == NULL) // if V has just the right child so bypass V (case 2)
     {    Vertex* C = V->Right;  // C is the right child
	  cout << "removing a vertex with just the right child" << endl;
	  if(C->Elem < P->Elem)//if right child of V element  is less than  parent's element then make parent left point to C
	      P->Left = C;
	else 
  	 P->Right = C;//parents right point to C
            
 // You need if then else to determine Parent's left or right
	  //    should point to C; 
          C->Up = P; // Make C point UP to the parent;   
          cout << C->Elem << " points up to " << C->Up->Elem << endl;
          delete V; // Be sure to delete V
          //** EC call from P to adjust height and BF 
          climbUp(P);
        }//end of V with right child
      
   else // V has two children (case 3)
	{ cout << "removing an internal vertex with children" << endl;
	  cout << "..find the MAX of its left sub-tree" << endl;
	  el_t Melem;
	  // find MAX element in the left sub-tree of V
          Melem = findMax(V); 
          cout << "..replacing " << V->Elem << " with " << Melem << endl;
          V->Elem = Melem; // Replace V's element with Melem here
        }//end of V with two children
      
}// end of remove

// PURPOSE: Finds the Maximum element in the left sub-tree of V
// and also deletes that vertex
// PARA: V is for the root/starting point 
el_t BST::findMax(Vertex *V)
{
  Vertex *Parent = V;
  V = V->Left;          // start with the left child of V
  
  while(V->Right != NULL) // while the right child of V is still available
  {
    Parent = V->Right; // update Parent and V to go to the right
    V = V->Right;	
  }
  
  // reached NULL Right  -- V now has the MAX element
  el_t X = V->Elem;
  cout << "...Max is " << X << endl;
  remove(V, Parent);    // remove the MAX vertex 
  return X;             // return the MAX element
  
}// end of FindMax


//PURPOSE: calls height() and BF() to calcuate height and BF of all nodes
//pARA: V is the starting point
void BST::climbUp(Vertex* V)
{
  cout << "...Start climbing up to adjust heights ......" << endl;
  while (V != NULL)
    {
              // ** compute V->Height  based on the left/right children's heights
             V->Height = height(V);
                  // ** compute V->Balance based on the left/right children's heights
             V->Balance = BF(V);

        cout << "..." << V->Elem << "'s height: "
         << V->Height << " with balance: " << V->Balance << endl;
          //**go up to the parent
          //
         if(V->Balance == 2 || V->Balance == -2)
             fixIt(V);


           V = V->Up;
         
      }
   }


//PURPSOE: calcute height of a vertex
//PARAMTER: V is the root   
 int BST::height(Vertex*V)
  {
      if(V == NULL)
         return -1;//gets rid of extra +1 due to height's starting point is 0 not 1
      else
   return 1+ max(height(V->Left),height(V->Right));//adds 1 to height until V is null
}

//PURPOSE: calculate BF of a vertex
//PARAMETER: V is the vertex you are trying to find the BF of 
 int BST :: BF(Vertex* V)
   {
    return (height(V->Right) - height(V->Left));
              
  }


//Note that rotated.out shows what happens if you rotate the tree
//everytime Balance -2 or 2 is found, and the tree is displayed
//as soon as the rotation is completed.

//Hint: I called fixIt from climbUp whenever 2 or -2
 //     was found as V->Balance.
  //    And fixIt called the correct
  //    rotation routine(s) based on V's BF and the BF of
   //   a sub-tree.
   //   And then Display in Inorder to show the fixed tree.

// Red is where +2 or -2 was found
// PURPOSE: fix tree according to BF of a vertex
// PARA: BAd Vertex that has BF of 2 or -2
 void BST::fixIt(Vertex* Red)
 { cout << ">>>Fixing an unbalanced node at " << Red->Elem << endl;

  Vertex* Pivot;
  if (Red->Balance == 2 && Red->Right->Balance == 1) // case 1
        {
           cout << "   case 1: right heavy so rotate to left" << endl;
        Pivot =  rotateLeft(Red);//single left rotation 
        }
  else if(Red->Balance == -2 && Red->Left->Balance == -1)//case 2
  {
  cout << "	case 2: left heavy so rotate to right" << endl;
       Pivot =  rotateRight(Red);//single right rotation
  }
  else if(Red->Balance == 2 && Red->Right->Balance == -1)//case 3
  {
   cout << "	case 3: right heavy with left heavy substree" << endl;
    Pivot =  rotateRight(Red->Right);//right rotation for right sub tree
   Pivot =  rotateLeft(Red);//left rotation for red tree
  }
  else if(Red->Balance == -2 && Red->Left->Balance == 1)//case 4
  {
  cout << "	case 4: left heavy with right heavy substree" << endl;
  Pivot = rotateLeft(Red->Left);//left rotation for left-substree
  Pivot = rotateRight(Red);//right rotation of red tree 

  }
//                          // handle all other cases here

     if (Root == Red)//if the root is still the bad vertex make it equal to pivot
             { Root = Pivot; // new Root
              cout << "   New root is: " << Root->Elem << endl;}//show new root
              cout << ">>>Fixed" << endl;
             Display();//display tree
    }

Vertex* BST::rotateLeft(Vertex* Red)
{
  Vertex * Pivot;//replacement of root of sub tree

  Pivot = Red->Right;//Right child of the red node is the pivot
  Red->Right = Pivot->Left;//red right is equal to pivot LC
  Pivot->Left = Red;//pivot LC is red

//update up link of red RC
 if(Red->Right != NULL)
   Red->Right->Up  = Red;


//update up link for pivot
  Pivot->Up = Red->Up;
  Red->Up = Pivot;//update up link for red

//update parent of red to point to pivot
 if(Pivot->Up != NULL){
   if(Pivot->Up->Left == Red)//this means parent of red is point to red still, not pivot
     Pivot->Up->Left = Pivot;
   else
     Pivot->Up->Right = Pivot;//else point parent RC to pivot
  }

 //updat height of pivot and red
 Pivot->Height = height(Pivot);
 Red->Height = height(Red);  

//update BF  of pivot and red
 Pivot->Balance = BF(Pivot);
  Red->Balance = BF(Red);

 return Pivot;//returning pivot 
}


Vertex*  BST::rotateRight(Vertex* Red)
{
  Vertex * Pivot; 

 Pivot = Red->Left;
 Red->Left = Pivot->Right;
 Pivot->Right = Red;

//update up link of red left child
if(Red->Left != NULL)
 Red->Left->Up = Red;

//update pivot up link
Pivot->Up = Red->Up;
Red->Up = Pivot;//update red up link

//update parent of red to point to pivot
if(Pivot->Up != NULL){
 if(Pivot->Up->Left == Red)//if parent left  pointing to red set parent LC  to pivot
  Pivot->Up->Left = Pivot;
else 
 Pivot->Up->Right = Pivot;//otherwise set parent RC to pivot
}

///updating heights of pivot and red
 Pivot->Height = height(Pivot);
 Red->Height = height(Red);

//updating BF of pivot and red
  Pivot->Balance = BF(Pivot);
 Red->Balance = BF(Red);

 
 return Pivot; 
}
