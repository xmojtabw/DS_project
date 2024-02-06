# Implementation of *kd tree* in cpp language
You can read about K-D Trees [here](https://www.baeldung.com/cs/k-d-trees).\
Note: In this implementation we save pizza shops which has a x and y coordinates and a name in a k-d tree.\
Note2: You can read about project [here].
## Commands
- Add-N [name] (X1,Y1) (X2,Y2) (X3,Y3) (X4,Y4)\
   *(Adds a neighborhood which is rectangle.)*[^1]
- Add-P [x-coordinate] [y-coordinate] [name]\
  *(Adds a main branch pizza shop into the k-d tree.)*
- Add-Br [x-coordinate] [y-coordinate] [name] [main_branch]\
   *(Adds a sub branch of pizza shop into the k-d tree which belongs to a [main_branch] pizza shop.)*
- Del-Br [x-coordinate] [y-coordinate]\
   *(Deletes a branch with coordinates.)*[^2]
- List-P [neighborhood_name]\
  *(Shows pizza shops inside this neighborhood.)*
- List-Brs [main_branch name]\
   *(Shows sub pizza shops of main_branch.)*
- Near-P [x-coordinate] [y-coordinate]\
   *(Shows the nearest pizza shop to this coordinates.)*
- Near-Br [x-coordinate] [y-coordinate] [main_branch name]\
   *(Shows the nearest pizza shop to this coordinates of main_branch.)*
- Avail-P [x] [y] [R]\
   *(Shows pizza shops inside a circle with an x,y center, and R radius.)*
- Most-Brs\
   *(Shows main branch pizza shop which has the most sub branches.)*
- Undo [Time] [Sub-Time]\
   *(Undo to time which you enter the Time'th command.)*

[^1]: Notice you must enter pure rectangle which means X1 = X2, Y1 = Y3, X3 = X4, Y2 = Y4.
[^2]: Cannot delete a pizzeria which is main branch!
